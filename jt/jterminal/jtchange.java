
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
import javax.swing.text.*;
import org.w3c.dom.*;
import java.util.*;
 
//===========================================================================
public class jtchange
{
//===========================================================================

public String  text=null;
public String  tooltip=null;
public String  picture=null;
public String  icon=null;
public String  image=null;

public String  escape=null;
public String  enabled=null;
public String  editable=null;
public String  focusable=null;
public String  setfocus=null;
public String  linewrap=null;


//--------------------------------------------------------------------------- 
public jtchange(Node msg)
{
    build(msg);
}

//--------------------------------------------------------------------------- 
public void build (Node msg)
{
    for( Node child=msg.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();

             if( name.equals("control") )       {}
        else if( name.equals("changetext") )    text=jterminal.getTextContent(child);
        else if( name.equals("changetooltip") ) tooltip=jterminal.getTextContent(child);
        else if( name.equals("changepicture") ) picture=jterminal.getTextContent(child);
        else if( name.equals("changeicon") )    icon=jterminal.getTextContent(child);
        else if( name.equals("changeimage") )   image=jterminal.getTextContent(child);
        else if( name.equals("escape") )        escape=jterminal.getTextContent(child);
        else if( name.equals("enabled") )       enabled=jterminal.getTextContent(child);
        else if( name.equals("editable") )      editable=jterminal.getTextContent(child);
        else if( name.equals("focusable") )     focusable=jterminal.getTextContent(child);
        else if( name.equals("setfocus") )      setfocus=jterminal.getTextContent(child);
        else if( name.equals("linewrap") )      linewrap=jterminal.getTextContent(child);
    }

}

//--------------------------------------------------------------------------- 
public void setText(AbstractButton ab, jtparam param)
{
    if( text!=null ) ab.setText(param.text=text); 
}

public void setText(JLabel lab, jtparam param)
{
    if( text!=null ) lab.setText(param.text=text);}

public void setText(JPasswordField pw, jtparam param)
{
    if( text!=null ) pw.setText(param.text=text); 
}

public void setText(JTextArea ta, jtparam param)
{
    if( text!=null ) ta.setText(param.text=text); 
}

//--------------------------------------------------------------------------- 
public void setToolTip(JComponent jc, jtparam param)
{
    if( tooltip!=null ) jc.setToolTipText(param.tooltip=tooltip); 
}

public void setToolTip(AbstractButton ab, jtparam param)
{
    if( tooltip!=null ) ab.setToolTipText(param.tooltip=tooltip); 
}

//--------------------------------------------------------------------------- 
public void setPicture(jtget g, jtparam param)
{
    if( picture!=null ) g.setPicture(param.picture=picture);
}

//--------------------------------------------------------------------------- 
public void setIcon(AbstractButton ab, jtparam param)
{
    if( icon!=null ) ab.setIcon(jterminal.loadIcon(param.icon=icon)); 
}

public void setIcon(JLabel lab, jtparam param)
{
    if( icon!=null ) lab.setIcon(jterminal.loadIcon(param.icon=icon)); 
}

//--------------------------------------------------------------------------- 
public void setImage(JLabel lab, jtparam param)
{
    if( image!=null )
    {
        param.image=image;
        byte[] b64=image.getBytes();
        byte[] img=base64.decode(b64);
        lab.setIcon(new ImageIcon(img)); 
    }
}

//--------------------------------------------------------------------------- 
public void setEscape(jtparam param)
{
    if( escape!=null ) param.escape=escape.equals("true"); 
}

//--------------------------------------------------------------------------- 
public void setEnabled(JComponent jc, jtparam param)
{
    if( enabled!=null ) jc.setEnabled(param.enabled=enabled.equals("true")); 
}

//--------------------------------------------------------------------------- 
public void setEditable(JTextComponent jt, jtparam param)
{
    if( editable!=null) jt.setEditable(param.editable=editable.equals("true")); 
}

//--------------------------------------------------------------------------- 
public void setFocusable(jtparam param)
{
    if( focusable!=null ) param.focusable=focusable.equals("true"); 
}

//--------------------------------------------------------------------------- 
public void setFocus(JComponent jc)
{
    if( setfocus!=null ) jc.requestFocus(); 
}

//--------------------------------------------------------------------------- 
public void setLineWrap(JTextArea jt, jtparam param)
{
    if( linewrap!=null ) jt.setLineWrap(param.linewrap=linewrap.equals("true")); 
}

//--------------------------------------------------------------------------- 
}