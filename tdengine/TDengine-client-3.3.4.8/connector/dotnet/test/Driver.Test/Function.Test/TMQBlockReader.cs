﻿using System.Text;
using TDengine.Driver;
using Xunit;
using Xunit.Abstractions;

namespace Function.Test.Taosc;

public class TMQBlockReaderTest
{
    private readonly ITestOutputHelper _testOutputHelper;

    public TMQBlockReaderTest(ITestOutputHelper testOutputHelper)
    {
        _testOutputHelper = testOutputHelper;
    }

    [Fact]
    public void TestTenBlock()
    {
        var data = new byte[]
        {
            0x01,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x01,
            0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x0a, 0x00, 0x00, 0x00,
            0x01,
            0x01,

            // block1
            0x4e,

            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x00,

            0x02, 0x00, 0x00, 0x00,
            0x3c, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x09, 0x08, 0x00, 0x00, 0x00,
            0x04, 0x04, 0x00, 0x00, 0x00,

            0x08, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,

            0x00,
            0x52, 0xed, 0x5b, 0x3a, 0x8d, 0x01, 0x00, 0x00,

            0x00,
            0x01, 0x00, 0x00, 0x00,

            0x04,
            0x00,

            0x09,
            0x01,
            0x10,
            0x02,
            0x03,
            0x74, 0x73, 0x00,

            0x04,
            0x01,
            0x08,
            0x04,
            0x02,
            0x76, 0x00,

            0x03,
            0x74, 0x31, 0x00,

            //block2
            0x4e,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,

            0x00,

            0x02, 0x00, 0x00, 0x00,
            0x3c, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x09, 0x08, 0x00, 0x00, 0x00,
            0x04, 0x04, 0x00, 0x00, 0x00,

            0x08, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,
            0x00,
            0x52, 0xed, 0x5b, 0x3a, 0x8d, 0x01, 0x00, 0x00,
            0x00,
            0x02, 0x00, 0x00, 0x00,

            0x04,
            0x00,

            0x09,
            0x01,
            0x10,
            0x02,
            0x03,
            0x74, 0x73, 0x00,

            0x04,
            0x01,
            0x08,
            0x04,
            0x02,
            0x76, 0x00,

            0x03,
            0x74, 0x32, 0x00,

            //block3
            0x4e,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,

            0x00,
            0x02, 0x00, 0x00, 0x00,
            0x3c, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x09, 0x08, 0x00, 0x00, 0x00,
            0x04, 0x04, 0x00, 0x00, 0x00,
            0x08, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,

            0x00,
            0x52, 0xed, 0x5b, 0x3a, 0x8d, 0x01, 0x00, 0x00,

            0x00,
            0x03, 0x00, 0x00, 0x00,

            0x04,
            0x00,

            0x09,
            0x01,
            0x10,
            0x02,
            0x03,
            0x74, 0x73, 0x00,

            0x04,
            0x01,
            0x08,
            0x04,
            0x02,
            0x76, 0x00,

            0x03,
            0x74, 0x33, 0x00,

            //block4
            0x4e,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x00,

            0x02, 0x00, 0x00, 0x00,
            0x3c, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x09, 0x08, 0x00, 0x00, 0x00,
            0x04, 0x04, 0x00, 0x00, 0x00,
            0x08, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,

            0x00,
            0x52, 0xed, 0x5b, 0x3a, 0x8d, 0x01, 0x00, 0x00,

            0x00,
            0x04, 0x00, 0x00, 0x00,

            0x04,
            0x00,

            0x09,
            0x01,
            0x10,
            0x02,
            0x03,
            0x74, 0x73, 0x00,

            0x04,
            0x01,
            0x08,
            0x04,
            0x02,
            0x76, 0x00,

            0x03,
            0x74, 0x34, 0x00,

            // block5
            0x4e,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x00,

            0x02, 0x00, 0x00, 0x00,
            0x3c, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x09, 0x08, 0x00, 0x00, 0x00,
            0x04, 0x04, 0x00, 0x00, 0x00,

            0x08, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,

            0x00,
            0x52, 0xed, 0x5b, 0x3a, 0x8d, 0x01, 0x00, 0x00,

            0x00,
            0x05, 0x00, 0x00, 0x00,

            0x04,
            0x00,

            0x09,
            0x01,
            0x10,
            0x02,
            0x03,
            0x74, 0x73, 0x00,

            0x04,
            0x01,
            0x08,
            0x04,
            0x02,
            0x76, 0x00,

            0x03,
            0x74, 0x35, 0x00,

            //block6
            0x4e,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x00,

            0x02, 0x00, 0x00, 0x00,
            0x3c, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x09, 0x08, 0x00, 0x00, 0x00,
            0x04, 0x04, 0x00, 0x00, 0x00,

            0x08, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,

            0x00,
            0x52, 0xed, 0x5b, 0x3a, 0x8d, 0x01, 0x00, 0x00,

            0x00,
            0x06, 0x00, 0x00, 0x00,

            0x04,
            0x00,

            0x09,
            0x01,
            0x10,
            0x02,
            0x03,
            0x74, 0x73, 0x00,

            0x04,
            0x01,
            0x08,
            0x04,
            0x02,
            0x76, 0x00,

            0x03,
            0x74, 0x36, 0x00,

            //block7
            0x4e,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x00,

            0x02, 0x00, 0x00, 0x00,
            0x3c, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x09, 0x08, 0x00, 0x00, 0x00,
            0x04, 0x04, 0x00, 0x00, 0x00,

            0x08, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,

            0x00,
            0x52, 0xed, 0x5b, 0x3a, 0x8d, 0x01, 0x00, 0x00,

            0x00,
            0x07, 0x00, 0x00, 0x00,

            0x04,
            0x00,

            0x09,
            0x01,
            0x10,
            0x02,
            0x03,
            0x74, 0x73, 0x00,

            0x04,
            0x01,
            0x08,
            0x04,
            0x02,
            0x76, 0x00,

            0x03,
            0x74, 0x37, 0x00,

            //block8
            0x4e,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x00,

            0x02, 0x00, 0x00, 0x00,
            0x3c, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x09, 0x08, 0x00, 0x00, 0x00,
            0x04, 0x04, 0x00, 0x00, 0x00,
            0x08, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,

            0x00,
            0x52, 0xed, 0x5b, 0x3a, 0x8d, 0x01, 0x00, 0x00,

            0x00,
            0x08, 0x00, 0x00, 0x00,

            0x04,
            0x00,

            0x09,
            0x01,
            0x10,
            0x02,
            0x03,
            0x74, 0x73, 0x00,

            0x04,
            0x01,
            0x08,
            0x04,
            0x02,
            0x76, 0x00,

            0x03,
            0x74, 0x38, 0x00,

            //block9
            0x4e,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x00,

            0x02, 0x00, 0x00, 0x00,
            0x3c, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x09, 0x08, 0x00, 0x00, 0x00,
            0x04, 0x04, 0x00, 0x00, 0x00,

            0x08, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,

            0x00,
            0x52, 0xed, 0x5b, 0x3a, 0x8d, 0x01, 0x00, 0x00,

            0x00,
            0x09, 0x00, 0x00, 0x00,

            0x04,
            0x00,

            0x09,
            0x01,
            0x10,
            0x02,
            0x03,
            0x74, 0x73, 0x00,

            0x04,
            0x01,
            0x08,
            0x04,
            0x02,
            0x76, 0x00,

            0x03,
            0x74, 0x39, 0x00,

            //block10
            0x4e,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x00,

            0x02, 0x00, 0x00, 0x00,
            0x3c, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x09, 0x08, 0x00, 0x00, 0x00,
            0x04, 0x04, 0x00, 0x00, 0x00,

            0x08, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,

            0x00,
            0x52, 0xed, 0x5b, 0x3a, 0x8d, 0x01, 0x00, 0x00,
            0x00,
            0x0a, 0x00, 0x00, 0x00,

            0x04,
            0x00,

            0x09,
            0x01,
            0x10,
            0x02,
            0x03,
            0x74, 0x73, 0x00,

            0x04,
            0x01,
            0x08,
            0x04,
            0x02,
            0x76, 0x00,
            0x04,
            0x74, 0x31, 0x30, 0x00,

            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        };
        var tmqBlockReader = new TMQBlockReader(0);
        var blockInfo = tmqBlockReader.Parse(data);
        Assert.Equal(10, blockInfo.Length);
        for (int i = 0; i < 10; i++)
        {
            Assert.Equal(0, blockInfo[i].precision);
            Assert.Equal(2, blockInfo[i].schemas.Length);
            Assert.Equal(9, blockInfo[i].schemas[0].colType);
            Assert.Equal(1, blockInfo[i].schemas[0].flag);
            Assert.Equal(8, blockInfo[i].schemas[0].bytes);
            Assert.Equal(1, blockInfo[i].schemas[0].colId);
            Assert.Equal("ts", blockInfo[i].schemas[0].name);
            Assert.Equal(4, blockInfo[i].schemas[1].colType);
            Assert.Equal(1, blockInfo[i].schemas[1].flag);
            Assert.Equal(4, blockInfo[i].schemas[1].bytes);
            Assert.Equal(2, blockInfo[i].schemas[1].colId);
            Assert.Equal("v", blockInfo[i].schemas[1].name);
            Assert.Equal($"t{i + 1}", blockInfo[i].tableName);
            BlockReader blockReader = new(24);
            blockReader.SetTMQBlock(data, blockInfo[i].precision, blockInfo[i].rawBlockOffset);
            var rows = blockReader.GetRows();
            Assert.Equal(1, rows);
            Assert.Equal(i + 1, blockReader.Read(0, 1));
            var dateTime =
                TDengineConstant.ConvertTimeToDatetime(1706081119570, TDenginePrecision.TSDB_TIME_PRECISION_MILLI);
            Assert.Equal(dateTime, blockReader.Read(0, 0));
        }
    }

    [Fact]
    public void Test100VersionBlock()
    {
        var data = new byte[]
        {
            0x64, //version
            0x12, 0x00, 0x00, 0x00, // skip 18 bytes
            0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00, //block count 1

            0x01, // with table name
            0x01, // with schema

            0x92, 0x02, // block length 274
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x00,

            0x02, 0x00, 0x00, 0x00,
            0x00, 0x01, 0x00, 0x00, // 256
            0x01, 0x00, 0x00, 0x00, // rows
            0x0e, 0x00, 0x00, 0x00, // cols
            0x00, 0x00, 0x00, 0x80,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x09, 0x08, 0x00, 0x00, 0x00,
            0x01, 0x01, 0x00, 0x00, 0x00,
            0x02, 0x01, 0x00, 0x00, 0x00,
            0x03, 0x02, 0x00, 0x00, 0x00,
            0x04, 0x04, 0x00, 0x00, 0x00,
            0x05, 0x08, 0x00, 0x00, 0x00,
            0x0b, 0x01, 0x00, 0x00, 0x00,
            0x0c, 0x02, 0x00, 0x00, 0x00,
            0x0d, 0x04, 0x00, 0x00, 0x00,
            0x0e, 0x08, 0x00, 0x00, 0x00,
            0x06, 0x04, 0x00, 0x00, 0x00,
            0x07, 0x08, 0x00, 0x00, 0x00,
            0x08, 0x16, 0x00, 0x00, 0x00,
            0x0a, 0x52, 0x00, 0x00, 0x00,

            0x08, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,
            0x08, 0x00, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,
            0x08, 0x00, 0x00, 0x00,
            0x04, 0x00, 0x00, 0x00,
            0x08, 0x00, 0x00, 0x00,
            0x08, 0x00, 0x00, 0x00,
            0x16, 0x00, 0x00, 0x00,

            0x00,
            0x9e, 0x37, 0x6a, 0x04, 0x8f, 0x01, 0x00, 0x00,

            0x00,
            0x01,

            0x00,
            0x02,

            0x00,
            0x03, 0x00,

            0x00,
            0x04, 0x00, 0x00, 0x00,

            0x00,
            0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x00,
            0x06,

            0x00,
            0x07, 0x00,

            0x00,
            0x08, 0x00, 0x00, 0x00,

            0x00,
            0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

            0x00,
            0xcf, 0xf7, 0x21, 0x41,

            0x00,
            0xe5, 0xd0, 0x22, 0xdb, 0xf9, 0x3e, 0x26, 0x40,

            0x00, 0x00, 0x00, 0x00,
            0x06, 0x00,
            0x62, 0x69, 0x6e, 0x61, 0x72, 0x79,

            0x00, 0x00, 0x00, 0x00,
            0x14, 0x00,
            0x6e, 0x00, 0x00, 0x00,
            0x63, 0x00, 0x00, 0x00,
            0x68, 0x00, 0x00, 0x00,
            0x61, 0x00, 0x00, 0x00,
            0x72, 0x00, 0x00, 0x00,

            0x00, //

            0x1c, // cols 14
            0x00, // version

            // col meta
            0x09, 0x01, 0x10, 0x02, 0x03, 0x74, 0x73, 0x00,
            0x01, 0x01, 0x02, 0x04, 0x03, 0x63, 0x31, 0x00,
            0x02, 0x01, 0x02, 0x06, 0x03, 0x63, 0x32, 0x00,
            0x03, 0x01, 0x04, 0x08, 0x03, 0x63, 0x33, 0x00,
            0x04, 0x01, 0x08, 0x0a, 0x03, 0x63, 0x34, 0x00,
            0x05, 0x01, 0x10, 0x0c, 0x03, 0x63, 0x35, 0x00,
            0x0b, 0x01, 0x02, 0x0e, 0x03, 0x63, 0x36, 0x00,
            0x0c, 0x01, 0x04, 0x10, 0x03, 0x63, 0x37, 0x00,
            0x0d, 0x01, 0x08, 0x12, 0x03, 0x63, 0x38, 0x00,
            0x0e, 0x01, 0x10, 0x14, 0x03, 0x63, 0x39, 0x00,
            0x06, 0x01, 0x08, 0x16, 0x04, 0x63, 0x31, 0x30, 0x00,
            0x07, 0x01, 0x10, 0x18, 0x04, 0x63, 0x31, 0x31, 0x00,
            0x08, 0x01, 0x2c, 0x1a, 0x04, 0x63, 0x31, 0x32, 0x00,
            0x0a, 0x01, 0xa4, 0x01, 0x1c, 0x04, 0x63, 0x31, 0x33, 0x00,

            0x06, // table name
            0x74, 0x5f, 0x61, 0x6c, 0x6c, 0x00,
            // sleep time
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        };
        var tmqBlockReader = new TMQBlockReader(0);
        var blockInfo = tmqBlockReader.Parse(data);
        Assert.Single(blockInfo);
        Assert.Equal(0, blockInfo[0].precision);
        Assert.Equal(14, blockInfo[0].schemas.Length);

        Assert.Equal(9, blockInfo[0].schemas[0].colType);
        Assert.Equal(1, blockInfo[0].schemas[0].flag);
        Assert.Equal(8, blockInfo[0].schemas[0].bytes);
        Assert.Equal(1, blockInfo[0].schemas[0].colId);
        Assert.Equal("ts", blockInfo[0].schemas[0].name);

        Assert.Equal(1, blockInfo[0].schemas[1].colType);
        Assert.Equal(1, blockInfo[0].schemas[1].flag);
        Assert.Equal(1, blockInfo[0].schemas[1].bytes);
        Assert.Equal(2, blockInfo[0].schemas[1].colId);
        Assert.Equal("c1", blockInfo[0].schemas[1].name);

        Assert.Equal(2, blockInfo[0].schemas[2].colType);
        Assert.Equal(1, blockInfo[0].schemas[2].flag);
        Assert.Equal(1, blockInfo[0].schemas[2].bytes);
        Assert.Equal(3, blockInfo[0].schemas[2].colId);
        Assert.Equal("c2", blockInfo[0].schemas[2].name);

        Assert.Equal(3, blockInfo[0].schemas[3].colType);
        Assert.Equal(1, blockInfo[0].schemas[3].flag);
        Assert.Equal(2, blockInfo[0].schemas[3].bytes);
        Assert.Equal(4, blockInfo[0].schemas[3].colId);
        Assert.Equal("c3", blockInfo[0].schemas[3].name);

        Assert.Equal(4, blockInfo[0].schemas[4].colType);
        Assert.Equal(1, blockInfo[0].schemas[4].flag);
        Assert.Equal(4, blockInfo[0].schemas[4].bytes);
        Assert.Equal(5, blockInfo[0].schemas[4].colId);
        Assert.Equal("c4", blockInfo[0].schemas[4].name);

        Assert.Equal(5, blockInfo[0].schemas[5].colType);
        Assert.Equal(1, blockInfo[0].schemas[5].flag);
        Assert.Equal(8, blockInfo[0].schemas[5].bytes);
        Assert.Equal(6, blockInfo[0].schemas[5].colId);
        Assert.Equal("c5", blockInfo[0].schemas[5].name);

        Assert.Equal(11, blockInfo[0].schemas[6].colType);
        Assert.Equal(1, blockInfo[0].schemas[6].flag);
        Assert.Equal(1, blockInfo[0].schemas[6].bytes);
        Assert.Equal(7, blockInfo[0].schemas[6].colId);
        Assert.Equal("c6", blockInfo[0].schemas[6].name);

        Assert.Equal(12, blockInfo[0].schemas[7].colType);
        Assert.Equal(1, blockInfo[0].schemas[7].flag);
        Assert.Equal(2, blockInfo[0].schemas[7].bytes);
        Assert.Equal(8, blockInfo[0].schemas[7].colId);
        Assert.Equal("c7", blockInfo[0].schemas[7].name);

        Assert.Equal(13, blockInfo[0].schemas[8].colType);
        Assert.Equal(1, blockInfo[0].schemas[8].flag);
        Assert.Equal(4, blockInfo[0].schemas[8].bytes);
        Assert.Equal(9, blockInfo[0].schemas[8].colId);
        Assert.Equal("c8", blockInfo[0].schemas[8].name);

        Assert.Equal(14, blockInfo[0].schemas[9].colType);
        Assert.Equal(1, blockInfo[0].schemas[9].flag);
        Assert.Equal(8, blockInfo[0].schemas[9].bytes);
        Assert.Equal(10, blockInfo[0].schemas[9].colId);
        Assert.Equal("c9", blockInfo[0].schemas[9].name);

        Assert.Equal(6, blockInfo[0].schemas[10].colType);
        Assert.Equal(1, blockInfo[0].schemas[10].flag);
        Assert.Equal(4, blockInfo[0].schemas[10].bytes);
        Assert.Equal(11, blockInfo[0].schemas[10].colId);
        Assert.Equal("c10", blockInfo[0].schemas[10].name);

        Assert.Equal(7, blockInfo[0].schemas[11].colType);
        Assert.Equal(1, blockInfo[0].schemas[11].flag);
        Assert.Equal(8, blockInfo[0].schemas[11].bytes);
        Assert.Equal(12, blockInfo[0].schemas[11].colId);
        Assert.Equal("c11", blockInfo[0].schemas[11].name);

        Assert.Equal(8, blockInfo[0].schemas[12].colType);
        Assert.Equal(1, blockInfo[0].schemas[12].flag);
        Assert.Equal(22, blockInfo[0].schemas[12].bytes);
        Assert.Equal(13, blockInfo[0].schemas[12].colId);
        Assert.Equal("c12", blockInfo[0].schemas[12].name);

        Assert.Equal(10, blockInfo[0].schemas[13].colType);
        Assert.Equal(1, blockInfo[0].schemas[13].flag);
        Assert.Equal(82, blockInfo[0].schemas[13].bytes);
        Assert.Equal(14, blockInfo[0].schemas[13].colId);
        Assert.Equal("c13", blockInfo[0].schemas[13].name);

        Assert.Equal("t_all", blockInfo[0].tableName);
        BlockReader blockReader = new(24);
        blockReader.SetTMQBlock(data, blockInfo[0].precision, blockInfo[0].rawBlockOffset);
        var rows = blockReader.GetRows();
        Assert.Equal(1, rows);
        var dateTime =
            TDengineConstant.ConvertTimeToDatetime(1713766021022, TDenginePrecision.TSDB_TIME_PRECISION_MILLI);
        Assert.Equal(dateTime, blockReader.Read(0, 0));
        Assert.Equal(true, blockReader.Read(0, 1));
        Assert.Equal((sbyte)2, blockReader.Read(0, 2));
        Assert.Equal((short)3, blockReader.Read(0, 3));
        Assert.Equal((int)4, blockReader.Read(0, 4));
        Assert.Equal((long)5, blockReader.Read(0, 5));
        Assert.Equal((byte)6, blockReader.Read(0, 6));
        Assert.Equal((ushort)7, blockReader.Read(0, 7));
        Assert.Equal((uint)8, blockReader.Read(0, 8));
        Assert.Equal((ulong)9, blockReader.Read(0, 9));
        Assert.Equal((float)10.123, blockReader.Read(0, 10));
        Assert.Equal((double)11.123, blockReader.Read(0, 11));
        Assert.Equal(Encoding.UTF8.GetBytes("binary"), blockReader.Read(0, 12));
        Assert.Equal("nchar", blockReader.Read(0, 13));
    }
}