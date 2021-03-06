/**
 * pccl is pleased to support the open source community by making Tars available.
 *
 * Copyright (C) 2016THL A29 Limited, a Tencent company. All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use this file except 
 * in compliance with the License. You may obtain a copy of the License at
 *
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software distributed 
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the 
 * specific language governing permissions and limitations under the License.
 */

#include "BaseRpcServer.h"
#include "RpcControllerImplement.h"
#include "BaseRpcController.h"
#include <string>


using namespace std;
using namespace tars;

namespace pccl
{



BaseRpcServer::BaseRpcServer(const std::string& objName):
_objName(objName)
{
	
	
}

void BaseRpcServer::initialize()
{
    //initialize application here:
    //addServant< ControllerImplement<UserController> >(ServerConfig::Application + "." + ServerConfig::ServerName + _objName);
    //addServantProtocol(ServerConfig::Application + "." + ServerConfig::ServerName + _objName,&BaseController::checkHttpPacket);

}
/////////////////////////////////////////////////////////////////
void BaseRpcServer::destroyApp()
{
    //destroy application here:
    //...
}


void BaseRpcServer::onNewClient(tars::TC_EpollServer::Connection* conn)
{
    TLOGINFO( "New client from " << conn->getIp() << ":" << conn->getPort() << std::endl );
}


}

