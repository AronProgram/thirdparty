
#pragma once

#include "BaseRpcPlus.h"
#include "WebSocketHelpers.h"
#include "WebSocketProtocol.h"
#include "WebsocketType.h"
#include "json.h"
#include <string>

using namespace pccl;

namespace pccl::protocol::websocket 
{

struct WebsocketUserData
{	
	int          opCode;
	std::string  route;
	std::string  text;
	Json::Value  doc;

	WebsocketUserData(): 
		opCode(0),
		route(""),
		text("")
	{
	
	}

	WebsocketUserData(const WebsocketUserData& object)
	{		
		opCode   	= object.opCode;
		route       = object.route;	
		text        = object.text;	
		doc         = object.doc;
	}
		
	WebsocketUserData& operator = ( const WebsocketUserData& object)
	{
		if ( &object == this )
		{
			return *this;
		}

		opCode   	= object.opCode;
		route       = object.route;	
		text        = object.text;			
		doc         = object.doc;
		
		return *this;
		
	}
			
	
};



struct WebsocketImpl {
    static bool refusePayloadLength(uint64_t length, WebSocketState<true> *wState, void *s) {

        /* We need a limit */
        if (length > 16000) {
			setOpCode(s,pccl::protocol::websocket::REFUSE);
            return true;
        }

        /* Return ok */
        return false;
    }

    static bool setCompressed(WebSocketState<true> *wState, void *s) {
        /* We support it */
        return true;
    }

    static void forceClose(WebSocketState<true> *wState, void *s, std::string_view reason = {}) {
		setOpCode(s,pccl::protocol::websocket::CLOSE);
		setText(s,reason);
    }

    static bool handleFragment(char *data, size_t length, unsigned int remainingBytes, int opCode, bool fin, WebSocketState<true> *webSocketState, void *s) {
		
		setOpCode(s,opCode);

        if (opCode == pccl::protocol::websocket::TEXT ) 
		{			
            if ( isValidUtf8((unsigned char *)data, length) )

			{				
				std::string source(data,length);
				parseText(s,source);
				
                return true;
            }
        }
		else if (opCode == pccl::protocol::websocket::CLOSE ) 
		{			
            parseClosePayload((char *)data, length);			
        }

        /* Return ok */
        return false;
    }

	static void setOpCode( void *s, int opCode)
	{
		WebsocketUserData* data = static_cast<WebsocketUserData*>(s);
		data->opCode = opCode;
		data->route  = getOpRoute(opCode);
	}

	static void setText( void *s, std::string_view& reason)
	{
		WebsocketUserData* data = static_cast<WebsocketUserData*>(s);
		data->text              = reason.data();
	}

	static void setText( void *s, const std::string& content)
	{
		WebsocketUserData* data = static_cast<WebsocketUserData*>(s);
		data->text              = content;
	}
	
	static std::string getOpRoute(int opCode)
	{	
		std::string route = "";
		switch (opCode)
		{
			case pccl::protocol::websocket::TEXT:
				route = WEBSOCKET_PTOTOCOL_TEXT_ROUTE;
				break;
			
			case pccl::protocol::websocket::BINARY:
				route = WEBSOCKET_PTOTOCOL_BINARY_ROUTE;
				break;
			
			case pccl::protocol::websocket::CLOSE:
				route = WEBSOCKET_PTOTOCOL_CLOSE_ROUTE;
				break;
			
			case pccl::protocol::websocket::PING:
				route = WEBSOCKET_PTOTOCOL_PING_ROUTE;
				break;
			
			case pccl::protocol::websocket::PONG:
				route = WEBSOCKET_PTOTOCOL_PONG_ROUTE;
				break;
			
			case pccl::protocol::websocket::REFUSE:
				route = WEBSOCKET_PTOTOCOL_REFUSE_ROUTE;
				break;

			default:
				route = WEBSOCKET_PTOTOCOL_EMPTY_ROUTE;
				break;
				
		}

		return route;
	}

	
	static int parseText( void *s, const std::string& content)
	{

		WebsocketUserData* ptr = static_cast<WebsocketUserData*>(s);
		ptr->text              = content;
		
		try 
		{
			Json::Reader	reader;

			Json::Value 	data;
			
			bool status = reader.parse(content, data);
			if ( !status ) 
			{	
				TLOG_ERROR ( "parse error ,source:" << content << std::endl );	
				return pccl::STATE_ERROR;
			}	
	
			if ( data.isMember("aid") && data["aid"].isString() )
			{
				ptr->route = data["aid"].asString();
			}	
			
			ptr->doc = data;					
	
			return pccl::STATE_SUCCESS;
		}
		catch( Json::Exception& e)
		{
			TLOG_ERROR ( "Json::Exception  error :" << e.what() << ",source:" << content << std::endl );			
			return pccl::STATE_ERROR;
		}
		catch( std::exception& e)
		{
			TLOG_ERROR ( "exception  error :" << e.what() << ",source:" << content << std::endl );			
			return pccl::STATE_ERROR;
		}
	}
	
	
};

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

    /* Create the parser state */
    WebSocketState<true> state;

    makeChunked(makePadded(data, size), size, [&state](const uint8_t *data, size_t size) {
        /* Parse it */
        WebSocketProtocol<true, WebsocketImpl>::consume((char *) data, size, &state, nullptr);
    });

    return 0;
}


}


