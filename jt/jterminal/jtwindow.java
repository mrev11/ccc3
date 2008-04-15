
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

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
 
//===========================================================================
public class jtwindow {
//===========================================================================

public Window wnd; 
protected boolean frame=false;
protected int prefw=0;
protected int prefh=0;
 

//----------------------------------------------------------------------------
jtwindow()
{
    frame=true;
    wnd=new jtf();
}

//----------------------------------------------------------------------------
jtwindow(jtdialog parent)
{
    frame=false;
    if( parent.frame ) 
    {
        wnd=new jtd( (JFrame)(parent.wnd) );
    }
    else
    {
        wnd=new jtd( (JDialog)(parent.wnd) );
    }
}
 
//----------------------------------------------------------------------------
public void show()
{
    wnd.show();
}

//----------------------------------------------------------------------------
public void pack()
{
    wnd.pack();
}


//----------------------------------------------------------------------------
public void setEnabled(boolean flag)
{
    if( frame )
    {
        ((JFrame)wnd).setEnabled(flag);
    }
    else
    {
        ((JDialog)wnd).setEnabled(flag); 
    }
}

public boolean isEnabled()
{
    boolean flag;
    if( frame )
    {
        flag=((JFrame)wnd).isEnabled();
    }
    else
    {
        flag=((JDialog)wnd).isEnabled(); 
    }
    return flag;
}


//----------------------------------------------------------------------------
public void setFocusable(boolean flag)
{
    if( frame )
    {
        ((JFrame)wnd).setFocusable(flag);
    }
    else
    {
        ((JDialog)wnd).setFocusable(flag); 
    }
}

public boolean isFocusable()
{
    boolean flag;
    if( frame )
    {
        flag=((JFrame)wnd).isFocusable();
    }
    else
    {
        flag=((JDialog)wnd).isFocusable(); 
    }
    return flag;
}

//----------------------------------------------------------------------------
public void setTitle(String title)
{
    if( frame )
    {
        ((JFrame)wnd).setTitle(title);
    }
    else
    {
        ((JDialog)wnd).setTitle(title); 
    }
}
 

//----------------------------------------------------------------------------
public Container getContentPane()
{
    if( frame )
    {
        return ((JFrame)wnd).getContentPane();
    }
    else
    {
        return ((JDialog)wnd).getContentPane();
    }
}

//----------------------------------------------------------------------------
public JMenuBar getJMenuBar()
{
    if( frame )
    {
        return ((JFrame)wnd).getJMenuBar();
    }
    else
    {
        return ((JDialog)wnd).getJMenuBar();
    }
}

//----------------------------------------------------------------------------
public void setJMenuBar(JMenuBar jmb)
{
    if( frame )
    {
        ((JFrame)wnd).setJMenuBar( jmb );
    }
    else
    {
        ((JDialog)wnd).setJMenuBar( jmb );
    }
}

//----------------------------------------------------------------------------
public void addWindowListener( WindowAdapter wa )
{
    wnd.addWindowListener(wa);
}

//----------------------------------------------------------------------------
public void setDefaultCloseOperation( int op )
{
    if( frame )
    {
        ((JFrame)wnd).setDefaultCloseOperation( op );
    }
    else
    {
        ((JDialog)wnd).setDefaultCloseOperation( op );
    }
}
 

//----------------------------------------------------------------------------
public Point getLocationOnScreen()
{
    return wnd.getLocationOnScreen();
}

//----------------------------------------------------------------------------
public GraphicsConfiguration getGraphicsConfiguration()
{
    return wnd.getGraphicsConfiguration();
}

//----------------------------------------------------------------------------
public void setSize(int x, int y)
{
    wnd.setSize(x,y);
}

//----------------------------------------------------------------------------
public void setLocation( int x, int y )
{
    wnd.setLocation( x, y );
}

//----------------------------------------------------------------------------
public void setLocationRelativeTo( jtdialog dlg )
{
    wnd.setLocationRelativeTo( dlg==null ? null:dlg.wnd );
}

//----------------------------------------------------------------------------
private class jtf extends JFrame {
//----------------------------------------------------------------------------

public Dimension getPreferredSize()
{
    return new Dimension(prefw,prefh); 
}

//---------------------------------------------------------------------------- 
} //end of jtf

//----------------------------------------------------------------------------
private class jtd extends JDialog {
//----------------------------------------------------------------------------

jtd(JFrame jf)
{
    super(jf);
}

jtd(JDialog jd)
{
    super(jd);
}

public Dimension getPreferredSize()
{
    return new Dimension(prefw,prefh); 
}

 
//---------------------------------------------------------------------------- 
} //end of jtd
 

//----------------------------------------------------------------------------
}  

