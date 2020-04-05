-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le: Mar 31 Mars 2020 à 12:48
-- Version du serveur: 5.5.24-log
-- Version de PHP: 5.4.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `bdd_escape_game`
--

-- --------------------------------------------------------

--
-- Structure de la table `actionneurs`
--

CREATE TABLE IF NOT EXISTS `actionneurs` (
  `ID_actionneurs` int(11) NOT NULL AUTO_INCREMENT,
  `ID_mecanismes` int(11) NOT NULL,
  `type` text NOT NULL,
  `Etat` tinyint(1) NOT NULL,
  `Valeur_numerique` int(5) NOT NULL,
  `Heure_derniere_mesure` datetime NOT NULL,
  PRIMARY KEY (`ID_actionneurs`),
  KEY `ID_mecanismes` (`ID_mecanismes`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Contenu de la table `actionneurs`
--

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(1, 1, 'led rouge', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(2, 2, 'led rouge', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(3, 3, 'led rouge', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(4, 3, 'led verte', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(5, 4, 'led rouge', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(6, 4, 'led verte', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(7, 5, 'led verte', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(8, 6, 'led rouge', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(9, 6, 'led verte', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(10, 7, 'led rouge', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(11, 8, 'led rouge', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(12, 9, 'led verte', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(13, 9, 'led verte', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(14, 9, 'led verte', 1, 0, '2020-03-24 20:51:52');

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Valeur_numerique`, `Heure_derniere_mesure`) VALUES
(15, 9, 'led verte', 1, 0, '2020-03-24 20:51:52');

-- --------------------------------------------------------

--
-- Structure de la table `capteurs`
--

CREATE TABLE IF NOT EXISTS `capteurs` (
  `ID_capteurs` int(11) NOT NULL AUTO_INCREMENT,
  `ID_mecanismes` int(11) NOT NULL,
  `Type` text NOT NULL,
  `Etat` tinyint(1) NOT NULL,
  `Heure_derniere_mesure` datetime NOT NULL,
  PRIMARY KEY (`ID_capteurs`),
  KEY `ID_mecanismes` (`ID_mecanismes`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Contenu de la table `capteurs`
--

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(1, 1, 'Plateau', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(2, 1, 'Plateau', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(3, 2, 'Hall', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(4, 3, 'Hall', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(5, 4, 'Cle', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(6, 4, 'Trappe', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(7, 4, 'Fumee', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(8, 5, 'Humidite', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(9, 5, 'Fontaine', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(10, 5, 'Frigo', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(11, 6, 'Vanne', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(12, 6, 'Vanne', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(13, 6, 'Vanne', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(14, 6, 'Vanne', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(15, 6, 'Vanne', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(16, 6, 'Vanne', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(17, 6, 'Vanne', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(18, 7, 'Course', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(19, 8, 'Poids', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(20, 8, 'Tableau', 1, '2020-03-24 20:51:09');

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure_derniere_mesure`) VALUES
(21, 9, 'Poussoir', 1, '2020-03-24 20:51:09');

-- --------------------------------------------------------

--
-- Structure de la table `general`
--

CREATE TABLE IF NOT EXISTS `general` (
  `ID_mecanismes` int(11) NOT NULL AUTO_INCREMENT,
  `Nom_mecanisme` text NOT NULL,
  `Etat` tinyint(1) NOT NULL,
  PRIMARY KEY (`ID_mecanismes`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Contenu de la table `general`
--

INSERT INTO `general` (`ID_mecanismes`, `Nom_mecanisme`, `Etat`) VALUES
(6, 'Echiquier', 0);

INSERT INTO `general` (`ID_mecanismes`, `Nom_mecanisme`, `Etat`) VALUES
(6, 'Le Lion', 0);

INSERT INTO `general` (`ID_mecanismes`, `Nom_mecanisme`, `Etat`) VALUES
(6, 'Terre', 0);

INSERT INTO `general` (`ID_mecanismes`, `Nom_mecanisme`, `Etat`) VALUES
(6, 'Feu', 0);

INSERT INTO `general` (`ID_mecanismes`, `Nom_mecanisme`, `Etat`) VALUES
(6, 'Eau', 0);

INSERT INTO `general` (`ID_mecanismes`, `Nom_mecanisme`, `Etat`) VALUES
(6, 'Air', 0);

INSERT INTO `general` (`ID_mecanismes`, `Nom_mecanisme`, `Etat`) VALUES
(6, 'Katana', 0);

INSERT INTO `general` (`ID_mecanismes`, `Nom_mecanisme`, `Etat`) VALUES
(6, 'Riz', 0);

INSERT INTO `general` (`ID_mecanismes`, `Nom_mecanisme`, `Etat`) VALUES
(6, 'Quatre Elements', 0);
--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `actionneurs`
--
ALTER TABLE `actionneurs`
  ADD CONSTRAINT `actionneurs_ibfk_3` FOREIGN KEY (`ID_mecanismes`) REFERENCES `general` (`ID_mecanismes`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Contraintes pour la table `capteurs`
--
ALTER TABLE `capteurs`
  ADD CONSTRAINT `capteurs_ibfk_1` FOREIGN KEY (`ID_mecanismes`) REFERENCES `general` (`ID_mecanismes`) ON DELETE NO ACTION ON UPDATE NO ACTION;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
