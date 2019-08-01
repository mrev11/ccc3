
//------------------------------------------------------------------------------
XCODE.xpattern=function(ctrl)
//------------------------------------------------------------------------------
{
    if( ctrl.xpattern==undefined )
    {
        var pat=ctrl.pattern;
        if(!pat.startsWith("^")){pat="^"+pat;}
        if(!pat.endsWith("$")){pat+="$";}
        var match=pat.match(/(\[[^\]]+\])|(\{[^}]+\})|(\\.)|(.)/g);
        // (\[[^\]]+\])
        // (\{[^}]+\})
        // (\\.)
        // (.)
        var xpat="";
        for( var n=0; n<match.length; n++ )
        {
            var x=match[n];
            if( x[0]=='[' )
            {
                x='[\\v'+x.slice(1); // [0-9] -> [\v0-9]
            }
            else if( x[0]=='\\' )
            {
                x='[\\v'+x+']'; // \x -> [\v\x]
            }
            else if( "^?*+{()|".includes(x[0]) )
            {
            }
            else if( "$".includes(x[0]) )
            {
                x='\\v*$'; // $ -> \v*$
            }
            else
            {
                //x='[\\v'+x+']'; //x -> [\vx]  hiba:  [\v.] rossz
                x='(\\v|'+x+')'; //x -> (\v|x)
            }
            xpat+=x;
        }
        //console.log(pat);
        //console.log(match.toString());
        //console.log(xpat);
        ctrl.xpattern=xpat;
    }
    return ctrl.xpattern;
}

//------------------------------------------------------------------------------
XCODE.patsettlevalue=function(ctrl)
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
    //console.log("patsettlevalue",ctrl.id,"edit=",edit,"settle=",settle,origvalue);

    if( ctrl.xreadvalue==undefined )
    {
        //honnan hivodik?
        //modszer a callstack megtekintesere
        //console.log(new Error().stack);

        ctrl.xreadvalue=function()
        {
            var v=this.value;
            if( v!="" )
            {
                var r=new RegExp(this.pattern)
                if( !r.test(v) )
                {
                    v="? "+v;
                }
            }
            return v;
        }
    }

    if( edit && !settle && ctrl.value!=origvalue )
    {
        //console.log("dispatch");
        ctrl.dispatchEvent(new Event('change'));
    }
}

//------------------------------------------------------------------------------
XCODE.patkeypress=function(e)
//------------------------------------------------------------------------------
{
    var ctrl=e.target; //input mezo

    if( e.charCode==0 )
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

        var pat=XCODE.xpattern(ctrl);
        var reg=new RegExp(pat);
        var str=x+String.fromCharCode(11).repeat(1024);  // chr(11)=\v (vertical tab)

        //console.log(str);
        //console.log(reg);
        //console.log(reg.test(str));

        if( !reg.test(str) ) 
        {
            e.preventDefault();
        }
    }
} 

//------------------------------------------------------------------------------


