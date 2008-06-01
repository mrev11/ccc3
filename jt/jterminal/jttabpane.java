
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

import java.awt.*;
import javax.swing.*;
import javax.swing.event.*;
import org.w3c.dom.*;
import java.util.*;
 
//===========================================================================
public class jttabpane
extends tabpanefield
implements xmlcomponent, ChangeListener
{
//===========================================================================

public jtparam param=null;

private ArrayList itemlist=new ArrayList(); //jtpanelek
 
public jtdialog dialog=null; 
public String  lastsend=null;
 
//--------------------------------------------------------------------------- 
jttabpane(jtdialog parent, Node node)
{
    param=new jtparam(node,"jttabpane");
    //param.list();

    dialog=parent;

    resize(param.left,param.top,param.right-param.left+1,param.bottom-param.top+1);

    for( Node child=node.getFirstChild(); child!=null; child=child.getNextSibling() ) 
    {
        String name=child.getNodeName();
        String text=jterminal.getTextContent(child);
 
        if( name.equals("selectedindex") )
        {
            try
            {
                setSelectedIndex(jterminal.parseInt(text)-1); //a Java 0-tol szamol
            }
            catch( IllegalArgumentException e )
            {
            }
        }

        else if( name.equals("placement") )
        {
            char c=text.charAt(0);

                 if( c=='t' )  setTabPlacement(JTabbedPane.TOP);
            else if( c=='b' )  setTabPlacement(JTabbedPane.BOTTOM); 
            else if( c=='l' )  setTabPlacement(JTabbedPane.LEFT); 
            else if( c=='r' )  setTabPlacement(JTabbedPane.RIGHT); 
        }
 
        else if( name.equals("jtpanel") )
        {
            jtpanel c=new jtpanel(dialog,child);

            //A jtpanel text-jebol lesz a ful cimkeje.
            //Ha a jtpanel-nek text attributuma van, 
            //akkor keretet is csinal maganak,
            //ezt meg kell szuntetni:

            c.setBorder(null);

            addTab( c.param.text(),
                    jterminal.loadIcon(c.param.icon()),
                    c.getScrollPane(),
                    c.param.tooltip());
            
            if( c.param.mnemonic()!=0 )
            {
                setMnemonicAt(itemlist.size(),c.param.mnemonic());

                //a JPanel-nek eredetileg nincs mnemonicja,
                //viszont a jttabpanek jtpanelekbol epulnek fel,
                //es a jtpanel mnemonicjaival vezerelheto a jttabpane
            }
            itemlist.add(c);
        }
    }
    addChangeListener(this);
    setmenu();
}

//---------------------------------------------------------------------------
public void stateChanged(ChangeEvent e)
{
    setmenu();
    if( param.valid() )
    {
        dialog.action(this);
    }
    //System.out.println("jttabpane.stateChanged");
}
 
//--------------------------------------------------------------------------- 
private void setmenu()
{
    int i=getSelectedIndex();
    if( 0<=i && i<itemlist.size() ) 
    {
        jtpanel p=(jtpanel)itemlist.get(i);
    
        if( p.menubar!=null )
        {
            dialog.setJMenuBar(p.menubar);
            dialog.pack();
        }
    }
}

//--------------------------------------------------------------------------- 
public String xmlget() throws pfexception 
{
    String x="<"+param.name+">"+ Integer.toString(1+getSelectedIndex()) +"</"+param.name+">"; 

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

    try
    {
        setSelectedIndex(jterminal.parseInt(x)-1); //a Java 0-tol szamol
    }
    catch( IllegalArgumentException e )
    {
    }
    lastsend=null;
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
public void message(Node msg)
{

}
 
//--------------------------------------------------------------------------- 
public void buildvarlist()
{
    if( !param.name.equals("") )
    {
        dialog.varlist.add(this);
    }
    for( int i=0; i<itemlist.size(); i++)
    {
        ((xmlcomponent)itemlist.get(i)).buildvarlist();
    }
}
 
//----------------------------------------------------------------------------
}

