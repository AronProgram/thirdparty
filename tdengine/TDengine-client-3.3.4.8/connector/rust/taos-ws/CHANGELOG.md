# Changelog

All notable changes to this project will be documented in this file.


The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).
## [0.3.18] - 2023-01-12

### Features
- Use rustls with native roots by default


## [0.3.17] - 2023-01-08

### Dep
- Taos-query v0.3.13


## [0.3.16] - 2022-12-21

### Bug Fixes
- Fix DSN parsing with localhost and specified port


## [0.3.15] - 2022-12-10

### Bug Fixes
- Support api changes since 3.0.2.0
- Fix test error in CI


## [0.3.14] - 2022-12-09

### Bug Fixes
- Support write_raw_block_with_fields action


## [0.3.11] - 2022-11-22

### Enhancements

- *(ws)* Add features `rustls`/`native-tls` for ssl libs

## [0.3.10] - 2022-11-16

### Bug Fixes

- *(ws)* Fix websocket handout in release build

## [0.3.9] - 2022-11-11

### Bug Fixes

- *(ws)* Fix send error
- *(ws)* Fix call blocking error in async runtime- Use oneshot sender for async drop impls


## [0.3.8] - 2022-11-04

### Bug Fixes

- *(ws)* Fix error catching for query failed

## [0.3.7] - 2022-11-02

### Bug Fixes

- *(ws)* Broadcast errors when connection broken

## [0.3.6] - 2022-11-01

### Bug Fixes
- Remove initial poll since first msg not always none


## [0.3.5] - 2022-10-31

### Bug Fixes
- Cover timeout=never feature for websocket


## [0.3.4] - 2022-10-27

### Features
- Refactor write_raw_* apis


## [0.3.3] - 2022-10-13

### Bug Fixes

- *(ws)* Fix close on closed websocket connection

## [0.3.2] - 2022-10-12

### Bug Fixes

- *(ws)* Fix coredump when websocket already closed

## [0.3.0] - 2022-09-21

### Bug Fixes
- Handle error on ws disconnected abnormally


### Features
- Add MetaData variant for tmq message.
  - **BREAKING**: add MetaData variant for tmq message.


## [0.2.7] - 2022-09-16

### Bug Fixes
- Catch error in case of action fetch_block


### Performance

- *(mdsn)* Improve dsn parse performance and reduce binary size

## [0.2.6] - 2022-09-07

### Bug Fixes
- Sync on async websocket query support


### Testing
- Fix test cases compile error


## [0.2.5] - 2022-09-06

### Bug Fixes

- *(ws)* Fix data lost in large query set- Fix unknown action 'close', use 'free_result'


## [0.2.4] - 2022-09-02

### Bug Fixes
- Fix version action response error in websocket


## [0.2.3] - 2022-09-01

### Bug Fixes
- Fix websocket stmt set json tags error


## [0.2.2] - 2022-08-30

### Bug Fixes
- Remove unused log print


## [0.2.1] - 2022-08-22

### Bug Fixes

- *(query)* Fix websocket v2 float null
- *(ws)* Fix bigint/unsigned-bigint precision bug
- *(ws)* Fix stmt null error when buffer is empty
- *(ws)* Fix timing compatibility bug for v2
- *(ws)* Fix stmt bind with non-null values coredump
- *(ws)* Fix query errno when connection is not alive
- *(ws)* Fix fetch block unexpect exit
- *(ws)* Add ws-related error codes, fix version detection
- *(ws)* Use ws_errno/errstr in ws_fetch_block
- *(ws)* Not block on ws_get_server_info- Fix column length calculation for v2 block


### Documentation
- Add README and query/tmq examples


### Enhancements

- *(ws)* Feature gated ssl support for websocket

### Features

- *(libtaosws)* Add ws_get_server_info
- *(ws)* Add ws_stop_query, support write raw block
- *(ws)* Add ws_take_timing method for taosc cost
- *(ws)* Add stmt API- Add main connector


### Refactor

- *(query)* New version of raw block
- *(query)* Refactor query interface- Fix stmt bind with raw block error
- Fix nchar/json error, refactor error handling
- Use stable channel


### Testing
- Fix llvm-cov test error and report code coverage


## [0.2.0] - 2022-08-11

### Bug Fixes

- *(query)* Fix websocket v2 float null
- *(ws)* Fix bigint/unsigned-bigint precision bug
- *(ws)* Fix stmt null error when buffer is empty
- *(ws)* Fix timing compatibility bug for v2
- *(ws)* Fix stmt bind with non-null values coredump
- *(ws)* Fix query errno when connection is not alive
- *(ws)* Fix fetch block unexpect exit
- *(ws)* Add ws-related error codes, fix version detection
- *(ws)* Use ws_errno/errstr in ws_fetch_block
- *(ws)* Not block on ws_get_server_info- Fix column length calculation for v2 block


### Documentation
- Add README and query/tmq examples


### Enhancements

- *(ws)* Feature gated ssl support for websocket

### Features

- *(libtaosws)* Add ws_get_server_info
- *(ws)* Add ws_stop_query, support write raw block
- *(ws)* Add ws_take_timing method for taosc cost
- *(ws)* Add stmt API- Add main connector


### Refactor

- *(query)* New version of raw block
- *(query)* Refactor query interface- Fix stmt bind with raw block error
- Fix nchar/json error, refactor error handling
- Use stable channel


### Init
- First version for C libtaosws


<!-- generated by git-cliff -->