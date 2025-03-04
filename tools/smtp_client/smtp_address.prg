

******************************************************************************************
class smtp.address(object)
    attrib  email
    attrib  name
    attrib  type   // -> SMTP_ADDRESS_FROM ...

    method  initialize


******************************************************************************************
static function smtp.address.initialize(this,type,email,name)
    this:type:=type
    this:email:=email
    this:name:=name
    return this

******************************************************************************************
    