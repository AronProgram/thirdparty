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
#include <jemalloc/jemalloc.h>
#include "WebsocketType.h"
#include "WebSocketProtocol.h"
#include "util/tc_cgi.h"
#include "json.h"
#include <string>



namespace pccl::protocol::websocket
{


template<typename RpcPacket > 
class BaseWebsocketApiHandler : public BaseRpcApiHandler<RpcPacket>
{


public:	
	
	/**
	*
	*  构造函数
	*/
	BaseWebsocketApiHandler(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseWebsocketApiHandler();

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
	*  websocket 握手协议，返回成功消息
	* 
	*/
	virtual void forbid(const std::string& sMsg ); 	
	virtual void handshake(const std::string& wsAccept, const std::string& wsProtocol, const std::string& wxExtension, const std::string& wxVersion);

	virtual void pong(const std::string& sMsg = "pong");
	virtual void ping(const std::string& sMsg = "ping");
	virtual void end(int code = 0, const std::string&  message = "" );


	virtual void success( const std::string& data , bool fin = true);
	virtual void success( const Json::Value& data , const std::string& aid , bool fin = true);
	virtual void failure( int code, const std::string&  message,  bool fin = true);
	virtual void failure( const Json::Value& data,int code, const std::string&  message,  bool fin = true);


	/**
	* websocket data trans frame 
	*/
	virtual int  sendFirstFragment(const std::string& message, OpCode opCode = OpCode::TEXT, bool compress = false);
	virtual int  sendFragment(const std::string& message, bool compress = false);
	virtual int  sendLastFragment(const std::string& message, bool compress = false);
	virtual int  send(const std::string& message, OpCode opCode = OpCode::TEXT, bool compress = false, bool fin = true); 

	
	/**
	*
	*/
	uint32_t getUID();
	
private:

	/** 
	*  json反序列化
	*
	*/
	std::string  serialize(const Json::Value& data ,const std::string& aid, int code,const std::string& msg);
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
BaseWebsocketApiHandler<RpcPacket>::BaseWebsocketApiHandler(void)
{

}

template<typename RpcPacket > 
BaseWebsocketApiHandler<RpcPacket>::~BaseWebsocketApiHandler(void)
{

}

template<typename RpcPacket > 
void BaseWebsocketApiHandler<RpcPacket>::reset(void)
{
	BaseRpcApiHandler<RpcPacket>::reset();
}

template<typename RpcPacket > 
int   BaseWebsocketApiHandler<RpcPacket>::doCheckParams(void)
{
	return pccl::STATE_SUCCESS;
}

template<typename RpcPacket > 
int   BaseWebsocketApiHandler<RpcPacket>::doProcessWork(void)
{
	return pccl::STATE_SUCCESS;
}

template<typename RpcPacket > 
void   BaseWebsocketApiHandler<RpcPacket>::forbid(const std::string& sMsg)
{
	std::map<std::string,std::string> header;	
	std::vector<std::string>          cookie;	
	Json::Value                       doc;
	std::string sRsp = serialize(doc,403,sMsg);	
	BaseWebsocketApiHandler<RpcPacket>::result( header,cookie , 403, "Forbidden", sRsp );
}


template<typename RpcPacket > 
void   BaseWebsocketApiHandler<RpcPacket>::handshake(const std::string& wsAccept, const std::string& wsProtocol, const std::string& wxExtension, const std::string& wxVersion)
{
	
	std::map<std::string,std::string> header;
	std::vector<std::string>          cookie;
	std::string                       sBody = "";	

	header["Upgrade"]                 = "websocket";
	header["connection"]              = "Upgrade";
	header["Sec-WebSocket-Accept"]    = wsAccept;
	
	if ( !wsProtocol.empty() )
	{
		header["Sec-WebSocket-Protocol"]    = wsProtocol;
	}

	if ( !wxExtension.empty() )
	{
		header["Sec-WebSocket-Extensions"]  = wxExtension;
	}

	if ( !wxVersion.empty() )
	{
		header["Sec-WebSocket-Version"]     = wxVersion;
	}
	
    BaseWebsocketApiHandler<RpcPacket>::result(header, cookie, 101,  "Switching Protocols", sBody );	
	
}


template<typename RpcPacket >
void BaseWebsocketApiHandler<RpcPacket>::pong(const std::string& sMsg )
{
	BaseWebsocketApiHandler<RpcPacket>::send(sMsg,OpCode::PONG,false, true );
}

template<typename RpcPacket >
void BaseWebsocketApiHandler<RpcPacket>::ping(const std::string& sMsg )
{
	BaseWebsocketApiHandler<RpcPacket>::send(sMsg,OpCode::PING,false, true );
}



template<typename RpcPacket > 
void   BaseWebsocketApiHandler<RpcPacket>::success(const std::string& data , bool fin)
{
	BaseWebsocketApiHandler<RpcPacket>::send(data,OpCode::TEXT,false, fin );
}


template<typename RpcPacket > 
void   BaseWebsocketApiHandler<RpcPacket>::success(const Json::Value& data , const std::string& aid ,  bool fin)
{	
	std::string sBody  = BaseWebsocketApiHandler<RpcPacket>::serialize(data, aid, pccl::STATE_SUCCESS, "");	
	BaseWebsocketApiHandler<RpcPacket>::send(sBody,OpCode::TEXT,false, fin);
}

template<typename RpcPacket > 
void BaseWebsocketApiHandler<RpcPacket>::failure( int code, const std::string&	message,  bool fin)
{
	std::string sBody  = BaseWebsocketApiHandler<RpcPacket>::serialize(std::string(""), code, message);	
	BaseWebsocketApiHandler<RpcPacket>::send(sBody,OpCode::TEXT,false, fin);
}


template<typename RpcPacket > 
void BaseWebsocketApiHandler<RpcPacket>::failure( const Json::Value& data,int code, const std::string&	message,  bool fin)
{
	std::string sBody  = BaseWebsocketApiHandler<RpcPacket>::serialize(data, code, message);	
	BaseWebsocketApiHandler<RpcPacket>::send(sBody,OpCode::TEXT,false, fin);
}


template<typename RpcPacket > 
std::string  BaseWebsocketApiHandler<RpcPacket>::serialize(const Json::Value& data ,const std::string& aid, int code,const std::string& msg)
{

	Json::Value 	 root;
	
	root["code"]	  = code;
	root["msg"] 	  = msg;
	root["aid"] 	  = aid;
	root["data"]	  = data;
	root["sequence"]  = BaseRpcApiHandler<RpcPacket>::getSequence();	

	Json::StreamWriterBuilder builder;
	std::string content  = Json::writeString(builder, root);	

	return content;


}


template<typename RpcPacket > 
std::string  BaseWebsocketApiHandler<RpcPacket>::serialize(const Json::Value& data ,int code,const std::string& msg)
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
std::string  BaseWebsocketApiHandler<RpcPacket>::serialize(const std::string& data ,int code,const std::string& msg)
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
void BaseWebsocketApiHandler<RpcPacket>::result( const std::string& data)
{
	BaseWebsocketApiHandler<RpcPacket>::result(data, pccl::STATE_SUCCESS,"OK");
}

template<typename RpcPacket > 
void BaseWebsocketApiHandler<RpcPacket>::result( const Json::Value& data)
{
	BaseWebsocketApiHandler<RpcPacket>::result(data, pccl::STATE_SUCCESS,"OK");

}

template<typename RpcPacket > 
void BaseWebsocketApiHandler<RpcPacket>::result( const std::string& data, int code, const std::string& msg)
{
	std::map<std::string,std::string> header;
	std::vector<std::string>          cookie;
	
	std::string sBody  = serialize(data, code, msg);	
    BaseWebsocketApiHandler<RpcPacket>::result(header, cookie, 200,  "OK", sBody );
}

template<typename RpcPacket > 
void BaseWebsocketApiHandler<RpcPacket>::result( const Json::Value& data, int code, const std::string& msg)
{
	std::map<std::string,std::string> header;
	std::vector<std::string>          cookie;
	
	std::string sBody  = serialize(data, code, msg);	
    BaseWebsocketApiHandler<RpcPacket>::result(header, cookie, 200,  "OK", sBody );

}

template<typename RpcPacket > 
void BaseWebsocketApiHandler<RpcPacket>::result(const std::map<std::string,std::string>& httpHeader,  const std::vector<std::string>& cookieHeader, int httpStutus, const std::string& about , const std::string& body )
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

template<typename RpcPacket > 
void  BaseWebsocketApiHandler<RpcPacket>::end(int code, const std::string& message) 
{
	  
	   // Format and send the close frame 
	   static const int MAX_CLOSE_PAYLOAD = 123;
	   std::size_t      length            = std::min<size_t>( MAX_CLOSE_PAYLOAD, message.length() );
	   
	   char closePayload[MAX_CLOSE_PAYLOAD + 2];	   
	   formatClosePayload(closePayload, (uint16_t) code, message.c_str(), length);

	   // send close frame
	   BaseWebsocketApiHandler<RpcPacket>::send( message, OpCode::CONTINUATION );  

	   // close socket
	   BaseRpcApiHandler<RpcPacket>::close();
}


template<typename RpcPacket > 
int  BaseWebsocketApiHandler<RpcPacket>::send(const std::string& message, OpCode opCode , bool compress , bool fin ) 
{
   
	std::size_t messageFrameSize = messageFrameSize( message.length() ); 

	char * sendBuffer = static_cast<char*>( je_malloc( messageFrameSize ) );
	
	formatMessage<true>( sendBuffer, message.data(), message.length(), opCode, message.length(), compress, fin );
	BaseRpcApiHandler<RpcPacket>::sendClient( (const char*) sendBuffer,messageFrameSize );

	je_free(sendBuffer);

	/* Return success */
	return pccl::STATE_SUCCESS;
}





/* Sending fragmented messages puts a bit of effort on the user; you must not interleave regular sends
 * with fragmented sends and you must sendFirstFragment, [sendFragment], then finally sendLastFragment. */
template<typename RpcPacket > 
int BaseWebsocketApiHandler<RpcPacket>::sendFirstFragment(const std::string& message, OpCode opCode , bool compress ) 
{
	return send(message, opCode, compress, false);
}

template<typename RpcPacket > 
int BaseWebsocketApiHandler<RpcPacket>::sendFragment(const std::string& message, bool compress) 
{
    return send(message, CONTINUATION, compress, false);
}

template<typename RpcPacket >
int BaseWebsocketApiHandler<RpcPacket>::sendLastFragment(const std::string& message, bool compress) 
{
    return send(message, CONTINUATION, compress, true);
}


template<typename RpcPacket >
uint32_t BaseWebsocketApiHandler<RpcPacket>::getUID()
{
   tars::TarsCurrentPtr& current = BaseRpcApiHandler<RpcPacket>::getCurrent();
   return current->getUId();
}

 
}

