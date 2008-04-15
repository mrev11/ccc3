
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
public class jtfilechooser implements Runnable {
//============================================================================

public Component parent=null; 
 
public String workdir=null;
public String caption="";
public String text="OK";
public boolean multiselect=false;
public String selectmode="FD";
public ArrayList filterlist=new ArrayList(); 
private jterminal jterm=null;
 
//----------------------------------------------------------------------------
public jtfilechooser(jterminal jt, Window parent, Node dom)
{
    jterm=jt;
    build(dom);
    this.parent=parent;
}

//----------------------------------------------------------------------------
private void build(Node dom)
{
    if( dom.getNodeName().equals("#document") )
    {
        dom=dom.getFirstChild(); 
    }
    if( !dom.getNodeName().equals("jtfilechooser") )
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

        else if( name.equals("caption") )      
        {
            caption=jterminal.getTextContent(node); 
        }

        else if( name.equals("multiselect") )  
        {
            multiselect=true; 
        }

        else if( name.equals("selectmode") )  
        {
            selectmode=jterminal.getTextContent(node);
        }
 
        else if( name.equals("text") )         
        {
            text=jterminal.getTextContent(node);   
        }

        else if( name.equals("filter") )       
        {
            filterlist.add(new jtfilefilter(node));
        }
    }
}

 
//----------------------------------------------------------------------------
public void run()
{
    JFileChooser fc;
    if( workdir==null )
    {
        fc=new JFileChooser();
    }
    else
    { 
        fc=new JFileChooser(workdir);
    }
    
    fc.setDialogTitle(caption);
    fc.setMultiSelectionEnabled(multiselect);

    if( selectmode.equals("F") )
    {
        fc.setFileSelectionMode(JFileChooser.FILES_ONLY);
    }
    else if( selectmode.equals("D") )
    {
        fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
    }
    else
    {
        fc.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
    }



    fc.setAcceptAllFileFilterUsed( 0==filterlist.size() );
 
    for( int i=0; i<filterlist.size(); i++ )
    {
        fc.addChoosableFileFilter( (jtfilefilter)filterlist.get(i) );
    }

    int r=fc.showDialog(parent,text);

    String x="";

    if( r==JFileChooser.APPROVE_OPTION ) 
    {
        if( multiselect )
        {
            File[] f=fc.getSelectedFiles();
            for( int i=0; i<f.length; i++ )
            {
                //jterminal.out.println(f[i].toString());
                x+="<file>"+f[i].toString()+"</file>";
            }
        }
        else
        {
            File f=fc.getSelectedFile();
            //jterminal.out.println(f.toString());
            x+="<file>"+f.toString()+"</file>";
        }
    }
    jterm.send("<filechooser>"+x+"</filechooser>");
}

                   
//----------------------------------------------------------------------------
} 
 