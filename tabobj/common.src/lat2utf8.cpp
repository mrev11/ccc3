
#include <cccapi.h>


//----------------------------------------------------------------------------
void _clp_lat2utf8(int argno)
{

    CCC_PROLOG("lat2utf8",1);
    char *p=_parb(1);
    int len=_parblen(1);
    
    char *u=binaryl(len+len);
    int ulen=0;
    
    for( int i=0; i<len; i++) 
    {
        int c=*(p+i);

        switch (c)
        {               
            case 0xa0 : u[ulen++]=0xc3; u[ulen++]=0xa1; break;  /*a*/
            case 0x82 : u[ulen++]=0xc3; u[ulen++]=0xa9; break;  /*e*/
            case 0xa1 : u[ulen++]=0xc3; u[ulen++]=0xad; break;  /*i*/
            case 0xa2 : u[ulen++]=0xc3; u[ulen++]=0xb3; break;  /*o*/
            case 0x94 : u[ulen++]=0xc3; u[ulen++]=0xb6; break;  /*o*/
            case 0x93 : u[ulen++]=0xc5; u[ulen++]=0x91; break;  /*o*/
            case 0xa3 : u[ulen++]=0xc3; u[ulen++]=0xba; break;  /*u*/
            case 0x81 : u[ulen++]=0xc3; u[ulen++]=0xbc; break;  /*u*/
            case 0x96 : u[ulen++]=0xc5; u[ulen++]=0xb1; break;  /*u*/

            case 0x8f : u[ulen++]=0xc3; u[ulen++]=0x81; break;  /*A*/
            case 0x90 : u[ulen++]=0xc3; u[ulen++]=0x89; break;  /*E*/
            case 0x8c : u[ulen++]=0xc3; u[ulen++]=0x8d; break;  /*I*/
            case 0x8d : u[ulen++]=0xc3; u[ulen++]=0x8d; break;  /*I*/
            case 0x95 : u[ulen++]=0xc3; u[ulen++]=0x93; break;  /*O*/
            case 0x99 : u[ulen++]=0xc3; u[ulen++]=0x96; break;  /*O*/
            case 0xa7 : u[ulen++]=0xc5; u[ulen++]=0x90; break;  /*O*/
            case 0x97 : u[ulen++]=0xc3; u[ulen++]=0x9a; break;  /*U*/
            case 0x9a : u[ulen++]=0xc3; u[ulen++]=0x9c; break;  /*U*/
            case 0x98 : u[ulen++]=0xc5; u[ulen++]=0xb0; break;  /*U*/

            case 0xe1 : u[ulen++]=0xc3; u[ulen++]=0xa1; break;  /*a*/
            case 0xe9 : u[ulen++]=0xc3; u[ulen++]=0xa9; break;  /*e*/
            case 0xed : u[ulen++]=0xc3; u[ulen++]=0xad; break;  /*i*/
            case 0xf3 : u[ulen++]=0xc3; u[ulen++]=0xb3; break;  /*o*/
            case 0xf6 : u[ulen++]=0xc3; u[ulen++]=0xb6; break;  /*o*/
            case 0xf4 : u[ulen++]=0xc5; u[ulen++]=0x91; break;  /*o*/
            case 0xf5 : u[ulen++]=0xc5; u[ulen++]=0x91; break;  /*o*/
            case 0xfa : u[ulen++]=0xc3; u[ulen++]=0xba; break;  /*u*/
            case 0xfc : u[ulen++]=0xc3; u[ulen++]=0xbc; break;  /*u*/
            case 0xfb : u[ulen++]=0xc5; u[ulen++]=0xb1; break;  /*u*/

            case 0xc1 : u[ulen++]=0xc3; u[ulen++]=0x81; break;  /*A*/
            case 0xc9 : u[ulen++]=0xc3; u[ulen++]=0x89; break;  /*E*/
            case 0xcd : u[ulen++]=0xc3; u[ulen++]=0x8d; break;  /*I*/
            case 0xd3 : u[ulen++]=0xc3; u[ulen++]=0x93; break;  /*O*/
            case 0xd6 : u[ulen++]=0xc3; u[ulen++]=0x96; break;  /*O*/
            case 0xd4 : u[ulen++]=0xc5; u[ulen++]=0x90; break;  /*O*/
            case 0xd5 : u[ulen++]=0xc5; u[ulen++]=0x90; break;  /*O*/
            case 0xda : u[ulen++]=0xc3; u[ulen++]=0x9a; break;  /*U*/
            case 0xdc : u[ulen++]=0xc3; u[ulen++]=0x9c; break;  /*U*/
            case 0xdb : u[ulen++]=0xc5; u[ulen++]=0xb0; break;  /*U*/

            default: u[ulen++]=c;
        }
    }


    //p[len]=0;    
    //u[ulen]=0;    
    //printf("[%s]->[%s]\n",p,u);

    _retblen(u,ulen);

    CCC_EPILOG();
}

//----------------------------------------------------------------------------













