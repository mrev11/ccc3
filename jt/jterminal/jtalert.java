
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
import java.awt.*;
import java.awt.Toolkit;
import javax.swing.*; 
import org.w3c.dom.*;


//  <jtalert>
//     <messsage>text</message>  default empty
//     <caption>text</caption>   default empty 
//     <type>t</type>            default JOptionPane.WARNING_MESSAGE
//     <options>                 default JOptionPane.DEFAULT_OPTION  
//        <opt>opt1</opt> 
//        <opt>opt2</opt> 
//        ...
//     </options>
//  </jtalert>

//  JOptionPane.ERROR_MESSAGE 
//  JOptionPane.INFORMATION_MESSAGE
//  JOptionPane.WARNING_MESSAGE
//  JOptionPane.QUESTION_MESSAGE
//  JOptionPane.PLAIN_MESSAGE
 
//============================================================================
public class jtalert implements Runnable {
//============================================================================

public String message=""; 
public String caption="";
public int type=JOptionPane.WARNING_MESSAGE;  
public Object[] options={"OK"};
public Window parent=null; 
public boolean send=true;
public boolean beep=true;
private JDialog dialogwindow=null;

private jterminal jterm=null;
 
//----------------------------------------------------------------------------
public jtalert(jterminal jt)
{
    //kozvetlenul megadhatok az attributumok
    jterm=jt;
}

//----------------------------------------------------------------------------
public jtalert(jterminal jt, Node dom)
{
    jterm=jt;
    build(dom);
}
 
//----------------------------------------------------------------------------
public jtalert(jterminal jt, Window parent, Node dom)
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
    if( !dom.getNodeName().equals("jtalert") )
    {
        throw new Error( "invalid nodename:"+dom.getNodeName() );
    }

 
    String typecode=null;
    Node   optnode=null;

    for( Node node=dom.getFirstChild(); node!=null; node=node.getNextSibling() )
    {
        String name=node.getNodeName();

             if( name.equals("message") )  message=jterminal.getTextContent(node);
        else if( name.equals("caption") )  caption=jterminal.getTextContent(node); 
        else if( name.equals("type") )     typecode=jterminal.getTextContent(node);  
        else if( name.equals("options") )  optnode=node; 
    }

    if( typecode!=null )
    {
             if( typecode.equalsIgnoreCase("e") ) type=JOptionPane.ERROR_MESSAGE; 
        else if( typecode.equalsIgnoreCase("i") ) type=JOptionPane.INFORMATION_MESSAGE;
        else if( typecode.equalsIgnoreCase("w") ) type=JOptionPane.WARNING_MESSAGE;
        else if( typecode.equalsIgnoreCase("q") ) type=JOptionPane.QUESTION_MESSAGE;
        else if( typecode.equalsIgnoreCase("p") ) type=JOptionPane.PLAIN_MESSAGE;
    }
    
    if( optnode!=null )
    {
        NodeList optlist=optnode.getChildNodes();;
        options=new Object[optlist.getLength()]; 

        for( int i=0; i<options.length; i++ )
        {
            if( optlist.item(i).getNodeType()==Node.TEXT_NODE )
            {
                options[i]=jterminal.getTextContent(optnode);
            }
            else if( optlist.item(i).getNodeName().equals("opt")  )
            {
                options[i]=jterminal.getTextContent(optlist.item(i));
            }
            else
            {
                throw new Error("invalid option");
            }
        }
    }
}

//----------------------------------------------------------------------------
public void run()
{
    JOptionPane pane=new JOptionPane(
                     new JLabel(message),         //message object (string) 
                     type,                        //message type (icon)
                     JOptionPane.DEFAULT_OPTION,  //option type (OK)
                     null,                        //custom icon
                     options);                    //options

    dialogwindow=pane.createDialog(parent,caption); 

    if( beep )
    {
        Toolkit.getDefaultToolkit().beep();
    }
    
    //2011.08.06
    if( jterminal.windows_os && parent!=null )
    {
        //enable, hogy ne keruljon alulra
        //jterminal.out.println("ALERT.PARENT.ENABLED");
        parent.setEnabled(true);
    }

    //2011.08.06
    //feltetelezes szerint menti a parent allapotat,
    //a sajat futasi idejere disabled allapotba teszi,
    //majd dispose utan, visszateres elott visszaallitja 
    //a mentett allapotot (tehat show alatt disabled,
    //elotte-utana egy-egy pillanatra enabled)

    dialogwindow.show();

    //2011.08.06
    if( jterminal.windows_os && parent!=null )
    {
        //jterminal.out.println("ALERT.PARENT.DISABLED");
        parent.setEnabled(false);
    }

    (new jtremove(dialogwindow)).run();
 
    int ch=0;
    Object choice=pane.getValue();
    if( choice!=null && options!=null )
    {
        for( int i=0; i<options.length; i++ )
        {
            if( options[i]==choice )
            {
                ch=i+1;
                break;
            }
        }
    }
    
    if( send )
    {
        jterm.send("<alert>"+Integer.toString(ch)+"</alert>");
    }
}
                   
//----------------------------------------------------------------------------
} 
 