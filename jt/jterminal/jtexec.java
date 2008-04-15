
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
public class jtexec{
//============================================================================

//----------------------------------------------------------------------------
static public void exec(jterminal jterm, Node dom) throws Exception
{
    if( dom.getNodeName().equals("#document") )
    {
        dom=dom.getFirstChild(); 
    }
    if( !dom.getNodeName().equals("jtexec") )
    {
        throw new Error( "invalid nodename:"+dom.getNodeName() );
    }
    
    String cmd=jterminal.getTextContent(dom);

    try
    {
        Runtime runtime=Runtime.getRuntime();
        Process proc=runtime.exec( cmd );
        proc.waitFor();
        jterm.sck.send("<exitvalue>"+proc.exitValue()+"</exitvalue>");
    }
    catch( Exception e )
    {
        jterm.sck.send("<execerror>"+jterminal.cdataif(e.toString())+"</execerror>");
    }
}

//----------------------------------------------------------------------------
}