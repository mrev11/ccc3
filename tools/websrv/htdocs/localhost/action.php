<?php 
    //phpinfo(); 

    echo '_REQUEST=', count($_REQUEST), '<br>'; //_POST vagy _GET
    echo '_GET=', count($_GET), '<br>';
    echo '_POST=', count($_POST), '<br>';

    foreach( $_REQUEST as $kulcs => $ertek )
    {
        print( "$kulcs=$ertek<br>" );
    }

    echo "HOPP";
?>
