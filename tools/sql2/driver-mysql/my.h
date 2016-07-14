
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

#ifdef NOT_DEFINED

#include <mysql/mysql.h>

#else

// valójában csak ezek kellenek mysql.h-ból
// ezekkel a definíciókkal a projekt lefordul 
// a libmysqlclient-dev csomag telepítése nélkül is
// a futáshoz csak az kell, hogy a dlopen megtalálja
// és be tudja tölteni libmysqlclient_r.so-t
// kétség esetén vissza lehet térni mysql.h-hoz

typedef unsigned long long my_ulonglong;

typedef struct st_mysql {} MYSQL;
typedef struct st_mysql_res {} MYSQL_RES;
typedef struct st_mysql_field {char *name;} MYSQL_FIELD;
typedef char **MYSQL_ROW;


// az alábbiak egy az egybe át vannak véve

extern MYSQL *mysql_init(MYSQL *mysql);
extern void mysql_close(MYSQL *mysql);
extern unsigned int mysql_errno(MYSQL *mysql);
extern const char *mysql_error(MYSQL *mysql);
extern MYSQL *mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag);
extern const char *mysql_get_server_info(MYSQL *mysql);
extern const char *mysql_character_set_name(MYSQL *mysql);

extern int mysql_real_query(MYSQL *mysql, const char *stmt_str, unsigned long length);
extern MYSQL_RES *mysql_store_result(MYSQL *mysql);
extern void mysql_free_result(MYSQL_RES *result);
extern unsigned int mysql_field_count(MYSQL *mysql);
extern unsigned int mysql_num_fields(MYSQL_RES *result);
extern my_ulonglong mysql_affected_rows(MYSQL *mysql);
extern MYSQL_FIELD *mysql_fetch_field_direct(MYSQL_RES *result, unsigned int fieldnr);
extern MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);
extern unsigned long* mysql_fetch_lengths(MYSQL_RES *result);

#endif
