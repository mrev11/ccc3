
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

%{
#define GTKSYM_LEXER
#include <gtksym_lexer.h>
#include <gtk.ch>
#include <gdk.ch>

#ifdef EMLEKEZTETO
  Az a probléma, hogy a glade fájlokban szimbolikus konstansokkal
  végzett műveletekkel magadott értékek vannak (néha az XML tag
  szövegeként, néha egy attribútum értékeként). Például:
    
  <accelerator key="P" modifiers="GDK_SHIFT_MASK | GDK_MOD1_MASK" signal="activate"/>
    
  C kód generálására ez jó, minden más esetben nehézséget okoz, 
  hogy megkapjuk a konkrét számértéket. A konkrét számok kiszámítására 
  való ez a kis elemző.
#endif

%}

%option c++
%option yyclass="gtksym_lexer"
%option noyywrap
%option stack
%option prefix="gtksym"

number   [0-9]+
xnumber  [0][xX][0-9a-fA-F]+

%%

"GDK_SHIFT_MASK"            {value=GDK_SHIFT_MASK; return NUMBER;}
"GDK_LOCK_MASK"             {value=GDK_LOCK_MASK; return NUMBER;}
"GDK_CONTROL_MASK"          {value=GDK_CONTROL_MASK; return NUMBER;}
"GDK_MOD1_MASK"             {value=GDK_MOD1_MASK; return NUMBER;}
"GDK_MOD2_MASK"             {value=GDK_MOD2_MASK; return NUMBER;}

"GTK_WINDOW_TOPLEVEL"       {value=GTK_WINDOW_TOPLEVEL; return NUMBER;}
"GTK_WINDOW_POPUP"          {value=GTK_WINDOW_POPUP; return NUMBER;}

"GTK_POLICY_ALWAYS"         {value=GTK_POLICY_ALWAYS; return NUMBER;}
"GTK_POLICY_AUTOMATIC"      {value=GTK_POLICY_AUTOMATIC; return NUMBER;}
"GTK_POLICY_NEVER"          {value=GTK_POLICY_NEVER; return NUMBER;}

"GTK_JUSTIFY_LEFT"          {value=GTK_JUSTIFY_LEFT; return NUMBER;}
"GTK_JUSTIFY_RIGHT"         {value=GTK_JUSTIFY_RIGHT; return NUMBER;}
"GTK_JUSTIFY_CENTER"        {value=GTK_JUSTIFY_CENTER; return NUMBER;}
"GTK_JUSTIFY_FILL"          {value=GTK_JUSTIFY_FILL; return NUMBER;}

"GTK_WRAP_NONE"             {value=GTK_WRAP_NONE; return NUMBER;}
"GTK_WRAP_CHAR"             {value=GTK_WRAP_CHAR; return NUMBER;}
"GTK_WRAP_WORD"             {value=GTK_WRAP_WORD; return NUMBER;}

"GTK_BUTTONBOX_DEFAULT_STYLE" {value=GTK_BUTTONBOX_DEFAULT_STYLE; return NUMBER;}
"GTK_BUTTONBOX_SPREAD"      {value=GTK_BUTTONBOX_SPREAD; return NUMBER;}
"GTK_BUTTONBOX_EDGE"        {value=GTK_BUTTONBOX_EDGE; return NUMBER;}
"GTK_BUTTONBOX_START"       {value=GTK_BUTTONBOX_START; return NUMBER;}
"GTK_BUTTONBOX_END"         {value=GTK_BUTTONBOX_END; return NUMBER;}

"GTK_POS_LEFT"              {value=GTK_POS_LEFT; return NUMBER;}
"GTK_POS_RIGHT"             {value=GTK_POS_RIGHT; return NUMBER;}
"GTK_POS_TOP"               {value=GTK_POS_TOP; return NUMBER;}
"GTK_POS_BOTTOM"            {value=GTK_POS_BOTTOM; return NUMBER;}

"GTK_FILE_CHOOSER_ACTION_OPEN"           {value=GTK_FILE_CHOOSER_ACTION_OPEN; return NUMBER;}
"GTK_FILE_CHOOSER_ACTION_SAVE"           {value=GTK_FILE_CHOOSER_ACTION_SAVE; return NUMBER;}
"GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER"  {value=GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER; return NUMBER;}
"GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER"  {value=GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER; return NUMBER;}

"GTK_TOOLBAR_ICONS"         {value=GTK_TOOLBAR_ICONS; return NUMBER;}
"GTK_TOOLBAR_TEXT"          {value=GTK_TOOLBAR_TEXT; return NUMBER;}
"GTK_TOOLBAR_BOTH"          {value=GTK_TOOLBAR_BOTH; return NUMBER;}
"GTK_TOOLBAR_BOTH_HORIZ"    {value=GTK_TOOLBAR_BOTH_HORIZ; return NUMBER;}

"GTK_WIN_POS_NONE"              {value=GTK_WIN_POS_NONE; return NUMBER;}
"GTK_WIN_POS_CENTER"            {value=GTK_WIN_POS_CENTER; return NUMBER;}
"GTK_WIN_POS_MOUSE"             {value=GTK_WIN_POS_MOUSE; return NUMBER;}
"GTK_WIN_POS_CENTER_ALWAYS"     {value=GTK_WIN_POS_CENTER_ALWAYS; return NUMBER;}
"GTK_WIN_POS_CENTER_ON_PARENT"  {value=GTK_WIN_POS_CENTER_ON_PARENT; return NUMBER;}

{number}                    {value=(int)strtoul(YYText(),0,10); return NUMBER;}
{xnumber}                   {value=(int)strtoul(YYText(),0,16); return NUMBER;}

"|"                         {return OR;}
"&"                         {return AND;}
"+"                         {return PLUS;}
"-"                         {return MINUS;}
"("                         {return LPAR;}
")"                         {return RPAR;}
.
\n

%%


