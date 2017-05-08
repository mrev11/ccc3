@echo off

pushd msk2say
call m.bat
popd

call bapp_w32c  -xmask -xpage  @parfile.bld
call bapp_w32_  -xmsk2pge -xpge2wro  @parfile.bld

