@echo off
pushd codegen 
    call m.bat
    run.exe
popd

pushd code_byhand
    call m.bat
popd

