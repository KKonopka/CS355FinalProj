<?php

$link = mysql_connect("localhost", "root", "pass");

mysql_select_db("imagedb");

$sql = "SELECT img FROM images ORDER BY id DESC LIMIT 1";
$result = mysql_query("$sql");

$row = mysql_fetch_assoc($result);

mysql_close($link);

header("Content-type: image/jpeg");
echo $row['img'];

?>
