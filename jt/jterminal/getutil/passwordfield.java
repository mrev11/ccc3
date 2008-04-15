
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
public class passwordfield  
extends javax.swing.JPasswordField 
{
//===========================================================================

private static int fontsize=getutil.getposition.getFontSize();
private static int fontwidth=getutil.getposition.getFontWidth();

private int pixelwidth=0;
private int pixelheight=0;


//---------------------------------------------------------------------------
public passwordfield()
{
    setFont( getutil.getposition.getDefaultMonoFont() );
}

//---------------------------------------------------------------------------
public passwordfield(int x, int y, int w)
{
    this();
    resize(x,y,w);
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
    return getPreferredSize();
}
 
//----------------------------------------------------------------------------
}

