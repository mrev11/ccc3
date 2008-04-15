@echo off 
@echo PRG2OBJ.BAT %1 %2 

del error 2>nul
md ppo 2>nul
 

:Preprocesszor (prg-->ppo)
set CMPOPT=ppo\prg2ppo
del %CMPOPT% 2>nul

if not "%BUILD_PRE%"=="" echo %BUILD_PRE% >>%CMPOPT% 
 
set ECHOOUT=%CMPOPT%
set ECHOPRE=-I
set ECHOPOST=
call %BUILD_BAT%\_echo %BUILD_INC%

 
echo -dARROW     >>%CMPOPT%
echo -d_CCC_     >>%CMPOPT%
echo -d_CCC3_    >>%CMPOPT%
echo -dWIN32     >>%CMPOPT%
echo -dWINDOWS   >>%CMPOPT%
echo -d_WINDOWS_ >>%CMPOPT%
echo -ustd1.ch   >>%CMPOPT%
:type %CMPOPT%

if [%prg2ppo%] == [] set prg2ppo=prg2ppo
%prg2ppo% %2\%1.prg -oppo\%1.ppo  @%CMPOPT% >outpre
if errorlevel 1 copy outpre error >nul
if exist error goto stop


:CCC forditas (ppo-->cpp)
pushd ppo
del %1.cpp 2>nul
echo %2\%1.prg >ppo2cpp
ppo2cpp %1.ppo 2>>ppo2cpp
popd
if errorlevel 1 copy ppo\ppo2cpp error >nul
if exist error goto stop
:stouch ppo\%1.cpp


:C++ forditas (cpp-->obj)
call %BUILD_BAT%\_compile %1 ppo

:stop
@echo -------------------------------------------------------------------------

 