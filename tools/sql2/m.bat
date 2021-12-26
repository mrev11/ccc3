@echo off

: Windowson is minden lefordul, 
: de semmi sincs kiprobalva,
: szerezni kellene kliens dll-eket.


pushd driver-postgres   &  call m.bat & popd
pushd driver-oracle     &  call m.bat & popd
pushd driver-sqlite3    &  call m.bat & popd
pushd driver-mysql      &  call m.bat & popd
pushd driver-db2        &  call m.bat & popd
pushd util              &  call m.bat & popd

::pushd test              &  call m.bat & popd

