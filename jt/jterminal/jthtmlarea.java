
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

import getutil.*;
import javax.swing.*;
import javax.swing.text.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.net.URL;
import java.io.IOException;
import org.w3c.dom.*;


//===========================================================================
public class jthtmlarea
extends htmlareafield
implements  xmlcomponent, ActionListener, HyperlinkListener 
{
//===========================================================================

public jtparam param=null;

private scrollfield scrollpane=null; //JScrollPane 
public jtdialog dialog=null; 
public String  lastsend=null;

 
//--------------------------------------------------------------------------- 
jthtmlarea(jtdialog parent, Node node)
{
    dialog=parent;

    param=new jtparam();
    param.editable(false); //!
    param.build(node,"jthtmlarea");
    //param.list();

    param.setAlignXY(this);
    param.setToolTip(this);
    param.setEnabled(this);
    param.setEditable(this);

    if( !param.text().equals("") )
    {
        setPage(param.text());
    }

    addHyperlinkListener(this);
    
    resize(param.left,param.top,param.right-param.left+1,param.bottom-param.top+1);
    scrollpane=new scrollfield(param.left,param.top,param.right-param.left+1,param.bottom-param.top+1,this);
}

//--------------------------------------------------------------------------- 
public JComponent getScrollPane()
{
    return scrollpane==null?(JComponent)this:(JComponent)scrollpane;
}

//--------------------------------------------------------------------------- 
public void setPage(String url)
{
    //jterminal.out.println("SETPAGE: "+text);

    try
    {
        if( url.startsWith("<html>") )
        {
            setContentType("text/html");
            setText(url);
            lastsend="";
            param.text("");
        }
        else
        {
            URL x=new URL(url);
            super.setPage(x);
            param.text(url);
            //scrollToReference(x.getRef());
            //jterminal.out.println(" OK");
        }
    }
    catch( Exception e )
    {
        setContentType("text/plain");  //!
        setText( e.toString() );
        lastsend=null;
        param.text("");
        //jterminal.out.println(" failed");
    }
}

//--------------------------------------------------------------------------- 
public void setPage(URL url)
{
    try
    {
        super.setPage(url);
        //scrollToReference(url.getRef());
        param.text(url.toString()); 
    }
    catch( Exception e )
    {
        setContentType("text/plain");  //!
        setText( e.toString() );
        lastsend=null;
        param.text(""); 
    }
}
 
//----------------------------------------------------------------------------
public void hyperlinkUpdate(HyperlinkEvent e)
{
    //ENTERED    , ha fole kerul a kurzor
    //EXITED     , ha lemegy rola a kurzor
    //ACTIVATED  , ha kliekkelnek rajta
    
    if( e.getEventType().equals(HyperlinkEvent.EventType.ACTIVATED) )
    {
        //System.out.println( "URL  >"+e.getURL().toString() );
        //System.out.println( "host >"+e.getURL().getHost() );
        //System.out.println( "prot >"+e.getURL().getProtocol() );
        //System.out.println( "path >"+e.getURL().getPath() );
        //System.out.println( "file >"+e.getURL().getFile() );
        //System.out.println( "ref  >"+e.getURL().getRef() );
        
        if( param.followlink() )
        {
            setPage( e.getURL() );
        }
        else
        {
            param.text(e.getURL().toString()); 
        }

        if( param.valid() )
        {
            dialog.action(this);
        }
    }
}
 
//--------------------------------------------------------------------------- 
public void actionPerformed(ActionEvent e)
{
    if( param.valid() )
    {
        dialog.action(this);
    }
}

//--------------------------------------------------------------------------- 
public String xmlget() throws pfexception
{
    String x="<"+param.name+">"+jterminal.cdataif(param.text())+"</"+param.name+">"; 

    if( (lastsend!=null) && lastsend.equals(x) )
    {
        x=""; //nem kell kuldeni
    }
    else
    {
        lastsend=x;
    }
    return x;
}

//--------------------------------------------------------------------------- 
public void xmlset(Node data)
{
    String x=jterminal.getTextContent(data); 
    setPage(x);
}
 
//--------------------------------------------------------------------------- 
public void xmlreset()
{
    lastsend=null;
}
 
//---------------------------------------------------------------------------
public boolean isEscape()
{
    return param.escape();
}

//---------------------------------------------------------------------------
public String getName()
{
    return param.name;
}
 
 
//--------------------------------------------------------------------------- 
public boolean isFocusable()
{
    return param.focusable();
}

//--------------------------------------------------------------------------- 
public void message(Node msg)
{
    jtchange change=new jtchange(msg);
    change.setFocus(this);
    change.setFocusable(param);
    change.setEscape(param);
    change.setToolTip(this,param);
    change.setEnabled(this,param);
    change.setPage(this,param);
}

//--------------------------------------------------------------------------- 
public void buildvarlist()
{
    if( !param.name.equals("") )
    {
        dialog.varlist.add(this);
    }
}
 
//--------------------------------------------------------------------------- 
} 
