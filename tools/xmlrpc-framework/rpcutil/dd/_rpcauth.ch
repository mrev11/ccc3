
#define RPCAUTH             (TABLE:_rpcauth)

#ifdef ARROW
#define RPCAUTH_TID                  rpcauth->tid                 
#define RPCAUTH_METHOD               rpcauth->method              
#define RPCAUTH_PERMISSION           rpcauth->permission          
#else
#define RPCAUTH_TID                  (FIELD:_rpcauth:1)
#define RPCAUTH_METHOD               (FIELD:_rpcauth:2)
#define RPCAUTH_PERMISSION           (FIELD:_rpcauth:3)
#endif

