<?php
setcookie("zoldseg","articsóka",0);
//setcookie("zoldseg","articsoka",time()+3600,"/");
?>
<html><head><title>Cookies</title></head>
<body>
<?php

    $zoldseg=$_COOKIE['zoldseg'];
    echo $zoldseg;

    if( isset( $zoldseg ) )
    {
        print("<p>Az Ön által kiválasztott zöldség a(z) $zoldseg.</p>");
    }
    else
    {
        print("<p>Üdvözöljük, ez az Ön első látogatása.</p>");
    }
?>

</body>
</html>

<?php?>
