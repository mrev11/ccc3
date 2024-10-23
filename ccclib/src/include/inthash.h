
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
#include <stdlib.h>

class inthash
{
  private:
    
    int index(int key)
    {
        int xkey=abs(key)%size;
    
        while(1)
        {
            if( pkey[xkey]==0 )
            {
                return xkey;
            }
            else if( pkey[xkey]==key )
            {
                return xkey;
            }
            else if( ++xkey>=size  )
            {
                xkey=0;
            }
        }
    }

  public:

    int count;
    int size;
    int *pkey;
    int *pval;
    
    void set(int key, int val)
    {   
        int xkey=index(key);

        if(pkey[xkey]==0)
        {
            count++;
        }
        pkey[xkey]=key;
        pval[xkey]=val;
    }

    int get(int key)
    {
        return pval[index(key)];
    }


    int getx(int key)
    {
        int val=pval[index(key)];
        return  val?val:key;
    }


    int bulk( int *keys, int*vals)
    {
        for(int i=0; keys[i]!=0; i++)
        {
            set(keys[i],vals[i]);
        }
        return count;
    }


    inthash(int hashsize)
    {
        count=0;
        size=hashsize;
        pkey=(int*)calloc(size,sizeof(int));
        pval=(int*)calloc(size,sizeof(int));
    }

    inthash(int hashsize, int *keys, int*vals)
    {
        count=0;
        size=hashsize;
        pkey=(int*)calloc(size,sizeof(int));
        pval=(int*)calloc(size,sizeof(int));
        bulk(keys,vals);
    }


    ~inthash()
    {
        free(pkey);
        free(pval);
    }
};
