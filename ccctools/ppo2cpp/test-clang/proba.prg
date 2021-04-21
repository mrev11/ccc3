

namespace proba

static vanaki:=a"vanaki forrón szereti"


********************************************************************************************
// A static valtozok es a function/class-ok kozott lehet egy (0 vagy 1 darab) 
// #clang section, itt lehet elhelyezni az #include-okat es a C fuggvenyeket.

#clang
#include <cccapi.h>

static int print(const char *txt)
{
    return printf("%s\n",txt);
}
#cend

********************************************************************************************
function proba(txt)
local x:=a"!"

    vanaki+x
    txt+x

    ?? "Hopp-1"+":"

    // A fuggvenyek belsejeben, az utasitasok helyen
    // lehetnek #clang section-ok (tobb is), ezek kotelezoen
    // valtozatlan allapotban hagyjak maguk utan a stacket.

    #clang
        push_symbol(_st_vanaki_ptr());//vanaki
        push_symbol(base+1);//x
        add();
        print( BINARYPTR(TOP()) );
        pop();
    #cend

    ?? "Hopp-2"+":"

    #clang
        push_symbol(base+0);//txt
        push_symbol(base+1);//x
        add();
        print( BINARYPTR(TOP()) );
        pop();
    #cend


    #clang
        for(int i=0; i<10; i++)
        {
            printf("%d ",i);
        }
        printf("\n");
    #cend

    ?? "Ok"


********************************************************************************************



    