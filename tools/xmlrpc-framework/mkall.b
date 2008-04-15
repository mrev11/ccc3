#!/bin/bash

pushd rpcutil                   && m; popd
pushd server/rpcwrapper         && m; popd
pushd server/rpcsession         && m; popd
pushd server/test               && m; popd

pushd client/rpcmonitor         && m; popd
pushd client/test               && m; popd
