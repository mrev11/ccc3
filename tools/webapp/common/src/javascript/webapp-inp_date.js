

//------------------------------------------------------------------------------
XCODE.dat2str=function(d) //datumok formazasa: YYYY-MM-DD
//------------------------------------------------------------------------------
{
    var yyyy=(d.getFullYear()).toString();
    var mm=(1+d.getMonth()).toString();
    var dd=(d.getDate()).toString();
    yyyy=("0000"+yyyy);yyyy=yyyy.slice(yyyy.length-4); //padl
    mm=("00"+mm);mm=mm.slice(mm.length-2); //padl
    dd=("00"+dd);dd=dd.slice(dd.length-2); //padl
    return yyyy+"-"+mm+"-"+dd;
}


//------------------------------------------------------------------------------
XCODE.datisvalid=function(s) //datumstring ellenorzes
//------------------------------------------------------------------------------
{
    //elfogadja, ha kiegeszitheto (!) ervenyes datumma 

    s=s.replace(/-/g,""); //kiszedi a szemetet
    s=s.replace(/ /g,""); //kiszedi a szemetet
    s+="19991010".slice(s.length); //kiegesziti 8 hosszura
    s=s.slice(0,4)+"-"+s.slice(4,6)+"-"+s.slice(6); //tagol:yyyy-mm-ddx*
    s=s.replace("-00","-01"); //korrekcio
    return s==XCODE.dat2str(new Date(s));
}

//------------------------------------------------------------------------------
XCODE.datreadvalue=function(ctrl)
//------------------------------------------------------------------------------
{
    var v=ctrl.value;
    var x=v;
    if( v=="" )
    {
        return x;
    }
    x=x.replace(/-/g,"" );
    x=x.replace(/ /g,"" );
    if( x.length!=8 || !XCODE.datisvalid(x) )
    {
        return "? "+x;  //invalid
    }
    return x;
} 

//------------------------------------------------------------------------------
XCODE.datsettlevalue=function(ctrl)
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
    //console.log("datsettlevalue",ctrl.id,"edit=",edit,"settle=",settle,origvalue);
 
    if( ctrl.xreadvalue==undefined )
    {
        ctrl.xreadvalue=function()
        {
            return XCODE.datreadvalue(this);                
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
    v=v.replace(/-/g,"" );
    v=v.replace(/ /g,"" );
    var num="0123456789";
    var pic="9999-99-99";
    var i=0,j=0;
    for(i=0,j=0; i<pic.length && j<v.length; i++,j++)
    {
        var t=pic.charAt(i);
        if( t=="9" )
        {
            if((num).includes(v.charAt(j))) 
            {
                x+=v.charAt(j);
            }
            else
            {
                return "? "+x;
            }
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
    if( j<v.length )
    {
        return "? "+x;
    }
    if( i<pic.length )
    {
        return "? "+x;
    }
    if( !XCODE.datisvalid(x) )
    {
        x+=" " //ne illeszkedjen!
    }
    ctrl.value=x;

    if( edit && !settle && ctrl.value!=origvalue )
    {
        //console.log("dispatch");
        ctrl.dispatchEvent(new Event('change'));
    }
    return x;
    
    //a return ertek nincs sehol felhasznalva
    //egyedul a ctrl.value beallitasa szamit
} 

//------------------------------------------------------------------------------
XCODE.datkeypress=function(e) 
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
        var v=ctrl.value.trim(); //eredeti tartalom
        var pos=ctrl.selectionStart; //caret pozicio
        var chr=String.fromCharCode(e.charCode); //aktualis karakter
        var x=v.slice(0,pos)+chr; //balfel + uj karakter
        var xr=v.slice(pos); //jobbfel
        var num="0123456789";
        var pic="9999-99-99";

        var i=0, j=0;
        for(i=0, j=0; i<pic.length && j<x.length; i++ )
        {
            var t=pic.charAt(i);
            if( t=="9" )
            {
                if((num).includes(x.charAt(j)))
                {
                    j++;
                } 
                else 
                {
                    break;
                }
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

        if( j>=x.length && XCODE.datisvalid(x) )
        {
            //(balfel + uj karakter) illeszkedik
            //(balfel + uj karakter) kiegeszitheto datumma
            //ha ez fennall, akkor beengedjuk a leutest

            var offs=x.length+xr.length-pic.length;
            if( offs>0 )
            {
                xr=xr.slice(offs)
            }
            ctrl.value=x+xr;
            if( !XCODE.datisvalid(ctrl.value) )
            {
                ctrl.value+=" " //ne illeszkedjen!
            }
            ctrl.selectionStart=pos+1;
            ctrl.selectionEnd=pos+1;
            ctrl.focus();
        }
        e.preventDefault();
    }
}

//------------------------------------------------------------------------------
