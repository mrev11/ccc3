
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
import javax.swing.event.*;
import org.w3c.dom.*;
import java.util.*;
 
//===========================================================================
public class jtsplitpane
extends splitpanefield
implements xmlcomponent//, ChangeListener
{
//===========================================================================

public jtparam param=null;

public int divider=0;
public jtdialog dialog=null; 
private ArrayList itemlist=new ArrayList();
 
//--------------------------------------------------------------------------- 
jtsplitpane(jtdialog parent, Node node)
{
    dialog=parent;

    param=new jtparam(node,"jtsplitpane");
    //param.list();
    param.setAlignXY(this);

    resize(param.left,param.top,param.right-param.left+1,param.bottom-param.top+1);

    for( Node child=node.getFirstChild(); child!=null; child=child.getNextSibling() ) 
    {
        String itype=child.getNodeName();

        if( itype.equals("orientation") )
        {
            String o=jterminal.getTextContent(child);
        
            if( o.startsWith("v") )
            {
                setOrientation(JSplitPane.VERTICAL_SPLIT);
            }
            else if( o.startsWith("h") ) 
            {
                setOrientation(JSplitPane.HORIZONTAL_SPLIT);
            }
        }

        else if( itype.equals("divider") )
        {
            divider=jterminal.parseInt(jterminal.getTextContent(child));
        }
 
        else if( itype.equals("jtpanel") )
        {
            jtpanel c=new jtpanel(dialog,child);
            //setcomponent(c.scrollpane==null?c:c.scrollpane);//ez nem jó
            setcomponent(c);
        }

        else if( itype.equals("jtsplitpane") )
        {
            jtsplitpane c=new jtsplitpane(dialog,child);
            setcomponent(c);
        }

        else if( itype.equals("jtlabel") )
        {
            jtlabel c=new jtlabel(dialog,child);
            setcomponent(c);
        }

        else if( itype.equals("jttable") )
        {
            jttable c=new jttable(dialog,child);
            //setcomponent(c.scrollpane==null?c:c.scrollpane);//ez nem jó
            setcomponent(c);
        }

        else if( itype.equals("jttextarea") )
        {
            jttextarea c=new jttextarea(dialog,child);
            //setcomponent(c.scrollpane==null?c:c.scrollpane);//ez nem jó
            setcomponent(c);
        }

        else if( itype.equals("jthtmlarea") )
        {
            jthtmlarea c=new jthtmlarea(dialog,child);
            //setcomponent(c.scrollpane==null?c:c.scrollpane);//ez nem jó
            setcomponent(c);
        }

        else if( itype.equals("jttree") )
        {
            jttree c=new jttree(dialog,child);
            setcomponent(c);
        }
    }
    
    if( divider!=0 )
    {
        //a szerver karaktermeretben adja meg a divider  
        //poziciojat, amit at kell konvertalni pixelre

        if( getOrientation()==JSplitPane.VERTICAL_SPLIT )
        {
            setDividerLocation( (int)(divider*getutil.getposition.getFontSize()) );
        }
        else
        {
            setDividerLocation( (int)(divider*getutil.getposition.getFontWidth()) );
        }
    }
}

//--------------------------------------------------------------------------- 
private void setcomponent( Component c )
{
    //a dokumentacio szerint setTopComponent() <--> setLeftComponent() 
    //a dokumentacio szerint setBottomComponent() <--> setRightComponent() 
    //ezert nincs szukseg kulon programagra
    
    //a tapasztalat szerint JScrollPane ilyen alkalmazasa mellett,
    //a berakott jtpanel vscroll es hscroll attributumaival lehet
    //szabalyozni a scrollbarokat

    if( itemlist.size()==0 )
    {
        if( c instanceof javax.swing.JSplitPane  )
        {
            setTopComponent(c); 

            //ha egy splitpane-t tovabb osztunk,
            //(azaz ujabb splitpane-t teszunk bele)
            //akkor el kell kerulni a scrollbarok duplazodasat
        }
        else
        {
            setTopComponent(new JScrollPane(c));
        }
    }
    else
    {
        if( c instanceof javax.swing.JSplitPane  )
        {
            setBottomComponent(c);
        }
        else
        {
            setBottomComponent(new JScrollPane(c));
        }
    }

    itemlist.add(c);
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
} 
