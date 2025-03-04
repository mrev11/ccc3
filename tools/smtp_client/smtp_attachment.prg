

class smtp.attachment(object)
    attrib  name
    attrib  b64_data
    
    method  initialize



static function smtp.attachment.initialize(this,name,b64_data)
    this:name:=name
    this:b64_data:=b64_data
    
    return this