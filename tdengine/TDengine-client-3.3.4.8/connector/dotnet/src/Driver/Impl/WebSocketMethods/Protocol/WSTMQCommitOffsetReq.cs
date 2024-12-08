﻿using Newtonsoft.Json;

namespace TDengine.Driver.Impl.WebSocketMethods.Protocol
{
    public class WSTMQCommitOffsetReq
    {
        [JsonProperty("req_id")] public ulong ReqId { get; set; }

        [JsonProperty("topic")] public string Topic { get; set; }

        [JsonProperty("vgroup_id")] public int VGroupId { get; set; }

        [JsonProperty("offset")] public long Offset { get; set; }
    }
}