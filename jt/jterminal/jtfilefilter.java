
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
import javax.swing.*; 
import java.io.File;
import org.w3c.dom.*;
 
//============================================================================
public class jtfilefilter 
extends javax.swing.filechooser.FileFilter 
implements FileFilter
{
//============================================================================

private String description="";
private String dirmask=null;
private ArrayList masklist=new ArrayList();

//----------------------------------------------------------------------------
public jtfilefilter(Node node)
{
    for( node=node.getFirstChild(); node!=null; node=node.getNextSibling() )
    {
        String name=node.getNodeName();

        if( name.equals("description") )  
        {
            description=jterminal.getTextContent(node);
        }
        else if( name.equals("mask") )         
        {
            masklist.add(jterminal.getTextContent(node)); 
        }
        else if( name.equals("dirmask") )         
        {
            dirmask=jterminal.getTextContent(node); 
        }
    }
}

//----------------------------------------------------------------------------
public boolean accept(File f) 
{
    String fname=f.getName();

    if( f.isDirectory() ) 
    {
        return  dirmask!=null && fname.matches(dirmask);
    }

    if( f.isFile() ) 
    {
        for(int i=0; i<masklist.size(); i++) 
        {
            if( fname.matches( (String)masklist.get(i)) )
            {
                return true;
            }
        }
    }
 
    return false;
}    
    
//----------------------------------------------------------------------------
public String getDescription() 
{
    return description;
}

//----------------------------------------------------------------------------
}
                   
