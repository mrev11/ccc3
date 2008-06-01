
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
public String   name=""; 
public String   dialogid="";  
public String   pid="";  

public int      top=0; 
public int      left=0;  
public int      bottom=0;  
public int      right=0;  

public int      halign=-1;
public int      valign=-1;
public int      htextpos=-1;
public int      vtextpos=-1;
public double   alignx=-1;
public double   aligny=-1;


private Hashtable hash=null;

//ezek atkerultek a hash-be
//public String   text=""; 
//public String   picture=null; 
//public String   icon=null; 
//public String   selectedicon=null; 
//public String   image=null; 
//public String   tooltip=null; 
//public String   layout=null; 
//public String   border=null; 
//public KeyStroke accelerator=null; 
//public KeyStroke mnemonic=null;  //int-re valtozott

//public boolean  enabled=true;
//public boolean  editable=true;
//public boolean  focusable=true;
//public boolean  followlink=true;

//public boolean  escape=false;
//public boolean  valid=false;
//public boolean  selected=false;
//public boolean  linewrap=false;
//public boolean  hscroll=false;
//public boolean  vscroll=false;


//--------------------------------------------------------------------------- 
public jtparam()
{
    hash=new Hashtable();
}

//--------------------------------------------------------------------------- 
public jtparam(Node node)
{
    hash=new Hashtable();
    build(node);
}

//--------------------------------------------------------------------------- 
public jtparam(Node node, String expected_type)
{
    hash=new Hashtable();
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
private void build (Node node)
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
        
        if( nname.startsWith("jt") )
            ;//kihagy
        else if( nname.startsWith("#") )
            ;//kihagy
        else
        {
            hash.put(nname,jterminal.getTextContent(child));
        }
        
        //atkerultek a hash-be
        //     if( nname.equals("text") )         text=jterminal.getTextContent(child);
        //else if( nname.equals("picture") )      picture=jterminal.getTextContent(child); 
        //else if( nname.equals("tooltip") )      tooltip=jterminal.getTextContent(child); 
        //else if( nname.equals("icon") )         icon=jterminal.getTextContent(child);
        //else if( nname.equals("selectedicon") ) selectedicon=jterminal.getTextContent(child);
        //else if( nname.equals("image") )        image=jterminal.getTextContent(child);
        //else if( nname.equals("hscroll") )      hscroll=true;
        //else if( nname.equals("vscroll") )      vscroll=true;
        //else if( nname.equals("mnemonic") )     mnemonic=KeyStroke.getKeyStroke(jterminal.getTextContent(child).toUpperCase());
        //else if( nname.equals("accelerator") )  accelerator=KeyStroke.getKeyStroke(jterminal.getTextContent(child));
        //else if( nname.equals("escape") )       escape=jterminal.getTextContent(child).equals("true");  
        //else if( nname.equals("enabled") )      enabled=jterminal.getTextContent(child).equals("true");
        //else if( nname.equals("editable") )     editable=jterminal.getTextContent(child).equals("true");
        //else if( nname.equals("focusable") )    focusable=jterminal.getTextContent(child).equals("true");
        //else if( nname.equals("valid") )        valid=jterminal.getTextContent(child).equals("true");
        //else if( nname.equals("selected") )     selected=true;//jterminal.getTextContent(child).equals("true");
        //else if( nname.equals("followlink") )   followlink=jterminal.getTextContent(child).equals("true");
        //else if( nname.equals("linewrap") )     linewrap=jterminal.getTextContent(child).equals("true");
        //else if( nname.equals("layout") )       layout=jterminal.getTextContent(child); 
        //else if( nname.equals("border") )       border=jterminal.getTextContent(child); 
    }
    //list();//debug
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
//az alabbiak a hash-bol
//--------------------------------------------------------------------------- 
public void setText(AbstractButton ab)
{
    ab.setText(text()); 
}

public void setText(JLabel lab)
{
    lab.setText(text()); 
}

public void setText(JPasswordField pw)
{
    pw.setText(text()); 
}

public void setText(JTextArea ta)
{
    ta.setText(text()); 
}

public String text()
{
    String value=(String)hash.get("text");
    return value==null?"":value; //default: ""
}

public String text(String value)
{
    hash.put("text",value==null?"":value);
    return value;
}

//--------------------------------------------------------------------------- 
public String picture()
{
    return (String)hash.get("picture"); //default: null
}

public String picture(String value)
{
    hash.put("picture",value);
    return value;
}

//--------------------------------------------------------------------------- 
public void setIcon(AbstractButton ab)
{
    String icon=icon();
    if( icon!=null ) ab.setIcon(jterminal.loadIcon(icon)); 
}

public void setIcon(JLabel lab)
{
    String icon=icon();
    if( icon!=null ) lab.setIcon(jterminal.loadIcon(icon)); 
}

public String icon()
{
    return (String)hash.get("icon"); //default: null
}

public String icon(String value)
{
    hash.put("icon",value);
    return value;
}

//--------------------------------------------------------------------------- 
public void setSelectedIcon(AbstractButton ab)
{
    String icon=selectedicon();
    if( icon!=null ) ab.setSelectedIcon(jterminal.loadIcon(icon)); 
}

public String selectedicon()
{
    return (String)hash.get("selectedicon"); //default: null
}

public String selectedicon(String value)
{
    hash.put("selectedicon",value);
    return value;
}

//--------------------------------------------------------------------------- 
public void setImage(JLabel lab)
{
    String image=image();
    if( image!=null )
    {
        byte[] b64=image.getBytes();
        byte[] img=base64.decode(b64);
        lab.setIcon(new ImageIcon(img)); 
    }
}

public String image()
{
    return (String)hash.get("image"); //default: null
}

public String image(String value)
{
    hash.put("image",value);
    return value;
}

//--------------------------------------------------------------------------- 
public void setToolTip(JComponent jc)
{
    jc.setToolTipText(tooltip()); 
}

public String tooltip()
{
    return (String)hash.get("tooltip"); //default: null
}

public String tooltip(String value)
{
    hash.put("tooltip",value);
    return value;
}

//--------------------------------------------------------------------------- 
public void setLayout(Container co)
{
    LayoutManager layout_man=null;
    String layout=(String)hash.get("layout"); //default: null

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
public void setBorder(JComponent c)
{
    Border border_obj=null;
    String border=(String)hash.get("border"); //default: null

         if( border==null )             border_obj=null;
    else if( border.equals("null") )    border_obj=BorderFactory.createEmptyBorder();
    else if( border.equals("empty") )   border_obj=BorderFactory.createEmptyBorder();
    else if( border.equals("lowered") ) border_obj=BorderFactory.createLoweredBevelBorder();
    else if( border.equals("raised") )  border_obj=BorderFactory.createRaisedBevelBorder();
    else if( border.equals("etched") )  border_obj=BorderFactory.createEtchedBorder();
    else if( border.equals("line") )    border_obj=BorderFactory.createLineBorder(new Color(128,128,192));//progbar

    if( c instanceof JPanel && !text().equals("") )
    {
        if( border_obj==null )
        {
            border_obj=BorderFactory.createEtchedBorder();
        }
        border_obj=BorderFactory.createTitledBorder(border_obj,text()); 
    }

    if( border!=null || border_obj!=null ) 
    {
        c.setBorder(border_obj);
    }
}

//--------------------------------------------------------------------------- 
public void setAccelerator(JMenuItem mi)
{
    KeyStroke accelerator=accelerator();
    if( accelerator!=null ) mi.setAccelerator(accelerator); 
}

public KeyStroke accelerator()
{
    String accelerator=(String)hash.get("accelerator"); //default:null
    if( accelerator!=null )
    {
        return KeyStroke.getKeyStroke(accelerator);
    }
    return null;
}

//--------------------------------------------------------------------------- 
public void setMnemonic(AbstractButton ab)
{
    int mnemonic=mnemonic();
    if( mnemonic!=0 ) ab.setMnemonic(mnemonic); 
}

public int mnemonic()
{
    String mnemonic=(String)hash.get("mnemonic"); //default:0
    if( mnemonic!=null )
    {
        return KeyStroke.getKeyStroke(mnemonic.toUpperCase()).getKeyCode();
    }
    return 0;
}

//--------------------------------------------------------------------------- 
public void setEnabled(JComponent jc)
{
    jc.setEnabled(enabled()); 
}

public boolean enabled()
{
    String value=(String)hash.get("enabled");
    return value==null || value.equals("true"); //default: true
}

public boolean enabled(boolean value)
{
    hash.put("enabled",value?"true":"false");
    return value;
}

//--------------------------------------------------------------------------- 
public void setEditable(JTextComponent jt)
{
    jt.setEditable(editable()); 
}

public boolean editable()
{
    String value=(String)hash.get("editable");
    return value==null || value.equals("true");  //default: true
}

public boolean editable(boolean value)
{
    hash.put("editable",value?"true":"false");
    return value;
}

//--------------------------------------------------------------------------- 
public void setFocusable(JComponent jc)
{
    jc.setFocusable(focusable()); 
}

public boolean focusable()
{
    String value=(String)hash.get("focusable");
    return value==null || value.equals("true"); //default: true
}

public boolean focusable(boolean value)
{
    hash.put("focusable",value?"true":"false");
    return value;
}

//--------------------------------------------------------------------------- 
public boolean followlink()
{
    String value=(String)hash.get("followlink");
    return value==null || value.equals("true"); //default: true
}

public boolean followlink(boolean value)
{
    hash.put("followlink",value?"true":"false");
    return value;
}


//--------------------------------------------------------------------------- 
public boolean escape()
{
    String value=(String)hash.get("escape");
    return value!=null && value.equals("true"); //default: false
}

public boolean escape(boolean value)
{
    hash.put("escape",value?"true":"false");
    return value;
}

//--------------------------------------------------------------------------- 
public boolean valid()
{
    String value=(String)hash.get("valid");
    return value!=null && value.equals("true"); //default: false
}

public boolean valid(boolean value)
{
    hash.put("valid",value?"true":"false");
    return value;
}

//--------------------------------------------------------------------------- 
public void setSelected(AbstractButton ab)
{
    ab.setSelected(selected()); 
}

public boolean selected()
{
    String selected=(String)hash.get("selected");
    return selected!=null && !selected.equals("false"); //!
}

public boolean selected(boolean value)
{
    hash.put("selected",value?"true":"false");
    return value;
}

//--------------------------------------------------------------------------- 
public void setLineWrap(JTextArea jt)
{
    jt.setLineWrap(linewrap()); 
}

public boolean linewrap()
{
    String value=(String)hash.get("linewrap");
    return value!=null && value.equals("true"); //default: false
}

public boolean linewrap(boolean value)
{
    hash.put("linewrap",value?"true":"false");
    return value;
}

//--------------------------------------------------------------------------- 
public boolean hscroll()
{
    String value=(String)hash.get("hscroll");
    return value!=null && !value.equals("false"); //default: false
}

public boolean hscroll(boolean value)
{
    hash.put("hscroll",value?"true":"false");
    return value;
}

//--------------------------------------------------------------------------- 
public boolean vscroll()
{
    String value=(String)hash.get("vscroll");
    return value!=null && !value.equals("false"); //default: false
}

public boolean vscroll(boolean value)
{
    hash.put("vscroll",value?"true":"false");
    return value;
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
    System.out.println(nodename);
    System.out.println("--------------------------");

    System.out.print("name       : ");    System.out.println(name);
    System.out.print("top        : ");    System.out.println(top);
    System.out.print("left       : ");    System.out.println(left);
    System.out.print("bottom     : ");    System.out.println(bottom);
    System.out.print("right      : ");    System.out.println(right);
    System.out.print("halign     : ");    System.out.println(halign);
    System.out.print("valign     : ");    System.out.println(valign);
    System.out.print("alignx     : ");    System.out.println(alignx);
    System.out.print("aligny     : ");    System.out.println(aligny);

    for(Enumeration e=hash.keys(); e.hasMoreElements();) 
    {
        String key=(String)e.nextElement();
        System.out.print(key);
        System.out.print(" => ");
        System.out.println(hash.get(key));
    }    
}

//--------------------------------------------------------------------------- 
} 
