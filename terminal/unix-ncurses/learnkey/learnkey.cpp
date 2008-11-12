
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
#include <unistd.h>
#include <inkey.ch>

#define  LEARNKEY
#include "../readkey.cpp"

struct KEYMAP
{
  char const *name;
  int code;
} keymap[]={ 
{"K_UP          ",K_UP          },
{"K_DOWN        ",K_DOWN        },
{"K_LEFT        ",K_LEFT        },
{"K_RIGHT       ",K_RIGHT       },
{"K_HOME        ",K_HOME        },
{"K_END         ",K_END         },
{"K_PGUP        ",K_PGUP        },
{"K_PGDN        ",K_PGDN        },
{"K_CTRL_UP     ",K_CTRL_UP     },
{"K_CTRL_DOWN   ",K_CTRL_DOWN   },
{"K_CTRL_LEFT   ",K_CTRL_LEFT   },
{"K_CTRL_RIGHT  ",K_CTRL_RIGHT  },
{"K_CTRL_HOME   ",K_CTRL_HOME   },
{"K_CTRL_END    ",K_CTRL_END    },
{"K_CTRL_PGUP   ",K_CTRL_PGUP   },
{"K_CTRL_PGDN   ",K_CTRL_PGDN   },
{"K_ALT_UP      ",K_ALT_UP      },
{"K_ALT_DOWN    ",K_ALT_DOWN    },
{"K_ALT_LEFT    ",K_ALT_LEFT    },
{"K_ALT_RIGHT   ",K_ALT_RIGHT   },
{"K_ALT_HOME    ",K_ALT_HOME    },
{"K_ALT_END     ",K_ALT_END     },
{"K_ALT_PGUP    ",K_ALT_PGUP    },
{"K_ALT_PGDN    ",K_ALT_PGDN    },
{"K_ESC         ",K_ESC         },
{"K_INS         ",K_INS         },
{"K_DEL         ",K_DEL         },
{"K_ALT_A       ",K_ALT_A       },
{"K_ALT_B       ",K_ALT_B       },
{"K_ALT_C       ",K_ALT_C       },
{"K_ALT_D       ",K_ALT_D       },
{"K_ALT_E       ",K_ALT_E       },
{"K_ALT_F       ",K_ALT_F       },
{"K_ALT_G       ",K_ALT_G       },
{"K_ALT_H       ",K_ALT_H       },
{"K_ALT_I       ",K_ALT_I       },
{"K_ALT_J       ",K_ALT_J       },
{"K_ALT_K       ",K_ALT_K       },
{"K_ALT_L       ",K_ALT_L       },
{"K_ALT_M       ",K_ALT_M       },
{"K_ALT_N       ",K_ALT_N       },
{"K_ALT_O       ",K_ALT_O       },
{"K_ALT_P       ",K_ALT_P       },
{"K_ALT_Q       ",K_ALT_Q       },
{"K_ALT_R       ",K_ALT_R       },
{"K_ALT_S       ",K_ALT_S       },
{"K_ALT_T       ",K_ALT_T       },
{"K_ALT_U       ",K_ALT_U       },
{"K_ALT_V       ",K_ALT_V       },
{"K_ALT_W       ",K_ALT_W       },
{"K_ALT_X       ",K_ALT_X       },
{"K_ALT_Y       ",K_ALT_Y       },
{"K_ALT_Z       ",K_ALT_Z       },
{"K_F1          ",K_F1          },
{"K_F2          ",K_F2          },
{"K_F3          ",K_F3          },
{"K_F4          ",K_F4          },
{"K_F5          ",K_F5          },
{"K_F6          ",K_F6          },
{"K_F7          ",K_F7          },
{"K_F8          ",K_F8          },
{"K_F9          ",K_F9          },
{"K_F10         ",K_F10         },
{"K_F11         ",K_F11         },
{"K_F12         ",K_F12         },
{"K_SH_F1       ",K_SH_F1       },
{"K_SH_F2       ",K_SH_F2       },
{"K_SH_F3       ",K_SH_F3       },
{"K_SH_F4       ",K_SH_F4       },
{"K_SH_F5       ",K_SH_F5       },
{"K_SH_F6       ",K_SH_F6       },
{"K_SH_F7       ",K_SH_F7       },
{"K_SH_F8       ",K_SH_F8       },
{"K_SH_F9       ",K_SH_F9       },
{"K_SH_F10      ",K_SH_F10      },
{"K_SH_F11      ",K_SH_F11      },
{"K_SH_F12      ",K_SH_F12      },
{"K_CTRL_F1     ",K_CTRL_F1     },
{"K_CTRL_F2     ",K_CTRL_F2     },
{"K_CTRL_F3     ",K_CTRL_F3     },
{"K_CTRL_F4     ",K_CTRL_F4     },
{"K_CTRL_F5     ",K_CTRL_F5     },
{"K_CTRL_F6     ",K_CTRL_F6     },
{"K_CTRL_F7     ",K_CTRL_F7     },
{"K_CTRL_F8     ",K_CTRL_F8     },
{"K_CTRL_F9     ",K_CTRL_F9     },
{"K_CTRL_F10    ",K_CTRL_F10    },
{"K_CTRL_F11    ",K_CTRL_F11    },
{"K_CTRL_F12    ",K_CTRL_F12    },
{"K_ALT_F1      ",K_ALT_F1      },
{"K_ALT_F2      ",K_ALT_F2      },
{"K_ALT_F3      ",K_ALT_F3      },
{"K_ALT_F4      ",K_ALT_F4      },
{"K_ALT_F5      ",K_ALT_F5      },
{"K_ALT_F6      ",K_ALT_F6      },
{"K_ALT_F7      ",K_ALT_F7      },
{"K_ALT_F8      ",K_ALT_F8      },
{"K_ALT_F9      ",K_ALT_F9      },
{"K_ALT_F10     ",K_ALT_F10     },
{"K_ALT_F11     ",K_ALT_F11     },
{"K_ALT_F12     ",K_ALT_F12     },
{0,0}};

//---------------------------------------------------------------------------
int main(int argc, char**argv)
{
    int i=0;
    while( 1 )
    {
        if( keymap[i].name==0 )
        {
            return 0;
        }

        printf("%s",keymap[i].name);
        fflush(0);
        while( 0==readkey() );
        printf(",%d\n",keymap[i].code);

        i++;
    }
}

//---------------------------------------------------------------------------



