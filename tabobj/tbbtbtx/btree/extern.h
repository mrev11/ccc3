
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

//belso fuggvenyek

  int    __bt_free         (BTREE*, PAGE*);
  PAGE  *__bt_new0         (BTREE*, pgno_t*, pgno_t*);
  PAGE  *__bt_new          (BTREE*, pgno_t*, pgno_t*);
  EPG   *__bt_search       (BTREE*, DBT*, int*);
  void   __bt_setcur       (BTREE*, pgno_t, indx_t, DBT*);
  DBT    __bt_getkey       (BTREE*, EPG*);
  int    __bt_split        (BTREE*, PAGE*, DBT*, size_t, indx_t, EPGNO*);
  int    __bt_cmp          (BTREE*, DBT*, EPG*);
  void   __bt_print_header (BTREE*, char*);
  void   __bt_print_free   (BTREE*);
  int    __bt_defcmp       (DBT*, DBT*);
  void   __bt_error        (const char*);
  void   __bt_swapin       (PAGE*);
  void   __bt_swapout      (PAGE*);
 

//public btree interface

  BTREE *__bt_open           (int, int, int);
  int    __bt_close          (BTREE*);
  int    __bt_delete         (BTREE*, DBT*);
  int    __bt_fd             (BTREE*);
  int    __bt_pagesize       (BTREE*);
  int    __bt_put            (BTREE*, DBT*, int);
  int    __bt_seq            (BTREE*, DBT*, int);

  int    __bt_creord         (BTREE*, char*);
  int    __bt_setord         (BTREE*, char*);
  int    __bt_delord         (BTREE*, char*);
  int    __bt_renord         (BTREE*, char*, char*);
 
  RECPOS __bt_addresource    (BTREE*, DBT*, indx_t);
  RECPOS __bt_append         (BTREE*, DBT*, int*);
  int    __bt_rewrite        (BTREE*, DBT*, RECPOS*);
  int    __bt_read           (BTREE*, DBT*, RECPOS*);
  int    __bt_read1          (BTREE*, DBT*, pgno_t, indx_t);

  void   __bt_pagelock       (BTREE*, pgno_t, int);
  void   __bt_pageunlock     (BTREE*, pgno_t);
  int    __bt_header_read    (BTREE*, int);
  int    __bt_header_write   (BTREE*);
  int    __bt_header_sync    (BTREE*);
  int    __bt_header_release (BTREE*);
  int    __bt_lastrec        (BTREE*);
  

//byte order functions (swap.c)

  void       store16(char *buf, u_int32_t n);
  void       store32(char *buf, u_int32_t n);
  u_int32_t  load16(char *buf);
  u_int32_t  load32(char *buf);
 
