
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


//Ezek kellenek az eredeti libpq-fe.h-ból az interfész lefordításához.
//Ezzel akkor is megy a fordítás, ha nincs installálva a Postgres.


typedef unsigned int Oid;
typedef struct pg_result PGresult;
typedef struct pg_conn PGconn;

typedef enum
{
    CONNECTION_OK,
    CONNECTION_BAD
} ConnStatusType;

typedef enum
{
    PGRES_EMPTY_QUERY = 0,      /* empty query string was executed */
    PGRES_COMMAND_OK,           /* a query command that doesn't return
                                 * anything was executed properly by the
                                 * backend */
    PGRES_TUPLES_OK,            /* a query command that returns tuples was
                                 * executed properly by the backend, PGresult
                                 * contains the result tuples */
    PGRES_COPY_OUT,             /* Copy Out data transfer in progress */
    PGRES_COPY_IN,              /* Copy In data transfer in progress */
    PGRES_BAD_RESPONSE,         /* an unexpected response was recv'd from the
                                 * backend */
    PGRES_NONFATAL_ERROR,       /* notice or warning message */
    PGRES_FATAL_ERROR           /* query failed */
} ExecStatusType;


extern void PQclear(PGresult *res);
extern void PQfinish(PGconn *conn);
extern PGconn *PQconnectdb(const char *conninfo);
extern ConnStatusType PQstatus(const PGconn *conn);
extern char *PQerrorMessage(const PGconn *conn);
extern PGconn *PQsetdbLogin(const char *pghost, const char *pgport, const char *pgoptions, const char *pgtty, const char *dbName, const char *login, const char *pwd);
extern void PQtrace(PGconn *conn, FILE *debug_port);
extern void PQuntrace(PGconn *conn);
extern PGresult *PQexec(PGconn *conn, const char *query);
extern ExecStatusType PQresultStatus(const PGresult *res);
extern char *PQresStatus(ExecStatusType status);
extern char *PQcmdStatus(PGresult *res);
extern int  PQntuples(const PGresult *res);
extern char *PQresultErrorMessage(const PGresult *res);
extern char *PQresultErrorField(const PGresult *res, int fieldcode);
extern char *PQcmdTuples(PGresult *res);
extern int  PQbinaryTuples(const PGresult *res);
extern int  PQnfields(const PGresult *res);
extern char *PQfname(const PGresult *res, int field_num);
extern Oid  PQftype(const PGresult *res, int field_num);
extern int  PQfsize(const PGresult *res, int field_num);
extern int  PQfmod(const PGresult *res, int field_num);
extern Oid  PQoidValue(const PGresult *res);
extern int  PQgetisnull(const PGresult *res, int tup_num, int field_num);
extern int  PQgetlength(const PGresult *res, int tup_num, int field_num);
extern char *PQgetvalue(const PGresult *res, int tup_num, int field_num);
extern unsigned char *PQescapeBytea(const unsigned char *from, size_t from_length, size_t *to_length);
extern unsigned char *PQunescapeBytea(const unsigned char *strtext,size_t *retbuflen);
extern size_t PQescapeString(char *to, const char *from, size_t length);
extern void PQfreemem(void *ptr);

