
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

#ifndef _FILECONV_CH_
#define _FILECONV_CH_

// Windows<->UNIX konverziós flagek
// Clipper-be és C-be is inkludálódik
 
//----------------------------------------------------------------------------
// convertfspec2nativeformat-hoz való flagek
// convertfspec2nativeformat() mindig meghívódik, 
// amikor filénevet adunk át az os-nek
//----------------------------------------------------------------------------
 
#define DOSCONV_BS2SLASH         1  // bslash -> slash
#define DOSCONV_DRIVE2PATH       2  // drive: -> megadott path
#define DOSCONV_FNAME2LOWER      4  // a filénevet kisbetűre
#define DOSCONV_FNAMERTRIM       8  // a filénevet trimeli
#define DOSCONV_PATH2LOWER      16  // a path-t kisbetűre
#define DOSCONV_ENCODEFNAME     32  // ékezetes betűk átkódolása a filénévben
#define DOSCONV_ENCODEPATH      64  // ékezetes betűk átkódolása a pathban
#define DOSCONV_FNAMETO8PLUS3  128  // filénév csonkolása 8+3 alakúra
#define DOSCONV_PATHTO8PLUS3   256  // a path elemeinek csonkolása 8+3 alakúra
#define FDOSCONV_ALL           511

// csak a következők támogatottak:
// DOSCONV_BS2SLASH, DOSCONV_FNAMERTRIM,  
// DOSCONV_FNAME2LOWER, DOSCONV_PATH2LOWER 


//----------------------------------------------------------------------------
// directory() működését szabályozó flag-ek
//----------------------------------------------------------------------------
 
#define DOSCONV_FNAME_UPPER    512  // directory() nagybetűsíti a filéneveket
#define DOSCONV_FSPEC_ASTERIX 1024  // directory() a *.*-ot lecseréli *-ra
#define DDOSCONV_ALL          1536

//----------------------------------------------------------------------------
// fopen(), fcreate() működését szabályozó flag-ek
//----------------------------------------------------------------------------
 
#define DOSCONV_SPECDOSDEV    2048  // DOS eszközök (LPTn, PRN, CON, null)
#define DOSCONV_FILESHARE     4096  // exclusive/shared mód emulálás
#define ODOSCONV_ALL          6144

// getenv(), setenv(), putenv() működését szabályozó flag-ek

#define DOSCONV_ENVVAR2UPPER  8192  // nagybetűre konvertál
#define EDOSCONV_ALL          8192

//----------------------------------------------------------------------------
// defaultok
//----------------------------------------------------------------------------
 
#define FDOSCONV_DEFAULT (DOSCONV_BS2SLASH+DOSCONV_FNAME2LOWER+DOSCONV_FNAMERTRIM+DOSCONV_PATH2LOWER)
#define DDOSCONV_DEFAULT (DOSCONV_FNAME_UPPER+DOSCONV_FSPEC_ASTERIX)
#define ODOSCONV_DEFAULT (DOSCONV_SPECDOSDEV+DOSCONV_FILESHARE)
#define EDOSCONV_DEFAULT (DOSCONV_ENVVAR2UPPER)

#define DOSCONV_DEFAULT (FDOSCONV_DEFAULT+DDOSCONV_DEFAULT+ODOSCONV_DEFAULT+EDOSCONV_DEFAULT)

#endif

