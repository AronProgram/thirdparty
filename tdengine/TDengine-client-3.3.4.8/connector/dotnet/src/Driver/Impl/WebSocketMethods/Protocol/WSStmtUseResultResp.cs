﻿using Newtonsoft.Json;

namespace TDengine.Driver.Impl.WebSocketMethods.Protocol
{
    public class WSStmtUseResultResp:IWSBaseResp
    {
        [JsonProperty("code")] public int Code { get; set; }

        [JsonProperty("message")] public string Message { get; set; }

        [JsonProperty("action")] public string Action { get; set; }

        [JsonProperty("req_id")] public ulong ReqId { get; set; }

        [JsonProperty("timing")] public long Timing { get; set; }

        [JsonProperty("stmt_id")] public ulong StmtId { get; set; }

        [JsonProperty("result_id")] public ulong ResultId { get; set; }

        [JsonProperty("fields_count")] public int FieldsCount { get; set; }

        [JsonProperty("fields_names")] public string[] FieldsNames { get; set; }

        [JsonProperty("fields_types")] public byte[] FieldsTypes { get; set; }

        [JsonProperty("fields_lengths")] public long[] FieldsLengths { get; set; }

        [JsonProperty("precision")] public int Precision { get; set; }
    }
}