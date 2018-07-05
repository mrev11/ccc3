
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

//CCC select interfesz UNIX-ra es Win32-re
//Vermes M., 2001.06.03.

#include <sckcompat.h> 
#include <cccapi.h> 
 

//---------------------------------------------------------------------------
void _clp_select_sckdesc(int argno)  
{
    //par1: olvasasra varo fd-k (array, opcionalis)
    //par2: irasra varo fd-k (array, opcionalis)
    //par3: kiveteles fd-k (array, opcionalis)
    //par4: varakozasi ido msec (number, NIL=vegtelen)
    
    //az array parameterek modosulnak, 
    //csak az irhato/olvashato/kiveteles fd-k maradnak benne,
    //visszateres: a feltetelt teljesito fd-k szama
    
    //Peldak:
    //
    //1. varakozas egyetlen socket olvasasara
    //
    //     select({s},,,1000)
    //
    //  1 sec-ig var arra, hogy az s socket olvashato legyen,
    //  ha ezalatt jon adat, akkor azonnal visszater 1 ertekkel,
    //  ha nem jon adat, akkor csak 1 sec mulva, 0 ertekkel.
    //
    //2. varakozas tobb socket olvashatosagara
    //
    //     sck:={s1,s2,s3}
    //     select(sck)
    //
    //  Addig var, amig az sck socketei kozul valamelyik olvashato 
    //  nem lesz, amikor ez bekovetkezik, azonnal visszater az olvashato 
    //  socketek szamaval. Az sck array modosul, csak azokat a socketeket 
    //  fogja tartalmazni, amik (blokkolas nelkul) olvashatok.
    //
    //3. varakozas megadott ideig
    //
    //     #xtranslate sleep(<wtime>)  =>  select(,,,<wtime>)
    //
    //  Ez hasznalhato volna a sleep-re, ha az nem volna lenyegeben 
    //  ugyanigy, de fuggvenykent implementalva az alapkonyvtarban.
    
 
    //Megjegyzes:
    //Ha a tavoli fel lezar egy socketet, az NEM a kiveteles
    //socketek kozott, hanem az olvashato socketek halmazaban
    //jelenik meg, de ezutan az olvasas hibas lesz. Ugy latszik,
    //ez a lezarodo socketek normalis sorsa.


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
        long t=_parnu(4); //varakozasi ido (msec)
        tv.tv_sec=t/1000;
        tv.tv_usec=(t%1000)*1000;   
    }

    int result=select(smax+1,&fd[0],&fd[1],&fd[2],ISNUMBER(4)?&tv:NULL);

    for( set=0; set<3; set++ )
    {
        if( ISARRAY(set+1) )
        {
            push(base+set);number(0);_clp_asize(2);pop(); //kiuritve

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


