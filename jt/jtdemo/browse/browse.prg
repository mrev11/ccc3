
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

//primitív HTML böngésző, 
//ami a JEditorPane osztály képességeire támaszkodik

#include "icons.ch"

static stack:={}
static stkix:=0

******************************************************************************
function main(url)

    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
    
    if( url!=NIL .and. left(url,1)=="-" )
        url:=jtgetenv("url")
    end
        
    if( !empty(url) )
        stack:={url}
        stkix:=1
    end
    
    msgloop(makedlg())
 
    return NIL


******************************************************************************
static function msgloop(dlg)
local msg, url
    
    if( stkix>0 )
        dlg:var:url:varput( stack[stkix] )
        dlg:var:html:varput( stack[stkix] )
    end

    dlg:show
    while( NIL!=(msg:=dlg:getmessage)  )

        if( msg=="esc" )
            quit

        elseif( msg=="url" )              //beírtak egy URL-t
            url:=dlg:var:url:varget 
            dlg:var:html:varput( url )
            stack:={url}
            stkix:=1

        elseif( msg=="html" )             //kattintottak egy linken
            url:=dlg:var:html:varget 
            dlg:var:url:varput( url )
            asize(stack,stkix)
            aadd(stack,url)
            stkix++
 
        elseif( msg=="back" )             //vissza az előzőre
            if( stkix>1 )
                stkix--
                url:=stack[stkix]
                dlg:var:url:varput( url )
                dlg:var:html:varput( url )
            end
 
        elseif( msg=="forward" )          //vissza a következőre
            if( stkix<len(stack) )
                stkix++
                url:=stack[stkix]
                dlg:var:url:varput( url )
                dlg:var:html:varput( url )
            end
        
        elseif( msg=="reload" )           //újratölti a kurrens lapot
            if( stkix>0 )
                dlg:list
                dlg:var:html:changeurl( stack[stkix] )
            end
        end

        printstack() 
    end
    return NIL

******************************************************************************
static function makedlg()

local dlg,html,tbar,url
local back,forw,reload,esc

    dlg:=jtdialogNew(5,15,20,100) 
    dlg:caption:="CCC HTML Browser"
    dlg:layout:="vbox"
    
    html:=jthtmlareaNew()
    html:bottom:=32
    html:name:="html"
    html:valid:=.t. //küldi a követett linkek URL-jét
    
    tbar:=jttoolbarNew()

    tbar:additem( back:=jtpushNew() ) 
                  back:name:="back"
                  back:tooltip:="Back"
                  back:icon:=ICON_BACK

    tbar:additem( forw:=jtpushNew() ) 
                  forw:name:="forward"
                  forw:tooltip:="Forward"
                  forw:icon:=ICON_FORWARD

    tbar:additem( reload:=jtpushNew() )
                  reload:name:="reload"
                  reload:tooltip:="Reload"
                  reload:icon:=ICON_RELOAD

    tbar:additem( jthglueNew() )

    tbar:additem( url:=jtgetNew() )
                  url:name:="url"
                  url:tooltip:="Location"
                  url:valid:=.t.

    tbar:additem( jthglueNew() )

    tbar:additem( esc:=jtpushNew() )
                  esc:name:="esc"
                  esc:tooltip:="Escape"
                  esc:icon:=ICON_EXIT
 
    dlg:add(tbar)
    dlg:add(html)
    
    dlg:varinst("browser")
    
    return dlg

******************************************************************************
static function printstack()
local n
    ? "----------------------------------"
    for n:=1 to stkix
        ? stack[n]
    next
    return NIL


******************************************************************************
 