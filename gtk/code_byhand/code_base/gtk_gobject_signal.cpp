
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
#include <stdint.h>
#include <gtk/gtk.h>
#include <cccapi.h>
#include <cccgtk.h>

#define INSTANCE_OF(o,t)  g_type_check_instance_is_a((GTypeInstance*)o,t)

namespace _nsp_gtk {
namespace _nsp_gobject {

extern void _clp_signal_register_codeblock(int argno);
extern void _clp_signal_unregister_codeblock(int argno);
extern void _clp_signal_execute_codeblock(int argno);
extern void *find_callback(gpointer widget, const char *sigspec);

DEFINE_METHOD(gobject);
DEFINE_METHOD(operation);
DEFINE_METHOD(description);

#define DEBUG_NOTIFY

//---------------------------------------------------------------------------
static void destroy_notify(void *x, GClosure *closure)
{
    #ifdef DEBUG_NOTIFY
    printf("\nNOTIFY %ld %lx", (LONG)x, (ULONG)closure);
    #endif 

    number((LONG)x); //idx
    _nsp_gtk::_nsp_gobject::_clp_signal_unregister_codeblock(1);
    pop();
}

//---------------------------------------------------------------------------
static void signal_connect(int argno, GConnectFlags flags)
{
    CCC_PROLOG("gtk.gobject.signal_connect",4);
    
    gpointer wdg=_parp(1);           //1: widget
    const char *name=_parc_utf8(2);  //2: signal_name

    VALUE *blk=0;
    if( ISBLOCK(3) )
    { 
        blk=_par(3);                 //3: code_block
    }
    else
    { 
        ARGERROR(); 
    }

    VALUE *obj=0;
    if( argno>3 )
    {
        obj=_par(4);                 //4: object
    }
    
    pointer(wdg);
    push_symbol(blk);
    push_symbol(obj?obj:&NIL);
    _nsp_gtk::_nsp_gobject::_clp_signal_register_codeblock(3);
    long idx=D2INT(TOP()->data.number);
    pop();

    void *callback=find_callback(wdg,name); //hiba kezelve

    gulong id=g_signal_connect_data(    G_OBJECT(wdg),
                                        name,
                                        G_CALLBACK(callback),
                                        (gpointer)(LONG)idx,
                                        destroy_notify,
                                        flags );
    _retp((void*)(ULONG)id);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_signal_connect(int argno)
{
    signal_connect(argno,(GConnectFlags)0);
}

//---------------------------------------------------------------------------
void _clp_signal_connect_after(int argno)
{
    signal_connect(argno,G_CONNECT_AFTER);
}

//---------------------------------------------------------------------------
void _clp_signal_handler_disconnect(int argno)
{
    CCC_PROLOG("gtk.gobject.signal_handler_disconnect",2);
    gpointer o=_parp(1);
    gulong id=(ULONG)_parp(2);
    g_signal_handler_disconnect(o,id);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_signal_handler_block(int argno)
{
    CCC_PROLOG("gtk.gobject.signal_handler_block",2);
    gpointer o=_parp(1);
    gulong id=(ULONG)_parp(2);
    g_signal_handler_block(o,id);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_signal_handler_unblock(int argno)
{
    CCC_PROLOG("gtk.gobject.signal_unhandler_block",2);
    gpointer o=_parp(1);
    gulong id=(ULONG)_parp(2);
    g_signal_handler_unblock(o,id);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

} //gobject
} //gtk
