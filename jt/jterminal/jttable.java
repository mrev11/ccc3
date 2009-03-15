
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
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;
import java.awt.event.*;
import org.w3c.dom.*;

import javax.swing.border.*;
import javax.swing.BorderFactory; 
 
//===========================================================================
public class jttable
extends tablefield
implements xmlcomponent, getcolor,getfont
{
//===========================================================================

public jtparam param=null;

private Vector header=new Vector(0);
private Vector data=new Vector(0); 
private Vector colortable=null; 
private ArrayList changelist=new ArrayList();
private jtmodel model;

private scrollfield scrollpane=null;
public jtdialog dialog=null; 
public String  lastsend=null;
private Node selection=null;

//--------------------------------------------------------------------------- 
jttable(jtdialog parent, Node node)
{
    dialog=parent;

    param=new jtparam(node,"jttable");
    //param.list();

    param.setAlignXY(this); 
    param.setBorder(this);
    param.setEnabled(this);
    param.setToolTip(this);
 
    for( Node child=node.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();

        if( name.equals("jtcolumn") )
        {
            header.addElement(readcolumn(child));
        }

        else if( name.equals("r") )
        {
            data.addElement(readdatarow(child));
        }

        else if( name.equals("sel") )
        {
            this.selection=child;
        }

        else if( name.equals("colortable") )
        {
            this.colortable=new Vector(0);
            for( Node color=child.getFirstChild(); color!=null; color=color.getNextSibling() )
            {
                int r=0;
                int g=0;
                int b=0;
                for( Node rgb=color.getFirstChild(); rgb!=null; rgb=rgb.getNextSibling() )
                {
                    String rgbname=rgb.getNodeName();
                    if( rgbname.equals("r") )
                    {
                        r=Integer.parseInt(jterminal.getTextContent(rgb));
                    }
                    else if( rgbname.equals("g") )
                    {
                        g=Integer.parseInt(jterminal.getTextContent(rgb));
                    }
                    else if( rgbname.equals("b") )
                    {
                        b=Integer.parseInt(jterminal.getTextContent(rgb));
                    }
                }
                this.colortable.addElement(new Color(r,g,b));
            }
        }
    }

    setModel( model=new jtmodel() );
    
    //Mi a szine a default renderer kivalasztott hatterenek?
    //TableCellRenderer r=getDefaultRenderer("".getClass());
    //Component c=r.getTableCellRendererComponent(this,"",true,false,0,0);
    //jterminal.out.println(c.getBackground());
    
    //Hogyan lehet beallitani egy oszlop rendererjet?
    //TableColumn c=getColumnModel().getColumn(1); 
    //c.setCellRenderer(new picturefield("@R! XXXXXXXX-XXXXXXXX"));
 
    for( int i=0; i<header.size(); i++) 
    {
        //cellak szelessegenek/picture-jenek beallitasa
        TableColumn column=getColumnModel().getColumn(i); 
        jtcolumn hdr=(jtcolumn)header.elementAt(i);
        column.setPreferredWidth( (1+hdr.width)*fontwidth );
 
        if( hdr.type.equals("L") )
        {
            //if( "CUSTOMIZED_BOOLEAN_RENDERER"==null )
            {
                //A DefaultTableCellRenderer megjelenito komponense
                //mindig (fixen) egy JLabel, ezt orokles utan atdefinialjuk
                //egy checkboxra. Ha a getTableCellRendererComponent 
                //metodust nem definialom at, akkor a mezo true/false
                //szoveges kiirassal jelenik meg. 
            
                //Ha a cellrenderert egyaltalan nem piszkalom, akkor 
                //a JTable olyan renderert hasznal (JTable$BooleanRenderer),
                //ami checkboxkent jelenik meg, de nem nutatja, 
                //hogy mikor van kivalasztva.
                //jterminal.out.println(getCellRenderer(0,i).getClass().getName()); 
            

                DefaultTableCellRenderer r=new DefaultTableCellRenderer()
                {
                    private JCheckBox cb=new JCheckBox();
 
                    public Component getTableCellRendererComponent
                        (JTable table, Object value, 
                            boolean isSelected, boolean hasFocus, int row, int col )
                    {
                        cb.setHorizontalAlignment(JLabel.CENTER);
                        cb.setBorder(cellcolor.FBORDER);
                        cb.setBorderPainted( hasFocus && isCellEditable(row,col) );
                        //cb.setBackground( isSelected ? (hasFocus?cellcolor.FOCUS:cellcolor.SELECT) : cellcolor.NORMAL);

                        if( isSelected )
                        {
                            cb.setBackground( hasFocus?cellcolor.FOCUS:cellcolor.SELECT );
                        }
                        else
                        {
                            Color bg=((getcolor)table).getBgColorAt(row,col);
                            cb.setBackground( bg!=null?bg:cellcolor.DEFBGR );
                        }
                        
                        cb.setSelected(((Boolean)value).booleanValue());
                        return cb;
                    }              
                };
                column.setCellRenderer(r); 
            }
            
            //if( "CUSTOMIZED_BOOLEAN_EDITOR"==null  )
            {
                //A DefaultTableCellEditor konstruktoraban megadhato 
                //nehany komponensfajta, amiben az editalas tortenik. 
                //Itt csak atallitjuk ClickCountToStart erteket 1-rol 2-re.
                   
                JCheckBox cb=new JCheckBox();
                cb.setHorizontalAlignment(JLabel.CENTER);
                DefaultCellEditor e=new DefaultCellEditor(cb);
                e.setClickCountToStart(2); 
                column.setCellEditor(e); 
            }
        }

        else
        {
            //Minden nem Boolean mezőt a picturefield editál.
            //Külön objektumot kell rakni az editorba és a rendererbe.
            //jterminal.out.print(hdr.name);
            //jterminal.out.print(" ");
            //jterminal.out.println(hdr.picture);
            
            column.setCellEditor(new picturefield(hdr.picture)); 
            column.setCellRenderer(new picturefield(hdr.picture)); 
        }
    }

    //setIntercellSpacing(new Dimension(1,1)); //nem jol mukodik!
    setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
    scrollpane=new scrollfield(param.left,param.top,param.right-param.left+1,param.bottom-param.top+1,this);
    
    if( selection!=null )
    {
        this.xmlset(selection);
        this.selection=null;
    }
}

//--------------------------------------------------------------------------- 
public JComponent getScrollPane()
{
    return scrollpane==null?(JComponent)this:(JComponent)scrollpane;
}

//---------------------------------------------------------------------------
private jtcolumn readcolumn(Node node)
{
    String  nam=null;
    String  typ="C";
    int     wid=16;
    String  pic=null;
    boolean edi=false;

    for( Node child=node.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();

             if(name.equals("name"))     nam=jterminal.getTextContent(child);
        else if(name.equals("type"))     typ=jterminal.getTextContent(child);
        else if(name.equals("picture"))  pic=jterminal.getTextContent(child); 
        else if(name.equals("width"))    wid=jterminal.parseInt(jterminal.getTextContent(child));
        else if(name.equals("editable")) edi=true;
    }

    return new jtcolumn(nam,typ,wid,pic,edi);
}

//---------------------------------------------------------------------------
private Vector readdatarow(Node node)
{
    NodeList cl=node.getChildNodes();
    Vector row=new Vector(cl.getLength());

    for( int i=0; i<cl.getLength(); i++ )
    {
        String x=jterminal.getTextContent(cl.item(i));
        jtcolumn h=(jtcolumn)header.elementAt(i);
        jtcelldata o=null;
        
        if( h.type.equals("C") )
        {
            o=new jtcelldata(x);
        }
        else if( h.type.equals("N") )
        {
            o=new jtcelldata(x); //nem szabad szamra konvertalni!
        }
        else if( h.type.equals("D") )
        {
            o=new jtcelldata(x);
        }
        else if( h.type.equals("L") )
        {
            o=new jtcelldata(new Boolean(x.equals("t")));
        }

        NamedNodeMap atts=cl.item(i).getAttributes();
        for( int j=0; j<atts.getLength(); j++ ) 
        {
            Node att = atts.item(j);
            String attname=att.getNodeName();
            String attvalue=att.getNodeValue();
            if( attname.equals("fg") )
            {
                o.fg=Integer.parseInt(attvalue);
            }
            else if( attname.equals("bg") )
            {
                o.bg=Integer.parseInt(attvalue);
            }
            else if( attname.equals("sty") )
            {
                o.style=Integer.parseInt(attvalue);
            }       
            else if( attname.equals("fam") )
            {
                o.family=Integer.parseInt(attvalue);
            }       
        }

        row.addElement(o);
    }

    return row;
}

//--------------------------------------------------------------------------- 
public String xmlget()
{
    if( isEditing() )
    {
        ((picturefield)getEditorComponent()).stopCellEditing(); 
    }

    String x;
    int[] sr=getSelectedRows();

    x="<"+param.name+">";

    x+="<sel>";
    if( sr.length>0 )
    {
        for( int i=0; i<sr.length; i++ )
        {
            if(i>0)
            {
                x+=",";
            }
            x+=Integer.toString(1+sr[i]);  //a Java 0-tol, a CCC 1-tol szamoz
        }
    }
    x+="</sel>";
 
    if( changelist.size()>0 )
    {
        Object[] changes=changelist.toArray();
        Arrays.sort(changes, new jtcompare());
        for( int i=0; i<changes.length; i++ )
        {
            jtcellchange c=(jtcellchange)changes[i];
            x+=c.xmlout();
        }
        changelist.clear();
    }


    x+="</"+param.name+">";

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
    String b,x=jterminal.getTextContent(data); 
    ListSelectionModel lsm=getSelectionModel();
    lsm.clearSelection();
    
    while( x.length()>0 )
    {
        int p=x.indexOf(',');
        
        if( p>0 )
        {
            b=x.substring(0,p);   //eleje
            x=x.substring(p+1);   //maradek
        }
        else if( p<0 )
        {
            b=x;                  //eleje 
            x="";                 //maradek 
        }
        else
        {
            break;                //hibas
        }

        try
        {
            int i=jterminal.parseInt(b)-1; //a Java 0-tol szamol 
            lsm.addSelectionInterval(i,i);
        }
        catch( Exception e )
        {
            break;                //hibas 
        }
    }

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
public void message(Node msg)  //jtmessage uzenet feldolgozasa
{
    jtchange change=new jtchange(msg);
    change.setFocus(this);
    change.setFocusable(param);
    change.setToolTip(this,param);
    change.setEnabled(this,param);

    for( Node c=msg.getFirstChild(); c!=null; c=c.getNextSibling() )
    {
        String name=c.getNodeName();
    
        if( name.equals("setpage") )
        {
            data= new Vector(0);

            for( Node r=c.getFirstChild(); r!=null; r=r.getNextSibling() )
            {
                if( r.getNodeName().equals("r") )
                {
                    data.addElement(readdatarow(r));
                }
            }
            resizeAndRepaint();
        }

        else if( name.equals("setrow") )
        {
            int index=0;

            for( Node r=c.getFirstChild(); r!=null; r=r.getNextSibling() )
            {
                if( r.getNodeName().equals("index") )
                {   
                    index=Integer.parseInt(jterminal.getTextContent(r))-1;
                }
                else if( r.getNodeName().equals("r") )
                {
                    data.set(index,readdatarow(r));
                }
            }
            resizeAndRepaint();
        }
    }
}

//--------------------------------------------------------------------------- 
// getfont interface
//--------------------------------------------------------------------------- 
public Font getFontAt(int row, int col)
{       
    jtcelldata cd=(jtcelldata)((Vector)data.elementAt(row)).elementAt(col);
    return getutil.getposition.createSmallFont(cd.family,cd.style);
}

//--------------------------------------------------------------------------- 
// getcolor interface
//--------------------------------------------------------------------------- 
public Color getFgColorAt(int row, int col)
{
    Color c=null;
    int x=((jtcelldata)((Vector)data.elementAt(row)).elementAt(col)).fg; 
    
    if( colortable!=null && 1<=x && x<=colortable.size() )
    {
        c=(Color)colortable.elementAt(x-1);
    }
    return c;
}

public Color getBgColorAt(int row, int col)
{
    Color c=null;
    int x=((jtcelldata)((Vector)data.elementAt(row)).elementAt(col)).bg; 
    
    if( colortable!=null && 1<=x && x<=colortable.size() )
    {
        c=(Color)colortable.elementAt(x-1);
    }
    return c;
}


//--------------------------------------------------------------------------- 
public void buildvarlist()
{
    dialog.varlist.add(this);
}
 
//===========================================================================
private class jtmodel extends AbstractTableModel {
//===========================================================================

//--------------------------------------------------------------------------- 
public int getColumnCount() 
{ 
    return header.size(); 
}

//--------------------------------------------------------------------------- 
public int getRowCount() 
{ 
    return data.size(); 
}

//--------------------------------------------------------------------------- 
public Object getValueAt(int row, int col)
{ 
    return ((jtcelldata)((Vector)data.elementAt(row)).elementAt(col)).data; 
}

//---------------------------------------------------------------------------
public void setValueAt(Object value, int row, int col) 
{
    //Az uj erteket csak akkor taroljuk, 
    //ha az tartalmilag is valtozott,
    //es formailag megfelel a picture-nek.
    
    String type=((jtcolumn)header.elementAt(col)).type;
    String vold=getValueAt(row,col).toString().trim();
    String vnew=value.toString().trim();

    if( vold.equals(vnew) )
    {
        //jterminal.out.println("nem valtozott a tartalom");
    }
    else if( type.equals("N") &&  
             (Double.parseDouble(vold)==Double.parseDouble(vnew)) )
    {
        //jterminal.out.println("nem valtozott (type==N)");
    }
    else if( (getEditorComponent() instanceof picturefield) &&
                 !((picturefield)getEditorComponent()).verify() )
    {
        //jterminal.out.println("formailag nem megfelelo a tartalom");
    }
    else
    {
        //jterminal.out.print("["+vold+"]");
        //jterminal.out.print("-->");
        //jterminal.out.println("["+vnew+"]");

        int i=0; 
        for( ; i<changelist.size(); i++ )
        {
            jtcellchange c=(jtcellchange)changelist.get(i);
            if( c.row==row && c.col==col )
            {
                c.newval=value;
                break;
            }
        }

        if( i>=changelist.size() )
        {
            changelist.add( new jtcellchange(row,col,getValueAt(row,col),value) );
        }

        ((jtcelldata)((Vector)data.elementAt(row)).elementAt(col)).data=value; 
        fireTableCellUpdated(row, col);
    }
}

//--------------------------------------------------------------------------- 
public String getColumnName(int col)
{ 
    return ((jtcolumn)header.elementAt(col)).name; 
}

//--------------------------------------------------------------------------- 
public boolean isCellEditable(int row, int col) 
{
    return ((jtcolumn)header.elementAt(col)).editable;  
}
 
//--------------------------------------------------------------------------- 
public Class getColumnClass(int c) 
{
    return ((jtcolumn)header.elementAt(c)).colclass;
}
 
//--------------------------------------------------------------------------- 
} //class jtmodel 


//===========================================================================
private class jtcellchange{
//===========================================================================

int row;
int col;
Object oldval=null;
Object newval=null;

//--------------------------------------------------------------------------- 
public jtcellchange(int r, int c, Object vold, Object vnew)
{
    row=r;
    col=c;
    oldval=vold;
    newval=vnew;
}

//--------------------------------------------------------------------------- 
public String xmlout()
{
    return  "<change>"+
            "<r>"+Integer.toString(row+1)+"</r>"+  
            "<c>"+Integer.toString(col+1)+"</c>"+
            "<from>"+jterminal.cdataif(oldval.toString().trim())+"</from>"+
            "<to>"+jterminal.cdataif(newval.toString().trim())+"</to>"+
            "</change>";
}

//--------------------------------------------------------------------------- 
} //class jtcellchange
 

//===========================================================================
private class jtcompare implements Comparator{
//===========================================================================
 
//--------------------------------------------------------------------------- 
public int compare(Object o1, Object o2)
{
    jtcellchange c1=(jtcellchange)o1;
    jtcellchange c2=(jtcellchange)o2;

    if( c1.row<c2.row )   
        return -1;
    else if( c2.row<c1.row )   
        return 1;
    else if( c1.col<c2.col )   
        return -1;
    else if( c2.col<c1.col )   
        return 1;
    else
        return 0;
}

//--------------------------------------------------------------------------- 
} //class jtcompare


//===========================================================================
private class jtcolumn {
//===========================================================================
 
public String  name=null;
public String  type="C";
public int     width=16;
public boolean editable=false;
public String  picture=null;
public Class   colclass=null;
 
//--------------------------------------------------------------------------- 
public jtcolumn(String n, String t, int w, String p, boolean e)
{
    name=n;
    type=t;
    width=w;
    picture=p;
    editable=e;

         if( t.equals("C") )  colclass=String.class;
    else if( t.equals("D") )  colclass=String.class;
    else if( t.equals("N") )  colclass=String.class; //nem szam! 
    else if( t.equals("L") )  colclass=Boolean.class;
    else                      colclass=Object.class;
    
    //jterminal.out.println(this);
}

//--------------------------------------------------------------------------- 
public String toString()
{
    String x;
    x="{";
    x+="name="+name+",";
    x+="type="+type+",";
    x+="width="+Integer.toString(width)+",";
    x+="picture="+picture+",";
    x+="editable="+(editable?"t":"f");
    x+="}";
    return x;
}

//--------------------------------------------------------------------------- 
} //class jtcolumn

//===========================================================================
private class jtcelldata {
//===========================================================================
 
public Object  data=null;
public int     fg=0;        //color index, 0=default
public int     bg=0;        //color index, 0=default
public int     family=0;    //0=default
public int     style=0;     //0=default

//--------------------------------------------------------------------------- 
public jtcelldata(Object celldata)
{
    data=celldata;
    fg=0;
    bg=0;
    family=0;
    style=0;
}

//--------------------------------------------------------------------------- 
public String toString()
{
    return this.data.toString();
}

//--------------------------------------------------------------------------- 
} //class jtcelldata



//--------------------------------------------------------------------------- 
} //class jtable
 
