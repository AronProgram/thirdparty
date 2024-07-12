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


#include "WebsocketPacket.h"
#include "BaseRpcRoute.h"
#include "WebsocketType.h"
#include "WebSocketImpl.h"
#include "WebSocketProtocol.h"
#include "util/tc_http.h"
#include "util/tc_cgi.h"
#include "json.h"



using namespace pccl;

namespace pccl::protocol::websocket
{


WebsocketPacket::WebsocketPacket():_method(0),_route("")
{

}


WebsocketPacket::~WebsocketPacket()
{
	
}


void WebsocketPacket::reset()
{	
	pccl::BaseRpcPacket::reset();
	
	_method = 0;
	_route = "";
	_text  = "";
	_params.clear();
	_document.clear();
}


int WebsocketPacket::decodePacket(const std::vector<char>& buffer)
{	

	if ( buffer.size() < 2 )
	{
		TLOGERROR( "packet error, length:" << buffer.size() << std::endl );
		return pccl::STATE_ERROR;  
	}

	// websocket 握手协议
	if ( buffer[0] == 'G' )
	{
		return parseHttpPacket(buffer);
	}
	else
	{
		return parseFrame(buffer);
	}
	
}

int WebsocketPacket::parseHttpPacket(const std::vector<char>& buffer)  
{	

	try
	{
		// packet
		_text.insert(_text.begin(), buffer.begin(),buffer.end());

		TLOG_DEBUG( "packet:" << _text  << ",lenght:" << buffer.size() << std::endl );

		// http packet
		tars::TC_HttpRequest packet;		
		
		bool status = packet.decode( buffer );
		if ( !status )
		{
			TLOGERROR( "parse http packet error,packet:" << _text << std::endl );
			return pccl::STATE_ERROR;  
		}
			
		// 路由
		_method              = packet.requestType();
		_route               = packet.getRequestUrl();	

		// http headers
		pccl::REQUEST_PARAMS   headers;
		packet.getHeaders(headers);
		for( auto it = headers.begin(); it != headers.end(); ++it )
		{
			_params.insert(map<string, string>::value_type( it->first, it->second ));
		}

		std::string urlParam = packet.getRequestParam();

		// 解析其他参数
		parseUrlBody(urlParam);			
		

		// content body
		std::string& content       = packet.getContent();
		_params["Body"]            = content;

		/// content type
		std::string  contentType   = tars::TC_Common::lower( packet.getContentType() );		
		
		// json         application/json
		if ( !content.empty() && contentType.find("application/json") != std::string::npos )  
		{
			parseJsonBody( content );
		}
		else 
		{
			parseUrlBody(content);
		}		
			
		return pccl::STATE_SUCCESS;

	}
	catch(std::exception& e )
	{
		TLOGERROR("packet http packet error, exception:" << e.what() << ",packet:" << _text << std::endl );
		return pccl::STATE_ERROR;
	}
}

 
int WebsocketPacket::parseFrame(const std::vector<char>& buffer)
{

	_text.insert(_text.begin(), buffer.begin(),buffer.end());

	WebSocketState<true> state;
	WebsocketUserData    data;
	WebSocketProtocol<true, WebsocketImpl>::consume( (char*) _text.c_str(), _text.length(), &state, (void*)(&data) );

	_method              = pccl::BaseRpcRoute::NONE_ROUTE_TYPE;
	_route               = data.route;	
	_params["Body"]      = data.text;
	_document            = data.doc;	
		
	TLOG_DEBUG( "consume,opcode:" << data.opCode << ",route:"<< data.route << ",text:" << data.text << std::endl );


	return pccl::STATE_SUCCESS;
}


int WebsocketPacket::parseJsonBody(const std::string& content ) 
{		
	
	Json::Reader    reader;

	Json::Value     data;
	bool status = reader.parse(content, data);	
    if ( !status ) 
	{
		return pccl::STATE_SUCCESS;
    }	

	return pccl::STATE_ERROR;
	
}

void    WebsocketPacket::parseUrlBody(const std::string& sQuery)
{

	std::vector<std::string> query = tars::TC_Common::sepstr<std::string>(sQuery,"&");
	
	for( std::size_t i = 0; i < query.size(); i++ )
	{	
		{
			std::vector<std::string> params;

			params.clear();
			
			params = tars::TC_Common::sepstr<std::string>( query[i], "=", true );
			if ( 2 == params.size() )
			{
				_params[ params[0] ] = tars::TC_Cgi::decodeURL(params[1]);
			}
		}
	}

}


std::string&			WebsocketPacket::getRoute(void)	  
{
	return _route;
}

pccl::REQUEST_PARAMS& 		WebsocketPacket::getParams(void)    
{
	return _params;
}

Json::Value& 		    WebsocketPacket::getDocument(void)    
{
	return _document;
}


int 					WebsocketPacket::getMethod(void)
{
	return _method;
}



}





