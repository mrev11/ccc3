
# Windows Install

This install procedure was verified on Windows 7 (SP1), with MinGW 64-bit compiler. 
The 32-bit MinGW compiler was not tested, but it should work without any problem.
Microsoft C compiler is not supported any more.

### Dependencies

Make these directories in your home:

    c:\users\%USERNAME%\ccchome
    c:\users\%USERNAME%\ccchome\bin

Later we will refer to the `c:\users\%USERNAME%\ccchome` directory
as `CCCHOME` or `%CCCHOME%`. 

You have to download the latest PortableGit package from 
[this site](https://git-scm.com/download/win).
Choose the 64-bit "thumbdrive edition" version. 
Extract the archive in the `CCCHOME` directory, now you have

    c:\users\%USERNAME%\ccchome\PortableGit
    
with the Git version control system and many more utilities (ssh, scp, grep, diff, ...) 
in it. But you do not have any C compiler  yet.
On Windows we use the MinGW (Minimalist GNU for Windows) compiler, 
which is the Windows port of the [GNU Compiler Collection](https://en.wikipedia.org/wiki/GNU_Compiler_Collection) 
(GCC). Its maintenance needs the MSYS2 system, so you have to install the MSYS2 first.

From [this page](https://msys2.github.io/) 
download the 64-bit version of the msys2 package, install it  following the 
description on the same  page. The result is the `c:\msys64` directory on your computer. 
If you execute the

    c:\msys64\msys2_shell.cmd

script, then you get a console window with a proper msys2 environment in it.
In that environment execute this script:


    PREFIX=mingw-w64-x86_64

    pacman -S \
        $PREFIX-gcc\
        $PREFIX-openssl\
        $PREFIX-pcre\
        $PREFIX-gtk2\
        $PREFIX-pkg-config\
        $PREFIX-glib2

    # or
    # pacman -S $PREFIX-toolchain


which will install all CCC dependencies in the `c:\msys64\mingw64` directory.
Now, as the last step, make a directory junction 

    mklink /J c:\users\%USERNAME%\ccchome\mingw64  c:\msys64\mingw64 

As a result, you have the  `c:\users\%USERNAME%\ccchome\mingw64`
directory containing all C compilers and libraries.


### CCC environment

Install the following script into `CCCHOME\bin\cccenv.bat`: 

    @echo off
    chcp 65001
    
    set CCCVER=%1
    set CCCSUB=%2
    
    
    set CCCBIN=mng
    set CCCUNAME=windows
    set OREF_SIZE=50000
    
    set CCCDIR=%CCCHOME%\ccc%CCCVER%%CCCSUB%
    set CMPDIR=%CCCHOME%\mingw64
    set GTKDIR=%CCCHOME%\mingw64
    set GNUDIR=%CCCHOME%\portablegit
    
    :compiler path
    set PATH=%CMPDIR%\bin;%PATH%
    set INCLUDE=%CMPDIR%\include;%INCLUDE%
    set LIB=%CMPDIR%\lib;%LIB%
    
    :gnu-util path
    set PATH=%GNUDIR%\bin;%PATH%
    set PATH=%GNUDIR%\usr\bin;%PATH%
    
    :ccc path
    set PATH=%CCCDIR%\usr\bin\%CCCUNAME%;%PATH%
    set PATH=%CCCHOME%\bin;%PATH%
    
    :ccc terminal
    set CCCTERM_SIZE=90x32
    set CCCTERM_FONTSIZE=18
    set CCCTERM_CONNECT=%CCCDIR%\usr\bin\%CCCUNAME%\terminal.exe
    set JTERMINAL=%CCCDIR%\usr\bin\%CCCUNAME%\jterminal.jar
    
    :z-editor
    set ZCOLOR_0=b/w
    set ZCOLOR_2=w/b
    set ZHOME=%CCCHOME%\z
    
    :start terminal
    :cd %CCCHOME%
    cd %CCCDIR%
    title %CCCDIR%-%CCCBIN%
    :set | grep CCC
    start /b

and install the following 

    @echo off
    set CCCHOME=c:\users\%USERNAME%\ccchome
    %CCCHOME%\bin\cccenv  3


on your desktop into the `ccc3.bat` script. Now, if you start this script,
then you get a console window with the CCC3 environment in it.


### Cloning the CCC source

Start a CCC console (with the ccc3.bat script above), and in that
console execute the following command from the `CCCHOME` directory. 

    git clone https://github.com/mrev11/ccc3.git

This command extracts the CCC source into the `CCCHOME/ccc3` directory.
This place will be referred as `CCCDIR`. 


### Compiling CCC

Start a CCC console (with `ccc3.bat` from the desktop), 
go into the `CCCDIR`(=`CCCHOME\ccc3`) directory,
and  execute the `i.bat` script. 
This will compile the whole CCC. The process must be successful without
any error or warning. Otherwise you have to verify the 

  * fulfilment of dependencies,
    
  * the CCC environment.

From time to time, using the newer and newer C compilers, there may be new warnings,
which will be fixed during the regular maintenance of CCC.
   


