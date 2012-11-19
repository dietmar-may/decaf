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

#ifndef _CMSTEMPLATE_CMSMESSAGECREATOR_H_
#define _CMSTEMPLATE_CMSMESSAGECREATOR_H_

#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/core/ActiveMQConnection.h>
#include <activemq/library/ActiveMQCPP.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>

#include <activemq/cmsutil/CmsTemplate.h>
#include <activemq/cmsutil/MessageCreator.h>

namespace cmstemplate {

    class CmsMessageCreator : public activemq::cmsutil::MessageCreator {
    private:

        std::string m_txt;

    public:

        CmsMessageCreator(const std::string& txt);

        virtual ~CmsMessageCreator();
        virtual cms::Message* createMessage(cms::Session* session);

    };
}

#endif /** _CMSTEMPLATE_CMSMESSAGECREATOR_H_ */
