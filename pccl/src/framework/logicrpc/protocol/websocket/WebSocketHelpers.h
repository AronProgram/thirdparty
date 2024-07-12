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


#include <functional>
#include <string_view>
#include <cstring>

namespace pccl::protocol::websocket 
{
    
/* We use this to pad the fuzz */
static inline const uint8_t *makePadded(const uint8_t *data, size_t size) 
{
    static int paddedLength = 512 * 1024;
    static char *padded = new char[128 + paddedLength + 128];

    /* Increase landing area if required */
    if ( paddedLength < (int)size) 
    {
        delete [] padded;
        paddedLength = size;
        padded = new char [128 + paddedLength + 128];
    }

    memcpy(padded + 128, data, size);

    return (uint8_t *) padded + 128;
}

/* Splits the fuzz data in one or many chunks */
static inline void makeChunked(const uint8_t *data, size_t size, std::function<void(const uint8_t *data, size_t size)> cb)
{
    /* First byte determines chunk size; 0 is all that remains, 1-255 is small chunk */
    for (int i = 0; i < (int)size; ) 
    {
        unsigned int chunkSize = data[i++];
        if (!chunkSize) 
        {
            chunkSize = size - i;
        } 
        else 
        {
            chunkSize = std::min<int>(chunkSize, size - i);
        }

        cb(data + i, chunkSize);
        i += chunkSize;
    }
}

/* Reads all bytes to trigger invalid reads */
static inline void readBytes(std::string_view s) 
{
    volatile int sum = 0;
    for (int i = 0; i < (int)( s.size() ); i++) 
    {
        sum += s[i];
    }
}

}


