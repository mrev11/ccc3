
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

#ifndef __PARSENODE_H__
#define __PARSENODE_H__

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#define SYM_LOCAL     0x010000
#define SYM_GLOBSTAT  0x020000
#define SYM_LOCSTAT   0x040000
#define SYM_BLKARG    0x080000
#define SYM_BLKLOC    0x100000
#define SYM_BLKSTAT   0x200000
 
 
struct parsenode {

    static int cnt_constructor;
    static int cnt_destructor;
    static parsenode *start_node;
    static parsenode *last_node;
    static void walk();
 
    int nodeid;                         //egyedi azonosító/label
    int tokenid;                        //term: tokenid>0, nemterm: tokenid==0
    const char *text;                   //term: a token szövege, nemterm: szabály
    int (*codegen)(parsenode*,void*);   //kódgeneráló függvény
    int (*outsource)(parsenode*,void*); //forrásszöveg kiírása
    int lineno;                         //sor, amiben a token volt
    int cargo;                          //változók offsete a stacken/listák hossza
    parsenode **right;                  //a szabály jobboldala

    parsenode *next;                    //lista kapcsoló
    parsenode *prev;                    //lista kapcsoló
 
    parsenode();
    ~parsenode();
    parsenode *token(int id,char *txt,int lineno);
    parsenode *rule(int rlen,...);
    void print(const char*prompt="");
    void tprint(int indent=0);
};
 
#endif
