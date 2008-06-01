
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
import java.awt.event.*;
import org.w3c.dom.*;

//===========================================================================
public class jtprogbar
extends progbarfield
implements xmlcomponent
{
//===========================================================================

public jtparam param=null;

public jtdialog dialog=null; 
private int minval=0;
private int maxval=100;
private jterminal jterm=null;

//--------------------------------------------------------------------------- 
jtprogbar(jtdialog parent)
{
    dialog=parent;
    jterm=dialog.jterm;
    param=new jtparam();
}

//--------------------------------------------------------------------------- 
jtprogbar(jtdialog parent, Node node)
{
    dialog=parent;
    jterm=dialog.jterm;

    param=new jtparam(node,"jtprogbar");
    //param.list();

    param.setAlignXY(this);
    param.setToolTip(this);
    param.setBorder(this);

    if( param.text().equals("percent") )
    {
        setString(null);
    }
    else
    {
        setString(param.text());
    }

    for( Node child=node.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();
        
        if( name.equals("min") )
        {
            minval=jterminal.parseInt(jterminal.getTextContent(child));
            setMinimum( minval );
        }

        else if( name.equals("max") )
        {
            maxval=jterminal.parseInt(jterminal.getTextContent(child));
            setMaximum( maxval );
        }
 
        else if( name.equals("caption") )
        {
            if( dialog!=null && dialog.createdAutomatically() )
            {
                dialog.setTitle( jterminal.getTextContent(child) );
            }
        }
    }

    resize(param.left,param.top,param.right-param.left+1,param.bottom-param.top+1);
}

//--------------------------------------------------------------------------- 
public String xmlget()
{
    return "";
}

//--------------------------------------------------------------------------- 
public void xmlset(Node data)
{

}
 
//--------------------------------------------------------------------------- 
public void xmlreset()
{

}
 
//---------------------------------------------------------------------------
public boolean isEscape()
{
    return false;
}

//---------------------------------------------------------------------------
public String getName()
{
    return param.name;
}
 
//--------------------------------------------------------------------------- 
public void message(Node msg)  //jtmessage uzenet feldolgozasa
{
    for( Node c=msg.getFirstChild(); c!=null; c=c.getNextSibling() )
    {
        String name=c.getNodeName();

    
        if( name.equals("setbar") )
        {
            //<jtmessage>
            //<control>name</control> 
            //<setbar>
            //  <value>val</value> 
            //  <text>txt</text> 
            //  <caption>cap</caption> 
            //</setbar>
            //</jtmessage>
        
            for( Node x=c.getFirstChild(); x!=null; x=x.getNextSibling() )
            {
                String xname=x.getNodeName();
                String xtext=jterminal.getTextContent(x);

                if( xname.equals("value") )
                {
                    setValue( jterminal.parseInt(xtext)%maxval );
                }

                else if( xname.equals("text") )
                {
                    if( xtext.equals("percent") )
                    {
                        setString(null); //default
                    }
                    else
                    {
                        setString(xtext);
                    }
                    setStringPainted(true);
                }

                else if( xname.equals("caption") )
                {
                    if( dialog!=null && dialog.createdAutomatically() )
                    {
                        dialog.setTitle( xtext );
                    }
                }
            }
        }

        else if( name.equals("clearbar") )
        {
            setValue(0);              //default 
            setStringPainted(false);  //default 
            setString(null);          //default
            
            if( dialog!=null && dialog.param.name.equals("CREATED_AUTOMATICALLY") )
            {
                jterm.removedlg(dialog);
                (new jtremove(dialog.wnd)).run(); 
            }
        }
    }
}

//--------------------------------------------------------------------------- 
public void buildvarlist()
{
    dialog.varlist.add(this);
}

//--------------------------------------------------------------------------- 
} 