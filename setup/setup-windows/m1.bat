@echo off 

:: egyesevel fordit
:: csak akkor hasznalhato 
:: ha rendelekzesre all a comp.exe (CCC) program
:: tesztelesjez ez a jo, mert nem kell varni
:: a korabbrol meglevo objectek forditasara



pushd lib1
    call ../comp/cc.bat
popd

pushd lib2
    call ../comp/cc.bat
popd

pushd lib3
    call ../comp/cc.bat
popd


pushd _build
    call ../comp/cc.bat
    call ../comp/x.bat build
popd

pushd _ccomp
    call ../comp/cc.bat
    call ../comp/x.bat ccomp
popd

pushd _prg2ppo
    call ../comp/cc.bat
    call ../comp/x.bat prg2ppo
popd


cat _build\log-link           >log-install
cat _ccomp\log-link          >>log-install
cat _prg2ppo\log-link        >>log-install

:: less log-install

