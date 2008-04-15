
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

package getutil;

import javax.swing.event.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.text.*;

import javax.swing.table.*;
import javax.swing.border.*;
import javax.swing.BorderFactory; 
import java.util.EventObject;
 
 
//===========================================================================
public class picturefield  
extends  javax.swing.JTextField 
implements ActionListener, TableCellRenderer, TableCellEditor, Runnable
{
//===========================================================================

private static int fontsize=getutil.getposition.getFontSize();
private static int fontwidth=getutil.getposition.getFontWidth();

private int pixelwidth=0;
private int pixelheight=0;

protected boolean expand=false;

//CellEditor alkatreszek
protected EventListenerList listenerList=new EventListenerList();
transient protected ChangeEvent changeEvent=null;

protected int clickCountToStart = 1;
 
//---------------------------------------------------------------------------
public picturefield()
{
    setFont( getutil.getposition.getDefaultMonoFont() );
    addActionListener(this);
}

//---------------------------------------------------------------------------
public picturefield(int x, int y, int w)
{
    this();
    resize(x,y,w);
}

//---------------------------------------------------------------------------
public picturefield(String p)
{
    this();
    setPicture(p);
}

//----------------------------------------------------------------------------
public void run()
{
    requestFocus();
}
 
//---------------------------------------------------------------------------
public void resize(int x, int y, int w)
{
    pixelwidth=w*fontwidth+(int)(0.6*fontwidth);
    pixelheight=getutil.getposition.ypos(1)-2;
    setLocation(getutil.getposition.xpos(x)-(int)(0.3*fontwidth),getutil.getposition.ypos(y)+1);
    setSize(pixelwidth,pixelheight);
}

//---------------------------------------------------------------------------
public Dimension getPreferredSize()
{
    return new Dimension(pixelwidth,pixelheight); 
}
//---------------------------------------------------------------------------
public Dimension getMinimumSize()
{
    return getPreferredSize();
}
//---------------------------------------------------------------------------
public Dimension getMaximumSize()
{
    Dimension maxsize=getPreferredSize();
    if( expand )
    {
        Dimension ms=super.getMaximumSize();
        maxsize.width=ms.width;
        //maxsize.height=ms.height;
    }
    return maxsize;
}
 
//---------------------------------------------------------------------------
public void setPicture(String picture)
{
    if( picture==null )
    {
        setDocument( new pictnulldocument(this) );
    }
    else
    {
        setDocument( new picturedocument(this,picture) );
    }
}

//---------------------------------------------------------------------------
public String getText()
{
    String text="";
    if( getDocument() instanceof picturedocument )
    {
        text=((picturedocument)getDocument()).getText();
    }
    else if( getDocument() instanceof pictnulldocument )
    {
        text=((pictnulldocument)getDocument()).getText();
    }
    return text;
}

//---------------------------------------------------------------------------
public void setText(String t)
{
    super.setText(t);
    normalize();
    setCaretPosition(0); //2006.08.14
}
 
//---------------------------------------------------------------------------
public boolean verifyX()
{
    boolean v=false;
    if( getDocument() instanceof picturedocument )
    {
        v=((picturedocument)getDocument()).verifyX();
    }
    return v;
}

//---------------------------------------------------------------------------
public boolean verifyF()
{
    boolean v=false;
    if( getDocument() instanceof picturedocument )
    {
        v=((picturedocument)getDocument()).verifyF();
    }
    return v;
}

//---------------------------------------------------------------------------
public boolean verify()  
{
    boolean v=true;
    if( getDocument() instanceof picturedocument )
    {
        v=((picturedocument)getDocument()).verify();
    }
    return v;
}
 
//---------------------------------------------------------------------------
public void normalize()
{
    if( getDocument() instanceof picturedocument )
    {
        ((picturedocument)getDocument()).normalize();
    }
}

//--------------------------------------------------------------------------- 
public void actionPerformed(ActionEvent e)
{
    stopCellEditing();
    //System.out.println("picturefield.actionPerformed");
}

//--------------------------------------------------------------------------- 
// TableCellRenderer interface
//--------------------------------------------------------------------------- 
public Component getTableCellRendererComponent
    (JTable table, Object value, 
        boolean isSelected, boolean hasFocus, int row, int col )
{

    //setFont( getutil.getposition.getSmallMonoFont() );
    Font f=((getfont)table).getFontAt(row,col);
    if( f!=null)
    {
        setFont( f );
    }
    else
    {
        setFont( getutil.getposition.getSmallMonoFont() );
    }

    setBorder( (hasFocus && table.isCellEditable(row,col)) ? cellcolor.FBORDER : null ); 
    //setBackground( isSelected ? (hasFocus?cellcolor.FOCUS:cellcolor.SELECT) : cellcolor.NORMAL );

    Color fg=((getcolor)table).getFgColorAt(row,col);
    setForeground(fg!=null?fg:cellcolor.DEFFGR);

    if( isSelected )
    {
        setBackground( hasFocus?cellcolor.FOCUS:cellcolor.SELECT );
    }
    else
    {
        Color bg=((getcolor)table).getBgColorAt(row,col);
        setBackground( bg!=null?bg:cellcolor.DEFBGR );
    }
    
    setText(value.toString());
    return this;
}              

//--------------------------------------------------------------------------- 
// TableCellEditor interface
//--------------------------------------------------------------------------- 
public Component getTableCellEditorComponent
    (JTable table, Object value, 
        boolean isSelected, int row, int col )
{
    //setFont( getutil.getposition.getSmallMonoFont() );
    Font f=((getfont)table).getFontAt(row,col);
    if( f!=null)
    {
        setFont( f );
    }
    else
    {
        setFont( getutil.getposition.getSmallMonoFont() );
    }

    setBorder(cellcolor.FBORDER); 
    setBackground(cellcolor.NORMAL);
    setText(value.toString());
    //System.out.println("picturefield.getTableCellEditorComponent");
    SwingUtilities.invokeLater(this); //requestFocus();
    return this;
}              

//---------------------------------------------------------------------------
public void setClickCountToStart(int count) 
{
    clickCountToStart=count;
}

//----------------------------------------------------------------------------
public int getClickCountToStart() 
{
    return clickCountToStart;
}
 
//----------------------------------------------------------------------------
public Object  getCellEditorValue()  
{
    return getText();
}

//----------------------------------------------------------------------------
public boolean isCellEditable(EventObject anEvent) 
{
    if( anEvent instanceof MouseEvent ) 
    { 
        return ((MouseEvent)anEvent).getClickCount() >= clickCountToStart;
    }

    //return false; //csak egerrel
    return true; //billentyuvel is
}
 
//----------------------------------------------------------------------------
public boolean shouldSelectCell(EventObject anEvent) 
{ 
    return true; 
}
    
//----------------------------------------------------------------------------
public boolean stopCellEditing() 
{ 
    normalize();
    fireEditingStopped(); 
    return true;
}

//----------------------------------------------------------------------------
public void  cancelCellEditing() 
{ 
    fireEditingCanceled(); 
}

//----------------------------------------------------------------------------
public void addCellEditorListener(CellEditorListener l) 
{
    listenerList.add(CellEditorListener.class, l);
}

//----------------------------------------------------------------------------
public void removeCellEditorListener(CellEditorListener l) 
{
    listenerList.remove(CellEditorListener.class, l);
}

//----------------------------------------------------------------------------
public CellEditorListener[] getCellEditorListeners() 
{
    return (CellEditorListener[])listenerList.getListeners(CellEditorListener.class);
}

//----------------------------------------------------------------------------
protected void fireEditingStopped() 
{
    Object[] listeners = listenerList.getListenerList(); //not null!

    // Process the listeners last to first, 
    // notifying those that are interested in this event

    for( int i=listeners.length-2; i>=0; i-=2 ) 
    {
        if( listeners[i]==CellEditorListener.class ) 
        {
            if( changeEvent==null )
            {
                changeEvent=new ChangeEvent(this);
            }
            ((CellEditorListener)listeners[i+1]).editingStopped(changeEvent);
        }           
    }
}

//----------------------------------------------------------------------------
protected void fireEditingCanceled() 
{
    Object[] listeners=listenerList.getListenerList(); //not null!

    for( int i=listeners.length-2; i>=0; i-=2 ) 
    {
        if( listeners[i]==CellEditorListener.class ) 
        {
            if( changeEvent==null )
            {
                changeEvent=new ChangeEvent(this);
            }

            ((CellEditorListener)listeners[i+1]).editingCanceled(changeEvent);
        }           
    }
}

//----------------------------------------------------------------------------
}
