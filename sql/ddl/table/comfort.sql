
CREATE TABLE IF NOT EXISTS `tripdb`.`comfort` (
  `IdComfort` int unsigned NOT NULL AUTO_INCREMENT,
  `NomeComfort` varchar(45) NOT NULL,
  `DescrizioneComfort` varchar(1000) NOT NULL,
  PRIMARY KEY (`IdComfort`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
