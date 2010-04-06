@echo off

set BUILD=%CCCDIR%\usr\bin\%CCCUNAME%\build.exe
:set PPO2CPP=%CCCDIR%\usr\bin\%CCCUNAME%\ppo2cpp.exe
set PRG2PPO=%CCCDIR%\usr\bin\%CCCUNAME%\prg2ppo.exe
set CCOMP=%CCCDIR%\usr\bin\%CCCUNAME%\ccomp.exe

if not exist %BUILD%    copy build_exe     %BUILD%    1>nul
:if not exist %PPO2CPP%  copy ppo2cpp_exe   %PPO2CPP%  1>nul
if not exist %PRG2PPO%  copy prg2ppo_exe   %PRG2PPO%  1>nul
if not exist %CCOMP%    copy ccomp_exe     %CCOMP%    1>nul

