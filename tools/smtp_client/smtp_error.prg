

class smtp.error(apperror)
    method  initialize


static function smtp.error.initialize(this,expected,rsp)
    this:(error)initialize
    this:subsystem:="smtp"
    this:operation:="smtp.read"
    this:description:="unexpected response"
    this:args({expected,val(rsp),rsp})
    return this

    