

//------------------------------------------------------------------------------
XCODE.xpicture=function(ctrl)
//------------------------------------------------------------------------------
{
    if( ctrl.xpicture==undefined )
    {
        ctrl.xpicture=ctrl.getAttribute("data-picture");
        var xpat="^";
        var p="",r=0;
        var last=false;

        var addexp=function()
        {
            //console.log(xpat,p,r);
            if( p=="" )
            {
            }
            else if( "09".includes(p) )
            {
                xpat+="[0-9]";
            }   
            else if("aA".includes(p))
            {
                xpat+="[a-zA-Z]";
            }   
            else if("nN".includes(p))
            {
                xpat+="[0-9a-zA-Z]";
            }   
            else if( "X".includes(p) )
            {
                xpat+=".";
            }   
            else if("?*+{}()[]|^$".includes(p) )
            {
                xpat+="\\"+p;
            }
            else if(p=="\\")
            {
                xpat+="\\\\";
            }   
            else
            {
                xpat+=p;
            } 
        
            if( last && p=='X' )
            {
                xpat+="{0,"+r.toString()+"}" //X-ek a vegen elhagyhatok
            }
            else if(r>1)
            {
                xpat+="{"+r.toString()+"}"
            }
        }

        for(var n=0; n<ctrl.xpicture.length; n++)
        {
            var c=ctrl.xpicture[n];
            if( c==p )
            {
                r++;
            }
            else
            {
                addexp();
                p=c;
                r=1;
            }
        }
        if(r>0)
        {
            last=true;
            addexp();
        }
        xpat+="$";
        //console.log(new Error("testing XCODE.xpicture").stack);
        //console.log(ctrl.xpicture);
        //console.log(xpat);
        ctrl.pattern=xpat;
    }
    return ctrl.xpicture;

}

//------------------------------------------------------------------------------
XCODE.picreadvalue=function(ctrl)
//------------------------------------------------------------------------------
{
    var v=ctrl.value;
    var x="";
    if( v=="" )
    {
        return x;
    }
    var num="0123456789";
    var abc="abcdefghijklmnopqrstuvwxyz";
    var ABC="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    var pic=XCODE.xpicture(ctrl);
    for(var i=0, j=0; i<pic.length && j<v.length; i++,j++ )
    {
        var t=pic.charAt(i);
        if( "09".includes(t) )
        {
            if((num).includes(v.charAt(j))) {x+=v.charAt(j);}else{return "? "+x;}
        }
        else if( "Aa".includes(t) )
        {
            if((abc+ABC).includes(v.charAt(j))) {x+=v.charAt(j);}else{return "? "+x;}
        }
        else if( "Nn".includes(t) )
        {
            if((num+abc+ABC).includes(v.charAt(j))) {x+=v.charAt(j);}else{return "? "+x;}
        }
        else if( "X".includes(t) )
        {
            x+=v.charAt(j);
        }
        else 
        {
            if( t!=v.charAt(j) ) {return "? "+x;}
        }
    }

    //1) lehet, hogy pic es v egyszerre elfogyott -> kesz
    //2) lehet, hogy v-bol maradt -> hibas adat
    //3) lehet, hogy pic-bol maradt -> el kell fogyasztani

    for( ; j<v.length; j++  )
    {
        return "? "+x;
    }
    for( ; i<pic.length; i++  )
    {
        var t=pic.charAt(i);
        if( "9AaNnX".includes(t) )
        { 
            return "? "+x;
        }
    }
    return x;
} 


//------------------------------------------------------------------------------
XCODE.picsettlevalue=function(ctrl)
//------------------------------------------------------------------------------
{
    var edit=false;
    var settle=false;
    var origvalue;
    if( ctrl.edit_in_progress )
    {
        edit=true;
        settle=ctrl.edit_in_progress.settle;
        origvalue=ctrl.edit_in_progress.origvalue;
        ctrl.edit_in_progress=null;
    }
    //console.log("picsettlevalue",ctrl.id,"edit=",edit,"settle=",settle,origvalue);

    if( ctrl.xreadvalue==undefined )
    {
        ctrl.xreadvalue=function()
        {
            return XCODE.picreadvalue(this);                
        }
    }
    var v=ctrl.value;
    var x="";
    if( v=="" )
    {
        if( edit && !settle && ctrl.value!=origvalue )
        {
            //console.log("dispatch");
            ctrl.dispatchEvent(new Event('change'));
        }
        return x;
    }
    var num="0123456789";
    var abc="abcdefghijklmnopqrstuvwxyz";
    var ABC="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    var pic=XCODE.xpicture(ctrl);
    var i=0,j=0;
    for(i=0,j=0; i<pic.length && j<v.length; i++,j++)
    {
        var t=pic.charAt(i);
        if( "09".includes(t) )
        {
            if((num).includes(v.charAt(j))) {x+=v.charAt(j);}else{return "? "+x;}
        }
        else if( "a".includes(t) )
        {
            if((abc+ABC).includes(v.charAt(j))){x+=v.charAt(j);}else{return "? "+x;}
        }
        else if( "A".includes(t) )
        {
            if((abc+ABC).includes(v.charAt(j))){x+=v.charAt(j).toUpperCase();}else{return "? "+x;}
        }
        else if( t=="n" )
        {
            if((num+abc+ABC).includes(v.charAt(j))) {x+=v.charAt(j);}else{return "? "+x;}
        }
        else if( t=="N" )
        {
            if((num+abc+ABC).includes(v.charAt(j))) {x+=v.charAt(j).toUpperCase();}else{return "? "+x;}
        }
        else if( t=="X" )
        {
            x+=v.charAt(j);
        }
        else 
        {
            x+=t;
            if( t!=v.charAt(j) )
            {
                --j;
            }
        }
    }

    //1) lehet, hogy pic es v egyszerre elfogyott -> kesz
    //2) lehet, hogy v-bol maradt -> hibas adat
    //3) lehet, hogy pic-bol maradt -> el kell fogyasztani

    for( ; j<v.length; j++  )
    {
        return "? "+x;
    }
    for( ; i<pic.length; i++  )
    {
        var t=pic.charAt(i);
        if( "9AaNnX".includes(t) )
        { 
            return "? "+x;
        }
        else
        {
            x+=t;
        }
    }

    if( edit && !settle && ctrl.value!=origvalue )
    {
        //console.log("dispatch");
        ctrl.dispatchEvent(new Event('change'));
    }
    ctrl.value=x;
    return x;
} 


//------------------------------------------------------------------------------
XCODE.pickeypress=function(e)                                                  
//------------------------------------------------------------------------------
{
    var ctrl=e.target; //input mezo

    if( XCODE.evententer(e) && e.target.onblur!=undefined )
    {
        ctrl.onblur(ctrl);
    }
    else if( e.charCode==0 )
    {
        //del,bs,right,left,...
    }
    else
    {
        var v=ctrl.value; //tartalom az aktualis karakter nelkul
        var pos=ctrl.selectionStart; //caret pozicio
        var chr=String.fromCharCode(e.charCode); //aktualis karakter
        var x=v.slice(0,pos)+chr; //balfel + uj karakter
        var xr=v.slice(pos); //jobbfel
        var num="0123456789";
        var abc="abcdefghijklmnopqrstuvwxyz";
        var ABC="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        var pic=XCODE.xpicture(ctrl);

        var i=0, j=0;
        for(i=0, j=0; i<pic.length && j<x.length; i++ )
        {
            var t=pic.charAt(i);
            if( "09".includes(t) )
            {
                if((num).includes(x.charAt(j))){j++;} else {break;}
            }
            else if( "a".includes(t) )
            {
                if((abc+ABC).includes(x.charAt(j))){j++;} else {break;}
            }
            else if( "A".includes(t) )
            {
                if( abc.includes(x.charAt(j)) )
                {
                    if( x.charAt(j)!=x.charAt(j).toUpperCase() )
                    {
                        x=x.slice(0,j)+x.charAt(j).toUpperCase()+x.slice(j+1);
                    }
                    j++;
                }
                else if( ABC.includes(x.charAt(j)) )
                {
                    j++;
                }
                else
                {
                    break;
                }
            }
            else if( "n".includes(t) )
            {
                if((num+abc+ABC).includes(x.charAt(j))){j++;} else {break;}
            }
            else if( "N".includes(t) )
            {
                if( (abc).includes(x.charAt(j))) 
                {
                    x=x.slice(0,j)+x.charAt(j).toUpperCase()+x.slice(j+1);
                    j++;
                } 
                if( (num+ABC).includes(x.charAt(j))) 
                {
                    j++;
                } 
                else   
                {
                    break;
                }
            }
            else if( "X".includes(t) )
            {
                j++;
            }
            else 
            {
                if( t==x.charAt(j) )
                {
                    j++;
                }
                else
                {
                    x=x.slice(0,j)+t+x.slice(j);
                    j++;
                    pos++;
                }
            }
        }
        if( j>=x.length )
        {
            var offs=x.length+xr.length-pic.length;
            if( offs>0 )
            {
                xr=xr.slice(offs)
            }
            ctrl.value=x+xr;
            ctrl.selectionStart=pos+1;
            ctrl.selectionEnd=pos+1;
            ctrl.focus();
        }
        e.preventDefault();
    }
}

//------------------------------------------------------------------------------
