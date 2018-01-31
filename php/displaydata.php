<!DOCTYPE html>
<html>
	<body>
<?php
$servername = 'localhost';
$username = 'root';
$password = 'root';
$dbname = 'test';

try
{
	$bdd = new PDO('mysql:host=localhost;dbname=test;charset=utf8','root,'root');
}
catch(Exception $e)
{
	die('Erreur : '.$e->getMessage());
}

$reponse = $bdd->query('SELECT * FROM test ORDER BY id DESC LIMIT 0,5');
while ($donnees = $reponse->fetch())
{
	?>
	<p>
	La température relevee est : <?php echo $donnees['temp']; ?> °C <br />
	</p>
<?php
}

$reponse->closeCursor();

?>
	</body>
</html>

