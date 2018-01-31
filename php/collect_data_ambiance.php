<?php

$temp = $_GET['temp'];

echo "<h1>debut</h1>";

try
{
echo "<h1>try</h1>";
$conn = new PDO('mysql:host=localhost;dbname=test','root','root');
}
catch(Exception $e)
{	
	echo "<h1>bdd erreur</h1>";
	die('Erreur : '.$e->getMessage());
}

$conn->exec('INSERT INTO test(temp) VALUES(' . $temp . ')');

echo "<h1>The data has been sent!!</h1>";
?>

