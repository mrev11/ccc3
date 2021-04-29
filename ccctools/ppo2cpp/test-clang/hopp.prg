
//cpp helyett lehet prg-t irni
//ha a teljes tartalmat #clang-ba tesszuk
//plusz irunk bele egy dummy fuggvenyt


#clang



#include <cccapi.h>

namespace _nsp_proba{
namespace _nsp_szerencse{
extern void _clp_valueofpi(int argno);
}}//namespace proba.szerencse

void _clp_hopp(int argno)
{
    stack-=argno;
    printf("\nHOPP");
    //number(3.141592);
    _nsp_proba::_nsp_szerencse::_clp_valueofpi(0);
}



#cend

static function dummy()
//kell legyen benne egy fuggveny
//(static -> senkit sem zavar)

