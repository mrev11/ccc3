@echo off

pushd driver-postgres
    call m.bat
popd

pushd driver-oracle
    call m.bat
popd

pushd util
    call mkall.bat
popd

pushd test
    call mkall.bat
popd
