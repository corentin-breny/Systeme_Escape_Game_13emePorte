<?php

	$PARAM_hote='localhost';
	$PARAM_port='80';
	$PARAM_nom_bdd='bdd_escape_game';
	$PARAM_utilisateur='root';
	$PARAM_mot_passe='';

	$connexion = new PDO('mysql:host='.$PARAM_hote.';port='.$PARAM_port.';dbname='.$PARAM_nom_bdd, $PARAM_utilisateur, $PARAM_mot_passe);
	


?>