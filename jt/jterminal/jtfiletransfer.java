
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
public class jtfiletransfer{
//============================================================================

//----------------------------------------------------------------------------
static public void upload(jterminal jterm, Node dom) throws Exception
{
    if( dom.getNodeName().equals("#document") )
    {
        dom=dom.getFirstChild(); 
    }
    if( !dom.getNodeName().equals("jtupload") )
    {
        throw new Error( "invalid nodename:"+dom.getNodeName() );
    }
    
    String filespec=jterminal.getTextContent(dom);
    
    try
    {
        File file=new File(filespec);
        FileInputStream in=new FileInputStream(file);
        byte[] buffer=new byte[4096];
        //byte[] buffer=new byte[64];
        int nbyte;

        jterm.sck.send("<uploadbegin>"+Long.toString(file.length())+"</uploadbegin>");
    
        while( 0<(nbyte=in.read(buffer)) )
        {
            jterm.sck.send(buffer,nbyte);
        }

        jterm.sck.send("<uploadend/>");
    }

    catch( Exception e )
    {
        jterm.sck.send("<uploaderror>"+e.toString()+"</uploaderror>");
    }
}

//----------------------------------------------------------------------------
static public void download(jterminal jterm, Node dom) throws Exception
{
    if( dom.getNodeName().equals("#document") )
    {
        dom=dom.getFirstChild(); 
    }
    if( !dom.getNodeName().equals("jtdownload") )
    {
        throw new Error( "invalid nodename:"+dom.getNodeName() );
    }
    
    String fspec=null;
    long flength=0;
    String fdate=null;
    String ftime=null;
    
    for( Node child=dom.getFirstChild(); child!=null; child=child.getNextSibling() ) 
    {
        String name=child.getNodeName(); 
        
        if( name.equals("file") )
        {
            fspec=jterminal.getTextContent(child);
        }
        else if( name.equals("length") )
        {
            flength=Long.parseLong(jterminal.getTextContent(child));
        }
        else if( name.equals("date") )
        {
            fdate=jterminal.getTextContent(child);
        }
        else if( name.equals("time") )
        {
            ftime=jterminal.getTextContent(child);
        }
    }

    int nbyte=0;
    byte[] buffer;
    String result="OK";
    File file=null;
    
    try
    {
        file=new File(fspec); 
        file.delete();
        file.createNewFile();
        FileOutputStream out=new FileOutputStream(file);

        while( (nbyte<flength) && null!=(buffer=jterm.sck.recv()) )        
        {
            nbyte+=buffer.length;
            out.write(buffer);
        }
        out.close();  //regi hiba javitasa!
    }

    catch( Exception e )
    {
        result=e.toString();

        //a maradekot ki kell olvasni,
        //hogy megmaradjon a szinkron

        while( (nbyte<flength) && null!=(buffer=jterm.sck.recv()) )        
        {
            nbyte+=buffer.length;
        }
    }
    
    if(  fdate!=null && ftime!=null )
    {
        //fdate: yyyymmdd
        //ftime  hh:mm:ss

        try
        {
            int year   = jterminal.parseInt(fdate.substring(0,4));
            int month  = jterminal.parseInt(fdate.substring(4,6))-1;
            int day    = jterminal.parseInt(fdate.substring(6,8));
            int hour   = jterminal.parseInt(ftime.substring(0,2));
            int minute = jterminal.parseInt(ftime.substring(3,5));
            int second = jterminal.parseInt(ftime.substring(6,8));

            Calendar c=Calendar.getInstance();
            c.set(year, month, day, hour, minute, second);

            if(  !file.setLastModified(c.getTimeInMillis()) )
            {
                throw( new Exception("file.setLastModified failed") );
            }
        }
        catch( Exception e )
        {
            e.printStackTrace();
 
            jterminal.out.println(fspec);
            jterminal.out.println(flength);
            jterminal.out.println(fdate);
            jterminal.out.println(ftime);
        }
    }

    jterm.sck.send("<download>"+result+"</download>");
}

//----------------------------------------------------------------------------
}
