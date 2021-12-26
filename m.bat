@echo off

call make_base 2>&1 | tee log-install

if "%1" == "x" (
    call make_extn 2>&1 | tee -a log-install
)
