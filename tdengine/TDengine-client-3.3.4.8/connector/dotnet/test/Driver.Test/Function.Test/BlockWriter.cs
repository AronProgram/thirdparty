﻿using System;
using System.Text;
using TDengine.Driver;
using Xunit;
using Xunit.Abstractions;

namespace Driver.Test.Function.Test
{
    public class BlockWriterTest
    {
        private readonly ITestOutputHelper _testOutputHelper;

        public BlockWriterTest(ITestOutputHelper testOutputHelper)
        {
            _testOutputHelper = testOutputHelper;
        }

        [Fact]
        public void TestAllType()
        {
            var allType = new TaosFieldE[]
            {
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_BOOL },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_TINYINT },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_SMALLINT },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_INT },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_BIGINT },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_FLOAT },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_DOUBLE },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_BINARY },
                new TaosFieldE
                {
                    type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_TIMESTAMP,
                    precision = (byte)TDenginePrecision.TSDB_TIME_PRECISION_MILLI
                },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_NCHAR },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_UTINYINT },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_USMALLINT },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_UINT },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_UBIGINT },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_VARBINARY },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_GEOMETRY },
                new TaosFieldE { type = (sbyte)TDengineDataType.TSDB_DATA_TYPE_JSONTAG },
            };
            Random rand = new Random();
            bool v1 = true;
            sbyte v2 = 1;
            short v3 = -13084;
            int v4 = 171640731;
            long v5 = 768714961;
            byte v6 = 253;
            ushort v7 = 64626;
            uint v8 = 392905068;
            ulong v9 = 1790327521;
            float v10 = (float)0.3929452;
            double v11 = 0.45324843272107396;

            bool vv1 = false;
            sbyte vv2 = 1;
            short vv3 = 1;
            int vv4 = 1;
            long vv5 = 1;
            byte vv6 = 1;
            ushort vv7 = 1;
            uint vv8 = 1;
            ulong vv9 = 1;
            float vv10 = 1;
            double vv11 = 1;

            DateTime dateTime = DateTime.Now;
            var ts = (dateTime.ToUniversalTime().Ticks - TDengineConstant.TimeZero.Ticks) * 100;
            var nextSecondTs = (dateTime.Add(TimeSpan.FromSeconds(1)).ToUniversalTime().Ticks -
                                TDengineConstant.TimeZero.Ticks) * 100;
            var next2SecondTs = (dateTime.Add(TimeSpan.FromSeconds(2)).ToUniversalTime().Ticks -
                                 TDengineConstant.TimeZero.Ticks) * 100;
            var now = TDengineConstant.ConvertTimeToDatetime(ts, TDenginePrecision.TSDB_TIME_PRECISION_NANO);
            var nextSecond =
                TDengineConstant.ConvertTimeToDatetime(nextSecondTs, TDenginePrecision.TSDB_TIME_PRECISION_NANO);
            var next2Second =
                TDengineConstant.ConvertTimeToDatetime(next2SecondTs, TDenginePrecision.TSDB_TIME_PRECISION_NANO);

            var ab = new bool?[] { v1, null, vv1, };
            var ai8 = new sbyte?[] { v2, null, vv2 };
            var ai16 = new short?[] { v3, null, vv3 };
            var ai32 = new int?[] { v4, null, vv4 };
            var ai64 = new long?[] { v5, null, vv5 };
            var af = new float?[] { v10, null, vv10 };
            var ad = new double?[] { v11, null, vv11 };
            var av = new string?[] { "test1", null, "中文" };
            var au8 = new byte?[] { v6, null, vv6 };
            var au16 = new ushort?[] { v7, null, vv7 };
            var au32 = new uint?[] { v8, null, vv8 };
            var au64 = new ulong?[] { v9, null, vv9 };
            var at = new long[] { 1692754030419, 1692754031419, 1692754032419 };
            var an = new string?[] { "中文n", null, "n中文" };
            var aj = new string?[] { "{\"a\":\"b\"}", null, "{\"a\":\"b\"}" };
            var aVarBinary = new byte[]?[]
                { Encoding.UTF8.GetBytes("test_varbinary"), null, Encoding.UTF8.GetBytes("test_varbinary") };
            var aGeometry = new byte[]?[]
            {
                new byte[]
                {
                    0x01, 0x01, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x59,
                    0x40, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x59, 0x40
                },
                null, new byte[]
                {
                    0x01, 0x01, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x59,
                    0x40, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x59, 0x40
                }
            };
            var block = BlockWriter.Serialize(3, allType, ab, ai8, ai16,
                ai32, ai64, af, ad, av, at, an, au8, au16, au32, au64, aVarBinary, aGeometry, aj);
            var expect = new byte[]
            {
                0x01, 0x00, 0x00, 0x00, //version
                0x25, 0x02, 0x00, 0x00, //length
                0x03, 0x00, 0x00, 0x00, //rows
                0x11, 0x00, 0x00, 0x00, //columns
                0x00, 0x00, 0x00, 0x00, //flagSegment

                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //groupID

//types
                0x01, 0x01, 0x00, 0x00, 0x00,
                0x02, 0x01, 0x00, 0x00, 0x00,
                0x03, 0x02, 0x00, 0x00, 0x00,
                0x04, 0x04, 0x00, 0x00, 0x00,
                0x05, 0x08, 0x00, 0x00, 0x00,
                0x06, 0x04, 0x00, 0x00, 0x00,
                0x07, 0x08, 0x00, 0x00, 0x00,
                0x08, 0x00, 0x00, 0x00, 0x00,
                0x09, 0x08, 0x00, 0x00, 0x00,
                0x0A, 0x00, 0x00, 0x00, 0x00,
                0x0B, 0x01, 0x00, 0x00, 0x00,
                0x0C, 0x02, 0x00, 0x00, 0x00,
                0x0D, 0x04, 0x00, 0x00, 0x00,
                0x0E, 0x08, 0x00, 0x00, 0x00,
                0x10, 0x00, 0x00, 0x00, 0x00,
                0x14, 0x00, 0x00, 0x00, 0x00,
                0x0F, 0x00, 0x00, 0x00, 0x00,

//lengths
                0x03, 0x00, 0x00, 0x00,
                0x03, 0x00, 0x00, 0x00,
                0x06, 0x00, 0x00, 0x00,
                0x0C, 0x00, 0x00, 0x00,
                0x18, 0x00, 0x00, 0x00,
                0x0C, 0x00, 0x00, 0x00,
                0x18, 0x00, 0x00, 0x00,
                0x0F, 0x00, 0x00, 0x00,
                0x18, 0x00, 0x00, 0x00,
                0x1C, 0x00, 0x00, 0x00,
                0x03, 0x00, 0x00, 0x00,
                0x06, 0x00, 0x00, 0x00,
                0x0C, 0x00, 0x00, 0x00,
                0x18, 0x00, 0x00, 0x00,
                0x20, 0x00, 0x00, 0x00,
                0x2e, 0x00, 0x00, 0x00,
                0x16, 0x00, 0x00, 0x00,

                0x40, //bool
                0x01,
                0x00,
                0x00,

                0x40, //i8
                0x01,
                0x00,
                0x01,

                0x40, //i16
                0xE4, 0xCC,
                0x00, 0x00,
                0x01, 0x00,

                0x40, //i32
                0x9B, 0x07, 0x3B, 0x0A,
                0x00, 0x00, 0x00, 0x00,
                0x01, 0x00, 0x00, 0x00,

                0x40, //i64
                0xD1, 0xA8, 0xD1, 0x2D, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                0x40, //float 
                0x1D, 0x30, 0xC9, 0x3E,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x80, 0x3F,

                0x40, // double 
                0x68, 0x04, 0xE0, 0xB6, 0x05, 0x02, 0xDD, 0x3F,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F,

                0x00, 0x00, 0x00, 0x00, //binary
                0xFF, 0xFF, 0xFF, 0xFF,
                0x07, 0x00, 0x00, 0x00,
                0x05, 0x00,
                0x74, 0x65, 0x73, 0x74, 0x31,
                0x06, 0x00,
                0xE4, 0xB8, 0xAD, 0xE6, 0x96, 0x87,

                0x00, //ts
                0x53, 0xAF, 0x00, 0x20, 0x8A, 0x01, 0x00, 0x00,
                0x3B, 0xB3, 0x00, 0x20, 0x8A, 0x01, 0x00, 0x00,
                0x23, 0xB7, 0x00, 0x20, 0x8A, 0x01, 0x00, 0x00,

                0x00, 0x00, 0x00, 0x00, //nchar
                0xFF, 0xFF, 0xFF, 0xFF,
                0x0E, 0x00, 0x00, 0x00,
                0x0C, 0x00,
                0x2D, 0x4E, 0x00, 0x00, 0x87, 0x65, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x00,
                0x0C, 0x00,
                0x6E, 0x00, 0x00, 0x00, 0x2D, 0x4E, 0x00, 0x00, 0x87, 0x65, 0x00, 0x00,

                0x40, //u8
                0xFD,
                0x00,
                0x01,

                0x40, //u16
                0x72, 0xFC,
                0x00, 0x00,
                0x01, 0x00,

                0x40, //u32
                0x6C, 0x41, 0x6B, 0x17,
                0x00, 0x00, 0x00, 0x00,
                0x01, 0x00, 0x00, 0x00,

                0x40, //u64
                0xE1, 0x3A, 0xB6, 0x6A, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                //varbinary
                0x00, 0x00, 0x00, 0x00,
                0xFF, 0xFF, 0xFF, 0xFF,
                0x10, 0x00, 0x00, 0x00,
                0x0E, 0x00,
                0x74, 0x65, 0x73, 0x74, 0x5F, 0x76, 0x61, 0x72, 0x62, 0x69, 0x6E, 0x61, 0x72, 0x79,
                0x0E, 0x00,
                0x74, 0x65, 0x73, 0x74, 0x5F, 0x76, 0x61, 0x72, 0x62, 0x69, 0x6E, 0x61, 0x72, 0x79,

                //geometry
                0x00, 0x00, 0x00, 0x00,
                0xFF, 0xFF, 0xFF, 0xFF,
                0x17, 0x00, 0x00, 0x00,
                0x15, 0x00,
                0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x59, 0x40, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x59, 0x40,
                0x15, 0x00,
                0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x59, 0x40, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x59, 0x40,

                0x00, 0x00, 0x00, 0x00, //json
                0xFF, 0xFF, 0xFF, 0xFF,
                0x0B, 0x00, 0x00, 0x00,
                0x09, 0x00,
                0x7B, 0x22, 0x61, 0x22, 0x3A, 0x22, 0x62, 0x22, 0x7D,
                0x09, 0x00,
                0x7B, 0x22, 0x61, 0x22, 0x3A, 0x22, 0x62, 0x22, 0x7D,
            };
            Assert.Equal(expect, block);
        }
    }
}