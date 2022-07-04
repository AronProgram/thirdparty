/**
 * PCCL is pleased to support the open source community by making Tars available.
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



#include "BaseResult.h"
#include "util/tc_common.h"
#include "util/tc_cgi.h"
#include "BaseRpcPlus.h"
#include <map>


namespace pccl
{


BaseResult::BaseResult(): _code(0), _message(""),_sequence(""),_response("")
{
	reset();
}



BaseResult::~BaseResult()
{
	
}

void BaseResult::reset()
{	
	_code     = 0;
	_message  = "";
	_sequence = "";	
	_response = "";	
}

int  BaseResult::getCode()
{
	return _code;
}

const std::string&  BaseResult::getMessage()
{
	return _message;
}


const std::string&	BaseResult::getSequence()
{
	return _sequence;
}


void BaseResult::setSequence(const std::string& sSeq)
{
	_sequence = sSeq;
}

void	BaseResult::setResponse(const std::string& sRsp)
{
	_response = sRsp;
}

std::string&  BaseResult::getResponse()
{
	return _response;
}

void  BaseResult::error(int code,const std::string& msg )
{
	_code    = code;
	_message = msg;
}



}

