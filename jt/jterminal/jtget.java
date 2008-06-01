
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
public class jtget 
extends picturefield
implements  xmlcomponent, FocusListener, ActionListener 
{
//===========================================================================

public jtparam param=null;
 
public jtdialog dialog=null; 
public String  lastsend=null;
 
public Color bground=null;
static public Color bground_error=new Color(255,200,200); //piros
static public Color bground_normal=new Color(222,222,222); //szurke

private jterminal jterm=null;
 
//--------------------------------------------------------------------------- 
jtget(jtdialog parent, Node node)
{
    dialog=parent;
    jterm=dialog.jterm;

    param=new jtparam();
    param.escape(true); //!
    param.build(node,"jtget");
    //param.list();

    //param.setHVAlign(this);
    param.setAlignXY(this);
    //param.setHVTextPos(this);
    param.setToolTip(this);
    //param.setIcon(this);
    //param.setSelectedIcon(this);
    //param.setSelected(this);
    param.setEnabled(this);
    //param.setFocusable(this); //nem kell --> isFocusable
    //param.setMnemonic(this);

    setPicture(param.picture());
    setText(param.text());
    
    resize(param.left,param.top,param.right-param.left+1);
    
    if( param.top==0 && param.left==0 && param.bottom==0 && param.right==0 )
    {
        expand=true;
    }

    setBackground( bground=bground_normal );

    addFocusListener(this);

    //addActionListener(this);
    //ha az elobbi sor nincs kikommentezve,
    //akkor egy ENTER ketto(!) akciot eredmemyez,
    //ui. a picturefield mar beallitja sajat magat listenernek.
    //Viszont mindketszer a jtget actionPerformed metodusa
    //hivodik meg, minthogy az feluldefinialja a picturefield
    //(baseclass) actionPerformed metodusat.
}


//--------------------------------------------------------------------------- 
public void actionPerformed(ActionEvent e)
{
    //jterminal.out.println("jtget.actionPerformed");
    //jterminal.out.println(e);

    super.actionPerformed(e);

    if( param.valid() )
    {
        if( !verify() )
        {
            dataerror();
        }
        else
        {
            dialog.action(this);
        }
    }
}

//--------------------------------------------------------------------------- 
public String xmlget() throws pfexception
{
    if( !verify() )
    {
        //nem megfelelo a kitoltes
    
        if( verifyX() )
        {
            //a pictureben be van allitva az  X flag,
            //ezert nem engedjuk folytatni az akciot

            throw new pfexception(this); 
        }
        return "";  //nem kuldjuk 
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
    //jterminal.out.print(name);
    //jterminal.out.print(":");
    //jterminal.out.print("FOCUS-GAINED");

    setBackground(bground=Color.white);
    jterminal.autoscroll(this);

    //jterminal.out.println(" white");
}

//--------------------------------------------------------------------------- 
public void focusLost(FocusEvent e)
{
    //jterminal.out.print(name);
    //jterminal.out.print(":");
    //jterminal.out.print("FOCUS-LOST");
 
    //Megjegyzes:
    //a JDialog.getContentPane() egy JPanel-t ad,
    //ugyanazt a JPanel-t, mint JTextField.getParent(),
    //ezt a JPanelt lehet szinezni, a szinet kiolvasni.
    //getParent() null-t add, ha a komponens meg nincs
    //hozzaadva a JPanel-hez.
    
    boolean v=verify();
    boolean x=verifyX();
    //boolean f=verifyF();
    
    if( v || !x )
    {
        setBackground(bground=bground_normal); 
        //jterminal.out.println(" normal");
    }
    else
    {
        setBackground(bground=bground_error); 
        //jterminal.out.println(" error");
    }

}

//--------------------------------------------------------------------------- 
public void message(Node msg)
{
    jtchange change=new jtchange(msg);
    change.setFocus(this);
    change.setFocusable(param);
    change.setEscape(param);
    change.setToolTip(this,param);
    change.setPicture(this,param);
    change.setEnabled(this,param);
    change.setText(this,param);
}

//--------------------------------------------------------------------------- 
private void dataerror()
{ 
    jtalert a;
    a=new jtalert(jterm);
    a.message="Hibas adatbevitel!";
    a.send=false;
    a.type=JOptionPane.ERROR_MESSAGE;
    a.run();
}

//--------------------------------------------------------------------------- 
public void buildvarlist()
{
    dialog.varlist.add(this);
}

//--------------------------------------------------------------------------- 
} 