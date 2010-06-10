/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <decaf/util/concurrent/locks/ReentrantLock.h>

#include <decaf/lang/Thread.h>

#include <sstream>

#if HAVE_PTHREAD_H
#include <pthread.h>
#endif
#if HAVE_PTHREAD_H
#include <pthread.h>
#endif
#if HAVE_SIGNAL_H
#include <signal.h>
#endif
#if HAVE_STRING_H
#include <string.h>
#endif
#if HAVE_SCHED_H
#include <sched.h>
#endif
#if HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#if HAVE_TIME_H
#include <time.h>
#endif
#if HAVE_ERRNO_H
#include <errno.h>
#endif

using namespace decaf;
using namespace decaf::lang;
using namespace decaf::lang::exceptions;
using namespace decaf::util;
using namespace decaf::util::concurrent;
using namespace decaf::util::concurrent::locks;

////////////////////////////////////////////////////////////////////////////////
namespace decaf{
namespace util{
namespace concurrent{
namespace locks{

    /**
     * Lock Handle provides the data needed to keep track of the Lock on
     * the supported platforms.
     */
    class LockHandle {
    public:

        // OS specific Lock Object.
#ifdef HAVE_PTHREAD_H
        pthread_mutex_t handle;
#else
        CRITICAL_SECTION handle;
#endif

        // Lock Status Members
        Thread* lock_owner;
        volatile long long lock_owner_tid;
        volatile long long lock_count;

    public:

        LockHandle() {

            lock_count = 0;
            lock_owner_tid = 0;
            lock_owner = NULL;

#ifdef HAVE_PTHREAD_H

            if( pthread_mutex_init( &handle, NULL ) != 0 ) {
                throw RuntimeException(
                    __FILE__, __LINE__, "Failed to create OS Mutex object." );
            }

#else

            try{
                InitializeCriticalSection( &handle );
            } catch(...) {
                throw RuntimeException(
                    __FILE__, __LINE__, "Failed to create OS Mutex object." );
            }

#endif
        }

        ~LockHandle() {
#ifdef HAVE_PTHREAD_H
            pthread_mutex_destroy( &handle );
#else
            DeleteCriticalSection( &handle );
#endif
        }

    };

    /**
     * Internally defined Condition Object.
     *
     * This Condition Object implements a Condition object that is associated with
     * a single ReentrantLock object and has access to its internal LockHandle.
     */
    class ConditionObject : public Condition {
    private:

        LockHandle* lock;

#ifdef HAVE_PTHREAD_H
        pthread_cond_t condition;
#else
        HANDLE semaphore;
        CRITICAL_SECTION criticalSection;
        unsigned int numWaiting;
        unsigned int numWake;
        unsigned int generation;
#endif

    public:

        ConditionObject( LockHandle* lock ) {

            this->lock = lock;

#ifdef HAVE_PTHREAD_H
            if( pthread_cond_init( &condition, NULL ) != 0 ) {
                throw RuntimeException(
                    __FILE__, __LINE__, "Failed to initialize OS Condition object." );
            }
#else
            semaphore = CreateSemaphore( NULL, 0, LONG_MAX, NULL );
            if( semaphore == NULL ) {
                throw RuntimeException(
                    __FILE__, __LINE__, "Failed to initialize OS Condition object." );
            }

            try{
                InitializeCriticalSection( &criticalSection );
            } catch(...) {
                throw RuntimeException(
                    __FILE__, __LINE__, "Failed to initialize OS Condition object." );
            }

            this->numWaiting = 0;
            this->numWake = 0;
            this->generation = 0;
#endif
        }

        virtual ~ConditionObject() {
#ifdef HAVE_PTHREAD_H
            pthread_cond_destroy( &condition );
#else
            CloseHandle( semaphore );
            ::DeleteCriticalSection( &criticalSection );
#endif
        }

        virtual void await()
            throw( decaf::lang::exceptions::RuntimeException,
                   decaf::lang::exceptions::InterruptedException,
                   decaf::lang::exceptions::IllegalMonitorStateException );

        virtual void awaitUninterruptibly()
            throw( decaf::lang::exceptions::RuntimeException,
                   decaf::lang::exceptions::IllegalMonitorStateException );

        virtual long long awaitNanos( long long nanosTimeout )
            throw( decaf::lang::exceptions::RuntimeException,
                   decaf::lang::exceptions::InterruptedException,
                   decaf::lang::exceptions::IllegalMonitorStateException );

        virtual bool await( long long time, const TimeUnit& unit )
            throw( decaf::lang::exceptions::RuntimeException,
                   decaf::lang::exceptions::InterruptedException,
                   decaf::lang::exceptions::IllegalMonitorStateException );

        virtual bool awaitUntil( const Date& deadline )
            throw( decaf::lang::exceptions::RuntimeException,
                   decaf::lang::exceptions::InterruptedException,
                   decaf::lang::exceptions::IllegalMonitorStateException );

        virtual void signal() throw ( decaf::lang::exceptions::RuntimeException );

        virtual void signalAll() throw ( decaf::lang::exceptions::RuntimeException );

    };

}}}}

////////////////////////////////////////////////////////////////////////////////
ReentrantLock::ReentrantLock() {
    this->handle.reset( new LockHandle );
}

////////////////////////////////////////////////////////////////////////////////
ReentrantLock::~ReentrantLock() {
    try{
        this->handle.reset( NULL );
    }
    DECAF_CATCHALL_NOTHROW()
}

////////////////////////////////////////////////////////////////////////////////
void ReentrantLock::lock() throw( decaf::lang::exceptions::RuntimeException ) {

    long long threadId = Thread::getId();

    if( threadId == handle->lock_owner_tid ) {
        handle->lock_count++;
    } else {

#ifdef HAVE_PTHREAD_H

        if( pthread_mutex_lock( &( handle->handle ) ) != 0 ) {
            throw RuntimeException(
                __FILE__, __LINE__, "Failed to Lock OS Mutex" );
        }

#else

        try{
            EnterCriticalSection( &handle->handle );
        } catch(...) {
            throw RuntimeException(
                __FILE__, __LINE__, "Failed to Lock OS Mutex" );
        }

#endif

        handle->lock_owner_tid = threadId;
        handle->lock_owner = Thread::currentThread();
        handle->lock_count = 1;
    }
}

////////////////////////////////////////////////////////////////////////////////
void ReentrantLock::lockInterruptibly() throw ( decaf::lang::exceptions::RuntimeException,
                                                decaf::lang::exceptions::InterruptedException ) {

    this->lock();
}

////////////////////////////////////////////////////////////////////////////////
bool ReentrantLock::tryLock() throw( decaf::lang::exceptions::RuntimeException ) {

    long long threadId = Thread::getId();

    if( threadId == handle->lock_owner_tid ) {
        handle->lock_count++;
    } else {

        unsigned int result = 0;

#ifdef HAVE_PTHREAD_H
        result = pthread_mutex_trylock( &( handle->handle ) );
#else
        try{
            result = TryEnterCriticalSection( &handle->handle );
        } catch(...) {
            throw RuntimeException(
                __FILE__, __LINE__, "Failed to Lock OS Mutex" );
        }
#endif

        if( result == 0 ) {
            handle->lock_owner_tid = threadId;
            handle->lock_count = 1;
            handle->lock_owner = Thread::currentThread();
        } else {
            return false;
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
bool ReentrantLock::tryLock( long long time, const TimeUnit& unit )
    throw ( decaf::lang::exceptions::RuntimeException,
            decaf::lang::exceptions::InterruptedException ) {

//    long long threadId = Thread::getId();
//
//    if( threadId == handle->lock_owner_tid ) {
//        handle->lock_count++;
//    } else {
//
//        if( pthread_mutex_timedlock( &( handle->handle ) ) == 0 ) {
//            handle->lock_owner_tid = threadId;
//            handle->lock_count = 1;
//            handle->lock_owner = Thread::currentThread();
//        } else {
//            return false;
//        }
//    }
//
//    return true;

    return false;
}

////////////////////////////////////////////////////////////////////////////////
void ReentrantLock::unlock() throw( decaf::lang::exceptions::RuntimeException,
                                    decaf::lang::exceptions::IllegalMonitorStateException ) {

    if( handle->lock_owner_tid == 0 ) {
        return;
    }

    if( handle->lock_owner_tid != Thread::getId() ) {
        throw IllegalMonitorStateException(
            __FILE__, __LINE__,
            "Unlock Failed, this thread is not the Lock Owner!" );
    }

    handle->lock_count--;

    if( handle->lock_count == 0 ) {
        handle->lock_owner_tid = 0;
        handle->lock_owner = NULL;

#ifdef HAVE_PTHREAD_H
        pthread_mutex_unlock( &( handle->handle ) );
#else
        try{
            LeaveCriticalSection( &handle->handle );
        } catch(...) {
            throw RuntimeException(
                __FILE__, __LINE__, "Failed to Unlock OS Mutex" );
        }
#endif
    }
}

////////////////////////////////////////////////////////////////////////////////
Condition* ReentrantLock::newCondition()
    throw ( decaf::lang::exceptions::RuntimeException,
            decaf::lang::exceptions::UnsupportedOperationException ) {

    return new ConditionObject( this->handle.get() );
}

////////////////////////////////////////////////////////////////////////////////
int ReentrantLock::getHoldCount() const {

    long long threadId = Thread::getId();

    if( threadId == handle->lock_owner_tid ) {
        return (int)handle->lock_count;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
bool ReentrantLock::isHeldByCurrentThread() const {
    long long threadId = Thread::getId();

    if( threadId == handle->lock_owner_tid ) {
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool ReentrantLock::isLocked() const {
    return this->handle->lock_count > 0;
}

////////////////////////////////////////////////////////////////////////////////
bool ReentrantLock::isFair() const {
    return false;
}

////////////////////////////////////////////////////////////////////////////////
std::string ReentrantLock::toString() const {
    std::ostringstream result;

    result << "ReentrantLock: ";

    Thread* current = handle->lock_owner;

    if( current != NULL ) {
        result << "[Locked by Thread: " << current->getName() << "]";
    } else {
        result << "[Unlocked]";
    }

    return result.str();
}

////////////////////////////////////////////////////////////////////////////////
void ConditionObject::await()
    throw( decaf::lang::exceptions::RuntimeException,
           decaf::lang::exceptions::InterruptedException,
           decaf::lang::exceptions::IllegalMonitorStateException ) {

    // Save the current owner as we are going to unlock and release for
    // someone else to lock on potentially.  When we come back and
    // re-lock we want to restore to the state we were in before.
    long long lock_owner_tid = lock->lock_owner_tid;
    long long lock_count = lock->lock_count;
    Thread* lock_owner = lock->lock_owner;

    // Clear the owner for now.
    lock->lock_owner = NULL;
    lock->lock_count = 0;
    lock->lock_owner_tid = 0;

#ifdef HAVE_PTHREAD_H
    if( pthread_cond_wait( &condition, &lock->handle ) != 0 ) {
        throw RuntimeException(
            __FILE__, __LINE__, "Failed to wait on OS Condition object." );
    }
#else

#endif

    // restore the owner
    lock->lock_owner = lock_owner;
    lock->lock_count = lock_count;
    lock->lock_owner_tid = lock_owner_tid;
}

////////////////////////////////////////////////////////////////////////////////
void ConditionObject::awaitUninterruptibly()
    throw( decaf::lang::exceptions::RuntimeException,
           decaf::lang::exceptions::IllegalMonitorStateException ) {

    this->await();
}

////////////////////////////////////////////////////////////////////////////////
long long ConditionObject::awaitNanos( long long nanosTimeout )
    throw( decaf::lang::exceptions::RuntimeException,
           decaf::lang::exceptions::InterruptedException,
           decaf::lang::exceptions::IllegalMonitorStateException ) {

    // Save the current owner as we are going to unlock and release for
    // someone else to lock on potentially.  When we come back and
    // re-lock we want to restore to the state we were in before.
    long long lock_owner_tid = lock->lock_owner_tid;
    long long lock_count = lock->lock_count;
    Thread* lock_owner = lock->lock_owner;

    // Clear the owner for now.
    lock->lock_owner = NULL;
    lock->lock_count = 0;
    lock->lock_owner_tid = 0;

    // Get time now as nanoseconds.
    struct timeval tv;
    gettimeofday( &tv, NULL );
    long long timeNow = TimeUnit::SECONDS.toNanos( tv.tv_sec ) +
                        TimeUnit::MICROSECONDS.toNanos( tv.tv_usec );

    // Convert delay to nanoseconds and add it to now.
    long long delay = nanosTimeout + timeNow;

    struct timespec abstime;
    abstime.tv_sec = TimeUnit::NANOSECONDS.toSeconds( delay );
    abstime.tv_nsec = delay % 1000000000;

#ifdef HAVE_PTHREAD_H
    unsigned int result = pthread_cond_timedwait( &condition, &lock->handle, &abstime );
#else

#endif

    // restore the owner
    lock->lock_owner = lock_owner;
    lock->lock_count = lock_count;
    lock->lock_owner_tid = lock_owner_tid;

    if( result != 0 && result != ETIMEDOUT ) {
        throw RuntimeException(
            __FILE__, __LINE__, "Failed to wait on OS Condition object." );
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
bool ConditionObject::await( long long time, const TimeUnit& unit )
    throw( decaf::lang::exceptions::RuntimeException,
           decaf::lang::exceptions::InterruptedException,
           decaf::lang::exceptions::IllegalMonitorStateException ) {

    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool ConditionObject::awaitUntil( const Date& deadline )
    throw( decaf::lang::exceptions::RuntimeException,
           decaf::lang::exceptions::InterruptedException,
           decaf::lang::exceptions::IllegalMonitorStateException ) {

    return false;
}

////////////////////////////////////////////////////////////////////////////////
void ConditionObject::signal() throw ( decaf::lang::exceptions::RuntimeException ) {

#ifdef HAVE_PTHREAD_H
    if( pthread_cond_signal( &condition ) ) {
        throw RuntimeException(
            __FILE__, __LINE__, "Failed to signal OS Condition object." );
    }
#else

    try {

        bool doWake = false;

        EnterCriticalSection( &criticalSection );

        if( numWaiting > numWake ) {
            doWake = true;
            numWake++;
            generation++;
        }

        LeaveCriticalSection( &criticalSection );

        if( doWake ) {
            ReleaseSemaphore( semaphore, 1, NULL );
        }

    } catch(...) {
        throw RuntimeException(
            __FILE__, __LINE__, "Failed to signal OS Condition object." );
    }

#endif
}

////////////////////////////////////////////////////////////////////////////////
void ConditionObject::signalAll() throw ( decaf::lang::exceptions::RuntimeException ) {

#ifdef HAVE_PTHREAD_H
    if( pthread_cond_broadcast( &condition ) ) {
        throw RuntimeException(
            __FILE__, __LINE__, "Failed to broadcast signal OS Condition object." );
    }
#else

    try {

        unsigned int numWakeTemp = 0;

        EnterCriticalSection( &criticalSection );

        if( numWaiting > numWake ) {
            numWakeTemp = numWaiting - numWake;
            numWake = numWaiting;
            generation++;
        }

        LeaveCriticalSection( &criticalSection );

        if( numWakeTemp ) {
            ReleaseSemaphore( semaphore, numWake, NULL );
        }

    } catch(...) {
        throw RuntimeException(
            __FILE__, __LINE__, "Failed to broadcast signal OS Condition object." );
    }

#endif
}
