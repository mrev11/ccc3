
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
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import org.w3c.dom.*;


//===========================================================================
public class jttree
extends treefield
implements  xmlcomponent, TreeSelectionListener 
{
//===========================================================================

public jtparam param=null;

private scrollfield scrollpane=null; //JScrollPane 
public jtdialog dialog=null; 
public String  lastsend=null;

 
//--------------------------------------------------------------------------- 
//ez van a nodeokban
//--------------------------------------------------------------------------- 
static private class treenode
{
    public String key;
    public String text;
    public String icon;
    public String tooltip;

    public String toString()
    {
        return text;
    }
    
    public treenode(String k, String t, String ic, String tt)
    {
        key=k;
        if(key==null)
        {
            key="unknown";
        }
        text=t;
        if(text==null)
        {
            key="new node";
        }
        icon=ic;
        tooltip=tt;
    }
}

//--------------------------------------------------------------------------- 
//faepites
//--------------------------------------------------------------------------- 
static private DefaultMutableTreeNode buildnode(Node node) //jttreenode-ra
{
    DefaultMutableTreeNode tree=new DefaultMutableTreeNode();
    String key=null,text=null,icon=null,tooltip=null;
    for( Node child=node.getFirstChild(); child!=null; child=child.getNextSibling() ) 
    {
        String type=child.getNodeName();
        
        if( type.equals("key") )
        {
            key=jterminal.getTextContent(child);
        }
        else if( type.equals("text") )
        {
            text=jterminal.getTextContent(child);
        }
        else if( type.equals("icon") )
        {
            icon=jterminal.getTextContent(child);
        }
        else if( type.equals("tooltip") )
        {
            tooltip=jterminal.getTextContent(child);
        }
        else if( type.equals("jttreenode") )
        {
            DefaultMutableTreeNode treenode=buildnode(child);
            tree.add(treenode);
        }
    }
    tree.setUserObject(new treenode(key,text,icon,tooltip));
    return tree;
}

//--------------------------------------------------------------------------- 
//kereses a faban (Java hibak kerulgetve)
//--------------------------------------------------------------------------- 
private DefaultMutableTreeNode findnode(String key)
{
    TreeModel model=getModel();
    DefaultMutableTreeNode root=(DefaultMutableTreeNode)model.getRoot();
    return findnode1(root,key);
}

static private DefaultMutableTreeNode findnode1(DefaultMutableTreeNode node, String key)
{
    if( matchkey(node,key) )
    {
        return node;
    }
    DefaultMutableTreeNode child;
    for( child=firstchild(node); child!=null; child=nextchild(child) )
    {
        DefaultMutableTreeNode n=findnode1(child,key);
        if( n!=null )
        {
            return n;
        }
    }
    return null;
}

static private DefaultMutableTreeNode firstchild( DefaultMutableTreeNode node )
{
    DefaultMutableTreeNode child=null;
    try{ child=(DefaultMutableTreeNode)node.getFirstChild(); }
    catch( Exception e ) {}
    return child;

    //ez nem jol mukodik:
    //a dokumentaciotol elteroen nem nullt ad, ha nincs node,
    //hanem kivetelt dob, vagy eppen hibauzenet nelkul kilep 
}

static private DefaultMutableTreeNode nextchild( DefaultMutableTreeNode node )
{
    DefaultMutableTreeNode child=null;
    try{ child=(DefaultMutableTreeNode)node.getNextSibling(); }
    catch( Exception e ){}
    return child;

    //ez nem jol mukodik:
    //a dokumentaciotol elteroen nem nullt ad, ha nincs node,
    //hanem kivetelt dob, vagy eppen hibauzenet nelkul kilep 
}

static private boolean matchkey(DefaultMutableTreeNode node, String key)
{
    treenode uo=(treenode)node.getUserObject();
    return uo.key.equals(key);
}

//--------------------------------------------------------------------------- 
//renderer (ikon, tooltip)
//--------------------------------------------------------------------------- 
static private class jttreerenderer extends DefaultTreeCellRenderer
{
    public Component getTreeCellRendererComponent(
                            JTree tree,
                            Object value,
                            boolean sel,
                            boolean expanded,
                            boolean leaf,
                            int row,
                            boolean hasFocus) 
    {
        super.getTreeCellRendererComponent(tree,value,sel,expanded,leaf,row,hasFocus);
        DefaultMutableTreeNode node=(DefaultMutableTreeNode)value;
        treenode uo=(treenode)node.getUserObject();
        setToolTipText(uo.tooltip); //null is lehet
        setIcon(jterminal.loadIcon(uo.icon)); //null is lehet
        return this;
    }
}

//--------------------------------------------------------------------------- 
jttree(jtdialog parent, Node node)
{
    dialog=parent;

    param=new jtparam();
    param.editable(false); //!
    param.build(node,"jttree");
    //param.list();

    param.setAlignXY(this);
    param.setToolTip(this);
    param.setEnabled(this);
    //param.setEditable(this);

    DefaultMutableTreeNode tree=null;

    for( Node child=node.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();
        if( name.equals("jttreenode") )
        {
            tree=buildnode(child); 
        }
    }

    setModel(new DefaultTreeModel(tree));
    getSelectionModel().setSelectionMode (TreeSelectionModel.SINGLE_TREE_SELECTION);
    addTreeSelectionListener(this);

    //enable tool tips
    ToolTipManager.sharedInstance().registerComponent(this);
    this.setCellRenderer(new jttreerenderer());
    
    resize(param.left,param.top,param.right-param.left+1,param.bottom-param.top+1);
    scrollpane=new scrollfield(param.left,param.top,param.right-param.left+1,param.bottom-param.top+1,this);
}

//--------------------------------------------------------------------------- 
public JComponent getScrollPane()
{
    return scrollpane==null?(JComponent)this:(JComponent)scrollpane;
}

//--------------------------------------------------------------------------- 
private String selectedkey()
{
    String key="nn";
    DefaultMutableTreeNode node=(DefaultMutableTreeNode)getLastSelectedPathComponent();
    if( node!=null ) 
    {
        treenode uo=(treenode)node.getUserObject();
        key=uo.key;
    }
    return key;
}

private String selectedtext()
{
    DefaultMutableTreeNode node=(DefaultMutableTreeNode)getLastSelectedPathComponent();

    if( node!=null ) 
    {
        treenode uo=(treenode)node.getUserObject();
        return uo.text;
    }
    return "";
}

//--------------------------------------------------------------------------- 
public void valueChanged(TreeSelectionEvent e) 
{
    // A részfa becsukásával összekapcsolt változást
    // a Jáva két lépcsőben adja:
    // 
    // 1) A becsukott részfában korábban kiválasztott node 
    //    kiválasztottsága megszűnik: nincs kiválasztott node.
    // 2) Kiválasztódik a becsukott részfa gyökere.
    //
    // Ha viszont a változás nem jár részfa becsukásával,
    // akkor egyből az új kiválasztást adja.

    TreePath pn=e.getNewLeadSelectionPath(); //new path
    TreePath po=e.getOldLeadSelectionPath(); //old path

    if( pn==null && po!=null && !isVisible(po) )
    {
        //Jelenleg nincs kiválasztott node (pn==null),
        //korábban volt kiválasztott node (po!=null),
        //ez nem látszik => valamelyik felmenőjét becsukták.
        //
        //Ilyenkor nem jelentjük az akciót,
        //mert rögtön jönni fog egy másik akció,
        //a becsukott felmenő kiválasztódásáról.
        //Ezt a második akciót kell jelenteni.
        //
        //Az első akció jelentése nemcsak felesleges,
        //de hibás is, ui. az akció küldése után
        //a reakció megérkezéséig el vannak nyomva 
        //a további akciók, emiatt a szerver nem értesül
        //a parent kiválasztódásáról.
        //
        //Megjegyzés.
        //Veszélyes a kiválasztás kétlépcsős kezelése:
        //Pl. a JTree megváltozhat úgy, hogy a szimpla
        //(becsukás nélküli) kiválasztás-változást is két
        //lépésben kezelje, ami elrontja a itteni logikát.

        return;
    }

    if( param.valid() ) 
    {
        dialog.action(this);
    }
}

//--------------------------------------------------------------------------- 
public String xmlget() throws pfexception
{
    String x="<"+param.name+">"+selectedkey()+"</"+param.name+">"; 

    if( (lastsend!=null) && lastsend.equals(x) )
    {
        x=""; //nem kell kuldeni
    }
    else
    {
        lastsend=x;
    }
    return x;
}

//--------------------------------------------------------------------------- 
public void xmlset(Node data)
{
    String x=jterminal.getTextContent(data); 
    DefaultMutableTreeNode node=findnode(x); //ezt kell kiválasztani
    if( node==null )
    {
        setSelectionPath( null );
    }
    else
    {
        TreeNode[] tn=node.getPath();
        setSelectionPath( new TreePath(tn) );
        lastsend=null;
    }
}
 
//--------------------------------------------------------------------------- 
public void xmlreset()
{
    lastsend=null;
}
 
//---------------------------------------------------------------------------
public boolean isEscape()
{
    return param.escape();
}

//---------------------------------------------------------------------------
public String getName()
{
    return param.name;
}
 
 
//--------------------------------------------------------------------------- 
public boolean isFocusable()
{
    return param.focusable();
}

//--------------------------------------------------------------------------- 
public void message(Node msg)
{
    //System.out.print("MESSAGE");

    jtchange change=new jtchange(msg);
    change.setEnabled(this,param);

    for( Node child=msg.getFirstChild(); child!=null; child=child.getNextSibling() )
    {
        String name=child.getNodeName();
        
        if( name.equals("changetext") )
        {
            //System.out.println(" changetext");

            String key=null;
            String text=null;
            for( Node ch=child.getFirstChild(); ch!=null; ch=ch.getNextSibling() )
            {
                String nm=ch.getNodeName();
                if( nm.equals("key") )
                {
                    key=jterminal.getTextContent(ch); 
                }
                else if( nm.equals("text") )
                {
                    text=jterminal.getTextContent(ch); 
                }
            }
            if( key!=null && text!=null )
            {
                DefaultMutableTreeNode tnode=findnode(key);
                if( tnode!=null )
                {
                    treenode uo=(treenode)tnode.getUserObject();
                    uo.text=text;
                    updateUI();
                }
            }
        }

        else if( name.equals("changeaddnode") )
        {
            //System.out.println(" changeaddnode");

            String key=null;
            DefaultMutableTreeNode subtree=null;
            for( Node ch=child.getFirstChild(); ch!=null; ch=ch.getNextSibling() )
            {
                String nm=ch.getNodeName();
                if( nm.equals("key") )
                {
                    key=jterminal.getTextContent(ch); 
                    
                }
                else if( nm.equals("jttreenode") )
                {
                    subtree=buildnode(ch);
                }
            }

            if( key!=null && subtree!=null )
            {
                //utolsó gyereknek teszi be

                DefaultMutableTreeNode tnode=findnode(key);
                if( tnode!=null )
                {
                    tnode.add(subtree);
                    updateUI();
                }
            }
        }

        else if( name.equals("changeinsnode") )
        {
            //System.out.println(" changeinsnode");

            String key=null;
            DefaultMutableTreeNode subtree=null;
            for( Node ch=child.getFirstChild(); ch!=null; ch=ch.getNextSibling() )
            {
                String nm=ch.getNodeName();
                if( nm.equals("key") )
                {
                    key=jterminal.getTextContent(ch); 
                    
                }
                else if( nm.equals("jttreenode") )
                {
                    subtree=buildnode(ch);
                }
            }

            if( key!=null && subtree!=null )
            {
                //key baloldali testverenek teszi be

                DefaultMutableTreeNode tnode=findnode(key);
                if( tnode!=null )
                {
                    DefaultMutableTreeNode parent=(DefaultMutableTreeNode)tnode.getParent();
                    if( parent!=null)
                    {
                        int pos=0;
                        DefaultMutableTreeNode ch;
                        for( ch=firstchild(parent); parent!=null; ch=nextchild(ch) )
                        {
                            if( matchkey(ch,key) )
                            {
                                parent.insert(subtree,pos);
                                updateUI();
                                break;
                            }
                            ++pos;
                        }
                    }
                
                }
            }
        }

        else if( name.equals("changedelnode") )
        {
            //System.out.println(" changedelnode");

            String key=null;
            for( Node ch=child.getFirstChild(); ch!=null; ch=ch.getNextSibling() )
            {
                String nm=ch.getNodeName();
                if( nm.equals("key") )
                {
                    key=jterminal.getTextContent(ch); 
                    
                }
            }

            if( key!=null )
            {
                DefaultMutableTreeNode tnode=findnode(key);
                if( tnode!=null )
                {
                    DefaultMutableTreeNode pnode=(DefaultMutableTreeNode)tnode.getParent();
                    if( pnode!=null )
                    {
                        pnode.remove(tnode);
                        updateUI();
                    }
                }
            }
        }
    }
}

//--------------------------------------------------------------------------- 
public void buildvarlist()
{
    if( !param.name.equals("") )
    {
        dialog.varlist.add(this);
    }
}
 
//--------------------------------------------------------------------------- 
} 
