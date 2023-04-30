

extern void screensize(int*,int*);
extern void curs_set(int);
extern void attron(int fg, int bg);
extern void attroff(int);
extern void move(int,int);
extern void addnstr(const char*,unsigned);
extern void addch(char);
extern void refresh();

