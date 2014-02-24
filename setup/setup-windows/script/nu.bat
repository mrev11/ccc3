@echo off 
net use s: \\10.0.2.4\qemu xxx  /USER:xxxxx /PERSISTENT:NO
net use
dir s:
