/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <activemq/connector/openwire/marshal/v2/ProducerInfoMarshaller.h>

#include <activemq/connector/openwire/commands/ProducerInfo.h>

//
//     NOTE!: This file is autogenerated - do not modify!
//            if you need to make a change, please see the Java Classes in the
//            activemq-core module
//

using namespace std;
using namespace activemq;
using namespace activemq::io;
using namespace activemq::connector;
using namespace activemq::connector::openwire;
using namespace activemq::connector::openwire::commands;
using namespace activemq::connector::openwire::marshal;
using namespace activemq::connector::openwire::utils;
using namespace activemq::connector::openwire::marshal::v2;

///////////////////////////////////////////////////////////////////////////////
DataStructure* ProducerInfoMarshaller::createObject() const {
    return new ProducerInfo();
}

///////////////////////////////////////////////////////////////////////////////
unsigned char ProducerInfoMarshaller::getDataStructureType() const {
    return ProducerInfo::ID_PRODUCERINFO;
}

///////////////////////////////////////////////////////////////////////////////
void ProducerInfoMarshaller::tightUnmarshal( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataInputStream* dataIn, BooleanStream* bs ) throw( io::IOException ) {

    try {

        BaseCommandMarshaller::tightUnmarshal( wireFormat, dataStructure, dataIn, bs );

        ProducerInfo* info =
            dynamic_cast<ProducerInfo*>( dataStructure );
        info->setProducerId( dynamic_cast< ProducerId* >(
            tightUnmarshalCachedObject( wireFormat, dataIn, bs ) ) );
        info->setDestination( dynamic_cast< ActiveMQDestination* >(
            tightUnmarshalCachedObject( wireFormat, dataIn, bs ) ) );

        if( bs->readBoolean() ) {
            short size = dataIn->readShort();
            info->getBrokerPath().reserve( size );
            for( int i = 0; i < size; i++ ) {
                info->getBrokerPath().push_back( dynamic_cast< BrokerId* >(
                    tightUnmarshalNestedObject( wireFormat, dataIn, bs ) ) );
            }
        }
        else {
            info->getBrokerPath().clear();
        }
        info->setDispatchAsync( bs->readBoolean() );
    }
    AMQ_CATCH_RETHROW( io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, io::IOException )
    AMQ_CATCHALL_THROW( io::IOException )
}

///////////////////////////////////////////////////////////////////////////////
int ProducerInfoMarshaller::tightMarshal1( OpenWireFormat* wireFormat, DataStructure* dataStructure, BooleanStream* bs ) throw( io::IOException ) {

    try {

        ProducerInfo* info =
            dynamic_cast<ProducerInfo*>( dataStructure );

        int rc = BaseCommandMarshaller::tightMarshal1( wireFormat, dataStructure, bs );
        rc += tightMarshalCachedObject1( wireFormat, info->getProducerId(), bs );
        rc += tightMarshalCachedObject1( wireFormat, info->getDestination(), bs );
        rc += tightMarshalObjectArray1( wireFormat, info->getBrokerPath(), bs );
        bs->writeBoolean( info->isDispatchAsync() );

        return rc + 0;
    }
    AMQ_CATCH_RETHROW( io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, io::IOException )
    AMQ_CATCHALL_THROW( io::IOException )
}

///////////////////////////////////////////////////////////////////////////////
void ProducerInfoMarshaller::tightMarshal2( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataOutputStream* dataOut, BooleanStream* bs ) throw( io::IOException ) {

    try {

        BaseCommandMarshaller::tightMarshal2( wireFormat, dataStructure, dataOut, bs );

        ProducerInfo* info =
            dynamic_cast<ProducerInfo*>( dataStructure );
        tightMarshalCachedObject2( wireFormat, info->getProducerId(), dataOut, bs );
        tightMarshalCachedObject2( wireFormat, info->getDestination(), dataOut, bs );
        tightMarshalObjectArray2( wireFormat, info->getBrokerPath(), dataOut, bs );
        bs->readBoolean();
    }
    AMQ_CATCH_RETHROW( io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, io::IOException )
    AMQ_CATCHALL_THROW( io::IOException )
}

///////////////////////////////////////////////////////////////////////////////
void ProducerInfoMarshaller::looseUnmarshal( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataInputStream* dataIn ) throw( io::IOException ) {

    try {

        BaseCommandMarshaller::looseUnmarshal( wireFormat, dataStructure, dataIn );
        ProducerInfo* info =
            dynamic_cast<ProducerInfo*>( dataStructure );
        info->setProducerId( dynamic_cast< ProducerId* >( 
            looseUnmarshalCachedObject( wireFormat, dataIn ) ) );
        info->setDestination( dynamic_cast< ActiveMQDestination* >( 
            looseUnmarshalCachedObject( wireFormat, dataIn ) ) );

        if( dataIn->readBoolean() ) {
            short size = dataIn->readShort();
            info->getBrokerPath().reserve( size );
            for( int i = 0; i < size; i++ ) {
                info->getBrokerPath().push_back( dynamic_cast<BrokerId* >(
                    looseUnmarshalNestedObject( wireFormat, dataIn ) ) );
            }
        }
        else {
            info->getBrokerPath().clear();
        }
        info->setDispatchAsync( dataIn->readBoolean() );
    }
    AMQ_CATCH_RETHROW( io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, io::IOException )
    AMQ_CATCHALL_THROW( io::IOException )
}

///////////////////////////////////////////////////////////////////////////////
void ProducerInfoMarshaller::looseMarshal( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataOutputStream* dataOut ) throw( io::IOException ) {

    try {

        ProducerInfo* info =
            dynamic_cast<ProducerInfo*>( dataStructure );
         BaseCommandMarshaller::looseMarshal( wireFormat, dataStructure, dataOut );

        looseMarshalCachedObject( wireFormat, info->getProducerId(), dataOut );
        looseMarshalCachedObject( wireFormat, info->getDestination(), dataOut );
        looseMarshalObjectArray( wireFormat, info->getBrokerPath(), dataOut );
        dataOut->writeBoolean( info->isDispatchAsync() );
    }
    AMQ_CATCH_RETHROW( io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, io::IOException )
    AMQ_CATCHALL_THROW( io::IOException )
}

