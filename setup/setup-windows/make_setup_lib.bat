@echo off

call cc %CCCDIR%\ccclib\src\ui_\main.cpp
call cc %CCCDIR%\ccclib\src\ui_\remoteio.cpp

call cc %CCCDIR%\ccclib\src\windows\envir.cpp
call cc %CCCDIR%\ccclib\src\windows\filecreat.cpp
call cc %CCCDIR%\ccclib\src\windows\filecopy.cpp
call cc %CCCDIR%\ccclib\src\windows\findnext.cpp
call cc %CCCDIR%\ccclib\src\windows\fseek.cpp
call cc %CCCDIR%\ccclib\src\windows\lstat.cpp
call cc %CCCDIR%\ccclib\src\windows\nlstext.cpp
call cc %CCCDIR%\ccclib\src\windows\signals.cpp
call cc %CCCDIR%\ccclib\src\windows\spawn.cpp
call cc %CCCDIR%\ccclib\src\windows\thread.cpp

call cc %CCCDIR%\ccclib\src\add.cpp
call cc %CCCDIR%\ccclib\src\argv.cpp
call cc %CCCDIR%\ccclib\src\array.cpp
call cc %CCCDIR%\ccclib\src\asc.cpp
call cc %CCCDIR%\ccclib\src\asort.cpp
call cc %CCCDIR%\ccclib\src\at.cpp
call cc %CCCDIR%\ccclib\src\binary.cpp
call cc %CCCDIR%\ccclib\src\break.cpp
call cc %CCCDIR%\ccclib\src\color.cpp
call cc %CCCDIR%\ccclib\src\dirsep.cpp
call cc %CCCDIR%\ccclib\src\dtos.cpp
call cc %CCCDIR%\ccclib\src\empty.cpp
call cc %CCCDIR%\ccclib\src\equalto.cpp
call cc %CCCDIR%\ccclib\src\errorcode.cpp
call cc %CCCDIR%\ccclib\src\errorgen.cpp
call cc %CCCDIR%\ccclib\src\eval.cpp
call cc %CCCDIR%\ccclib\src\evalarr.cpp
call cc %CCCDIR%\ccclib\src\exec.cpp
call cc %CCCDIR%\ccclib\src\file.cpp
call cc %CCCDIR%\ccclib\src\fileconv.cpp
call cc %CCCDIR%\ccclib\src\fileio.cpp
call cc %CCCDIR%\ccclib\src\hashcode.cpp
call cc %CCCDIR%\ccclib\src\i2bin.cpp
call cc %CCCDIR%\ccclib\src\isalpha.cpp
call cc %CCCDIR%\ccclib\src\max.cpp
call cc %CCCDIR%\ccclib\src\object.cpp
call cc %CCCDIR%\ccclib\src\pad.cpp
call cc %CCCDIR%\ccclib\src\procline.cpp
call cc %CCCDIR%\ccclib\src\push.cpp
call cc %CCCDIR%\ccclib\src\pushcall.cpp
call cc %CCCDIR%\ccclib\src\qout.cpp
call cc %CCCDIR%\ccclib\src\quit.cpp
call cc %CCCDIR%\ccclib\src\rat.cpp
call cc %CCCDIR%\ccclib\src\replicate.cpp
call cc %CCCDIR%\ccclib\src\round.cpp
call cc %CCCDIR%\ccclib\src\run.cpp
call cc %CCCDIR%\ccclib\src\slice.cpp
call cc %CCCDIR%\ccclib\src\ss.cpp
call cc %CCCDIR%\ccclib\src\stat.cpp
call cc %CCCDIR%\ccclib\src\stdcmp.cpp
call cc %CCCDIR%\ccclib\src\str.cpp
call cc %CCCDIR%\ccclib\src\str2bin.cpp
call cc %CCCDIR%\ccclib\src\string.cpp
call cc %CCCDIR%\ccclib\src\stuff.cpp
call cc %CCCDIR%\ccclib\src\stvar.cpp
call cc %CCCDIR%\ccclib\src\substr.cpp
call cc %CCCDIR%\ccclib\src\time.cpp
call cc %CCCDIR%\ccclib\src\transform.cpp
call cc %CCCDIR%\ccclib\src\trim.cpp
call cc %CCCDIR%\ccclib\src\upper.cpp
call cc %CCCDIR%\ccclib\src\utf8conv.cpp
call cc %CCCDIR%\ccclib\src\val.cpp
call cc %CCCDIR%\ccclib\src\valtype.cpp
call cc %CCCDIR%\ccclib\src\variable.cpp
call cc %CCCDIR%\ccclib\src\variablex.cpp
call cc %CCCDIR%\ccclib\src\varprint.cpp
call cc %CCCDIR%\ccclib\src\xmethod3.cpp
call cc %CCCDIR%\ccclib\src\xmethod4.cpp
call cc %CCCDIR%\ccclib\src\xmethod6.cpp


:: plusz le kell forditani a helyben megorzott cpp-ket,
:: amik a ccc es ccc_ui_ konyvtarak forditasakor keszultek prg-bol 
:: (ez egyszerre mindent lefordit)

call cc 
