@echo off

if not exist obj%CCCBIN% (
    mkdir obj%CCCBIN%
)

pkg-config --cflags gtk+-2.0             >obj%CCCBIN%/gtk-cflags
echo -DGDK_DISABLE_DEPRECATED           >>obj%CCCBIN%/gtk-cflags
::echo -DGTK_DISABLE_DEPRECATED           >>obj%CCCBIN%/gtk-cflags
echo -DGTK_DISABLE_SINGLE_INCLUDES      >>obj%CCCBIN%/gtk-cflags
echo -DGSEAL_ENABLE                     >>obj%CCCBIN%/gtk-cflags

echo -DCOMPILE_TERMINAL                 >>obj%CCCBIN%/gtk-cflags
echo -Wno-deprecated-declarations       >>obj%CCCBIN%/gtk-cflags

pkg-config --libs   gtk+-2.0            >obj%CCCBIN%/gtk-libs



call bapp_w320.bat @parfile.bld 
