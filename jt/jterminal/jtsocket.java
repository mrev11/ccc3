
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
import java.net.*;
import javax.net.*;
import javax.net.ssl.*;
import java.security.cert.*;
import java.security.KeyStore;
import java.util.*;
import java.security.Key;
 
//===========================================================================
public class jtsocket {
//===========================================================================
 
private Socket sck;
private InputStream sckin;
private OutputStream sckout;
private jterminal jterm; 

//---------------------------------------------------------------------------
public jtsocket(jterminal t, String host, int port, boolean ssl, 
                String aut, String key, String psw) throws Exception 
{
    jterm=t;

    //try
    {
        if( ssl )
        {
            KeyManager[] km=null; //kliens hitelesítés (default=off)
            TrustManager[] tm=null; //szerver hitelesítés (default=cacerts)
            
            if( key!=null || psw!=null )
            {
                //kliens hitelesítés bekapcsolva
                //a kliens certificate-je key-ben (default=.keystore) 
            
                KeyStore ks=KeyStore.getInstance("JKS");
                if( key==null )
                {
                    String home=System.getProperty("user.home");
                    String filsep=System.getProperty("file.separator");
                    key=home+filsep+".keystore";
                }
                ks.load(new FileInputStream(key),null);

                //kmf.init elbukik, 
                //ha a keystore-ban olyan klucs is van, 
                //amihez nem jó a megadott (egyetlen) jelszó,
                //ezért előzőleg töröljük a nem elérhető kulcsokat.

                Enumeration ksenum=ks.aliases();
                while( ksenum.hasMoreElements() )
                {
                    String alias=(String)ksenum.nextElement();
                    if( ks.isKeyEntry(alias) )
                    {
                        try
                        {
                            ks.getKey(alias,psw.toCharArray());
                        }
                        catch( Exception e )
                        {
                            ks.deleteEntry(alias);  
                        }
                    }
                }
                
                if( psw==null )
                {
                    psw="";
                }
               
                KeyManagerFactory kmf=KeyManagerFactory.getInstance("SunX509"); 
                kmf.init(ks,psw.toCharArray());
                km=kmf.getKeyManagers(); //KeyManager[], km.length==1
            }


            if( aut==null ) //aut nincs megadva
            {
                //szerver hitelesítés kikapcsolva
                tm=new TrustManager[1];
                tm[0]=new dummytrustmanager();
            }
            //else if( aut.isEmpty() ) //aut (üresen) 
            else if( aut.length()==0 ) //aut (üresen) 
            {
                //hitelesítés a cacerts-ből
                //Linuxon: /usr/lib/java/jre/lib/security/cacerts
                //tm=null;
            }
            else //aut=<keystore>
            {
                KeyStore ks=KeyStore.getInstance("JKS");
                ks.load(new FileInputStream(aut),null);
                TrustManagerFactory tmf=TrustManagerFactory.getInstance("SunX509"); 
                tmf.init(ks); //itt nincs jelszóvédelem
                tm=tmf.getTrustManagers();         
            }

            SSLContext ctx=SSLContext.getInstance("TLS");
            ctx.init(km,tm,null);
            SSLSocketFactory factory=(SSLSocketFactory)ctx.getSocketFactory();
            sck=factory.createSocket(host,port); 
            ((SSLSocket)sck).startHandshake();
        }
        else
        {
            sck=new Socket(host,port); //rogton konnektal! 
        }
    }
    //catch( Exception e )
    //{
    //    throw(e);
    //}

    //System.out.println(sck.getSoTimeout()); //default 0
    //int one_minute=60000; //in millis
    //sck.setSoTimeout(120*one_minute);
 
    sckin=sck.getInputStream();
    sckout=sck.getOutputStream();
}

//---------------------------------------------------------------------------
public void send(byte[] x, int length) throws Exception 
{
    synchronized( sckout )
    {
        String hdr=int2str(length,8)+int2str(checksum(x,length),8);
        byte[] buf=hdr.getBytes();

        /*
        jterminal.out.print(":hdr:");jterminal.out.print(hdr);
        jterminal.out.print(":len:");jterminal.out.print(buf.length);
        jterminal.out.print(":");jterminal.out.print(buf);
        jterminal.out.print(":");
        for( int i=0; i<buf.length; i++ )
        {
            jterminal.out.print( " " );
            jterminal.out.print( Integer.toString(255&(int)buf[i]) );
        }
        jterminal.out.println("");
        */

        sckout.write(buf,0,16);
        sckout.write(x,0,length);
    }
     
    //jterminal.out.print(">>>>send:");
    //jterminal.out.println( jterm.byte2char_ex(x) );
}

//---------------------------------------------------------------------------
public void send(byte[] x) throws Exception 
{
    send(x,x.length);
}
 
//---------------------------------------------------------------------------
public void send(String x) throws Exception 
{
    send(jterm.char2byte_ex(x));
}

//---------------------------------------------------------------------------
public void cgi(String url) throws Exception 
{
    sckout.write(("GET "+url+" HTTP/1.1\r\n\r\n").getBytes());
}
 
//---------------------------------------------------------------------------
public byte[] recv() throws Exception
{
    byte[] hdr1=read1(8); if( hdr1==null )  return null;
    byte[] hdr2=read1(8); if( hdr2==null )  return null; 

    byte[] x=read1(str2int(hdr1));
    
    if( x==null ) 
    {
        return null;
    }

    //jterminal.out.print(">>>>recv:");
    //jterminal.out.println( jterm.byte2char_ex(x) );
 
    if( checksum(x)!=str2int(hdr2) )
    {
        //jterminal.out.println( checksum(x) );
        //jterminal.out.println( str2int(hdr2) );
        throw new Error("checksum error");
    }    
 
    return x;
}
 
//---------------------------------------------------------------------------
private byte[] read1(int len) //throws Exception 
{
    synchronized( sckin )
    {
        try
        {
            byte[] x=new byte[len];
            int offset=0, rbyte=0;
            while( offset<len && (rbyte=sckin.read(x,offset,len-offset))>=0 )
            {
                offset+=rbyte;    
            }
            return len==offset ? x : null;   
        }

        //catch(java.net.SocketTimeoutException e)
        catch(Exception e)
        {
            System.out.println(e);
            return null;
        }
    }
}

//---------------------------------------------------------------------------
private static int str2int(String x) throws Exception  
{ 
    return Integer.parseInt(x);
}

private static int str2int(byte[] x) throws Exception  
{ 
    return Integer.parseInt( new String(x) ); 
}

//---------------------------------------------------------------------------
private static String int2str(int x, int w)
{ 
    String y=Integer.toString(x);
    while( y.length()<w )
    {
        y="0"+y;
    }
    return y.substring(0,w);
}
 
//---------------------------------------------------------------------------
private static int checksum( byte[] x, int length ) throws Exception   
{
    int sum=0;
    for(int n=0; n<length; n++)
    {
        sum+=0xff&x[n];
    }
    
    String crc=Integer.toString(sum);
    int crclen=crc.length();
    if( crclen>8 )
    {
        crc=crc.substring(crclen-8,crclen);
        sum=str2int(crc);
    }
    return sum;
}

//---------------------------------------------------------------------------
private static int checksum( byte[] x ) throws Exception    
{
    return checksum(x,x.length);
}


//----------------------------------------------------------------------------
class dummytrustmanager implements X509TrustManager{
//----------------------------------------------------------------------------

//Ez kikapcsolja a szerver bizonyitvanyanak
//ellenorzeset azzal, hogy mindent elfogad.
//A default az ellenorzes volna.

public void checkClientTrusted(X509Certificate[] chain, String authType){}
public void checkServerTrusted(X509Certificate[] chain, String authType){}
public X509Certificate[] getAcceptedIssuers(){ return new X509Certificate[0]; }

//----------------------------------------------------------------------------
}
 
//---------------------------------------------------------------------------
}
 