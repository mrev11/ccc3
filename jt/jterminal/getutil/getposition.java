
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

import javax.swing.*;
import javax.swing.text.*;
import java.awt.*;
 
//============================================================================
public class getposition extends JTextField{
//============================================================================
 
private static final int FAM_MONO        =  1;
private static final int FAM_DIALOG      =  2;
private static final int FAM_DIALOGINPUT =  3;
private static final int FAM_SANSSERIF   =  4;
private static final int FAM_SERIF       =  5;

private static final int STY_PLAIN       =  1;
private static final int STY_BOLD        =  2;
private static final int STY_ITALIC      =  3;


static private int fontsize=0;
static private int fontwidth=0;

static private Font defaultmonofont;
static private Font smallmonofont; 
static private Font defaultboldfont;
static private Font smallboldfont;

static
{
    boolean highres=false;
    String jtresol=null;//System.getenv("JTRESOL"); //1.4.2-ben nem megy!
    
    //Az 1.4.2-ben a System.getenv(String) deprecated.
    //Lefordul, de runtime errorral elszáll, és azt ajánlja, 
    //hogy használjunk helyette -D opciót és getProperty-t.
    //Az 1.5.0-ban megint nem deprecated, és működik.
    //A végeredmény, hogy nem használható, ui. nem ismert,
    //hogy a felhasználónál milyen JRE van.
    //A kúrva anyjukat.
    
    if( jtresol==null )
    {
    }
    else if( jtresol.equals("high") )
    {
        highres=true;
    }
    else if( jtresol.equals("low") )
    {
        highres=false;
    }
    else
    {
        jtresol=null;
    }

    if( jtresol==null )
    {
        JWindow w=new JWindow();
        Rectangle screen=w.getGraphicsConfiguration().getBounds();
        w.dispose();
        highres=screen.width>1024;
    }

    //highres=false;

    if( highres )
    {
        fontsize=14;

        defaultmonofont = new Font("Monospaced",Font.PLAIN,fontsize);
        smallmonofont   = new Font("Monospaced",Font.PLAIN,fontsize-2);
        defaultboldfont = new Font("Dialog",Font.BOLD,fontsize-2);
        smallboldfont   = new Font("Dialog",Font.BOLD,fontsize-3);
    }
    else
    {
        fontsize=12;

        defaultmonofont = new Font("Monospaced",Font.PLAIN,fontsize);
        smallmonofont   = new Font("Monospaced",Font.PLAIN,fontsize-1);
        defaultboldfont = new Font("Dialog",Font.BOLD,fontsize-1); //?
        smallboldfont   = new Font("Dialog",Font.BOLD,fontsize-2); //?
    }

    //System.out.println(highres?"highres":"lowres");
    //System.out.println(screen.height);
    //System.out.println(screen.width);
}
 

//----------------------------------------------------------------------------
static public Font getDefaultDlgFont()
{
    return defaultboldfont;
}

//----------------------------------------------------------------------------
static public Font getSmallDlgFont()
{
    return smallboldfont;
}
 
//----------------------------------------------------------------------------
static public Font getDefaultMonoFont()
{
    return defaultmonofont;
}

//----------------------------------------------------------------------------
static public Font getSmallMonoFont()
{
    return smallmonofont;
}
 
//----------------------------------------------------------------------------
static public int getFontSize()
{
    return fontsize;
}
 
//----------------------------------------------------------------------------
static public int getFontSize(Font f)
{
    return f.getSize();
}
 
//----------------------------------------------------------------------------
static public int getFontWidth()
{
    if( fontwidth==0 )
    {
        getposition gp=new getposition();
    }
    return fontwidth;
}

//----------------------------------------------------------------------------
static public int getFontWidth(Font f)
{
    getposition gp=new getposition();
    gp.setFont( f );
    return gp.getColumnWidth();
}
    
//----------------------------------------------------------------------------
static public int xpos(double x)
{
    return (int)(x*getFontWidth());
}

//----------------------------------------------------------------------------
static public int ypos(double y)
{
    return (int)(y*getFontSize()*1.8);
}
    
//----------------------------------------------------------------------------
getposition()
{
    setFont( getDefaultMonoFont() );
    fontwidth=getColumnWidth();
}


//----------------------------------------------------------------------------
static public Font createFont(int family, int style)
{
    return create_font(family,style,fontsize);
}

//----------------------------------------------------------------------------
static public Font createSmallFont(int family, int style)
{
    return create_font(family,style,fontsize-2);
}

//----------------------------------------------------------------------------
static private Font create_font(int family, int style, int size)
{
    Font f=null;
    if( family==0 && style==0 )
    {
        //nincs megadva
    }
    else
    {
        String ff=Family2Fontfamily(family);
        int fs=Style2Fontstyle(style);
        if( ff!=null && fs!=0 )
        {
            f=new Font(ff,fs,size); 
        }
    }
    return f; //null -> default
}

//----------------------------------------------------------------------------
static private int Style2Fontstyle(int style)
{
    int fontstyle=0;

    if(style==0)
    {
        fontstyle=Font.PLAIN;
    }
    else if(style==STY_PLAIN)
    {
        fontstyle=Font.PLAIN;
    }
    else if(style==STY_BOLD)
    {
        fontstyle=Font.BOLD;
    }
    else if(style==STY_ITALIC)
    {
        fontstyle=Font.ITALIC;
    }       
    return fontstyle;
}

//----------------------------------------------------------------------------
static private String Family2Fontfamily(int family)
{
    String fontfamily=null;

    if( family==0 )
    {
        fontfamily="Monospaced";
    }
    else if(family==FAM_MONO)
    {
        fontfamily="Monospaced";
    }
    else if(family==FAM_DIALOG)
    {
        fontfamily="Dialog";
    }
    else if(family==FAM_DIALOGINPUT)
    {
        fontfamily="DialogInput";
    }
    else if(family==FAM_SERIF)
    {
        fontfamily="Serif";
    }
    else if(family==FAM_SANSSERIF)
    {
         fontfamily="SansSerif";
    }
    return fontfamily;
}

//----------------------------------------------------------------------------
}
