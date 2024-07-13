 /* Minzea is pleased to support the open source community by making Tars available.
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

#include <string>

namespace pccl::protocol::websocket
{

/////////////////////////////////////////////////////////////////////////
////
//// websocket 协议常量定义
/////////////////////////////////////////////////////////////////////////

//// websocket 魔法数
const std::string  WEBSOCKET_PTOTOCOL_MAGIC                    = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

//// websocket 协议路由
const std::string  WEBSOCKET_PTOTOCOL_CONTINUATION_ROUTE       = "continuationHandle";
const std::string  WEBSOCKET_PTOTOCOL_TEXT_ROUTE		       = "textHandle";
const std::string  WEBSOCKET_PTOTOCOL_BINARY_ROUTE		       = "binaryHandle";
const std::string  WEBSOCKET_PTOTOCOL_CLOSE_ROUTE		       = "closeHandle";
const std::string  WEBSOCKET_PTOTOCOL_PING_ROUTE		       = "pingHandle";
const std::string  WEBSOCKET_PTOTOCOL_PONG_ROUTE		       = "popngHandle";
const std::string  WEBSOCKET_PTOTOCOL_REFUSE_ROUTE		       = "refuseHandle";
const std::string  WEBSOCKET_PTOTOCOL_EMPTY_ROUTE		       = "emptyHandle";


}

