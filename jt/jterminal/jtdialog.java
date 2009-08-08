
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
 
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*; 
import org.w3c.dom.*;


//===========================================================================
public class jtdialog 
extends jtwindow
implements  Runnable
{
//===========================================================================

public jtparam param=null;

//public String  pid; 
//public String  dialogid; 

//public int  top=0; 
//public int  left=0;  
//public int  bottom=0;  
//public int  right=0;  
//public String  name=""; 
//public String  text=""; 
//public String layout=null;

private boolean actionenabled=false;


public  ArrayList varlist=new ArrayList(); //variable controls (flat)
private ArrayList itemlist=new ArrayList();
 
// A varlist-be akkor kell betenni egy komponenst, ha nev szerint
// kell elernunk az uzenetekben, pl:
//  1) akcio/reakcioban xmlget/xmlset-tel lekerdezzuk, vagy beallitjuk,
//  2) specialis message uzenetet akarunk kuldeni neki,
//  3) fokuszt akarunk adni ra.
 
private jtdialog dlgparent=null;

public jterminal jterm=null;

//---------------------------------------------------------------------------
jtdialog(jterminal t) throws Exception   
{
    jterm=t;
    param=new jtparam();
}

//---------------------------------------------------------------------------
jtdialog(jterminal t, Node doc) throws Exception   
{
    jterm=t;
    param=new jtparam();
    build(doc);
}
 
//---------------------------------------------------------------------------
jtdialog(jterminal t, jtdialog parent) throws Exception   
{
    super(parent); //@
    dlgparent=parent;
    jterm=t;
    param=new jtparam();
}

//---------------------------------------------------------------------------
jtdialog(jterminal t, jtdialog parent, Node doc) throws Exception   
{
    super(parent); //@
    dlgparent=parent;
    jterm=t;
    param=new jtparam();
    build(doc);
}
 
//---------------------------------------------------------------------------
public void run()
{
    if( !param.name.equals(jterminal.AUTOCRE_LOWER)  )
    {
        show();
    }
}
 
//---------------------------------------------------------------------------
private void build(Node node)
{
    if( node.getNodeName().equals("#document") )
    {
        node=node.getFirstChild(); 
    }
    param.build(node,"jtdialog");
 
    getContentPane().setLayout( null ); //default=abszolut pozicionalas
 
    ButtonGroup implicitgroup=new ButtonGroup();
 
    for( Node child=node.getFirstChild(); child!=null; child=child.getNextSibling() ) 
    {
        int type=child.getNodeType();
        String name=child.getNodeName(); 
        
        if( type!=Node.ELEMENT_NODE )
        {
        }

        else if( name.equals("caption") ) 
        {
            setTitle( param.text(jterminal.getTextContent(child)) );
        }

        else if( name.equals("jtmenu") ) 
        {
            if( getJMenuBar()==null )
            {
                setJMenuBar( new javax.swing.JMenuBar() ); 
            }
            jtmenu m=new jtmenu(this,child); 
            getJMenuBar().add(m); 
            itemlist.add(m);
        }
 
        else if( name.equals("jtmenuitem") ) 
        {
            if( getJMenuBar()==null )
            {
                setJMenuBar( new javax.swing.JMenuBar() ); 
            }
            jtmenuitem m=new jtmenuitem(this,child); 
            getJMenuBar().add(m); 
            itemlist.add(m);
        }

        else if( name.equals("jtmenusep") ) 
        {
            if( getJMenuBar()==null )
            {
                setJMenuBar( new javax.swing.JMenuBar() ); 
            }
            getJMenuBar().add(Box.createHorizontalGlue()); 
        }
 
        else if( name.equals("jttoolbar") ) 
        {
            jttoolbar c=new jttoolbar(this, child);
            getContentPane().add(c);
            itemlist.add(c);
        }

        else if( name.equals("jtpanel") ) 
        {
            jtpanel c=new jtpanel(this, child);
            getContentPane().add(c.getScrollPane()); 
            itemlist.add(c);
        }

        else if( name.equals("jttabpane") ) 
        {
            jttabpane c=new jttabpane(this, child);
            getContentPane().add(c); 
            itemlist.add(c);
        }

        else if( name.equals("jtsplitpane") ) 
        {
            jtsplitpane c=new jtsplitpane(this, child);
            getContentPane().add(c); 
            itemlist.add(c);
        }
 
        else if( name.equals("jttable") || name.equals("jtbrowse") ) 
        {
            jttable c=new jttable(this,child);
            getContentPane().add(c.getScrollPane()); 
            itemlist.add(c);
        }

 
        else if( name.equals("jtlabel") ) 
        {
            jtlabel c=new jtlabel(this,child);
            getContentPane().add(c); 
            if( !c.param.name.equals("") )
            {
                itemlist.add(c);
            }
        }

        else if( name.equals("jtprogbar") ) 
        {
            jtprogbar c=new jtprogbar(this,child);
            getContentPane().add(c); 
            itemlist.add(c);
        }

        else if( name.equals("jtcombo") ) 
        {
            jtcombo c=new jtcombo(this,child);
            getContentPane().add(c); 
            itemlist.add(c);
        }
 
        else if( name.equals("jtget") ) 
        {
            jtget c=new jtget(this,child);
            getContentPane().add(c); 
            itemlist.add(c);
        }

        else if( name.equals("jttextarea") ) 
        {
            jttextarea c=new jttextarea(this,child);
            getContentPane().add(c.getScrollPane()); 
            itemlist.add(c);
        }

        else if( name.equals("jthtmlarea") ) 
        {
            jthtmlarea c=new jthtmlarea(this,child);
            getContentPane().add(c.getScrollPane()); 
            itemlist.add(c);
        }

        else if( name.equals("jttree") ) 
        {
            jttree c=new jttree(this,child);
            getContentPane().add(c.getScrollPane()); 
            itemlist.add(c);
        }
 
        else if( name.equals("jtpassw") ) 
        {
            jtpassw c=new jtpassw(this,child);
            getContentPane().add(c); 
            itemlist.add(c);
        }
 
        else if( name.equals("jtslider") ) 
        {
            jtslider c=new jtslider(this,child);
            getContentPane().add(c); 
            itemlist.add(c);
        }

        else if( name.equals("jtpush") ) 
        {
            jtpush c=new jtpush(this,child);
            getContentPane().add(c); 
            itemlist.add(c);
        }

        else if( name.equals("jtcheck") ) 
        {
            jtcheck c=new jtcheck(this,child);
            getContentPane().add(c); 
            itemlist.add(c);
        }

        else if( name.equals("jtradio") ) 
        {
            jtradio c=new jtradio(this,child);
            getContentPane().add(c); 
            implicitgroup.add(c);
            itemlist.add(c);
        }
 
        else if( name.equals("jtradiogroup") ) 
        {
            ButtonGroup bg=new ButtonGroup();
            for( Node b=child.getFirstChild(); b!=null; b=b.getNextSibling() )
            {
                if( b.getNodeName().equals("jtradio") )
                {
                    jtradio c=new jtradio(this,b);
                    getContentPane().add(c); 
                    bg.add(c);  
                    itemlist.add(c);
                }
            }
        }
    }
    
    param.setLayout(this.getContentPane());

    buildvarlist();

    this.addWindowListener(new jtwindowlistener());
    //this.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
    this.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
 
    int px=getutil.getposition.xpos(param.left);
    int py=getutil.getposition.ypos(param.top);

    if( dlgparent!=null  )
    {
        Point p=dlgparent.getLocationOnScreen();
        px+=(int)p.getX() - getutil.getposition.xpos(dlgparent.param.left); 
        py+=(int)p.getY() - getutil.getposition.ypos(dlgparent.param.top); 
    }
    
    int plusheight=getutil.getposition.getPlusHeight();
    if( getJMenuBar()!=null )
    {
        plusheight+=(getutil.getposition.ypos(1)*2)/3; 
    }
    else
    {
        plusheight-=getutil.getposition.ypos(1)/3; 
    }

    prefw=getutil.getposition.xpos(1+param.right-param.left);
    prefh=getutil.getposition.ypos(1+param.bottom-param.top)+plusheight;  
  
    //Modositjuk az ablak pozicionalasat, 
    //hogy a caption ne logjon le teljesen a kepernyorol:
    //a caption legfeljebb 10 pixellel loghat ki felfele,
    //mas iranyokban pedig legalabb 100 pixel-t benntartunk.

    Rectangle screen=getGraphicsConfiguration().getBounds();
    
    if( px<-prefw+100 )
    {
        px=-prefw+100;
    }
    else if( px>screen.width-100 )
    {
        px=screen.width-100;
    }
    if( py<-10 )
    {
        py=-10;
    }
    else if( py>screen.height-100 ) 
    {
        py=screen.height-100;
    }
    setLocation(px,py);

    pack();

    //setResizable(false);
    setActionEnabled(true);
}

//--------------------------------------------------------------------------- 
public void setActionEnabled(boolean flag)
{
    //setFocusable(flag); //nem jó
    setEnabled(flag);
    actionenabled=flag;
}

public boolean isActionEnabled()
{
    return actionenabled;
}

//Kérdéses a koncepció:
//Ha az akcióküldés tiltása alatt az ablak nincs letiltva, annak is 
//van előnye: Lehet panelt váltani, scrollozni, stb.. Hátránya, hogy 
//állapotváltás történhet az akciójelentés nélkül, pl. változhat egy 
//listbox vagy checkbox kiválasztás. Ilyenkor újabb akció kell, 
//hogy az ilyen állapotváltás eljusson a szerverre.

//--------------------------------------------------------------------------- 
public void buildvarlist()
{
    varlist=new ArrayList(); 
    for( int i=0; i<itemlist.size(); i++)
    {
        ((xmlcomponent)itemlist.get(i)).buildvarlist();
    }
}
 
//---------------------------------------------------------------------------
private void close() //az event dispath thread-ben fut
{
    if( isActionEnabled() )
    {
        jterm.removedlg(this); 
        jterm.send("<destroy dialogid=\""+param.dialogid+"\"/>");
        this.wnd.dispose();
    }
}
 
//---------------------------------------------------------------------------
public void action(xmlcomponent source)
{
    if( !isActionEnabled() )
    {
        return;
    }

    String x="<action dialogid=\""+param.dialogid+"\">";
    x+="<source>"+source.getName()+"</source>";

    for( int i=0; i<varlist.size(); i++ )
    {
        xmlcomponent c=(xmlcomponent)varlist.get(i); 
        
        try
        {
            x+=c.xmlget();
        }
        catch( pfexception e )
        {
            if( !source.isEscape() )
            {
                //szolni kell a kontrolloknak:
                //amit kuldeni akartak, nem ment el,
                //erre valo az xmlreset()
 
                for( int k=0; k<i; k++  )
                {
                    ((xmlcomponent)varlist.get(k)).xmlreset();
                }

                jtalert a=new jtalert(jterm);
                a.message="Hibas adatbevitel: "+c.getName();
                a.parent=this.wnd;
                a.send=false;
                //a.beep=false;
                a.type=JOptionPane.ERROR_MESSAGE;
                a.run();
                e.getField().requestFocus();
                return;
            }
        }
    }
    x+="</action>";
    setActionEnabled(false);
    jterm.send(x);
}


//---------------------------------------------------------------------------
public void message(Node msg) 
{
    //Ezt a metodust kotelezoen az EventDispatchThread-ben kell
    //vegrehajtani, mert a swing altalanossagban nem threadsafe.
    //Az alabbi kod ezt a feltetelt ellenorzi.
    //if( SwingUtilities.isEventDispatchThread() )
    //{
    //    jterminal.out.println( "within EventDispatchThread" );
    //}

    //jterminal.out.println(msg);
    String name=msg.getNodeName();  
    
    if( name.equals("close")  )
    {
        setActionEnabled(true);
        close();
    }

    else if( name.equals("reaction") )
    {
        for( Node c=msg.getFirstChild(); c!=null; c=c.getNextSibling() )
        {
            if( c.getNodeName().equals("focus") )
            {
                String fname=jterminal.getTextContent(c);
                JComponent f=(JComponent)varbyname(fname);
                f.requestFocus();
            }
            else if( c.getNodeName().equals("set") )
            {
                for( Node v=c.getFirstChild(); v!=null; v=v.getNextSibling() )
                {
                    String xname=v.getNodeName();
                    xmlcomponent xvar=varbyname(xname); 
                    xvar.xmlset(v);
                }
            }
        }
        setActionEnabled(true);
    }

    else if( name.equals("jtmessage") )
    {
        //Itt megkeressuk, hogy melyik kontrollnak
        //kell tovabbitani az uzenetet, aztan egeszben tovabbadjuk.
        //Nem lehet arra szamitani, hogy egy node adott sorszamu
        //helyen volna, mert a dom tele van ures #text node-okkal!
        
        //Ha name==AUTOCRE_LOWER, akkor ez egy automatikus,
        //ures dialogbox, direkt azert letrehozva, hogy benne valami 
        //elhelyezheto legyen. Ilyenkor az elso message <control> tagjabol
        //kitalalt tipusu kontrollt teszunk a dialogboxba (de csak egyszer), 
        //majd ennek tovabbitjuk az uzenetet. Igy mukodik pl. az olyan
        //progressbar, ami alatt nem volt parent window.
    
        for( Node c=msg.getFirstChild(); c!=null; c=c.getNextSibling() )
        {
            if( c.getNodeName().equals("control") )
            {
                String cname=jterminal.getTextContent(c); //kontroll nev

                if( this.param.name.equals(jterminal.AUTOCRE_LOWER)  )
                {
                    this.param.name=jterminal.AUTOCRE_UPPER; //tobbszor nem!

                    //automatikus kontroll(ok)

                    if( cname.equals("progressbar") )
                    {
                        jtprogbar pb=new jtprogbar(this);
                        pb.param.name="progressbar";
                        getContentPane().add(pb); 
                        itemlist.add(pb);
                        buildvarlist();

                        setSize( getutil.getposition.xpos(48),
                                 getutil.getposition.ypos( 3) ); 

                        setLocationRelativeTo(dlgparent); 
                    }

                    show(); //csak, ha mar ismert a pozicio
                }

                xmlcomponent x=varbyname(cname); //kontroll objektum
                if( x!=null )
                {
                    x.message(msg);
                }
                break;
            }
        }
    }
}

//---------------------------------------------------------------------------
private xmlcomponent varbyname(String name)
{
    for( int i=0; i<varlist.size(); i++ )
    {
        xmlcomponent c=(xmlcomponent)varlist.get(i); 
        //jterminal.out.println("["+name+"]["+c.getName()+"]" );
        if( c.getName().equals(name) )
        {
            return c;
        }
    }
    return null;
}

//---------------------------------------------------------------------------
public boolean canDispatchMessageTo(String varname)
{
    boolean autcre = createdAutomatically();
    boolean hasvar = (null!=varbyname(varname));

    //jterminal.out.print("VARNAM "); jterminal.out.println("'"+varname+"'"); 
    //jterminal.out.print("AUTCRE "); jterminal.out.println(autcre); 
    //jterminal.out.print("HASVAR "); jterminal.out.println(hasvar); 
    //jterminal.out.println(); 
 
    return  autcre || hasvar;
}

//---------------------------------------------------------------------------
public boolean createdAutomatically()
{
    return param.name.equalsIgnoreCase(jterminal.AUTOCRE_UPPER);
}

 
//===========================================================================
class jtwindowlistener extends WindowAdapter {
//===========================================================================

public void windowClosing(WindowEvent e)
{
    close();
}
 
//---------------------------------------------------------------------------
} //end of class jtwindowlistener  

//---------------------------------------------------------------------------
} //end of class jtdialog   

 