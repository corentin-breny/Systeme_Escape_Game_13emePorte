<?php

	$dsn = 'mysql:dbname=bdd_escape_game;host=127.0.0.1';
	$user = 'root';
	$password = '';

	//$connexion = new PDO('mysql:host='.$PARAM_hote.';port='.$PARAM_port.';dbname='.$PARAM_nom_bdd, $PARAM_utilisateur, $PARAM_mot_passe);
	
	try {
    $dbh = new PDO($dsn, $user, $password);
	} catch (PDOException $e) {
    echo 'Connexion échouée : ' . $e->getMessage();
	}
	
?>