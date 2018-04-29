@echo off 

:: egyszerre mindent (*.cpp) fordit
:: installalaskor csak ez hasznalhato 
:: mert ilyenkor a comp.exe (CCC) program
:: nem all rendelkezesre

set BUILD=%CCCDIR%\usr\bin\%CCCUNAME%\build.exe
set PRG2PPO=%CCCDIR%\usr\bin\%CCCUNAME%\prg2ppo.exe
set CCOMP=%CCCDIR%\usr\bin\%CCCUNAME%\ccomp.exe

if not exist %BUILD%      goto install
if not exist %PRG2PPO%    goto install
if not exist %CCOMP%      goto install
goto stop

:install


pushd lib1
    call ../comp/cc0.bat
popd

pushd lib2
    call ../comp/cc0.bat
popd

pushd lib3
    call ../comp/cc0.bat
popd


pushd _build
    call ../comp/cc0.bat
    call ../comp/x.bat build
popd

pushd _ccomp
    call ../comp/cc0.bat
    call ../comp/x.bat ccomp
popd

pushd _prg2ppo
    call ../comp/cc0.bat
    call ../comp/x.bat prg2ppo
popd


cat _build\log-link           >log-install
cat _ccomp\log-link          >>log-install
cat _prg2ppo\log-link        >>log-install

:: less log-install

:stop
