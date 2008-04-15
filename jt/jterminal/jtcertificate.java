
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

//import java.security.cert.*;
import org.w3c.dom.*;
 
//============================================================================
public class jtcertificate{
//============================================================================

//----------------------------------------------------------------------------
static public void uploadcert(jterminal jterm, Node dom) throws Exception
{
    if( dom.getNodeName().equals("#document") )
    {
        dom=dom.getFirstChild(); 
    }
    if( !dom.getNodeName().equals("jtcertificate") )
    {
        throw new Error( "invalid nodename:"+dom.getNodeName() );
    }
    
    String alias=jterminal.getTextContent(dom); 
    jterminal.out.println(alias);
    
    byte[] buf;
    
    try
    {
        java.security.cert.Certificate cert=ksutil.getCertificate(alias);
        buf=base64.encode(cert.getEncoded());
    }
    catch( Exception e )
    {
        buf=new byte[0];
    }
    
    byte[] xml=new byte[0];
    
    xml=jterminal.cat( xml, "<certificate>".getBytes() );
    xml=jterminal.cat( xml, buf );
    xml=jterminal.cat( xml, "</certificate>".getBytes() );
 
    jterm.sck.send(xml);
}

//----------------------------------------------------------------------------
}
