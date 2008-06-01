
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

private Hashtable hash=null;

//minden atkerult a hash-be
//private String  text=null;       //   "changetext"
//private String  tooltip=null;    //   "changetooltip"
//private String  picture=null;    //   "changepicture"
//private String  icon=null;       //   "changeicon"
//private String  image=null;      //   "changeimage"
//private String  escape=null;     //   "escape"
//private String  focusable=null;  //   "focusable"
//private String  setfocus=null;   //   "setfocus"
//private String  enabled=null;    //   "enabled"
//private String  editable=null;   //   "editable"
//private String  linewrap=null;   //   "linewrap"

//--------------------------------------------------------------------------- 
public jtchange(Node msg)
{
    build(msg);
}

//--------------------------------------------------------------------------- 
private void build (Node msg)
{
    hash=new Hashtable();

    for( Node child=msg.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();
        
        if( name.startsWith("jt") )
            ;//kihagy
        else if( name.startsWith("#") )
            ;//kihagy
        else
        {
            hash.put(name,jterminal.getTextContent(child));
        }

        //minden atkerult a hash-be
        //     if( name.equals("control") )       {}
        //else if( name.equals("changetext") )    text=jterminal.getTextContent(child);
        //else if( name.equals("changetooltip") ) tooltip=jterminal.getTextContent(child);
        //else if( name.equals("changepicture") ) picture=jterminal.getTextContent(child);
        //else if( name.equals("changeicon") )    icon=jterminal.getTextContent(child);
        //else if( name.equals("changeimage") )   image=jterminal.getTextContent(child);
        //else if( name.equals("escape") )        escape=jterminal.getTextContent(child);
        //else if( name.equals("enabled") )       enabled=jterminal.getTextContent(child);
        //else if( name.equals("editable") )      editable=jterminal.getTextContent(child);
        //else if( name.equals("focusable") )     focusable=jterminal.getTextContent(child);
        //else if( name.equals("setfocus") )      setfocus=jterminal.getTextContent(child);
        //else if( name.equals("linewrap") )      linewrap=jterminal.getTextContent(child);
    }
    
    //list();
}

//--------------------------------------------------------------------------- 
public String get(String key)
{
    return (String)hash.get(key);
}

//--------------------------------------------------------------------------- 
public void set(String key, String value)
{
    hash.put(key,value);
}

//--------------------------------------------------------------------------- 
public void list()
{
    System.out.println("--------------------------");
    for(Enumeration e=hash.keys(); e.hasMoreElements();) 
    {
        String key=(String)e.nextElement();
        System.out.print(key);
        System.out.print(" => ");
        System.out.println(hash.get(key));
    }    
}

//--------------------------------------------------------------------------- 
public void setText(AbstractButton ab, jtparam param)
{
    String text=(String)hash.get("changetext");
    if( text!=null ) ab.setText(param.text(text)); 
}

public void setText(JLabel lab, jtparam param)
{
    String text=(String)hash.get("changetext");
    if( text!=null ) lab.setText(param.text(text));}

public void setText(JPasswordField pw, jtparam param)
{
    String text=(String)hash.get("changetext");
    if( text!=null ) pw.setText(param.text(text)); 
}

public void setText(JTextArea ta, jtparam param)
{
    String text=(String)hash.get("changetext");
    if( text!=null ) ta.setText(param.text(text)); 
}

public void setText(jtget jt, jtparam param)
{
    String text=(String)hash.get("changetext");
    if( text!=null ) jt.setText(param.text(text)); 
}

//--------------------------------------------------------------------------- 
public void setToolTip(JComponent jc, jtparam param)
{
    String tooltip=(String)hash.get("changetooltip");
    if( tooltip!=null ) jc.setToolTipText(param.tooltip(tooltip)); 
}

public void setToolTip(AbstractButton ab, jtparam param)
{
    String tooltip=(String)hash.get("changetooltip");
    if( tooltip!=null ) ab.setToolTipText(param.tooltip(tooltip)); 
}

//--------------------------------------------------------------------------- 
public void setPicture(jtget g, jtparam param)
{
    String picture=(String)hash.get("changepicture");
    if( picture!=null ) g.setPicture(param.picture(picture));
}

//--------------------------------------------------------------------------- 
public void setIcon(AbstractButton ab, jtparam param)
{
    String icon=(String)hash.get("changeicon");
    if( icon!=null ) ab.setIcon(jterminal.loadIcon(param.icon(icon))); 
}

public void setIcon(JLabel lab, jtparam param)
{
    String icon=(String)hash.get("changeicon");
    if( icon!=null ) lab.setIcon(jterminal.loadIcon(param.icon(icon))); 
}

//--------------------------------------------------------------------------- 
public void setImage(JLabel lab, jtparam param)
{
    String image=(String)hash.get("changeimage");
    if( image!=null )
    {
        param.image(image);
        byte[] b64=image.getBytes();
        byte[] img=base64.decode(b64);
        lab.setIcon(new ImageIcon(img)); 
    }
}

//--------------------------------------------------------------------------- 
public void setEscape(jtparam param)
{
    String escape=(String)hash.get("escape");
    if( escape!=null ) param.escape(escape.equals("true")); 
}

//--------------------------------------------------------------------------- 
public void setFocusable(jtparam param)
{
    String focusable=(String)hash.get("focusable");
    if( focusable!=null ) param.focusable(focusable.equals("true")); 
}

//--------------------------------------------------------------------------- 
public void setFocus(JComponent jc)
{
    String setfocus=(String)hash.get("setfocus");
    if( setfocus!=null ) jc.requestFocus(); 
}

//--------------------------------------------------------------------------- 
public void setEnabled(JComponent jc, jtparam param)
{
    String enabled=(String)hash.get("enabled");
    if( enabled!=null ) jc.setEnabled(param.enabled(enabled.equals("true"))); 
}

//--------------------------------------------------------------------------- 
public void setEditable(JTextComponent jt, jtparam param)
{
    String editable=(String)hash.get("editable");
    if( editable!=null) jt.setEditable(param.editable(editable.equals("true"))); 
}

//--------------------------------------------------------------------------- 
public void setLineWrap(JTextArea jt, jtparam param)
{
    String linewrap=(String)hash.get("linewrap");
    if( linewrap!=null ) jt.setLineWrap(param.linewrap(linewrap.equals("true"))); 
}

//--------------------------------------------------------------------------- 
public boolean setPage(jthtmlarea jt, jtparam param)
{
    String url=(String)hash.get("changeurl");
    if( url!=null ) jt.setPage(param.text(url));
    return url!=null;
}

//--------------------------------------------------------------------------- 
public boolean setValue(jtslider jt)
{
    String value=(String)hash.get("changevalue");
    if( value!=null ) jt.setValue(jterminal.parseInt(value));
    return value!=null;
}

//--------------------------------------------------------------------------- 


}
