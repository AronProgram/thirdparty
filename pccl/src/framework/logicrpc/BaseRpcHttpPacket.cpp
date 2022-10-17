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


#include "BaseRpcHttpPacket.h"
#include "util/tc_http.h"
#include "util/tc_cgi.h"
#include "json.h"



namespace pccl
{



BaseRpcHttpPacket::BaseRpcHttpPacket():_method(0)
{

}


BaseRpcHttpPacket::~BaseRpcHttpPacket()
{
	
}

void	BaseRpcHttpPacket::reset()
{
	_route = "";
	_text  = "";
	_params.clear();
	_document.clear();
}


int BaseRpcHttpPacket::decodePacket(const std::vector<char>& buffer)
{	

	try
	{
		// packet
		_text.insert(_text.begin(), buffer.begin(),buffer.end());

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
		REQUEST_PARAMS   headers;
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
			return parseJsonBody( content );
		}
		
		//解析http query stirng 的参数
		parseUrlBody(content);		
		
		return pccl::STATE_SUCCESS;

	}
	catch(std::exception& e )
	{
		TLOGERROR("packet http packet error, exception:" << e.what() << ",packet:" << _text << std::endl );
		return pccl::STATE_ERROR;
	}
}




int BaseRpcHttpPacket::parseJsonBody(const std::string& content)
{		
	
	Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader( builder.newCharReader() );
	
	JSONCPP_STRING  err;
	bool status = reader->parse(content.c_str(), content.c_str() + content.length() , &_document, &err);	
    if ( status ) 
	{
		return pccl::STATE_SUCCESS;
    }
	
	return pccl::STATE_ERROR;
	
}
void    BaseRpcHttpPacket::parseUrlBody(const std::string& sQuery)
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


std::string&			BaseRpcHttpPacket::getRoute(void)	  
{
	return _route;
}

REQUEST_PARAMS& 		BaseRpcHttpPacket::getParams(void)    
{
	return _params;
}

Json::Value& 		    BaseRpcHttpPacket::getDocument(void)    
{
	return _document;
}


int 					BaseRpcHttpPacket::getMethod(void)
{
	return _method;
}



}









