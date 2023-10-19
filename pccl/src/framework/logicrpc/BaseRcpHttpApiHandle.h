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

#include "BaseRpcApiHandler.h"
#include "util/tc_cgi.h"
#include "json.h"
#include <string>


using namespace pccl;


namespace pccl
{


template<typename RpcPacket > 
class BaseRpcHttpApiHandler : public BaseRpcApiHandler<RpcPacket>
{


public:	
	
	/**
	*
	*  构造函数
	*/
	BaseRpcHttpApiHandler(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseRpcHttpApiHandler();

	/**
	*
	* 重置
	*/
	virtual void reset();

	
	
protected:
	/**
	*  检查参数
	**/
	virtual int  doCheckParams(void);
	

	/**
	* 用户注册业务处理
	**/
	virtual int  doProcessWork(void);



protected:
	/**
	*  返回成功的消息
	* 
	*/
	virtual void direct(const std::string& sBody);
	virtual void success( const std::string& data );
	virtual void success( const Json::Value& data );
	virtual void textplain(const std::string& sBody);
	virtual void failure( int code, const std::string&  message);
	virtual void failure( const Json::Value& data,int code, const std::string&  message);
	virtual void forbid(const std::string& sMsg);
	virtual void redirect(const std::string& sUrl);
	virtual void redirect(const std::string& sUrl, const std::vector<std::string>& cookieHeader);
	virtual void redirect(const std::map<std::string,std::string>& httpHeader,const std::vector<std::string>& cookie);
	
private:

	/** 
	*  json反序列化
	*
	*/
	std::string  serialize(const Json::Value& data ,int code,const std::string& msg);
	std::string  serialize(const std::string& data ,int code,const std::string& msg);

	/*
	* 返回结果
	*/
	void result( const std::string& data);
	void result( const Json::Value& data);
	void result( const std::string& data, int code, const std::string& msg);
	void result( const Json::Value& data, int code, const std::string& msg);	
	void result(const std::map<std::string,std::string>& httpHeader,  const std::vector<std::string>& cookieHeader, int httpStutus, const std::string& about , const std::string& body );

	
};


template<typename RpcPacket > 
BaseRpcHttpApiHandler<RpcPacket>::BaseRpcHttpApiHandler(void)
{

}

template<typename RpcPacket > 
BaseRpcHttpApiHandler<RpcPacket>::~BaseRpcHttpApiHandler(void)
{

}

template<typename RpcPacket > 
void BaseRpcHttpApiHandler<RpcPacket>::reset(void)
{
	BaseRpcApiHandler<RpcPacket>::reset();
}

template<typename RpcPacket > 
int   BaseRpcHttpApiHandler<RpcPacket>::doCheckParams(void)
{
	return pccl::STATE_SUCCESS;
}

template<typename RpcPacket > 
int   BaseRpcHttpApiHandler<RpcPacket>::doProcessWork(void)
{
	return pccl::STATE_SUCCESS;
}

template<typename RpcPacket > 
void   BaseRpcHttpApiHandler<RpcPacket>::direct(const std::string& sBody)
{
	std::map<std::string,std::string> header;
	std::vector<std::string>          cookie;
	
    BaseRpcHttpApiHandler<RpcPacket>::result(header, cookie, 200,  "OK", sBody );
}


template<typename RpcPacket > 
void   BaseRpcHttpApiHandler<RpcPacket>::success(const std::string& data )
{
	BaseRpcHttpApiHandler<RpcPacket>::result(data);
}


template<typename RpcPacket > 
void   BaseRpcHttpApiHandler<RpcPacket>::success(const Json::Value& data    )
{
	BaseRpcHttpApiHandler<RpcPacket>::result(data);
}

template<typename RpcPacket > 
void   BaseRpcHttpApiHandler<RpcPacket>::textplain(const std::string& sBody)
{
	
	std::map<std::string,std::string> header;
	std::vector<std::string>          cookie;
	
	header["Content-Type"]	 = "text/plain";

	BaseRpcHttpApiHandler<RpcPacket>::result(header, cookie, 200,  "OK", sBody );
	
}


template<typename RpcPacket > 
void BaseRpcHttpApiHandler<RpcPacket>::failure( int code, const std::string&	message)
{
	std::string data;
	BaseRpcHttpApiHandler<RpcPacket>::result( data,code,message);
}


template<typename RpcPacket > 
void BaseRpcHttpApiHandler<RpcPacket>::failure( const Json::Value& data,int code, const std::string&	message)
{
	BaseRpcHttpApiHandler<RpcPacket>::result( data,code,message);
}

template<typename RpcPacket > 
void   BaseRpcHttpApiHandler<RpcPacket>::forbid(const std::string& sMsg)
{
	std::map<std::string,std::string> header;	
	std::vector<std::string>          cookie;	
	Json::Value                       doc;
	std::string sRsp = serialize(doc,403,sMsg);	
	BaseRpcHttpApiHandler<RpcPacket>::result( header,cookie , 403, "Forbidden", sRsp );
}

template<typename RpcPacket > 
void   BaseRpcHttpApiHandler<RpcPacket>::redirect(const std::string& sUrl)
{
	std::map<std::string,std::string> header;
	const std::vector<std::string>    cookie;
	
	BaseRpcHttpApiHandler<RpcPacket>::redirect( header,cookie );
}

template<typename RpcPacket > 
void BaseRpcHttpApiHandler<RpcPacket>::redirect(const std::string& sUrl, const std::vector<std::string>& cookieHeader)
{
	
	std::map<std::string,std::string> header;
	header["Content-Type"]   = "text/html";
	header["Location"]       = tars::TC_Cgi::decodeURL(sUrl);
	
	redirect( header,cookieHeader );

}

template<typename RpcPacket > 
void BaseRpcHttpApiHandler<RpcPacket>::redirect(const std::map<std::string,std::string>& httpHeader,const std::vector<std::string>& cookie)
{
	result( httpHeader,cookie,302 ,"Found","" );
}



template<typename RpcPacket > 
std::string  BaseRpcHttpApiHandler<RpcPacket>::serialize(const Json::Value& data ,int code,const std::string& msg)
{
	Json::Value 	 root;
	
	root["code"]	  = code;
	root["msg"] 	  = msg;
	root["data"]	  = data;
	root["sequence"]  = BaseRpcApiHandler<RpcPacket>::getSequence();	

	Json::StreamWriterBuilder builder;
	std::string content  = Json::writeString(builder, root);	

	return content;
}

template<typename RpcPacket > 
std::string  BaseRpcHttpApiHandler<RpcPacket>::serialize(const std::string& data ,int code,const std::string& msg)
{
	Json::Value 	 root;
	
	root["code"]	  = code;
	root["msg"] 	  = msg;
	root["data"]	  = data;
	root["sequence"]  = BaseRpcApiHandler<RpcPacket>::getSequence();	

	Json::StreamWriterBuilder builder;
	std::string content  = Json::writeString(builder, root);	
	
	return content;
}

template<typename RpcPacket > 
void BaseRpcHttpApiHandler<RpcPacket>::result( const std::string& data)
{
	BaseRpcHttpApiHandler<RpcPacket>::result(data, pccl::STATE_SUCCESS,"OK");
}

template<typename RpcPacket > 
void BaseRpcHttpApiHandler<RpcPacket>::result( const Json::Value& data)
{
	BaseRpcHttpApiHandler<RpcPacket>::result(data, pccl::STATE_SUCCESS,"OK");

}

template<typename RpcPacket > 
void BaseRpcHttpApiHandler<RpcPacket>::result( const std::string& data, int code, const std::string& msg)
{
	std::map<std::string,std::string> header;
	std::vector<std::string>          cookie;
	
	std::string sBody  = serialize(data, code, msg);	
    BaseRpcHttpApiHandler<RpcPacket>::result(header, cookie, 200,  "OK", sBody );
}

template<typename RpcPacket > 
void BaseRpcHttpApiHandler<RpcPacket>::result( const Json::Value& data, int code, const std::string& msg)
{
	std::map<std::string,std::string> header;
	std::vector<std::string>          cookie;
	
	std::string sBody  = serialize(data, code, msg);	
    BaseRpcHttpApiHandler<RpcPacket>::result(header, cookie, 200,  "OK", sBody );

}

template<typename RpcPacket > 
void BaseRpcHttpApiHandler<RpcPacket>::result(const std::map<std::string,std::string>& httpHeader,  const std::vector<std::string>& cookieHeader, int httpStutus, const std::string& about , const std::string& body )
{
	tars::TC_HttpResponse http;

	// http header
	if ( httpHeader.empty() )
	{	
		http.setHeader("Content-Type","application/json;charset=utf-8");
	}
	else
	{
		for( auto it = httpHeader.begin(); it != httpHeader.end(); it++ )
		{
			http.setHeader(it->first, it->second);
		}
	}

	// http cookie
	for( auto it = cookieHeader.begin(); it != cookieHeader.end(); it++ )
	{
		http.setSetCookie(*it);
	}

	http.setResponse(httpStutus,about,body);

	BaseRpcApiHandler<RpcPacket>::setResponse( http.encode() );

}


}

