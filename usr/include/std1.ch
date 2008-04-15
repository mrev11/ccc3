
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

#ifndef _SET_CH
#include "set.ch"
#endif

//-----------------------------------------------------------------------
//compatibility
//-----------------------------------------------------------------------
 
#xtranslate end case    => endcase
#xtranslate end while   => endwhile
#xtranslate end do      => enddo
#xtranslate end if      => endif
#xtranslate end for     => endfor

//-----------------------------------------------------------------------
//date
//-----------------------------------------------------------------------
 
#command SET CENTURY <x:ON,OFF,&>       => __SetCentury( <(x)> )
#command SET CENTURY (<x>)              => __SetCentury( <x> )
#command SET EPOCH TO <year>            => Set( _SET_EPOCH, <year> )
#command SET DATE FORMAT [TO] <c>       => Set( _SET_DATEFORMAT, <c> )

#define  _DFSET(x, y)  Set( _SET_DATEFORMAT, if(__SetCentury(), x, y) )

#command SET DATE [TO] AMERICAN         => _DFSET( "mm/dd/yyyy", "mm/dd/yy" )
#command SET DATE [TO] ANSI             => _DFSET( "yyyy.mm.dd", "yy.mm.dd" )
#command SET DATE [TO] BRITISH          => _DFSET( "dd/mm/yyyy", "dd/mm/yy" )
#command SET DATE [TO] FRENCH           => _DFSET( "dd/mm/yyyy", "dd/mm/yy" )
#command SET DATE [TO] GERMAN           => _DFSET( "dd.mm.yyyy", "dd.mm.yy" )
#command SET DATE [TO] ITALIAN          => _DFSET( "dd-mm-yyyy", "dd-mm-yy" )
#command SET DATE [TO] JAPANESE         => _DFSET( "yyyy/mm/dd", "yy/mm/dd" )
#command SET DATE [TO] USA              => _DFSET( "mm-dd-yyyy", "mm-dd-yy" )


//-----------------------------------------------------------------------
//i/o
//-----------------------------------------------------------------------

#command SET CONSOLE <x:ON,OFF>         => Set( _SET_CONSOLE, <(x)> )
#command SET CONSOLE (<x>)              => Set( _SET_CONSOLE, <x> )

#command SET PRINTER <x:ON,OFF,&>       => Set( _SET_PRINTER, <(x)> )
#command SET PRINTER (<x>)              => Set( _SET_PRINTER, <x> )
#command CLOSE PRINTER                  => Set( _SET_PRINTFILE, "")
#command SET PRINTER TO                 => Set( _SET_PRINTFILE, "" )
#command SET PRINTER TO <(file)> [<add: ADDITIVE>];
      => Set( _SET_PRINTFILE, <(file)>, <.add.> )

#command SET ALTERNATE <x:ON,OFF>       => Set( _SET_ALTERNATE, <(x)> )
#command SET ALTERNATE (<x>)            => Set( _SET_ALTERNATE, <x> )
#command CLOSE ALTERNATE                => Set( _SET_ALTFILE, "")
#command SET ALTERNATE TO               => Set( _SET_ALTFILE, "" )
#command SET ALTERNATE TO <(file)> [<add: ADDITIVE>];
      => Set( _SET_ALTFILE, <(file)>, <.add.> )

#command SET EXTRA     <x:ON,OFF>       => Set( _SET_EXTRA, <(x)> )
#command SET EXTRA     (<x>)            => Set( _SET_EXTRA, <x> )
#command CLOSE EXTRA                    => Set( _SET_EXTRAFILE, "")
#command SET EXTRA TO                   => Set( _SET_EXTRAFILE, "" )
#command SET EXTRA TO <(file)> [<add: ADDITIVE>];
      => Set( _SET_EXTRAFILE, <(file)>, <.add.> )

//-----------------------------------------------------------------------
//color
//-----------------------------------------------------------------------

#command SET COLOR TO [<*spec*>]        => SetColor( #<spec> )
#command SET COLOR TO ( <c> )           => SetColor( <c> )

//-----------------------------------------------------------------------
//cursor
//-----------------------------------------------------------------------

#command SET CURSOR <x:ON,OFF>;
      => SetCursor( if(Upper(<(x)>) == "ON", 1, 0) )

//-----------------------------------------------------------------------
//DOS compatibility
//-----------------------------------------------------------------------

#command SET DOSCONV [TO] <x> => SetDosconv( <x> )
#command SET DOSCONV <x:ON,OFF> => SetDosconv( <(x)> )
#command SET DOSCONV [TO] <x:DEFAULT> => SetDosconv( <(x)> )
#command SET DOSCONV [TO] <x:FILESHARE> => SetDosconv( <(x)> )

//-----------------------------------------------------------------------
//signal
//-----------------------------------------------------------------------
 
#command SET SIGNAL <x:BLOCK,DISABLE,UNBLOCK,ENABLE> =>;
         SetSignal(upper(<(x)>)=="UNBLOCK".or.upper(<(x)>)=="ENABLE")
 
//-----------------------------------------------------------------------
//qout
//-----------------------------------------------------------------------
 
#command ?  [ <list,...> ]      => QOut( <list> )
#command ?? [ <list,...> ]      => QQOut( <list> )

#command EJECT                  => __Eject()


//-----------------------------------------------------------------------
//clear screen
//-----------------------------------------------------------------------
 
#command CLS                                                            ;
      => Scroll()                                                       ;
       ; SetPos(0,0)

#command CLEAR SCREEN                                                   ;
      => CLS

#command @ <top>, <left> CLEAR TO <bottom>, <right>                     ;
      => Scroll( <top>, <left>, <bottom>, <right> )                     ;
       ; SetPos( <top>, <left> )


//-----------------------------------------------------------------------
//dispbox
//-----------------------------------------------------------------------
 
#command @ <top>, <left>, <bottom>, <right> BOX <string>                ;
                                            [COLOR <color>]             ;
      => DispBox(                                                       ;
                  <top>, <left>, <bottom>, <right>, <string>            ;
                  [, <color> ]                                          ;
                )


#command @ <top>, <left> TO <bottom>, <right> [DOUBLE]                  ;
                                              [COLOR <color>]           ;
      => DispBox(                                                       ;
                  <top>, <left>, <bottom>, <right>, 2                   ;
                  [, <color> ]                                          ;
                )


#command @ <top>, <left> TO <bottom>, <right> [COLOR <color>]           ;
                                                                        ;
      => DispBox(                                                       ;
                  <top>, <left>, <bottom>, <right>, 1                   ;
                  [, <color> ]                                          ;
                )


//-----------------------------------------------------------------------
//say
//-----------------------------------------------------------------------
 
#command @ <row>, <col> SAY <xpr>                                       ;
                        [PICTURE <pic>]                                 ;
                        [COLOR <color>]                                 ;
                                                                        ;
      => DevPos( <row>, <col> )                                         ;
       ; DevOutPict( <xpr>, <pic> [, <color>] )


#command @ <row>, <col> SAY <xpr>                                       ;
                        [COLOR <color>]                                 ;
                                                                        ;
      => DevPos( <row>, <col> )                                         ;
       ; DevOut( <xpr> [, <color>] )


//-----------------------------------------------------------------------
//get
//-----------------------------------------------------------------------

#command @ <row>, <col> GET <var>                                       ;
                        [PICTURE <pic>]                                 ;
                        [VALID <valid>]                                 ;
                        [WHEN <when>]                                   ;
                        [SEND <msg>]                                    ;
                                                                        ;
      => SetPos( <row>, <col> )                                         ;
       ; AAdd(                                                          ;
           GetList,                                                     ;
           GETNEW(@<var>,<"var">,<pic>,<{valid}>,<{when}>):display()    ;
           )                                                            ;
      [; ATail(GetList):<msg>]


//-----------------------------------------------------------------------
//savescreen
//-----------------------------------------------------------------------
 
#command SAVE SCREEN TO <var>;
      => <var> := SaveScreen( 0, 0, Maxrow(), Maxcol() )

#command RESTORE SCREEN FROM <c>;
      => RestScreen( 0, 0, Maxrow(), Maxcol(), <c> )


//-----------------------------------------------------------------------
//keyboard input
//-----------------------------------------------------------------------

#command KEYBOARD <c>     => __Keyboard( <c> )
#command CLEAR TYPEAHEAD  => __Keyboard()


//-----------------------------------------------------------------------
//filecopy
//-----------------------------------------------------------------------
 
#command COPY FILE <(src)> TO <(dest)>  => FileCopy( <(src)>, <(dest)> )

//-----------------------------------------------------------------------
//menu separator
//-----------------------------------------------------------------------

#define MENUSEP  chr(0x2500)

//-----------------------------------------------------------------------
// Binary literal
//-----------------------------------------------------------------------

//#define BINLIT(x)  str2bin(x)
#xtranslate BINLIT(<str>) => a<str>

