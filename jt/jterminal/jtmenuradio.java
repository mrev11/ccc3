
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

import java.awt.event.*;
import javax.swing.*;
import org.w3c.dom.*;

 
//===========================================================================
public class jtmenuradio 
extends javax.swing.JRadioButtonMenuItem
implements xmlcomponent, ActionListener 
{
//===========================================================================

public jtparam param=null;

public jtdialog dialog=null; 
public String  lastsend=null;
 
//--------------------------------------------------------------------------- 
jtmenuradio(jtdialog parent, Node node)
{
    dialog=parent;

    param=new jtparam(node,"jtmenuradio");
    //param.list();
 
    param.setText(this);
    param.setToolTip(this);
    param.setSelected(this);
    param.setIcon(this);
    param.setSelectedIcon(this);
    param.setEnabled(this);
    param.setMnemonic(this);

    addActionListener(this);
    setFont( getutil.getposition.getDefaultDlgFont() );
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
public String xmlget()
{
    String x="<"+param.name+">"+(isSelected()?"true":"false")+"</"+param.name+">"; 

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
    setSelected( x.equals("true") );
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
    jtchange change=new jtchange(msg);
    change.setEscape(param);
    change.setText(this,param);
    change.setToolTip(this,param);
    change.setIcon(this,param);
    change.setEnabled(this,param);
}
 
//--------------------------------------------------------------------------- 
public void buildvarlist()
{
    dialog.varlist.add(this);
}

//--------------------------------------------------------------------------- 
} 