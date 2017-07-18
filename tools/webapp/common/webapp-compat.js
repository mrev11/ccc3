

if( String.prototype.includes==undefined )
{
    String.prototype.includes=function(x)
    {
        return this.indexOf(x)>=0;
    }
}

if( String.prototype.startsWith==undefined )
{
    String.prototype.startsWith=function(x)
    {
        return this.indexOf(x)==0;
    }
}

if( String.prototype.endsWith==undefined )
{
    String.prototype.endsWith=function(x)
    {
        return this.lastIndexOf(x)==(this.length-x.length);
    }
}

if( String.prototype.repeat==undefined )
{
    String.prototype.repeat=function(x)
    {
        var r="";
        while(x>0.5)
        {
            r+=this;
            x--;
        } 
        return r;
    }
}

