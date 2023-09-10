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

#pragma once


#include "json.h"
#include "util/tc_http.h"
#include "BaseErrorCode.h"
#include <string>



namespace pccl
{



/**
*
*
*/
class BaseResult           
{

public:		
	/**
	*
	*  构造函数
	*/
	BaseResult(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseResult();
	

public:

	/**
	*  重置
	* 
	*/
	void reset();	
	void clear();	
	
	int  getCode();
	const std::string&  getMessage();
	
	std::string         getErrorResponse();

	void                setSequence(const std::string& sSeq);
	const std::string&  getSequence();

	void                setResponse(const std::string& sRsp);
	std::string&        getResponse();	

	void error(int code);
	void error(int code,const std::string& msg );






protected:
	int           _code;
	std::string   _message;
	std::string   _sequence;
	std::string   _response;
      
	
};



}

