
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

import java.awt.*;
import javax.swing.*;

//============================================================================
public class progbarfield
extends javax.swing.JProgressBar
{
//============================================================================
private static int fontsize=getutil.getposition.getFontSize();
private static int fontwidth=getutil.getposition.getFontWidth();

private int pixelwidth=0;
private int pixelheight=0;

//----------------------------------------------------------------------------
public progbarfield()
{
    setFont( getutil.getposition.getDefaultDlgFont() );
}

//----------------------------------------------------------------------------
public progbarfield(int x, int y, int w)
{
    this();
    resize(x,y,w);
}
 
//----------------------------------------------------------------------------
public progbarfield(int x, int y, int w, int h)
{
    this();
    resize(x,y,w,h);
}

//----------------------------------------------------------------------------
public void resize(int x, int y, int w)
{
    resize(x,y,w,2);
}

//----------------------------------------------------------------------------
public void resize(int x, int y, int w, int h)
{
    int xpos=getutil.getposition.xpos(x);
    int ypos=getutil.getposition.ypos(y);
    int xsiz=getutil.getposition.xpos(w);
    int ysiz=getutil.getposition.ypos(h);

    ypos+=2;
    ysiz-=5;

    pixelwidth=xsiz;
    pixelheight=ysiz;

    setSize(xsiz,ysiz);
    setLocation(xpos,ypos); 
}

//----------------------------------------------------------------------------
public Dimension getPreferredSize()
{
    Dimension d=super.getPreferredSize();
    d.width=pixelwidth>d.width ? pixelwidth:d.width;
    d.height=pixelheight>d.height ? pixelheight:d.height;
    return d;
}

public Dimension getMinimumSize()
{
    return getPreferredSize();
}

public Dimension getMaximumSize()
{
    Dimension d=super.getMaximumSize();
    d.width=pixelwidth>d.width ? pixelwidth:d.width;
    d.height=pixelheight>d.height ? pixelheight:d.height;
    return d;
}

//----------------------------------------------------------------------------
}

 