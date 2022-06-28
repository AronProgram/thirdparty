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
#include "BaseRpcPacket.h"
#include <map>
#include <string>


namespace pccl
{


class BaseRpcHttpPacket : public BaseRpcPacket
{

public:
	BaseRpcHttpPacket();
	~BaseRpcHttpPacket();

public:
	virtual  void                   reset();
	virtual  int   				    decodePacket(const std::vector<char>& buffer)  ;
	virtual std::string&  			getRoute(void)    ;	
	virtual REQUEST_PARAMS&        	getParams(void)    ;
	virtual Json::Value&        	getDocument(void)    ;
	virtual int                     getMethod(void);
	


private:
	int                             parseJsonBody(const std::string& content);
	void                            parseUrlBody(const std::string& content);


private:
	int               _method;
	std::string       _route;
	REQUEST_PARAMS    _params;
	Json::Value       _document;
	std::string       _text;
	

};


}

