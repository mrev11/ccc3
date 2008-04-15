
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

import getutil.*;
 
import java.awt.*;
import javax.swing.*;
 
import javax.xml.parsers.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;
import org.w3c.dom.*;

import java.util.*;
import java.io.*;
import java.net.*;
 
//===========================================================================
public class jterminal extends Thread { 
//===========================================================================

public static final String JTVERSION = "1.1.10-UTF8 (2008.03.27)";
public static final String JTCOPYRIGHT = JTVERSION+" ComFirm";
 
public static final String AUTOCRE_LOWER = "created_automatically";
public static final String AUTOCRE_UPPER = "CREATED_AUTOMATICALLY";  

public static String xmlhdr="<?xml version=\"1.0\" encoding=\"ENCODING\"?>";

public static String encoding_in="UTF-8"; //inner encoding
public static String encoding_def="ISO8859-2"; //default server encoding
public String encoding_ex; //server encoding

private static ClassLoader jtloader=null;

private static int thcount=0;
private static ArrayList termlst=new ArrayList(); 

private ArrayList dlglst=new ArrayList(); 

public jtsocket sck;
public jtmutex mutex=new jtmutex(); 
 
//---------------------------------------------------------------------------
public static void main(String[] args) throws Exception 
{
    jtloader=Class.forName("jterminal").getClassLoader();
    xmlhdr=xmlhdr.replaceAll("ENCODING",encoding_in);
    new jterminal(args).start(); 
}

//---------------------------------------------------------------------------
jterminal(String[] args) throws Exception  
{
    if( args.length<2 )
    {
        usage();
    }

    String   host = args[0];
    int      port = Integer.parseInt(args[1]);
    boolean  ssl  = false;
    String   aut  = null;
    String   key  = null;
    String   psw  = null;
    String   cgi  = null;
    
    for( int n=2; n<args.length; n++ )
    {
        if( args[n].equals("ssl")  )
        {
            ssl=true;
        }
        else if( args[n].equals("aut") )
        {
            ssl=true;
            aut="";
        }
        else if( args[n].startsWith("aut=") )
        {
            ssl=true;
            aut=args[n].substring(4);
            //System.out.print("aut:"); System.out.println("["+aut+"]");
        }
        else if( args[n].startsWith("key=") )
        {
            ssl=true;
            key=args[n].substring(4);
            //System.out.print("key:"); System.out.println("["+key+"]");
        }
        else if( args[n].startsWith("psw=") )
        {
            ssl=true;
            psw=args[n].substring(4);
            //System.out.print("psw:"); System.out.println("["+psw+"]");
        }
        else if( args[n].startsWith("cgi=") )
        {
            cgi=args[n].substring(4);
            //System.out.print("get:"); System.out.println("["+cgi+"]");
        }
        else
        {
            usage();
        }
    }

    sck=new jtsocket(this,host,port,ssl,aut,key,psw);
    
    if( cgi!=null )
    {
        sck.cgi(cgi); //küld egy GET requestet (indul a CGI program)
    }
}

//---------------------------------------------------------------------------
jterminal(String host, int port, boolean ssl, String aut, String key, String psw) throws Exception  
{
    sck=new jtsocket(this,host,port,ssl,aut,key,psw);
}
 
//---------------------------------------------------------------------------
public void run()
{
    synchronized( termlst )
    {
        thcount++;
        termlst.add(this);
    }

    try
    {
        run1();
    }
    catch( Exception e )
    {
    }

    synchronized( termlst )
    {
        thcount--;
        if( thcount<=0 )
        {
            System.exit(0); //endofprog
        }

        int j=termlst.indexOf(this);

        if( j>=0 )
        {
            termlst.remove(j); 

            for(int i=dlglst.size()-1; i>=0; i--)
            {
                (((jtdialog)dlglst.get(i)).wnd).dispose(); 
            }
        }
    }
    return;
}    
 
//---------------------------------------------------------------------------
private void run1() throws Exception
{
    encoding_ex=encoding_def;
    DocumentBuilder db=docbuilder();

    while( true ) //messageloop
    {
        byte[] msg=sck.recv();
        if( msg==null )
        {
            //out.println("connection closed");
            return;  //endofthread
        }
        
        invalid_char_filter(msg);
        msg=char2byte_in(byte2char_ex(msg));
        msg=cat(xmlhdr.getBytes(),msg);
        Document doc=db.parse(new ByteArrayInputStream(msg));
        
        Node command=doc.getFirstChild();
        String cmd=command.getNodeName();
        
        synchronized( dlglst )
        {
            if( cmd.equals("exit") )
            {
                return; //endofthread
            }

            else if( cmd.equals("jtdialog") ) 
            {
                deiconify1(this);
                jtdialog dlg; 
                jtdialog parent=gettopjtdlg(); 

                if( parent!=null )
                {
                    dlg=new jtdialog(this,parent,command); 
                }
                else
                {
                    dlg=new jtdialog(this,command); 
                }
                dlglst.add(dlg);
                SwingUtilities.invokeLater(dlg);
            }

            else if( cmd.equals("jtalert") ) 
            {
                deiconify();
                jtdialog parent=gettopjtdlg(); 
                jtalert a=new jtalert(this,parent==null?null:parent.wnd,command);
                SwingUtilities.invokeLater(a);
            }

            else if( cmd.equals("jtfilechooser") ) 
            {
                deiconify();
                jtdialog parent=gettopjtdlg(); 
                jtfilechooser fc=new jtfilechooser(this,parent==null?null:parent.wnd,command);
                SwingUtilities.invokeLater(fc);
            }

            else if( cmd.equals("jtdirlist") ) 
            {
                (new jtdirlist(this,command)).run();
            }
 
            else if( cmd.equals("jtupload") ) 
            {
                jtfiletransfer.upload(this,command);
            }

            else if( cmd.equals("jtdownload") ) 
            {
                jtfiletransfer.download(this,command);
            }

            else if( cmd.equals("jtfileutil") ) 
            {
                for( Node node=command.getFirstChild(); node!=null; node=node.getNextSibling() )
                {
                    String name=node.getNodeName();

                         if( name.equals("makedir") )    jtfileutil.makedir(this,getTextContentChild(node,"name"));
                    else if( name.equals("makedirs") )   jtfileutil.makedirs(this,getTextContentChild(node,"name"));
                    else if( name.equals("delete") )     jtfileutil.delete(this,getTextContentChild(node,"name"));
                    else if( name.equals("exists") )     jtfileutil.exists(this,getTextContentChild(node,"name"));
                    else if( name.equals("isfile") )     jtfileutil.isfile(this,getTextContentChild(node,"name"));
                    else if( name.equals("isdirectory")) jtfileutil.isdirectory(this,getTextContentChild(node,"name"));
                    else if( name.equals("rename") )     jtfileutil.rename(this,getTextContentChild(node,"oldname"),
                                                                                getTextContentChild(node,"newname"));
                }
            }
 
            else if( cmd.equals("jtversion") ) 
            {
                sck.send("<jtversion>"+JTVERSION+"</jtversion>");
            }

            else if( cmd.equals("jtencoding") )
            {
                sck.send("<jtencoding>"+encoding_ex+"</jtencoding>");
                String enc=jterminal.getTextContent(command);
                if( enc.length()>0 )
                {
                    encoding_ex=enc;
                }
            }

            else if( cmd.equals("jtcertificate") ) 
            {
                jtcertificate.uploadcert(this,command);
            }

            else if( cmd.equals("jtconnect") ) 
            {
                jtconnect.connect(this,command);
            }

            else if( cmd.equals("jtexec") ) 
            {
                jtexec.exec(this,command);
            }

            else if( cmd.equals("jtgetenv") ) 
            {
                jtenvir.getenv(this,command);
            }

            else if( cmd.equals("jtsetenv") ) 
            {
                jtenvir.setenv(this,command);
            }
 
            else
            {
                dispatch_message(command);
            }

        }//synchronized( dlglst ) 

    }//messageloop 
}
 
//---------------------------------------------------------------------------
private void dispatch_message(Node command) throws Exception  
{
    mutex.lock();

    //A message feldolgozás sorba van állítva,
    //figyelni kell rá, hogy a mutex el legyen engedve,
    //a mutexet vagy a message feldolgozás engedi el,
    //vagy explicite itt kell elengedni.

    //A stack lebontas minden messagere vonatkozik,
    //akkor fut, ha a message megadott ablaknak szol.

    String dialogid=null;

    if( null!=(dialogid=getAttrib(command,"dialogid")) ) 
    {
        //Leszedi a stackrol az ablakokat mindaddig,
        //amig felulre nem kerul az, amelyiknek a message szol,
        //es ennek tovabbitja a message-et.

        for( int i=dlglst.size()-1; i>=0; i-- )
        {
            Object o=dlglst.get(i); 

            if( ((jtdialog)o).param.dialogid.equals(dialogid) )
            {
                jtdlgmsg r=new jtdlgmsg((jtdialog)o,command,mutex); //unlock
                SwingUtilities.invokeLater(r);
                return;
            }
            else
            {
                //jterminal.out.print(i);
                //jterminal.out.print(" ");
                //jterminal.out.print(dialogid);
                //jterminal.out.print(" ");
                //jterminal.out.print(o);
                //jterminal.out.print(" ");
                //jterminal.out.println(((jtdialog)o).dialogid);

                dlglst.remove(i);  
                jtremove r=new jtremove(((jtdialog)o).wnd); 
                SwingUtilities.invokeLater(r);
            }
        }
        mutex.unlock();
        return;
    }
    
    //Itt annak az esetnek a kezelese kovetkezik,
    //amikor a message nem egy meghatarozott ablaknak szolt.
    //Ekkor megnezzuk, hogy a felso ablak kepes-e fogadni
    //a message-et, vagy bizonyos esetekben uj ablakot keszitunk.
    //A tovabbiakban csak jtmessage-ekkel foglalkozunk, 
    //ezekkel is csak akkor, ha tartalmaz <control> tagot.

    String mname=command.getNodeName();
    String cname=getTextContentChild(command,"control");
    String pid=getAttrib(command,"pid"); 

    if( !mname.equals("jtmessage") || cname==null || pid==null )
    {
        mutex.unlock();
        return;
    }

    //A legfelso dialogboxnak kuldjuk a message-et, 
    //ha az kepes fogadni azt, vagy csinalunk egy uj ablakot.

    jtdialog topdlg=gettopjtdlg();
    
    if( topdlg==null || 
        !topdlg.param.pid.equals(pid) ||
        !topdlg.canDispatchMessageTo(cname) )
    {
        if( cname.equals("progressbar")  )
        {
            //Csak meghatarozott esetekben
            //csinalunk automatikus ablakot,
            //ez kesobb bovulhet mas esetekkel.

            if( topdlg!=null )
            {
                topdlg=new jtdialog(this,topdlg); //parentje van
            }
            else
            {
                topdlg=new jtdialog(this);
            }

            topdlg.param.name=AUTOCRE_LOWER;
            topdlg.param.pid=pid;
            dlglst.add(topdlg);
            SwingUtilities.invokeLater(topdlg);
        }
        else
        {
            topdlg=null; 
        }
    }

    if( topdlg!=null )
    {
        jtdlgmsg r=new jtdlgmsg(topdlg,command,mutex); //unlock
        SwingUtilities.invokeLater(r);
        return;
    }

    mutex.unlock();
    return;
}

//---------------------------------------------------------------------------
public jtdialog gettopjtdlg() 
{
    synchronized( dlglst )
    {
        jtdialog d=null;
    
        if( dlglst.size()>0 )
        {
            d=(jtdialog)(dlglst.get(dlglst.size()-1));
        }
        return d; //null, ha nincs ablak
    }
}

//---------------------------------------------------------------------------
private void deiconify() 
{
    if( !deiconify1(this) )
    {
        synchronized( termlst )
        {
            for(int j=0; j<termlst.size(); j++ )
            {
                deiconify1( (jterminal)termlst.get(j) );
            }
        }
    }
}

//---------------------------------------------------------------------------
private boolean deiconify1(jterminal t) 
{
    synchronized( t.dlglst )
    {
        if( t.dlglst.size()>0 )
        {
            jtdialog d=(jtdialog)(t.dlglst.get(0));

            if( d.wnd instanceof Frame )
            {
                Frame f=(Frame)(d.wnd);
                int state=f.getExtendedState();
                        
                if( (state&Frame.ICONIFIED)!=0 )
                {
                    state&=~Frame.ICONIFIED;
                    f.setExtendedState(state);
                }
                return true;
            }
        }
    }
    return false;
}
 
//---------------------------------------------------------------------------
public boolean removedlg(Object o) 
{
    //Ezt a metodust az ablakok hivjak meg,
    //amikor megszuntetik magukat (ami az event dispatch
    //threadben tortenik). A dlglst-hez valo nyulkalast
    //a main thread (messageloop) es az event dispatch thread
    //kozott szinkronizalni kell.

    synchronized( dlglst )
    {
        int i=dlglst.indexOf(o);

        if( i>=0 )
        {
            dlglst.remove(i); 
            return true;
        }
        return false;
    }
}

//---------------------------------------------------------------------------
public void send(String x)
{
    try
    {
        sck.send(x);
    }
    catch( Exception e )
    {
        //amikor hibazik a send,
        //legegyszerubb tovabbengedni,
        //ami utan azonnal a recv is hibazik,
        //ami utan "connection closed" uzenettel
        //magatol kilep a thread (pont ez kell)
        
        jterminal.out.println("send failed");
        //(new Exception("DEBUG")).printStackTrace();
        e.printStackTrace();
    }
}

//---------------------------------------------------------------------------
public static void usage() 
{
    System.err.println("Java Terminal "+JTVERSION);
    System.err.println("Usage: java -jar jterminal.jar <host> <port> [options]");
    System.err.println("Valid options are:");
    System.err.println("    ssl");
    System.err.println("    aut[=<cacerts>]");
    System.err.println("    key=<keystore>");
    System.err.println("    psw=<storepass>");
    System.err.println("    cgi=<cgispec>");
    System.exit(1); //endofprog
}
 
//---------------------------------------------------------------------------
public static void die(Object e) 
{
    throw new Error(e.toString());
}

//---------------------------------------------------------------------------
public static PrintWriter out=pw();

private static PrintWriter pw() 
{
    OutputStreamWriter ow=null;
    try
    { 
        ow=new OutputStreamWriter(System.out,"iso-8859-1");
    }
    catch(Exception e)
    {
        die(e);
    }
    return new PrintWriter(ow,true);
}

//---------------------------------------------------------------------------
public static DocumentBuilder docbuilder() throws Exception  
{
    DocumentBuilderFactory dbf=DocumentBuilderFactory.newInstance();
    dbf.setNamespaceAware(false);
    dbf.setValidating(false);
    dbf.setIgnoringComments(true);
    dbf.setIgnoringElementContentWhitespace(true); //hatastalan!
    dbf.setCoalescing(false); //not convert CDATA into #text 
    dbf.setExpandEntityReferences(false);
    return dbf.newDocumentBuilder();
}
 
//---------------------------------------------------------------------------
public static String getTextContent(Node node) 
{
    String text="";
    for( Node c=node.getFirstChild(); c!=null; c=c.getNextSibling() ) 
    {
        int type=c.getNodeType(); 

        if( type==Node.TEXT_NODE ||
            type==Node.CDATA_SECTION_NODE )
        {
            text+=c.getNodeValue();
        }
    }
    return text;
}

//---------------------------------------------------------------------------
public static String getTextContentChild(Node node, String childname )
{
    for( Node c=node.getFirstChild(); c!=null; c=c.getNextSibling() )
    {
        if( c.getNodeName().equals(childname) )
        {
            return jterminal.getTextContent(c);
        }
    }
    return null;
}
 
//---------------------------------------------------------------------------
public static String getAttrib(Node node, String attrname)
{
    NamedNodeMap attribs=node.getAttributes();
    for( int i=0; i<attribs.getLength(); i++ ) 
    {
        Node a=attribs.item(i);
        if( a.getNodeName().equals(attrname) )
        {
             return a.getNodeValue(); 
        }
    }
    return null;
}

 
//---------------------------------------------------------------------------
public static String cdataif(String x) 
{
    if( x.indexOf('<')>=0 || x.indexOf('&')>=0 )
    {
        return cdata(x);
    }
    return x;
}

//---------------------------------------------------------------------------
public static String cdata(String x)
{
    String cd=""; 
    while( true )
    {
        int n=x.indexOf("]]>");
        if( n<0 )
        {
            cd+="<![CDATA["+x+"]]>";
            break;
        }
        else
        {
            cd+="<![CDATA["+x.substring(0,n+2)+"]]>";
            x=x.substring(n+2);
        }
    }
    return cd;
}
 
//---------------------------------------------------------------------------
public static ImageIcon loadIcon( String iconFilespec )
{
 
    ImageIcon icon=null;
    
    if( iconFilespec!=null )
    {
        //URL url=ClassLoader.getSystemResource(iconFilespec); //egyik megoldas
        URL url=jtloader.getResource(iconFilespec); //masik megoldas (jobb)
        if( url!=null )  
        {
            icon=new ImageIcon(url);
        }
    }

    return icon;
}

//---------------------------------------------------------------------------
static public int parseInt(String value)
{
    return (int)Double.parseDouble(value); 
}

//---------------------------------------------------------------------------
public byte[] char2byte_ex( String str )
{
    try
    {
        return str.getBytes(encoding_ex);
    }
    catch( UnsupportedEncodingException e )
    {
        return str.getBytes();
    }
}

//---------------------------------------------------------------------------
public byte[] char2byte_in( String str )
{
    try
    {
        return str.getBytes(encoding_in);
    }
    catch( UnsupportedEncodingException e )
    {
        return str.getBytes();
    }
}

//---------------------------------------------------------------------------
public String byte2char_ex( byte[] buf)
{
    try
    {
        return new String(buf,encoding_ex);
    }
    catch( UnsupportedEncodingException e )
    {
        return new String(buf);
    }
}


//---------------------------------------------------------------------------
public String byte2char_in( byte[] buf)
{
    try
    {
        return new String(buf,encoding_in);
    }
    catch( UnsupportedEncodingException e )
    {
        return new String(buf);
    }
}
 
//---------------------------------------------------------------------------
static public byte[]  cat( byte[] a,  byte[] b )
{
    byte[] c=new byte[a.length+b.length];
    int j=0;
    for(int i=0; i<a.length; i++)  c[j++]=a[i];
    for(int i=0; i<b.length; i++)  c[j++]=b[i];
    return c;
}
 
//---------------------------------------------------------------------------
static public void sleep(long millis)
{
    try
    {
        java.lang.Thread.currentThread().sleep(millis);
    }
    catch( Exception e )
    {
    }
}    

//---------------------------------------------------------------------------
static private void invalid_char_filter(byte[] x)
{
    for( int i=0; i<x.length; i++ )
    {
        if( (0xff&x[i]) < 32 ) 
        {
            switch( x[i] )
            {
                case   9 : break; //tab
                case  10 : break; //nl
                case  13 : break; //cr

                default  : x[i]=(byte)32; //szokoz
            }
        }
    }
}

//---------------------------------------------------------------------------
static public void autoscroll(JComponent c)
{
    Rectangle cb=c.getBounds();
    Rectangle cv=c.getVisibleRect();
    if( cv.getWidth()<cb.getWidth() || cv.getHeight()<cb.getHeight() )
    {
        Container p=c.getParent();
        while( p instanceof JComponent )
        {
            if( p instanceof jtpanel )
            {
                jtpanel p1=(jtpanel)p;
                JScrollPane s1=(JScrollPane)(p1.getScrollPane());
                if( s1 instanceof JScrollPane )
                {
                    JViewport v1=s1.getViewport();
                    if(  v1 instanceof JViewport )
                    {
                        v1.setViewPosition(new Point(0,0));
                        v1.scrollRectToVisible(c.getBounds());
                    }
                }
            }
            c=(JComponent)p;
            p=c.getParent();
        }
    }
}

//---------------------------------------------------------------------------
}
 