
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
import java.awt.*;
import java.awt.event.*;
import org.w3c.dom.*;

//===========================================================================
public class jttextarea
extends textareafield
implements  xmlcomponent, FocusListener, ActionListener 
{
//===========================================================================

public jtparam param=null;

private scrollfield scrollpane=null; //JScrollPane 
public jtdialog dialog=null; 
public String  lastsend=null;
public Color bground=null;
static public Color bground_error=new Color(255,200,200); //piros
static public Color bground_normal=new Color(222,222,222); //szurke
 
//--------------------------------------------------------------------------- 
jttextarea(jtdialog parent, Node node)
{
    dialog=parent;

    param=new jtparam(node,"jttextarea");
    //param.list();
 
    param.setAlignXY(this); 
    param.setToolTip(this); 
    param.setText(this); 
    param.setEnabled(this); 
    param.setEditable(this); 
    param.setLineWrap(this); 

    setBackground( bground=bground_normal );
    addFocusListener(this);
    
    setFont( getutil.getposition.getDefaultMonoFont() );

    resize(param.left,param.top,param.right-param.left+1,param.bottom-param.top+1);
    scrollpane=new scrollfield(param.left,param.top,param.right-param.left+1,param.bottom-param.top+1,this);

    // Amikor a jttextarea-t betesszük 
    // egy jtdialogba vagy jtpanelba,
    // akkor nem magát a komponenst, 
    // hanem ezt a scrollpane-t kell berakni,
    // így működik a scrollozás.
    // Méretezni sem magát a komponenst kell,
    // hanem a scrollpane-jét.

}

//--------------------------------------------------------------------------- 
public JComponent getScrollPane()
{
    return scrollpane==null?(JComponent)this:(JComponent)scrollpane;
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
    if( !param.editable() )
    {
        return "";
    }

    String x="<"+param.name+">"+jterminal.cdataif(getText())+"</"+param.name+">"; 

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
    setText(x);
    setCaretPosition(0);
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
    setBackground( bground=(param.editable() ? Color.white : bground_normal) );
    jterminal.autoscroll(this);
}
 
//--------------------------------------------------------------------------- 
public void focusLost(FocusEvent e)
{
    //Megjegyzes:
    //a JDialog.getContentPane() egy JPanel-t ad,
    //ugyanazt a JPanel-t, mint JTextField.getParent(),
    //ezt a JPanelt lehet szinezni, a szinet kiolvasni.
    //getParent() null-t add, ha a komponens meg nincs
    //hozzaadva a JPanel-hez.
    
    setBackground( bground=bground_normal ); 
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
    change.setLineWrap(this,param);
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
