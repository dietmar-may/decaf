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

#include "ActiveMQConnectionFactoryTest.h"

#include <cms/Connection.h>
#include <decaf/util/concurrent/Concurrent.h>
#include <decaf/util/concurrent/Mutex.h>
#include <decaf/lang/Thread.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/core/ActiveMQConnection.h>
#include <activemq/core/ActiveMQSession.h>
#include <activemq/core/ActiveMQProducer.h>
#include <memory>

using namespace std;
using namespace activemq;
using namespace activemq::core;

//////////////////////////////////////////////////////////////////////////////////
//void ActiveMQConnectionFactoryTest::test1WithStomp()
//{
//    try
//    {
//        std::string URI =
//            "mock://127.0.0.1:23232?wireFormat=stomp";
//
//        ActiveMQConnectionFactory connectionFactory( URI );
//
//        cms::Connection* connection =
//            connectionFactory.createConnection();
//
//        CPPUNIT_ASSERT( connection != NULL );
//
//        delete connection;
//
//        return;
//    }
//    AMQ_CATCH_NOTHROW( exceptions::ActiveMQException )
//    AMQ_CATCHALL_NOTHROW( )
//
//    CPPUNIT_ASSERT( false );
//}
//
//////////////////////////////////////////////////////////////////////////////////
//void ActiveMQConnectionFactoryTest::test2WithStomp()
//{
//    try
//    {
//        std::string URI = std::string() +
//            "mock://127.0.0.1:23232?wireFormat=stomp&"
//            "username=" + username + "&password=" + password +
//            "&client-id=" + clientId;
//
//        ActiveMQConnectionFactory connectionFactory( URI );
//
//        cms::Connection* connection =
//            connectionFactory.createConnection();
//        CPPUNIT_ASSERT( connection != NULL );
//
//        ActiveMQConnection* amqConnection =
//            dynamic_cast< ActiveMQConnection* >( connection );
//        CPPUNIT_ASSERT( amqConnection != NULL );
//
//        connector::Connector* connector =
//            dynamic_cast< connector::Connector* >(
//            amqConnection->getConnectionData()->getConnector() );
//        CPPUNIT_ASSERT( connector != NULL );
//
//        CPPUNIT_ASSERT( username == connector->getUsername() );
//        CPPUNIT_ASSERT( password == connector->getPassword() );
//        CPPUNIT_ASSERT( clientId == connector->getClientId() );
//
//        // Free the allocated connection object.
//        delete connection;
//
//        return;
//    }
//    AMQ_CATCH_NOTHROW( exceptions::ActiveMQException )
//    AMQ_CATCHALL_NOTHROW( )
//
//    CPPUNIT_ASSERT( false );
//}

////////////////////////////////////////////////////////////////////////////////
void ActiveMQConnectionFactoryTest::test1WithOpenWire()
{
    try
    {
        std::string URI =
            "mock://127.0.0.1:23232?wireFormat=openwire";

        ActiveMQConnectionFactory connectionFactory( URI );

        cms::Connection* connection =
            connectionFactory.createConnection();

        CPPUNIT_ASSERT( connection != NULL );

        delete connection;

        return;
    }
    AMQ_CATCH_NOTHROW( exceptions::ActiveMQException )
    AMQ_CATCHALL_NOTHROW( )

    CPPUNIT_ASSERT( false );
}

////////////////////////////////////////////////////////////////////////////////
void ActiveMQConnectionFactoryTest::test2WithOpenWire()
{
    try
    {
        std::string URI = std::string() +
            "mock://127.0.0.1:23232?wireFormat=openwire&"
            "username=" + username + "&password=" + password +
            "&client-id=" + clientId;

        ActiveMQConnectionFactory connectionFactory( URI );

        std::auto_ptr<cms::Connection> connection(
            connectionFactory.createConnection() );
        CPPUNIT_ASSERT( connection.get() != NULL );

        ActiveMQConnection* amqConnection =
            dynamic_cast< ActiveMQConnection* >( connection.get() );
        CPPUNIT_ASSERT( amqConnection != NULL );
        CPPUNIT_ASSERT( username == amqConnection->getUsername() );
        CPPUNIT_ASSERT( password == amqConnection->getPassword() );
        CPPUNIT_ASSERT( clientId == amqConnection->getClientId() );

        return;
    }
    AMQ_CATCH_NOTHROW( exceptions::ActiveMQException )
    AMQ_CATCHALL_NOTHROW( )

    CPPUNIT_ASSERT( false );
}

////////////////////////////////////////////////////////////////////////////////
void ActiveMQConnectionFactoryTest::testExceptionOnCreate() {
    try
    {
        std::string URI =
            "tcp://127.0.0.2:23232?wireFormat=openwire";

        ActiveMQConnectionFactory connectionFactory( URI );

        auto_ptr<cms::Connection> connection(
            connectionFactory.createConnection() );

        CPPUNIT_ASSERT( false );
    }
    AMQ_CATCH_NOTHROW( exceptions::ActiveMQException )
    AMQ_CATCHALL_NOTHROW( )
}

////////////////////////////////////////////////////////////////////////////////
void ActiveMQConnectionFactoryTest::testCreateWithURIOptions()
{
    try
    {
        std::string URI = std::string() +
            "mock://127.0.0.1:23232?connection.producerWindowSize=65536";

        ActiveMQConnectionFactory connectionFactory( URI );

        std::auto_ptr<cms::Connection> connection(
            connectionFactory.createConnection() );
        CPPUNIT_ASSERT( connection.get() != NULL );

        ActiveMQConnection* amqConnection =
            dynamic_cast< ActiveMQConnection* >( connection.get() );

        std::auto_ptr<ActiveMQSession> session( dynamic_cast<ActiveMQSession*>(
            amqConnection->createSession() ) );

        std::auto_ptr<ActiveMQProducer> producer( dynamic_cast<ActiveMQProducer*>(
            session->createProducer( NULL ) ) );

        CPPUNIT_ASSERT( producer->getProducerInfo().getWindowSize() == 65536 );

        return;
    }
    AMQ_CATCH_NOTHROW( exceptions::ActiveMQException )
    AMQ_CATCHALL_NOTHROW( )

    CPPUNIT_ASSERT( false );
}