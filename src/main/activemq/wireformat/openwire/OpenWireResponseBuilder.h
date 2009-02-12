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

#ifndef ACTIVEMQ_WIREFORMAT_OPENWIRE_OPENWIRERESPONSEBUILDER_H_
#define ACTIVEMQ_WIREFORMAT_OPENWIRE_OPENWIRERESPONSEBUILDER_H_

#include <activemq/util/Config.h>
#include <activemq/transport/mock/MockTransport.h>
#include <decaf/util/StlQueue.h>

namespace activemq{
namespace wireformat{
namespace openwire{

    class AMQCPP_API OpenWireResponseBuilder :
        public transport::mock::MockTransport::ResponseBuilder{
    public:

        OpenWireResponseBuilder() {}
        virtual ~OpenWireResponseBuilder() {}

        virtual commands::Response* buildResponse( const commands::Command* command );

        virtual void buildIncomingCommands(
            const commands::Command* command,
            decaf::util::StlQueue<commands::Command*>& queue );

    };

}}}

#endif /*ACTIVEMQ_WIREFORMAT_OPENWIRE_OPENWIRERESPONSEBUILDER_H_*/
