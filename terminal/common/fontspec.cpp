

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// az envname valtozobol kiolvassa
// a hasznalando font nevet -> fontface
// a hasznalando font meretet -> fontsize
// ha az envname nincs definialva, CCCTERM_FONTSPEC-et veszi
//
// ha CCCTERM_FONTSPEC sincs definialva : Monospace 12
// ha csak a font neve van megadva      : <name> 12
// ha csak a font merete van megadva    : Monospace <size>
//
// peldak:
//  CCCTERM_QTFONT="Monospace 12"
//  CCCTERM_QTFONT="Monospace-12"
//  CCCTERM_QTFONT="Monospace12"
//  CCCTERM_QTFONT="Monospace"
//  CCCTERM_QTFONT="12"
//  CCCTERM_QTFONT="Courier New 12"
//  CCCTERM_QTFONT="Courier New"


//------------------------------------------------------------------------------------------
void fontspec(const char *envname, char **fontface, int *fontsize)
{
    char *env=0;
    static char *name=strdup("Monospace");
    static int size=12;

    if( envname && getenv(envname) )
    {
        env=strdup(getenv(envname));
    }
    else if( getenv("CCCTERM_FONTSPEC") )
    {
        env=strdup(getenv("CCCTERM_FONTSPEC"));
    }
    else
    {
        *fontface=name;
        *fontsize=size;
        return;
    }
    
    int i, len=strlen(env);
    
    for(i=len-1; 0<=i; i--)
    {
        if( !isdigit( env[i]) )
        {
            break;
        }
    }
    if( env[i+1] )
    {
        sscanf(env+i+1,"%d",&size);
    }

    for( ; 0<=i; i--)
    {
        if( isalpha(env[i]) )
        {
            break;
        }
    }
    if( 0<=i && i<len )
    {
        env[i+1]=0;
        name=env;
    }

    *fontface=name;
    *fontsize=size;
}

//------------------------------------------------------------------------------------------

