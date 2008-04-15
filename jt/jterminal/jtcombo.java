
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
public class jtcombo
extends choicefield
implements xmlcomponent, ActionListener, FocusListener
{
//===========================================================================

public jtparam param=null;

public jtdialog dialog=null; 
public String  lastsend=null;
 
//--------------------------------------------------------------------------- 
jtcombo(jtdialog parent, Node node)
{
    dialog=parent;

    param=new jtparam(node,"jtcombo");
    //param.list();

    //param.setHVAlign(this);
    param.setAlignXY(this);
    //param.setHVTextPos(this);
    //param.setText(this);
    param.setToolTip(this);
    //param.setIcon(this);
    //param.setSelectedIcon(this);
    //param.setSelected(this);
    param.setEnabled(this);
    //param.setFocusable(this);
    //param.setMnemonic(this);
 
    for( Node child=node.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();
        String text=jterminal.getTextContent(child);

        if( name.equals("item") )
        {
            addItem(text);
        }

        else if( name.equals("selectedindex") )
        {
            try
            {
                setSelectedIndex(jterminal.parseInt(text)-1); //a Java 0-tol szamol
            }
            catch( IllegalArgumentException e )
            {
            }
        }
    }
    this.resize(param.left,param.top,param.right-param.left+1);
    addActionListener(this);
    addFocusListener(this);
}

//---------------------------------------------------------------------------
public void actionPerformed(ActionEvent e)
{
    if( param.valid ) 
    {
        dialog.action(this);
    }
}

//--------------------------------------------------------------------------- 
public String xmlget()
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
    return param.escape;
}

//---------------------------------------------------------------------------
public String getName()
{
    return param.name;
}

//--------------------------------------------------------------------------- 
public void focusGained(FocusEvent e)
{
    jterminal.autoscroll(this);
}
 
//--------------------------------------------------------------------------- 
public void focusLost(FocusEvent e)
{
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

    for( Node child=msg.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();
        if( name.equals("changelist") )
        {
            changelist(child);
        }
    }
}


//--------------------------------------------------------------------------- 
private void changelist(Node node)
{
    for( node=node.getFirstChild(); node!=null; node=node.getNextSibling() )
    {
        String name=node.getNodeName();
        String text=jterminal.getTextContent(node);

        if( name.equals("removeall") )
        {
            removeAllItems();
        }

        else if( name.equals("app") )
        {
            addItem(text);
        }

        else if( name.equals("ins") )
        {
            String index=jterminal.getTextContentChild(node,"at");
            int i=jterminal.parseInt(index);
            if( 0<=i && i<getItemCount() )
            {
                insertItemAt(text,i);
            }
            else
            {
                addItem(text);
            }
        }

        else if( name.equals("del") )
        {
            int i=jterminal.parseInt(text);
            if( 0<=i && i<getItemCount() )
            {
                removeItemAt(i);
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