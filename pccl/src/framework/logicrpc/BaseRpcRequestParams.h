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
#include "BaseRpcHttpPacket.h"
#include "json.h"
#include "BaseRandom.h"
#include <algorithm>
#include <map>
#include <string>
#include <vector>



namespace pccl
{


template<typename RpcPacket>
class BaseRpcRequestParams 
{		

public:
	/**
	*
	*  构造函数
	*/
	BaseRpcRequestParams(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseRpcRequestParams(void);

	/**
	*
	*
	*/
	void setBuffer(std::vector<char>* inBuffer, std::vector<char>* outBuffer);
	

	/*
	* 输出缓冲区 
	*
	*/
	std::vector<char>& getOutBuffer(void);
	

	/*
	*
	*  清空变量
	*
	*/
	virtual void reset();
	



	/*
	*  请求序列号,用于日志染色,追踪数据链条
	*/
	std::string& getSequence(void);


	int                   getMethod();

	
	/*
	*
	*  获取路由
	*/
	const std::string&		getRoute();	
	

  
	/*
	*
	*  获取http body json数据参数
	*/
	Json::Value&           getDoc (void);

	
	/**
	* 获取http请求的header/body的后面序列化后的参数列表,
	* 
	*/
	REQUEST_PARAMS& 	getParams(void);	
	
	std::string&    	getParams(const std::string& sKey);	
	
	void                putParams(const std::string& sKey, const std::string& sValue );	
	
	RpcPacket&          getPacket();

	/*
	*
	*  解析报文
	*  @return  : 0:success, !0: error
	*/
	int parse(void);
	
	

protected:
	
	

	
	/**
	*	解析整个http报文
	*	@return  : success: OK, error: error
	*/
	virtual int parseRpcPacket(void);
	


private:	
	void        dump(void);		
	
	
	/*
	* 打印参数
	*/
	void 		dumpParams(void);
	


	
protected:
	/*
	* 输入buffer
	*/
	std::vector<char>*      _inBuffer;
	
	/*
	* 输出buffer
	*/
	std::vector<char>* 		_outBuffer;  


	/*
	*解析报文              
	*/
	RpcPacket              _packet;
	
	/*
	* 序列号
	*/
	std::string             _sequence;

	/*
	* 命令
	*/
	int                     _method;

	/*
	* 路由
	*/
	std::string             _route;
	
	/*
	* http参数：
	* 1. http 协议header/body query string参数
	* 2. 鉴权用户信息的参数（ 鉴权权可以写入进来）
	*/
	REQUEST_PARAMS			_params;

	
	/*
	* http报文解析后json
	*/
	Json::Value				_doc; 

};


template<typename RpcPacket> 
BaseRpcRequestParams<RpcPacket>::BaseRpcRequestParams(void):_inBuffer(NULL), _outBuffer(NULL), _sequence("")
{

}


template<typename RpcPacket>  
BaseRpcRequestParams<RpcPacket>::~BaseRpcRequestParams(void)
{

}

template<typename RpcPacket>  
void BaseRpcRequestParams<RpcPacket>::setBuffer(std::vector<char>* inBuffer, std::vector<char>* outBuffer)	
{
	_inBuffer  = inBuffer;
	_outBuffer = outBuffer;
}


template<typename RpcPacket>  
void BaseRpcRequestParams<RpcPacket>::reset()	
{	
	_packet.reset();
	_params.clear();
	_doc.clear();	
	_sequence = "";
	_route	  = "";	
	_method   = 0;
}

template<typename RpcPacket>   
std::vector<char>& BaseRpcRequestParams<RpcPacket>::getOutBuffer(void)
{
	return *_outBuffer;
}

template<typename RpcPacket>  
std::string& BaseRpcRequestParams<RpcPacket>::getSequence(void)	
{
	return _sequence;	
}


template<typename RpcPacket> 
int BaseRpcRequestParams<RpcPacket>::getMethod()	
{
	return _method;
}


template<typename RpcPacket> 
const std::string& BaseRpcRequestParams<RpcPacket>::getRoute()	
{
	return _route;
}


template<typename RpcPacket> 
Json::Value&     BaseRpcRequestParams<RpcPacket>::getDoc (void)  
{ 
	return _doc;
}


template<typename RpcPacket> 
REQUEST_PARAMS& 	BaseRpcRequestParams<RpcPacket>::getParams(void) 
{ 
	return _params; 
}

template<typename RpcPacket> 
std::string&    	BaseRpcRequestParams<RpcPacket>::getParams(const std::string& sKey) 
{ 
	return _params[sKey]; 
}

template<typename RpcPacket> 
void    BaseRpcRequestParams<RpcPacket>::putParams(const std::string& sKey, const std::string& sValue )
{
	_params[ sKey ] =  sValue ;
}

template<typename RpcPacket> 
RpcPacket&          BaseRpcRequestParams<RpcPacket>::getPacket() 
{ 
	return _packet; 
}

template<typename RpcPacket>  
void  BaseRpcRequestParams<RpcPacket>::dump(void)		
{
	dumpParams();
}

template<typename RpcPacket>  
void  BaseRpcRequestParams<RpcPacket>::dumpParams(void)
{		
	
	TLOGDEBUG( "dumpParams, " << _sequence << std::endl );
	for( auto it = _params.begin(); it != _params.end(); it++ )
	{
		TLOGDEBUG( "dumpParams, " << _sequence << ", key:" <<it->first << ",value:" << it->second << std::endl);
	}
	
	
}

template<typename RpcPacket>  
int BaseRpcRequestParams<RpcPacket>::parse(void)
{
	// 构建染色ID，用于日志的数据链条的追踪
	_sequence = BaseRandom::alpha(12);

	
	int result = parseRpcPacket();
	if ( pccl::STATE_SUCCESS != result )
	{
		TLOGERROR("parse packet error" << "\n" );
		return pccl::STATE_ERROR;
	}	


 	dump();

	return result;
}


template<typename RpcPacket>  
int BaseRpcRequestParams<RpcPacket>::parseRpcPacket(void)
{	

	int result =  _packet.decodePacket( *_inBuffer  );
	if ( pccl::STATE_SUCCESS != result )
	{
		return pccl::STATE_ERROR;
	}

	_method = _packet.getMethod();
	_route  = _packet.getRoute();
	_params = _packet.getParams();
	_doc    = _packet.getDocument();	
	
	return pccl::STATE_SUCCESS;
}


}

