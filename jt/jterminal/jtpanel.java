
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
import javax.swing.*;
import org.w3c.dom.*;
import java.util.*;
 
//===========================================================================
public class jtpanel
extends panelfield
implements xmlcomponent, Scrollable
{
//===========================================================================

public jtparam param=null;

private scrollfield scrollpane=null;   //JScrollPane 
public JMenuBar menubar=null;
public jtdialog dialog=null; 

private ArrayList itemlist=new ArrayList();

//--------------------------------------------------------------------------- 
jtpanel(jtdialog parent, Node node)
{
    dialog=parent;
    build(node);
}

//--------------------------------------------------------------------------- 
private void build (Node node)
{
    param=new jtparam(node,"jtpanel");
    //param.list();
    
    param.setAlignXY(this); 
    param.setLayout(this);
    param.setBorder(this);

    ButtonGroup bg=new ButtonGroup();

    for( Node child=node.getFirstChild(); child!=null; child=child.getNextSibling() ) 
    {
        String itype=child.getNodeName();

        if( itype.equals("jtpanel") )
        {
            jtpanel c=new jtpanel(dialog,child);
            itemlist.add(c);
            add(c.getScrollPane());
        }

        else if( itype.equals("jtsplitpane") )
        {
            jtsplitpane c=new jtsplitpane(dialog,child);
            itemlist.add(c);
            add(c);
        }

        else if( itype.equals("jttabpane") )
        {
            jttabpane c=new jttabpane(dialog,child);
            itemlist.add(c);
            add(c);
        }
 
        else if( itype.equals("jttable") || itype.equals("jtbrowse") ) 
        {
            jttable c=new jttable(dialog,child);
            itemlist.add(c);
            add(c.getScrollPane());
        }

        else if( itype.equals("jttoolbar") ) 
        {
            jttoolbar c=new jttoolbar(dialog,child);
            itemlist.add(c);
            add(c);
        }
 
        else if( itype.equals("jtlabel") )
        {
            jtlabel c=new jtlabel(dialog,child);
            if( !c.param.name.equals("") )
            {
                itemlist.add(c);
            }
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
        }

        else if( itype.equals("vglue") )
        {
            add(Box.createVerticalGlue());
        }

        else if( itype.equals("jtmenu") ) 
        {
            if( menubar==null )
            {
                menubar=new javax.swing.JMenuBar(); 
            }
            jtmenu c=new jtmenu(dialog,child); 
            itemlist.add(c);
            menubar.add(c); 
        }
 
        else if( itype.equals("jtmenuitem") ) 
        {
            if( menubar==null )
            {
                menubar=new javax.swing.JMenuBar(); 
            }
            jtmenuitem c=new jtmenuitem(dialog,child); 
            itemlist.add(c);
            menubar.add(c); 
        }

        else if( itype.equals("jtmenusep") ) 
        {
            if( menubar==null )
            {
                menubar=new javax.swing.JMenuBar(); 
            }
            menubar.add(Box.createHorizontalGlue()); 
        }
    }


    int top=param.top;
    int left=param.left;
    int bottom=param.bottom;
    int right=param.right;

    resize(left,top,right-left+1,bottom-top+1);
    
    
    if( scrollpane==null )
    {
        //mindig készül scrollpane,
        //viszont a changeitem jtmessage után,
        //amikor újraépül a panel, 
        //már eleve van scrolpane,
        //amit nem szabad kicserélni,
        //ezért kell null-ra vizsgálni. 

        scrollpane=new scrollfield(left,top,right-left+1,bottom-top+1,this);
    }

    if( getBorder()!=null )
    {
        scrollpane.setBorder(null);
    }
}

//--------------------------------------------------------------------------- 
public JComponent getScrollPane()
{
    return scrollpane==null?(JComponent)this:(JComponent)scrollpane;
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
    for( Node child=msg.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();

        if( name.equals("control") )
        {
            //sajat nev
        }

        else if( name.equals("changeitem") )
        {
            removeAll();
            itemlist=new ArrayList(); 
            build(child.getFirstChild());
            dialog.buildvarlist();
        }
    }
}

//--------------------------------------------------------------------------- 
public void buildvarlist()
{
    if( !param.name.equals("") )
    {
        dialog.varlist.add(this);
    }
    for( int i=0; i<itemlist.size(); i++)
    {
        ((xmlcomponent)itemlist.get(i)).buildvarlist();
    }
}
 
//----------------------------------------------------------------------------
public Dimension getPreferredScrollableViewportSize()  
{
    return getPreferredSize();
}
 
//----------------------------------------------------------------------------
public int getScrollableUnitIncrement(Rectangle r, int o, int d)  
{
    return 5;
}

//----------------------------------------------------------------------------
public int getScrollableBlockIncrement(Rectangle r, int o, int d)   
{
    return 5;
}

//----------------------------------------------------------------------------
public boolean getScrollableTracksViewportWidth() 
{
    return !param.hscroll();
}

//----------------------------------------------------------------------------
public boolean getScrollableTracksViewportHeight() 
{
    return !param.vscroll();
}

//--------------------------------------------------------------------------- 
} 