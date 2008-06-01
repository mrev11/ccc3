
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

import javax.swing.BorderFactory;
 
import javax.swing.*;
import java.awt.*;
import org.w3c.dom.*;


//===========================================================================
public class jtlabel 
extends labelfield
implements xmlcomponent
{
//===========================================================================

public jtparam param=null;
public jtdialog dialog=null; 
 
//--------------------------------------------------------------------------- 
jtlabel(jtdialog parent, Node node)
{
    dialog=parent;

    param=new jtparam(node,"jtlabel");
    //param.list();

    param.setHVAlign(this);
    param.setAlignXY(this);
    param.setHVTextPos(this);
    param.setText(this);
    param.setToolTip(this);
    param.setIcon(this);
    param.setImage(this);
    param.setEnabled(this);
    //param.setMnemonic(this);
 
    resize(param.left,param.top,param.right-param.left+1,param.bottom-param.top+1);
    //setForeground(Color.black);
    //setForeground(Color.blue);
    setForeground( new Color(0,0,128) ); 

}

//--------------------------------------------------------------------------- 
public String xmlget()
{
    return "";
}

//--------------------------------------------------------------------------- 
public void xmlset(Node data)
{
    String x=jterminal.getTextContent(data); 
    setText(x);
}
 
//--------------------------------------------------------------------------- 
public void xmlreset()
{

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
    change.setText(this,param);
    change.setToolTip(this,param);
    change.setIcon(this,param);
    change.setImage(this,param);
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
