<?php

$cmd = $_GET['cmd'];

$fp = fopen ("/dev/rfcomm0", "w+");
if (!$fp) {
    echo "Error";
} else {
    fputs ($fp, $cmd);
    $contents = fgets($fp);
    fclose ($fp);
    echo $contents;
}

?>
