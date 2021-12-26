@echo off
call bapp_w320  @parlib.bld

call bapp_w32_ -xbti -xbt2dbf -xbt2txt -xtsema @parexe.bld
call bapp_w32c -xtstru -xtview -bccc%CCCVER%_btbtxui @parexe.bld
