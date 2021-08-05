
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

//interfesz az sckutil.cpp-hez

#define  SOCKOPT_NODELAY        1
#define  SOCKOPT_NONBLOCKING    2
#define  SOCKOPT_REUSEADDR      3
#define  SOCKOPT_REUSEPORT      4
 
extern int socket_wsastartup();
extern int socket_new();
extern int socket_tcp();
extern int socket_udp();
extern int socket_bind(int socket, char *ipaddr, int port); //compat
extern int socket_bind(int socket, const char *ipaddr, int port);
extern int socket_listen(int socket, int queuelength);
extern int socket_listen(int socket);
extern int socket_accept(int srvsocket);
extern int socket_connect(int socket, char *ipaddr, int port); //compat
extern int socket_connect(int socket, const char *ipaddr, int port);
extern int socket_setoption(int s, int option, int value);
extern int socket_noinherit(int socket);
extern int socket_available(int sck);
extern int socket_write(int socket, void*src, int datalen);
extern int socket_read(int socket, void*dest, int datalen, int wtime);
extern int socket_close(int socket);
extern int socket_error();
 
extern int client_socket_new(const char *ipaddr, int port);
extern int server_socket_new(const char *ipaddr, int port);
extern int server_socket_new(const char *ipaddr, int port, int qlen);

extern int client_socket(char *ipaddr, int port); //compat
extern int client_socket(const char *ipaddr, int port);
extern int server_socket(const char *ipaddr, int port);
extern int server_socket(const char *ipaddr, int port, int qlen);

extern int server_socket_accept(int srvsck);

