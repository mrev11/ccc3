
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

/*	gl.h

	GL to OpenGL translator.
	If you include this, you might be able to port old GL programs.
	There are also much better emulators available on the net.

*/

#include <FL/gl.h>
#include "gl_draw.H"

inline void clear() {glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);}
#define RGBcolor(r,g,b) glColor3ub(r,g,b)
#define bgnline() glBegin(GL_LINE_STRIP)
#define bgnpolygon() glBegin(GL_POLYGON)
#define bgnclosedline() glBegin(GL_LINE_LOOP)
#define endline() glEnd()
#define endpolygon() glEnd()
#define endclosedline() glEnd()
#define v2f(v) glVertex2fv(v)
#define v2s(v) glVertex2sv(v)
#define cmov(x,y,z) glRasterPos3f(x,y,z)
#define charstr(s) gl_draw(s)
#define fmprstr(s) gl_draw(s)
typedef float Matrix[4][4];
inline void pushmatrix() {glPushMatrix();}
inline void popmatrix() {glPopMatrix();}
inline void multmatrix(Matrix m) {glMultMatrixf((float *)m);}
inline void color(int n) {glIndexi(n);}
inline void rect(int x,int y,int r,int t) {gl_rect(x,y,r-x,t-y);}
inline void rectf(int x,int y,int r,int t) {glRectf(x,y,r+1,t+1);}
inline void recti(int x,int y,int r,int t) {gl_rect(x,y,r-x,t-y);}
inline void rectfi(int x,int y,int r,int t) {glRecti(x,y,r+1,t+1);}
inline void rects(int x,int y,int r,int t) {gl_rect(x,y,r-x,t-y);}
inline void rectfs(int x,int y,int r,int t) {glRects(x,y,r+1,t+1);}
