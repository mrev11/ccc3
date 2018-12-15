
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

#include <QObject>
#include <QGuiApplication>
#include <QKeyEvent>


#define KEY_UP          Qt::Key_Up
#define KEY_DOWN        Qt::Key_Down
#define KEY_LEFT        Qt::Key_Left
#define KEY_RIGHT       Qt::Key_Right
#define KEY_HOME        Qt::Key_Home
#define KEY_END         Qt::Key_End
#define KEY_PGUP        Qt::Key_PageUp
#define KEY_PGDN        Qt::Key_PageDown
#define KEY_INS         Qt::Key_Insert
#define KEY_DEL         Qt::Key_Delete

#define KEY_KP_UP       Qt::Key_Up      
#define KEY_KP_DOWN     Qt::Key_Down    
#define KEY_KP_LEFT     Qt::Key_Left    
#define KEY_KP_RIGHT    Qt::Key_Right   
#define KEY_KP_HOME     Qt::Key_Home    
#define KEY_KP_END      Qt::Key_End     
#define KEY_KP_PGUP     Qt::Key_PageUp  
#define KEY_KP_PGDN     Qt::Key_PageDown
#define KEY_KP_INS      Qt::Key_Insert  
#define KEY_KP_DEL      Qt::Key_Delete  

#define KEY_RETURN      Qt::Key_Return
#define KEY_ESC         Qt::Key_Escape
#define KEY_BS          Qt::Key_Backspace
#define KEY_TAB         Qt::Key_Tab

#define KEY_F1          Qt::Key_F1
#define KEY_F2          Qt::Key_F2
#define KEY_F3          Qt::Key_F3
#define KEY_F4          Qt::Key_F4
#define KEY_F5          Qt::Key_F5
#define KEY_F6          Qt::Key_F6
#define KEY_F7          Qt::Key_F7
#define KEY_F8          Qt::Key_F8
#define KEY_F9          Qt::Key_F9
#define KEY_F10         Qt::Key_F10
#define KEY_F11         Qt::Key_F11
#define KEY_F12         Qt::Key_F12

#define KEYCODE keycode_qt
#include <keycode.h>


//---------------------------------------------------------------------------------------------
char *qstring_to_utf8(QString str) //kimasolja
{
    QByteArray arr=str.toUtf8();
    int len=arr.length();
    char *buf=(char*)malloc(len+1);
    for(int i=0; i<len; i++)
    {
        buf[i]=arr.at(i);
    }
    buf[len]=0;
    return buf; //free
}

//---------------------------------------------------------------------------------------------
int qstring_to_unicode(QString str)
{
    if( str.length()>0 )
    {
        QChar c=str.at(0);
        return c.unicode();
    }
    return 0;
}

//---------------------------------------------------------------------------------------------
void key_press(QKeyEvent *ev)
{
    //#define DEBUG

    #ifdef DEBUG
    char *text=qstring_to_utf8(ev->text());
    printf("key_press\n");
    //printf("    count %d\n",ev->count()); 
    printf("    key    %x\n",(unsigned int)ev->key()); 
    printf("    modif  %x\n",(unsigned int)ev->modifiers());
    printf("    nscan  %x\n",(unsigned int)ev->nativeScanCode());
    printf("    nkey   %x\n",(unsigned int)ev->nativeVirtualKey());
    printf("    nmodif %x\n",(unsigned int)ev->nativeModifiers());
    printf("    ucode  %d %s\n",qstring_to_unicode(ev->text()),text);
    free(text);
    #endif


    int state=0;
    if(ev->modifiers() & Qt::ShiftModifier)   state|=1;
    if(ev->modifiers() & Qt::ControlModifier) state|=2;
    if(ev->modifiers() & Qt::AltModifier)     state|=4; //Alt
    if(ev->modifiers() & Qt::KeypadModifier)  state|=8; //NumLock


    int code=qstring_to_unicode(ev->text());
    if( code )
    {
        if( (int)ev->key()==Qt::Key_Delete )
        {
            if( ev->nativeScanCode()!=0x5b ) 
            { 
                //nem keypad  
                code=keycode_qt(Qt::Key_Delete,state);
            }
            else if( ev->nativeModifiers()!=0x10 )
            {
                //keypad, numlock kiengedve  
                code=keycode_qt(Qt::Key_Delete,state);
            }
            else
            {
                //keypad, numlock benyomva
                //code=','; //magyar  
                code='.'; //angol
            }
        }
        else if( (state&4) && 'a'<=code  && code<='z' )
        {
            code=-(code-'a'+1); //ALT+(a-z)
        }
    }
    else
    {
        code=keycode_qt((int)ev->key(),state);
    }


    #ifdef DEBUG
        printf(">>>>> %d\n",code);
    #endif


    if( code )
    {
        extern void tcpio_sendkey(int);
        tcpio_sendkey(code);
    }
}

//---------------------------------------------------------------------------------------------
void key_release(QKeyEvent *ev)
{
    //printf( "key_release\n"); 
}

//---------------------------------------------------------------------------------------------



