
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

//SIGNAL.CH for CCC

#ifndef _SIGNAL_CH_
#define _SIGNAL_CH_

#define SIG_HUP        1    // Hangup (POSIX)
#define SIG_INT        2    // Interrupt (ANSI)
#define SIG_QUIT       4    // Quit (POSIX)
#define SIG_ILL        8    // Illegal instruction (ANSI)
#define SIG_ABRT      16    // Abort (ANSI)
#define SIG_FPE       32    // Floating-point exception (ANSI)
#define SIG_SEGV      64    // Segmentation violation (ANSI)
#define SIG_PIPE     128    // Broken pipe (POSIX)
#define SIG_TERM     256    // Termination (ANSI)

#define SIG_CONT    1024    // Continue (POSIX)
#define SIG_STOP    2048    // Stop, unblockable (POSIX)
#define SIG_KILL    4096    // Kill, unblockable (POSIX)

#endif//_SIGNAL_CH_
