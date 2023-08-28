
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

static const char *fontface="Consoleas";
static int fontheight=12;

static void print_logfont(LOGFONT *lf)
{
    printf("\n");
    printf("lfFaceName       = %s  \n", lf->lfFaceName      );
    printf("lfHeight         = %ld \n", lf->lfHeight        );
    printf("lfWidth          = %ld \n", lf->lfWidth         );
    printf("lfEscapement     = %ld \n", lf->lfEscapement    );
    printf("lfOrientation    = %ld \n", lf->lfOrientation   );
    printf("lfWeight         = %ld \n", lf->lfWeight        );
    printf("lfItalic         = %d  \n", lf->lfItalic        );
    printf("lfUnderline      = %d  \n", lf->lfUnderline     );
    printf("lfStrikeOut      = %d  \n", lf->lfStrikeOut     );
    printf("lfCharSet        = %d  \n", lf->lfCharSet       );
    printf("lfOutPrecision   = %d  \n", lf->lfOutPrecision  );
    printf("lfClipPrecision  = %d  \n", lf->lfClipPrecision );
    printf("lfQuality        = %d  \n", lf->lfQuality       );
    printf("lfPitchAndFamily = %d  \n", lf->lfPitchAndFamily);
}


HFONT font()
{
#ifdef KISERLETEZEM_A_FONTOKKAL
    CHOOSEFONT cf;
    LOGFONT lf;

    // Initialize members of the CHOOSEFONT structure.

    cf.lStructSize = sizeof(CHOOSEFONT);
    cf.hwndOwner = (HWND)NULL;
    cf.hDC = (HDC)NULL;
    cf.lpLogFont = &lf;
    cf.iPointSize = 0;
    cf.Flags = CF_SCREENFONTS;
    cf.rgbColors = RGB(0,0,0);
    cf.lCustData = 0L;
    cf.lpfnHook = (LPCFHOOKPROC)NULL;
    cf.lpTemplateName = (LPSTR)NULL;
    cf.hInstance = (HINSTANCE) NULL;
    cf.lpszStyle = (LPSTR)NULL;
    cf.nFontType = SCREEN_FONTTYPE;
    cf.nSizeMin = 0;
    cf.nSizeMax = 0;

    // Display the CHOOSEFONT common-dialog box.

    ChooseFont(&cf);

    print_logfont(&lf);

    // Create a logical font based on the user's
    // selection and return a handle identifying
    // that font.

    return CreateFontIndirect(cf.lpLogFont);
#else

    if( getenv("CCCTERM_FONTFACE") )
    {
        fontface=getenv("CCCTERM_FONTFACE");
    }

    if( getenv("CCCTERM_FONTSIZE") )
    {
        sscanf(getenv("CCCTERM_FONTSIZE"),"%d",&fontheight);
    }

    // a LOGFONT-ba irando ertekeket
    // a fenti kiserlettel allapitottam meg

         if( fontheight<=10 ) fontheight=-13;
    else if( fontheight<=11 ) fontheight=-15;
    else if( fontheight<=12 ) fontheight=-16;
    else if( fontheight<=14 ) fontheight=-19;
    else if( fontheight<=16 ) fontheight=-21;
    else if( fontheight<=18 ) fontheight=-24;
    else if( fontheight<=20 ) fontheight=-27;
    else if( fontheight<=24 ) fontheight=-32;
    else if( fontheight<=26 ) fontheight=-35;
    else if( fontheight<=28 ) fontheight=-37;
    else                      fontheight=-37;

    LOGFONT lf;
    strcpy(lf.lfFaceName,fontface);
    lf.lfHeight         = fontheight;
    lf.lfWidth          = 0;
    lf.lfEscapement     = 0;
    lf.lfOrientation    = 0;
    lf.lfWeight         = 400; // FW_NORMAL;
    lf.lfItalic         = 0;
    lf.lfUnderline      = 0;
    lf.lfStrikeOut      = 0;
    lf.lfCharSet        = 0;
    lf.lfOutPrecision   = 3;
    lf.lfClipPrecision  = 2;
    lf.lfQuality        = 1;
    lf.lfPitchAndFamily = 49;

    return CreateFontIndirect(&lf);
#endif
}
