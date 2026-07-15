
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

#ifndef SMTP_H
#define SMTP_H

// address types
#define SMTP_ADDRESS_FROM           0
#define SMTP_ADDRESS_TO             1
#define SMTP_ADDRESS_CC             2
#define SMTP_ADDRESS_BCC            3

// connection mode
#define SMTP_SECURITY_STARTTLS      0
#define SMTP_SECURITY_TLS           1
#define SMTP_SECURITY_NONE          2

// authentication
#define SMTP_AUTH_CRAM_MD5          0
#define SMTP_AUTH_NONE              1
#define SMTP_AUTH_PLAIN             2
#define SMTP_AUTH_LOGIN             3


// result codes
#define SMTP_INTERNAL_ERROR         -1
#define SMTP_READY                  220
#define SMTP_CLOSE                  221
#define SMTP_AUTH_SUCCESS           235
#define SMTP_DONE                   250
#define SMTP_AUTH_CONTINUE          334
#define SMTP_BEGIN_MAIL             354

#endif SMTP_H
