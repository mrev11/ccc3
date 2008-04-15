
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

#ifndef _CCCGTK_H_
#define _CCCGTK_H_

#define stringn0(p)  ((p)?stringnb(p):string(L""))

namespace _nsp_gtk{

extern void push_gslist_c(GSList *list); // stack:  --- array
extern void push_gslist_c_freelist(GSList *list); // stack:  --- array
extern void push_gslist_c_freedata(GSList *list); // stack:  --- array
extern void push_gslist_c_freelist_freedata(GSList *list); // stack:  --- array

extern void push_gslist_p(GSList *list); // stack:  --- array
extern void push_gslist_p_freelist(GSList *list); // stack:  --- array
extern void push_gslist_p_freedata(GSList *list); // stack:  --- array
extern void push_gslist_p_freelist_freedata(GSList *list); // stack:  --- array


extern void push_glist_c(GList *list); // stack:  --- array
extern void push_glist_c_freelist(GList *list); // stack:  --- array
extern void push_glist_c_freedata(GList *list); // stack:  --- array
extern void push_glist_c_freelist_freedata(GList *list); // stack:  --- array

extern void push_glist_p(GList *list); // stack:  --- array
extern void push_glist_p_freelist(GList *list); // stack:  --- array
extern void push_glist_p_freedata(GList *list); // stack:  --- array
extern void push_glist_p_freelist_freedata(GList *list); // stack:  --- array


extern void *_parp_object(int paridx, VALUE*base, int argno);
extern char *_parc_utf8(int paridx, VALUE*base, int argno);
extern void _retc_utf8(const char *str, VALUE *base);
extern void _retclen_utf8(const char *str, int len, VALUE *base);


} //gtk

#undef  _parp
#define _parp(x)   _nsp_gtk::_parp_object(x,base,argno)

#define _parc_utf8(x)       (str2bin(base+x-1),_parb(x))
#define _retc_utf8(s)       (s==0?_retc(L""):_retcb(s))
#define _retclen_utf8(s,l)  (s==0?_retc(L""):_retcblen(s,l))



#endif //_CCCGTK_H_

