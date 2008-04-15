#!/bin/bash
# A $CCCDIR/tools/malloc_dbg wrapper könyvtárral indítja a programot.
# libmalloc_dbg.so-nak az LD_LIBRARY_PATH-ban kell lennie.

(LD_PRELOAD="/usr/lib/libdl.so libmalloc_dbg.so" "$@")
