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

#include "BaseRpcPlus.h"
#include "json.h"
#include "BaseRpcController.h"
#include "BaseResult.h"
#include "BaseErrorCode.h"
#include <iostream>
#include <string>
#include <map>


using namespace tars;

namespace pccl
{

template<typename RpcPacket >
class BaseRpcApiHandler
{
public:
	/*
	* 构造函数
	*/
	BaseRpcApiHandler(void);
	
    /**
     * 析构函数
     **/
    virtual ~BaseRpcApiHandler(void);


	/**
	* 重置
	*/
	virtual void reset();
	
	
 	
	void  setBasePointer(BaseRpcController<RpcPacket>* pBase);
	 
	

	BaseRpcController<RpcPacket>&  getBasePointerRef();
	 
	
	

public:
	/**
	* 业务逻辑处理入口 
	* 
	*/
	virtual int  doProcessApi(void);
	 

protected:
	/**
	*  检查参数
	**/
	virtual int  doCheckParams(void);
	 
	

	/**
	* 业务处理
	**/
	virtual int  doProcessWork(void);




protected:
	/**
	* 清除错误
	**/
	void               clear(void);

	/**
	* 设置返回错误 
	**/
	void               error( int code , const std::string& msg);
	const std::string& getError( int code );
	std::string&       getResponse(void);
	void               setResponse(const std::string& response);
	const std::string& getSequence(void);
	std::string&       getParams(const std::string& sKey);
	void               putParams(const std::string& sKey, const std::string& sValue);
	Json::Value&       getDoc(void);
	TarsCurrentPtr&    getCurrent(void);
	void               close(void);
	void               sendClient(const char* sendBuff, uint32_t length);
	void               sendClient(const std::string& sendBuff);
	
	
	
protected:
	BaseRpcController<RpcPacket>*  _pBase;

};

template<typename RpcPacket > 
BaseRpcApiHandler<RpcPacket>::BaseRpcApiHandler(void):        _pBase(NULL)
{

}

template<typename RpcPacket >
BaseRpcApiHandler<RpcPacket>::~BaseRpcApiHandler(void) 
{ 

}

template<typename RpcPacket >
void BaseRpcApiHandler<RpcPacket>::reset()	
{ 
	_pBase = NULL;
}


template<typename RpcPacket >
void  BaseRpcApiHandler<RpcPacket>::setBasePointer(BaseRpcController<RpcPacket>* pBase)
{
	_pBase =  pBase;
}

template<typename RpcPacket >
BaseRpcController<RpcPacket>&  BaseRpcApiHandler<RpcPacket>::getBasePointerRef()
{
	return *_pBase;
}


template<typename RpcPacket >
void BaseRpcApiHandler<RpcPacket>::clear(void)
{	
	 _pBase->clear();
}


template<typename RpcPacket >	
void BaseRpcApiHandler<RpcPacket>::error( int code , const std::string& msg )
{
	_pBase->error( code, msg );
}

template<typename RpcPacket >	
const std::string& BaseRpcApiHandler<RpcPacket>::getError( int code )
{
	return _pBase->getError( code );
}


template<typename RpcPacket >	
std::string& BaseRpcApiHandler<RpcPacket>::getResponse(void)
{
	return _pBase->getResponse();
}

template<typename RpcPacket >	
void	BaseRpcApiHandler<RpcPacket>::setResponse(const std::string& response)
{
	return _pBase->setResponse( response );
}

template<typename RpcPacket >
const std::string& BaseRpcApiHandler<RpcPacket>::getSequence(void)
{
	return _pBase->getSequence();
}

template<typename RpcPacket >
std::string&	   BaseRpcApiHandler<RpcPacket>::getParams(const std::string& sKey)
{
	return _pBase->getParams(sKey);
}

template<typename RpcPacket >
void 	   BaseRpcApiHandler<RpcPacket>::putParams(const std::string& sKey, const std::string& sValue)
{
	return _pBase->putParams(sKey,sValue);
}

template<typename RpcPacket >
Json::Value& 	   BaseRpcApiHandler<RpcPacket>::getDoc(void)
{
	return _pBase->getDoc();
}

template<typename RpcPacket >
TarsCurrentPtr&    BaseRpcApiHandler<RpcPacket>::getCurrent(void)
{
	return _pBase->getCurrent();
}

template<typename RpcPacket >
void			   BaseRpcApiHandler<RpcPacket>::close(void)
{
	_pBase->close();
}

template<typename RpcPacket >
void			   BaseRpcApiHandler<RpcPacket>::sendClient(const char* sendBuff, uint32_t length)
{
	TarsCurrentPtr& current = BaseRpcApiHandler<RpcPacket>::getCurrent();
	current->sendResponse(sendBuff,length);
}

template<typename RpcPacket >
void			   BaseRpcApiHandler<RpcPacket>::sendClient(const std::string& sendBuff)
{
	BaseRpcApiHandler<RpcPacket>::sendClient( sendBuff.c_str(), sendBuff.length() );
}
			   


template<typename RpcPacket >
int   BaseRpcApiHandler<RpcPacket>::doProcessApi(void)
{

	int result = pccl::STATE_SUCCESS;

	result = doCheckParams();
	if ( pccl::STATE_SUCCESS != result )
	{	
		error( BaseErrorCode::PARAMS_ERROR ,getError( BaseErrorCode::PARAMS_ERROR ) );
		return pccl::STATE_ERROR;
	}

	
	result = doProcessWork();
	if ( pccl::STATE_SUCCESS != result )
	{
		error( BaseErrorCode::SERVER_ERROR ,getError( BaseErrorCode::SERVER_ERROR ) );
		return pccl::STATE_ERROR;
	}


	return result;	

}



template<typename RpcPacket >
int   BaseRpcApiHandler<RpcPacket>::doCheckParams(void)
{
	return pccl::STATE_SUCCESS;		
}


template<typename RpcPacket >
int   BaseRpcApiHandler<RpcPacket>::doProcessWork(void)
{
	return pccl::STATE_SUCCESS;		
}


}

