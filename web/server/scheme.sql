CREATE DATABASE IF NOT EXISTS `test` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE test;

CREATE TABLE IF NOT EXISTS `accounts` (
  `id` int(20) NOT NULL AUTO_INCREMENT,
  `password` varchar(10) NOT NULL,
  `email` varchar(100) NOT NULL,
  `token` varchar(42),
  `create_date` date NOT NULL,
  `last_login` date,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

# debug account
INSERT INTO `accounts` (`id`, `password`, `email`, `create_date`) VALUES (1, 'test', 'test@test.com', '2024-01-06');
