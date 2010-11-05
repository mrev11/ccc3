
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

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <cccapi.h>

//A classid<->slot cache kezelést szinkronizálni kell.
//
//Az xmethod modulban a különböző típusú metódus osztályokat
//egymástól függetlenül definiáltuk (kompatibilitási okokból),
//ez azonban nehezítette a karbantartást a kódismétlések miatt.
//Az xmethod2 modulban alkalmazzuk az öröklődést, a findslot-ot
//virtuálissá tesszük, és bevezetünk egy új adattagot (slothashcode),
//amivel az osztály<->metódus párosítást optimalizáljuk.
//
//A régi xmethod osztály bennmarad a könyvtárban, így a régi
//fordítású objectek változtatás nélkül futnak. Az új kódgenerálás
//a _method_ osztály helyett _method2_ osztályú metódusdefiníciókat
//csinál, ezek már az xmethod2-vel működnek. A kézzel írt C++
//modulokban sokáig megmaradhatnak a régi xmethod hivátkozások,
//ui. ezek újrafordításkor sem alakulnak át xmethod2 kóddá.


//----------------------------------------------------------------------
_method2_::_method2_(char *sname)
{
    classid=0;
    slotname=sname; 
    slothashcode=hashcode(sname);
    slot.type=TYPE_NIL;
    MUTEX_INIT(mutex);
};


_methods2_::_methods2_(char *sname, char *bname) : _method2_(sname)
{
    basename=bname; 
};


_methodc2_::_methodc2_(char *sname, char *bname) : _method2_(sname)
{
    basename=bname; 
};


_methodp2_::_methodp2_(char *sname, char *pname, char *bname) : _method2_(sname)
{
    prntname=pname; 
    basename=bname; 
};


//----------------------------------------------------------------------
_method2_::_method2_(const char *sname)
{
    classid=0;
    slotname=sname; 
    slothashcode=hashcode(sname);
    slot.type=TYPE_NIL;
    MUTEX_INIT(mutex);
};


_methods2_::_methods2_(const char *sname, const char *bname) : _method2_(sname)
{
    basename=bname; 
};


_methodc2_::_methodc2_(const char *sname, const char *bname) : _method2_(sname)
{
    basename=bname; 
};


_methodp2_::_methodp2_(const char *sname, const char *pname, const char *bname) : _method2_(sname)
{
    prntname=pname; 
    basename=bname; 
};


//----------------------------------------------------------------------
void _method2_::findslot(int clid)
{
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    number(clid);
    binary(slotname);
    number(slothashcode);
    _clp___findslot(3);  
    
    //Clipper szinten keresünk.
    //Ha nem talált, akkor ide már nem jön,
    //mert a hibát _clp___findslot() kezeli.
    //A mutex jelenleg éppen nincs lockolva, tehát, 
    //ha a hibát elkapják, a mutex szabad állapotban marad.
    //Ha talált, akkor a method blokkja,
    //vagy az attribútum indexe van a stacken.
    //Ezt a blokkot/indexet megőrizzük a slot memberben,
    //(VIGYáZAT) itt a blokkot a szemétgyűjtés nem tudja 
    //megtalálni, és csak amiatt nem takarítódik le, 
    //mert ugyanerre az objektumra a static aclass
    //tömbből is van hivatkozás.
    
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    classid=clid;
    slot=*TOP();
}

void _methods2_::findslot(int clid)
{
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    number(clid);
    binary(slotname);
    binary(basename);
    number(slothashcode);
    _clp___findslot_s(4);  
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    classid=clid;
    slot=*TOP();
}

void _methodc2_::findslot(int clid)
{
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    number(clid);
    binary(slotname);
    binary(basename);
    number(slothashcode);
    _clp___findslot_c(4);  
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    classid=clid;
    slot=*TOP();
}

void _methodp2_::findslot(int clid)
{
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    number(clid);
    binary(slotname);
    binary(prntname);
    binary(basename);
    number(slothashcode);
    _clp___findslot_p(5);  
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    classid=clid;
    slot=*TOP();
}
 
 
//----------------------------------------------------------------------
void _method2_::eval(int argno)
{
    //stack: Obj A1 A2... Aargno-1 --- retval
    
    VALUE *base=stack-argno;  //object
    
    if( base->type!=TYPE_OBJECT )
    {
        error_obj(slotname,base,argno);
    }

    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    if( base->data.object.subtype!=classid )
    {
        findslot(base->data.object.subtype); //virtual!

        //Ha findslot sikertelen, 
        //akkor Clipper runtime error keletkezik,
        //és ide már nem jön a vezérlés.
    }
    else
    {
        push(&slot);
    }
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();

    
    //Ha a TOP-ban szám van, akkor az egy attribútum indexe.
    //Ha a TOP-ban kódblokk van, akkor azt ki kell értékelni.

    if( TOP()->type==TYPE_NUMBER )
    {
        //attribútum kiolvasás/felülírás
    
        unsigned int len=OBJECTLEN(base);
        unsigned int idx=(int)TOP()->data.number;

        if( (idx<1) || (len<idx) )
        {
            error_siz("_method_::eval",base,argno);
        }
    
        VALUE *v=OBJECTPTR(base)+idx-1;

        if( argno>1 ) //beírás
        {
            *v=*(base+1);
        }

        *base=*v;
        stack=base+1;
    }
    
    else if( TOP()->type==TYPE_BLOCK )
    {
        //method végrehajtás
        //a stacket eggyel feljebb kell hozni,
        //hogy a kódblokkot betehessük alulra
        
        VALUE blk=*TOP();
        int i;
        for( i=argno; i>0; i-- )
        {
            *(base+i)=*(base+i-1);
        }
        
        //ha most a base-be bemásoljuk a kódblokkot,
        //akkor a verem éppen olyan, mint _clp_eval-nál
        
        *base=blk;
        base->data.block.code(argno+1);
    }

    else
    {
        error_gen(L"invalid slot type","_method_::eval",base,argno);
    }
}

//----------------------------------------------------------------------

