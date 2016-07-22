
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "savex.ch"


****************************************************************************
function usage()
    ? "SAVEX -sSave -iInExt -xExExt -lLike -rExDir -dDate -tSec -mMode -cText"
    ?
    ? "Save  - dirspec which we want to save to     e.g. -sa: or -s."
    ? "InExt - included extensions                  e.g. -i.prg.ch.cpp.h."
    ? "ExExt - excluded extensions                  e.g. -x.obj..exe."
    ? "Like  - included/excluded file name pattern  e.g. -li*.prg or -lx*.zip"
    ? "ExDir - excluded directories                 e.g. -r.ppo.obj32. or -r*"
    ? "Date  - minimal file modification date       e.g. -d1997.01.31"
    ? "Sec   - show seconds in file list            e.g. -ts" 
    ? "Mode  - comparing mode                       e.g. -m1 (see below)"
    ? 'Text  - only those files contain text        e.g. "-ctext"'
    ?
    ? "   -m0  : exist in Work and Save, different size or datetime"
    ? "   -m1  : exist in Work and Save (default)"
    ? "   -m2  : exist in Work and Save, the same size and datetime"
    ? "   -md  : unio of -mw and ms"
    ? "   -mw  : files newer in WORK than SAVE or missed in SAVE"
    ? "   -ms  : files newer in SAVE than WORK or missed in WORK"
    ?
    ? "Environment variables"
    ?
    ? "   CMP   filecomp-bin  default UNIX cmp , NT fc /b "
    ? "   DIFF  filecomp-txt  default UNIX diff, NT fc    "
    ? "   LIST  view          default UNIX less, NT list  "
    ?
    

****************************************************************************
