
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
local options:=<<OPT>>
ddsync -- directory synchronization

With ddsync you can examine files in a directory structure.
Also, you can compare modification time of files in two parallel 
directory structures, examine the difference of file contents with 
diff utility, and synchronize files between the structures.

Onedir mode:
    If no -sSAVE option is given ddsync will run in "onedir" mode.
    All files of WORK directory that satisfy name-filter criteria 
    will be showed in a browse. The selection happens as follows:
 
    1) Any directories match to a pattern in -r or -lr will be skipped.

    2) Files that match to a pattern in -plx will be excluded. 
    3) Files that match to a pattern in -pli will be included. 
    4) Files that match to a pattern in -lx will be excluded. 
    5) Files that match to a pattern in -li will be included. 

    6) Now, if there is -x option then it gives the final result:
       A file will be excluded if and only if its extension is in -x.

    7) Next, if there is -i option then it gives the final result:
       A file will be included if and only if its extension is in -i.
       
    8) Ultimately, a file will be included if there is no -pli nor 
       -li option. Eg. if there is no other than one -pli option then 
       only those files  match to that pattern will be included.
       Conversely, if there are no options at all, all files will
       be included.

Twodir mode:
    With the -sSAVE option ddsync will run in "twodir" mode.    
    The program collects all files that satisfy name-filter criteria
    (see above) in both WORK and SAVE directories, then evaluates 
    the compare-filter criteria, and shows the result in a browse.
    The newer version of files are highlighted. One can examine 
    the difference of file contents with the diff utility. 
    Ddsync can synchronize files between the two directory structures.
    It has functions to overwrite old files  with the newer versions, 
    one at a time, or all at once. It is also possible to abandon 
    wrong changes and return to the older state.

Directory options:
    -s      SAVE directory, eg. "-ssome_place" (default empty)
    -w      WORK directory, eg. "-wsome_place" (defaults to cwd)


Name-Filter options:
    -r      excluded directories, eg. "-r:ppo:objlin:.git:" (additive)
    -lr     excluded directory name pattern, eg. "-lr*.nopack" (additive)

    -x      excluded extensions, eg. "-x.obj.ppo.bak." (additive)
    -lx     excluded name pattern, eg. "-lxlog-*", "-lxlog" (additive)          
    -plx    excluded pathname pattern (additive)      
    -plx@   filespec with excluded pathname patterns, eg. "-plx@some_file"  

    -i      included extensions, eg. "-i.prg.cpp.ch.h." (additive)
    -li     included name pattern (additive)
    -pli    included pathname pattern (additive)
    -pli@   filespec with included pathname patterns, eg. "-pli@some_file"


Compare-Filter options:
    -m0     include files exist in both SAVE and WORK if they differ
    -m1     include files exist in both SAVE and WORK
    -m2     include files exist in both SAVE and WORK if they match
    -mW     include files newer in WORK or don't exist in SAVE 
    -mS     include files newer in SAVE or don't exist in WORK
    -mD     unio of -mS and -mW (all difference)

Other options:
    -f      print names (instead of browsing)
    -h      show this page and quit
    -t      use seconds in filetime, eg. "-ts" use seconds (default no)
    -y      follow symlinks
    -yd     follow symlinks for directories
    -yf     follow symlinks for files

    -c      show files containing a given text, eg. "-ctext" (onedir mode)
    -d      show files newer than a date, eg. "-d19991231" (onedir mode)
    --edit: file editor, see EDIT evironment below (onedir mode, additive)
    --list: file viewer, see LIST evironment below (onedir mode, additive)

Environment:    
    CMP     program to do binary compare (default: cmp)
    DIFF    program to do text compare (default: diff)
    PREDIFFS filter to preprocess files in SAVE before text compare
    PREDIFFW filter to preprocess files in WORK before text compare

    EDIT    file editor (onedir mode, F4 shortcut)
            see LIST below with the same rules

    LIST    file viewer (onedir mode, F3 shortcut) 
            eg. export LIST='*=list.exe:png=eog:jpg=eog:mp3=mplayer "%f"&:'
            delimeter ':'
            png files will be "listed" with eog
            jpg files will be "listed" with eog
            mp3 files will be "listed" with mplayer
            all others (*) will be listed with list.exe
            %f will be replaced with filespec (pathname)
            if not given "%f" is added as the last argument
            (default 'list.exe "%f"')

    PLAY    program to process files (onedir/twodir mode, K_ALT_P shortcut)
            name comes from the case of audio files when processing means
            playing them whith a music player

Shortcuts in onedir mode:
    K_ALT_S skip: take out current row from the browse
    K_F3    list: "view/list" current file
    K_F4    edit: "edit" current file
    K_ALT_P play: start "playing" files from the current row 
    
Shortcuts in twodir mode:
    K_ALT_S skip: take out current row from the browse
    L_ALT_N copy new: old version of a file will be overwriten by the newer 
            one, current row will be taken out
    K_ALT_R reset: newer version of a file will be overwriten by the old one, 
            file without pair will be deleted, current row will be taken out  
    K_ALT_P play: start "playing" files from the current row 

<<OPT>>

    return options


****************************************************************************
