//input: ppo/opt_ppo.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_opt_ppo(int argno);

//=======================================================================
void _clp_opt_ppo(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("opt_ppo",base);
//
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

