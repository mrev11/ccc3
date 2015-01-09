#!/bin/bash
#export MKENTITYLIB_FORCE=on

pushd  driver-sqlite3;   m;         popd
pushd  driver-postgres;  m;         popd
pushd  driver-oracle;    m;         popd
pushd  driver-mysql;     m;         popd
pushd  util;             mkall.b;   popd
pushd  test;             mkall.b;   popd

pushd  $CCCDIR/usr/bin/$CCCUNAME; mklink.exe; popd
