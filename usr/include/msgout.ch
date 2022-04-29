
#ifdef MSGOUT

#include "fileio.ch"

#command ?@  [ <list,...> ]      => msgout( <list> )
#command ??@ [ <list,...> ]      => mmsgout( <list> )

static function msgout_fd()
static fd:=fopen(getenv("MSGOUT"),FO_CREATE+FO_READWRITE+FO_APPEND)
    if( fd==NIL )
        break("MSGOUT variable not set")
    end
    return fd

static function msgout(*)
local args:={*},n
local fd:=msgout_fd()
    for n:=1 to len(args)
        fwrite(fd,if(n==1,chr(10)," ")+args[n]::any2str)
    next


static function mmsgout(*)
local args:={*},n
local fd:=msgout_fd()
    for n:=1 to len(args)
        fwrite(fd,if(n==1,""," ")+args[n]::any2str)
    next

#else

#command ?@  [ <list,...> ]      =>
#command ??@ [ <list,...> ]      =>

#endif
