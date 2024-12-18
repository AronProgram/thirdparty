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
#include "util/tc_http.h"


using namespace tars;

namespace pccl
{


/**
 *
 *
 */
template<typename Controller, bool IsCore = true>
class RpcControllerImplement : public Servant {
public:
    /**
     * 构造函数
     */
	RpcControllerImplement(void) {} 
	
	
    /**
     * 析构函数
     */
    virtual ~RpcControllerImplement() {}

    /**
     * 初始化
     */
    virtual void initialize() {}

    /**
     *  资源释放
     */
    virtual void destroy() {}

    /**
     * 处理http请求
     * @param TarsCurrentPtr : current
     * @param vector<char>   : buffer
     * @return :  true : is exist , false: not exist
     */
    int doRequest(TarsCurrentPtr current, std::vector<char>& outBuffer)
	{
		if ( IsCore == true )
		{
			return doRequestWithAny(current,outBuffer);
		}
		else
		{
			return doRequestWithDebug(current,outBuffer);
		}
		
	}

	
    /**
     * 处理http请求
     * @param TarsCurrentPtr : current
     * @param vector<char>   : buffer
     * @return :  true : is exist , false: not exist
     */
    int doRequestWithDebug(TarsCurrentPtr current, std::vector<char>& outBuffer)
	{
		try
		{
			return doRequestWithAny(current,outBuffer);
		}
		catch(exception &ex)
		{
			TLOGERROR("[PCCL]ControllerImplement::doRequest error: " << ex.what() << endl);
		}
		catch(...)
		{
			TLOGERROR("[PCCL]ControllerImplement::doRequest unknown error" << endl);
		}

		return pccl::STATE_SUCCESS;
	}


	 /**
     * 处理http请求
     * @param TarsCurrentPtr : current
     * @param vector<char>   : buffer
     * @return :  true : is exist , false: not exist
     */
    int doRequestWithAny(TarsCurrentPtr current, std::vector<char>& outBuffer)
	{
		
		_controller.reset();
		_controller.setRequest( current, &outBuffer );
		int result = _controller.doProcess();
		_controller.doOutput();
		
		TLOGDEBUG( "[PCCL] RpcApi result:" << result << ",response outBuffer size:" << outBuffer.size() << std::endl );
		
		return pccl::STATE_SUCCESS;
	}

private:
	Controller _controller;
	


};

}


