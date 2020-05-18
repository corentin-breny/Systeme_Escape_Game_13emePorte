-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Client :  127.0.0.1
-- Généré le :  Lun 18 Mai 2020 à 02:24
-- Version du serveur :  5.6.17
-- Version de PHP :  5.5.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données :  `bdd_escape_game`
--

-- --------------------------------------------------------

--
-- Structure de la table `actionneurs`
--

CREATE TABLE IF NOT EXISTS `actionneurs` (
  `ID_actionneurs` int(11) NOT NULL AUTO_INCREMENT,
  `ID_mecanismes` int(11) NOT NULL,
  `Numero_Salle` int(1) NOT NULL,
  `type` text NOT NULL,
  `Etat` enum('TRUE','FALSE') NOT NULL,
  `Heure_derniere_mesure` datetime NOT NULL,
  PRIMARY KEY (`ID_actionneurs`),
  KEY `ID_mecanismes` (`ID_mecanismes`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=16 ;

--
-- Contenu de la table `actionneurs`
--

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `Numero_Salle`, `type`, `Etat`, `Heure_derniere_mesure`) VALUES
(1, 1, 1, 'led rouge', 'TRUE', '2020-03-24 20:51:52'),
(2, 2, 1, 'led rouge', 'TRUE', '2020-03-24 20:51:52'),
(3, 3, 1, 'led rouge', 'TRUE', '2020-03-24 20:51:52'),
(4, 3, 1, 'led verte', 'TRUE', '2020-03-24 20:51:52'),
(5, 4, 1, 'led rouge', 'TRUE', '2020-03-24 20:51:52'),
(6, 4, 1, 'led verte', 'TRUE', '2020-03-24 20:51:52'),
(7, 5, 1, 'led verte', 'TRUE', '2020-03-24 20:51:52'),
(8, 6, 1, 'led rouge', 'TRUE', '2020-03-24 20:51:52'),
(9, 6, 1, 'led verte', 'TRUE', '2020-03-24 20:51:52'),
(10, 7, 1, 'led rouge', 'TRUE', '2020-03-24 20:51:52'),
(11, 8, 1, 'led rouge', 'TRUE', '2020-03-24 20:51:52'),
(12, 9, 1, 'led verte', 'TRUE', '2020-03-24 20:51:52'),
(13, 9, 1, 'led verte', 'TRUE', '2020-03-24 20:51:52'),
(14, 9, 1, 'led verte', 'TRUE', '2020-03-24 20:51:52'),
(15, 9, 1, 'led verte', 'TRUE', '2020-03-24 20:51:52');

-- --------------------------------------------------------

--
-- Structure de la table `capteurs`
--

CREATE TABLE IF NOT EXISTS `capteurs` (
  `ID_capteurs` int(11) NOT NULL AUTO_INCREMENT,
  `ID_mecanismes` int(11) NOT NULL,
  `Numero_Salle` int(1) NOT NULL,
  `Type` text NOT NULL,
  `Valeur` int(11) NOT NULL,
  `Heure_derniere_mesure` datetime NOT NULL,
  PRIMARY KEY (`ID_capteurs`),
  KEY `ID_mecanismes` (`ID_mecanismes`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=23 ;

--
-- Contenu de la table `capteurs`
--

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Numero_Salle`, `Type`, `Valeur`, `Heure_derniere_mesure`) VALUES
(1, 1, 1, 'Plateau', 0, '2020-03-24 20:51:09'),
(2, 1, 1, 'Plateau', 0, '2020-03-24 20:51:09'),
(3, 2, 1, 'Hall', 0, '2020-03-24 20:51:09'),
(4, 3, 1, 'Hall', 0, '2020-03-24 20:51:09'),
(5, 4, 1, 'Cle', 0, '2020-03-24 20:51:09'),
(6, 4, 1, 'Trappe', 0, '2020-03-24 20:51:09'),
(7, 4, 1, 'Fumee', 0, '2020-03-24 20:51:09'),
(8, 5, 1, 'Humidite', 0, '2020-03-24 20:51:09'),
(9, 5, 1, 'Fontaine', 0, '2020-03-24 20:51:09'),
(10, 5, 1, 'Frigo', 0, '2020-03-24 20:51:09'),
(11, 6, 1, 'Vanne', 0, '2020-03-24 20:51:09'),
(12, 6, 1, 'Vanne', 0, '2020-03-24 20:51:09'),
(13, 6, 1, 'Vanne', 0, '2020-03-24 20:51:09'),
(14, 6, 1, 'Vanne', 0, '2020-03-24 20:51:09'),
(15, 6, 1, 'Vanne', 0, '2020-03-24 20:51:09'),
(16, 6, 1, 'Vanne', 0, '2020-03-24 20:51:09'),
(17, 6, 1, 'Vanne', 0, '2020-03-24 20:51:09'),
(18, 7, 1, 'Chien', 0, '2020-03-24 20:51:09'),
(19, 7, 1, 'Course', 0, '2020-03-24 20:51:09'),
(20, 8, 1, 'Poids', 0, '2020-03-24 20:51:09'),
(21, 8, 1, 'Tableau', 0, '2020-03-24 20:51:09'),
(22, 9, 1, 'Poussoir', 0, '2020-03-24 20:51:09');

-- --------------------------------------------------------

--
-- Structure de la table `general`
--

CREATE TABLE IF NOT EXISTS `general` (
  `ID_mecanismes` int(11) NOT NULL AUTO_INCREMENT,
  `Numero_Salle` int(1) NOT NULL,
  `Nom_mecanisme` text NOT NULL,
  `Etat` enum('TRUE','FALSE') NOT NULL,
  PRIMARY KEY (`ID_mecanismes`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=10 ;

--
-- Contenu de la table `general`
--

INSERT INTO `general` (`ID_mecanismes`, `Numero_Salle`, `Nom_mecanisme`, `Etat`) VALUES
(1, 1, 'Echiquier', ''),
(2, 1, 'Le Lion', 'TRUE'),
(3, 1, 'Terre', 'TRUE'),
(4, 1, 'Feu', 'TRUE'),
(5, 1, 'Eau', 'TRUE'),
(6, 1, 'Air', 'TRUE'),
(7, 1, 'Katana', 'TRUE'),
(8, 1, 'Riz', 'TRUE'),
(9, 1, 'Quatre Elements', 'TRUE');

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
