@echo on

call make_verf.bat 3

pushd jt\jtlib          & call m.bat & popd
                         
pushd tools\dbaseiii    & call m.bat & popd
pushd tools\dbfview     & call m.bat & popd
pushd tools\ddict2      & call m.bat & popd
pushd tools\list        & call m.bat & popd
pushd tools\pcre        & call m.bat & popd
pushd tools\savex       & call m.bat & popd
pushd tools\sql2        & call m.bat & popd
pushd tools\tdccmp      & call m.bat & popd
pushd tools\tran2cpp    & call m.bat & popd
pushd tools\websrv      & call m.bat & popd
pushd tools\zgrep       & call m.bat & popd
                         
pushd tutor\dtree       & call m.bat & popd
pushd tutor\fpath       & call m.bat & popd
pushd tutor\rename      & call m.bat & popd
                         

javac -version 2>NUL
if %errorlevel% == 0 (
pushd jt\jterminal      & call m.bat & popd
)

