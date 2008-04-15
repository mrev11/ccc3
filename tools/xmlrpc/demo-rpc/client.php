<html>
<head><title>xmlrpc</title></head>
<body>
<?php
include("xmlrpc.inc");

    $c=new xmlrpc_client("/RPC2", "suse", 45000);
    $c->setDebug(1);

//    $f=new xmlrpcmsg('system.listMethods');
//    $f=new xmlrpcmsg('sample.array');
    $f=new xmlrpcmsg('sample.echo');
//    $f=new xmlrpcmsg('sample.struct');
 
    $f->addparam(new xmlrpcval( "", "string"));
//    $f->addparam(new xmlrpcval("hopp"));
//    $f->addparam(new xmlrpcval("próba","string"));
//    $f->addparam(new xmlrpcval("szerencse","string"));
//    $f->addparam(new xmlrpcval(1,"boolean"));
 
    $r=$c->send($f); 

    if( !$r )
    { 
        echo "send failed"; 
    }
    else if( $r->faultCode() ) 
    {
        echo  $r->faultCode(), $r->faultString();
    } 
    else 
    {
        echo $r->serialize();
    }

?>
</body>
</html>
