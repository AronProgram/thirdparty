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


#include "BaseRpcController.h"
#include "BaseRpcApiHandler.h"
#include "BaseRpcRouteFactory.h"
#include <string>
#include <memory>



namespace pccl
{

template<typename RpcPacket >
class BaseRpcApiController : public pccl::BaseRpcController<RpcPacket>
{


public:
	
	
	/**
	*
	*  构造函数
	*/
	BaseRpcApiController(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseRpcApiController();

	/**
	*
	* 清空环境
	*/
	virtual void reset();
	 


protected:
	/**
	*
	* 初始化路由，统一处理处接口
	*/ 
	virtual void initRoute(void) override;
	 

	/**
	*
	* 初始化错误码
	*/	
	virtual void initError(void) override;


	/**
	*
	* 输出结果
	*/	
	virtual void doOutput(void) override;
	 

	
	/**
	*	注册api handler 函数
	*  @parmams: sApi ，API名称
	*  @params:  httpMethod, POST,GET,DELETE
	*  @params:  handler,  BaseBpiHandler 
	*  @params:  isAuth,   是否要鉴权
	*
	*/
	void	regiterRoute(const std::string& sApi,BaseRpcApiHandler<RpcPacket>* handler );
	 
	/**
	*	注册api handler 函数
	*  @parmams: sApi ，API名称
	*  @params:  httpMethod, POST,GET,DELETE
	*  @params:  handler,  BaseBpiHandler 
	*  @params:  isAuth,   是否要鉴权
	*
	*/
	void	regiterRoute(const std::string& sApi,BaseRpcApiHandler<RpcPacket>* handler, int       method,	bool isAuth = false );
	 
	
	/**
	*  http协议路由处理总入口
	*/
	virtual int handle(void);
	 


private:
	/*
	* api handler 工厂
	*/
	RegisterRouteHandlerFactory<RpcPacket> 	_factory;

	
	
};





template<typename RpcPacket >
BaseRpcApiController<RpcPacket>::BaseRpcApiController(void) 
{

}

template<typename RpcPacket >
BaseRpcApiController<RpcPacket>:: ~BaseRpcApiController()
{

}

template<typename RpcPacket >
void BaseRpcApiController<RpcPacket>::reset()	
{
	BaseRpcController<RpcPacket>::reset();
}



template<typename RpcPacket >
void BaseRpcApiController<RpcPacket>::initRoute(void) 
{

}

template<typename RpcPacket >	
void BaseRpcApiController<RpcPacket>::initError(void) 
{
	
}


template<typename RpcPacket >	
void BaseRpcApiController<RpcPacket>::doOutput(void) 
{
	
}


template<typename RpcPacket >
void	BaseRpcApiController<RpcPacket>::regiterRoute(const std::string& sApi,BaseRpcApiHandler<RpcPacket>* handler )
{	
	// API处理统一入口
	this->bindRoute( sApi,  std::bind(&BaseRpcApiController<RpcPacket>::handle, this), BaseRpcRoute::NONE_ROUTE_TYPE,false );

	// 每个API对应具体处理的ApiHandler
	_factory.addApiHandle( sApi, handler );
}

template<typename RpcPacket >
void	BaseRpcApiController<RpcPacket>::regiterRoute(const std::string& sApi,BaseRpcApiHandler<RpcPacket>* handler, int       method,	bool isAuth  )
{	
	// API处理统一入口
	this->bindRoute( sApi,  std::bind(&BaseRpcApiController<RpcPacket>::handle, this), (BaseRpcRoute::RpcRouteRquestType)method , isAuth );

	// 每个API对应具体处理的ApiHandler
	_factory.addApiHandle( sApi, handler );
}

template<typename RpcPacket >
int BaseRpcApiController<RpcPacket>::handle(void)	
{
	int result = pccl::STATE_SUCCESS;

	//获取的api handler
	BaseRpcApiHandler<RpcPacket>*		pHandler  = _factory.createHandler( this->getRoute() );

	//处理前准备
	pHandler->reset();
	pHandler->setBasePointer(this);

	//逻辑处理
	result = pHandler->doProcessApi();		
	
	return result;	
}


}



