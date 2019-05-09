
//------------------------------------------------------------------------------
XCODE.getpassword=function(srcid,salt1,salt2)
//------------------------------------------------------------------------------
{
    var x="<password>"
    var ctrl=XCODE.document.x.getElementById(srcid);
    var pswd=ctrl.value
    if( salt1!=null )
    {
        pswd=XCODE.md5(pswd+salt1)
    }
    if( salt2!=null )
    {
        pswd=XCODE.md5(pswd+salt2)
    }
    x+=pswd
    x+="</password>"
    XCODE.send(x);

}

//------------------------------------------------------------------------------

