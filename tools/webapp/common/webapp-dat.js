

//-------------------------------------------------------------------------------
XCODE.dat2str=function(d) //datumok formazasa: YYYY-MM-DD
//-------------------------------------------------------------------------------
{
    var s=d.getFullYear().toString();
    s+="-"+(1+d.getMonth()).toLocaleString("en-US",{minimumIntegerDigits:2})
    s+="-"+d.getDate().toLocaleString("en-US",{minimumIntegerDigits:2})
    return s
}

//-------------------------------------------------------------------------------
XCODE.datsettlevalue=function(ctrl)
//-------------------------------------------------------------------------------
{
    if( ctrl.xreadvalue==undefined )
    {
        ctrl.xreadvalue=function()
        {
            return this.value.replace(/-/g,"");
        }
    }
    var x=ctrl.xreadvalue();
    x=x.slice(0,4)+"-"+x.slice(4,6)+"-"+x.slice(6,8);
    x=x.replace("--","");
    ctrl.value=x; 
}

//-------------------------------------------------------------------------------
XCODE.datkeypress=function(e) 
//-------------------------------------------------------------------------------
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
        var x=ctrl.value; //tartalom az aktualis karakter nelkul
        var pos=ctrl.selectionStart; //caret pozicio
        var chr=String.fromCharCode(e.charCode); //aktualis karakter
        x=x.slice(0,pos)+chr+x.slice(pos); //karakter beillesztve
        x=x.replace(/-/g,"" ); //kiszedi a szemetet
        x=x+"19991010".slice(x.length);
        x=x.slice(0,4)+"-"+x.slice(4,6)+"-"+x.slice(6);
        x=x.replace("-00","-01");
        d=new Date(x);  //pl. new Date('1954-10-11')
        
        if( !(x==XCODE.dat2str(d))  )
        {
            //beillesztes letiltva
            e.preventDefault();
        }
    }
}

//-------------------------------------------------------------------------------


