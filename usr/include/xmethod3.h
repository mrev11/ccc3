
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

#ifndef _XMETHOD3_H_
#define _XMETHOD3_H_ 

typedef void CLASSID(int argno);
 
//----------------------------------------------------------------------------
class _method3_
{
  protected:

    virtual void findslot(int clid);

    int classid;
    const char *slotname;
    unsigned slothashcode;
    VALUE slot;

    MUTEX_DECLARE(mutex);

  public:

    void eval(int argno);
    _method3_(const char *sname);
    virtual ~_method3_(){};
};


//----------------------------------------------------------------------------
class _method3s_ : public _method3_
{
  protected:

    virtual void findslot(int clid);
    CLASSID *baseid;

  public:

    _method3s_(const char *sname, CLASSID *bid);
};


//----------------------------------------------------------------------------
class _method3c_ : public _method3_
{
  protected:

    virtual void findslot(int clid);
    CLASSID *baseid;

  public:

    _method3c_(const char *sname, CLASSID *bid);
};


//----------------------------------------------------------------------------
class _method3p_ : public _method3_
{
  protected:

    virtual void findslot(int clid);
    CLASSID *prntid;
    CLASSID *baseid;

  public:

    _method3p_(const char *sname, CLASSID *pid, CLASSID *bid);
};
 
//----------------------------------------------------------------------------
#endif


