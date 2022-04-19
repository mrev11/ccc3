
#define RPCUSER             (TABLE:_rpcuser)

#ifdef ARROW
#define RPCUSER_UID                  rpcuser->uid                 
#define RPCUSER_TID                  rpcuser->tid                 
#define RPCUSER_GID                  rpcuser->gid                 
#define RPCUSER_NAME                 rpcuser->name                
#define RPCUSER_PASSWORD             rpcuser->password            
#define RPCUSER_STARTDATE            rpcuser->startdate           
#define RPCUSER_ENDDATE              rpcuser->enddate             
#else
#define RPCUSER_UID                  (FIELD:_rpcuser:1)
#define RPCUSER_TID                  (FIELD:_rpcuser:2)
#define RPCUSER_GID                  (FIELD:_rpcuser:3)
#define RPCUSER_NAME                 (FIELD:_rpcuser:4)
#define RPCUSER_PASSWORD             (FIELD:_rpcuser:5)
#define RPCUSER_STARTDATE            (FIELD:_rpcuser:6)
#define RPCUSER_ENDDATE              (FIELD:_rpcuser:7)
#endif

