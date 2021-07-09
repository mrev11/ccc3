
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

#ifndef _CCCEXT1_H_
#define _CCCEXT1_H_

//power.obj:
extern void power(void);

//gettick.obj:
extern unsigned gettickcount(void);

//errorgen.obj:
extern void error_gen(const wchar_t*,const char*,VALUE*,int);
extern void error_arg(const char*,VALUE*,int);
extern void error_arr(const char*,VALUE*,int);
extern void error_blk(const char*,VALUE*,int);
extern void error_cln(const char*,VALUE*,int);
extern void error_bln(const char*,VALUE*,int);
extern void error_nul(const char*,VALUE*,int);
extern void error_div(const char*,VALUE*,int);
extern void error_idx(const char*,VALUE*,int);
extern void error_met(const char*,VALUE*,int);
extern void error_neg(const char*,VALUE*,int);
extern void error_obj(const char*,VALUE*,int);
extern void error_siz(const char*,VALUE*,int);
extern void error_wcr(const char*,VALUE*,int);

//color.obj:
extern int gettextattr(void);
extern void setcoloridx(int);

//variablex.obj:
extern void vartab_setsize(struct VARTAB_SETSIZE*);

//transform.obj:
extern void trn_number(VALUE*,VALUE*);
extern void trn_string(VALUE*,VALUE*);
extern void trn_date(VALUE*,VALUE*);
extern void trn_flag(VALUE*,VALUE*);

//varprint.obj:
extern void stack_print(void);
extern void var_print(VALUE*);
extern void debug(const char*);

//break.obj:
extern void begseqpop_ret(void);
extern void begseqpop_exit(void);
extern void begseqpop_loop(void);

//binary.obj:
extern char *binaryl(unsigned long);
extern void binary(const char*);
extern void binaryn(const char*);
extern void binarys(const char*,unsigned long);
extern void binaryx(const char*);

//push.obj:
extern void push(VALUE*);
extern void push_blkenv(VALUE*);
extern void push_symbol(VALUE*);
extern void push_symbol_ref(VALUE*);
extern void dup(void);
extern void swap(void);
extern void pop(void);
extern void block(void(*)(int),int);
extern VALUE *blkenv(VALUE*);
extern void assign(VALUE*);
extern void assign2(VALUE*);
extern void number(double);
extern void date(long);
extern void logical(int);
extern void pointer(void*);
extern VALUE prototype_object(void);

//sckutil.obj:
extern int socket_new(void);
extern int socket_bind(int,const char*,int);
extern int socket_read(int,void*,int,int);
extern int socket_close(int);
extern int socket_error(void);
extern int socket_write(int,void*,int);
extern int client_socket(const char*,int);
extern int socket_accept(int);
extern int socket_listen(int);
extern int socket_listen(int,int);
extern int socket_connect(int,const char*,int);
extern int socket_available(int);
extern int socket_setoption(int,int,int);
extern int server_socket_new(const char*,int);
extern int server_socket_new(const char*,int,int);
extern int server_socket_accept(int);

//hashcode.obj:
extern unsigned hashcode(const char*);
extern unsigned hashcode(const wchar_t*);

//pushcall.obj:
extern void push_call(const char*,VALUE*);

//equalto.obj:
extern void gt(void);
extern void lt(void);
extern void eqeq(void);
extern void gteq(void);
extern void lteq(void);
extern void neeq(void);
extern void topnot(void);
extern void ss(void);
extern int  flag(void);
extern int  greaterthan(void);
extern int  equalto(void);
extern int  lessthan(void);
extern int  notequal(void);

//string.obj:
extern void string(const wchar_t*);
extern void stringn(const wchar_t*);
extern void strings(const wchar_t*,unsigned long);
extern void stringnb(const char*);
extern void stringsb(const char*,unsigned long);
extern wchar_t* stringl(unsigned long);

//utf8conv.obj:
extern unsigned utf8_to_ucs(const char *utf8, unsigned *ucs);
extern unsigned ucs_to_utf8(unsigned ucs, char*utf8);
extern char *wchar_to_utf8(wchar_t const *wstr, unsigned wlen, unsigned *reslen);
extern wchar_t *utf8_to_wchar(char const *utf8, unsigned blen, unsigned *reslen);

//array.obj:
extern VALUE* idxl(void); //obsolete
extern VALUE* idxxl(void);
extern void idxr(void);
extern void array(int);
extern VALUE* idxl0(double); //obsolete
extern VALUE* idxxl0(double);
extern void idxr0(double);
extern void idxr0nil(double);
extern VALUE* array0(int);

//slice.obj:
extern void slice(void);
extern void sliceright(void);
extern void sliceleft(void);

//add.obj:
extern int  sign(void);
extern void add(void);
extern void div(void);
extern void mul(void);
extern void sub(void);
extern void addneg(double);
extern void addnum(double);
extern void modulo(void);
extern void mulnum(double);
extern void signneg(void);
extern void signpos(void);

//fileconv.obj:
extern void convertfspec2nativeformat(VALUE*);

//str2bin.obj:
extern void bin2str(VALUE*);
extern void str2bin(VALUE*);

//variable.obj:
extern void vartab_ini(void);
extern void vartab_lock(void);
extern void vartab_lock0(void);
extern void vartab_unlock(void);
extern void vartab_unlock0(void);
extern void vartab_rebuild(void);
extern char *newBinary(unsigned);
extern wchar_t *newChar(unsigned);
extern VALUE* newValue(unsigned);
extern void deleteValue(VALUE*);
extern OREF* oref_new(void);
extern VREF* vref_new(void);
extern void valuemove(VALUE*,VALUE*,int);

//dtos.obj:
extern long stod(const char*);
extern long stod(const wchar_t*);

//nlstext.obj:
extern const wchar_t *nls_text(const wchar_t*);

//signals.obj:
extern int signal_send(int,int);
extern int signal_raise(int);
extern void setup_signal_handlers(void);

#endif //_CCCEXT1_H_
