
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

#include <string.h>
#include <wchar.h>
#include <cccapi.h>
 
DEFINE_METHOD(args);
DEFINE_METHOD(description);
DEFINE_METHOD(operation);

//------------------------------------------------------------------------
void error_gen(const CHAR *description, const char *operation, VALUE *base, int argno)
{
    argno=min(argno,stack-base);

    _clp_errornew(0);

    DUP();
    stringn(description);
    _o_method_description.eval(2);
    POP();

    DUP();
    stringnb(operation);
    _o_method_operation.eval(2);
    POP();

    DUP();
    for(int i=0; i<argno; i++)
    {
        PUSH(base+i);
    }
    array(argno);
    _o_method_args.eval(2);
    POP();

    _clp_break(1);
}

//------------------------------------------------------------------------
void error_arg(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("argument error"),operation,base,argno);
}

//------------------------------------------------------------------------
void error_idx(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("index violation"),operation,base,argno);
}

//------------------------------------------------------------------------
void error_arr(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("bad array indexing"),operation,base,argno);
}

//------------------------------------------------------------------------
void error_obj(const char *operation, VALUE *base, int argno)
{
    char buf[128];
    strcpy(buf,"message sending - ");
    strncat(buf,operation,100);
    error_gen(CHRLIT("not an object"),buf,base,argno);
}

//------------------------------------------------------------------------
void error_met(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("no exported method"),operation,base,argno);
}

//------------------------------------------------------------------------
void error_div(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("zero division"),operation,base,argno);
}

//------------------------------------------------------------------------
void error_neg(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("negative argument"),operation,base,argno);
}

//------------------------------------------------------------------------
void error_blk(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("not a codeblock"),operation,base,argno);
}

//------------------------------------------------------------------------
void error_cln(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("character variable too long"),operation,base,argno);
}

//------------------------------------------------------------------------
void error_bln(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("binary variable too long"),operation,base,argno);
}

//------------------------------------------------------------------------
void error_nul(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("null pointer"),operation,base,argno);
}

//------------------------------------------------------------------------
void error_wcr(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("invalid window handle"),operation,base,argno);
}

//------------------------------------------------------------------------
void error_siz(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("size error"),operation,base,argno);
}


//------------------------------------------------------------------------
void error_cnd(const char *operation, VALUE *base, int argno)
{
    error_gen(CHRLIT("conditional error"),operation,base,argno);
}

//------------------------------------------------------------------------

