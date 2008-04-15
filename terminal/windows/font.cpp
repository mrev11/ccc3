
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

#include <windows.h>
#include <stdio.h>
#include <string.h>

static char *fontface="Courier New";
static int fontheight=16;


HFONT font()
{
    if( getenv("CCCTERM_FONTFACE") )
    {
        fontface=getenv("CCCTERM_FONTFACE");
    }

    if( getenv("CCCTERM_FONTSIZE") )
    {
        sscanf(getenv("CCCTERM_FONTSIZE"),"%d",&fontheight);
    }

    LOGFONT lf;
    lf.lfHeight         = fontheight;
    lf.lfWidth          = 0;
    lf.lfEscapement     = 0;
    lf.lfOrientation    = 0;
    lf.lfWeight         = FW_NORMAL;
    lf.lfItalic         = 0;
    lf.lfUnderline      = 0;
    lf.lfStrikeOut      = 0;
    lf.lfCharSet        = OEM_CHARSET; //DEFAULT_CHARSET;
    lf.lfOutPrecision   = 1;
    lf.lfClipPrecision  = 2;
    lf.lfQuality        = 1;
    lf.lfPitchAndFamily = 1;

    strcpy(lf.lfFaceName,fontface);
            
    return CreateFontIndirect(&lf);
}    
