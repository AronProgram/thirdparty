/**
 * Minzea is pleased to support the open source community by making Tars available.
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
#pragma once


#include <iostream>
#include "servant/Application.h"
#include <string>

using namespace tars;


namespace pccl
{


/**
 *
 **/
class BaseRpcServer : public Application
{

public:
	/**
	* 构造函数
	**/
	BaseRpcServer(const std::string& objName);
	
    /**
     * 析构函数
     **/
    virtual ~BaseRpcServer() {};

    /**
     * 资源初始化
     **/
	virtual void initialize();

    /**
     * 资源释放
     **/
    virtual void destroyApp();

protected:
	/**
	*  新连接
	**/
	virtual void 		onNewClient(tars::TC_EpollServer::Connection* conn);

	
	
protected:
	/*
	* tars object name
	*/
	std::string _objName;
};


}

