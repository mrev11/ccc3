
#include <cccapi.h>

namespace _nsp_pageman {

//----------------------------------------------------------------------------
void _clp_hex2num(int argno)  // hexa (binary)stringből szám
{
    CCC_PROLOG("hex2num",1);
    char *p=_parb(1);
    unsigned long x;
    sscanf(p,"%lx",&x);
    _retnl(x);
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp_num2hex(int argno)  // számból hexa (binary)string 
{
    CCC_PROLOG("num2hex",2);
    unsigned long x=_parnu(1);
    int w=_parnu(2);
    char buf[32];
    sprintf(buf,"%0*lx",w,x);
    _retblen(buf,w);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_hexinc(int argno)  // hexa (binary)stringben megadott számot növel
{
    CCC_PROLOG("hexinc",1);
    char *p=_parb(1);
    int w=_parblen(1);
    char buf[32];
    unsigned long x;
    sscanf(p,"%lx",&x);
    sprintf(buf,"%0*lx",w,x+1);
    _retblen(buf,w);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------


} //namespace
