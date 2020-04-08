<?php

	$dsn = 'mysql:dbname=bdd_escape_game;host=localhost';
	$user = 'root';
	$password = '';

	global $dbh;
	
	try {
		$dbh = new PDO('mysql:host=localhost; dbname=bdd_espace_game; charset=utf8', $user, $password);
		$dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		$dbh->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
    echo "Connected successfully"; 
    } catch(PDOException $e) 
	{    
    die('Erreur : ' . $e->getMessage());
    }
		
?>