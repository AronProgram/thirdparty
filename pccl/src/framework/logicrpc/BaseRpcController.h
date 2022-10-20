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


#include "util/tc_http.h"
#include "util/tc_network_buffer.h"
#include "json.h"
#include "BaseRpcRequestParams.h"
#include "BaseRpcRoute.h"
#include "BaseRpcProcess.h"
#include "BaseResult.h"
#include <map>
#include <string>
#include <vector>


using namespace tars;


namespace pccl
{


template<typename RpcPacket >
class BaseRpcController : public pccl::BaseRpcProcess,  public pccl::BaseRpcRoute,  public  pccl::BaseResult
{

public:
	/**
	* parse http packet
	* @param in
	* @param out
	*
	* @return int
	*/
	static tars::TC_NetWorkBuffer::PACKET_TYPE checkRpcPacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out)
	{
		return tars::TC_NetWorkBuffer::PACKET_FULL;
	}
	
	static tars::TC_NetWorkBuffer::PACKET_TYPE ignoreRpcPacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out)	
	{
		return tars::TC_NetWorkBuffer::PACKET_ERR;	
	}


public:
	
	/**
	*
	*  构造函数
	*/
	BaseRpcController(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseRpcController();

	/*
	*
	*  清空变量
	*
	*/
	virtual void reset();

	
	/*
	*
	*  清空变量
	*
	*/	
	void         clear();


	/**
	*
	* 设置输入和输出
	*/
	void setInOut(std::vector<char>* inBuffer, std::vector<char>* outBuffer);

	
	/*
	* 输出缓冲区 
	*
	*/
	std::vector<char>& getOutBuffer(void);
	


	
	/**
	*
	* 初始化
	*/
	void initialization(void);
	


	/**
	*
	* 初始化路由，绑定路由处理函数
	*/ 
	virtual void initRoute(void)             = 0;    

	

	/**
	* 初始化错误码，统一错误码处理
	*  
	*/
	virtual void initError(void)         = 0;
	

	/** 
	*输出数据结果到客户端
	*/
	virtual void  doOutput(void)         = 0;
	


    /**
     * 处理RPC路由请求
     * @return :  0 : success , 非0: error
     */
    virtual int doProcess(void);

	
	/*
	* 获取路由
	*/
	const std::string& getRoute();


	/*
	* 获取请求ID
	*/
	const std::string& getSequence();

	
	BaseRpcRequestParams<RpcPacket>& getRequest();

	/*
	*
	*  获取http body json数据参数
	*/
	Json::Value&         getDoc (void);

	
	/**
	* 获取http请求的header/body的后面序列化后的参数列表,
	* 
	*/
	REQUEST_PARAMS& 	 getParams(void);	
	
	std::string&    	 getParams(const std::string& sKey);	
	void                 putParams(const std::string& sKey, const std::string& sValue);
	const std::string&   getError(int code);
	

protected:		
	/** 
	* 处理RPC协议报文的处理
	*/
	int doProcessParse(void);
	
	/** 
	* 处理路由
	*/
	int doProcessRoute(void);
	
	
	/** 
	* 处理鉴权: jwt,authorize,token等等鉴权模式
	* reutrn int , 0：success ，返回200; 非0 ： 失败,返回403
	*/
	virtual int   doProcessAuth(void);



protected:
	
	/*
	* 状态
	*/	
	bool 		                     _status;
	
	/*
	* 输入buffer
	*/
	std::vector<char>*      		 _inBuffer;
	
	/*
	* 输出buffer
	*/
	std::vector<char>* 				 _outBuffer;  

	/*
	*错误CODE
	*/
	BaseErrorCode                    _error;	

	/*
	*报文
	*/
	BaseRpcRequestParams<RpcPacket>  _request;

	
};


template<typename RpcPacket > 
BaseRpcController<RpcPacket>::BaseRpcController(void) :        _status(false) 
{  

} 

template<typename RpcPacket >
BaseRpcController<RpcPacket>::~BaseRpcController(void)
{  

} 

template<typename RpcPacket >
void BaseRpcController<RpcPacket>::clear()
{
	BaseResult::clear();
}


template<typename RpcPacket >
void BaseRpcController<RpcPacket>::reset()
{
	BaseResult::reset();
	_request.reset();	
}

template<typename RpcPacket >
BaseRpcRequestParams<RpcPacket>& BaseRpcController<RpcPacket>::getRequest()
{
	return _request;
}

template<typename RpcPacket >
Json::Value&       BaseRpcController<RpcPacket>::getDoc (void)
{
	return _request.getDoc();
}

template<typename RpcPacket >

REQUEST_PARAMS& 	 BaseRpcController<RpcPacket>::getParams(void)
{
	return _request.getParams();
}

template<typename RpcPacket >
std::string&    	 BaseRpcController<RpcPacket>::getParams(const std::string& sKey)
{
	return _request.getParams(sKey);
}

template<typename RpcPacket >
void    	 BaseRpcController<RpcPacket>::putParams(const std::string& sKey, const std::string& sValue)
{
	_request.putParams(sKey,sValue);
}


template<typename RpcPacket >
void BaseRpcController<RpcPacket>::setInOut(std::vector<char>* inBuffer, std::vector<char>* outBuffer)
{
	_inBuffer  = inBuffer;
	_outBuffer = outBuffer;

	_request.setBuffer(_inBuffer,_outBuffer);
}


template<typename RpcPacket >
std::vector<char>& BaseRpcController<RpcPacket>::getOutBuffer(void)
{
	return *_outBuffer;
}



template<typename RpcPacket >
void BaseRpcController<RpcPacket>::initialization(void)	
{	
	initError();	
	initRoute();		
}

template<typename RpcPacket >
int BaseRpcController<RpcPacket>::doProcess(void)
{
	int result = pccl::STATE_SUCCESS;

	
	TLOG_DEBUG( "doProcessParse" << std::endl );
	
	// 初始化
	result = doProcessParse();
	if ( pccl::STATE_ERROR == result )
	{	
		this->error( BaseErrorCode::PARSE_ERROR, getError( BaseErrorCode::PARSE_ERROR ) );
		return pccl::STATE_SUCCESS;
	}	

	TLOG_DEBUG( "doProcessRoute" << std::endl );

	// 处理路由
	result = doProcessRoute();
	
	TLOG_DEBUG( "doProcess finish, result:" << result << std::endl );

	return result;
	
}	



template<typename RpcPacket >
int BaseRpcController<RpcPacket>::doProcessParse(void)
{
	if ( !this->_status )
	{
		initialization();
		
		this->_status = true;
	}

	return  _request.parse();
}

template<typename RpcPacket >
int BaseRpcController<RpcPacket>::doProcessRoute(void)
{
	// 调用处理过程	
	const std::string& route  = _request.getRoute();
	int                method = _request.getMethod();
	
	TLOG_DEBUG("doProcessRoute , sequence:" <<  _request.getSequence() <<  ",route:" << route << ",method:" << method << std::endl);	
	

	//处理业务逻辑
	if (  !this->hasMethod( route, method ) )
	{	
		this->error( BaseErrorCode::ROUTER_ERROR, getError( BaseErrorCode::ROUTER_ERROR ) );
		return pccl::STATE_ERROR;
	}

	// 处理鉴权
	if ( this->hasAuth( route ) &&  doProcessAuth() != pccl::STATE_SUCCESS )
	{
		this->error( BaseErrorCode::AUTHOR_ERROR, getError( BaseErrorCode::AUTHOR_ERROR ) );
		return pccl::STATE_ERROR;
	}

	// 处理路由
	return this->doRoute(route);	
	
}


template<typename RpcPacket >
int BaseRpcController<RpcPacket>::doProcessAuth(void)
{
	return pccl::STATE_SUCCESS;
}


template<typename RpcPacket >
const std::string& BaseRpcController<RpcPacket>::getRoute()
{
	return _request.getRoute();
}


template<typename RpcPacket >
const std::string& BaseRpcController<RpcPacket>::getSequence()
{
	return _request.getSequence();
}

template<typename RpcPacket >
const std::string& BaseRpcController<RpcPacket>::getError(int code)
{
	return _error.getError(code);
}


}



