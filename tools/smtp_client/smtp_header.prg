
class smtp.header(object)
    attrib  key
    attrib  value
    
    method  initialize
    

static function smtp.header.initialize(this,k,v)
    this:key:=k    
    this:value:=v
    return this
    