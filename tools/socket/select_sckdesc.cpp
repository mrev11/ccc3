
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

//CCC select interfész UNIX-ra és Win32-re
//Vermes M., 2001.06.03.

#include <sckcompat.h> 
#include <cccapi.h> 
 

//---------------------------------------------------------------------------
void _clp_select_sckdesc(int argno)  
{
    //par1: olvasásra váró fd-k (array, opcionális)
    //par2: írásra váró fd-k (array, opcionális)
    //par3: kivételes fd-k (array, opcionális)
    //par4: várakozási idő msec (number, NIL=végtelen)
    
    //az array paraméterek módosulnak, 
    //csak az írható/olvasható/kivételes fd-k maradnak benne,
    //visszatérés: a feltételt teljesítő fd-k száma
    
    //Példák:
    //
    //1. várakozás egyetlen socket olvasására
    //
    //     select({s},,,1000)
    //
    //  1 sec-ig vár arra, hogy az s socket olvasható legyen,
    //  ha ezalatt jön adat, akkor azonnal visszatér 1 értékkel,
    //  ha nem jön adat, akkor csak 1 sec múlva, 0 értékkel.
    //
    //2. várakozás több socket olvashatóságára
    //
    //     sck:={s1,s2,s3}
    //     select(sck)
    //
    //  Addig vár, amíg az sck socketei közül valamelyik olvasható 
    //  nem lesz, amikor ez bekövetkezik, azonnal visszatér az olvasható 
    //  socketek számával. Az sck array módosul, csak azokat a socketeket 
    //  fogja tartalmazni, amik (blokkolás nélkül) olvashatók.
    //
    //3. várakozás megadott ideig
    //
    //     #xtranslate sleep(<wtime>)  =>  select(,,,<wtime>)
    //
    //  Ez használható volna a sleep-re, ha az nem volna lényegében 
    //  ugyanígy, de függvényként implementálva az alapkönyvtárban.
    
 
    //Megjegyzés:
    //Ha a távoli fél lezár egy socketet, az NEM a kivételes
    //socketek között, hanem az olvasható socketek halmazában
    //jelenik meg, de ezután az olvasás hibás lesz. Úgy látszik,
    //ez a lezáródó socketek normális sorsa.


    CCC_PROLOG("select_sckdesc",4);

    int i,s,smax=0;
    int set;
    fd_set fd[3];
   
    for( set=0; set<3; set++ )
    {
        FD_ZERO( &fd[set] ); 
        
        if( !ISNIL( set+1 ) )
        {
            for(i=0; i<_paralen(set+1); i++)
            {
                VALUE *v=_parax(set+1,i);
        
                if( v->type!=TYPE_NUMBER )
                {
                    ARGERROR();
                }
                s=D2INT(v->data.number);

                if( s>smax )
                {
                    smax=s;
                }

                FD_SET(s,&fd[set]);
            }
        }
    }        
 
    struct timeval tv;
    if( !ISNIL(4) )
    {
        long t=_parnu(4); //várakozási idő (msec)
        tv.tv_sec=t/1000;
        tv.tv_usec=(t%1000)*1000;   
    }

    int result=select(smax+1,&fd[0],&fd[1],&fd[2],ISNUMBER(4)?&tv:NULL);

    for( set=0; set<3; set++ )
    {
        if( ISARRAY(set+1) )
        {
            push(base+set);number(0);_clp_asize(2);pop(); //kiürítve

            for( s=0; s<=smax; s++ )
            {
                if( FD_ISSET(s,&fd[set]) )
                {
                    push(base+set);number(s);_clp_aadd(2);pop(); //berakva
                }
            }
        }
    }
    _retni( result );
    
    CCC_EPILOG();
}    

//---------------------------------------------------------------------------


