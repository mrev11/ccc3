
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

#ifndef _TERMAPI_H_
#define _TERMAPI_H_

#include <screenbuf.h>

extern void initialize_terminal();

extern int  maxcol();
extern int  maxrow();
extern int  wherex();
extern int  wherey();
extern void gotoxy(int x, int y);
extern void setcursoron();
extern void setcursoroff();
extern void getrect(int lef, int top, int rig, int bot, screencell *destin);
extern void putrect(int lef, int top, int rig, int bot, screencell *source);
extern int  getkey(int timeout);
extern void setcaption(char *cap, int len);
extern void getwsize(int *sizex,int *sizey);
extern void setwsize(int sizex,int sizey);
extern void dispbegin();
extern void dispend();
 
#endif
