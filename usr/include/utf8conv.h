

extern unsigned utf8_to_ucs(const char *utf8, unsigned *ucs);
extern unsigned ucs_to_utf8(unsigned ucs, char*utf8);
extern char *wchar_to_utf8(wchar_t const *wstr, unsigned wlen, unsigned *reslen);
extern wchar_t *utf8_to_wchar(char const *utf8, unsigned blen, unsigned *reslen);

