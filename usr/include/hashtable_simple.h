
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
union hashvalue
{
    int         value_int;
    unsigned    value_unsigned;
    long        value_long;
    double      value_double;
    void       *value_vptr;
    char       *value_cptr;
};

//-----------------------------------------------------------------------------
struct hashitem
{
    const char *key;
    hashvalue value;
};

//-----------------------------------------------------------------------------
class hashtable_simple
{
  private:

    hashitem *buffer;
    unsigned int buflen;
    unsigned int itemcount;
    unsigned int iter;

    static unsigned hashcode(const char *p)
    {
        unsigned hcode;
        for( hcode=0; *p; p++ )
        {
            hcode+=(unsigned)*p;
            hcode*=99817; //prím
        }
        return hcode;
    }

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
        unsigned int hcode=hashcode(key);
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
        buffer=(hashitem*)malloc(sizeof(hashitem)*buflen);
        memset(buffer,0,sizeof(hashitem)*buflen);
    };
    
    ~hashtable_simple()
    {
        free(buffer);
    }

    hashvalue get(const char *key)
    {
        unsigned int x=index(key);
        return buffer[x].value;
    }
  
    void add(const char *key, hashvalue value)
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
    
    hashitem *first()
    {
        iter=0;
        while( iter<buflen && buffer[iter].value.value_vptr==0 )
        {
            iter++;
        }
        return iter<buflen?buffer+iter:(hashitem*)0;
    }

    hashitem *next()
    {
        iter++;
        while( iter<buflen && buffer[iter].value.value_vptr==0 )
        {
            iter++;
        }
        return iter<buflen?buffer+iter:(hashitem*)0;
    }
};

//-----------------------------------------------------------------------------

