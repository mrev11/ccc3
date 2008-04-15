<html>
<head><title>Env</title></head>
<body>
<?php 

    echo "cwd=",getcwd(),"<br>";

    ksort($_ENV);

    foreach( $_ENV as $key => $value )
    {
        print( "$key=$value<br>" );
    }

?>
</body>
</html>
