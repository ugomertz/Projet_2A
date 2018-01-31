<?php

$etat = $_GET['etat'];
$date_mes = date("Y-m-d");
$heure_mes = date("H:i:s");

try
{
    $conn = new PDO('mysql:host=localhost;dbname=domotique','root','root');
}

catch(Exception $e)
{	
	die('Erreur : '.$e->getMessage());
}

$conn->exec('CREATE TABLE IF NOT EXISTS `congelateur`(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,date_mes DATE, heure_mes TIME, etat VARCHAR(64))');
$conn->exec('INSERT INTO congelateur(date_mes,heure_mes,etat) VALUES("' . $date_mes . '","' . $heure_mes . '","' . $etat . '")');

echo "<h1>The data has been sent!!</h1>";
?>

