
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

#ifndef _XMETHOD4_H_
#define _XMETHOD4_H_ 

#ifndef SLOTITEM
#define SLOTITEM
struct slotitem 
{
    int   classid;
    VALUE slotvalue; //codeblock/attrindex
};
#endif

typedef void CLASSID(int argno);
 
//----------------------------------------------------------------------------
class _method4_
{
  protected:

    virtual void findslot(int clid);

    const char *slotname;
    unsigned slothashcode;
    unsigned slotbuffersize;
    slotitem *slotbuffer;

    MUTEX_DECLARE(mutex);

  public:

    void eval(int argno);
    _method4_(const char *sname);
    virtual ~_method4_(){};
};


//----------------------------------------------------------------------------
class _method4s_ : public _method4_
{
  protected:

    virtual void findslot(int clid);
    CLASSID *baseid;

  public:

    _method4s_(const char *sname, CLASSID *bid);
};


//----------------------------------------------------------------------------
class _method4c_ : public _method4_
{
  protected:

    virtual void findslot(int clid);
    CLASSID *baseid;

  public:

    _method4c_(const char *sname, CLASSID *bid);
};


//----------------------------------------------------------------------------
class _method4p_ : public _method4_
{
  protected:

    virtual void findslot(int clid);
    CLASSID *prntid;
    CLASSID *baseid;

  public:

    _method4p_(const char *sname, CLASSID *pid, CLASSID *bid);
};
 
//----------------------------------------------------------------------------
#endif


