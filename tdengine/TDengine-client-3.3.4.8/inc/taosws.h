/*
 * Copyright (c) 2022 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TDENGINE_TAOS_WS_H
#define TDENGINE_TAOS_WS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * When using libtaosws along with libtaos, include `taos.h` in front of `taosws.h`, eg.
 *
 * ```c
 * include "taos.h"
 * include "taosws.h"
 * ```
 */
#ifndef TDENGINE_TAOS_H

/**
 * Data type definitions.
 */
#define TSDB_DATA_TYPE_NULL       0   // 1 bytes
#define TSDB_DATA_TYPE_BOOL       1   // 1 bytes
#define TSDB_DATA_TYPE_TINYINT    2   // 1 byte
#define TSDB_DATA_TYPE_SMALLINT   3   // 2 bytes
#define TSDB_DATA_TYPE_INT        4   // 4 bytes
#define TSDB_DATA_TYPE_BIGINT     5   // 8 bytes
#define TSDB_DATA_TYPE_FLOAT      6   // 4 bytes
#define TSDB_DATA_TYPE_DOUBLE     7   // 8 bytes
#define TSDB_DATA_TYPE_VARCHAR    8   // string, alias for varchar
#define TSDB_DATA_TYPE_TIMESTAMP  9   // 8 bytes
#define TSDB_DATA_TYPE_NCHAR      10  // unicode string
#define TSDB_DATA_TYPE_UTINYINT   11  // 1 byte
#define TSDB_DATA_TYPE_USMALLINT  12  // 2 bytes
#define TSDB_DATA_TYPE_UINT       13  // 4 bytes
#define TSDB_DATA_TYPE_UBIGINT    14  // 8 bytes
#define TSDB_DATA_TYPE_JSON       15  // json string
#define TSDB_DATA_TYPE_VARBINARY  16  // binary
#define TSDB_DATA_TYPE_DECIMAL    17  // decimal
#define TSDB_DATA_TYPE_BLOB       18  // binary
#define TSDB_DATA_TYPE_MEDIUMBLOB 19
#define TSDB_DATA_TYPE_BINARY     TSDB_DATA_TYPE_VARCHAR  // string
#define TSDB_DATA_TYPE_GEOMETRY   20  // geometry

#endif

/**
 * Websocket errors defnitions.
 *
 * Use error code prefix `E` to distinct from taosc error codes.
 */
#define TSDB_CODE_WS_DSN_ERROR        0xE000
#define TSDB_CODE_WS_INTERNAL_ERRO    0xE001
#define TSDB_CODE_WS_INTERNAL_ERROR   0xE001
#define TSDB_CODE_WS_CLOSED           0xE002
#define TSDB_CODE_WS_SEND_TIMEOUT     0xE003
#define TSDB_CODE_WS_RECV_TIMEOUT     0xE004



#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum WS_TSDB_SML_PROTOCOL_TYPE {
  WS_TSDB_SML_UNKNOWN_PROTOCOL = 0,
  WS_TSDB_SML_LINE_PROTOCOL = 1,
  WS_TSDB_SML_TELNET_PROTOCOL = 2,
  WS_TSDB_SML_JSON_PROTOCOL = 3,
} WS_TSDB_SML_PROTOCOL_TYPE;

typedef enum WS_TSDB_SML_TIMESTAMP_TYPE {
  WS_TSDB_SML_TIMESTAMP_NOT_CONFIGURED = 0,
  WS_TSDB_SML_TIMESTAMP_HOURS,
  WS_TSDB_SML_TIMESTAMP_MINUTES,
  WS_TSDB_SML_TIMESTAMP_SECONDS,
  WS_TSDB_SML_TIMESTAMP_MILLI_SECONDS,
  WS_TSDB_SML_TIMESTAMP_MICRO_SECONDS,
  WS_TSDB_SML_TIMESTAMP_NANO_SECONDS,
} WS_TSDB_SML_TIMESTAMP_TYPE;

typedef enum ws_tmq_conf_res_t {
  WS_TMQ_CONF_UNKNOWN = -2,
  WS_TMQ_CONF_INVALID = -1,
  WS_TMQ_CONF_OK = 0,
} ws_tmq_conf_res_t;

typedef enum ws_tmq_res_t {
  WS_TMQ_RES_INVALID = -1,
  WS_TMQ_RES_DATA = 1,
  WS_TMQ_RES_TABLE_META = 2,
  WS_TMQ_RES_METADATA = 3,
} ws_tmq_res_t;

/**
 * Opaque type definition for websocket connection.
 */
typedef void WS_TAOS;

/**
 * Opaque type definition for websocket result set.
 */
typedef void WS_RES;

/**
 * Field struct that has v3-compatible memory layout, which is recommended.
 */
typedef struct WS_FIELD {
  char name[65];
  uint8_t type;
  uint32_t bytes;
} WS_FIELD;

/**
 * Only useful for developers who use along with TDengine 2.x `TAOS_FIELD` struct.
 * It means that the struct has the same memory layout with the `TAOS_FIELD` struct
 * in taos.h of TDengine 2.x
 */
typedef struct WS_FIELD_V2 {
  char name[65];
  uint8_t type;
  uint16_t bytes;
} WS_FIELD_V2;

/**
 * Opaque type definition for websocket row.
 */
typedef const void *const *WS_ROW;

/**
 * Opaque STMT type alias.
 */
typedef void WS_STMT;

typedef struct TaosMultiBind {
  int buffer_type;
  const void *buffer;
  uintptr_t buffer_length;
  const int32_t *length;
  const char *is_null;
  int num;
} TaosMultiBind;

typedef struct TaosMultiBind WS_MULTI_BIND;

typedef struct StmtField {
  char name[65];
  int8_t type;
  uint8_t precision;
  uint8_t scale;
  int32_t bytes;
} StmtField;

typedef void ws_tmq_conf_t;

typedef void ws_tmq_list_t;

typedef void ws_tmq_t;

typedef struct ws_tmq_topic_assignment {
  int32_t vgId;
  int64_t currentOffset;
  int64_t begin;
  int64_t end;
} ws_tmq_topic_assignment;

/**
 * Enable inner log to stdout with para log_level.
 *
 * # Example
 *
 * ```c
 * ws_enable_log("debug");
 * ```
 */
int32_t ws_enable_log(const char *log_level);

const char *ws_data_type(int32_t type);

/**
 * Connect via dsn string, returns NULL if failed.
 *
 * Remember to check the return pointer is null and get error details.
 *
 * # Example
 *
 * ```c
 * char* dsn = "taos://localhost:6041";
 * WS_TAOS* taos = ws_connect(dsn);
 * if (taos == NULL) {
 *   int errno = ws_errno(NULL);
 *   char* errstr = ws_errstr(NULL);
 *   printf("Connection failed[%d]: %s", errno, errstr);
 *   exit(-1);
 * }
 * ```
 */
WS_TAOS *ws_connect(const char *dsn);

/**
 * Same to taos_get_server_info, returns server version info.
 */
const char *ws_get_server_info(WS_TAOS *taos);

/**
 * Same to taos_close. This should always be called after everything done with the connection.
 */
int32_t ws_close(WS_TAOS *taos);

/**
 * Query with a sql command, returns pointer to result set.
 *
 * Please always use `ws_errno` to check it work and `ws_free_result` to free memory.
 */
WS_RES *ws_query(WS_TAOS *taos, const char *sql);

WS_RES *ws_query_with_reqid(WS_TAOS *taos, const char *sql, uint64_t req_id);

int32_t ws_stop_query(WS_RES *rs);

/**
 * Query a sql with timeout.
 *
 * Please always use `ws_errno` to check it work and `ws_free_result` to free memory.
 */
WS_RES *ws_query_timeout(WS_TAOS *taos, const char *sql, uint32_t seconds);

/**
 * Get taosc execution timing duration as nanoseconds.
 */
int64_t ws_take_timing(WS_RES *rs);

/**
 * Always use this to ensure that the query is executed correctly.
 */
int32_t ws_errno(WS_RES *rs);

/**
 * Use this method to get a formatted error string when query errno is not 0.
 */
const char *ws_errstr(WS_RES *rs);

/**
 * Works exactly the same to taos_affected_rows.
 */
int32_t ws_affected_rows(const WS_RES *rs);

/**
 * Works exactly the same to taos_affected_rows64.
 */
int64_t ws_affected_rows64(const WS_RES *rs);

/**
 * use db.
 */
int32_t ws_select_db(WS_TAOS *taos, const char *db);

/**
 * If the query is update query or not
 */
const char *ws_get_client_info(void);

/**
 * Returns number of fields in current result set.
 */
int32_t ws_field_count(const WS_RES *rs);

/**
 * If the element is update query or not
 */
bool ws_is_update_query(const WS_RES *rs);

/**
 * Works like taos_fetch_fields, users should use it along with a `num_of_fields`.
 */
const struct WS_FIELD *ws_fetch_fields(WS_RES *rs);

/**
 * To fetch v2-compatible fields structs.
 */
const struct WS_FIELD_V2 *ws_fetch_fields_v2(WS_RES *rs);

/**
 * Works like taos_fetch_raw_block, it will always return block with format v3.
 */
int32_t ws_fetch_raw_block(WS_RES *rs, const void **pData, int32_t *numOfRows);

/**
 * If the element in (row, column) is null or not
 */
bool ws_is_null(const WS_RES *rs, int32_t row, int32_t col);

/**
 * Works like taos_fetch_row
 */
WS_ROW ws_fetch_row(WS_RES *rs);

/**
 * Returns number of fields in current result set.
 */
int32_t ws_num_fields(const WS_RES *rs);

/**
 * Same to taos_free_result. Every websocket result-set object should be freed with this method.
 */
int32_t ws_free_result(WS_RES *rs);

/**
 * Same to taos_result_precision.
 */
int32_t ws_result_precision(const WS_RES *rs);

/**
 * To get value at (row, col) in a block (as a 2-dimension matrix), input row/col index,
 * it will write the value type in *ty, and data length in *len, return a pointer to the real data.
 *
 * For type which is var-data (varchar/nchar/json), the `*len` is the bytes length, others is fixed size of that type.
 *
 * ## Example
 *
 * ```c
 * u8 ty = 0;
 * int len = 0;
 * void* v = ws_get_value_in_block(rs, 0, 0, &ty, &len);
 * if (ty == TSDB_DATA_TYPE_TIMESTAMP) {
 *   int64_t* timestamp = (int64_t*)v;
 *   printf("ts: %d\n", *timestamp);
 * }
 * ```
 */
const void *ws_get_value_in_block(WS_RES *rs,
                                  int32_t row,
                                  int32_t col,
                                  uint8_t *ty,
                                  uint32_t *len);

/**
 * Convert timestamp to C string.
 *
 * This function use a thread-local variable to print, it may works in most cases but not always be thread-safe,
 *  use it only if it work as you expected.
 */
void ws_timestamp_to_rfc3339(uint8_t *dest,
                             int64_t raw,
                             int32_t precision,
                             bool use_z);

int32_t ws_print_row(char *str,
                     int32_t str_len,
                     WS_ROW row,
                     const struct WS_FIELD *fields,
                     int32_t num_fields);

/**
 * Same to taos_get_current_db.
 */
int32_t ws_get_current_db(WS_TAOS *taos, char *database, int len, int *required);

WS_RES *ws_schemaless_insert_raw(WS_TAOS *taos,
                                 const char *lines,
                                 int len,
                                 int32_t *totalRows,
                                 int protocal,
                                 int precision);

WS_RES *ws_schemaless_insert_raw_with_reqid(WS_TAOS *taos,
                                            const char *lines,
                                            int len,
                                            int32_t *totalRows,
                                            int protocal,
                                            int precision,
                                            uint64_t reqid);

WS_RES *ws_schemaless_insert_raw_ttl(WS_TAOS *taos,
                                     const char *lines,
                                     int len,
                                     int32_t *totalRows,
                                     int protocal,
                                     int precision,
                                     int ttl);

WS_RES *ws_schemaless_insert_raw_ttl_with_reqid(WS_TAOS *taos,
                                                const char *lines,
                                                int len,
                                                int32_t *totalRows,
                                                int protocal,
                                                int precision,
                                                int ttl,
                                                uint64_t reqid);

/**
 * Create new stmt object.
 */
WS_STMT *ws_stmt_init(const WS_TAOS *taos);

/**
 * Create new stmt object with req_id.
 */
WS_STMT *ws_stmt_init_with_reqid(const WS_TAOS *taos, uint64_t req_id);

/**
 * Prepare with sql command
 */
int ws_stmt_prepare(WS_STMT *stmt, const char *sql, unsigned long len);

/**
 * Set table name.
 */
int ws_stmt_set_tbname(WS_STMT *stmt, const char *name);

/**
 * Set sub table name.
 */
int ws_stmt_set_sub_tbname(WS_STMT *stmt, const char *name);

/**
 * Set table name and tags.
 */
int ws_stmt_set_tbname_tags(WS_STMT *stmt,
                            const char *name,
                            const WS_MULTI_BIND *bind,
                            uint32_t len);

/**
 * Get tag fields.
 *
 * Please always use `ws_stmt_reclaim_fields` to free memory.
 */
int ws_stmt_get_tag_fields(WS_STMT *stmt, int *fieldNum, struct StmtField **fields);

/**
 * Get col fields.
 *
 * Please always use `ws_stmt_reclaim_fields` to free memory.
 */
int ws_stmt_get_col_fields(WS_STMT *stmt, int *fieldNum, struct StmtField **fields);

/**
 * Free memory of fields that was allocated by `ws_stmt_get_tag_fields` or `ws_stmt_get_col_fields`.
 */
int ws_stmt_reclaim_fields(WS_STMT *stmt, struct StmtField **fields, int fieldNum);

/**
 * Currently only insert sql is supported.
 */
int ws_stmt_is_insert(WS_STMT *stmt, int *insert);

int ws_stmt_set_tags(WS_STMT *stmt, const WS_MULTI_BIND *bind, uint32_t len);

int ws_stmt_bind_param_batch(WS_STMT *stmt, const WS_MULTI_BIND *bind, uint32_t len);

int ws_stmt_add_batch(WS_STMT *stmt);

/**
 * Execute the bind batch, get inserted rows in `affected_row` pointer.
 */
int ws_stmt_execute(WS_STMT *stmt, int32_t *affected_rows);

/**
 * Get inserted rows in current statement.
 */
int ws_stmt_affected_rows(WS_STMT *stmt);

/**
 * Get inserted rows in current statement.
 */
int ws_stmt_affected_rows_once(WS_STMT *stmt);

/**
 * Get num_params in current statement.
 */
int ws_stmt_num_params(WS_STMT *stmt, int *nums);

/**
 * Get param by index in current statement.
 */
int ws_stmt_get_param(WS_STMT *stmt, int idx, int *type, int *bytes);

/**
 * Equivalent to ws_errstr
 */
const char *ws_stmt_errstr(WS_STMT *stmt);

/**
 * Same to taos_stmt_close
 */
int32_t ws_stmt_close(WS_STMT *stmt);

/**
 * Create a new TMQ configuration object.
 */
ws_tmq_conf_t *ws_tmq_conf_new(void);

/**
 * Set a configuration property for the TMQ configuration object.
 */
enum ws_tmq_conf_res_t ws_tmq_conf_set(ws_tmq_conf_t *conf, const char *key, const char *value);

/**
 * Destroy the TMQ configuration object.
 */
int32_t ws_tmq_conf_destroy(ws_tmq_conf_t *conf);

/**
 * Create a new TMQ topic list object.
 */
ws_tmq_list_t *ws_tmq_list_new(void);

/**
 * Append a topic to the TMQ topic list.
 */
int32_t ws_tmq_list_append(ws_tmq_list_t *list, const char *topic);

/**
 * Destroy the TMQ topic list object.
 */
int32_t ws_tmq_list_destroy(ws_tmq_list_t *list);

/**
 *  Get the size of the TMQ topic list.
 */
int32_t ws_tmq_list_get_size(ws_tmq_list_t *list);

/**
 * Convert the TMQ topic list to a C array.
 */
char **ws_tmq_list_to_c_array(const ws_tmq_list_t *list, uint32_t *topic_num);

/**
 * Free the C array of topic strings.
 */
int32_t ws_tmq_list_free_c_array(char **c_str_arry, uint32_t topic_num);

/**
 * Create a new TMQ consumer.
 */
ws_tmq_t *ws_tmq_consumer_new(ws_tmq_conf_t *conf, const char *dsn, char *errstr, int errstr_len);

/**
 * Close the TMQ consumer.
 */
int32_t ws_tmq_consumer_close(ws_tmq_t *tmq);

/**
 * Subscribe the TMQ consumer to a list of topics.
 */
int32_t ws_tmq_subscribe(ws_tmq_t *tmq, const ws_tmq_list_t *topic_list);

/**
 * Unsubscribe the TMQ consumer from all topics.
 */
int32_t ws_tmq_unsubscribe(ws_tmq_t *tmq);

/**
 * Poll the TMQ consumer for messages.
 */
WS_RES *ws_tmq_consumer_poll(ws_tmq_t *tmq, int64_t timeout);

/**
 * Get the topic name from the result object.
 */
const char *ws_tmq_get_topic_name(const WS_RES *rs);

/**
 * Get the database name from the result object.
 */
const char *ws_tmq_get_db_name(const WS_RES *rs);

/**
 * Get the table name from the result object.
 */
const char *ws_tmq_get_table_name(const WS_RES *rs);

/**
 * Get the vgroup ID from the result object.
 */
int32_t ws_tmq_get_vgroup_id(const WS_RES *rs);

/**
 * Get the vgroup offset from the result object.
 */
int64_t ws_tmq_get_vgroup_offset(const WS_RES *rs);

/**
 * Get the result type from the result object.
 */
enum ws_tmq_res_t ws_tmq_get_res_type(const WS_RES *rs);

/**
 * Get the topic assignment for the TMQ consumer.
 */
int32_t ws_tmq_get_topic_assignment(ws_tmq_t *tmq,
                                    const char *pTopicName,
                                    struct ws_tmq_topic_assignment **assignment,
                                    int32_t *numOfAssignment);

/**
 * Free the topic assignment.
 */
int32_t ws_tmq_free_assignment(struct ws_tmq_topic_assignment *pAssignment,
                               int32_t numOfAssignment);

/**
 * Commit the current offset synchronously.
 */
int32_t ws_tmq_commit_sync(ws_tmq_t *tmq, const WS_RES *rs);

/**
 * Commit a specific topic and vgroup offset synchronously.
 */
int32_t ws_tmq_commit_offset_sync(ws_tmq_t *tmq,
                                  const char *pTopicName,
                                  int32_t vgId,
                                  int64_t offset);

/**
 * Get the committed offset for a specific topic and vgroup.
 */
int64_t ws_tmq_committed(ws_tmq_t *tmq, const char *pTopicName, int32_t vgId);

/**
 * Seek to a specific offset for a specific topic and vgroup.
 */
int32_t ws_tmq_offset_seek(ws_tmq_t *tmq, const char *pTopicName, int32_t vgId, int64_t offset);

/**
 * Get the current position for a specific topic and vgroup.
 */
int64_t ws_tmq_position(ws_tmq_t *tmq, const char *pTopicName, int32_t vgId);

/**
 * Equivalent to ws_errstr
 */
const char *ws_tmq_errstr(ws_tmq_t *tmq);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif
