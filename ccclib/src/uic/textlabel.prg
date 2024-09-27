

class textlabel(get)
    method  initialize



static function textlabel.initialize(this,r,c,b,v) 
    this:(get)initialize(r,c,b,v)
    this:preblock:={||.f.}
    this:picture:=replicate("X",len(this:varget))
    return this



    