<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
		<link rel="stylesheet" href="style2.css" />
        <title>Notre page web</title>
    </head>

    <body>
        <header>
		<img src="images/logo.png" class = "imageflottante" />
		<h1> Page web projet 2A </h1>
		<p> Vous êtes sur la page des mesures du capteur d'ambiance </p>
	</header>
		
	<div id="main">
	<nav>
		<h3> Menu </h3>
		</br>
		<ul>
			<li> <a href= index.php>Acceuil </a> </li>
			<li> <a href= station.php>Station météo </a> </li>
			<li> <a href= surveillance.php>Surveillance habitation </a> </li>
			<li> <a href= apropos.php>A propos </a> </li>
			
		</ul>
	</nav>
	
	<section>
		<article>
			<p> Cette fonctionnalité n'est malheureusement pas encore disponible en dynamique.</br> </p>
			
			<?php

				try
				{
					$bdd = new PDO('mysql:host=localhost;dbname=test','root','root');
				}
				catch(Exception $e)
				{
					die('Erreur : '.$e->getMessage());
				}

				$reponse = $bdd->query('SELECT * FROM test ORDER BY id DESC LIMIT 1');
				while ($donnees = $reponse->fetch())
				{
					?>
					<p>
					La température relevée est : <?php echo $donnees['temp']; ?> °C <br />
					</p>
					<?php
				}

				$reponse->closeCursor();
			?>
		</article>
	
	</section>
	
	
	</div>
	<footer> <p> Victor Ugo domotique </p> </footer>
    </body>
</html>
