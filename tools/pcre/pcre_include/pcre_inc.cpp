
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include <pcre.h>

int main(int argc, char* argv[])
{
    printf("\n//pcre.compile options\n");

    printf("#define PCRE_ANCHORED             0x%08x\n",PCRE_ANCHORED           );
    printf("#define PCRE_AUTO_CALLOUT         0x%08x\n",PCRE_AUTO_CALLOUT       );
    printf("#define PCRE_BSR_ANYCRLF          0x%08x\n",PCRE_BSR_ANYCRLF        );
    printf("#define PCRE_BSR_UNICODE          0x%08x\n",PCRE_BSR_UNICODE        );
    printf("#define PCRE_CASELESS             0x%08x\n",PCRE_CASELESS           );
    printf("#define PCRE_DOLLAR_ENDONLY       0x%08x\n",PCRE_DOLLAR_ENDONLY     );
    printf("#define PCRE_DOTALL               0x%08x\n",PCRE_DOTALL             );
    printf("#define PCRE_DUPNAMES             0x%08x\n",PCRE_DUPNAMES           );
    printf("#define PCRE_EXTENDED             0x%08x\n",PCRE_EXTENDED           );
    printf("#define PCRE_EXTRA                0x%08x\n",PCRE_EXTRA              );
    printf("#define PCRE_FIRSTLINE            0x%08x\n",PCRE_FIRSTLINE          );
    printf("#define PCRE_JAVASCRIPT_COMPAT    0x%08x\n",PCRE_JAVASCRIPT_COMPAT  );
    printf("#define PCRE_MULTILINE            0x%08x\n",PCRE_MULTILINE          );
    printf("#define PCRE_NEVER_UTF            0x%08x\n",PCRE_NEVER_UTF          );
    printf("#define PCRE_NEWLINE_ANY          0x%08x\n",PCRE_NEWLINE_ANY        );
    printf("#define PCRE_NEWLINE_ANYCRLF      0x%08x\n",PCRE_NEWLINE_ANYCRLF    );
    printf("#define PCRE_NEWLINE_CR           0x%08x\n",PCRE_NEWLINE_CR         );
    printf("#define PCRE_NEWLINE_CRLF         0x%08x\n",PCRE_NEWLINE_CRLF       );
    printf("#define PCRE_NEWLINE_LF           0x%08x\n",PCRE_NEWLINE_LF         );
    printf("#define PCRE_NO_AUTO_CAPTURE      0x%08x\n",PCRE_NO_AUTO_CAPTURE    );
    printf("#define PCRE_NO_AUTO_POSSESS      0x%08x\n",PCRE_NO_AUTO_POSSESS    );
    printf("#define PCRE_NO_START_OPTIMIZE    0x%08x\n",PCRE_NO_START_OPTIMIZE  );
    printf("#define PCRE_NO_UTF16_CHECK       0x%08x\n",PCRE_NO_UTF16_CHECK     );
    printf("#define PCRE_NO_UTF32_CHECK       0x%08x\n",PCRE_NO_UTF32_CHECK     );
    printf("#define PCRE_NO_UTF8_CHECK        0x%08x\n",PCRE_NO_UTF8_CHECK      );
    printf("#define PCRE_UCP                  0x%08x\n",PCRE_UCP                );
    printf("#define PCRE_UNGREEDY             0x%08x\n",PCRE_UNGREEDY           );
    printf("#define PCRE_UTF16                0x%08x\n",PCRE_UTF16              );
    printf("#define PCRE_UTF32                0x%08x\n",PCRE_UTF32              );
    printf("#define PCRE_UTF8                 0x%08x\n",PCRE_UTF8               );

 
    printf("\n//pcre.exec options\n");

    printf("#define PCRE_ANCHORED             0x%08x\n",PCRE_ANCHORED           );
    printf("#define PCRE_BSR_ANYCRLF          0x%08x\n",PCRE_BSR_ANYCRLF        );
    printf("#define PCRE_BSR_UNICODE          0x%08x\n",PCRE_BSR_UNICODE        );
    printf("#define PCRE_NEWLINE_ANY          0x%08x\n",PCRE_NEWLINE_ANY        );
    printf("#define PCRE_NEWLINE_ANYCRLF      0x%08x\n",PCRE_NEWLINE_ANYCRLF    );
    printf("#define PCRE_NEWLINE_CR           0x%08x\n",PCRE_NEWLINE_CR         );
    printf("#define PCRE_NEWLINE_CRLF         0x%08x\n",PCRE_NEWLINE_CRLF       );
    printf("#define PCRE_NEWLINE_LF           0x%08x\n",PCRE_NEWLINE_LF         );
    printf("#define PCRE_NOTBOL               0x%08x\n",PCRE_NOTBOL             );
    printf("#define PCRE_NOTEOL               0x%08x\n",PCRE_NOTEOL             );
    printf("#define PCRE_NOTEMPTY             0x%08x\n",PCRE_NOTEMPTY           );
    printf("#define PCRE_NOTEMPTY_ATSTART     0x%08x\n",PCRE_NOTEMPTY_ATSTART   );
    printf("#define PCRE_NO_START_OPTIMIZE    0x%08x\n",PCRE_NO_START_OPTIMIZE  );
    printf("#define PCRE_NO_UTF16_CHECK       0x%08x\n",PCRE_NO_UTF16_CHECK     );
    printf("#define PCRE_NO_UTF32_CHECK       0x%08x\n",PCRE_NO_UTF32_CHECK     );
    printf("#define PCRE_NO_UTF8_CHECK        0x%08x\n",PCRE_NO_UTF8_CHECK      );
    printf("#define PCRE_PARTIAL_HARD         0x%08x\n",PCRE_PARTIAL_HARD       );
    printf("#define PCRE_PARTIAL_SOFT         0x%08x\n",PCRE_PARTIAL_SOFT       );


    printf("\n//pcre error codes\n");


    printf("#define  PCRE_ERROR_NOMATCH        (%d)\n",PCRE_ERROR_NOMATCH       );
    printf("#define  PCRE_ERROR_NULL           (%d)\n",PCRE_ERROR_NULL          );
    printf("#define  PCRE_ERROR_BADOPTION      (%d)\n",PCRE_ERROR_BADOPTION     );
    printf("#define  PCRE_ERROR_BADMAGIC       (%d)\n",PCRE_ERROR_BADMAGIC      );
    printf("#define  PCRE_ERROR_UNKNOWN_OPCODE (%d)\n",PCRE_ERROR_UNKNOWN_OPCODE);
    printf("#define  PCRE_ERROR_NOMEMORY       (%d)\n",PCRE_ERROR_NOMEMORY      );
    printf("#define  PCRE_ERROR_NOSUBSTRING    (%d)\n",PCRE_ERROR_NOSUBSTRING   );
    printf("#define  PCRE_ERROR_MATCHLIMIT     (%d)\n",PCRE_ERROR_MATCHLIMIT    );
    printf("#define  PCRE_ERROR_CALLOUT        (%d)\n",PCRE_ERROR_CALLOUT       );
    printf("#define  PCRE_ERROR_BADUTF8        (%d)\n",PCRE_ERROR_BADUTF8       );
    printf("#define  PCRE_ERROR_BADUTF8_OFFSET (%d)\n",PCRE_ERROR_BADUTF8_OFFSET);
    printf("#define  PCRE_ERROR_PARTIAL        (%d)\n",PCRE_ERROR_PARTIAL       );
    printf("#define  PCRE_ERROR_BADPARTIAL     (%d)\n",PCRE_ERROR_BADPARTIAL    );
    printf("#define  PCRE_ERROR_INTERNAL       (%d)\n",PCRE_ERROR_INTERNAL      );
    printf("#define  PCRE_ERROR_BADCOUNT       (%d)\n",PCRE_ERROR_BADCOUNT      );
    printf("#define  PCRE_ERROR_DFA_UITEM      (%d)\n",PCRE_ERROR_DFA_UITEM     );
    printf("#define  PCRE_ERROR_DFA_UCOND      (%d)\n",PCRE_ERROR_DFA_UCOND     );
    printf("#define  PCRE_ERROR_DFA_UMLIMIT    (%d)\n",PCRE_ERROR_DFA_UMLIMIT   );
    printf("#define  PCRE_ERROR_DFA_WSSIZE     (%d)\n",PCRE_ERROR_DFA_WSSIZE    );
    printf("#define  PCRE_ERROR_DFA_RECURSE    (%d)\n",PCRE_ERROR_DFA_RECURSE   );
    printf("#define  PCRE_ERROR_RECURSIONLIMIT (%d)\n",PCRE_ERROR_RECURSIONLIMIT);
    printf("#define  PCRE_ERROR_BADNEWLINE     (%d)\n",PCRE_ERROR_BADNEWLINE    );
    printf("#define  PCRE_ERROR_BADOFFSET      (%d)\n",PCRE_ERROR_BADOFFSET     );
    printf("#define  PCRE_ERROR_SHORTUTF8      (%d)\n",PCRE_ERROR_SHORTUTF8     );
    printf("#define  PCRE_ERROR_RECURSELOOP    (%d)\n",PCRE_ERROR_RECURSELOOP   );
    printf("#define  PCRE_ERROR_JIT_STACKLIMIT (%d)\n",PCRE_ERROR_JIT_STACKLIMIT);
    printf("#define  PCRE_ERROR_BADMODE        (%d)\n",PCRE_ERROR_BADMODE       );
    printf("#define  PCRE_ERROR_BADENDIANNESS  (%d)\n",PCRE_ERROR_BADENDIANNESS );
    printf("#define  PCRE_ERROR_DFA_BADRESTART (%d)\n",PCRE_ERROR_DFA_BADRESTART);
    printf("#define  PCRE_ERROR_BADLENGTH      (%d)\n",PCRE_ERROR_BADLENGTH     );



    printf("\n");

}
