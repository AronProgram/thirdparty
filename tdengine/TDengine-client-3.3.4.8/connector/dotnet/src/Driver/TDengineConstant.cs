﻿using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace TDengine.Driver
{
    public enum TDengineDataType
    {
        TSDB_DATA_TYPE_NULL = 0, // 1 bytes
        TSDB_DATA_TYPE_BOOL = 1, // 1 bytes
        TSDB_DATA_TYPE_TINYINT = 2, // 1 bytes
        TSDB_DATA_TYPE_SMALLINT = 3, // 2 bytes
        TSDB_DATA_TYPE_INT = 4, // 4 bytes
        TSDB_DATA_TYPE_BIGINT = 5, // 8 bytes
        TSDB_DATA_TYPE_FLOAT = 6, // 4 bytes
        TSDB_DATA_TYPE_DOUBLE = 7, // 8 bytes
        TSDB_DATA_TYPE_BINARY = 8, // string
        TSDB_DATA_TYPE_TIMESTAMP = 9, // 8 bytes
        TSDB_DATA_TYPE_NCHAR = 10, // unicode string
        TSDB_DATA_TYPE_UTINYINT = 11, // 1 byte
        TSDB_DATA_TYPE_USMALLINT = 12, // 2 bytes
        TSDB_DATA_TYPE_UINT = 13, // 4 bytes
        TSDB_DATA_TYPE_UBIGINT = 14, // 8 bytes
        TSDB_DATA_TYPE_JSONTAG = 15, //4096 bytes 
        TSDB_DATA_TYPE_VARBINARY = 16,
        TSDB_DATA_TYPE_GEOMETRY = 20,
    }

    public enum TDengineInitOption
    {
        TSDB_OPTION_LOCALE = 0,
        TSDB_OPTION_CHARSET = 1,
        TSDB_OPTION_TIMEZONE = 2,
        TSDB_OPTION_CONFIGDIR = 3,
        TSDB_OPTION_SHELL_ACTIVITY_TIMER = 4
    }

    public enum TDengineSchemalessProtocol
    {
        TSDB_SML_UNKNOWN_PROTOCOL = 0,
        TSDB_SML_LINE_PROTOCOL = 1,
        TSDB_SML_TELNET_PROTOCOL = 2,
        TSDB_SML_JSON_PROTOCOL = 3
    }

    public enum TDengineSchemalessPrecision
    {
        TSDB_SML_TIMESTAMP_NOT_CONFIGURED = 0,
        TSDB_SML_TIMESTAMP_HOURS = 1,
        TSDB_SML_TIMESTAMP_MINUTES = 2,
        TSDB_SML_TIMESTAMP_SECONDS = 3,
        TSDB_SML_TIMESTAMP_MILLI_SECONDS = 4,
        TSDB_SML_TIMESTAMP_MICRO_SECONDS = 5,
        TSDB_SML_TIMESTAMP_NANO_SECONDS = 6
    }

    enum TaosField
    {
        STRUCT_SIZE = 72,
        NAME_LENGTH = 65,
        TYPE_OFFSET = 65,
        BYTES_OFFSET = 68,
    }

    public class TDengineMeta
    {
        public string name = string.Empty;
        public int size;
        public byte type;

        public string TypeName()
        {
            switch ((TDengineDataType)type)
            {
                case TDengineDataType.TSDB_DATA_TYPE_BOOL:
                    return "BOOL";
                case TDengineDataType.TSDB_DATA_TYPE_TINYINT:
                    return "TINYINT";
                case TDengineDataType.TSDB_DATA_TYPE_SMALLINT:
                    return "SMALLINT";
                case TDengineDataType.TSDB_DATA_TYPE_INT:
                    return "INT";
                case TDengineDataType.TSDB_DATA_TYPE_BIGINT:
                    return "BIGINT";
                case TDengineDataType.TSDB_DATA_TYPE_UTINYINT:
                    return "TINYINT UNSIGNED";
                case TDengineDataType.TSDB_DATA_TYPE_USMALLINT:
                    return "SMALLINT UNSIGNED";
                case TDengineDataType.TSDB_DATA_TYPE_UINT:
                    return "INT UNSIGNED";
                case TDengineDataType.TSDB_DATA_TYPE_UBIGINT:
                    return "BIGINT UNSIGNED";
                case TDengineDataType.TSDB_DATA_TYPE_FLOAT:
                    return "FLOAT";
                case TDengineDataType.TSDB_DATA_TYPE_DOUBLE:
                    return "DOUBLE";
                case TDengineDataType.TSDB_DATA_TYPE_BINARY:
                    return "BINARY";
                case TDengineDataType.TSDB_DATA_TYPE_TIMESTAMP:
                    return "TIMESTAMP";
                case TDengineDataType.TSDB_DATA_TYPE_NCHAR:
                    return "NCHAR";
                case TDengineDataType.TSDB_DATA_TYPE_JSONTAG:
                    return "JSON";
                case TDengineDataType.TSDB_DATA_TYPE_VARBINARY:
                    return "VARBINARY";
                case TDengineDataType.TSDB_DATA_TYPE_GEOMETRY:
                    return "GEOMETRY";
                default:
                    return "undefine";
            }
        }

        public Type ScanType()
        {
            return TDengineConstant.ScanType((sbyte)type);
        }
    }

    public class StmtFields
    {
        internal string name { get; } = String.Empty;
        internal sbyte type { get; }
        internal byte preicision { get; }
        internal byte scale { get; }
        internal int bytes { get; }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct TAOS_MULTI_BIND
    {
        // column type
        public int buffer_type;

        // array, one or more lines column value
        public IntPtr buffer;

        //length of element in TAOS_MULTI_BIND.buffer (for binary and nchar it is the longest element's length)
        public UIntPtr buffer_length;

        //array, actual data length for each value
        public IntPtr length;

        //array, indicates each column value is null or not
        public IntPtr is_null;

        // line number, or the values number in buffer 
        public int num;
    }

    /// <summary>
    /// User defined callback function for interface "QueryAsync()"
    /// ,actually is a delegate in .Net.
    /// This function aim to handle the taoRes which points to
    /// the caller method's sql resultset.
    /// </summary>
    /// <param name="param"> This parameter will sent by caller method (QueryAsync()).</param>
    /// <param name="taoRes"> This is the retrieved by caller method's sql.</param>
    /// <param name="code"> 0 for indicate operation success and negative for operation fail.</param>
    public delegate void QueryAsyncCallback(IntPtr param, IntPtr taoRes, int code);

    /// <summary>
    /// User defined callback function for interface "FetchRowAsync()"
    /// ,actually is a delegate in .Net.
    /// This callback allow applications to get each row of the
    /// batch records by calling FetchRowAsync() forward iteration.
    /// After reading all the records in a block, the application needs to continue calling 
    /// FetchRowAsync() in this callback function to obtain the next batch of records for 
    /// processing until the number of records
    /// </summary>
    /// <param name="param">The parameter passed by <see cref="FetchRowAsync"/></param>
    /// <param name="taoRes">Query status</param>
    /// <param name="numOfRows"> The number of rows of data obtained (not a function of
    /// the entire query result set). When the number is zero (the result is returned) 
    /// or the number of records is negative (the query fails).</param>
    public delegate void FetchRawBlockAsyncCallback(IntPtr param, IntPtr taoRes, int numOfRows);

    //typedef void (tmq_commit_cb(tmq_t*, int32_t code, void* param));
    [UnmanagedFunctionPointer(callingConvention: CallingConvention.Cdecl)]
    public delegate void TmqCommitCallback(IntPtr tmq, Int32 code, IntPtr param);

    public enum TsdbServerStatus
    {
        TSDB_SRV_STATUS_UNAVAILABLE = 0,
        TSDB_SRV_STATUS_NETWORK_OK = 1,
        TSDB_SRV_STATUS_SERVICE_OK = 2,
        TSDB_SRV_STATUS_SERVICE_DEGRADED = 3,
        TSDB_SRV_STATUS_EXTING = 4,
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct TaosFieldE
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 65)]
        public string name;

        public sbyte type;
        public byte precision;
        public byte scale;
        public int bytes;
    }

    public enum TDenginePrecision : int
    {
        TSDB_TIME_PRECISION_MILLI = 0,
        TSDB_TIME_PRECISION_MICRO = 1,
        TSDB_TIME_PRECISION_NANO = 2
    }

    public static class TDengineConstant
    {
        public static readonly DateTime TimeZero = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
        public static readonly int Int8Size = sizeof(sbyte);
        public static readonly int Int16Size = sizeof(short);
        public static readonly int Int32Size = sizeof(int);
        public static readonly int Int64Size = sizeof(long);
        public static readonly int UInt8Size = sizeof(byte);
        public static readonly int UInt16Size = sizeof(ushort);
        public static readonly int UInt32Size = sizeof(uint);
        public static readonly int UInt64Size = sizeof(ulong);
        public static readonly int Float32Size = sizeof(float);
        public static readonly int Float64Size = sizeof(double);
        public static readonly int ByteSize = sizeof(byte);
        public static readonly int BoolSize = sizeof(bool);

        public static long ConvertDatetimeToTick(DateTime value, TDenginePrecision precision)
        {
            switch (precision)
            {
                case TDenginePrecision.TSDB_TIME_PRECISION_MILLI:
                    return (value.ToUniversalTime().Ticks - TimeZero.Ticks) / 10000;
                case TDenginePrecision.TSDB_TIME_PRECISION_MICRO:
                    return (value.ToUniversalTime().Ticks - TimeZero.Ticks) / 10;
                case TDenginePrecision.TSDB_TIME_PRECISION_NANO:
                    return (value.ToUniversalTime().Ticks - TimeZero.Ticks) * 100;
                default:
                    throw new NotSupportedException($"unknown precision {precision}");
            }
        }

        public static DateTime ConvertTimeToDatetime(long value, TDenginePrecision precision,
            TimeZoneInfo tz = default)
        {
            if (tz == default)
            {
                tz = TimeZoneInfo.Local;
            }

            switch (precision)
            {
                case TDenginePrecision.TSDB_TIME_PRECISION_MILLI:
                    return TimeZoneInfo.ConvertTime(TimeZero.AddTicks(value * 10000), tz);
                case TDenginePrecision.TSDB_TIME_PRECISION_MICRO:
                    return TimeZoneInfo.ConvertTime(TimeZero.AddTicks(value * 10), tz);
                case TDenginePrecision.TSDB_TIME_PRECISION_NANO:
                    return TimeZoneInfo.ConvertTime(TimeZero.AddTicks(value / 100), tz);
                default:
                    throw new NotSupportedException($"unknown precision {precision}");
            }
        }

        public static int BitmapLen(int n) => (n + ((1 << 3) - 1)) >> 3;
        public static int BitPos(int n) => n & ((1 << 3) - 1);
        public static int CharOffset(int n) => n >> 3;
        public static bool BitmapIsNull(byte c, int n) => (c & (1 << (7 - BitPos(n)))) == (1 << (7 - BitPos(n)));

        public static Dictionary<TDengineDataType, int> TypeLengthMap = new Dictionary<TDengineDataType, int>
        {
            { TDengineDataType.TSDB_DATA_TYPE_NULL, 1 },
            { TDengineDataType.TSDB_DATA_TYPE_BOOL, 1 },
            { TDengineDataType.TSDB_DATA_TYPE_TINYINT, 1 },
            { TDengineDataType.TSDB_DATA_TYPE_SMALLINT, 2 },
            { TDengineDataType.TSDB_DATA_TYPE_INT, 4 },
            { TDengineDataType.TSDB_DATA_TYPE_BIGINT, 8 },
            { TDengineDataType.TSDB_DATA_TYPE_FLOAT, 4 },
            { TDengineDataType.TSDB_DATA_TYPE_DOUBLE, 8 },
            { TDengineDataType.TSDB_DATA_TYPE_TIMESTAMP, 8 },
            { TDengineDataType.TSDB_DATA_TYPE_UTINYINT, 1 },
            { TDengineDataType.TSDB_DATA_TYPE_USMALLINT, 2 },
            { TDengineDataType.TSDB_DATA_TYPE_UINT, 4 },
            { TDengineDataType.TSDB_DATA_TYPE_UBIGINT, 8 }
        };

        public static string SchemalessPrecisionString(TDengineSchemalessPrecision precision)
        {
            switch (precision)
            {
                case TDengineSchemalessPrecision.TSDB_SML_TIMESTAMP_NOT_CONFIGURED:
                    return "";

                case TDengineSchemalessPrecision.TSDB_SML_TIMESTAMP_HOURS:
                    return "h";
                case TDengineSchemalessPrecision.TSDB_SML_TIMESTAMP_MINUTES:
                    return "m";
                case TDengineSchemalessPrecision.TSDB_SML_TIMESTAMP_SECONDS:
                    return "s";
                case TDengineSchemalessPrecision.TSDB_SML_TIMESTAMP_MILLI_SECONDS:
                    return "ms";
                case TDengineSchemalessPrecision.TSDB_SML_TIMESTAMP_MICRO_SECONDS:
                    return "u";
                case TDengineSchemalessPrecision.TSDB_SML_TIMESTAMP_NANO_SECONDS:
                    return "ns";
                default:
                    return "";
            }
        }

        public const string ProtocolNative = "Native";
        public const string ProtocolWebSocket = "WebSocket";

        public static Type ScanType(sbyte type)
        {
            switch ((TDengineDataType)type)
            {
                case TDengineDataType.TSDB_DATA_TYPE_BOOL:
                    return typeof(bool);
                case TDengineDataType.TSDB_DATA_TYPE_TINYINT:
                    return typeof(sbyte);
                case TDengineDataType.TSDB_DATA_TYPE_SMALLINT:
                    return typeof(short);
                case TDengineDataType.TSDB_DATA_TYPE_INT:
                    return typeof(int);
                case TDengineDataType.TSDB_DATA_TYPE_BIGINT:
                    return typeof(long);
                case TDengineDataType.TSDB_DATA_TYPE_UTINYINT:
                    return typeof(byte);
                case TDengineDataType.TSDB_DATA_TYPE_USMALLINT:
                    return typeof(ushort);
                case TDengineDataType.TSDB_DATA_TYPE_UINT:
                    return typeof(uint);
                case TDengineDataType.TSDB_DATA_TYPE_UBIGINT:
                    return typeof(ulong);
                case TDengineDataType.TSDB_DATA_TYPE_FLOAT:
                    return typeof(float);
                case TDengineDataType.TSDB_DATA_TYPE_DOUBLE:
                    return typeof(double);
                case TDengineDataType.TSDB_DATA_TYPE_BINARY:
                    return typeof(byte[]);
                case TDengineDataType.TSDB_DATA_TYPE_TIMESTAMP:
                    return typeof(DateTime);
                case TDengineDataType.TSDB_DATA_TYPE_NCHAR:
                    return typeof(string);
                case TDengineDataType.TSDB_DATA_TYPE_JSONTAG:
                    return typeof(byte[]);
                case TDengineDataType.TSDB_DATA_TYPE_VARBINARY:
                    return typeof(byte[]);
                case TDengineDataType.TSDB_DATA_TYPE_GEOMETRY:
                    return typeof(byte[]);
                default:
                    return typeof(DBNull);
            }
        }

        public static Type ScanNullableType(sbyte type)
        {
            switch ((TDengineDataType)type)
            {
                case TDengineDataType.TSDB_DATA_TYPE_BOOL:
                    return typeof(bool?);
                case TDengineDataType.TSDB_DATA_TYPE_TINYINT:
                    return typeof(sbyte?);
                case TDengineDataType.TSDB_DATA_TYPE_SMALLINT:
                    return typeof(short?);
                case TDengineDataType.TSDB_DATA_TYPE_INT:
                    return typeof(int?);
                case TDengineDataType.TSDB_DATA_TYPE_BIGINT:
                    return typeof(long?);
                case TDengineDataType.TSDB_DATA_TYPE_UTINYINT:
                    return typeof(byte?);
                case TDengineDataType.TSDB_DATA_TYPE_USMALLINT:
                    return typeof(ushort?);
                case TDengineDataType.TSDB_DATA_TYPE_UINT:
                    return typeof(uint?);
                case TDengineDataType.TSDB_DATA_TYPE_UBIGINT:
                    return typeof(ulong?);
                case TDengineDataType.TSDB_DATA_TYPE_FLOAT:
                    return typeof(float?);
                case TDengineDataType.TSDB_DATA_TYPE_DOUBLE:
                    return typeof(double?);
                case TDengineDataType.TSDB_DATA_TYPE_BINARY:
                    return typeof(byte[]);
                case TDengineDataType.TSDB_DATA_TYPE_TIMESTAMP:
                    return typeof(DateTime?);
                case TDengineDataType.TSDB_DATA_TYPE_NCHAR:
                    return typeof(string);
                case TDengineDataType.TSDB_DATA_TYPE_JSONTAG:
                    return typeof(byte[]);
                case TDengineDataType.TSDB_DATA_TYPE_VARBINARY:
                    return typeof(byte[]);
                case TDengineDataType.TSDB_DATA_TYPE_GEOMETRY:
                    return typeof(byte[]);
                default:
                    return typeof(DBNull);
            }
        }
    }

    public enum TMQ_CONF_RES
    {
        TMQ_CONF_UNKNOWN = -2,
        TMQ_CONF_INVALID = -1,
        TMQ_CONF_OK = 0,
    }

    public enum TMQ_RES
    {
        TMQ_RES_INVALID = -1,
        TMQ_RES_DATA = 1,
        TMQ_RES_TABLE_META = 2,
        TMQ_RES_METADATA = 3,
    }

    public struct TMQTopicAssignment
    {
        public int vgId;
        public long currentOffset;
        public long begin;
        public long end;
    }

    //typedef struct tmq_raw_data {
    //void    *raw;
    //uint32_t raw_len;
    //uint16_t raw_type;
    //} tmq_raw_data;

    public struct TMQRawData
    {
        public IntPtr raw;
        public uint rawLen;
        public ushort rawType;
    }
}