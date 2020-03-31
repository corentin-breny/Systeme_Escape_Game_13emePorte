-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le: Mar 31 Mars 2020 à 12:12
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
  `Heure` datetime NOT NULL,
  PRIMARY KEY (`ID_actionneurs`),
  KEY `ID_mecanismes` (`ID_mecanismes`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Contenu de la table `actionneurs`
--

INSERT INTO `actionneurs` (`ID_actionneurs`, `ID_mecanismes`, `type`, `Etat`, `Heure`) VALUES
(1, 6, 'led', 1, '2020-03-24 20:51:52');

-- --------------------------------------------------------

--
-- Structure de la table `capteurs`
--

CREATE TABLE IF NOT EXISTS `capteurs` (
  `ID_capteurs` int(11) NOT NULL AUTO_INCREMENT,
  `ID_mecanismes` int(11) NOT NULL,
  `Type` text NOT NULL,
  `Etat` tinyint(1) NOT NULL,
  `Heure` datetime NOT NULL,
  PRIMARY KEY (`ID_capteurs`),
  KEY `ID_mecanismes` (`ID_mecanismes`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Contenu de la table `capteurs`
--

INSERT INTO `capteurs` (`ID_capteurs`, `ID_mecanismes`, `Type`, `Etat`, `Heure`) VALUES
(1, 6, 'Vanne', 1, '2020-03-24 20:51:09');

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
(6, 'L''échiquier', 0);

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
