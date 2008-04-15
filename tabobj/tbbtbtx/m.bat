call bapp_w320 @par-nt.bld  
call bapp_w320 @par-ntui.bld  
 
copy %BUILD_OBJ%\*.lib  %cccdir%\usr\lib\%cccbin%
 
pushd utility
call m
popd
 
 