@echo off

: Windowson is minden lefordul, 
: de semmi sincs kipróbálva,
: szerezni kellene kliens dll-eket.

pushd driver-postgres
    call m.bat
popd

pushd driver-oracle
    call m.bat
popd

pushd driver-sqlite3
    call m.bat
popd

pushd util
    call mkall.bat
popd

pushd test
    call mkall.bat
popd
