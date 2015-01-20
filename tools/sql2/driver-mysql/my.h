
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
