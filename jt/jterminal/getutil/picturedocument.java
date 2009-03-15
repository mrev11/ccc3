
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


//===========================================================================
class picturedocument extends PlainDocument{
//===========================================================================

static String templateChr="ANX9!";

private JTextField tfield=null;
private String text="";

private String picture="";
private String templateStr=null;
private String functionStr=null;

private int wwhole=0;   // egeszek szama
private int wfract=0;   // tizedesek szama
private int decpos=0;   // tizedespont helye
 
private boolean flagR=true;   //@R valtozott: mindig beallitva (2009.03.15)
private boolean flagU=false;  //@!
private boolean flagD=false;  //@D
private boolean flagL=false;  //@L
private boolean flagN=false;  //@N bovitmeny: szamoknal meg kell adni!
private boolean flagX=false;  //@X bovitmeny: a get ellenorzi magat
private boolean flagE=false;  //@E bovitmeny: empty ertek megengedett 
private boolean flagT=false;  //@T bovitmeny: trimelve adja az eredmenyt
private boolean flagF=false;  //@F bovitmeny: jelenti a fokusz elveszteset
 
private static final String LOGICAL="tTfFyYnN";

//---------------------------------------------------------------------------
public picturedocument(JTextField tf, String p)
{
    tfield=tf;
    picture=p;
    
    if( p.startsWith("@") )
    {
        int i=picture.indexOf(' ');
        if( i>=0 )
        {
            functionStr=p.substring(1,i);
            templateStr=p.substring(i+1);
        }
        else
        {
            functionStr=p.substring(1);
            templateStr="XXXXXXXXXX";
        }
    }
    else
    {
        templateStr=p;
    }

    if( functionStr!=null )
    {
      //flagR=functionStr.indexOf('R')>=0; //mindig beallitva (2009.03.15)
        flagU=functionStr.indexOf('!')>=0;
        flagD=functionStr.indexOf('D')>=0;
        flagL=functionStr.indexOf('L')>=0;
        flagN=functionStr.indexOf('N')>=0;
        flagX=functionStr.indexOf('X')>=0;
        flagE=functionStr.indexOf('E')>=0;
        flagT=functionStr.indexOf('T')>=0;
        flagF=functionStr.indexOf('F')>=0;
    }


    if( flagD )
    {
        templateStr="9999-99-99";
    }

    if( flagL )
    {
        templateStr="A";
    }

    if( flagN )
    {
        if( templateStr==null )
        {
            templateStr=replicate("9",12);
        }

        int i;
        for( i=0; i<templateStr.length(); i++ )
        {
            char c=templateStr.charAt(i);
            if( c=='.' )
            {
                break;
            }
            else if( c=='9' )
            {
                wwhole++;
            }
        }
        for( ; i<templateStr.length(); i++ )
        {
            char c=templateStr.charAt(i);
            if( c=='9' )
            {
                wfract++;
            }
        }
        
        decpos=templateStr.indexOf('.');
        if( decpos<0 )
        {
            decpos=templateStr.length();
        }

        //System.out.print("wwhole:"); System.out.println(wwhole); 
        //System.out.print("wfract:"); System.out.println(wfract); 
        //System.out.print("decpos:"); System.out.println(decpos); 
    }


    for( int n=0; n<templateStr.length(); n++ )    
    {
        text+=(isEditable(n)?' ':templateStr.charAt(n));
    }

    setSuperText(0);
}

//---------------------------------------------------------------------------
private void setSuperText(int minwid)
{
    int i=text.length();
    while( i>minwid && i>0 && text.charAt(i-1)==' ' ) i--;

    try
    {
        super.remove(0,super.getLength());
        super.insertString(0,text.substring(0,i),null);  
    }
    catch ( Exception e )
    {
        throw new Error( e.toString() );
    }
    
    //Megjegyzes:
    //Korabban mindig az egesz text-et betettuk a JTextField-be,
    //ennek hatasara az End gomb a get legvegere pozicionalt ahelyett,
    //hogy a getben levo szoveg vegere pozicionalt volna.
}

//---------------------------------------------------------------------------
public String getText()
{
    if( templateStr==null || !flagR  )
    {
        return flagT ? text.trim() : text;
    }

    String t="";
    for( int n=0; n<templateStr.length(); n++ )    
    {
        char c=text.charAt(n);

        if( isEditable(n) || (flagN && c=='.') || (flagN && c=='-') )
        {
            t+=c;
        }
    }
    
    if( flagN || flagT )
    {
        t=t.trim();
    }

    return t;
}

//---------------------------------------------------------------------------
private boolean isEmpty()
{
    boolean e=false;

    if( flagL )
    {
        //mindig kitoltve
    }
    else if( flagN )
    {
        //mindig kitoltve 
    }
    else
    {
        //string, datum
 
        boolean r=flagR;
        flagR=true;
        e=getText().trim().equals("");
        flagR=r;
    }
    return e;
}

//---------------------------------------------------------------------------
static boolean isLetter(char c){ return java.lang.Character.isLetter(c); }
static boolean isDigit(char c){ return java.lang.Character.isDigit(c); }
static boolean isLetterDigit(char c){ return isLetter(c) || isDigit(c); }
static boolean isEnglishLetter(char c){ return 'a'<=c && c<='z' || 'A'<=c && c<='Z'; }
static boolean isEnglishLetterDigit(char c){ return 'a'<=c && c<='z' || 'A'<=c && c<='Z' || '0'<=c && c<='9'; }

//---------------------------------------------------------------------------
private boolean isEditable(int offs)
{
    return  offs<templateStr.length() &&
            0<=templateChr.indexOf(templateStr.charAt(offs));
}

//---------------------------------------------------------------------------
private int nextNotEditable(int offs)
{
    int n;
    for( n=offs; n<templateStr.length(); n++ )
    {
        if( 0>templateChr.indexOf(templateStr.charAt(n)) )
        {
            break;
        }
    }
    return n;
}

//---------------------------------------------------------------------------
private int prevNotEditable(int offs)
{
    int n;
    for( n=offs-1; n>=0; n-- )
    {
        if( 0>templateChr.indexOf(templateStr.charAt(n)) )
        {
            break;
        }
    }
    return n;
}
 
//---------------------------------------------------------------------------
private int setpos(int pos)
{
    while( pos<templateStr.length() && !isEditable(pos) )
    {
        pos++;
    }
    return pos;
}
 
//---------------------------------------------------------------------------
private static String replicate(String s, int n)
{
    String b="";
    for(int i=0; i<n; i++ )
    {
        b+=s;
    }
    return b;
}

//---------------------------------------------------------------------------
public void remove(int offs, int len)  throws BadLocationException
{
    //System.out.print("remove:");
    //System.out.print(offs);
    //System.out.print(",");
    //System.out.print(len);
    //System.out.println();
    
    if( templateStr==null )
    {
        super.remove(offs,len);
        return;
    }
    
    String t=text.substring(0,offs);
    int p=prevNotEditable(offs+len);
    int n=nextNotEditable(offs+len);

    //System.out.println(p);
    //System.out.println(n);

    for( int i=offs; i<=p; i++ ) 
    {
        t+=(isEditable(i)?' ':templateStr.charAt(i));
    }
    t+=text.substring(offs+len,n);
    t+=replicate(" ",n-t.length()); 
    t+=text.substring(n); 
    
    text=t;
    setSuperText(offs);
    tfield.setCaretPosition(offs); 
}

//---------------------------------------------------------------------------
public void insertString(int offs, String str, AttributeSet a)  throws BadLocationException
{
    //System.out.print("insert:");
    //System.out.print(offs);
    //System.out.print(",");
    //System.out.print("'"+str+"'");
    //System.out.println();

    if( str.equals("") )
    {
        return;
    }
 
    if( templateStr==null )
    {
        if( flagU ) //@!
        {
            str=str.toUpperCase();
        }
        super.insertString(offs,str,a);
        return;
    }

    int pos=setpos(offs);
    for( int i=0; i<str.length() && pos<templateStr.length(); i++ )
    {
        pos=inschr(pos,str.charAt(i));
    }
    //System.out.println(str);
    
    if( str.length()>1 )
    {
        pos=setpos(offs);
    }

    setSuperText(pos);
    tfield.setCaretPosition( pos ); 
}

//---------------------------------------------------------------------------
private int inschr(int pos, char chr)
{
    //System.out.print(pos); 
    //System.out.print("'"+chr+"' "); 

    int n=nextNotEditable(pos);
    char p=templateStr.charAt(pos);
   
    //System.out.print( "template char:" );  System.out.println( p );
    //System.out.print( "inserting char:" ); System.out.println( chr );
    
    if( flagL && chr==' ' ) //toggle
    {
             if( text.equals(" ") ) chr='T';
        else if( text.equals("T") ) chr='F';
        else if( text.equals("F") ) chr='T';
        else if( text.equals("Y") ) chr='N';
        else if( text.equals("N") ) chr='Y';
    }
 
    if( p=='A' && !isEnglishLetter(chr) )
    {
        return pos; //csak betu megengedett
    }
    else if( p=='9' && !isDigit(chr) ) 
    {
        if( !flagN || pos>decpos )
        {
            return pos; 
        }
        else if( chr=='-' ) 
        {
        }
        else if( chr=='+' ) 
        {
        }
        else if( chr=='.' ) 
        {
            return dot(pos);
        }
        else
        {
            return pos; //csak szamjegy megengedett
        }
    }
    else if( p=='N' && !isEnglishLetterDigit(chr) )  
    {
        return pos; //csak szamjegy es betu megengedett
    }
    else if( p=='!' )
    {
        if( isLetterDigit(chr) )
        {
            chr=Character.toUpperCase(chr);
        }
        else
        {
            return pos;
        }
    }
    
    if( flagU )
    {
        chr=Character.toUpperCase(chr);
    }

    if( flagL && LOGICAL.indexOf(chr)<0  )
    {
        return pos;
    }
 
    String t=text.substring(0,pos);    
    t+=chr+text.substring(pos);     
    t=t.substring(0,n);            
    t+=text.substring(n);           
    text=t;
    
    if( flagL )
    {
        pos--; //ne menjen előre a kurzor
    }

    return setpos(pos+1);
}

//---------------------------------------------------------------------------
private int dot(int pos)
{
    //helyere teszi a getben a szamokat,
    //amikor megnyomjak a tizedes pontot

    //System.err.print( "["+ text +"]"  );
 
    int i,j;
    String t="";
    String t1="";
    boolean minus=false;
    
    for( i=0; i<decpos; i++ ) //tizedespont elott 
    {
        char c=text.charAt(i); 
 
        if( isEditable(i) || (c=='-') )
        {
            if( c==' ' )
            {
                if( !t.equals("") ) 
                {
                    break;
                }
            }
            else if( c=='+' )
            {
                t=""; //ujrakezd
                minus=false;
            }
            else if( c=='-' )
            {
                t=""; //ujrakezd
                minus=true;
            }
            else
            {
                t+=c;
            }
        }
    }

    for( i=decpos+1; i<templateStr.length(); i++ ) //tizedespont utan
    {
        char c=text.charAt(i); 
        t+=(isDigit(c) ? c:'0');
    }
    
    t="0"+t;
    while( t.length()>wfract+1 && t.charAt(0)=='0' && isDigit(t.charAt(1)) )
    {
        t=t.substring(1);
    }

    if( minus )
    {
        t='-'+t;
    }
    
    for( i=templateStr.length()-1,
                          j=t.length()-1; i>=0 && j>=0; i-- )
    {
        //System.out.println(templateStr);
        //System.out.println(replicate(" ",i)+"^");

        if( isEditable(i)  || (t.charAt(j)=='-') )
        {
            t1=t.charAt(j)+t1;
            j--;
        }
        else 
        {
            t1=templateStr.charAt(i)+t1;
        }
    }
    
    //(new Exception("DEBUG")).printStackTrace();
    //System.err.println( "["+ t1 +"]"  );
 
    text=replicate(" ",templateStr.length()-t1.length())+t1; 
    return setpos(decpos);
}

//---------------------------------------------------------------------------
public boolean verifyF()
{
    return flagF;
}

//---------------------------------------------------------------------------
public boolean verifyX()
{
    return flagX;
}

//---------------------------------------------------------------------------
public boolean verify()
{
         if( flagN )   return verif_n();
    else if( flagD )   return verif_d();
    else if( flagL )   return verif_l();
    else               return verif_c();
}
 
//---------------------------------------------------------------------------
private boolean verif_c()
{
    //System.out.println("verify_c");

    if( templateStr!=null )
    {
        for( int i=0; i<templateStr.length(); i++ )
        {
            if(  templateStr.charAt(i)!='X' && text.charAt(i)==' '  )
            {
                if( flagE && isEmpty() )
                {
                    return true; //teljesen ures megengedett
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return true;
}

//---------------------------------------------------------------------------
private boolean verif_n()
{
    //System.out.println("verify_n");
    normalize();
    return true;
}

//---------------------------------------------------------------------------
private boolean verif_d()
{
    //System.out.println("verify_d");

    if( text.indexOf(' ')>=0 )
    {
        if( flagE && isEmpty() )
        {
            return true; //teljesen ures megengedett 
        }
        else
        {
            return false;
        }
    }
    
    int year  = Integer.parseInt(text.substring(0, 4));
    int month = Integer.parseInt(text.substring(5, 7));
    int day   = Integer.parseInt(text.substring(8,10));
    int dom[] = {31,29,31,30,31,30,31,31,30,31,30,31};
    
    if( year<1900 || 2100<year )
    {
        return false;
    }
    else if( month<1 || 12<month )
    {
        return false;
    }
    else if( day<1 || dom[month-1]<day )
    {
        return false;
    }
    else if( month==2 && day==29 )
    {
        if( (year%4)!=0 || ((year%100)==0 && (year%400)!=0) )
        {
            return false;
        }
    }
    return true;
}

//---------------------------------------------------------------------------
private boolean verif_l()
{
    //System.out.println("verify_l");
    return  text.length()==1 && 0<=LOGICAL.indexOf(text); 
}


//---------------------------------------------------------------------------
public void normalize()
{
    if( flagN )
    {
        normalize_n();
    }
    else if( flagD )
    {
        normalize_d();
    }
    else if( flagL )
    {
        normalize_l();
    }
    else
    {
        normalize_c();
    }
}
 
//---------------------------------------------------------------------------
public void normalize_c() 
{
}

//---------------------------------------------------------------------------
public void normalize_n() 
{
    dot(decpos);
    setSuperText(0);
    tfield.setCaretPosition(0); 
}
 
//---------------------------------------------------------------------------
public void normalize_d() 
{
}

//---------------------------------------------------------------------------
public void normalize_l() 
{
}

//---------------------------------------------------------------------------
}

 