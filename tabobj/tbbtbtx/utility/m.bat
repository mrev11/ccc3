@echo off
call bapp_w320  @parlib.bld

:: normalis rendszerben ez egy sor lehetne
:: a windows cmd elhagyja a hosszabb sorok veget
:: es a @parexe.bld resz mar lemarad

call bapp_w32_  -xbti       -xbtmemo    -xbtpage    @parexe.bld
call bapp_w32_  -xbt2dbf    -xbt2txt    -xbtpack    @parexe.bld
call bapp_w32_  -xbtcheck   -xbtdecrypt -xbtencrypt @parexe.bld
call bapp_w32_  -xbthead    -xbtstat    -xbtwalk    @parexe.bld

call bapp_w32c -xtstru -xtview -xbtp  -bccc%CCCVER%_btbtxui @parexe.bld


