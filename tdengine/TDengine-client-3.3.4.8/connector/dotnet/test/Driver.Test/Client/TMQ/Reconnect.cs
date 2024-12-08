﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Net.Http;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;
using TDengine.Driver;
using TDengine.Driver.Client;
using TDengine.TMQ;
using Xunit;

namespace Driver.Test.Client.TMQ
{
    public partial class Consumer
    {
        private Process NewTaosAdapter(string port)
        {
            string exec;
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                exec = "C:\\TDengine\\taosadapter.exe";
            }
            else
            {
                exec = "taosadapter";
            }

            ProcessStartInfo startInfo = new ProcessStartInfo(exec, $"--port {port}");
            Process process = new Process { StartInfo = startInfo };
            return process;
        }

        private async Task Start(Process process, string port)
        {
            process.Start();
            await WaitForStart(port);
        }

        private void Stop(Process process)
        {
            if (process.HasExited)
            {
                return;
            }

            process.Kill();
        }

        private async Task WaitForStart(string port)
        {
            HttpClient client = new HttpClient();
            string url = $"http://127.0.0.1:{port}/-/ping";
            bool success = await WaitForPingSuccess(client, url);
            if (!success)
            {
                throw new Exception("Failed to start taosadapter");
            }
        }

        static async Task<bool> WaitForPingSuccess(HttpClient client, string url)
        {
            bool success = false;
            int retryCount = 20;
            int retryDelayMs = 100;

            for (int i = 0; i < retryCount; i++)
            {
                try
                {
                    HttpResponseMessage response = await client.GetAsync(url);
                    if (response.IsSuccessStatusCode)
                    {
                        success = true;
                        break;
                    }
                }
                catch (Exception e)
                {
                    // ignored
                }

                await Task.Delay(retryDelayMs);
            }

            return success;
        }

        [Fact]
        public void SubscribeReconnect()
        {
            var port = "36041";
            var process = NewTaosAdapter(port);
            Start(process, port).Wait();
            try
            {
                var connStr =
                    $"protocol=WebSocket;host=127.0.0.1;port={port};useSSL=false;username=root;password=taosdata;enableCompression=true";
                var builder = new ConnectionStringBuilder(connStr);
                using (var client = DbDriver.Open(builder))
                {
                    client.Exec("create database if not exists test_subscribe_reconnect");
                    client.Exec(
                        "create topic if not exists topic_subscribe_reconnect as database test_subscribe_reconnect");
                }

                var cfg = new Dictionary<string, string>()
                {
                    { "td.connect.type", "WebSocket" },
                    { "group.id", "test" },
                    { "auto.offset.reset", "earliest" },
                    { "td.connect.ip", "127.0.0.1" },
                    { "td.connect.user", "root" },
                    { "td.connect.pass", "taosdata" },
                    { "td.connect.port", $"{port}" },
                    { "client.id", "test_tmq_c" },
                    { "enable.auto.commit", "false" },
                    { "msg.with.table.name", "true" },
                    { "useSSL", "false" },
                    { "ws.autoReconnect", "true" },
                    { "ws.reconnect.retry.count", "3" },
                    { "ws.reconnect.interval.ms", "2000" }
                };
                var consumer = new ConsumerBuilder<Dictionary<string, object>>(cfg).Build();
                Stop(process);
                Task.Run(() =>
                {
                    Thread.Sleep(3000);
                    Start(process, port).Wait();
                });
                consumer.Subscribe("topic_subscribe_reconnect");
            }
            finally
            {
                Stop(process);
            }
        }

        [Fact]
        public void ConsumeReconnect()
        {
            var port = "36042";
            var process = NewTaosAdapter(port);
            Start(process, port).Wait();
            try
            {
                var connStr =
                    $"protocol=WebSocket;host=127.0.0.1;port={port};useSSL=false;username=root;password=taosdata;enableCompression=true";
                var builder = new ConnectionStringBuilder(connStr);
                using (var client = DbDriver.Open(builder))
                {
                    client.Exec("create database if not exists test_consume_reconnect");
                    client.Exec(
                        "create table if not exists test_consume_reconnect.t1 (ts timestamp, a int, b float, c binary(10))");
                    client.Exec(
                        "create topic if not exists topic_consume_reconnect as select * from test_consume_reconnect.t1");
                    client.Exec("insert into test_consume_reconnect.t1 values (now, 1, 1.1, 'abc')");
                }

                var cfg = new Dictionary<string, string>()
                {
                    { "td.connect.type", "WebSocket" },
                    { "group.id", "test" },
                    { "auto.offset.reset", "earliest" },
                    { "td.connect.ip", "127.0.0.1" },
                    { "td.connect.user", "root" },
                    { "td.connect.pass", "taosdata" },
                    { "td.connect.port", $"{port}" },
                    { "client.id", "test_tmq_c" },
                    { "enable.auto.commit", "false" },
                    { "msg.with.table.name", "true" },
                    { "useSSL", "false" },
                    { "ws.autoReconnect", "true" },
                    { "ws.reconnect.retry.count", "3" },
                    { "ws.reconnect.interval.ms", "2000" }
                };
                var consumer = new ConsumerBuilder<Dictionary<string, object>>(cfg).Build();
                consumer.Subscribe("topic_consume_reconnect");
                Stop(process);
                Task.Run(() =>
                {
                    Thread.Sleep(3000);
                    Start(process, port).Wait();
                });
                var data = consumer.Consume(1000);
                Assert.NotNull(data);
            }
            finally
            {
                Stop(process);
            }
        }
    }
}