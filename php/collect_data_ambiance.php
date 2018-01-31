<?php

$temp = $_GET['temp'];
$hum = $_GET['hum'];
$date_mes = date("Y-m-d");
$heure_mes = date("H:i:s");

echo "$date_mes";
echo "$heure_mes";
echo "$temp";
echo "$hum";

try
{
$conn = new PDO('mysql:host=localhost;dbname=domotique','root','root');
}

catch(Exception $e)
{	
	die('Erreur : '.$e->getMessage());
}

$conn->exec('CREATE TABLE IF NOT EXISTS `Ambiance`(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,date_mes DATE, heure_mes TIME, temp INT, hum INT)');
$conn->exec('INSERT INTO Ambiance(date_mes,heure_mes,temp,hum) VALUES("' . $date_mes . '","' . $heure_mes . '",' . $temp . ',' . $hum . ')');

echo "<h1>The data has been sent!!</h1>";
?>

