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

// All CPP Unit tests are registered in here so we can disable them and
// enable them easily in one place.

#include <decaf/internal/util/ByteArrayAdapterTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::util::ByteArrayAdapterTest );
#include <decaf/internal/util/TimerTaskHeapTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::util::TimerTaskHeapTest );

#include <decaf/internal/net/ssl/DefaultSSLSocketFactoryTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::net::ssl::DefaultSSLSocketFactoryTest );

#include <decaf/internal/nio/ByteArrayBufferTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::nio::ByteArrayBufferTest );
#include <decaf/internal/nio/BufferFactoryTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::nio::BufferFactoryTest );
#include <decaf/internal/nio/CharArrayBufferTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::nio::CharArrayBufferTest );
#include <decaf/internal/nio/DoubleArrayBufferTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::nio::DoubleArrayBufferTest );
#include <decaf/internal/nio/FloatArrayBufferTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::nio::FloatArrayBufferTest );
#include <decaf/internal/nio/LongArrayBufferTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::nio::LongArrayBufferTest );
#include <decaf/internal/nio/IntArrayBufferTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::nio::IntArrayBufferTest );
#include <decaf/internal/nio/ShortArrayBufferTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::nio::ShortArrayBufferTest );

#include <decaf/internal/net/URIEncoderDecoderTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::net::URIEncoderDecoderTest );
#include <decaf/internal/net/URIHelperTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::internal::net::URIHelperTest );

#include <decaf/nio/BufferTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::nio::BufferTest );

#include <decaf/io/InputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::InputStreamTest );
#include <decaf/io/OutputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::OutputStreamTest );
#include <decaf/io/FilterInputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::FilterInputStreamTest );
#include <decaf/io/FilterOutputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::FilterOutputStreamTest );
#include <decaf/io/BufferedInputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::BufferedInputStreamTest );
#include <decaf/io/BufferedOutputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::BufferedOutputStreamTest );
#include <decaf/io/ByteArrayInputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::ByteArrayInputStreamTest );
#include <decaf/io/ByteArrayOutputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::ByteArrayOutputStreamTest );
#include <decaf/io/PushbackInputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::PushbackInputStreamTest );
#include <decaf/io/DataInputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::DataInputStreamTest );
#include <decaf/io/DataOutputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::DataOutputStreamTest );
#include <decaf/io/WriterTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::WriterTest );
#include <decaf/io/ReaderTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::ReaderTest );
#include <decaf/io/OutputStreamWriterTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::OutputStreamWriterTest );
#include <decaf/io/InputStreamReaderTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::io::InputStreamReaderTest );

#include <decaf/lang/MathTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::MathTest );
#include <decaf/lang/ByteTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::ByteTest );
#include <decaf/lang/CharacterTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::CharacterTest );
#include <decaf/lang/BooleanTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::BooleanTest );
#include <decaf/lang/ShortTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::ShortTest );
#include <decaf/lang/IntegerTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::IntegerTest );
#include <decaf/lang/LongTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::LongTest );
#include <decaf/lang/FloatTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::FloatTest );
#include <decaf/lang/DoubleTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::DoubleTest );
#include <decaf/lang/ExceptionTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::ExceptionTest );
#include <decaf/lang/ThreadTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::ThreadTest );
#include <decaf/lang/ThreadLocalTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::ThreadLocalTest );
#include <decaf/lang/SystemTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::SystemTest );
#include <decaf/lang/PointerTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::PointerTest );
#include <decaf/lang/ArrayPointerTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::ArrayPointerTest );
#include <decaf/lang/StringTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::StringTest );
#include <decaf/lang/StringBuilderTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::StringBuilderTest );
#include <decaf/lang/StringBufferTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::lang::StringBufferTest );

#include <decaf/net/InetAddressTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::net::InetAddressTest );
#include <decaf/net/Inet4AddressTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::net::InetAddressTest );
#include <decaf/net/Inet6AddressTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::net::InetAddressTest );
#include <decaf/net/SocketFactoryTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::net::SocketFactoryTest );
#include <decaf/net/ServerSocketTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::net::ServerSocketTest );
#include <decaf/net/SocketTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::net::SocketTest );
#include <decaf/net/URITest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::net::URITest );
#include <decaf/net/URLTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::net::URLTest );
#include <decaf/net/URISyntaxExceptionTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::net::URISyntaxExceptionTest );
#include <decaf/net/URLEncoderTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::net::URLEncoderTest );
#include <decaf/net/URLDecoderTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::net::URLDecoderTest );

#include <decaf/net/ssl/SSLSocketFactoryTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::net::ssl::SSLSocketFactoryTest );

#include <decaf/util/concurrent/CopyOnWriteArrayListTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::CopyOnWriteArrayListTest );
#include <decaf/util/concurrent/CopyOnWriteArraySetTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::CopyOnWriteArraySetTest );
#include <decaf/util/concurrent/ConcurrentStlMapTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::ConcurrentStlMapTest );
#include <decaf/util/concurrent/CountDownLatchTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::CountDownLatchTest );
#include <decaf/util/concurrent/MutexTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::MutexTest );
#include <decaf/util/concurrent/ThreadPoolExecutorTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::ThreadPoolExecutorTest );
#include <decaf/util/concurrent/ExecutorsTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::ExecutorsTest );
#include <decaf/util/concurrent/TimeUnitTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::TimeUnitTest );
#include <decaf/util/concurrent/LinkedBlockingQueueTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::LinkedBlockingQueueTest );
#include <decaf/util/concurrent/SemaphoreTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::SemaphoreTest );
#include <decaf/util/concurrent/FutureTaskTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::FutureTaskTest );
#include <decaf/util/concurrent/AbstractExecutorServiceTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::AbstractExecutorServiceTest );
#include <decaf/util/concurrent/ConcurrentHashMapTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::ConcurrentHashMapTest );

#include <decaf/util/concurrent/atomic/AtomicBooleanTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::atomic::AtomicBooleanTest );
#include <decaf/util/concurrent/atomic/AtomicIntegerTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::atomic::AtomicIntegerTest );
#include <decaf/util/concurrent/atomic/AtomicReferenceTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::atomic::AtomicReferenceTest );

#include <decaf/util/concurrent/locks/LockSupportTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::locks::LockSupportTest );
#include <decaf/util/concurrent/locks/AbstractQueuedSynchronizerTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::locks::AbstractQueuedSynchronizerTest );
#include <decaf/util/concurrent/locks/ReentrantLockTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::locks::ReentrantLockTest );
#include <decaf/util/concurrent/locks/ReentrantReadWriteLockTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::concurrent::locks::ReentrantReadWriteLockTest );

#include <decaf/util/CollectionsTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::CollectionsTest );
#include <decaf/util/HashCodeTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::HashCodeTest );
#include <decaf/util/LinkedHashMapTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::LinkedHashMapTest );
#include <decaf/util/LinkedHashSetTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::LinkedHashSetTest );
#include <decaf/util/HashMapTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::HashMapTest );
//#include <decaf/util/HashSetTest.h>
//CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::HashSetTest );
#include <decaf/util/AbstractCollectionTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::AbstractCollectionTest );
#include <decaf/util/AbstractListTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::AbstractListTest );
#include <decaf/util/AbstractSequentialListTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::AbstractSequentialListTest );
#include <decaf/util/BitSetTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::BitSetTest );
#include <decaf/util/DateTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::DateTest );
#include <decaf/util/UUIDTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::UUIDTest );
#include <decaf/util/ListTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::ListTest );
#include <decaf/util/LinkedListTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::LinkedListTest );
#include <decaf/util/ArrayListTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::ArrayListTest );
#include <decaf/util/ArraysTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::ArraysTest );
#include <decaf/util/StlMapTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::StlMapTest );
#include <decaf/util/PropertiesTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::PropertiesTest );
#include <decaf/util/QueueTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::QueueTest );
#include <decaf/util/RandomTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::RandomTest );
#include <decaf/util/SetTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::SetTest );
#include <decaf/util/StringTokenizerTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::StringTokenizerTest );
#include <decaf/util/TimerTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::TimerTest );
#include <decaf/util/PriorityQueueTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::PriorityQueueTest );
#include <decaf/util/LRUCacheTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::LRUCacheTest );

#include <decaf/util/zip/DeflaterTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::zip::DeflaterTest );
#include <decaf/util/zip/InflaterTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::zip::InflaterTest );
#include <decaf/util/zip/Adler32Test.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::zip::Adler32Test );
#include <decaf/util/zip/CRC32Test.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::zip::CRC32Test );
#include <decaf/util/zip/CheckedInputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::zip::CheckedInputStreamTest );
#include <decaf/util/zip/CheckedOutputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::zip::CheckedOutputStreamTest );
#include <decaf/util/zip/DeflaterOutputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::zip::DeflaterOutputStreamTest );
#include <decaf/util/zip/InflaterInputStreamTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::util::zip::InflaterInputStreamTest );

#include <decaf/security/SecureRandomTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::security::SecureRandomTest );
#include <decaf/security/MessageDigestTest.h>
CPPUNIT_TEST_SUITE_REGISTRATION( decaf::security::MessageDigestTest );
