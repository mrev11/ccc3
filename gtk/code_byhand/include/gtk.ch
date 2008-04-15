
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
 

#ifndef _GTK_CH_
#define _GTK_CH_

//C++-ban és CCC3-ban is érvényes szintaktika kell! 

//GtkWindowType
#define  GTK_WINDOW_TOPLEVEL            0
#define  GTK_WINDOW_POPUP               1

//GtkAttachOptions
#define  GTK_EXPAND                     1
#define  GTK_SHRINK                     2
#define  GTK_FILL                       4

//GtkPackType
#define  GTK_PACK_START                 0
#define  GTK_PACK_END                   1

//GtkReliefStyle
#define  GTK_RELIEF_NORMAL              0
#define  GTK_RELIEF_HALF                1
#define  GTK_RELIEF_NONE                2

//GtkShadowType
#define  GTK_SHADOW_NONE                0
#define  GTK_SHADOW_IN                  1
#define  GTK_SHADOW_OUT                 2
#define  GTK_SHADOW_ETCHED_IN           3
#define  GTK_SHADOW_ETCHED_OUT          4

//GtkSelectionMode
#define  GTK_SELECTION_NONE             0
#define  GTK_SELECTION_SINGLE           1
#define  GTK_SELECTION_BROWSE           2
#define  GTK_SELECTION_MULTIPLE         3

//GtkPolicyType
#define  GTK_POLICY_ALWAYS              0
#define  GTK_POLICY_AUTOMATIC           1
#define  GTK_POLICY_NEVER               2

//GtkTreeViewMode
#define  GTK_TREE_VIEW_LINE             0
#define  GTK_TREE_VIEW_ITEM             1

//GtkArrowType
#define  GTK_ARROW_UP                   0
#define  GTK_ARROW_DOWN                 1
#define  GTK_ARROW_LEFT                 2
#define  GTK_ARROW_RIGHT                3

//GtkShadowType
#define  GTK_SHADOW_NONE                0
#define  GTK_SHADOW_IN                  1
#define  GTK_SHADOW_OUT                 2
#define  GTK_SHADOW_ETCHED_IN           3
#define  GTK_SHADOW_ETCHED_OUT          4

//GtkButtonBoxStyle
#define  GTK_BUTTONBOX_DEFAULT_STYLE    0
#define  GTK_BUTTONBOX_SPREAD           1
#define  GTK_BUTTONBOX_EDGE             2
#define  GTK_BUTTONBOX_START            3
#define  GTK_BUTTONBOX_END              4

//GtkStateType  
#define  GTK_STATE_NORMAL               0
#define  GTK_STATE_ACTIVE               1
#define  GTK_STATE_PRELIGHT             2
#define  GTK_STATE_SELECTED             3
#define  GTK_STATE_INSENSITIVE          4


//GtkDialogFlags;
#define  GTK_DIALOG_MODAL               1
#define  GTK_DIALOG_DESTROY_WITH_PARENT 2
#define  GTK_DIALOG_NO_SEPARATOR        4

//GtkMessageType;
#define  GTK_MESSAGE_INFO               0
#define  GTK_MESSAGE_WARNING            1
#define  GTK_MESSAGE_QUESTION           2
#define  GTK_MESSAGE_ERROR              3

//GtkButtonsType;
#define  GTK_BUTTONS_NONE               0
#define  GTK_BUTTONS_OK                 1
#define  GTK_BUTTONS_CLOSE              2
#define  GTK_BUTTONS_CANCEL             3
#define  GTK_BUTTONS_YES_NO             4
#define  GTK_BUTTONS_OK_CANCEL          5



//GtkResponseType
#define  GTK_RESPONSE_NONE              -1
#define  GTK_RESPONSE_REJECT            -2
#define  GTK_RESPONSE_ACCEPT            -3
#define  GTK_RESPONSE_DELETE_EVENT      -4
#define  GTK_RESPONSE_OK                -5
#define  GTK_RESPONSE_CANCEL            -6
#define  GTK_RESPONSE_CLOSE             -7
#define  GTK_RESPONSE_YES               -8
#define  GTK_RESPONSE_NO                -9
#define  GTK_RESPONSE_APPLY             -10
#define  GTK_RESPONSE_HELP              -11


//GtkWidgetFlags
#define  GTK_TOPLEVEL                   0x10
#define  GTK_NO_WINDOW                  0x20
#define  GTK_REALIZED                   0x40
#define  GTK_MAPPED                     0x80
#define  GTK_VISIBLE                    0x100
#define  GTK_SENSITIVE                  0x200
#define  GTK_PARENT_SENSITIVE           0x400
#define  GTK_CAN_FOCUS                  0x800
#define  GTK_HAS_FOCUS                  0x1000
#define  GTK_CAN_DEFAULT                0x2000
#define  GTK_HAS_DEFAULT                0x4000
#define  GTK_HAS_GRAB                   0x8000
#define  GTK_RC_STYLE                   0x10000
#define  GTK_COMPOSITE_CHILD            0x20000
#define  GTK_NO_REPARENT                0x40000
#define  GTK_APP_PAINTABLE              0x80000
#define  GTK_RECEIVES_DEFAULT           0x100000
#define  GTK_DOUBLE_BUFFERED            0x200000


#define GTK_TYPE_MENU_BAR       gtk.menu_bar.get_type()
#define GTK_TYPE_MENU           gtk.menu.get_type()
#define GTK_TYPE_OPTION_MENU    gtk.option_menu.get_type()

//GtkTreeViewColumnSizing
#define  GTK_TREE_VIEW_COLUMN_GROW_ONLY 0
#define  GTK_TREE_VIEW_COLUMN_AUTOSIZE  1
#define  GTK_TREE_VIEW_COLUMN_FIXED     2

//GtkSelectionMode
#define  GTK_SELECTION_NONE             0
#define  GTK_SELECTION_SINGLE           1
#define  GTK_SELECTION_BROWSE           2 
#define  GTK_SELECTION_MULTIPLE         3

//GtkIconSize
#define  GTK_ICON_SIZE_INVALID          0
#define  GTK_ICON_SIZE_MENU             1
#define  GTK_ICON_SIZE_SMALL_TOOLBAR    2
#define  GTK_ICON_SIZE_LARGE_TOOLBAR    3
#define  GTK_ICON_SIZE_BUTTON           4
#define  GTK_ICON_SIZE_DND              5
#define  GTK_ICON_SIZE_DIALOG           6

//GtkNotebook
#define  GTK_POS_LEFT                   0
#define  GTK_POS_RIGHT                  1
#define  GTK_POS_TOP                    2
#define  GTK_POS_BOTTOM                 3

//GtkFileChooserAction
#define  GTK_FILE_CHOOSER_ACTION_OPEN   0
#define  GTK_FILE_CHOOSER_ACTION_SAVE   1
#define  GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER  2
#define  GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER  3

//GtkJustification
#define  GTK_JUSTIFY_LEFT               0
#define  GTK_JUSTIFY_RIGHT              1
#define  GTK_JUSTIFY_CENTER             2
#define  GTK_JUSTIFY_FILL               3

//GtkWrapMode
#define  GTK_WRAP_NONE                  0
#define  GTK_WRAP_CHAR                  1
#define  GTK_WRAP_WORD                  2

//GtkFileChooserAction
#define  GTK_FILE_CHOOSER_ACTION_OPEN               0
#define  GTK_FILE_CHOOSER_ACTION_SAVE               1
#define  GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER      2
#define  GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER      3

//GtkFileChooserConfirmation
#define  GTK_FILE_CHOOSER_CONFIRMATION_CONFIRM          0
#define  GTK_FILE_CHOOSER_CONFIRMATION_ACCEPT_FILENAME  1
#define  GTK_FILE_CHOOSER_CONFIRMATION_SELECT_AGAIN     2

//GtkToolbarStyle
#define  GTK_TOOLBAR_ICONS          0
#define  GTK_TOOLBAR_TEXT           1
#define  GTK_TOOLBAR_BOTH           2
#define  GTK_TOOLBAR_BOTH_HORIZ     3

//GtkOrientation
#define  GTK_ORIENTATION_HORIZONTAL 0
#define  GTK_ORIENTATION_VERTICAL   1

//GtkWindowPosition
#define  GTK_WIN_POS_NONE               0
#define  GTK_WIN_POS_CENTER             1
#define  GTK_WIN_POS_MOUSE              2
#define  GTK_WIN_POS_CENTER_ALWAYS      3
#define  GTK_WIN_POS_CENTER_ON_PARENT   4


#define GTK_STOCK_DIALOG_AUTHENTICATION "gtk-dialog-authentication"
#define GTK_STOCK_DIALOG_INFO      "gtk-dialog-info"
#define GTK_STOCK_DIALOG_WARNING   "gtk-dialog-warning"
#define GTK_STOCK_DIALOG_ERROR     "gtk-dialog-error"
#define GTK_STOCK_DIALOG_QUESTION  "gtk-dialog-question"
#define GTK_STOCK_DND              "gtk-dnd"
#define GTK_STOCK_DND_MULTIPLE     "gtk-dnd-multiple"
#define GTK_STOCK_ABOUT            "gtk-about"
#define GTK_STOCK_ADD              "gtk-add"
#define GTK_STOCK_APPLY            "gtk-apply"
#define GTK_STOCK_BOLD             "gtk-bold"
#define GTK_STOCK_CANCEL           "gtk-cancel"
#define GTK_STOCK_CDROM            "gtk-cdrom"
#define GTK_STOCK_CLEAR            "gtk-clear"
#define GTK_STOCK_CLOSE            "gtk-close"
#define GTK_STOCK_COLOR_PICKER     "gtk-color-picker"
#define GTK_STOCK_CONVERT          "gtk-convert"
#define GTK_STOCK_CONNECT          "gtk-connect"
#define GTK_STOCK_COPY             "gtk-copy"
#define GTK_STOCK_CUT              "gtk-cut"
#define GTK_STOCK_DELETE           "gtk-delete"
#define GTK_STOCK_DIRECTORY        "gtk-directory"
#define GTK_STOCK_DISCONNECT       "gtk-disconnect"
#define GTK_STOCK_EDIT             "gtk-edit"
#define GTK_STOCK_EXECUTE          "gtk-execute"
#define GTK_STOCK_FILE             "gtk-file"
#define GTK_STOCK_FIND             "gtk-find"
#define GTK_STOCK_FIND_AND_REPLACE "gtk-find-and-replace"
#define GTK_STOCK_FLOPPY           "gtk-floppy"
#define GTK_STOCK_GOTO_BOTTOM      "gtk-goto-bottom"
#define GTK_STOCK_GOTO_FIRST       "gtk-goto-first"
#define GTK_STOCK_GOTO_LAST        "gtk-goto-last"
#define GTK_STOCK_GOTO_TOP         "gtk-goto-top"
#define GTK_STOCK_GO_BACK          "gtk-go-back"
#define GTK_STOCK_GO_DOWN          "gtk-go-down"
#define GTK_STOCK_GO_FORWARD       "gtk-go-forward"
#define GTK_STOCK_GO_UP            "gtk-go-up"
#define GTK_STOCK_HARDDISK         "gtk-harddisk"
#define GTK_STOCK_HELP             "gtk-help"
#define GTK_STOCK_HOME             "gtk-home"
#define GTK_STOCK_INDEX            "gtk-index"
#define GTK_STOCK_INDENT           "gtk-indent"
#define GTK_STOCK_UNINDENT         "gtk-unindent"
#define GTK_STOCK_ITALIC           "gtk-italic"
#define GTK_STOCK_JUMP_TO          "gtk-jump-to"
#define GTK_STOCK_JUSTIFY_CENTER   "gtk-justify-center"
#define GTK_STOCK_JUSTIFY_FILL     "gtk-justify-fill"
#define GTK_STOCK_JUSTIFY_LEFT     "gtk-justify-left"
#define GTK_STOCK_JUSTIFY_RIGHT    "gtk-justify-right"
#define GTK_STOCK_MISSING_IMAGE    "gtk-missing-image"
#define GTK_STOCK_MEDIA_FORWARD    "gtk-media-forward"
#define GTK_STOCK_MEDIA_NEXT       "gtk-media-next"
#define GTK_STOCK_MEDIA_PAUSE      "gtk-media-pause"
#define GTK_STOCK_MEDIA_PLAY       "gtk-media-play"
#define GTK_STOCK_MEDIA_PREVIOUS   "gtk-media-previous"
#define GTK_STOCK_MEDIA_RECORD     "gtk-media-record"
#define GTK_STOCK_MEDIA_REWIND     "gtk-media-rewind"
#define GTK_STOCK_MEDIA_STOP       "gtk-media-stop"
#define GTK_STOCK_NETWORK          "gtk-network"
#define GTK_STOCK_NEW              "gtk-new"
#define GTK_STOCK_NO               "gtk-no"
#define GTK_STOCK_OK               "gtk-ok"
#define GTK_STOCK_OPEN             "gtk-open"
#define GTK_STOCK_PASTE            "gtk-paste"
#define GTK_STOCK_PREFERENCES      "gtk-preferences"
#define GTK_STOCK_PRINT            "gtk-print"
#define GTK_STOCK_PRINT_PREVIEW    "gtk-print-preview"
#define GTK_STOCK_PROPERTIES       "gtk-properties"
#define GTK_STOCK_QUIT             "gtk-quit"
#define GTK_STOCK_REDO             "gtk-redo"
#define GTK_STOCK_REFRESH          "gtk-refresh"
#define GTK_STOCK_REMOVE           "gtk-remove"
#define GTK_STOCK_REVERT_TO_SAVED  "gtk-revert-to-saved"
#define GTK_STOCK_SAVE             "gtk-save"
#define GTK_STOCK_SAVE_AS          "gtk-save-as"
#define GTK_STOCK_SELECT_COLOR     "gtk-select-color"
#define GTK_STOCK_SELECT_FONT      "gtk-select-font"
#define GTK_STOCK_SORT_ASCENDING   "gtk-sort-ascending"
#define GTK_STOCK_SORT_DESCENDING  "gtk-sort-descending"
#define GTK_STOCK_SPELL_CHECK      "gtk-spell-check"
#define GTK_STOCK_STOP             "gtk-stop"
#define GTK_STOCK_STRIKETHROUGH    "gtk-strikethrough"
#define GTK_STOCK_UNDELETE         "gtk-undelete"
#define GTK_STOCK_UNDERLINE        "gtk-underline"
#define GTK_STOCK_UNDO             "gtk-undo"
#define GTK_STOCK_YES              "gtk-yes"
#define GTK_STOCK_ZOOM_100         "gtk-zoom-100"
#define GTK_STOCK_ZOOM_FIT         "gtk-zoom-fit"
#define GTK_STOCK_ZOOM_IN          "gtk-zoom-in"
#define GTK_STOCK_ZOOM_OUT         "gtk-zoom-out"

#endif
