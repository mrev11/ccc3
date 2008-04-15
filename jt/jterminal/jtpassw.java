
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

//olyan text mezo,
//aminek nincs picture-je,
//a karaktereket * helyettesiti,
//az eredmeny pedig: 
//base64.encode( text ) //ha salt1 es salt2 sincs megadva
//base64.encode( md5(text+saltX) ) //ha csak saltX van megadva
//base64.encode( md5( md5(text+salt1)+salt2 ) ) //ha salt1 es salt2 adott
 
import getutil.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.security.*;
import org.w3c.dom.*;

//===========================================================================
public class jtpassw 
extends passwordfield
implements  xmlcomponent, FocusListener, ActionListener 
{
//===========================================================================

public jtparam param=null;

public jtdialog dialog=null; 
public String  lastsend=null;
 
public Color bground=null;
static public Color bground_error=new Color(255,200,200); //piros
static public Color bground_normal=new Color(222,222,222); //szurke

private jterminal jterm;
 
//--------------------------------------------------------------------------- 
jtpassw(jtdialog parent, Node node)
{
    dialog=parent;
    jterm=dialog.jterm;

    param=new jtparam();
    param.build(node,"jtpassw");
    //param.list();

    param.setAlignXY(this);
    param.setToolTip(this);
    param.setEnabled(this);
    param.setText(this);
 
    this.resize(param.left,param.top,param.right-param.left+1);

    bground=bground_normal;
    setBackground( bground );

    addFocusListener(this);
    addActionListener(this);
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
public String xmlget() throws pfexception
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
public boolean isFocusable()
{
    return param.focusable;
}
 

//--------------------------------------------------------------------------- 
public void focusGained(FocusEvent e)
{
    setBackground(Color.white);
    jterminal.autoscroll(this);
}
 
//--------------------------------------------------------------------------- 
public void focusLost(FocusEvent e)
{
    bground=bground_normal;
    setBackground(bground); 
}
 

//--------------------------------------------------------------------------- 
public void message(Node msg)
{
    jtchange change=new jtchange(msg);
    change.setFocus(this);
    change.setFocusable(param);
    change.setEscape(param);
    change.setText(this,param);
    change.setToolTip(this,param);
    change.setEnabled(this,param);

    for( Node child=msg.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();

        if( name.equals("getpassword") )
        {
            getpassword(child);
        }

        else if( name.equals("sign") )
        {
            sign(child);
        }
    }
}

//--------------------------------------------------------------------------- 
private void getpassword(Node data)
{
    byte[] salt1=null;
    byte[] salt2=null;
 
    for( Node c=data.getFirstChild(); c!=null; c=c.getNextSibling() )
    {
        if( c.getNodeName().equals("salt1") )
        {
            salt1=jterm.char2byte_ex(jterminal.getTextContent(c)); 
        }
        else if( c.getNodeName().equals("salt2") )
        {
            salt2=jterm.char2byte_ex(jterminal.getTextContent(c)); 
        }
    }

    byte[] t=jterm.char2byte_ex( new String(getPassword()) );
 
    try
    {
        if( salt1!=null )
        {
            t=jterminal.cat(t,salt1);
            MessageDigest md5=MessageDigest.getInstance("MD5");
            md5.update(t);
            t=md5.digest();
        }

        if( salt2!=null )
        {
            t=jterminal.cat(t,salt2);
            MessageDigest md5=MessageDigest.getInstance("MD5");
            md5.update(t);
            t=md5.digest();
        }
    }
    catch(Exception e)
    {
        jterminal.die(e);
    }
    
    t=base64.encode(t);

    jterm.send("<password>"+new String(t)+"</password>");
}

//--------------------------------------------------------------------------- 
private void sign(Node node)
{
    String alias=null;
    byte[] data=null;
 
    for( Node c=node.getFirstChild(); c!=null; c=c.getNextSibling() )
    {
        if( c.getNodeName().equals("alias") )
        {
            alias=jterminal.getTextContent(c); 
        }
        else if( c.getNodeName().equals("data") )
        {
            data=jterm.char2byte_ex(jterminal.getTextContent(c)); 
            data=base64.decode(data);
        }
    }

    byte[] sig;
 
    try
    {
        PrivateKey key=ksutil.getPrivateKey(alias,getPassword());
        Signature rsa=Signature.getInstance("SHA1withRSA"); 
        rsa.initSign(key); 
        rsa.update(data,0,data.length);
        sig=rsa.sign(); 
        sig=base64.encode(sig);
    }
    catch(Exception e)
    {
        sig=new byte[0]; 
    }
    
    jterm.send("<signature>"+new String(sig)+"</signature>");
}

//--------------------------------------------------------------------------- 
public void buildvarlist()
{
    dialog.varlist.add(this);
}
 
//--------------------------------------------------------------------------- 
} 

