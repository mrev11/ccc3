
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


#include <string.h>
#include <stdlib.h>

//----------------------------------------------------------------------------
static unsigned int __hashcode(const char *p)
{
    unsigned hcode;
    for( hcode=0; *p; p++ )
    {
        hcode+=(unsigned)*p;
        hcode*=99817; //prím
    }
    return hcode;
}


//-----------------------------------------------------------------------------
struct node
{
    const char *key;
    void *value;
};

//-----------------------------------------------------------------------------
class hashtable_simple
{
  private:

    node *buffer;
    unsigned int buflen;
    unsigned int itemcount;

    void rebuild()
    {
        //printf("rebuild %d\n",buflen);fflush(0);

        hashtable_simple *temp=new hashtable_simple(buflen+buflen);
        unsigned int i;
        for(i=0; i<buflen; i++)
        {
            if( buffer[i].key )
            {
                temp->add(buffer[i].key,buffer[i].value);
            }
        }
        free(buffer);
        buffer=temp->buffer;
        buflen=temp->buflen;
    };

    int index(char const *key)
    {
        unsigned int hcode=__hashcode(key);
        unsigned int hidx=hcode%buflen;
        
        while(1)
        {
            if( buffer[hidx].key==0 )
            {
                return hidx;
            }
            else if( strcmp(key,buffer[hidx].key)==0 )
            {
                return hidx;
            }
            else if( ++hidx>=buflen )
            {
                hidx=0;
            }
        }
        return 0;
    };

  public:

    hashtable_simple(int len=256)
    {
        itemcount=0;
        buflen=len;
        buffer=(node*)malloc(sizeof(node)*buflen);
        memset(buffer,0,sizeof(node)*buflen);
    };
    
    ~hashtable_simple()
    {
        free(buffer);
    }

    void *get(const char *key)
    {
        unsigned int x=index(key);
        return buffer[x].value;
    }
  
    void add(const char *key, void *value)
    {
        //printf("add %s %s %d/%d\n",key,value,itemcount,buflen);

        unsigned int x=index(key);
        if( buffer[x].key==0 )
        {
            if( ++itemcount>(2*buflen/3) )
            {
                rebuild();
                x=index(key);
            }
        }
        buffer[x].key=key;
        buffer[x].value=value;
    }
};

//-----------------------------------------------------------------------------

