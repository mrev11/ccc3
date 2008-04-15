
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

import java.awt.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.*;
 
//============================================================================
public class tablefield extends JTable{
//============================================================================

public static Font tablefont=getutil.getposition.getSmallMonoFont(); 
public static int fontsize=getutil.getposition.getFontSize(tablefont);
public static int fontwidth=getutil.getposition.getFontWidth(tablefont);

public TableColumnModel columnModel;
 
//----------------------------------------------------------------------------
public tablefield()
{
    setFont(tablefont);
    columnModel=new DefaultTableColumnModel();
}
    
//----------------------------------------------------------------------------
public void addcolumn(int modelindex, String name, int width)
{
    TableColumn c=new TableColumn(modelindex);
    c.setHeaderValue(name);
    c.setPreferredWidth(getutil.getposition.xpos(width));
    columnModel.addColumn(c);
    setColumnModel(columnModel);
}
    
//----------------------------------------------------------------------------
public void changed()
{
    tableChanged(new TableModelEvent( getModel() ) );
}

//----------------------------------------------------------------------------
}

