<?php

	$dsn = 'mysql:dbname=bdd_escape_game;host=localhost';
	$user = 'root';
	$password = '';

	//$connexion = new PDO('mysql:host='.$PARAM_hote.';port='.$PARAM_port.';dbname='.$PARAM_nom_bdd, $PARAM_utilisateur, $PARAM_mot_passe);
	
	global $dbh;
	
	try {
		$dbh = new PDO('mysql:host=localhost; dbname=bdd_escape_game; charset=utf8', $user, $password);
		$dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		$dbh->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
    echo "Connected successfully"; 
    } catch(PDOException $e) 
	{    
    die('Erreur : ' . $e->getMessage());
    }
		
?>