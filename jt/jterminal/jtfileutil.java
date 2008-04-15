
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
import org.w3c.dom.*;
 
//============================================================================
public class jtfileutil{
//============================================================================

//----------------------------------------------------------------------------
static public void makedir(jterminal jterm, String name)
{
    File f=new File(name);
    answer(jterm,"makedir",f.mkdir());
}

//----------------------------------------------------------------------------
static public void makedirs(jterminal jterm, String name)
{
    File f=new File(name);
    answer(jterm,"makedirs",f.mkdirs());
}

//----------------------------------------------------------------------------
static public void delete(jterminal jterm, String name)
{
    File f=new File(name);
    answer(jterm,"delete",f.delete());
}

//----------------------------------------------------------------------------
static public void exists(jterminal jterm, String name)
{
    File f=new File(name);
    answer(jterm,"exists",f.exists());
}

//----------------------------------------------------------------------------
static public void isfile(jterminal jterm, String name)
{
    File f=new File(name);
    answer(jterm,"isfile",f.isFile());
}

//----------------------------------------------------------------------------
static public void isdirectory(jterminal jterm, String name)
{
    File f=new File(name);
    answer(jterm,"isdirectory",f.isDirectory());
}
 
//----------------------------------------------------------------------------
static public void rename(jterminal jterm, String oldname, String newname)
{
    File fo=new File(oldname);
    File fn=new File(newname);
    answer(jterm,"rename",fo.renameTo(fn));
}


//----------------------------------------------------------------------------
static private void answer(jterminal jterm, String cmd, boolean result)
{
    jterm.send("<"+cmd+">"+(result?"true":"false")+"</"+cmd+">"); 
}
 
//----------------------------------------------------------------------------
} 
