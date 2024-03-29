
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

#define MPOOL_DIRTY 1



typedef struct 
{
  int       pagesize;
  int       fd; 
  int       count;
  void      (*pgin)(void*);
  void      (*pgout)(void*);
  int       cryptflg;
  unsigned  salt;
} MPOOL;
 

extern MPOOL  * mpool_open(int fd, int pagesize);
extern int      mpool_close(MPOOL *mp);
extern int      mpool_count(MPOOL *mp, const char*msg);
extern void     mpool_dump(MPOOL *mp, void *page);
extern void   * mpool_new(MPOOL *mp, pgno_t *pgnoaddr);
extern void   * mpool_get(MPOOL *mp, pgno_t pgno);
extern int      mpool_put(MPOOL *mp, void *page, int dirty);
extern void     mpool_encrypt(MPOOL *mp, pgno_t pgno, char *buf);
extern void     mpool_decrypt(MPOOL *mp, pgno_t pgno, char *buf);

extern unsigned crc32(void*,int);

#define CRCPG(p,s) crc32(((char*)p)+4,s-4) // 0-1-2-3 byteok kihagyva

