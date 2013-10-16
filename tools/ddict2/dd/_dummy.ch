
#define DUMMY             (TABLE:_dummy)

#ifdef ARROW
#define DUMMY_FIELD       dummy->field       
#else
#define DUMMY_FIELD       (FIELD:_dummy:1)
#endif

