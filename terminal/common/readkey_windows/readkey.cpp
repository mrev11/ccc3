

#include <stdio.h>
#include <windows.h>

#include <utf8conv.h>
extern int keycode_win(int i,int j);

//#define DEBUG printf
#define DEBUG(...)


//----------------------------------------------------------------------------------------
int readkey()
{
    HANDLE hnd=GetStdHandle( STD_INPUT_HANDLE );
    if( hnd==NULL )
    {
        fprintf(stderr,"CONSOLE NOT FOUND\n");
        exit(1);
    }

    FlushConsoleInputBuffer(hnd);

    int inkeycode=0;
    unsigned utflen=0;
    char utfseq[32];

    while(1)
    {
        static int cnt=0;
        DWORD number_of_events;
        INPUT_RECORD inprec;
        KEY_EVENT_RECORD *keyrec;

        DEBUG("read %d",++cnt);fflush(0);
        int success=ReadConsoleInput(hnd, &inprec, 1, &number_of_events);
        DEBUG("!\n");fflush(0);

        if( success==0 )
        {
            printf( "ReadConsoleInput failed\n" );
        }
        else if( inprec.EventType==FOCUS_EVENT )
        {
            DEBUG( "FOCUS_EVENT\n" );
        }
        else if( inprec.EventType==MENU_EVENT )
        {
            DEBUG( "MENU_EVENT\n" );
        }
        else if( inprec.EventType==MOUSE_EVENT )
        {
            DEBUG( "MOUSE_EVENT\n" );
        }
        else if( inprec.EventType==WINDOW_BUFFER_SIZE_EVENT )
        {
            DEBUG( "WINDOW_BUFFER_SIZE_EVENT\n" );
        }
        else if( inprec.EventType==KEY_EVENT )
        {
            keyrec=(KEY_EVENT_RECORD*)&inprec.Event;

            DEBUG("key-%s vk=%d st=%x ch=%x\n",
                  keyrec->bKeyDown?"dn":"up", 
                  keyrec->wVirtualKeyCode,
                  keyrec->dwControlKeyState,
                  keyrec->uChar.UnicodeChar );

            if( !keyrec->bKeyDown )
            {
                continue; //keyup
            }
            else if( keyrec->wVirtualKeyCode==16 )
            {
                continue; //shift
            }
            else if( keyrec->wVirtualKeyCode==17 )
            {
                continue; //ctrl
            }
            else if( keyrec->wVirtualKeyCode==18 )
            {
                continue; //alt
            }

            int state=0;
            int state_sft =(keyrec->dwControlKeyState&16)!=0;
            int state_ctl =(keyrec->dwControlKeyState&4)!=0 || (keyrec->dwControlKeyState&8)!=0;
            int state_alt =(keyrec->dwControlKeyState&1)!=0 || (keyrec->dwControlKeyState&2)!=0;
            if( state_sft ) state|=1;
            if( state_ctl ) state|=2;
            if( state_alt ) state|=4;

            inkeycode=keycode_win(keyrec->wVirtualKeyCode,state);
            if( inkeycode )
            {
                break; //ok
            }

            WCHAR ch=keyrec->uChar.UnicodeChar; // byteonkent adja az UTF-8 sequence-et

            if( ch & 0xff00 ) // UTF-8 sequence
            {
                utfseq[utflen++]=ch&0xff;
                utfseq[utflen]=0;
                unsigned code=0;

                if( utflen==utf8_to_ucs(utfseq,(unsigned*)&code) )
                {
                    // ervenyes sequence (lehet)
                    if( code )
                    {
                        inkeycode=code;
                        break; //ok
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    // ervenytelen sequence (eldob)
                    utflen=0;
                }
            }
            else if( ch ) // ascii code
            {
                inkeycode=ch;
                if( state&4 && 'a'<=inkeycode && inkeycode<='z' )
                {
                    inkeycode=-(inkeycode-'a'+1); // ALT_A,...,ALT_Z
                }
                break; //ok
            }
            else
            {
                utflen=0;
            }
        }
    }
    FlushConsoleInputBuffer(hnd);
    return inkeycode;
}

//----------------------------------------------------------------------------------------
int xmain( )
{
    printf("set input codepage: %d\n", SetConsoleCP(65001)); // 65001 UTF-8
    printf("set output codepage: %d\n", SetConsoleOutputCP(65001)); // 65001 UTF-8

    printf("input codepage: %d\n", GetConsoleCP()); // 65001 UTF-8
    printf("output codepage: %d\n", GetConsoleOutputCP()); // 65001 UTF-8

    int key;
    while( (key=readkey())!=27 )
    {
        printf("INKEYCODE=%d ",key);

        if( key<32 )
        {
            printf(".\n");
        }
        else if( key<128 )
        {
            printf("%c\n",key);
        }
        else
        {
            char seq[32];
            seq[0]=0;
            ucs_to_utf8(key,seq);
            printf("%s\n",seq);
        }

        //tcpio_sendkey(key);
        DEBUG("--------------------------------\n");fflush(0);
    }

    return 0;
}

//----------------------------------------------------------------------------------------

#ifdef NOTDEF

BOOL WINAPI ReadConsoleInput(
  _In_  HANDLE        hConsoleInput,
  _Out_ PINPUT_RECORD lpBuffer,
  _In_  DWORD         nLength,
  _Out_ LPDWORD       lpNumberOfEventsRead
);


typedef struct _INPUT_RECORD {
  WORD  EventType;
  union {
    KEY_EVENT_RECORD          KeyEvent;
    MOUSE_EVENT_RECORD        MouseEvent;
    WINDOW_BUFFER_SIZE_RECORD WindowBufferSizeEvent;
    MENU_EVENT_RECORD         MenuEvent;
    FOCUS_EVENT_RECORD        FocusEvent;
  } Event;
} INPUT_RECORD;


typedef struct _KEY_EVENT_RECORD {
  BOOL  bKeyDown;
  WORD  wRepeatCount;
  WORD  wVirtualKeyCode;
  WORD  wVirtualScanCode;
  union {
    WCHAR UnicodeChar;
    CHAR  AsciiChar;
  } uChar;
  DWORD dwControlKeyState;
} KEY_EVENT_RECORD;


#endif

