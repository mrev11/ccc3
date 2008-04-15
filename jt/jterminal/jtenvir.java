
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

import java.util.*;
import java.io.*;
import org.w3c.dom.*;
 
//============================================================================
public class jtenvir{
//============================================================================

static public Vector envir_name=new Vector();
static public Vector envir_value=new Vector();
 
//----------------------------------------------------------------------------
static public void getenv(jterminal jterm, Node dom) throws Exception
{
    if( dom.getNodeName().equals("#document") )
    {
        dom=dom.getFirstChild(); 
    }
    if( !dom.getNodeName().equals("jtgetenv") )
    {
        throw new Error( "invalid nodename:"+dom.getNodeName() );
    }
    
    String envname=jterminal.getTextContent(dom);
    String envvalue=null;

    int i=envir_name.indexOf(envname);
    if( i>=0 )
    {
        envvalue=(String)envir_value.get(i); 
    }
    
    if( envvalue==null )
    {
        jterm.sck.send("<jtenv/>"); 
    }
    else
    {
        jterm.sck.send("<jtenv><name>"+envname+"</name><value>"+jterminal.cdataif(envvalue)+"</value></jtenv>"); 
    }
}

//----------------------------------------------------------------------------
static public void setenv(jterminal jterm, Node dom) throws Exception
{
    if( dom.getNodeName().equals("#document") )
    {
        dom=dom.getFirstChild(); 
    }
    if( !dom.getNodeName().equals("jtsetenv") )
    {
        throw new Error( "invalid nodename:"+dom.getNodeName() );
    }
    
    String envname=null;
    String envvalue=null;
 
    for( Node child=dom.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();

        if( name.equals("name") )
        {
            envname=jterminal.getTextContent(child); 
        }
        else if( name.equals("value") )
        {
            envvalue=jterminal.getTextContent(child);
        }
    }
    
    if( envname==null )
    {
        return;
    }
    
    int i=envir_name.indexOf(envname);

    if( i>=0 )
    {
        if( envvalue==null )
        {
            envir_name.remove(i);
            envir_value.remove(i);
        }
        else
        {
            envir_value.set(i,envvalue);
        }
    }
    else
    {
        if( envvalue==null )
        {
        }
        else
        {
            envir_name.add(envname);
            envir_value.add(envvalue);
        }
    }
}
 
//----------------------------------------------------------------------------
}