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

#include <activemq/concurrent/Thread.h>
#include <activemq/concurrent/Runnable.h>
#include <activemq/concurrent/CountDownLatch.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/util/Integer.h>
#include <activemq/util/Config.h>
#include <activemq/util/Date.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <stdlib.h>
#include <iostream>

using namespace activemq;
using namespace activemq::core;
using namespace activemq::util;
using namespace activemq::concurrent;
using namespace cms;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
class SimpleProducer : public Runnable {
private:

    Connection* connection;
    Session* session;
    Destination* destination;
    MessageProducer* producer;
    bool useTopic;
    unsigned int numMessages;
    std::string brokerURI;
    std::string destURI;

public:

    SimpleProducer( const std::string& brokerURI,
                    unsigned int numMessages,
                    const std::string& destURI,
                    bool useTopic = false ){
        connection = NULL;
        session = NULL;
        destination = NULL;
        producer = NULL;
        this->numMessages = numMessages;
        this->useTopic = useTopic;
        this->brokerURI = brokerURI;
        this->destURI = destURI;
    }

    virtual ~SimpleProducer(){
        cleanup();
    }

    virtual void run() {
        try {
            // Create a ConnectionFactory
            ActiveMQConnectionFactory* connectionFactory =
                new ActiveMQConnectionFactory( brokerURI );

            // Create a Connection
            connection = connectionFactory->createConnection();
            connection->start();

            // free the factory, we are done with it.
            delete connectionFactory;

            // Create a Session
            session = connection->createSession( Session::AUTO_ACKNOWLEDGE );

            // Create the destination (Topic or Queue)
            if( useTopic ) {
                destination = session->createTopic( destURI );
            } else {
                destination = session->createQueue( destURI );
            }

            // Create a MessageProducer from the Session to the Topic or Queue
            producer = session->createProducer( destination );
            producer->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

            // Create the Thread Id String
            string threadIdStr = Integer::toString( Thread::getId() );

            // Create a messages
            string text = (string)"Hello world! from thread " + threadIdStr;

            for( int ix=0; ix<numMessages; ++ix ){
                TextMessage* message = session->createTextMessage( text );

                message->setIntProperty( "Integer", ix );

                // Tell the producer to send the message
                printf( "Sent message #%d from thread %s\n", ix+1, threadIdStr.c_str() );
                producer->send( message );

                delete message;
            }

        }catch ( CMSException& e ) {
            e.printStackTrace();
        }
    }

private:

    void cleanup(){

            // Destroy resources.
            try{
                if( destination != NULL ) delete destination;
            }catch ( CMSException& e ) { e.printStackTrace(); }
            destination = NULL;

            try{
                if( producer != NULL ) delete producer;
            }catch ( CMSException& e ) { e.printStackTrace(); }
            producer = NULL;

            // Close open resources.
            try{
                if( session != NULL ) session->close();
                if( connection != NULL ) connection->close();
            }catch ( CMSException& e ) { e.printStackTrace(); }

            try{
                if( session != NULL ) delete session;
            }catch ( CMSException& e ) { e.printStackTrace(); }
            session = NULL;

            try{
                if( connection != NULL ) delete connection;
            }catch ( CMSException& e ) { e.printStackTrace(); }
            connection = NULL;
    }
};

////////////////////////////////////////////////////////////////////////////////
int main(int argc AMQCPP_UNUSED, char* argv[] AMQCPP_UNUSED) {

    std::cout << "=====================================================\n";
    std::cout << "Starting the example:" << std::endl;
    std::cout << "-----------------------------------------------------\n";

    // Set the URI to point to the IPAddress of your broker.
    // add any optional params to the url to enable things like
    // tightMarshalling or tcp logging etc.  See the CMS website for
    // a full list of configuration options.
    //
    //  http://activemq.apache.org/cms/
    //
    // Wire Foormat Options:
    // =====================
    // Use either stomp or openwire, the default ports are different for each
    //
    // Examples:
    //    tcp://127.0.0.1:61616                      default to openwire
    //    tcp://127.0.0.1:61616?wireFormat=openwire  same as above
    //    tcp://127.0.0.1:61613?wireFormat=stomp     use stomp instead
    //
    std::string brokerURI =
        "tcp://127.0.0.1:61616"
        "?wireFormat=openwire"
        "&transport.useAsyncSend=true";
//        "&transport.commandTracingEnabled=true"
//        "&transport.tcpTracingEnabled=true";
//        "&wireFormat.tightEncodingEnabled=true";

    //============================================================
    // Total number of messages for this producer to send.
    //============================================================
    unsigned int numMessages = 32730;

    //============================================================
    // This is the Destination Name and URI options.  Use this to
    // customize where the Producer produces, to have the producer
    // use a topic or queue set the 'useTopics' flag.
    //============================================================
    std::string destURI = "TEST.FOO";

    //============================================================
    // set to true to use topics instead of queues
    // Note in the code above that this causes createTopic or
    // createQueue to be used in the producer.
    //============================================================
    bool useTopics = true;

    // Create the producer and run it.
    SimpleProducer producer( brokerURI, numMessages, destURI, useTopics );
    producer.run();

    std::cout << "-----------------------------------------------------\n";
    std::cout << "Finished with the example." << std::endl;
    std::cout << "=====================================================\n";
}
