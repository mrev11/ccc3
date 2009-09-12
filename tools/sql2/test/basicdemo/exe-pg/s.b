#!/bin/bash
#export SQLDEBUG=on
rm log-*

te-create.exe
te-insert.exe
te-insupd.exe
te-select.exe
te-select_ge.exe
te-select_kk.exe
te-select_tf.exe
te-select_bl.exe

query.exe
entity.exe

list-abc.exe
list-ps.exe
