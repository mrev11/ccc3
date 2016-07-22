
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

//eredetileg ezek static változók voltak savex.prg-ben
//minden static változó egy setget függvényre preprocesszálódik
//a setget-ek a savex.prg-ben vannak definiálva
//ahol a változók értéket kapnak, ott az eredeti
//
//  s_list:=x
//
//helyet be kell irni
//
//  S_LIST(x)
//
//a fordító jelzi ezeket a helyeket


#define  s_save      S_SAVE      ()
#define  s_work      S_WORK      ()
#define  s_extinc    S_EXTINC    ()
#define  s_extexc    S_EXTEXC    ()
#define  s_mindate   S_MINDATE   ()
#define  s_compmode  S_COMPMODE  ()
#define  s_direxc    S_DIREXC    ()
#define  s_dirsep    S_DIRSEP    ()
#define  s_seconds   S_SECONDS   ()
#define  s_content   S_CONTENT   ()
#define  s_plikex    S_PLIKEX    ()
#define  s_plikei    S_PLIKEI    ()
#define  s_likex     S_LIKEX     ()
#define  s_likei     S_LIKEI     ()
#define  s_liker     S_LIKER     ()
#define  s_find      S_FIND      ()
#define  s_symlink   S_SYMLINK   ()
#define  s_edit      S_EDIT      ()
#define  s_list      S_LIST      ()
