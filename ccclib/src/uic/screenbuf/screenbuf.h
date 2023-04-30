
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

#ifndef _SCREENBUF_H_
#define _SCREENBUF_H_

#include <inttypes.h>

#undef getchar

#define DEFATTR 0x07

#if defined COMPILE_TERMINAL
  #define screencell          screencell4 
  #undef  screencell_term
#elif defined _CCC3_
  #define screencell          screencell4 
  #define screencell_term     screencell4
#elif defined _CCC2_
  #define screencell          screencell2 
  #define screencell_term     screencell4
#endif


// extended colorindex -> legacy colorindex
static char legacy[256]=
{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,4,4,4,4,12,2,6,8,4,4,12,2,8,6,6,6,14,2,2,6,6,6,14,2,2,6,6,6,14,10,10,14,14,14,14,1,5,8,4,4,12,3,8,8,12,12,12,8,8,8,8,12,12,2,10,8,6,6,14,2,10,10,6,14,14,10,10,10,14,14,14,1,8,5,5,5,13,8,8,8,8,12,12,3,8,8,12,12,12,3,8,10,6,7,14,3,10,10,7,14,14,11,10,10,14,14,14,1,1,5,5,5,13,1,9,8,5,5,13,3,8,9,5,7,13,3,3,3,7,7,12,3,3,7,7,7,15,11,11,11,10,15,14,1,1,5,5,5,13,1,9,9,5,13,13,3,9,9,7,13,13,3,3,7,7,7,15,3,11,11,7,7,15,11,11,11,15,15,15,9,9,13,13,13,13,9,9,9,13,13,13,11,9,9,13,13,13,11,11,11,9,15,13,11,11,11,15,15,15,11,11,11,11,15,15,0,0,0,0,0,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7}
;

#define LEGACY(x) legacy[255&(x)]


class screencell4{
  private:
    unsigned char low_char;
    unsigned char high_char;
    unsigned char low_attr;
    unsigned char high_attr;

  public:

    c_uint16_t getchar()
    {
        c_uint16_t c=0;
        c|=high_char;
        c=c<<8;
        c|=low_char;
        return c;
    }

    void setchar( c_uint16_t c )
    {
        low_char=0xff&c;
        high_char=0xff&(c>>8);
    }

    c_uint16_t getattr()
    {
        c_uint16_t a=0;
        a|=high_attr;
        a=a<<8;
        a|=low_attr;
        return a;
    }

    void setattr( c_uint16_t a )
    {
        low_attr=0xff&a;
        high_attr=0xff&(a>>8);
    }



    c_uint16_t get_fg()
    {
        return 255 & low_attr;
    }
    void set_fg(c_uint16_t fg)
    {
        low_attr=255 & fg;
    }

    c_uint16_t get_bg()
    {
        return 255 & high_attr;
    }
    void set_bg( c_uint16_t bg )
    {
        high_attr=255 & bg;
    }


}; //CCC3 (4 byteos) screencell


class screencell2{
  private:
    unsigned char low_char;
    unsigned char low_attr;

  public:

    c_uint16_t getchar()
    {
        c_uint16_t c=0;
        c|=low_char;
        return c;
    }

    void setchar( c_uint16_t c )
    {
        low_char=0xff&c;
    }

    c_uint16_t getattr()
    {
        c_uint16_t a=0;
        a|=low_attr;
        return a;
    }

    void setattr( c_uint16_t a )
    {
        low_attr=0xff&a;
    }


    c_uint16_t get_fg()
    {
        return 0x0f  & low_attr;
    }

    void set_fg(c_uint16_t fg)
    {
        low_attr=(0xf0 & low_attr) | LEGACY(fg);
    }

    c_uint16_t get_bg()
    {
        return (0xf0 & low_attr)>>4;
    }

    void set_bg( c_uint16_t bg )
    {
        low_attr=(0x0f & low_attr) | (LEGACY(bg)<<4);
    }


}; //CCC2 (2 byteos) screencell


class screenbuf{
  public:
  
    screencell *buffer;
  
    int sizex;
    int sizey;
    
    int uplef, uptop, uprig, upbot;

    unsigned short defattr;

    screenbuf(int x, int y);
    ~screenbuf();
    screencell *cell(int x, int y);
    void dump(const char *caption="SCREEN");
    void clear();
    void clearrect(int lef, int top, int rig, int bot);
    int getrect(int lef, int top, int rig, int bot, screencell *dest);
    int putrect(int lef, int top, int rig, int bot, screencell *src);

};

#endif
