
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
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;
import org.w3c.dom.*;

//===========================================================================
public class jtslider
extends sliderfield
implements xmlcomponent, FocusListener, ChangeListener
{
//===========================================================================

public jtparam param=null;
public jtdialog dialog=null; 
public String  lastsend=null;
public boolean actionenabled=true;
 
//--------------------------------------------------------------------------- 
jtslider(jtdialog parent, Node node)
{
    dialog=parent;

    param=new jtparam(node,"jtslider");
    param.setAlignXY(this);
    param.setToolTip(this);
    param.setEnabled(this);
    
    String par;
    if( (par=param.get("orientation"))!=null )
    {
        if( par.startsWith("v") )
        {
            this.setOrientation(VERTICAL);
        }
        else if( par.startsWith("h") )
        {
            this.setOrientation(HORIZONTAL); //default
        }
    }
    if( (par=param.get("inverted"))!=null )
    {
        this.setInverted(par.equals("true"));
    }
    if( (par=param.get("value"))!=null )
    {
        this.setValue(jterminal.parseInt(par));
    }
    if( (par=param.get("min"))!=null )
    {
        this.setMinimum(jterminal.parseInt(par));
    }
    if( (par=param.get("max"))!=null )
    {
        this.setMaximum(jterminal.parseInt(par));
    }
    if( (par=param.get("minortick"))!=null )
    {
        this.setMinorTickSpacing(jterminal.parseInt(par));
    }
    if( (par=param.get("majortick"))!=null )
    {
        this.setMajorTickSpacing(jterminal.parseInt(par));
    }
    if( (par=param.get("painttick"))!=null )
    {
        this.setPaintTicks(par.equals("true"));
    }
    if( (par=param.get("paintlabel"))!=null )
    {
        this.setPaintLabels(par.equals("true"));
    }

    Hashtable labelTable=new Hashtable();
    for(int i=1; i<=100; i++)
    {
        String value=param.get("val"+Integer.toString(i));
        String label=param.get("lab"+Integer.toString(i));

        if( value==null || label==null )
        {
            break;
        }
        labelTable.put(new Integer(Integer.parseInt(value)),new JLabel(label));
    }
    if( !labelTable.isEmpty() )
    {
        this.setLabelTable(labelTable);
    }
 
    Dictionary labtab=this.getLabelTable();
    for( Enumeration e = labtab.elements() ; e.hasMoreElements() ;) 
    {
         ((JLabel)e.nextElement()).setFont(getutil.getposition.getDefaultDlgFont());
    }    

    resize(param.left,param.top,param.right-param.left+1,param.bottom-param.top+1);
    addChangeListener(this);
    addFocusListener(this);
}

//---------------------------------------------------------------------------
public void stateChanged(ChangeEvent e) 
{
    if( actionenabled && !this.getValueIsAdjusting() )
    {
        if( param.valid() )
        {
            dialog.action(this);
        }
    }
}

//--------------------------------------------------------------------------- 
public String xmlget()
{
    String x="<"+param.name+">"+Integer.toString(this.getValue())+"</"+param.name+">"; 

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
    this.setValue( jterminal.parseInt(x) );
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
public boolean isFocusable()
{
    return param.focusable();
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

    actionenabled=false;
    change.setValue(this);
    actionenabled=true;
}

//--------------------------------------------------------------------------- 
public void buildvarlist()
{
    dialog.varlist.add(this);
}

//--------------------------------------------------------------------------- 
} 
