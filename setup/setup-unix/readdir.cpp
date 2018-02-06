
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

#include <dirent.h>
#include <string.h>
#include <cccapi.h>


#define ISREFNIL(i) (ISREF(i) && PARPTR(i)->data.vref->value.type==TYPE_NIL)
#define ISREFPTR(i) (ISREF(i) && PARPTR(i)->data.vref->value.type==TYPE_POINTER)



//-----------------------------------------------------------------------
struct __opdirstate
{
    DIR *dirstream;
    int binopt;

    __opdirstate(char *dirname, int flag)
    {
        this->dirstream=opendir(dirname);  //0 on error
        this->binopt=flag;
    }

    ~__opdirstate()
    {
        if(this->dirstream)
        {
            closedir(this->dirstream);
        }
    }
};



//-----------------------------------------------------------------------
void _clp____opendir(int argno)
{
    CCC_PROLOG("__opendir",3);

    //1. @handle
    //2. dirname
    //3. binopt
    
    if( !ISREFNIL(1) )
    {
        ARGERROR();
    }
    str2bin(base+1);
    char *dirname=_parb(2);
    int binopt=ISNIL(3)?0:_parl(3);

    __opdirstate *ods=new __opdirstate(dirname,binopt);
    if( !ods->dirstream )
    {
        delete ods;
        _retl(0);
    }
    else
    {
        pointer(ods);
        assign(base);
        _retl(1);
    }
    CCC_EPILOG();
}

//-----------------------------------------------------------------------
void _clp____readdir(int argno)
{
    CCC_PROLOG("__readdir",1);

    if( ISREFNIL(1) )
    {
         //already closed
        _ret();
    }
    else if( ISREFPTR(1) )
    {
        __opdirstate *ods=(__opdirstate*)REFVALUE(1)->data.pointer;
        
        struct dirent *de=readdir(ods->dirstream);
        if( de==0)
        {
            //close
            delete ods;
            PUSHNIL(); assign(base); pop();
            _ret();
        }
        else if( ods->binopt )
        {
            _retb(de->d_name); //binary name
        }
        else
        {
            _retcb(de->d_name); //character name
        }
    }
    else
    {
        ARGERROR();
    }
    CCC_EPILOG();
}


//-----------------------------------------------------------------------
void _clp____closedir(int argno)
{
    CCC_PROLOG("__closedir",1);
    if( ISREFNIL(1) )
    {
        //already closed
        _ret();
    }
    else if( ISREFPTR(1) )
    {
        //close
        __opdirstate *ods=(__opdirstate*)REFVALUE(1)->data.pointer;
        delete ods;
        PUSHNIL(); assign(base); pop();
        _ret();
    }
    else
    {
        ARGERROR();
    }
    CCC_EPILOG();
}

//-----------------------------------------------------------------------
void _clp____readlink(int argno)
{
    CCC_PROLOG("___readlink",2);
    str2bin(base);
    char *pathname=_parb(1);
    int binopt=ISNIL(2)?0:_parl(2);
    
    char buf[1024];
    ssize_t result=readlink(pathname,buf,sizeof(buf));

    if( result>0 )
    {
        if( binopt )
        {
            _retblen(buf,result);
        }
        else
        {
            _retcblen(buf,result);
        }
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}


//-----------------------------------------------------------------------



