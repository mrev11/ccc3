
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

import java.io.*;
import java.util.*;
import java.awt.*;
import javax.swing.*; 
import java.io.File;
import org.w3c.dom.*;
 
//============================================================================
public class jtdirlist implements Runnable {
//============================================================================

public String workdir=null;
public jtfilefilter filefilter=null; 
public int selectmode=JFileChooser.FILES_AND_DIRECTORIES;
private jterminal jterm=null;
 
//----------------------------------------------------------------------------
public jtdirlist(jterminal jt, Node dom)
{
    jterm=jt;
    build(dom);
}

//----------------------------------------------------------------------------
private void build(Node dom)
{
    if( dom.getNodeName().equals("#document") )
    {
        dom=dom.getFirstChild(); 
    }
    if( !dom.getNodeName().equals("jtdirlist") )
    {
        throw new Error( "invalid nodename:"+dom.getNodeName() );
    }

    for( Node node=dom.getFirstChild(); node!=null; node=node.getNextSibling() )
    {
        String name=node.getNodeName();

        if( name.equals("workdir") )      
        {
            workdir=jterminal.getTextContent(node);
        }

        else if( name.equals("filter") )       
        {
            filefilter= new jtfilefilter(node);
        }

        else if( name.equals("selectmode") )   
        {
            String sm=jterminal.getTextContent(node);

            if( sm.equals("F") )
            {
                selectmode=JFileChooser.FILES_ONLY;
            }
            else if( sm.equals("D") )
            {
                selectmode=JFileChooser.DIRECTORIES_ONLY; 
            }
            else if( sm.equals("FD") || sm.equals("DF") ) 
            {
                selectmode=JFileChooser.FILES_AND_DIRECTORIES; 
            }
        }
    }
}
 
//----------------------------------------------------------------------------
public void run()
{
    File fc;
    if( workdir==null )
    {
        fc=new File(".");
    }
    else
    { 
        fc=new File(workdir);
    }

    File[] flist=new File[0];
    if( fc.isDirectory() )
    {
        if( filefilter==null )
        {
            flist=fc.listFiles();
        }
        else
        {
            flist=fc.listFiles( (FileFilter)filefilter );
        }
    }

    String x="";
    for( int i=0; i<flist.length; i++ )
    {
        //jterminal.out.println(flist[i].getName());

        String attr="";
        if( flist[i].isDirectory() )
        {
            attr+="D";
        }
        if( flist[i].isHidden() )
        {
            attr+="H";
        }

        x+="<file>";
        x+="<name>"+flist[i].getName()+"</name>";
        x+="<size>"+Long.toString(flist[i].length())+"</size>";
        x+="<date>"+filedate(flist[i])+"</date>";
        x+="<time>"+filetime(flist[i])+"</time>";
        
//        if( !attr.equals("") )
        {
            x+="<attr>"+attr+"</attr>";
        }
        
        x+="</file>";
    }

    jterm.send("<dirlist>"+x+"</dirlist>");
}

//----------------------------------------------------------------------------
private String filedate(File f)
{
    Calendar c=Calendar.getInstance();
    c.setTimeInMillis( f.lastModified() );
    String y=Integer.toString( c.get(Calendar.YEAR) );
    String m=Integer.toString( c.get(Calendar.MONTH)+1 );
    String d=Integer.toString( c.get(Calendar.DAY_OF_MONTH) );
    if( m.length()<2 )
    {
        m="0"+m;
    }
    if( d.length()<2 )
    {
        d="0"+d;
    }
    return y+m+d;
 
}


//----------------------------------------------------------------------------
private String filetime(File f)
{
    Calendar c=Calendar.getInstance();
    c.setTimeInMillis( f.lastModified() );
    int ampm=((c.get(Calendar.AM_PM)==Calendar.PM)?12:0);
    
    String h=Integer.toString( c.get(Calendar.HOUR) + ampm );
    String m=Integer.toString( c.get(Calendar.MINUTE) );
    String s=Integer.toString( c.get(Calendar.SECOND) );

    if( h.length()<2 )
    {
        h="0"+h;
    }
    if( m.length()<2 )
    {
        m="0"+m;
    }
    if( s.length()<2 )
    {
        s="0"+s;
    }

    return h+":"+m+":"+s;
}

                   
//----------------------------------------------------------------------------
} 
 