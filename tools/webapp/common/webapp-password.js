
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
XCODE.getpwstrength=function(srcid)
//------------------------------------------------------------------------------
{
    var ctrl=XCODE.document.x.getElementById(srcid);
    var pswd=ctrl.value


    var score = 0;
    if (!pswd){
        return score;
    }

    // award every unique letter until 5 repetitions
    var letters = new Object();
    for (var i=0; i<pswd.length; i++) {
        letters[pswd[i]] = (letters[pswd[i]] || 0) + 1;
        score += 5.0 / letters[pswd[i]];
    }

    // bonus points for mixing it up
    var variations = {
        digits: /\d/.test(pswd),
        lower: /[a-z]/.test(pswd),
        upper: /[A-Z]/.test(pswd),
        nonWords: /\W/.test(pswd),
    }

    variationCount = 0;
    for (var check in variations) {
        variationCount += (variations[check] == true) ? 1 : 0;
    }
    score += (variationCount - 1) * 10;

    var x="<pwstrength>"
    x+=parseInt(score).toString();
    x+="</pwstrength>"
    XCODE.send(x);
}

//------------------------------------------------------------------------------
