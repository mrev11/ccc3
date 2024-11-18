
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
#include <windows.h>

extern "C" __declspec(dllexport)
void btpasswd(unsigned int salt, unsigned int pgno, unsigned char *key, unsigned char *iv)
{
    key[ 0] =  64;
    key[ 1] =   2;
    key[ 2] = 113;
    key[ 3] =  31;
    key[ 4] =  12;
    key[ 5] =  20;
    key[ 6] = 111;
    key[ 7] =  32;
    key[ 8] =  25;
    key[ 9] = 231;
    key[10] =  75;
    key[11] =  80;
    key[12] =   0;
    key[13] =  12;
    key[14] =  99;
    key[15] =   5;
    key[16] =  91;
    key[17] = 100;
    key[18] =  85;
    key[19] =  49;
    key[20] =  37;
    key[21] =  82;
    key[22] =  54;
    key[23] = 192;
    key[24] = 230;
    key[25] = 101;
    key[26] = 245;
    key[27] = 212;
    key[28] =  64;
    key[29] =  65;
    key[30] = 200;
    key[31] = 122;
    key[32] =   0;

    sprintf((char*)iv,"%08x%08x",salt,pgno);
}

extern "C" __declspec(dllexport)
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) 
{
    switch (ul_reason_for_call) 
    {
        case DLL_PROCESS_ATTACH: 
            //printf("btpasswd library loaded\n");
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;

        case DLL_PROCESS_DETACH:
            break;
    }
  return TRUE;
}

