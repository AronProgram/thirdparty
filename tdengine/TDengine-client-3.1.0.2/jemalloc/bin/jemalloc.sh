#!/bin/sh

prefix=/data/release/TDinternal/community/debug/build
exec_prefix=/data/release/TDinternal/community/debug/build
libdir=${exec_prefix}/lib

LD_PRELOAD=${libdir}/libjemalloc.so.2
export LD_PRELOAD
exec "$@"
