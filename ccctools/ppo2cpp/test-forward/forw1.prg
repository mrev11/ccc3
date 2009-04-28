
static globvar:="globvar"

*******************************************************************************
class adapter(object)
    method  initialize
    method  hopp
    attrib  error
    attrib  x

static function adapter.initialize(this)
    this:error:=errorNew()
    this:x:="adapter.x"
    return this

static function adapter.hopp(*)
    //? {"hopp",*}
    varstack()
    return "HOPP"


*******************************************************************************
class derived(object)
    method  initialize

    attrib  adapter
    attrib  x
    method  masik
    method  ugv         upper(globvar)   //=> {||upper(globvar)}


    method  hopp        :adapter:hopp
    method  desc        :adapter:error:description
    method  ax          :adapter:x
    method  dx          :x
    method  egyik       :masik


static function derived.initialize(this,adapter)
    this:(object)initialize
    this:adapter:=adapter
    this:x:="derived.x"
    return this

static function derived.masik(this,*)
    //? {"masik",*}
    varstack()
    return "MASIK"


*******************************************************************************
function main()

local a:=adapterNew()
local d:=derivedNew(a)

    ? d:hopp("a","bb","ccc","dddd","eeeee")
    ? d:egyik(11,22,33,44)

    ? d:ax
    ? d:dx
    d:ax:=upper(d:ax)
    d:dx:=upper(d:dx)
    ? d:ax
    ? d:dx
    
    a:error:description:="vanaki forrón"
    ? d:desc
    d:desc:=upper(d:desc)
    ? a:error:description
    
    ? d:ugv

    ?

*******************************************************************************
    