
#define SESSION             (TABLE:_session)

#ifdef ARROW
#define SESSION_SID                  session->sid                 
#define SESSION_SRVNAME              session->srvname             
#define SESSION_SECONDS              session->seconds             
#define SESSION_UID                  session->uid                 
#define SESSION_TID                  session->tid                 
#define SESSION_DATETIME             session->datetime            
#define SESSION_DBMDATA              session->dbmdata             
#else
#define SESSION_SID                  (FIELD:_session:1)
#define SESSION_SRVNAME              (FIELD:_session:2)
#define SESSION_SECONDS              (FIELD:_session:3)
#define SESSION_UID                  (FIELD:_session:4)
#define SESSION_TID                  (FIELD:_session:5)
#define SESSION_DATETIME             (FIELD:_session:6)
#define SESSION_DBMDATA              (FIELD:_session:7)
#endif

