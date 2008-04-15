
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

//beolvassa a default keystore-t,
//es adogatja belole az objektumokat
 
import java.io.*;
import java.security.*;
 
//===========================================================================
public class ksutil {
//===========================================================================

private static KeyStore ks=null;

static 
{
    try
    {
        //System.out.println("Loading keystore ...");
    
        ks=KeyStore.getInstance("JKS");
        String home=System.getProperty("user.home");
        String filsep=System.getProperty("file.separator");
        String ksfile=home+filsep+".keystore";
        ks.load(new FileInputStream(ksfile),null);
    }
    catch( Exception e)
    {
        ks=null;
    }
}

//---------------------------------------------------------------------------
static PrivateKey getPrivateKey(String alias, String passw) throws Exception  
{
    return (PrivateKey)ks.getKey(alias,passw.toCharArray());
} 

//---------------------------------------------------------------------------
static PrivateKey getPrivateKey(String alias, char[] passw) throws Exception  
{
    return (PrivateKey)ks.getKey(alias,passw);
} 
 
//---------------------------------------------------------------------------
static PublicKey getPublicKey(String alias) throws Exception  
{
    return ks.getCertificate(alias).getPublicKey(); 
} 

//---------------------------------------------------------------------------
static java.security.cert.Certificate getCertificate(String alias) throws Exception  
{
    return ks.getCertificate(alias); 
} 
 
//---------------------------------------------------------------------------
} 
