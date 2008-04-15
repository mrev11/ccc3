
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

#ifndef __SSL_CH__
#define __SSL_CH__

#define SSL_VERIFY_NONE                     0x00
#define SSL_VERIFY_PEER                     0x01
#define SSL_VERIFY_FAIL_IF_NO_PEER_CERT     0x02
#define SSL_VERIFY_CLIENT_ONCE              0x04
#define SSL_VERIFY_PEER_CERT                (SSL_VERIFY_PEER+SSL_VERIFY_FAIL_IF_NO_PEER_CERT+SSL_VERIFY_CLIENT_ONCE)


// see: man 3 SSL_CTX_set_session_cache_mode
#define SSL_SESS_CACHE_OFF                  0x0000
#define SSL_SESS_CACHE_CLIENT               0x0001
#define SSL_SESS_CACHE_SERVER               0x0002
#define SSL_SESS_CACHE_BOTH                 (SSL_SESS_CACHE_CLIENT+SSL_SESS_CACHE_SERVER)
#define SSL_SESS_CACHE_NO_AUTO_CLEAR        0x0080
#define SSL_SESS_CACHE_NO_INTERNAL_LOOKUP   0x0100
#define SSL_SESS_CACHE_NO_INTERNAL_STORE    0x0200
#define SSL_SESS_CACHE_NO_INTERNAL          (SSL_SESS_CACHE_NO_INTERNAL_LOOKUP+SSL_SESS_CACHE_NO_INTERNAL_STORE)

#endif // __SSL_CH__
