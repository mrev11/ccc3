@echo off 
@echo PRG2OBJ.BAT %1 %2 

del error--outpre-%1 2>nul
del error--ppo2cpp-%1 2>nul
del error--outcpp-%1 2>nul
md ppo 2>nul
 

:Preprocesszor (prg-->ppo)
set CMPOPT=ppo\prg2ppo-%1
del %CMPOPT% 2>nul

if not "%BUILD_PRE%"=="" echo %BUILD_PRE% >>%CMPOPT% 
 
set ECHOOUT=%CMPOPT%
set ECHOPRE=-I
set ECHOPOST=
call %BUILD_BAT%\_echo %BUILD_INC%

 
echo -dARROW            >>%CMPOPT%
echo -d_CCC_            >>%CMPOPT%
echo -d_CCC%CCCVER%_    >>%CMPOPT%
echo -dWIN32            >>%CMPOPT%
echo -dWINDOWS          >>%CMPOPT%
echo -d_WINDOWS_        >>%CMPOPT%
echo -ustd1.ch          >>%CMPOPT%
:type %CMPOPT%

if [%prg2ppo%] == [] set prg2ppo=prg2ppo
%prg2ppo% %2\%1.prg -oppo\%1.ppo  @%CMPOPT% >outpre-%1
if not errorlevel 1 goto prg2ppo_ok
    touch error
    type outpre-%1
    move outpre-%1 error--outpre-%1 >nul
    goto stop
:prg2ppo_ok
del outpre-%1

:CCC forditas (ppo-->cpp)
pushd ppo
del %1.cpp 2>nul
echo %2\%1.prg >ppo2cpp-%1
ppo2cpp %1.ppo 2>>ppo2cpp-%1
popd
if not errorlevel 1 goto ppo2cpp_ok
    touch error
    type ppo\ppo2cpp-%1
    move ppo\ppo2cpp-%1 error--ppo2cpp-%1 >nul
    goto stop
:ppo2cpp_ok
del ppo\ppo2cpp-%1

:C++ forditas (cpp-->obj)
call %BUILD_BAT%\_compile %1 ppo

:stop
@echo -------------------------------------------------------------------------

 