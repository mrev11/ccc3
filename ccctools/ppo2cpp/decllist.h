
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

extern void  fundecl_ini(void);
extern void  fundecl_setalias(char*name, const char*alias);
extern int   fundecl_using(char *fun, char*nsp);
extern void  fundecl_clpdef(char *fun,int stflag);
extern char *fundecl_clpcall(const char *fun);
extern void  fundecl_codeblock(const char *fun,int cnt);
extern void  fundecl_list(void);
extern void  namespace_begin(char*,FILE*);
extern void  namespace_end(char*,FILE*);

extern void flddecl_ini(void);
extern void flddecl_insert(char *text);
extern void flddecl_list(void);

extern void metdecl_ini(void);
extern void metdecl_insert(const char *slot, const char *prnt, const char*base);
extern void metdecl_list(void);

