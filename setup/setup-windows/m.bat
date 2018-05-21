@echo off 

set BUILD=%CCCDIR%\usr\bin\%CCCUNAME%\build.exe
set PRG2PPO=%CCCDIR%\usr\bin\%CCCUNAME%\prg2ppo.exe
set CCOMP=%CCCDIR%\usr\bin\%CCCUNAME%\ccomp.exe

if not exist %BUILD%      goto install
if not exist %PRG2PPO%    goto install
if not exist %CCOMP%      goto install
goto stop

:install


call make_setup_lib.bat


pushd build
    call ../cc.bat
    call ../xx.bat build
popd

pushd ccomp
    call ../cc.bat
    call ../xx.bat ccomp
popd

pushd prg2ppo
    call ../cc.bat
    call ../xx.bat prg2ppo
popd


cat build\log-link           >log-install
cat ccomp\log-link          >>log-install
cat prg2ppo\log-link        >>log-install

:: less log-install

:stop
