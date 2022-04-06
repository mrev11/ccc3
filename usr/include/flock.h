
#include <fileio.ch>

#define CCCLK_NOWAIT    0   // default
#define CCCLK_WRITE     0   // default
#define CCCLK_WAIT      1
#define CCCLK_READ      2
#define CCCLK_TIMEOUT   4

extern int _ccc_lock(int fd, unsigned low, unsigned high, unsigned length, unsigned flags);
extern int _ccc_unlock(int fd, unsigned low, unsigned high, unsigned length);

