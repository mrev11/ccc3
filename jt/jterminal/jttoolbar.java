
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
import org.w3c.dom.*;
import java.util.*;
 
//===========================================================================
public class jttoolbar 
extends JToolBar
implements xmlcomponent
{
//===========================================================================

public String  name=""; 
public jtdialog dialog=null; 

private ArrayList itemlist=new ArrayList();
 
//--------------------------------------------------------------------------- 
jttoolbar(jtdialog parent, Node node)
{
    if( !node.getNodeName().equals("jttoolbar") )
    {
        throw new Error( "invalid nodename:"+node.getNodeName() );
    }

    dialog=parent;

    NamedNodeMap atts = node.getAttributes();
    for( int i=0; i<atts.getLength(); i++ ) 
    {
        Node att = atts.item(i);
        String name=att.getNodeName();
        String value=att.getNodeValue();

        if( name.equals("name") )      
        {
            this.name=value; 
        }
        else if( name.equals("alignx"))
        {
            double alignx=0.5;
                 if( value.equals("center") )   alignx=0.5; 
            else if( value.equals("left") )     alignx=0.0;   
            else if( value.equals("right") )    alignx=1.0;
            setAlignmentX((float)alignx);
        }
    }

    ButtonGroup bg=new ButtonGroup();

    boolean flush=true;

    setFloatable(false);

    for( Node child=node.getFirstChild(); child!=null; child=child.getNextSibling() ) 
    {
        String itype=child.getNodeName();

        if( itype.equals("orientation") )
        {
            String o=jterminal.getTextContent(child);
            if( o.startsWith("v") )
            {
                setOrientation(VERTICAL);
            }
            else if( o.startsWith("h") )
            {
                setOrientation(HORIZONTAL); //default
            }
        }

        else if( itype.equals("floatable") )
        {
            String o=jterminal.getTextContent(child);
            setFloatable(o.startsWith("t"));
        }

        else if( itype.equals("jtlabel") )
        {
            jtlabel c=new jtlabel(dialog,child);
            itemlist.add(c);
            add(c); 
        }

        else if( itype.equals("jtprogbar") )
        {
            jtprogbar c=new jtprogbar(dialog,child);
            itemlist.add(c); 
            add(c); 
        }
 
        else if( itype.equals("jtslider") )
        {
            jtslider c=new jtslider(dialog,child);
            itemlist.add(c); 
            add(c);
        }

        else if( itype.equals("jtpush") )
        {
            jtpush c=new jtpush(dialog,child);
            itemlist.add(c); 
            add(c);
        }
 
        else if( itype.equals("jtcheck") )
        {
            jtcheck c=new jtcheck(dialog,child);
            itemlist.add(c); 
            add(c); 
        }

        else if( itype.equals("jtradio") )
        {
            jtradio c=new jtradio(dialog,child);
            itemlist.add(c); 
            bg.add(c);
            add(c); 
        }

        else if( itype.equals("jtget") )
        {
            jtget c=new jtget(dialog,child);
            itemlist.add(c); 
            add(c); 
        }

        else if( itype.equals("jttextarea") )
        {
            jttextarea c=new jttextarea(dialog,child);
            itemlist.add(c); 
            add(c.getScrollPane());
        }

        else if( itype.equals("jthtmlarea") )
        {
            jthtmlarea c=new jthtmlarea(dialog,child);
            itemlist.add(c); 
            add(c.getScrollPane()); 
        }

        else if( itype.equals("jttree") )
        {
            jttree c=new jttree(dialog,child);
            itemlist.add(c); 
            add(c.getScrollPane()); 
        }
 
        else if( itype.equals("jtpassw") )
        {
            jtpassw c=new jtpassw(dialog,child);
            itemlist.add(c); 
            add(c); 
        }
 
        else if( itype.equals("jtcombo") )
        {
            jtcombo c=new jtcombo(dialog,child);
            itemlist.add(c); 
            add(c); 
        }

        else if( itype.equals("hglue") )
        {
            add(Box.createHorizontalGlue());
            flush=false;
        }

        else if( itype.equals("vglue") )
        {
            add(Box.createVerticalGlue());
            flush=false;
        }

        addSeparator(new Dimension(4,4));
    }
    
    if( flush )
    {
        add(Box.createHorizontalGlue());
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

}
 
//--------------------------------------------------------------------------- 
public void xmlreset()
{

}
 
//---------------------------------------------------------------------------
public boolean isEscape()
{
    return false;
}

//---------------------------------------------------------------------------
public String getName()
{
    return name;
}

//--------------------------------------------------------------------------- 
public void message(Node msg)
{
}
 
//--------------------------------------------------------------------------- 
public void buildvarlist()
{
    if( !name.equals("") )
    {
        dialog.varlist.add(this);
    }
    for( int i=0; i<itemlist.size(); i++)
    {
        ((xmlcomponent)itemlist.get(i)).buildvarlist();
    }
}

//--------------------------------------------------------------------------- 
} 