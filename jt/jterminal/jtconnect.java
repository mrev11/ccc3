
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

import org.w3c.dom.*;
 
//============================================================================
public class jtconnect{
//============================================================================

//----------------------------------------------------------------------------
static public void connect(jterminal jterm, Node dom) throws Exception
{
    String   host = null;
    int      port = 0;
    boolean  ssl  = false;

    if( dom.getNodeName().equals("#document") )
    {
        dom=dom.getFirstChild(); 
    }
    if( !dom.getNodeName().equals("jtconnect") )
    {
        throw new Error( "invalid nodename:"+dom.getNodeName() );
    }

    for( Node child=dom.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();

        if( name.equals("host") )
        {
            host=jterminal.getTextContent(child); 
        }

        else if( name.equals("port") )
        {
            port=Integer.parseInt(jterminal.getTextContent(child));
        }

        else if( name.equals("ssl") )
        {
            ssl=jterminal.getTextContent(child).equals("true"); 
        }
    }
    
    if( host!=null || port!=0 )
    {
        new jterminal(host,port,ssl,null,null,null).start(); 
    }
}

//----------------------------------------------------------------------------
}
