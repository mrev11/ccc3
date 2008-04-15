
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
import javax.swing.border.Border;
import javax.swing.border.TitledBorder;
 
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.text.*;
import org.w3c.dom.*;
import java.util.*;
 
//===========================================================================
public class jtparam
{
//===========================================================================

public String   nodename="";

public int      top=0; 
public int      left=0;  
public int      bottom=0;  
public int      right=0;  

public String   dialogid="";  
public String   pid="";  

public String   name=""; 
public String   text=""; 
public String   picture=null; 

public String   icon=null; 
public String   selectedicon=null; 
public String   image=null; 
public String   tooltip=null; 

public KeyStroke accelerator=null; 
public KeyStroke mnemonic=null;

public String   layout=null; 
public String   border=null; 

public boolean  escape=false;
public boolean  enabled=true;
public boolean  editable=true;
public boolean  focusable=true;
public boolean  valid=false;
public boolean  selected=false;
public boolean  followlink=true;
public boolean  linewrap=false;

public boolean  vscroll=false;
public boolean  hscroll=false;

public int      halign=-1;
public int      valign=-1;

public int      htextpos=-1;
public int      vtextpos=-1;

public double   alignx=-1;
public double   aligny=-1;

//--------------------------------------------------------------------------- 
public jtparam()
{
}

//--------------------------------------------------------------------------- 
public jtparam(Node node)
{
    build(node);
}

//--------------------------------------------------------------------------- 
public jtparam(Node node, String expected_type)
{
    build(node,expected_type);
}

//--------------------------------------------------------------------------- 
public void build(Node node, String expected_type)
{
    build(node);
    if( !expected_type.equals(nodename) )
    {
        throw new Error( "invalid nodename:"+nodename );
    }
}

//--------------------------------------------------------------------------- 
public void build (Node node)
{
    nodename=node.getNodeName();

    NamedNodeMap atts = node.getAttributes();
    for( int i=0; i<atts.getLength(); i++ ) 
    {
        Node att = atts.item(i);
        String nname=att.getNodeName();
        String value=att.getNodeValue();

             if( nname.equals("name") )     name=value; 
        else if( nname.equals("dialogid") ) dialogid=value; 
        else if( nname.equals("pid") )      pid=value; 
        else if( nname.equals("top") )      top=jterminal.parseInt(value);
        else if( nname.equals("left") )     left=jterminal.parseInt(value); 
        else if( nname.equals("bottom") )   bottom=jterminal.parseInt(value); 
        else if( nname.equals("right") )    right=jterminal.parseInt(value); 

        //Hol legyen a szoveg a komponens belsejeben?
 
        else if( nname.equals("halign"))
        {
                 if( value.equals("center") )   halign=SwingConstants.CENTER; 
            else if( value.equals("left") )     halign=SwingConstants.LEFT; 
            else if( value.equals("right") )    halign=SwingConstants.RIGHT; 
        }
        else if( nname.equals("valign"))
        {
                 if( value.equals("center") )   valign=SwingConstants.CENTER; 
            else if( value.equals("top") )      valign=SwingConstants.TOP; 
            else if( value.equals("bottom") )   valign=SwingConstants.BOTTOM; 
        }

        //Melyik reszevel illeszkedjen a komponens a tobbiekhez,
        //pl. alignx=left azt jelenti, hogy a bal szel illeszkedik.

        else if( nname.equals("alignx"))
        {
                 if( value.equals("center") )   alignx=0.5; 
            else if( value.equals("left") )     alignx=0.0;   
            else if( value.equals("right") )    alignx=1.0;
        }
        else if( nname.equals("aligny"))
        {
                 if( value.equals("center") )   aligny=0.5;
            else if( value.equals("top") )      aligny=0.0;
            else if( value.equals("bottom") )   aligny=1.0;
        }
        else if( nname.equals("htextpos"))
        {
                 if( value.equals("leading") )  htextpos=SwingConstants.LEADING;
            else if( value.equals("trailing") ) htextpos=SwingConstants.TRAILING;
            else if( value.equals("center") )   htextpos=SwingConstants.CENTER;
            else if( value.equals("left") )     htextpos=SwingConstants.LEFT;
            else if( value.equals("right") )    htextpos=SwingConstants.RIGHT;
        }
        else if( nname.equals("vtextpos"))
        {
                 if( value.equals("center") )   vtextpos=SwingConstants.CENTER;
            else if( value.equals("top") )      vtextpos=SwingConstants.TOP;
            else if( value.equals("bottom") )   vtextpos=SwingConstants.BOTTOM;
        }
    }

    for( Node child=node.getFirstChild(); child!=null; child=child.getNextSibling() ) 
    {
        String nname=child.getNodeName();

             if( nname.equals("text") )         text=jterminal.getTextContent(child);
        else if( nname.equals("picture") )      picture=jterminal.getTextContent(child); 
        else if( nname.equals("tooltip") )      tooltip=jterminal.getTextContent(child); 
        else if( nname.equals("icon") )         icon=jterminal.getTextContent(child);
        else if( nname.equals("selectedicon") ) selectedicon=jterminal.getTextContent(child);
        else if( nname.equals("image") )        image=jterminal.getTextContent(child);
        else if( nname.equals("hscroll") )      hscroll=true;
        else if( nname.equals("vscroll") )      vscroll=true;
        else if( nname.equals("mnemonic") )     mnemonic=KeyStroke.getKeyStroke(jterminal.getTextContent(child).toUpperCase());
        else if( nname.equals("accelerator") )  accelerator=KeyStroke.getKeyStroke(jterminal.getTextContent(child));
        else if( nname.equals("escape") )       escape=jterminal.getTextContent(child).equals("true");  
        else if( nname.equals("enabled") )      enabled=jterminal.getTextContent(child).equals("true");
        else if( nname.equals("editable") )     editable=jterminal.getTextContent(child).equals("true");
        else if( nname.equals("focusable") )    focusable=jterminal.getTextContent(child).equals("true");
        else if( nname.equals("valid") )        valid=jterminal.getTextContent(child).equals("true");
        else if( nname.equals("selected") )     selected=true;//jterminal.getTextContent(child).equals("true");
        else if( nname.equals("followlink") )   followlink=jterminal.getTextContent(child).equals("true");
        else if( nname.equals("linewrap") )     linewrap=jterminal.getTextContent(child).equals("true");
        else if( nname.equals("layout") )       layout=jterminal.getTextContent(child); 
        else if( nname.equals("border") )       border=jterminal.getTextContent(child); 
    }
}

//--------------------------------------------------------------------------- 
public void setBorder(JComponent c)
{
    Border border_obj=null;

         if( border==null )             border_obj=null;
    else if( border.equals("null") )    border_obj=BorderFactory.createEmptyBorder();
    else if( border.equals("empty") )   border_obj=BorderFactory.createEmptyBorder();
    else if( border.equals("lowered") ) border_obj=BorderFactory.createLoweredBevelBorder();
    else if( border.equals("raised") )  border_obj=BorderFactory.createRaisedBevelBorder();
    else if( border.equals("etched") )  border_obj=BorderFactory.createEtchedBorder();
    else if( border.equals("line") )    border_obj=BorderFactory.createLineBorder(new Color(128,128,192));//progbar

    if( c instanceof JPanel && !text.equals("") )
    {
        if( border_obj==null )
        {
            border_obj=BorderFactory.createEtchedBorder();
        }
        border_obj=BorderFactory.createTitledBorder(border_obj,text); 
    }

    if( border!=null || border_obj!=null ) 
    {
        c.setBorder(border_obj);
    }
}

//--------------------------------------------------------------------------- 
public void setLayout(Container co)
{
    LayoutManager layout_man=null;

         if( layout==null )             layout_man=null;
    else if( layout.equals("flow") )    layout_man=new FlowLayout();
    else if( layout.equals("hbox") )    layout_man=new BoxLayout(co,BoxLayout.X_AXIS);
    else if( layout.equals("vbox") )    layout_man=new BoxLayout(co,BoxLayout.Y_AXIS);
    else if( layout.equals("null") )    layout_man=null;
    else if( layout.equals("fix") )     layout_man=null;
    else if( 0<=layout.indexOf(',') )
    {
        int p=layout.indexOf(',');
        int r=Integer.parseInt(layout.substring(0,p));
        int c=Integer.parseInt(layout.substring(p+1));
        layout_man=new GridLayout(r,c);
    }
    co.setLayout(layout_man);
}

//--------------------------------------------------------------------------- 
public void setHVAlign(AbstractButton ab)
{
    if( halign>=0 ) ab.setHorizontalAlignment(halign); 
    if( valign>=0 ) ab.setVerticalAlignment(valign); 
}

public void setHVAlign(JLabel lab)
{
    if( halign>=0 ) lab.setHorizontalAlignment(halign); 
    if( valign>=0 ) lab.setVerticalAlignment(valign); 
}

//--------------------------------------------------------------------------- 
public void setHVTextPos(AbstractButton ab)
{
    if( htextpos>=0 ) ab.setHorizontalTextPosition(htextpos);
    if( vtextpos>=0 ) ab.setVerticalTextPosition(vtextpos);
}

public void setHVTextPos(JLabel lab)
{
    if( htextpos>=0 ) lab.setHorizontalTextPosition(htextpos);
    if( vtextpos>=0 ) lab.setVerticalTextPosition(vtextpos);
}

//--------------------------------------------------------------------------- 
public void setAlignXY(JComponent jc)
{
    if( alignx>=0 ) jc.setAlignmentX((float)alignx); 
    if( aligny>=0 ) jc.setAlignmentY((float)aligny); 
}

//--------------------------------------------------------------------------- 
public void setText(AbstractButton ab)
{
    if( text!=null ) ab.setText(text); 
}

public void setText(JLabel lab)
{
    if( text!=null ) lab.setText(text); 
}

public void setText(JPasswordField pw)
{
    if( text!=null ) pw.setText(text); 
}

public void setText(JTextArea ta)
{
    if( text!=null ) ta.setText(text); 
}

//--------------------------------------------------------------------------- 
public void setIcon(AbstractButton ab)
{
    if( icon!=null ) ab.setIcon(jterminal.loadIcon(icon)); 
}

public void setIcon(JLabel lab)
{
    if( icon!=null ) lab.setIcon(jterminal.loadIcon(icon)); 
}

//--------------------------------------------------------------------------- 
public void setImage(JLabel lab)
{
    if( image!=null )
    {
        byte[] b64=image.getBytes();
        byte[] img=base64.decode(b64);
        lab.setIcon(new ImageIcon(img)); 
    }
}

//--------------------------------------------------------------------------- 
public void setSelectedIcon(AbstractButton ab)
{
    if( selectedicon!=null ) ab.setSelectedIcon(jterminal.loadIcon(selectedicon)); 
}

//--------------------------------------------------------------------------- 
public void setSelected(AbstractButton ab)
{
    ab.setSelected(selected); 
}

//--------------------------------------------------------------------------- 
public void setMnemonic(AbstractButton ab)
{
    if( mnemonic!=null ) ab.setMnemonic(mnemonic.getKeyCode()); 
}

//--------------------------------------------------------------------------- 
public void setAccelerator(JMenuItem mi)
{
    if( accelerator!=null ) mi.setAccelerator(accelerator); 
}

//--------------------------------------------------------------------------- 
public void setToolTip(JComponent jc)
{
    if( tooltip!=null ) jc.setToolTipText(tooltip); 
}

//--------------------------------------------------------------------------- 
public void setEnabled(JComponent jc)
{
    jc.setEnabled(enabled); 
}

//--------------------------------------------------------------------------- 
public void setEditable(JTextComponent jt)
{
    jt.setEditable(editable); 
}

//--------------------------------------------------------------------------- 
public void setLineWrap(JTextArea jt)
{
    jt.setLineWrap(linewrap); 
}

//--------------------------------------------------------------------------- 
public void list()
{
    System.out.print("nodename   : ");    System.out.println(nodename);
    System.out.print("top        : ");    System.out.println(top);
    System.out.print("left       : ");    System.out.println(left);
    System.out.print("bottom     : ");    System.out.println(bottom);
    System.out.print("right      : ");    System.out.println(right);
    System.out.print("name       : ");    System.out.println(name);
    System.out.print("text       : ");    System.out.println(text);
    System.out.print("icon       : ");    System.out.println(icon);
    System.out.print("image      : ");    System.out.println(image);
    System.out.print("tooltip    : ");    System.out.println(tooltip);
    System.out.print("layout     : ");    System.out.println(layout);
    System.out.print("border     : ");    System.out.println(border);
    System.out.print("mnemonic   : ");    System.out.println(mnemonic);
    System.out.print("accelerator: ");    System.out.println(accelerator);
    System.out.print("halign     : ");    System.out.println(halign);
    System.out.print("valign     : ");    System.out.println(valign);
    System.out.print("alignx     : ");    System.out.println(alignx);
    System.out.print("aligny     : ");    System.out.println(aligny);
}

//--------------------------------------------------------------------------- 
} 
