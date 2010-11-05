
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


#ifndef _CCCDEF_H_
#define _CCCDEF_H_

//----------------------------------------------------------------------------

#ifdef WINDOWS
#ifdef comment // hibát okoz, ha definiálva van (msxml.h)
  #error DEFINED_comment 
#endif
#include <windows.h>
#undef TRUE
#undef FALSE
#undef TEXT
#undef BYTE
#undef CHAR
#define wcscasecmp  wcsicmp
#define strcasecmp  stricmp
#endif

#define BYTE char
#define CHAR wchar_t

#ifdef UNIX
#include <unistd.h>
#endif

#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef MULTITHREAD

#ifdef UNIX
  #include <pthread.h>
#else
  #define pthread_t            DWORD
  #define pthread_key_t        DWORD
  #define pthread_getspecific  TlsGetValue
  #define pthread_setspecific  TlsSetValue
  #define pthread_self         GetCurrentThreadId
#endif  

  extern pthread_key_t thread_key;
  class thread_data;
  #define thread_data_ptr ((thread_data*)pthread_getspecific(thread_key))

#endif

#include <variable.h>

//----------------------------------------------------------------------------

extern int  ARGC;
extern char **ARGV;

extern int DOSCONV;
 
//----------------------------------------------------------------------------
unsigned const int TRACE_SIZE=256;

typedef struct 
{
    const char *func;
    VALUE *base;
    int line;
} TRACE;


#ifdef MULTITHREAD
  #define trace    (thread_data_ptr->_trace)
  #define tracebuf (thread_data_ptr->_tracebuf)
#else 
  extern TRACE *trace;
  extern TRACE tracebuf[];
#endif
 
//#define push_call(f,b)  (++trace,trace->func=f,trace->base=b,trace->line=0)
//extern void push_call(const char*, VALUE*);
#define pop_call()      (--trace)
#define line(l)         (trace->line=(l))

//----------------------------------------------------------------------------
unsigned const int STACK_SIZE=2048;
unsigned const int STSTACK_SIZE=1024;

#ifdef MULTITHREAD
  #define stack     (thread_data_ptr->_stack)
  #define stackbuf  (thread_data_ptr->_stackbuf)
#else 
  extern VALUE *stack;
  extern VALUE stackbuf[];
#endif
 
extern VALUE *ststack;
extern VALUE ststackbuf[];
 
#define PUSHNIL()  (stack->type=TYPE_NIL,stack++)
#define PUSHFLG()  (stack->type=TYPE_FLAG,stack++)
#define PUSHDAT()  (stack->type=TYPE_DATE,stack++)
#define PUSHPTR()  (stack->type=TYPE_POINTER,stack++)
#define PUSHNUM()  (stack->type=TYPE_NUMBER,stack++)
#define PUSH(v)    (*stack=*(v),stack++)

//Több szál esetén a pop()-> felhasználása tilos,
//ezért pop() visszatérése VALUE*-ról void-ra változott.
//Hogy a compiler kiszűrhesse a rossz POP()-> használatot,
//ideiglenesen POP-ot pop-ra preprocesszáljuk.

#define POP()      (pop())
//#define POP()      (--stack)
#define POP2()     (stack-=2)
#define POP3()     (stack-=3)

#define TOP0()     (stack)      // a stack tetején az első szabad hely
#define TOP()      (stack-1)    // a stack tetején lévő érték
#define TOP2()     (stack-2)    // a stack tetején a második érték
#define TOP3()     (stack-3)    // a stack tetején a harmadik érték
#define TOP4()     (stack-4)

#define DUP()      (PUSHNIL(),(*TOP()=*TOP2()))
#define DUP2()     (PUSHNIL(),(*TOP()=*TOP3()))
#define DUP3()     (PUSHNIL(),(*TOP()=*TOP4()))

#define RETURN(bs) {*bs=*TOP();stack=bs+1;return;}

#define STPUSH(v)  (*ststack=*(v),ststack++)

#define push_blkarg(v)      push_symbol(v)
#define push_blkarg_ref(v)  push_symbol_ref(v)
#define push_blkenv_ref(v)  push_symbol_ref(v)

//----------------------------------------------------------------------------
unsigned const int SEQJMP_SIZE=64;
unsigned const int USINGSTK_SIZE=512;

typedef struct
{
    VALUE       *jmp_stack;         // local stack állása
    TRACE       *jmp_trace;         // callstack (trace info) állása
    VALUE       *jmp_usingstk;      // using typeinfo stack állása;
    jmp_buf     jmpb;               // programregisztrek
} SEQJMP;
 
#ifdef MULTITHREAD
  #define seqjmp      (thread_data_ptr->_seqjmp)
  #define seqjmpbuf   (thread_data_ptr->_seqjmpbuf)
  #define usingstk    (thread_data_ptr->_usingstk)
  #define usingstkbuf (thread_data_ptr->_usingstkbuf)
  #define siglocklev  (thread_data_ptr->_siglocklev)
  #define signumpend  (thread_data_ptr->_signumpend)
  #define sigcccmask  (thread_data_ptr->_sigcccmask)
#else
  extern SEQJMP     seqjmpbuf[];
  extern SEQJMP     *seqjmp;
  extern VALUE      usingstkbuf[];
  extern VALUE      *usingstk;
  extern int        siglocklev;
  extern int        signumpend;
  extern int        sigcccmask;
#endif 

//----------------------------------------------------------------------------

class stvar
{
  public:
    VALUE *ptr;
    stvar();
    stvar(BYTE const *bin);
    stvar(BYTE const *bin, unsigned len);
    stvar(CHAR const *str);
    stvar(CHAR const *str, unsigned len);
    stvar(double number);
    stvar(void (*inicode)());
    stvar(VALUE *);
};

class stvarloc :public stvar
{
  public:
    stvarloc(void (*inicode)(VALUE*),VALUE*base);
};

//----------------------------------------------------------------------------

#undef TRUE
#undef FALSE

extern VALUE END;
extern VALUE NIL;
extern VALUE TRUE;
extern VALUE FALSE;
extern VALUE ZERO;
extern VALUE ONE;

extern VALUE PROTOTYPE_BINARY;
extern VALUE PROTOTYPE_STRING;
extern VALUE PROTOTYPE_DATE;
extern VALUE PROTOTYPE_ARRAY;
extern VALUE PROTOTYPE_BLOCK;
extern VALUE PROTOTYPE_OBJECT;

//----------------------------------------------------------------------------

#undef min
#undef max
#undef mod

#define min(x,y)   ((x)<(y)?(x):(y))
#define max(x,y)   ((x)>(y)?(x):(y))
#define mod(x,y)   ((x)-((x)/(y))*(y))

#define ROUND(x)   ((x)+((x)>0?0.5:-0.5))
#define D2INT(x)   ((int)ROUND(x))
#define D2UINT(x)  ((unsigned)ROUND(x))
#define D2LONG(x)  ((long)ROUND(x))
#define D2ULONG(x) ((unsigned long)ROUND(x))

//unsigned >  signed
//unsigned >= signed
#define GTUS(u,s)  ((s)<0 || (u) >  (unsigned)(s))
#define GEUS(u,s)  ((s)<0 || (u) >= (unsigned)(s))
#define minUS(u,s) ((s)<0 ? (s) : min(u,(unsigned)s))
#define maxUS(u,s) ((s)<0 ? (u) : max(u,(unsigned)s))

 
//----------------------------------------------------------------------------

#define TRANSFORM_B          0  // LeftNumber
#define TRANSFORM_Z          1  // ZeroBlank
#define TRANSFORM_U          2  // Uppercase (!)
#define TRANSFORM_A          3  // AlfaNumeric
#define TRANSFORM_K          4  // Clear
#define TRANSFORM_S          5  // Scroll
#define TRANSFORM_P          6  // PassWord (*)
#define TRANSFORM_FLAGS      7

//----------------------------------------------------------------------------
#ifndef CLASS_DBFIELD
class dbfield
{
    const char *alias;
    const char *field;
    int  ftabidx;
    int  ninsert;
    void fsearch(void);

  public:
    dbfield(char*a,char*f);
    dbfield(const char*a,const char*f);
    void fget(void);
    void fput(void);
};

#define CLASS_DBFIELD
#endif

//----------------------------------------------------------------------------

#ifdef WINDOWS

#define MEMALLOC(x)   GlobalAlloc(GMEM_FIXED,x)
#define MEMFREE(x)    GlobalFree(x)

#else

#define MEMALLOC(x)   malloc(x)
#define MEMFREE(x)    free(x)

#endif

//----------------------------------------------------------------------------
typedef short SHORT;
typedef long  LONG;
typedef unsigned short USHORT;
typedef unsigned long ULONG;
typedef USHORT FLAG;

//----------------------------------------------------------------------------
#if ! defined MULTITHREAD
#define MUTEX_CREATE(x)
#define MUTEX_DECLARE(x)
#define MUTEX_INIT(x)
#define MUTEX_LOCK(x)      0
#define MUTEX_UNLOCK(x)    0

#elif defined UNIX

#define MUTEX_CREATE(x)    static pthread_mutex_t x=PTHREAD_MUTEX_INITIALIZER
#define MUTEX_DESTROY(x)   pthread_mutex_destroy(&x)
#define MUTEX_DECLARE(x)   pthread_mutex_t x
#define MUTEX_INIT(x)      pthread_mutex_init(&x,0)

//#define MUTEX_DBG //setup-kor nem lehet bekapcsolva
#ifdef  MUTEX_DBG

//MUTEX_DBG: deadlockok felderítésére szolgál.
//Ha definiálva van, saját nyilvántartást vezet a lockolt mutexekről, 
//és deadlock esetén megpróbál úgy megállni, hogy a gdb backtrace 
//segítségével meg lehessen állapítani  a deadlock helyét és okát.
//
//Ahhoz hogy a backtrace informatív legyen:
//  -O6 helyett -ggdb opcióval kell fordítani,
//  telepíteni kell a libc debug változatát,
//  és annak helyét meg kell adni az LD_LIBRARY_PATH-ban.

extern int pthread_mutex_lock_wrapper(pthread_mutex_t *m);
extern int pthread_mutex_unlock_wrapper(pthread_mutex_t *m);
#define MUTEX_LOCK(x)      pthread_mutex_lock_wrapper(&x)
#define MUTEX_UNLOCK(x)    pthread_mutex_unlock_wrapper(&x)
#else //eredeti (debug nélküli) változat
#define MUTEX_LOCK(x)      pthread_mutex_lock(&x)
#define MUTEX_UNLOCK(x)    pthread_mutex_unlock(&x)
#endif

#else //WINDOWS
#define MUTEX_CREATE(x)    static HANDLE x=CreateMutex(0,0,0)
#define MUTEX_DESTROY(x)   CloseHandle(x)
#define MUTEX_DECLARE(x)   HANDLE x
#define MUTEX_INIT(x)      x=CreateMutex(0,0,0)
#define MUTEX_LOCK(x)      WaitForSingleObject(x,INFINITE)
#define MUTEX_UNLOCK(x)    ReleaseMutex(x)
#endif

#ifdef MULTITHREAD
#include <thread_data.h>
#endif

#define VARTAB_LOCK()     vartab_lock()  
#define VARTAB_UNLOCK()   vartab_unlock()  

#define SIGNAL_LOCK()     (++siglocklev)
#define SIGNAL_UNLOCK()   ((--siglocklev==0)&&(signumpend!=0)?signal_raise(signumpend):0)

#define CHRLIT(x)         L##x  // "literal" -> L"literal"

//----------------------------------------------------------------------------
#include <xmethod2.h>
#include <xmethod3.h>
#include <cccext1.h>
#include <cccext2.h>

//----------------------------------------------------------------------------
#endif // _CCCDEF_H_

