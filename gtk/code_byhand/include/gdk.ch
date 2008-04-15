
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

#ifndef _GDK_CH_
#define _GDK_CH_

//C++-ban és CCC3-ban is érvényes szintaktika kell! 

//GdkEventType
#define  GDK_NOTHING                    -1
#define  GDK_DELETE                     0
#define  GDK_DESTROY                    1
#define  GDK_EXPOSE                     2
#define  GDK_MOTION_NOTIFY              3
#define  GDK_BUTTON_PRESS               4
#define  GDK_2BUTTON_PRESS              5
#define  GDK_3BUTTON_PRESS              6
#define  GDK_BUTTON_RELEASE             7
#define  GDK_KEY_PRESS                  8
#define  GDK_KEY_RELEASE                9
#define  GDK_ENTER_NOTIFY               10
#define  GDK_LEAVE_NOTIFY               11
#define  GDK_FOCUS_CHANGE               12
#define  GDK_CONFIGURE                  13
#define  GDK_MAP                        14
#define  GDK_UNMAP                      15
#define  GDK_PROPERTY_NOTIFY            16
#define  GDK_SELECTION_CLEAR            17
#define  GDK_SELECTION_REQUEST          18
#define  GDK_SELECTION_NOTIFY           19
#define  GDK_PROXIMITY_IN               20
#define  GDK_PROXIMITY_OUT              21
#define  GDK_DRAG_ENTER                 22
#define  GDK_DRAG_LEAVE                 23
#define  GDK_DRAG_MOTION                24
#define  GDK_DRAG_STATUS                25
#define  GDK_DROP_START                 26
#define  GDK_DROP_FINISHED              27
#define  GDK_CLIENT_EVENT               28
#define  GDK_VISIBILITY_NOTIFY          29
#define  GDK_NO_EXPOSE                  30
#define  GDK_SCROLL                     31
#define  GDK_WINDOW_STATE               32
#define  GDK_SETTING                    33

//GdkEventMask
#define  GDK_EXPOSURE_MASK              0x2
#define  GDK_POINTER_MOTION_MASK        0x4
#define  GDK_POINTER_MOTION_HINT_MASK   0x8
#define  GDK_BUTTON_MOTION_MASK         0x10
#define  GDK_BUTTON1_MOTION_MASK        0x20
#define  GDK_BUTTON2_MOTION_MASK        0x40
#define  GDK_BUTTON3_MOTION_MASK        0x80
#define  GDK_BUTTON_PRESS_MASK          0x100
#define  GDK_BUTTON_RELEASE_MASK        0x200
#define  GDK_KEY_PRESS_MASK             0x400
#define  GDK_KEY_RELEASE_MASK           0x800
#define  GDK_ENTER_NOTIFY_MASK          0x1000
#define  GDK_LEAVE_NOTIFY_MASK          0x2000
#define  GDK_FOCUS_CHANGE_MASK          0x4000
#define  GDK_STRUCTURE_MASK             0x8000
#define  GDK_PROPERTY_CHANGE_MASK       0x10000
#define  GDK_VISIBILITY_NOTIFY_MASK     0x20000
#define  GDK_PROXIMITY_IN_MASK          0x40000
#define  GDK_PROXIMITY_OUT_MASK         0x80000
#define  GDK_SUBSTRUCTURE_MASK          0x100000
#define  GDK_SCROLL_MASK                0x200000
#define  GDK_ALL_EVENTS_MASK            0x3ffffe

//GdkModifierType;
#define  GDK_SHIFT_MASK                 0x1
#define  GDK_LOCK_MASK                  0x2
#define  GDK_CONTROL_MASK               0x4
#define  GDK_MOD1_MASK                  0x8
#define  GDK_MOD2_MASK                  0x10
#define  GDK_MOD3_MASK                  0x20
#define  GDK_MOD4_MASK                  0x40
#define  GDK_MOD5_MASK                  0x80
#define  GDK_BUTTON1_MASK               0x100
#define  GDK_BUTTON2_MASK               0x200
#define  GDK_BUTTON3_MASK               0x400
#define  GDK_BUTTON4_MASK               0x800
#define  GDK_BUTTON5_MASK               0x1000
#define  GDK_RELEASE_MASK               0x40000000
#define  GDK_MODIFIER_MASK              0x40001fff

#endif // _GDK_CH_
