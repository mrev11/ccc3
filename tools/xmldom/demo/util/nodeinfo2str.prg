

function nodeinfo2str(nodeinfo)

//    attrib  type
//    attrib  fullpath
//    attrib  nsmap
//    attrib  buildflag
//    attrib  userdata
//    method  nsprefix
//    method  namespace
//    method  uqname


local x:=""

    x+=nodeinfo:fullpath::padr(32)
    //x+="type="+nodeinfo:type::padr(16)
    //x+="nsmap="+nodeinfo:nsmap:toarr::any2str//::padr(64)

    return x

