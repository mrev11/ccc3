

namespace proba.szerencse

static vanaki:=a"vanaki forron szereti"
static pi:=valueofpi()


********************************************************************************************
// A static valtozok es a function/class-ok kozott lehet egy (0 vagy 1 darab) 
// #clang section, itt lehet elhelyezni az #include-okat es a C fuggvenyeket.
// A #clang section belsejeben global (ures) namespace van.

#clang //global namespace!

#include <cccapi.h>

static int print(const char *txt)
{
    return printf("%s\n",txt);
}
#cend


********************************************************************************************
function valueofpi()
local blk:={||3.141592} //legyen benne block is
    return eval(blk)


********************************************************************************************
function proba(txt)
static forron:=a"VANAKI FORRON SZERETI"
local x:=a"!"

    vanaki+x
    forron+x
    txt+x

    ?? "Hopp-1"+": "

    // A fuggvenyek belsejeben, az utasitasok helyen
    // lehetnek #clang section-ok (tobb is), ezek kotelezoen
    // valtozatlan allapotban hagyjak maguk utan a stacket.

    #clang
        push_symbol(_st_vanaki_ptr());  //vanaki (global static (zarojel))
        push_symbol(LOCAL_x);//x
        add();
        print( BINARYPTR(TOP()) );
        pop();
    #cend

    ?? "Hopp-2"+": "

    #clang
        push_symbol(_st_forron.ptr);    //forron (local static (nincs zarojel))
        push_symbol(LOCAL_x);//x
        add();
        print( BINARYPTR(TOP()) );
        pop();
    #cend

    ?? "Hopp-3"+": "

    #clang
        push_symbol(LOCAL_txt);         //txt (local auto)
        push_symbol(LOCAL_x);//x
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

    ?? "Ok ", pi



********************************************************************************************


    