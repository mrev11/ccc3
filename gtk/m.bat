@echo off

if "%1" == "" (
    m.bat tee 2>&1 | tee log-install

) else (
    pushd codegen       & call m.bat & run.exe  & popd
    pushd code_byhand   & call m.bat            & popd
)

