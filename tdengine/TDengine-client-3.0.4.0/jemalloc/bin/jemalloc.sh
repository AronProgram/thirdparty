#!/bin/sh

prefix=/home/ubuntu/workroom/jenkins/3.0/TDinternal/community/debug/build
exec_prefix=/home/ubuntu/workroom/jenkins/3.0/TDinternal/community/debug/build
libdir=${exec_prefix}/lib

LD_PRELOAD=${libdir}/libjemalloc.so.2
export LD_PRELOAD
exec "$@"
