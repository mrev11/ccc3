
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

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <termkey.h>
#include <inkey.ch>


int main()
{
    TermKey *tk;
    TermKeyKey key;
    TermKeyResult ret;

    tk = termkey_new(0,TERMKEY_FLAG_CTRLC);

    if(termkey_get_flags(tk) & TERMKEY_FLAG_UTF8)
    {
        printf("Termkey in UTF-8 mode\n");
    }
    else if(termkey_get_flags(tk) & TERMKEY_FLAG_RAW)
    {
        printf("Termkey in RAW mode\n");
    }


    int cnt=0;
    while(1) 
    {
        int inkeycode=0;

        ret = termkey_waitkey(tk, &key);
        char buffer[50];
        termkey_strfkey(tk,buffer,sizeof(buffer),&key,TERMKEY_FORMAT_VIM);
        printf("%4d Key %s\n",++cnt,buffer);

        // A program nem feltetlenul kap meg minden kombinaciot,
        // mert bizonyos kombinaciokat a terminal elhasznal lapozasra.
        //
        //  SHIFT-PGUP
        //  SHIFT-PGDN
        //  SHIFT-HOME
        //  SHIFT-END
        //
        // xterm-ben a lapozas ki lehet kapcsolni,
        // ehhez az X resource-ok kozott meg kell adni:
        //
        //   xterm*omitTranslation: paging
        //
        // xfce4-terminal-ban nem tudom kikapcsolni a lapozast

    
        if( ret==TERMKEY_RES_EOF )
            exit(0);

        else if( ret==TERMKEY_RES_ERROR ) 
            exit(0);

        else if(ret == TERMKEY_RES_KEY) 
        {
            if(key.type == TERMKEY_TYPE_MOUSE)
                ;
            else if(key.type == TERMKEY_TYPE_POSITION)
                ;
            else if(key.type == TERMKEY_TYPE_MODEREPORT)
                ;
            else if(key.type == TERMKEY_TYPE_UNKNOWN_CSI)
                ;
 
            else  if( key.type==TERMKEY_TYPE_UNICODE )
            {
                inkeycode=key.code.codepoint;
                
                if( 97<=inkeycode && inkeycode<=122 )
                {
                    if( key.modifiers==0 )
                        ;
                    else if( key.modifiers&4 ) // CTRL
                    {
                        inkeycode-=96;
                    }
                    else if( key.modifiers&2 ) // ALT
                    {
                        inkeycode=96-inkeycode;
                    }
                }
            }

            else if( key.type==TERMKEY_TYPE_FUNCTION )
            {
                int n=key.code.number;
                if( 1<=n && n<=12 )
                {
                    inkeycode=-(200+n);

                    int mod=key.modifiers;
                    if( mod&4 )
                    {
                        inkeycode-=200; //ctrl
                    }
                    else if( mod&2 )
                    {
                        inkeycode-=300; //alt
                    }
                    else if( mod&1 )
                    {
                        inkeycode-=100; //shift
                    }

                }
                else if( 13<=n && n<=24 )
                {
                    inkeycode=-(300+n-12);
                }
                else if( 25<=n && n<=36 )
                {
                    inkeycode=-(400+n-24);
                }
                else if( 49<=n && n<=60 )
                {
                    inkeycode=-(500+n-48);
                }
            }

            if( key.type==TERMKEY_TYPE_KEYSYM )
            {
                int sym=key.code.sym;
                int mod=key.modifiers;

                     if( sym==TERMKEY_SYM_BACKSPACE ) inkeycode=K_BS;
                else if( sym==TERMKEY_SYM_TAB )       inkeycode=K_TAB;
                else if( sym==TERMKEY_SYM_ENTER )     inkeycode=K_ENTER;
                else if( sym==TERMKEY_SYM_ESCAPE )    inkeycode=K_ESC;
                else if( sym==TERMKEY_SYM_DEL )       inkeycode=K_BS;
                else if( sym==TERMKEY_SYM_DELETE )    inkeycode=K_DEL;
                else if( sym==TERMKEY_SYM_INSERT )    inkeycode=K_INS;
                
                else if( sym==TERMKEY_SYM_KPPLUS )    inkeycode='+';
                else if( sym==TERMKEY_SYM_KPMINUS )   inkeycode='-';
                else if( sym==TERMKEY_SYM_KPMULT )    inkeycode='*';
                else if( sym==TERMKEY_SYM_KPDIV )     inkeycode='/';
                else if( sym==TERMKEY_SYM_KPCOMMA )   inkeycode=','; //wrong
                else if( sym==TERMKEY_SYM_KPPERIOD )  inkeycode='.'; //wrong


                else if( mod==0  )
                {
                    switch(sym)
                    {
                        case TERMKEY_SYM_UP       : inkeycode=K_UP; break;
                        case TERMKEY_SYM_DOWN     : inkeycode=K_DOWN; break;
                        case TERMKEY_SYM_LEFT     : inkeycode=K_LEFT; break;
                        case TERMKEY_SYM_RIGHT    : inkeycode=K_RIGHT; break;
                        case TERMKEY_SYM_PAGEUP   : inkeycode=K_PGUP; break;
                        case TERMKEY_SYM_PAGEDOWN : inkeycode=K_PGDN; break;
                        case TERMKEY_SYM_HOME     : inkeycode=K_HOME; break;
                        case TERMKEY_SYM_END      : inkeycode=K_END; break;
                    }
                }
                else if( mod&4 ) // CTRL
                {
                    switch(sym)
                    {
                        case TERMKEY_SYM_UP       : inkeycode=K_CTRL_UP; break;
                        case TERMKEY_SYM_DOWN     : inkeycode=K_CTRL_DOWN; break;
                        case TERMKEY_SYM_LEFT     : inkeycode=K_CTRL_LEFT; break;
                        case TERMKEY_SYM_RIGHT    : inkeycode=K_CTRL_RIGHT; break;
                        case TERMKEY_SYM_PAGEUP   : inkeycode=K_CTRL_PGUP; break;
                        case TERMKEY_SYM_PAGEDOWN : inkeycode=K_CTRL_PGDN; break;
                        case TERMKEY_SYM_HOME     : inkeycode=K_CTRL_HOME; break;
                        case TERMKEY_SYM_END      : inkeycode=K_CTRL_END; break;
                    }
                }
                else if( mod&2 ) // ALT
                {
                    switch(sym)
                    {
                        case TERMKEY_SYM_UP       : inkeycode=K_ALT_UP; break;
                        case TERMKEY_SYM_DOWN     : inkeycode=K_ALT_DOWN; break;
                        case TERMKEY_SYM_LEFT     : inkeycode=K_ALT_LEFT; break;
                        case TERMKEY_SYM_RIGHT    : inkeycode=K_ALT_RIGHT; break;
                        case TERMKEY_SYM_PAGEUP   : inkeycode=K_ALT_PGUP; break;
                        case TERMKEY_SYM_PAGEDOWN : inkeycode=K_ALT_PGDN; break;
                        case TERMKEY_SYM_HOME     : inkeycode=K_ALT_HOME; break;
                        case TERMKEY_SYM_END      : inkeycode=K_ALT_END; break;
                    }
                }
                else if( mod&1 ) // SHIFT
                {
                    switch(sym)
                    {
                        case TERMKEY_SYM_UP       : inkeycode=K_SH_UP; break;
                        case TERMKEY_SYM_DOWN     : inkeycode=K_SH_DOWN; break;
                        case TERMKEY_SYM_LEFT     : inkeycode=K_SH_LEFT; break;
                        case TERMKEY_SYM_RIGHT    : inkeycode=K_SH_RIGHT; break;
                        case TERMKEY_SYM_PAGEUP   : inkeycode=K_SH_PGUP; break;
                        case TERMKEY_SYM_PAGEDOWN : inkeycode=K_SH_PGDN; break;
                        case TERMKEY_SYM_HOME     : inkeycode=K_SH_HOME; break;
                        case TERMKEY_SYM_END      : inkeycode=K_SH_END; break;
                    }
                }
            }


            //--------------------------------------------------
            // reszletes adatok
            //--------------------------------------------------

            printf("                ");
            if( key.type==TERMKEY_TYPE_UNICODE )
            {
                printf( " cpt=%-4ld", key.code.codepoint);
            }
            else
            {
                printf( " cpt=%4s", "");
            }


            if( key.type==TERMKEY_TYPE_FUNCTION )
            {
                printf( " fun=%-4d", key.code.number);
            }
            else
            {
                printf( " fun=%4s", "");
            }


            if( key.type==TERMKEY_TYPE_KEYSYM )
            {
                printf( " sym=%-4d", key.code.sym );
            }
            else
            {
                printf( " sym=%4s", "");
            }
            
            printf( "mod=%x", key.modifiers);
            printf("   >>>> %d\n",inkeycode);


            // CTRL-C-re kilep
            if( key.type==TERMKEY_TYPE_UNICODE &&
                key.modifiers & TERMKEY_KEYMOD_CTRL &&
                (key.code.codepoint == 'C' || key.code.codepoint == 'c'))
            {
                break;
            }
        }
    }

    termkey_destroy(tk);

    return 0;
}
