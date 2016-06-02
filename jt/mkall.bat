@echo off

:pushd jterminal 
:call m
:popd    

pushd jtlib 
call m 
popd

pushd jtstart 
call m
popd
    
pushd sslforward 
call m
popd

pushd msk2dlg
call m
popd

