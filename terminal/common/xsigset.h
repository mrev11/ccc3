
typedef void (*sighandler_t)(int); //BSD-kbol hianyzik

extern void xsigset(int signum, sighandler_t sighnd);
extern void xsigset_handlers();


