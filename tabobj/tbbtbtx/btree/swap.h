
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

// Little endian <==> big endian 32-bit swap macros.
//   M_32_SWAP    swap a memory location
//   P_32_SWAP    swap a referenced memory location
//   P_32_COPY    swap from one location to another

#define    M_32_SWAP(a) {                      \
    u_int32_t _tmp = (a);                      \
    ((char *)&(a))[0] = ((char *)&_tmp)[3];    \
    ((char *)&(a))[1] = ((char *)&_tmp)[2];    \
    ((char *)&(a))[2] = ((char *)&_tmp)[1];    \
    ((char *)&(a))[3] = ((char *)&_tmp)[0];    \
}
#define    P_32_SWAP(a) {                      \
    u_int32_t _tmp = *(u_int32_t *)(a);        \
    ((char *)(a))[0] = ((char *)&_tmp)[3];     \
    ((char *)(a))[1] = ((char *)&_tmp)[2];     \
    ((char *)(a))[2] = ((char *)&_tmp)[1];     \
    ((char *)(a))[3] = ((char *)&_tmp)[0];     \
}
#define    P_32_COPY(a, b) {                   \
    ((char *)&(b))[0] = ((char *)&(a))[3];     \
    ((char *)&(b))[1] = ((char *)&(a))[2];     \
    ((char *)&(b))[2] = ((char *)&(a))[1];     \
    ((char *)&(b))[3] = ((char *)&(a))[0];     \
}


// Little endian <==> big endian 16-bit swap macros.
//   M_16_SWAP    swap a memory location
//   P_16_SWAP    swap a referenced memory location
//   P_16_COPY    swap from one location to another

#define M_16_SWAP(a) {                         \
    u_int16_t _tmp = (a);                      \
    ((char *)&(a))[0] = ((char *)&_tmp)[1];    \
    ((char *)&(a))[1] = ((char *)&_tmp)[0];    \
}

#define P_16_SWAP(a) {                         \
    u_int16_t _tmp = *(u_int16_t *)(a);        \
    ((char *)(a))[0] = ((char *)&_tmp)[1];     \
    ((char *)(a))[1] = ((char *)&_tmp)[0];     \
}

#define P_16_COPY(a, b) {                      \
    ((char *)&(b))[0] = ((char *)&(a))[1];     \
    ((char *)&(b))[1] = ((char *)&(a))[0];     \
}

