
#ifndef SMTP_H
#define SMTP_H

// address types
#define SMTP_ADDRESS_FROM           0
#define SMTP_ADDRESS_TO             1
#define SMTP_ADDRESS_CC             2
#define SMTP_ADDRESS_BCC            3

// connection mode
#define SMTP_SECURITY_STARTTLS      0
#define SMTP_SECURITY_TLS           1
#define SMTP_SECURITY_NONE          2

// authentication
#define SMTP_AUTH_CRAM_MD5          0
#define SMTP_AUTH_NONE              1
#define SMTP_AUTH_PLAIN             2
#define SMTP_AUTH_LOGIN             3


// result codes
#define SMTP_INTERNAL_ERROR         -1
#define SMTP_READY                  220
#define SMTP_CLOSE                  221
#define SMTP_AUTH_SUCCESS           235
#define SMTP_DONE                   250
#define SMTP_AUTH_CONTINUE          334
#define SMTP_BEGIN_MAIL             354

#endif SMTP_H
