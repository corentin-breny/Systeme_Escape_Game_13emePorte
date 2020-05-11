<?php include("connexion1.php"); ?>

<html lang="fr">
<head>
  <meta charset="utf-8">
  <title>13ème Porte Application WEB</title>
  <link rel="stylesheet" href="style2.css">
</head>
<body>


<?php 

	$query1=("SELECT*FROM capteurs");
	$resultatsCapt=$dbh->query($query1);
	$resultatsCapt->setFetchMode(PDO::FETCH_OBJ);
?>


<?php	
	$query2=("SELECT*FROM actionneurs");
	$resultatsAct=$dbh->query($query2);
	$resultatsAct->setFetchMode(PDO::FETCH_OBJ);
?>	
	
	
<?php	
	$query3=("SELECT*FROM general");
	$resultatsMeca=$dbh->query($query3);
	$resultatsMeca->setFetchMode(PDO::FETCH_OBJ);
?>

	<div class="center">
	<hr color="white">
	<img class="image" src="photo.png"/>
	<br/>
	<h1>Application WEB</h1>
	<br/>
	<hr color="white">
	</div>
	
	<div class="Fond">
	<img class="imgFond" src="Photo6.jpg"/>
	</div>
	
	
	<div class="Devant">
	
<?php

	while($mecanismes = $resultatsMeca->fetch())
	{
		$mecanisme = utf8_encode($mecanismes->ID_mecanismes);
		$Etat = utf8_encode($mecanismes->Etat);

		if($mecanisme==1)
		{
			if($Etat==TRUE)
			{
				?>
				<div class="carré1">
				<img class="mecanisme" src="Echec.png"/>
				</div>
				<?php			
			}
			elseif($Etat==FALSE)
			{
				?>
				<div class="carré1.1">
				<img class="mecanisme" src="Echec.png"/>
				</div>
				<?php
			}
		}
		
		if($mecanisme==2)
		{
			if($Etat==TRUE)
			{
				?>
				<div class="carré2">
				<img class="mecanisme" src="Lion.png"/>
				</div>
				<?php			
			}
			elseif($Etat==FALSE)
			{
				?>
				<div class="carré2.1">
				<img class="mecanisme" src="Lion.png"/>
				</div>
				<?php
			}
		}
		
		if($mecanisme==3)
		{
			if($Etat==TRUE)
			{
				?>
				<div class="carré3">
				<img class="mecanisme" src="Terre.png"/>
				</div>
				<?php			
			}
			elseif($Etat==FALSE)
			{
				?>
				<div class="carré3.1">
				<img class="mecanisme" src="Terre.png"/>
				</div>
				<?php
			}
		}
		
		if($mecanisme==4)
		{
			if($Etat==TRUE)
			{
			?>
				<div class="carré4">
				<img class="mecanisme" src="Feu.png"/>
				</div>
			<?php			
			}
			elseif($Etat==FALSE)
			{
			?>
				<div class="carré4.1">
				<img class="mecanisme" src="Feu.png"/>
				</div>
			<?php
			}
		}
		
		if($mecanisme==5)
		{
			if($Etat==TRUE)
			{
			?>
				<div class="carré5">
				<img class="mecanisme" src="Eau.png"/>
				</div>
			<?php			
			}
			elseif($Etat==FALSE)
			{
			?>
				<div class="carré5.1">
				<img class="mecanisme" src="Eau.png"/>
				</div>
			<?php
			}
		}
		
		if($mecanisme==6)
		{
			if($Etat==TRUE)
			{
			?>
				<div class="carré6">
				<img class="mecanisme" src="Air.png"/>
				</div>
			<?php			
			}
			elseif($Etat==FALSE)
			{
			?>
				<div class="carré6.1">
				<img class="mecanisme" src="Air.png"/>
				</div>
			<?php
			}
		}
		
		if($mecanisme==7)
		{
			if($Etat==TRUE)
			{
			?>
				<div class="carré7">
				<img class="mecanisme" src="Katana.png"/>
				</div>
			<?php			
			}
			elseif($Etat==FALSE)
			{
			?>
				<div class="carré7.1">
				<img class="mecanisme" src="Katana.png"/>
				</div>
			<?php
			}
		}
	
		if($mecanisme==8)
		{
			if($Etat==TRUE)
			{
			?>
				<div class="carré8">
				<img class="mecanisme" src="Riz.png"/>
				</div>
			<?php			
			}
			elseif($Etat==FALSE)
			{
			?>
				<div class="carré8.1">
				<img class="mecanisme" src="Riz.png"/>
				</div>
			<?php
			}
		}
	
		if($mecanisme==9)
		{
			if($Etat==TRUE)
			{
			?>
				<div class="carré9">
				<img class="mecanisme" src="QuatreEle.png"/>
				</div>
			<?php			
			}
			elseif($Etat==FALSE)
			{
			?>
				<div class="carré9.1">
				<img class="mecanisme" src="QuatreEle.png"/>
				</div>
			<?php
			}
		}
	
	}

?>	
	</div>
	
	<div class="Devant">

<?php

	while($capteurs = $resultatsCapt->fetch())
	{	
		$capteur = utf8_encode($capteurs->ID_capteurs);
		$etat = utf8_encode($capteurs->Etat);
		$dateMesure = utf8_encode($capteurs->Heure_derniere_mesure);
		
		if($capteur==1)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca1">
				<img class="mecanisme" src="Plateau.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca1.1">
				<img class="mecanisme" src="Plateau.png"/>
				</div>
			<?php
			}
		}
		
		if($capteur==2)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca2">
				<img class="mecanisme" src="Plateau.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca2.1">
				<img class="mecanisme" src="Plateau.png"/>
				</div>
			<?php
			}
		}
		
		
		if($capteur==3)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca4">
				<img class="mecanisme" src="Hall.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca4.1">
				<img class="mecanisme" src="Hall.png"/>
				</div>
			<?php
			}
		}
		if($capteur==4)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca6">
				<img class="mecanisme" src="Hall.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca6.1">
				<img class="mecanisme" src="Hall.png"/>
				</div>
			<?php
			}
		}
	
		if($capteur==5)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca9">
				<img class="mecanisme" src="Cle.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca9.1">
				<img class="mecanisme" src="Cle.png"/>
				</div>
			<?php
			}
		}
		
		if($capteur==6)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca10">
				<img class="mecanisme" src="Trappe.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca10.1">
				<img class="mecanisme" src="Trappe.png"/>
				</div>
			<?php
			}
		}
	
		if($capteur==7)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca11">
				<img class="mecanisme" src="Fumee.png"/>
				</div>
			<?php			
			}	
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca11.1">
				<img class="mecanisme" src="Fumee.png"/>
				</div>
			<?php
			}
		}
	
		if($capteur==8)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca14">
				<img class="mecanisme" src="Humidite.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca14.1">
				<img class="mecanisme" src="Humidite.png"/>
				</div>
			<?php
			}
		}
		
		if($capteur==9)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca15">
				<img class="mecanisme" src="Fontaine.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca15.1">
				<img class="mecanisme" src="Fontaine.png"/>
				</div>
			<?php
			}
		}

		if($capteur==10)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca16">
				<img class="mecanisme" src="Frigo.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca16.1">
				<img class="mecanisme" src="Frigo.png"/>
				</div>
			<?php
			}
		}

		if($capteur==11)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca18">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca18.1">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php
			}
		}
		
		if($capteur==12)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca19">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca19.1">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php
			}
		}

		if($capteur==13)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca20">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca20.1">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php
			}
		}
		
		if($capteur==14)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca21">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca21.1">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php
			}
		}
		 
		if($capteur==15)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca22.1">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca22">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php
			}
		}

		if($capteur==16)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca23.1">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca23">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php
			}
		}
		
		if($capteur==17)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca24">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca24.1">
				<img class="mecanisme" src="Valve.png"/>
				</div>
			<?php
			}
		}

		if($capteur==18)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca25">
				<img class="mecanisme" src="Chien.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca25.1">
				<img class="mecanisme" src="Chien.png"/>
				</div>
			<?php
			}
		}

		if($capteur==19)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca28">
				<img class="mecanisme" src="Course.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca28.1">
				<img class="mecanisme" src="Course.png"/>
				</div>
			<?php
			}
		}
		
		if($capteur==20)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca30">
				<img class="mecanisme" src="Poids.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca30.1">
				<img class="mecanisme" src="Poids.png"/>
				</div>
			<?php
			}
		}

		if($capteur==21)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca31">
				<img class="mecanisme" src="Tableau.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca31.1">
				<img class="mecanisme" src="Tableau.png"/>
				</div>
			<?php
			}
		}

		if($capteur==22)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca33">
				<img class="mecanisme" src="Poussoir.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca33.1">
				<img class="mecanisme" src="Poussoir.png"/>
				</div>
			<?php
			}
		}
	}
	
?>
	</div>

	<div class="Devant">

<?php
	
	while($actionneurs = $resultatsAct->fetch())
	{
		$actionneur	= utf8_encode($actionneurs->ID_actionneurs);
		$etat = utf8_encode($actionneurs->Etat);
		$dateMesure = utf8_encode($actionneurs->Heure_derniere_mesure);
	
		if($actionneur==1)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca3">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca3.1">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php
			}
		}
		
		if($actionneur==2)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca5">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca5.1">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php
			}
		}

		if($actionneur==3)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca7">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca7.1">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php
			}
		}

		if($actionneur==4)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca8">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca8.1">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php
			}
		}
		
		if($actionneur==5)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca12">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca12.1">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php
			}
		}

		if($actionneur==6)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca13">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca13.1">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php
			}
		}

		if($actionneur==7)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca17">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca17.1">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php
			}
		}

		if($actionneur==8)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca26">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca26.1">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php
			}
		}

		if($actionneur==9)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca27">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca27.1">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php
			}
		}
		
		if($actionneur==10)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca29">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca29.1">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php
			}
		}

		if($actionneur==11)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca32">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca32.1">
				<img class="mecanisme" src="LedRouge.png"/>
				</div>
			<?php
			}
		}

		if($actionneur==12)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca34">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca34.1">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php
			}
		}
		
		if($actionneur==13)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca35">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca35.1">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php
			}
		}

		if($actionneur==14)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca36">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca36.1">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php
			}
		}
	
		if($actionneur==15)
		{
			if($etat==TRUE)
			{
			?>
				<div class="carréMeca37">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php			
			}
			elseif($etat==FALSE)
			{
			?>
				<div class="carréMeca37.1">
				<img class="mecanisme" src="LedVerte.png"/>
				</div>
			<?php
			}
		}
	}	
?>	
	</div>

</body>
</html>