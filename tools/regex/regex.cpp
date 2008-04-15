
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

#include <sys/types.h>
#include <pcreposix.h>
#include <regex.ch>
#include <cccapi.h>

DEFINE_METHOD(operation);
DEFINE_METHOD(description);
DEFINE_METHOD(subsystem);
DEFINE_METHOD(subcode);

extern void _clp_invalidformaterrornew(int);

namespace _nsp_regex{

//----------------------------------------------------------------------------
void _clp_regcomp(int argno) //regex.regcomp(regex,flags) -> rx
{
    CCC_PROLOG("regex.regcomp",2);
    regex_t *preg=(regex_t*)malloc(sizeof(regex_t));
    const char *regex=_parb(1);
    int flags=ISNIL(2)?REGEX_EXTENDED:_parni(2); 

    int cflags=0;
    if( flags & REGEX_EXTENDED ) cflags|=REG_EXTENDED;
    if( flags & REGEX_NEWLINE  ) cflags|=REG_NEWLINE;
    if( flags & REGEX_NOSUB    ) cflags|=REG_NOSUB;
    if( flags & REGEX_ICASE    ) cflags|=REG_ICASE;

    int errcode=regcomp(preg,regex,cflags);
    if( errcode==0 )
    {
        pointer(preg);
    }
    else
    {
        char errbuf[1024];
        size_t len=regerror(errcode,preg,errbuf,sizeof(errbuf));
        regfree(preg);
        free(preg);
        _clp_invalidformaterrornew(0);
        dup(); string(L"regex.regcomp");_o_method_operation.eval(2);pop(); 
        dup(); stringsb(errbuf,len);_o_method_description.eval(2);pop();
        dup(); string(L"regex");_o_method_subsystem.eval(2);pop(); 
        dup(); number(errcode);_o_method_subcode.eval(2);pop();
        _clp_break(1);
    }
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_regexec(int argno) //regex.regexec(rx,text,offs,nmatch,flags)

//  -> NIL, ha nincs találat
//  -> {}, ha REG_NOSUB be van állítva
//  -> {offs,length}, ha nmatch==NIL/1
//  -> {{offs,length},...}, ha nmatch>1

{
    CCC_PROLOG("regex.regexec",5);
    regex_t *preg=(regex_t*)_parp(1);
    const char *text=_parb(2);
    int offs=ISNIL(3)?1:min(max(1,_parni(3)),(int)_parblen(2));
    size_t nmatch=ISNIL(4)?1:min(max(1,_parni(4)),128);
    int flags=ISNIL(5)?0:_parni(5); 

    int eflags=0; 
    if( flags & REGEX_NOTBOL ) eflags|=REG_NOTBOL;
    if( flags & REGEX_NOTEOL ) eflags|=REG_NOTEOL;
    
    regmatch_t *pmatch=(regmatch_t*)malloc(sizeof(regmatch_t)*nmatch);
    pmatch[0].rm_so=(regoff_t)-1;
    int errcode=regexec(preg,text+offs-1,nmatch,pmatch,eflags);
    if( errcode==0 )
    {
        size_t n=0;
        while( n<nmatch && pmatch[n].rm_so!=(regoff_t)-1 )
        {
            number(offs+pmatch[n].rm_so); //1 based offset
            number(pmatch[n].rm_eo-pmatch[n].rm_so); //length
            array(2);
            n++;
        }
        if( nmatch>1 )
        {
            array(n);
        }
    }
    else if( errcode==REG_NOMATCH )
    {
        PUSHNIL();
    }
    else
    {
        char errbuf[1024];
        size_t len=regerror(errcode,preg,errbuf,sizeof(errbuf));
        _clp_invalidformaterrornew(0);
        dup(); string(L"regex.regexec");_o_method_operation.eval(2);pop(); 
        dup(); stringsb(errbuf,len);_o_method_description.eval(2);pop();
        dup(); string(L"regex");_o_method_subsystem.eval(2);pop(); 
        dup(); number(errcode);_o_method_subcode.eval(2);pop();
        _clp_break(1);
    }
    free(pmatch);
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_regerror(int argno) //regex.regerror(rx,errcode) -> errtext
{
    CCC_PROLOG("regex.regerror",2);
    regex_t *preg=(regex_t*)_parp(1);
    int errcode=_parni(2);
    char errbuf[1024];
    size_t len=regerror(errcode,preg,errbuf,sizeof(errbuf));
    stringsb(errbuf,len);
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_regfree(int argno) //regex.regfree(rx) -> NIL
{
    CCC_PROLOG("regex.regfree",1);
    regex_t *preg=(regex_t*)(ISNIL(1)?(void*)0:_parp(1));
    if( preg )
    {
        regfree(preg);
        free(preg);
    }
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------

}
