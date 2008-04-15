
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

package getutil;

import javax.swing.*;
import javax.swing.text.*;

//  Ez annyiban tér el a síma PlainDocument-től
//  (és egyúttal a síma JTextField-től),
//  hogy nem nyeli el a text-ben levő \n és \r karaktereket.
//  A \r karakterek Linuxon átalakulnak \n-re az XML elemzőben.
//  Ezek az önkényes konverziók meglehetősen felháborítók.

//===========================================================================
class pictnulldocument extends PlainDocument{
//===========================================================================

private String text="";
private JTextField tfield=null;

//---------------------------------------------------------------------------
public pictnulldocument(JTextField tf)
{
    tfield=tf;
    setSuperText();
}

//---------------------------------------------------------------------------
public String getText()
{
    return text;
}

//---------------------------------------------------------------------------
private void setSuperText()
{
    try
    {
        super.remove(0,super.getLength());
        super.insertString(0,text,null);  
    }
    catch ( Exception e )
    {
        throw new Error( e.toString() );
    }
}

//---------------------------------------------------------------------------
public void remove(int offs, int len)  throws BadLocationException
{
    text=text.substring(0,offs)+text.substring(offs+len);
    setSuperText();
    tfield.setCaretPosition(offs); 
}

//---------------------------------------------------------------------------
public void insertString(int offs, String str, AttributeSet a)  throws BadLocationException
{
    /*
    byte[] b=str.getBytes();
    for(int i=0; i<b.length; i++)
    {
        System.out.print( "[" );
        System.out.print( b[i] );
        System.out.print( "]" );
    }
    */

    text=text.substring(0,offs)+str+text.substring(offs);
    setSuperText();
    tfield.setCaretPosition(offs+str.length()); 
}

//---------------------------------------------------------------------------
}
