CREATE DATABASE  IF NOT EXISTS `parkadmin` /*!40100 DEFAULT CHARACTER SET gb2312 */;
USE `parkadmin`;
-- MySQL dump 10.13  Distrib 5.5.16, for Win32 (x86)
--
-- Host: localhost    Database: parkadmin
-- ------------------------------------------------------
-- Server version	5.5.21

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `zkset`
--

DROP TABLE IF EXISTS `zkset`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `zkset` (
  `zkindex` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `zkname` varchar(45) NOT NULL DEFAULT 'Êú™Áü•',
  `zkflag` varchar(45) NOT NULL DEFAULT 'Êú™Áü•',
  `zkdetail` varchar(90) DEFAULT NULL,
  `zknumb` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`zkindex`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `zkset`
--

LOCK TABLES `zkset` WRITE;
/*!40000 ALTER TABLE `zkset` DISABLE KEYS */;
/*!40000 ALTER TABLE `zkset` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `parkdongleinfo`
--

DROP TABLE IF EXISTS `parkdongleinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `parkdongleinfo` (
  `AdministrativeID` varchar(50) NOT NULL,
  `BriefName` varchar(256) NOT NULL,
  `DongleHID` varbinary(2048) DEFAULT NULL,
  PRIMARY KEY (`AdministrativeID`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `parkdongleinfo`
--

LOCK TABLES `parkdongleinfo` WRITE;
/*!40000 ALTER TABLE `parkdongleinfo` DISABLE KEYS */;
INSERT INTO `parkdongleinfo` VALUES ('5101040001','ÂõõÂ∑ùÁúÅËÇøÁò§ÂåªÈô¢',' J\\iWÂ{Ë°\Z’±ÉÓ[òz!]¥ÀY1A¢∞{„7ˆ/JlïV}jÈûtg«€Z\\íì•}ÚlrÜv˙a–Ä≤Yó*péoâRWî„ºn¯Îd˙πëÚËç2Ò˛>∆ìπ-´–í£+˙p_¬¿ç◊J$f∏W`XöÖgw@ÿqNZàú?9≈çú^ﬂ––1Ø∞Î`Mî%¨uè∂Uà$H'),('5101070001','ÂâçÈÄîÈ´òÁßëÊµãËØï','\Z5]wgiQÄyøæ#e,<^ëÍäãøπñ·Ò≈≤#4,Õ∞0Ù,ù∫'),('5101070002','ÊàêÈÉΩÊ≠¶‰æØÂå∫ÈïøÂØøËãë','/y˛àÈ+\nöÓØSÖÙ±>,WèÉò\né÷˘é9°5˜A≈S¯foµ“aT0AN\'ısî\'*µÀπNËè.v	Î„Åˇ35q·Î*¯Ÿ∫áeqPõä=˝MæG„mê@œZà\04jMÕiªj‚îıYÏXaæƒÈGàÙ7ØD‹»¬`a ∏÷∞\'&ã8&;ı¿ô\nˆcáÎRe\r—ïg\rƒY}S'),('5101810001','ÈùíÂüéÂ±±ÈÉΩÊ±üÂ†∞ÊôØÂå∫','2Œ Ñ∞]F^§WtG≈»vë4_\r~dt˜Âp‘]eï8p.>\0\n¿[8.X¯XÏ«2±„≠⁄8:≤‰cä>N∑~S)¨ÉÃ$œ⁄Ú”™º8,÷$Ìc˜}f•\Zf4∆O‹ºÏV ≠‹Ÿˇı±°…√r)˝váDéæπB¶»´ùƒM^∆&©[ lr!Ó˝8†pﬂ¬Ã√ÍlêC·b‹»YA—<Àá±.≈#.√ˇkwU“óÿ¡◊çÏÀ'),('5115020001','‰∫îÁ≤ÆÊ∂≤ÈõÜÂõ¢Á£ÖÊàø','/y˛àÈ+\nöÓØSÖÙ±Ø89–àõ\'∑{yìÏBm≤#4,Õ∞0Ù,ù∫'),('5118020001','ÈõÖÂÆâÊ∏ÖÊ±üËä±Âõ≠','/y˛àÈ+\nöÓØSÖÙ±ÏŒB\0vTÁ∑x@ÜxG/');
/*!40000 ALTER TABLE `parkdongleinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `license`
--

DROP TABLE IF EXISTS `license`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `license` (
  `AdministrativeID` varchar(50) NOT NULL COMMENT '(Âå∫Âè∑) + ÂÅúËΩ¶Âú∫ÁºñÂè∑\n\n510107 + 0001\n\n510107 + 9999',
  `KeyContent` blob,
  PRIMARY KEY (`AdministrativeID`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `license`
--

LOCK TABLES `license` WRITE;
/*!40000 ALTER TABLE `license` DISABLE KEYS */;
INSERT INTO `license` VALUES ('5101040001','UE1TWuY2dBvFzgp4xxrpwF5ja0kLFWiDCSqgaclMhGNTDDdIJ7Zra/tWvdA7Xmc64R/hqiDyvbx38F0Lippnbi23K73fmEhXgy8e+uqkiraG8LrHsxqolXFLEqOQNnNWFdxiXy7PKRsRsfnu54VDCkGC2BO9b/e7LQquOLu7s16sXfTBPl8K20WOar1+I8PslKPb2uyc1iDw2C1/uE7HDofM5AtuijH9Whun3fESXhHjEKx/8AWzVzuhANsSrXHMtO0eIx8/74DQgHkzVZmPJZJoBARHHMCJrxPx9rG6nynHXbImKG2TzbneF+4tczFPhFbKLigAin2EPPjy5gyxuO/Yfu4LtNswtRffJU/4m7IVX0WMOtnUASVoED3JB9aLTBf6eazXLoa2rgdohnV61837mKX3ovuqJPlagHwFtdiYjs5IaVXP5qWe335/3nGvu1S/7QEYKf3IjY74TGQ6nRRnyZ1wEO/h+REtL6eWBp6NESM8R34MF3j/Uqxt1T/kfWQcJMP464NbHTDKmnBUiwYkcloU6cRs1KdUm/ASAU29qsVCG1c7SkO/ySbJi6n6lgGFF9tgRBGyNg5PD3xdV36GGcILRDRdZBOWeSx01cYngiBJzV2w1Ek3cqLt193ZwH9ACEa+OsIM/l4i5tTx1BpE1gvcXMsAIL0AXMLLuZdqJmjcoqP/cRlaRu2olQ4NUaO2HlGaNu35Tx2t6ldIgZar+wSxTYEGnpYUGOrL2gCraJLEwq55k115hRK0Q6xfRONDTJuINWiXzr8HaY6YBleoYwhBtbXWj4jwxnav66kJVqYK/b7jICTIJM8a037uPIe+SqmucHq1gDVpBCfjGOHZVdsizrkZMme6nWv9+U1A8X5zlTIx0jsRTsBkNbbPF1MNrxPqJcGcfxo5fDiy5EMOA+zLDwqgIXQCqqKsqzShuyTVuQl2sCCDBONkkVhjY5+cLmLz1HKuLb/Xc+VTwTI5IS4xPqyrMgu+pbrBpPdH1krwcKryN1/yg/fCPYKjso6PZ4rPUzLHWbhS80UR8c8uJgGI+ZVog8jlxg=='),('5101070001','UE1TWuY2dBvFzgp4xxrpwF5ja0kLFWiDCSqganFX6WA9UsOD+fIv2RKQzcXpNcxJXK6Zhy6bkRiApYklIy1YaqDxqZdxltQKj1yFrSikJLOFZUrIUVuCGAHtGcEXP19Pcr4IRfPxUn/yvJP+sK9SYnLRvgbv2yP3vI4Adpnw0C53ZPR4Xru+8jvPsUh5ypAFitGwNM98Z4LQ/GQdl7thPnH7t8pIeUlxEXl8yv0TMEN85H2TyZnp3p6h2Ol3V5OltGGpICd/Sy7oCc2m1lu69Qf7WbUM0sFO1QwaqeS2LtjJcZi0NH1y51f5YMFuhDyouMhEhlk0eXGbJSMD+B18lPpuOhYFkWpzETd+MmyBw5bSUhJwOEddpKVH8wOymCiHdukrZdwdr27roQp+BM2Vbu3fQ27aHCotac/tpPKMPW0n74mP4PpuV/UeD6kF3VzLPe1TY5bF7iS9Zgej3WCkJSiDuUenLur5Vh7gt+aj3IgYS7At9xoM8uodfmZ/7YWMZy18P6ccUFAmgRHDpLHcIJVakl8aQ0/dRS5cQ+rIAAGtWGiivQmMPbj9IxqZ0N5OT+MWDPRYOBw19saeRcqnt0Iuki5AnWAZNIW5PQWfnxdC4HMpe8KWFJG5EebZ94CyEfZjXsE8D3gmssLuugN0n0aFyeiT8v1MMIkzcHC8hGmBQnkU5vIxegqCoIZGr6DRZm568QYiCw3YvMtaWL7QeYZGep4='),('5101070002','UE1TWuY2dBvFzgp4xxrpwF5ja0kLFWiDCSqganFX6WM9UsODnWPjuu3TDuRB56I0bm8RsdWbYrF95MbpuYop1y2jM7KrOlSM24rumT+vIMC/qbOaQg1LfD7E2AFsQLz74sXzjbkmLrwYchvvhfo25d3866UBB1WAgCQq0XQsM4KDH5E8K6LUb4e3U1uY4jOeLDLMrsgL1VznUR5TisfVgyA+Wk8/pmBSq7amnwT+O3yzo/4vnpDjEfigu82KvRB/cJIqbxmUPHhEY3fpi3+gbaeg6v6N6YlGqmbsh01oap8eG3GEAzUJer6MKtNT3Evbd+wBz5exVaoOSHQFtv0xehDxmT7ITpvzlEZtxt9IWbC6WKw8AHDHPBcYhzY7zSN75pyEozsDdOFhh7g4cWepWnnX2ux/a+ziZnMQkt0SW2NPSSzgAJu6OwZVCUGpk+aP+4g3EkZSRqziE0W/LU2VyoKhgVlbCqITz+HpWG4GVdONkvo580gxkI9g+AgSyHgW1sIlwct5W0Twiu9Fgmlp3S34B9o6KpLCRvjFZMerYDRuG/vhOo7kjoqpsKB89qdNV/oIw1SBb02cZYXnMVbAUbYiezMcJXGRMHTSAQYKhjUXRWZmy5JZnmPm0qgLdJfq1tsXgH9cqgc+3t3p2xm6bvciRVmwq28h4s1fWtA3tWlqJXImZsnFe/kkGRpOtcuod4A+HjMjb1HnvH0c/DmAqHClNAOROSzaDrN8YmFko1hjhvcM5yEFEqPJO1RunFInRZQ3xwnLDYYGH5IImrIhQ8EtXZEk76w4OJc+a4ChCkF1GHitiuUMnjD3XWqYeC+AGiR+v8VCkLFMsxyL6WB/sbGQ57MUdCUmyieLD3ZJ8HbaC7U310SjcLvfEGfryVRSRN6prTcv4ooR9cR5qXskKYtdcnUZNhaPKPrcFnQZ+efB2Epkl3d8YxHSbeQ8rUW6F8HhjRUJEtXvOXJ4QCZsh2GWePOBWgIjFbd6uxSeWSmLvd6tSQ7v2lmdXdpD1WsIbhqU4yx7dX9KUxEtBdVT0iEfCaOPul8SHrYUTg=='),('5101810001','UE1TWuY2dBvFzgp4xxrpwF5ja0kLFWiDCSqobNmewWExJhRBAYmkKdOsr2MffMjg7FMYr4K/0/f42D+VG+PAN4w4pfvQyWCjFlzo0znrlhyxAi4Lzn552eqQDVaoVVAvD/hn/W7GFCYFAYpiEYKsEGStUSfzGAqdskUM8ks+N9rj/WgjuZJA4w5lBSvi3TnC5nqLtEWk9+wURFTAmnOHSyOZtVhEonO1UPUtqDXQWykETCmXVyuz9B1fFEIegDm2baYCoY1MrPMVJrwd2lcMiBe0wMPFOCyrB3wICiF6f7b8aY7V3FPVYsultGGB5vN8WclUW4+czx7FZLPEBUK9d1VkLaNrZeZWWBnRdhQr5VQLYnpBED20a8eiA3+AmfOT44TnP7BGTjoZx7ehtSZwDk3/3dYEF7I+sp/B3PVTE//kdxxB0Fwv7rdsr0fLElkIPdcjodWba+HafqqdDkdWWoyntYUqn2LS0INpWxhaXA2/wdL9yjHiv71ys9zlmVy0E/p6AzTmLsXAL7ZEYu1zJZRmF4Ev8h+uHlot5qVVR+PuDWVMG4WMok4TDMTffb/rHOW4b7wNbWgiP8sqyhz2Ii9vUI7RX8vTu7vQ6kbpnlNcD1ozuuoiqSda0uIp9nSZrowzVJ7n7K35IoR5ZaF425OyF5M15oGa95TudeAlz7pGeZO2Tjkf/v3TwziLKhAdThCUGzpDL47Hy7Z5DUqfAHqpGroB41kLbJbo6XUg0E22ZmqDxRTQTrocsQ9ZNvpUBSPAZ3rGzSjgN9TypRRml9d9yFe9PrBLaPt6owG+DJq6jI9Mg31mtle3dlZh+p0uAlKEsAUGZ9wpK4+T54u2o80fJtmjapu2i1Z1dN9BzaY4/X5I/OZnn1dg7z2rGh7aI7V6+FPDki2Fl12ASAKY5KU1yl1qMRGkaPdu5lTCgieoty+50BltCOLf132bhpweBYi+G8yh3qg3JmDy/AtmSmwkCZSnlZBOf3VpExjTKkInORik1JCEI7lQzZ4mSsS0p1Zv2yF4p8gd52gHwSimHOOhpu6JCrRytP6iOiGrnlheO8o1KNkfAlGwykxbCC2daCAQQV6W540KMWJUJzcYhuN6bClfueeJpPvMr8u8Q3j5so+MBB5ZNHo1pzxZdci4xgB02sJ4dkK719cNNuCfMA2eTXyoK00Ekdb5GFcZKMK4S6xHz7a+hwQRpDThInYmZf2/SlGFke2YlJ8U+rtTaf0Ilq91GDzH51rJ0NYwUbbi9fNN3hh+gLQjidx8ehOiHYGOPw=='),('5115020001','UE1TWuY2dBvFzgp4xxrpwF5ja0kLFWiDCC6gb6MIT+KQXiCkEnJiGhVzk4fmqww9kt5mbWE95UL2A+yH8RLwxiRNUTQnxAXiy5bHPJIOQC6+uJWJwTKOtdLBn1Mzu3mteNOtROm1LBi7kgoybAdFHDp/nepMzHQGAfJ0ZlBuQsogaXzV6X0D4OPeImo='),('5118020001','UE1TWuY2dBvFzgp4xxrpwF5ja0kLFWiDCCOgby4xQ4KLoXFcGxHCgwVZMQWBtzKS//tBGwUX3yyFa4d+Mp+nbOhhS2HGrTb61P5OMKYqViaaV48KkWofN5cWaHl1BpheWVRvFnJeO/hExvZG9ZtTrBPW9grHaPxdZPAzJl3h019/bqnRPLRfauA1Zhh/isoI4/10BixV+gj04Gr7VLwzIZPL4lAgQ/CcGIiyDijMQXeEBmm5yG9A2GYXaAd8+5wbEBqBt2a83ymw9d/MapNLngB4N6JK5CDsWo0/zg==');
/*!40000 ALTER TABLE `license` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pmslog`
--

DROP TABLE IF EXISTS `pmslog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pmslog` (
  `MsgID` int(11) NOT NULL AUTO_INCREMENT,
  `MsgKind` varchar(45) DEFAULT NULL,
  `MsgText` varchar(10240) DEFAULT NULL,
  `MsgDateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`MsgID`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pmslog`
--

LOCK TABLES `pmslog` WRITE;
/*!40000 ALTER TABLE `pmslog` DISABLE KEYS */;
/*!40000 ALTER TABLE `pmslog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmpcard`
--

DROP TABLE IF EXISTS `tmpcard`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmpcard` (
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `cardkind` varchar(50) DEFAULT 'EMIDÂç°',
  `cardfeebz` varchar(30) NOT NULL DEFAULT 'Áé∞Âú∫ÈÄâÊã©',
  `cardselfno` varchar(50) DEFAULT NULL,
  `cardstate` varchar(30) NOT NULL DEFAULT 'ÂêØÁî®',
  `Inside` int(10) DEFAULT '0',
  `EnterMustCard` int(10) DEFAULT '0',
  `LeaveMustCard` int(10) DEFAULT '0',
  PRIMARY KEY (`cardno`),
  KEY `cardselfno` (`cardselfno`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmpcard`
--

LOCK TABLES `tmpcard` WRITE;
/*!40000 ALTER TABLE `tmpcard` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmpcard` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`tmpcard_ai`
AFTER INSERT ON `parkadmin`.`tmpcard`
FOR EACH ROW
BEGIN
DECLARE a,b INT;
DECLARE ai char(30);
DECLARE cur_1 CURSOR FOR SELECT shebeiid FROM roadconerinfo;
DECLARE cur_2 CURSOR FOR SELECT shebeiname FROM roadconerinfo;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET b = 1;
OPEN cur_1;
OPEN cur_2;
set b = 0;
while b<>1 do
FETCH cur_1 INTO a;
FETCH cur_2 INTO ai;
if b<>1 then
insert into cardright(cardno,roadconind,shebeiname) values(NEW.cardno,a,ai);
end if;
END while;
CLOSE cur_1;
CLOSE cur_2;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`tmpcard_au`
AFTER UPDATE ON `parkadmin`.`tmpcard`
FOR EACH ROW
BEGIN
if new.cardno<>old.cardno then
update cardright set cardright.cardno=new.cardno where cardright.cardno=old.cardno;
update stoprd set stoprd.cardno=new.cardno where stoprd.cardno=old.cardno;
end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`tmpcard_ad`
AFTER DELETE ON `parkadmin`.`tmpcard`
FOR EACH ROW
BEGIN
delete from cardright where cardright.cardno=OLD.cardno;
delete from stoprd where stoprd.cardno=OLD.cardno and stoprd.outtime is NULL;  
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `blacklist`
--

DROP TABLE IF EXISTS `blacklist`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `blacklist` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `plate` varchar(45) DEFAULT NULL,
  `kind` varchar(45) DEFAULT NULL,
  `color` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `ind_plate` (`plate`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312 COMMENT='ÈªëÂêçÂçï';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `blacklist`
--

LOCK TABLES `blacklist` WRITE;
/*!40000 ALTER TABLE `blacklist` DISABLE KEYS */;
/*!40000 ALTER TABLE `blacklist` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprd1`
--

DROP TABLE IF EXISTS `stoprd1`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprd1` (
  `stoprdid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `inshebeiname` varchar(30) DEFAULT NULL,
  `outshebeiname` varchar(30) DEFAULT NULL,
  `invideo1` longblob,
  `invideo2` longblob,
  `invideo3` longblob,
  `invideo4` longblob,
  `outvideo1` longblob,
  `outvideo2` longblob,
  `outvideo3` longblob,
  `outvideo4` longblob,
  `intime` datetime DEFAULT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  `username` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT 'Êó†‰ºòÊÉ†',
  `carcpout` varchar(30) DEFAULT 'Êú™Áü•',
  `MayDelete` tinyint(1) NOT NULL DEFAULT '0',
  `Transfered` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`stoprdid`),
  KEY `cardno_outtime_parkid` (`cardno`,`outtime`,`parkid`),
  KEY `outtime_parkid` (`outtime`,`parkid`),
  KEY `intime_cardno` (`intime`,`cardno`),
  KEY `inshebeiname` (`inshebeiname`),
  KEY `outshebeiname` (`outshebeiname`),
  KEY `cardno` (`cardno`),
  KEY `intime` (`intime`),
  KEY `outtime` (`outtime`),
  KEY `feetime` (`feetime`),
  KEY `feeoperator` (`feeoperator`),
  KEY `carcp` (`carcp`),
  KEY `username` (`username`),
  KEY `cardselfno` (`cardselfno`),
  KEY `cardkind` (`cardkind`),
  KEY `parkid` (`parkid`),
  KEY `feekind` (`feekind`),
  KEY `childrdindx` (`childrdindx`),
  KEY `cardkind_outtime_parkid` (`cardkind`,`outtime`,`parkid`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd1`
--

LOCK TABLES `stoprd1` WRITE;
/*!40000 ALTER TABLE `stoprd1` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd1` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `parkinfo`
--

DROP TABLE IF EXISTS `parkinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `parkinfo` (
  `parkindex` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `shebeiid` int(10) unsigned NOT NULL,
  `parknum` int(10) unsigned DEFAULT '88',
  `parkname` varchar(30) NOT NULL DEFAULT 'Êñ∞Âª∫ÂÅúËΩ¶Âú∫',
  `usedSpace` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`parkindex`),
  KEY `shebeiid` (`shebeiid`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `parkinfo`
--

LOCK TABLES `parkinfo` WRITE;
/*!40000 ALTER TABLE `parkinfo` DISABLE KEYS */;
INSERT INTO `parkinfo` VALUES (27,131,888,'***ÂÅúËΩ¶Âú∫',0);
/*!40000 ALTER TABLE `parkinfo` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`parkinfo_ai`
AFTER INSERT ON `parkadmin`.`parkinfo`
FOR EACH ROW
BEGIN
 
    update feeratebackup set RParkid=New.parkindex;
    insert into feerate(RParkid,RFeeModel,RTimeIndex,RSmTime,RBmTime,RMoney,RMoneyDw,RIncTime) select * from feeratebackup;
    insert into feerate1(RParkid,RFeeModel) values(New.parkindex,0);
    insert into feerate1(RParkid,RFeeModel) values(New.parkindex,1);
    insert into feerate1(RParkid,RFeeModel) values(New.parkindex,2);
    insert into feerate1(RParkid,RFeeModel) values(New.parkindex,3);
    insert into feerate1(RParkid,RFeeModel) values(New.parkindex,4);
    insert into feerate1(RParkid,RFeeModel) values(New.parkindex,5);
    insert into feerate1(RParkid,RFeeModel) values(New.parkindex,6);
    insert into feerate1(RParkid,RFeeModel) values(New.parkindex,7);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`parkinfo_au`
AFTER UPDATE ON `parkadmin`.`parkinfo`
FOR EACH ROW
BEGIN
if new.parkname<>old.parkname then 
update treeview set treeview.shebeiname=new.parkname where treeview.shebeiid=old.shebeiid;
end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`parkinfo_ad`
AFTER DELETE ON `parkadmin`.`parkinfo`
FOR EACH ROW
BEGIN
    delete from feerate where RParkid=Old.parkindex;
    delete from feerate1 where RParkid=Old.parkindex;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `cardright`
--

DROP TABLE IF EXISTS `cardright`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cardright` (
  `cardsetind` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `roadconind` int(10) unsigned NOT NULL,
  `starttime` time NOT NULL DEFAULT '00:00:00',
  `endtime` time NOT NULL DEFAULT '23:59:59',
  `shebeiname` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  PRIMARY KEY (`cardsetind`),
  KEY `roadconind` (`roadconind`),
  KEY `cardno_starttime_endtime` (`cardno`,`starttime`,`endtime`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cardright`
--

LOCK TABLES `cardright` WRITE;
/*!40000 ALTER TABLE `cardright` DISABLE KEYS */;
/*!40000 ALTER TABLE `cardright` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `feerd`
--

DROP TABLE IF EXISTS `feerd`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `feerd` (
  `feeindex` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `feenumb` int(10) unsigned NOT NULL,
  `feetime` datetime NOT NULL,
  `feekind` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  `feeoperator` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  `cardno` varchar(50) NOT NULL DEFAULT 'Êú™Áü•',
  `timelen` int(10) unsigned DEFAULT NULL,
  `Transfered` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`feeindex`),
  KEY `feetime` (`feetime`),
  KEY `cardno` (`cardno`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `feerd`
--

LOCK TABLES `feerd` WRITE;
/*!40000 ALTER TABLE `feerd` DISABLE KEYS */;
/*!40000 ALTER TABLE `feerd` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `operator`
--

DROP TABLE IF EXISTS `operator`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `operator` (
  `operatorid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `operatorname` varchar(50) NOT NULL DEFAULT 'Êú™Áü•',
  `operatorphone` varchar(50) DEFAULT NULL,
  `operatorsex` varchar(50) DEFAULT 'Áî∑',
  `operatoraddress` varchar(50) DEFAULT NULL,
  `operatorpassword` varchar(50) DEFAULT '123',
  `qxgl` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'ÊùÉÈôêÁÆ°ÁêÜ',
  `cardgl` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Âç°Á•®ÁÆ°ÁêÜ',
  `exitgl` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'ÈÄÄÂá∫Á≥ªÁªü',
  `datagl` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Êï∞ÊçÆÁª¥Êä§',
  `setgl` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'È´òÁ∫ßËÆæÁΩÆ',
  `sfgl` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Êü•ËØ¢Êä•Ë°®',
  `operatorright` varchar(50) NOT NULL DEFAULT 'ÊôÆÈÄöÁî®Êà∑',
  `sysinfo` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Á≥ªÁªüÊó•Âøó',
  `feerate` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Ë¥πÁéáËÆæÁΩÆ',
  `surecardno` varchar(50) DEFAULT NULL,
  `StartVideo` tinyint(1) NOT NULL DEFAULT '0',
  `StartPlate` tinyint(1) NOT NULL DEFAULT '0',
  `ConnectDB` tinyint(1) NOT NULL DEFAULT '0',
  `MonthCard` tinyint(1) NOT NULL DEFAULT '0',
  `ValueCard` tinyint(1) NOT NULL DEFAULT '0',
  `TimeCard` tinyint(1) NOT NULL DEFAULT '0',
  `LedInfo` tinyint(1) NOT NULL DEFAULT '0',
  `DeviceConfig` tinyint(1) NOT NULL DEFAULT '0',
  `SystemSet` tinyint(1) NOT NULL DEFAULT '0',
  `CardRightSet` tinyint(1) NOT NULL DEFAULT '0',
  `DiscountSet` tinyint(1) NOT NULL DEFAULT '0',
  `SerialPortSet` tinyint(1) NOT NULL DEFAULT '0',
  `PlateRecogSet` tinyint(1) NOT NULL DEFAULT '0',
  `PassRecord` tinyint(1) NOT NULL DEFAULT '0',
  `FeeRecord` tinyint(1) NOT NULL DEFAULT '0',
  `DiscountReport` tinyint(1) NOT NULL DEFAULT '0',
  `DailyReport` tinyint(1) NOT NULL DEFAULT '0',
  `MonthlyReport` tinyint(1) NOT NULL DEFAULT '0',
  `YearlyReport` tinyint(1) NOT NULL DEFAULT '0',
  `SyncTime` tinyint(1) NOT NULL DEFAULT '0',
  `Blacklist` tinyint(1) NOT NULL DEFAULT '0',
  `EmployeeID` varchar(45) NOT NULL,
  PRIMARY KEY (`operatorid`),
  KEY `surecardno` (`surecardno`),
  KEY `operatorname` (`operatorname`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `operator`
--

LOCK TABLES `operator` WRITE;
/*!40000 ALTER TABLE `operator` DISABLE KEYS */;
INSERT INTO `operator` VALUES (1,'Á≥ªÁªüÁÆ°ÁêÜÂëò','','Áî∑','','8521951',-1,0,-1,-1,0,0,'Ë∂ÖÁ∫ßÁî®Êà∑',-1,-1,NULL,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,'18804'),(2,'ÂÅúËΩ¶Âú∫ÁÆ°ÁêÜÂëò','','Áî∑','','aaa',-1,0,-1,-1,0,0,'ÊôÆÈÄöÁî®Êà∑',-1,-1,NULL,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,'9400336'),(3,'Áª¥Êä§‰∫∫Âëò','','Áî∑','','8521951',-1,0,-1,-1,0,0,'Ë∂ÖÁ∫ßÁî®Êà∑',-1,-1,NULL,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,'17338');
/*!40000 ALTER TABLE `operator` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `feerate1`
--

DROP TABLE IF EXISTS `feerate1`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `feerate1` (
  `rparkid` int(11) DEFAULT '0' COMMENT '√ç¬£',
  `rfeemodel` int(11) DEFAULT '0',
  `gz1t` int(11) DEFAULT '0',
  `gz1f` int(11) DEFAULT '0',
  `gz2t` int(11) DEFAULT '0',
  `gz2f` int(11) DEFAULT '0',
  `gz3t` int(11) DEFAULT '0',
  `gz3f` int(11) DEFAULT '0',
  `gz4t` int(11) DEFAULT '0',
  `gz4f` int(11) DEFAULT '0',
  `gz5t` int(11) DEFAULT '0',
  `gz5f` int(11) DEFAULT '0',
  `gz6t` int(11) DEFAULT '0',
  `gz6f` int(11) DEFAULT '0',
  `gz7t` int(11) DEFAULT '0',
  `gz7f` int(11) DEFAULT '0',
  `gz8t` int(11) DEFAULT '0',
  `gz8f` int(11) DEFAULT '0',
  `gz9t` int(11) DEFAULT '0',
  `gz9f` int(11) DEFAULT '0',
  `gz10t` int(11) DEFAULT '0',
  `gz10f` int(11) DEFAULT '0',
  `gz11t` int(11) DEFAULT '0',
  `gz11f` int(11) DEFAULT '0',
  `gz12t` int(11) DEFAULT '0',
  `gz12f` int(11) DEFAULT '0',
  `xhdw` int(11) DEFAULT '0',
  `xhfh` int(11) DEFAULT '0',
  `kxiant` int(11) DEFAULT '0',
  `freet` int(11) DEFAULT '0' COMMENT '¬ø√≠√è√û√ä¬±¬º√§',
  `fdtimestar` time DEFAULT '00:00:00',
  `fdtimeend` time DEFAULT '23:59:59',
  `dldwt` int(11) DEFAULT '0',
  `dldwf` int(11) DEFAULT '0',
  `dlxianfee` int(11) DEFAULT '0',
  `dwdwt` int(11) DEFAULT '0',
  `dwdwf` int(11) DEFAULT '0',
  `dwxianfee` int(11) DEFAULT '0',
  `firstjstime` int(11) DEFAULT '0',
  `Section` tinyint(1) DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `feerate1`
--

LOCK TABLES `feerate1` WRITE;
/*!40000 ALTER TABLE `feerate1` DISABLE KEYS */;
INSERT INTO `feerate1` VALUES (5,0,13,14,15,16,17,18,19,20,21,22,23,24,0,0,0,0,0,0,0,0,0,0,0,0,27,28,11,12,'00:00:00','23:59:59',25,26,0,0,0,0,29,0),(5,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(5,2,240,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1440,140,0,0,'00:00:00','23:59:59',120,10,0,0,0,0,0,0),(5,3,60,40,120,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,5,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(5,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(5,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(6,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(6,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(7,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(7,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(7,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(7,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(7,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(21,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(21,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(21,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(21,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(21,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(21,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(21,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(21,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(22,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(22,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(22,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(22,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(22,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(22,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(22,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(27,0,720,150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1440,300,0,1,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(27,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(27,2,720,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1440,200,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(27,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(27,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(27,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(27,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0),(27,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0,0);
/*!40000 ALTER TABLE `feerate1` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprd`
--

DROP TABLE IF EXISTS `stoprd`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprd` (
  `stoprdid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `inshebeiname` varchar(30) DEFAULT NULL,
  `outshebeiname` varchar(30) DEFAULT NULL,
  `invideo1` longblob,
  `invideo2` longblob,
  `invideo3` longblob,
  `invideo4` longblob,
  `outvideo1` longblob,
  `outvideo2` longblob,
  `outvideo3` longblob,
  `outvideo4` longblob,
  `intime` datetime DEFAULT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  `username` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT 'Êó†‰ºòÊÉ†',
  `carcpout` varchar(30) DEFAULT 'Êú™Áü•',
  `MayDelete` tinyint(1) NOT NULL DEFAULT '0',
  `Transfered` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`stoprdid`),
  KEY `cardno_outtime_parkid` (`cardno`,`outtime`,`parkid`),
  KEY `outtime_parkid` (`outtime`,`parkid`),
  KEY `intime_cardno` (`intime`,`cardno`),
  KEY `inshebeiname` (`inshebeiname`),
  KEY `outshebeiname` (`outshebeiname`),
  KEY `cardno` (`cardno`),
  KEY `intime` (`intime`),
  KEY `outtime` (`outtime`),
  KEY `feetime` (`feetime`),
  KEY `feeoperator` (`feeoperator`),
  KEY `carcp` (`carcp`),
  KEY `username` (`username`),
  KEY `cardselfno` (`cardselfno`),
  KEY `cardkind` (`cardkind`),
  KEY `parkid` (`parkid`),
  KEY `feekind` (`feekind`),
  KEY `childrdindx` (`childrdindx`),
  KEY `cardkind_outtime_parkid` (`cardkind`,`outtime`,`parkid`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd`
--

LOCK TABLES `stoprd` WRITE;
/*!40000 ALTER TABLE `stoprd` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`InsertStoprd`
AFTER INSERT ON `parkadmin`.`stoprd`
FOR EACH ROW
BEGIN
	declare rdid bigint unsigned default null;
	set rdid = new.stoprdid;
	#select max( stoprdid ) into @stoprdid from stoprd; -- LAST_INSERT_ID()
	if ( 'Ëá™Áî±Âç°' <> new.cardkind ) then 
		if ( 'Êó†Âç°Â∑•‰Ωú' = new.cardkind ) then
			if ( 1 = new.parkid ) then
				REPLACE CardStoprdID( cardno, stoprdid ) values( new.carcp, rdid );
			end if;
		else
			REPLACE CardStoprdID( cardno, stoprdid ) values( new.cardno, rdid );
		end if;
	end if;

 if ( ( 'ËÆ°Êó∂Âç°' = new.cardkind || 'Êó†Âç°Â∑•‰Ωú' = new.cardkind ) && Exists( Select Table_name from information_schema.tables as a where a.table_name = 'tmpcardintime' and table_schema = 'parkadmin' ) )  then
    -- select max( stoprdid ) into @stoprdid from stoprd; -- LAST_INSERT_ID()
    -- REPLACE CardStoprdID( cardno, stoprdid ) values( new.cardno, @stoprdid );
	if ( 'Êó†Âç°Â∑•‰Ωú' = new.cardkind ) then
		if ( 1 = new.parkid ) then
			if ( '' <> new.carcp and 'Êú™Áü•' <> new.carcp ) then
				delete from tmpcardintime where cardno = new.carcp;
				insert tmpcardintime( cardno, intime, inshebeiname, stoprdid, invideo1, type ) values( new.carcp, new.intime, new.inshebeiname, rdid, new.invideo1, 1 );
			end if;
			#insert tmpcardintime( cardno, intime, inshebeiname, stoprdid, invideo1, type ) values( new.carcp, new.intime, new.inshebeiname, rdid, new.invideo1, 1 );
		else if ( 0 = new.parkid ) then
				if ( '' <> new.carcpout and 'Êú™Áü•' <> new.carcpout ) then
					delete from tmpcardintime where cardno = new.carcpout;
				end if;
			end if;
		end if;
	else
		delete from tmpcardintime where cardno = new.cardno;
		insert tmpcardintime( cardno, intime, inshebeiname, stoprdid ) values( new.cardno, new.intime, new.inshebeiname, rdid );
	end if;
 end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`BeforeUpdateStoprd`
BEFORE UPDATE ON `parkadmin`.`stoprd`
FOR EACH ROW
BEGIN
 if ( true and new.Transfered = 0 ) then -- ÈùíÂüéÂ±± true else false
    set new.MayDelete = old.Maydelete + 1;
 end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`test`@`%`*/ /*!50003 TRIGGER `parkadmin`.`UpdateStoprd`
AFTER UPDATE ON `parkadmin`.`stoprd`
FOR EACH ROW
-- Edit trigger body code below this line. Do not edit lines above this one
BEGIN
 if ( ( 'ËÆ°Êó∂Âç°' = new.cardkind  || 'Êó†Âç°Â∑•‰Ωú' = new.cardkind ) && Exists( Select Table_name from information_schema.tables as a where a.table_name = 'tmpcardintime'  and table_schema = 'parkadmin' ) ) then
  if ( new.invideo1 is not null ) then
    update tmpcardintime set invideo1 = new.invideo1 where stoprdid = old.stoprdid;
  
  end if;
 end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `carinfo`
--

DROP TABLE IF EXISTS `carinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `carinfo` (
  `carid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `carcp` varchar(50) NOT NULL DEFAULT 'Êú™Áü•',
  `carmodel` varchar(50) NOT NULL DEFAULT 'Â∞èÂûãËΩ¶',
  `carpic` longblob,
  `cardindex` varchar(50) NOT NULL DEFAULT '0',
  `carhaoma` varchar(50) NOT NULL DEFAULT 'Êú™Áü•',
  PRIMARY KEY (`carid`),
  KEY `cardindex` (`cardindex`),
  KEY `carcp` (`carcp`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `carinfo`
--

LOCK TABLES `carinfo` WRITE;
/*!40000 ALTER TABLE `carinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `carinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `feeratebackup`
--

DROP TABLE IF EXISTS `feeratebackup`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `feeratebackup` (
  `RParkid` int(10) DEFAULT NULL,
  `RFeeModel` int(10) DEFAULT NULL,
  `RTimeIndex` int(10) DEFAULT NULL,
  `RSmTime` int(10) DEFAULT NULL,
  `RBmTime` int(10) DEFAULT NULL,
  `RMoney` int(10) DEFAULT NULL,
  `RMoneyDw` int(10) DEFAULT NULL,
  `RIncTime` tinyint(1) NOT NULL DEFAULT '0',
  KEY `RParkid` (`RParkid`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `feeratebackup`
--

LOCK TABLES `feeratebackup` WRITE;
/*!40000 ALTER TABLE `feeratebackup` DISABLE KEYS */;
INSERT INTO `feeratebackup` VALUES (29,0,0,0,0,7,0,0),(29,0,1,1,2,0,0,0),(29,0,2,0,0,0,0,0),(29,0,3,0,0,0,0,0),(29,0,4,0,0,0,0,0),(29,0,5,0,0,0,0,0),(29,0,6,0,0,0,0,0),(29,0,7,0,0,0,0,0),(29,0,8,0,0,0,0,0),(29,1,0,0,0,7,0,0),(29,1,1,1,2,0,0,0),(29,1,2,0,0,0,0,0),(29,1,3,0,0,0,0,0),(29,1,4,0,0,0,0,0),(29,1,5,0,0,0,0,0),(29,1,6,0,0,0,0,0),(29,1,7,0,0,0,0,0),(29,1,8,0,0,0,0,0),(29,2,0,0,0,2,0,1),(29,2,1,1,2,6,0,0),(29,2,2,3,5,1,2,0),(29,2,3,6,1000,2,3,0),(29,2,4,0,0,0,0,0),(29,2,5,0,0,0,0,0),(29,2,6,0,0,0,0,0),(29,2,7,0,0,0,0,0),(29,2,8,0,0,0,0,0),(29,3,0,0,0,7,0,0),(29,3,1,1,2,0,0,0),(29,3,2,0,0,0,0,0),(29,3,3,0,0,0,0,0),(29,3,4,0,0,0,0,0),(29,3,5,0,0,0,0,0),(29,3,6,0,0,0,0,0),(29,3,7,0,0,0,0,0),(29,3,8,0,0,0,0,0),(29,4,0,0,0,7,0,0),(29,4,1,1,2,0,0,0),(29,4,2,0,0,0,0,0),(29,4,3,0,0,0,0,0),(29,4,4,0,0,0,0,0),(29,4,5,0,0,0,0,0),(29,4,6,0,0,0,0,0),(29,4,7,0,0,0,0,0),(29,4,8,0,0,0,0,0),(29,5,0,0,0,7,0,0),(29,5,1,1,2,0,0,0),(29,5,2,0,0,0,0,0),(29,5,3,0,0,0,0,0),(29,5,4,0,0,0,0,0),(29,5,5,0,0,0,0,0),(29,5,6,0,0,0,0,0),(29,5,7,0,0,0,0,0),(29,5,8,0,0,0,0,0),(29,6,0,0,0,7,0,0),(29,6,1,1,2,0,0,0),(29,6,2,0,0,0,0,0),(29,6,3,0,0,0,0,0),(29,6,4,0,0,0,0,0),(29,6,5,0,0,0,0,0),(29,6,6,0,0,0,0,0),(29,6,7,0,0,0,0,0),(29,6,8,0,0,0,0,0),(29,7,0,0,0,7,0,0),(29,7,1,1,2,0,0,0),(29,7,2,0,0,0,0,0),(29,7,3,0,0,0,0,0),(29,7,4,0,0,0,0,0),(29,7,5,0,0,0,0,0),(29,7,6,0,0,0,0,0),(29,7,7,0,0,0,0,0),(29,7,8,0,0,0,0,0);
/*!40000 ALTER TABLE `feeratebackup` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `rawplatetable`
--

DROP TABLE IF EXISTS `rawplatetable`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `rawplatetable` (
  `RawPlate` varchar(32) NOT NULL,
  PRIMARY KEY (`RawPlate`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `rawplatetable`
--

LOCK TABLES `rawplatetable` WRITE;
/*!40000 ALTER TABLE `rawplatetable` DISABLE KEYS */;
/*!40000 ALTER TABLE `rawplatetable` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `savecard`
--

DROP TABLE IF EXISTS `savecard`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `savecard` (
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `cardstate` varchar(30) NOT NULL DEFAULT 'ÂêØÁî®',
  `cardkind` varchar(30) DEFAULT 'EMIDÂç°',
  `cardselfno` varchar(50) DEFAULT NULL,
  `cardcomment` varchar(100) DEFAULT NULL,
  `cardcreator` varchar(30) DEFAULT NULL,
  `cardfeebz` varchar(30) NOT NULL DEFAULT 'Áé∞Âú∫ÈÄâÊã©',
  `cardfee` int(10) unsigned DEFAULT '0',
  `Inside` int(11) NOT NULL DEFAULT '0',
  `EnterMustCard` int(11) DEFAULT '0',
  `LeaveMustCard` int(11) DEFAULT '0',
  PRIMARY KEY (`cardno`),
  KEY `cardselfno` (`cardselfno`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `savecard`
--

LOCK TABLES `savecard` WRITE;
/*!40000 ALTER TABLE `savecard` DISABLE KEYS */;
/*!40000 ALTER TABLE `savecard` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`savecard_ai`
AFTER INSERT ON `parkadmin`.`savecard`
FOR EACH ROW
BEGIN
DECLARE a,b INT;
DECLARE ai char(30);
DECLARE cur_1 CURSOR FOR SELECT shebeiid FROM roadconerinfo;
DECLARE cur_2 CURSOR FOR SELECT shebeiname FROM roadconerinfo;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET b = 1;
OPEN cur_1;
OPEN cur_2;
set b = 0;
while b<>1 do
FETCH cur_1 INTO a;
FETCH cur_2 INTO ai;
if b<>1 then
insert into cardright(cardno,roadconind,shebeiname) values(NEW.cardno,a,ai);
end if;
END while;
CLOSE cur_1;
CLOSE cur_2;
insert into userinfo(cardindex) values(NEW.cardno);
insert into carinfo(cardindex) values(NEW.cardno); 
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`savecard_au`
AFTER UPDATE ON `parkadmin`.`savecard`
FOR EACH ROW
BEGIN
if new.cardno<>old.cardno then
update userinfo set userinfo.cardindex=new.cardno where userinfo.cardindex=old.cardno;
update carinfo set carinfo.cardindex=new.cardno where carinfo.cardindex=old.cardno;
update cardright set cardright.cardno=new.cardno where cardright.cardno=old.cardno;
update feerd set feerd.cardno=new.cardno where feerd.cardno=old.cardno;
update stoprd set stoprd.cardno=new.cardno where stoprd.cardno=old.cardno;
end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`savecard_ad`
AFTER DELETE ON `parkadmin`.`savecard`
FOR EACH ROW
BEGIN
delete from userinfo where userinfo.cardindex=OLD.cardno;
delete from carinfo where carinfo.cardindex=OLD.cardno;
delete from cardright where cardright.cardno=OLD.cardno;
delete from stoprd where stoprd.cardno=OLD.cardno and stoprd.outtime is NULL;  
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `tmpcardintime`
--

DROP TABLE IF EXISTS `tmpcardintime`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmpcardintime` (
  `idtmpcardintime` int(11) NOT NULL AUTO_INCREMENT,
  `cardno` varchar(45) NOT NULL,
  `intime` datetime NOT NULL,
  `inshebeiname` varchar(30) DEFAULT NULL,
  `invideo1` longblob,
  `stoprdid` bigint(20) DEFAULT NULL,
  `type` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`idtmpcardintime`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmpcardintime`
--

LOCK TABLES `tmpcardintime` WRITE;
/*!40000 ALTER TABLE `tmpcardintime` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmpcardintime` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sysinfo`
--

DROP TABLE IF EXISTS `sysinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sysinfo` (
  `infoindex` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `infooperator` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  `infokind` varchar(50) NOT NULL DEFAULT 'Êú™Áü•',
  `infotext` varchar(150) NOT NULL DEFAULT 'Êú™Áü•',
  `infotime` datetime NOT NULL,
  `infopic1` longblob,
  `infopic2` longblob,
  `infopic3` longblob,
  `infopic4` longblob,
  PRIMARY KEY (`infoindex`),
  KEY `infotime` (`infotime`),
  KEY `infooperator` (`infooperator`)
) ENGINE=InnoDB AUTO_INCREMENT=1509 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sysinfo`
--

LOCK TABLES `sysinfo` WRITE;
/*!40000 ALTER TABLE `sysinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `sysinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cardstoprdid`
--

DROP TABLE IF EXISTS `cardstoprdid`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cardstoprdid` (
  `cardno` varchar(50) NOT NULL,
  `stoprdid` bigint(20) DEFAULT NULL,
  PRIMARY KEY (`cardno`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cardstoprdid`
--

LOCK TABLES `cardstoprdid` WRITE;
/*!40000 ALTER TABLE `cardstoprdid` DISABLE KEYS */;
/*!40000 ALTER TABLE `cardstoprdid` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `feerate`
--

DROP TABLE IF EXISTS `feerate`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `feerate` (
  `RParkid` int(10) DEFAULT NULL,
  `RFeeModel` int(10) DEFAULT NULL,
  `RTimeIndex` int(10) DEFAULT NULL,
  `RSmTime` int(10) DEFAULT NULL,
  `RBmTime` int(10) DEFAULT NULL,
  `RMoney` int(10) DEFAULT NULL,
  `RMoneyDw` int(10) DEFAULT NULL,
  `RIncTime` tinyint(1) NOT NULL DEFAULT '0',
  `RIndex` int(10) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`RIndex`),
  KEY `RParkid` (`RParkid`)
) ENGINE=InnoDB AUTO_INCREMENT=1594 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `feerate`
--

LOCK TABLES `feerate` WRITE;
/*!40000 ALTER TABLE `feerate` DISABLE KEYS */;
INSERT INTO `feerate` VALUES (27,0,0,0,0,7,0,0,1522),(27,0,1,1,2,0,0,0,1523),(27,0,2,0,0,0,0,0,1524),(27,0,3,0,0,0,0,0,1525),(27,0,4,0,0,0,0,0,1526),(27,0,5,0,0,0,0,0,1527),(27,0,6,0,0,0,0,0,1528),(27,0,7,0,0,0,0,0,1529),(27,0,8,0,0,0,0,0,1530),(27,1,0,0,0,7,0,0,1531),(27,1,1,1,2,0,0,0,1532),(27,1,2,0,0,0,0,0,1533),(27,1,3,0,0,0,0,0,1534),(27,1,4,0,0,0,0,0,1535),(27,1,5,0,0,0,0,0,1536),(27,1,6,0,0,0,0,0,1537),(27,1,7,0,0,0,0,0,1538),(27,1,8,0,0,0,0,0,1539),(27,2,0,0,0,2,0,1,1540),(27,2,1,1,2,6,0,0,1541),(27,2,2,3,5,1,2,0,1542),(27,2,3,6,1000,2,3,0,1543),(27,2,4,0,0,0,0,0,1544),(27,2,5,0,0,0,0,0,1545),(27,2,6,0,0,0,0,0,1546),(27,2,7,0,0,0,0,0,1547),(27,2,8,0,0,0,0,0,1548),(27,3,0,0,0,7,0,0,1549),(27,3,1,1,2,0,0,0,1550),(27,3,2,0,0,0,0,0,1551),(27,3,3,0,0,0,0,0,1552),(27,3,4,0,0,0,0,0,1553),(27,3,5,0,0,0,0,0,1554),(27,3,6,0,0,0,0,0,1555),(27,3,7,0,0,0,0,0,1556),(27,3,8,0,0,0,0,0,1557),(27,4,0,0,0,7,0,0,1558),(27,4,1,1,2,0,0,0,1559),(27,4,2,0,0,0,0,0,1560),(27,4,3,0,0,0,0,0,1561),(27,4,4,0,0,0,0,0,1562),(27,4,5,0,0,0,0,0,1563),(27,4,6,0,0,0,0,0,1564),(27,4,7,0,0,0,0,0,1565),(27,4,8,0,0,0,0,0,1566),(27,5,0,0,0,7,0,0,1567),(27,5,1,1,2,0,0,0,1568),(27,5,2,0,0,0,0,0,1569),(27,5,3,0,0,0,0,0,1570),(27,5,4,0,0,0,0,0,1571),(27,5,5,0,0,0,0,0,1572),(27,5,6,0,0,0,0,0,1573),(27,5,7,0,0,0,0,0,1574),(27,5,8,0,0,0,0,0,1575),(27,6,0,0,0,7,0,0,1576),(27,6,1,1,2,0,0,0,1577),(27,6,2,0,0,0,0,0,1578),(27,6,3,0,0,0,0,0,1579),(27,6,4,0,0,0,0,0,1580),(27,6,5,0,0,0,0,0,1581),(27,6,6,0,0,0,0,0,1582),(27,6,7,0,0,0,0,0,1583),(27,6,8,0,0,0,0,0,1584),(27,7,0,0,0,7,0,0,1585),(27,7,1,1,2,0,0,0,1586),(27,7,2,0,0,0,0,0,1587),(27,7,3,0,0,0,0,0,1588),(27,7,4,0,0,0,0,0,1589),(27,7,5,0,0,0,0,0,1590),(27,7,6,0,0,0,0,0,1591),(27,7,7,0,0,0,0,0,1592),(27,7,8,0,0,0,0,0,1593);
/*!40000 ALTER TABLE `feerate` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `garageingarage`
--

DROP TABLE IF EXISTS `garageingarage`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `garageingarage` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `CardID` varchar(45) DEFAULT NULL,
  `PlateID` varchar(45) DEFAULT NULL,
  `DateTime` datetime DEFAULT NULL,
  `InOutFlag` tinyint(1) DEFAULT NULL,
  `ChannelName` varchar(45) DEFAULT NULL,
  `Level` int(8) DEFAULT NULL,
  `Image` longblob,
  `Cardkind` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `garageingarage`
--

LOCK TABLES `garageingarage` WRITE;
/*!40000 ALTER TABLE `garageingarage` DISABLE KEYS */;
/*!40000 ALTER TABLE `garageingarage` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`test`@`%`*/ /*!50003 TRIGGER `parkadmin`.`garageingarage_AINS`
AFTER INSERT ON `parkadmin`.`garageingarage`
FOR EACH ROW
-- Edit trigger body code below this line. Do not edit lines above this one

begin
	if ( 'Ëá™Áî±Âç°' <> new.cardkind ) then
		replace garagestoprdid( cardno, stoprdid ) value( new.cardid, new.id );
	end if;
end */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `userinfo`
--

DROP TABLE IF EXISTS `userinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `userinfo` (
  `userid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(30) DEFAULT 'Êú™Áü•',
  `usersex` varchar(30) DEFAULT 'Êú™Áü•',
  `useradress` varchar(50) DEFAULT 'Êú™Áü•',
  `usercorp` varchar(50) DEFAULT 'Êú™Áü•',
  `userphone` varchar(50) DEFAULT 'Êú™Áü•',
  `userhaoma` varchar(50) DEFAULT 'Êú™Áü•',
  `userpic` longblob,
  `cardindex` varchar(50) NOT NULL DEFAULT '0',
  `Comments` varchar(250) DEFAULT '',
  PRIMARY KEY (`userid`),
  KEY `cardindex` (`cardindex`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `userinfo`
--

LOCK TABLES `userinfo` WRITE;
/*!40000 ALTER TABLE `userinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `userinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprd2`
--

DROP TABLE IF EXISTS `stoprd2`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprd2` (
  `stoprdid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `inshebeiname` varchar(30) DEFAULT NULL,
  `outshebeiname` varchar(30) DEFAULT NULL,
  `invideo1` longblob,
  `invideo2` longblob,
  `invideo3` longblob,
  `invideo4` longblob,
  `outvideo1` longblob,
  `outvideo2` longblob,
  `outvideo3` longblob,
  `outvideo4` longblob,
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  `username` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT 'Êó†‰ºòÊÉ†',
  `carcpout` varchar(30) DEFAULT 'Êú™Áü•',
  `MayDelete` tinyint(1) DEFAULT '0',
  `Transfered` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`stoprdid`),
  KEY `cardno_outtime_parkid` (`cardno`,`outtime`,`parkid`),
  KEY `outtime_parkid` (`outtime`,`parkid`),
  KEY `intime_cardno` (`intime`,`cardno`),
  KEY `inshebeiname` (`inshebeiname`),
  KEY `outshebeiname` (`outshebeiname`),
  KEY `cardno` (`cardno`),
  KEY `intime` (`intime`),
  KEY `outtime` (`outtime`),
  KEY `feetime` (`feetime`),
  KEY `feeoperator` (`feeoperator`),
  KEY `carcp` (`carcp`),
  KEY `username` (`username`),
  KEY `cardselfno` (`cardselfno`),
  KEY `cardkind` (`cardkind`),
  KEY `parkid` (`parkid`),
  KEY `feekind` (`feekind`),
  KEY `childrdindx` (`childrdindx`),
  KEY `cardkind_outtime_parkid` (`cardkind`,`outtime`,`parkid`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd2`
--

LOCK TABLES `stoprd2` WRITE;
/*!40000 ALTER TABLE `stoprd2` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd2` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `test`
--

DROP TABLE IF EXISTS `test`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `test` (
  `idtest` int(11) NOT NULL AUTO_INCREMENT,
  `testcol` varchar(45) NOT NULL,
  `testcol1` varchar(45) NOT NULL,
  `testcol2` varchar(45) NOT NULL,
  PRIMARY KEY (`idtest`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `test`
--

LOCK TABLES `test` WRITE;
/*!40000 ALTER TABLE `test` DISABLE KEYS */;
/*!40000 ALTER TABLE `test` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `garagestoprdid`
--

DROP TABLE IF EXISTS `garagestoprdid`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `garagestoprdid` (
  `CardNo` varchar(45) NOT NULL,
  `stoprdid` bigint(20) DEFAULT NULL,
  PRIMARY KEY (`CardNo`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `garagestoprdid`
--

LOCK TABLES `garagestoprdid` WRITE;
/*!40000 ALTER TABLE `garagestoprdid` DISABLE KEYS */;
/*!40000 ALTER TABLE `garagestoprdid` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `roadconerinfo`
--

DROP TABLE IF EXISTS `roadconerinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `roadconerinfo` (
  `roadconerind` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `shebeiid` int(10) unsigned NOT NULL DEFAULT '0',
  `shebeiadr` int(10) unsigned NOT NULL DEFAULT '0',
  `video1` int(11) NOT NULL DEFAULT '0',
  `video2` int(11) NOT NULL DEFAULT '0',
  `video3` int(11) NOT NULL DEFAULT '0',
  `video4` int(11) NOT NULL DEFAULT '0',
  `shebeiname` varchar(30) NOT NULL DEFAULT 'Êñ∞Âª∫ÊéßÂà∂Âô®',
  `video1ip` varchar(30) NOT NULL DEFAULT '127.0.0.1',
  `video2ip` varchar(30) NOT NULL DEFAULT '127.0.0.1',
  `video3ip` varchar(30) NOT NULL DEFAULT '127.0.0.1',
  `video4ip` varchar(30) NOT NULL DEFAULT '127.0.0.1',
  `ifdoor` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`roadconerind`),
  KEY `shebeiid` (`shebeiid`),
  KEY `shebeiadr` (`shebeiadr`)
) ENGINE=InnoDB AUTO_INCREMENT=98 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roadconerinfo`
--

LOCK TABLES `roadconerinfo` WRITE;
/*!40000 ALTER TABLE `roadconerinfo` DISABLE KEYS */;
INSERT INTO `roadconerinfo` VALUES (54,134,1,0,0,0,0,'10-1','192.168.1.10','192.168.1.101','127.0.0.1','127.0.0.1',0),(55,135,2,0,0,0,0,'10-2','192.168.1.10','192.168.1.102','127.0.0.1','127.0.0.1',0),(58,138,3,0,0,0,0,'10-3','192.168.1.10','192.168.1.10','127.0.0.1','127.0.0.1',0),(86,172,1,0,0,0,0,'53-1','192.168.1.53','192.168.1.64','127.0.0.1','127.0.0.1',0),(87,173,2,0,0,0,0,'53-2','192.168.1.53','192.168.1.65','127.0.0.1','127.0.0.1',0),(88,174,33,0,0,0,0,'53-33','192.168.1.53','192.168.1.111','127.0.0.1','127.0.0.1',0),(92,178,1,0,0,0,0,'156-1','192.168.1.156','192.168.1.64','127.0.0.1','127.0.0.1',0),(93,179,2,0,0,0,0,'156-2','192.168.1.156','192.168.1.65','127.0.0.1','127.0.0.1',0),(94,180,1,0,0,0,0,'24-1','192.168.1.24','192.168.1.65','127.0.0.1','127.0.0.1',0),(95,181,2,0,0,0,0,'24-2','192.168.1.24','192.168.1.65','127.0.0.1','127.0.0.1',0),(96,182,33,0,0,0,0,'24-33','192.168.1.24','192.168.1.111','127.0.0.1','127.0.0.1',0),(97,183,34,0,0,0,0,'24-34','192.168.1.24','192.168.1.111','127.0.0.1','127.0.0.1',0);
/*!40000 ALTER TABLE `roadconerinfo` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`roadconerinfo_au`
AFTER UPDATE ON `parkadmin`.`roadconerinfo`
FOR EACH ROW
BEGIN
if new.shebeiname<>old.shebeiname then 
update cardright set  cardright.shebeiname=new.shebeiname where cardright.roadconind=old.shebeiid;
update treeview set treeview.shebeiname=new.shebeiname where treeview.shebeiid=old.shebeiid;
end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `treeview`
--

DROP TABLE IF EXISTS `treeview`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `treeview` (
  `shebeiid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `level` int(10) unsigned NOT NULL DEFAULT '0',
  `parentid` int(11) unsigned NOT NULL DEFAULT '0',
  `shebeikind` varchar(30) NOT NULL DEFAULT 'kzq',
  `shebeiname` varchar(30) NOT NULL DEFAULT 'Êú™Áü•',
  PRIMARY KEY (`shebeiid`),
  KEY `parentid` (`parentid`)
) ENGINE=InnoDB AUTO_INCREMENT=184 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `treeview`
--

LOCK TABLES `treeview` WRITE;
/*!40000 ALTER TABLE `treeview` DISABLE KEYS */;
INSERT INTO `treeview` VALUES (131,0,1,'tcc','***ÂÅúËΩ¶Âú∫'),(134,0,131,'kzq','10-1'),(135,0,131,'kzq','10-2'),(138,0,131,'kzq','10-3'),(172,0,131,'kzq','53-1'),(173,0,131,'kzq','53-2'),(174,0,131,'kzq','53-33'),(178,0,131,'kzq','156-1'),(179,0,131,'kzq','156-2'),(180,0,131,'kzq','24-1'),(181,0,131,'kzq','24-2'),(182,0,131,'kzq','24-33'),(183,0,131,'kzq','24-34');
/*!40000 ALTER TABLE `treeview` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`treeview_ai`
AFTER INSERT ON `parkadmin`.`treeview`
FOR EACH ROW
BEGIN
DECLARE a,b INT;
DECLARE ai char(50);
DECLARE cur_1 CURSOR FOR SELECT cardno FROM monthcard;
DECLARE cur_2 CURSOR FOR SELECT cardno FROM savecard;
DECLARE cur_3 CURSOR FOR SELECT cardno FROM tmpcard;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET b = 1;
OPEN cur_1;
OPEN cur_2;
OPEN cur_3;
set b = 0;
if NEW.shebeikind = 'kzq'   then
FETCH cur_1 INTO ai;
while b<>1 do
insert into cardright(cardno,roadconind,shebeiname) values(ai,new.shebeiid,shebeiname);
FETCH cur_1 INTO ai;
END while; 
set b = 0;
FETCH cur_2 INTO ai;
while b<>1 do
insert into cardright(cardno,roadconind,shebeiname) values(ai,new.shebeiid,shebeiname);
FETCH cur_2 INTO ai;
END while; 
set b = 0;
FETCH cur_3 INTO ai;
while b<>1 do
insert into cardright(cardno,roadconind,shebeiname) values(ai,new.shebeiid,shebeiname);
FETCH cur_3 INTO ai;
END while;
insert into roadconerinfo(shebeiid) values(NEW.shebeiid);
end if;
if NEW.shebeikind= 'tcc'  then
insert into parkinfo(shebeiid) values(NEW.shebeiid);
end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`treeview_ad`
AFTER DELETE ON `parkadmin`.`treeview`
FOR EACH ROW
BEGIN
delete from roadconerinfo where roadconerinfo.shebeiid=old.shebeiid;
delete from parkinfo where parkinfo.shebeiid=old.shebeiid;
delete from cardright where cardright.roadconind=old.shebeiid;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `monthcard`
--

DROP TABLE IF EXISTS `monthcard`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `monthcard` (
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `starttime` datetime NOT NULL DEFAULT '2006-06-01 12:00:00',
  `endtime` datetime NOT NULL DEFAULT '2006-06-01 12:00:00',
  `cardstate` varchar(30) NOT NULL DEFAULT 'ÂêØÁî®',
  `cardkind` varchar(30) DEFAULT 'EMIDÂç°',
  `cardselfno` varchar(50) DEFAULT 'Êú™Áü•',
  `cardcomment` varchar(100) DEFAULT 'Êú™Áü•',
  `cardcreator` varchar(30) DEFAULT 'Êú™Áü•',
  `Inside` int(10) DEFAULT '0',
  `EnterMustCard` int(10) DEFAULT '0',
  `LeaveMustCard` int(10) DEFAULT '0',
  `MIMO` int(10) DEFAULT '0',
  PRIMARY KEY (`cardno`),
  KEY `cardno_starttime_endtime` (`cardno`,`starttime`,`endtime`),
  KEY `cardselfno` (`cardselfno`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `monthcard`
--

LOCK TABLES `monthcard` WRITE;
/*!40000 ALTER TABLE `monthcard` DISABLE KEYS */;
/*!40000 ALTER TABLE `monthcard` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`monthcard_ai`
AFTER INSERT ON `parkadmin`.`monthcard`
FOR EACH ROW
BEGIN
DECLARE a,b INT;
DECLARE ai char(30);
DECLARE cur_1 CURSOR FOR SELECT shebeiid FROM roadconerinfo;
DECLARE cur_2 CURSOR FOR SELECT shebeiname FROM roadconerinfo;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET b = 1;
OPEN cur_1;
OPEN cur_2;
set b = 0;
while b<>1 do
FETCH cur_1 INTO a;
FETCH cur_2 INTO ai;
if b<>1 then
insert into cardright(cardno,roadconind,shebeiname) values(NEW.cardno,a,ai);
end if;
END while;
CLOSE cur_1;
CLOSE cur_2;
insert into userinfo(cardindex) values(NEW.cardno);
insert into carinfo(cardindex) values(NEW.cardno); 
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`monthcard_au`
AFTER UPDATE ON `parkadmin`.`monthcard`
FOR EACH ROW
BEGIN
if new.cardno<>old.cardno then
update userinfo set userinfo.cardindex=new.cardno where userinfo.cardindex=old.cardno;
update carinfo set carinfo.cardindex=new.cardno where carinfo.cardindex=old.cardno;
update cardright set cardright.cardno=new.cardno where cardright.cardno=old.cardno;
update feerd set feerd.cardno=new.cardno where feerd.cardno=old.cardno;
update stoprd set stoprd.cardno=new.cardno where stoprd.cardno=old.cardno;
end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`monthcard_ad`
AFTER DELETE ON `parkadmin`.`monthcard`
FOR EACH ROW
BEGIN
delete from userinfo where userinfo.cardindex=OLD.cardno;
delete from carinfo where carinfo.cardindex=OLD.cardno;
delete from cardright where cardright.cardno=OLD.cardno;
delete from stoprd where stoprd.cardno=OLD.cardno and stoprd.outtime is NULL; 
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `parkadminset`
--

DROP TABLE IF EXISTS `parkadminset`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `parkadminset` (
  `feejsbz` int(11) DEFAULT '1'
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `parkadminset`
--

LOCK TABLES `parkadminset` WRITE;
/*!40000 ALTER TABLE `parkadminset` DISABLE KEYS */;
INSERT INTO `parkadminset` VALUES (1);
/*!40000 ALTER TABLE `parkadminset` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'parkadmin'
--

--
-- Dumping routines for database 'parkadmin'
--
/*!50003 DROP FUNCTION IF EXISTS `CarInSide` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`test`@`%`*/ /*!50003 FUNCTION `CarInSide`( tabName char( 32 ), cardNo char( 32 ) ) RETURNS tinyint(1)
BEGIN
	declare tName char( 32 ) default upper( tabName );
	declare bInside bool default false;

	case tName 
		when 'MONTHCARD' then 
			begin
				select inside into bInside from MONTHCARD a, cardstoprdid b, stoprd c
					where a.cardno = cardNo and a.cardno = b.cardno and b.stoprdid = c.stoprdid 
						  and c.outtime is null and c.childrdindx is null;
			end;
		when 'SAVECARD' then
			begin
				select inside into bInside from SAVECARD a, cardstoprdid b, stoprd c
					where a.cardno = cardNo and a.cardno = b.cardno and b.stoprdid = c.stoprdid
						and c.outtime is null and c.childrdindx is null;
			end;
		when 'TMPCARD' then
			begin
				select inside into bInside from TMPCARD a, cardstoprdid b, stoprd c
					where a.cardno = cardNo and a.cardno = b.cardno and b.stoprdid = c.stoprdid
						and c.outtime is null and c.childrdindx is null;
			end;
	end case;
RETURN bInside;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP FUNCTION IF EXISTS `CenterController` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`test`@`%`*/ /*!50003 FUNCTION `CenterController`( cardNo char( 32 ) ) RETURNS int(11)
BEGIN
	declare bInside bool default null;
	declare bReturn bool default false;

	select inside into bInside from MONTHCARD a, cardstoprdid b, stoprd c
					where a.cardno = cardNo and a.cardno = b.cardno and b.stoprdid = c.stoprdid 
					and c.childrdindx = 1;

	if ( bInside is not null ) then
		RETURN bInside;
	end if;

	select inside into bInside from MONTHCARD a, cardstoprdid b, stoprd c
					where a.cardno = cardNo and a.cardno = b.cardno and b.stoprdid = c.stoprdid 
						  and c.outtime is null and c.childrdindx is null;
	if ( bInside is not null ) then
		RETURN bInside;
	end if;

	select inside into bInside from SaveCARD a, cardstoprdid b, stoprd c
					where a.cardno = cardNo and a.cardno = b.cardno and b.stoprdid = c.stoprdid 
						  and c.outtime is null and c.childrdindx is null;
	if ( bInside is not null ) then
		RETURN bInside;
	end if;

	select inside into bInside from TmpCARD a, cardstoprdid b, stoprd c
					where a.cardno = cardNo and a.cardno = b.cardno and b.stoprdid = c.stoprdid 
						  and c.outtime is null and c.childrdindx is null;
	if ( bInside is not null ) then
		RETURN bInside;
	end if;

RETURN bReturn;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP FUNCTION IF EXISTS `InsertFreeCardData` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`test`@`%`*/ /*!50003 FUNCTION `InsertFreeCardData`( cardNo varchar( 16 ), carTime varchar( 32 ), 
												   channel varchar( 64 ), plate varchar( 8 ), image longtext,
												   layer tinyint, flag tinyint, strType varchar( 32 ), nFee int ) RETURNS int(11)
BEGIN
	declare bEnter boolean default ( 0 <> flag );
	declare bGarage boolean default ( 1 < layer );

	if ( bGarage ) then
		Insert Into GarageInGarage( CardID, ChannelName, Level, DateTime,
                          InOutFlag, PlateID, image ) VALUE( cardNo, channel, layer, carTime, flag, plate, unhex( image ) );
	else
		if ( bEnter ) then
			insert into stoprd( inshebeiname, intime, cardno, carcp, cardkind, invideo1, parkid, childrdindx ) 
			value( channel, carTime, cardNo, plate, strType, unhex( image ), 1, 1 );
		else 
			insert into stoprd( outshebeiname, outtime, cardno, carcpout, cardkind, outvideo1, parkid, childrdindx, feefactnum ) 
			value( channel, carTime, cardNo, plate, strType, unhex( image ), 0, 1, nFee );
		end if;
	end if;
RETURN 1;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP FUNCTION IF EXISTS `NoCardWork` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`test`@`%`*/ /*!50003 FUNCTION `NoCardWork`( plate varchar( 16 ), cCan tinyint ) RETURNS varchar(1024) CHARSET gb2312
BEGIN
	declare strMsg varchar( 1024 ) default '';
	declare bMonth boolean default false;
	declare dtStart, dtEnd DATETIME default null;
	declare bEnter boolean default ( 0 <> ( cCan % 2 ) );

	#ÁôªËÆ∞ËΩ¶ÁâåË¶ÅÂîØ‰∏Ä
	select starttime, endtime into dtStart, dtEnd from carinfo, monthcard 
     where carcp = plate and carcp not in( '', 'Êú™Áü•' ) and cardindex = cardno limit 1;

	set bMonth = ( dtStart is not null);
	
	if ( bMonth ) then
		begin
			declare bExpire boolean default ( now( ) > dtEnd or dtEnd < dtStart );
			declare nDay int default ( TO_DAYS( DATE( dtEnd ) ) - TO_DAYS( curdate( ) ) );
			
			set strMsg = concat( 'month,', IF( bExpire, '1', '0' ), ',', convert( nDay, char ), ',', IF( bEnter, '1', '0' ) );
		end;
	else
		begin
			declare id1, id2 bigint default null;
			declare dtEnter datetime default null;
			declare bUnknown boolean default false;
			declare strChannel varchar( 64 ) default null;

			if ( bEnter ) then
				set strMsg = concat( 'time,', '1' );
			else 
				select idtmpcardintime, intime, stoprdid, inshebeiname into id1, dtEnter, id2, strChannel 
					from tmpcardintime where cardno = plate and cardno not in( '', 'Êú™Áü•' ) limit 1;

				set bUnknown = ( id1 is null );
				if ( bUnknown ) then
					set strMsg = concat( 'time,', '0,', '1' );
				else
					set strMsg = concat( 'time,', '0,', '0,', convert( id1, char ), ',', 
								 convert( id2, char ), ',', convert( dtEnter, char ), ',', strChannel );
				end if;
			end if;
		end;
	end if;

RETURN strMsg;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Calculate` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`test`@`%`*/ /*!50003 PROCEDURE `Calculate`( out nMonth int, out nSave int, out nTmp int )
BEGIN
select count( * ) into nMonth from monthcard where Inside = 1;
select count( * ) into nSave from Savecard where Inside = 1;
select count( * ) into nTmp from tmpcard where Inside = 1;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GenerateReport` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`test`@`%`*/ /*!50003 PROCEDURE `GenerateReport`( in dtStart DATETIME, in dtEnd DATETIME, in nReportType int )
BEGIN
#Êï∞Â≠óËΩ¨Â≠óÁ¨¶‰∏≤ :
#newstr=concat(n,'');
#Â≠óÁ¨¶‰∏≤ËΩ¨Êï∞Â≠ó:
#newn= str+0;
#select year( intime ), month( intime ), day( intime ), count( cardno ) from parkadmin.stoprd group by year( intime ), month( intime ), day( intime );
#select year( feetime ), month( feetime ), day( feetime ), sum( feenumb ) from parkadmin.feerd group by year( feetime ), month( feetime ), day( feetime );
    #nReportType 
    declare sYear int;
    declare eYear int;
    declare nYear int;
    declare sMonth int;
    declare eMonth int;
    declare nMonth int;
    declare sDay int;
    declare eDay int;
    
    declare strSYear varchar( 4 );
    declare strEYear varchar( 4 );
    declare strNYear varchar( 4 );
    declare strSMonth varchar( 2 );
    declare strEMonth varchar( 2 );
    declare strNMonth varchar( 2 );
    declare strSDay varchar( 2 );
    declare strEDay varchar( 2 );
    
    declare yBegin varchar( 40 );
    declare yEnd varchar( 40 );
    declare mBegin varchar( 40 );
    declare mEnd varchar( 40 );
    
    declare strSql varchar( 5120 ) default '';
    declare strFormat varchar( 30 ) default '%Y-%m-%d %T';
    declare strPerson varchar( 15 ) default '';
    
    declare strMonthCard varchar( 6 ) default 'ÊúàÁßüÂç°';
    declare strTimeCard varchar( 6 ) default 'ËÆ°Êó∂Âç°';
    declare strValueCard varchar( 6 ) default 'ÂÇ®ÂÄºÂç°';
    
    set sYear = YEAR( dtStart );
    set eYear = YEAR( dtEnd );
    set nYear = eYear + 1;
    set sMonth = MONTH( dtStart );
    set eMonth = MONTH( dtEnd );
    set nMonth = eMonth + 1;
    set sDay = DAY( dtStart );
    set eDay = DAY( dtEnd );
    
    set strSYear = concat( sYear, '' );
    set strEYear = concat( eYear, '' );
    set strNYear = concat( nYear, '' );
    set strSMonth = concat( sMonth, '' );
    set strEMonth = concat( eMonth, '' );
    set strNMonth = concat( nMonth, '' );
    set strSDay = concat( sDay, '' );
    set strEDay = concat( eDay, '' );
    
    set yBegin = concat( strSYear, '-01-01 00:00:00' );
    set yEnd = concat( strNYear, '-01-01 00:00:00' );
    set mBegin = concat( strSYear, '-', strSMonth, '-01 00:00:00' );
    set mEnd = concat( strEYear, '-', strNMonth, '-01 00:00:00' );
    
    case nReportType
        when 1 then #Year
            set strSql = concat( "select c.f1, c.f2, c.f4, d.f4, e.f4,f.f4,g.f4,h.f4 from ( select year( intime ) f1, month( intime ) f2, count( cardno ) f4 from stoprd a where  ( '",
                                 yBegin,
                                 "' <= a.intime and a.intime < '",
                                 yEnd,
                                 "' ) and a.cardkind = '",
                                 strMonthCard,
                                 "' group by year( a.intime ), month( a.intime ) ) c left join ( select year( feetime ) f1, month( feetime ) f2, sum( feenumb ) f4 from feerd where feekind like '",
                                 strMonthCard,
                                 "%' group by year( feetime ), month( feetime ) ) d on c.f1 = d.f1 and c.f2 = d.f2 left join ( select year( intime ) f1, month( intime ) f2, count( cardno ) f4 from stoprd a where  ( '",
                                 yBegin,
                                 "' <= a.intime and a.intime < '",
                                 yEnd,
                                 "' ) and a.cardkind = '",
                                 strTimeCard,
                                 "' group by year( a.intime ), month( a.intime ) ) e on c.f1 = e.f1 and c.f2 = e.f2 left join ( select year( feetime ) f1, month( feetime ) f2, sum( feenumb ) f4 from feerd where feekind like '",
                                 strTimeCard,
                                 "%' group by year( feetime ), month( feetime ) ) f on c.f1 = f.f1 and c.f2 = f.f2 left join ( select year( intime ) f1, month( intime ) f2, count( cardno ) f4 from stoprd a where  ( '",
                                 yBegin,
                                 "' <= a.intime and a.intime < '",
                                 yEnd,
                                 "' ) and a.cardkind = '",
                                 strValueCard,
                                 "' group by year( a.intime ), month( a.intime ) ) g on c.f1 = g.f1 and c.f2 = g.f2 left join ( select year( feetime ) f1, month( feetime ) f2, sum( feenumb ) f4 from feerd where feekind like '",
                                 strValueCard,
                                 "%' group by year( feetime ), month( feetime ) ) h on c.f1 = h.f1 and c.f2 = h.f2" );
        when 2 then #Month
            set strSql =  concat( "select c.f1, c.f2, c.f3, c.f4, d.f4, e.f4,f.f4,g.f4,h.f4 from ( select year( intime ) f1, month( intime ) f2, day( intime ) f3, count( cardno ) f4 from stoprd a where  ( '",
                                  mBegin,
                                  "' <= a.intime and a.intime < '",
                                  mEnd,
                                  "' ) and a.cardkind = '",
                                  strMonthCard,
                                  "'group by year( a.intime ), month( a.intime ), day( intime ) ) c left join ( select year( feetime ) f1, month( feetime ) f2, day( feetime ) f3, sum( feenumb ) f4 from feerd where feekind like '",
                                  strMonthCard,
                                  "%' group by year( feetime ), month( feetime ), day( feetime ) ) d on c.f1 = d.f1 and c.f2 = d.f2 and c.f3 = d.f3 left join ( select year( intime ) f1, month( intime ) f2, day( intime ) f3, count( cardno ) f4 from stoprd a where  ( '",
                                  mBegin,
                                  "' <= a.intime and a.intime < '",
                                  mEnd,
                                  "' ) and a.cardkind = '",
                                  strTimeCard,
                                  "' group by year( a.intime ), month( a.intime ) ) e on c.f1 = e.f1 and c.f2 = e.f2  and c.f3 = e.f3 left join ( select year( feetime ) f1, month( feetime ) f2, day( feetime ) f3, sum( feenumb ) f4 from feerd where feekind like '",
                                  strTimeCard,
                                  "%' group by year( feetime ), month( feetime ) ) f on c.f1 = f.f1 and c.f2 = f.f2  and c.f3 = f.f3 left join ( select year( intime ) f1, month( intime ) f2, day( intime ) f3, count( cardno ) f4 from stoprd a where  ( '",
                                  mBegin,
                                  "' <= a.intime and a.intime < '",
                                  mEnd,
                                  "' ) and a.cardkind = '",
                                  strValueCard,
                                  "' group by year( a.intime ), month( a.intime ) ) g on c.f1 = g.f1 and c.f2 = g.f2  and c.f3 = g.f3 left join ( select year( feetime ) f1, month( feetime ) f2, day( feetime ) f3, sum( feenumb ) f4 from feerd where feekind like '",
                                  strValueCard,
                                  "%' group by year( feetime ), month( feetime ) ) h on c.f1 = h.f1 and c.f2 = h.f2 and c.f3 = h.f3" );
        when 3 then #Day
            set strSql =  concat( "select c.f1, c.f2, c.f3, c.f4, d.f4, e.f4,f.f4,g.f4,h.f4 from ( select year( intime ) f1, month( intime ) f2, day( intime ) f3, count( cardno ) f4 from stoprd a where  ( '",
                                  DATE_FORMAT( dtStart, strFormat ),
                                  "' <= a.intime and a.intime < '",
                                  DATE_FORMAT( dtEnd, strFormat ),
                                  "' ) and a.cardkind = '",
                                  strMonthCard,
                                  "'group by year( a.intime ), month( a.intime ), day( intime ) ) c left join ( select year( feetime ) f1, month( feetime ) f2, day( feetime ) f3, sum( feenumb ) f4 from feerd where feekind like '",
                                  strMonthCard,
                                  "%' group by year( feetime ), month( feetime ), day( feetime ) ) d on c.f1 = d.f1 and c.f2 = d.f2 and c.f3 = d.f3 left join ( select year( intime ) f1, month( intime ) f2, day( intime ) f3, count( cardno ) f4 from stoprd a where  ( '",
                                  DATE_FORMAT( dtStart, strFormat ),
                                  "' <= a.intime and a.intime < '",
                                  DATE_FORMAT( dtEnd, strFormat ),
                                  "' ) and a.cardkind = '",
                                  strTimeCard,
                                  "' group by year( a.intime ), month( a.intime ) ) e on c.f1 = e.f1 and c.f2 = e.f2  and c.f3 = e.f3 left join ( select year( feetime ) f1, month( feetime ) f2, day( feetime ) f3, sum( feenumb ) f4 from feerd where feekind like '",
                                  strTimeCard,
                                  "%' group by year( feetime ), month( feetime ) ) f on c.f1 = f.f1 and c.f2 = f.f2  and c.f3 = f.f3 left join ( select year( intime ) f1, month( intime ) f2, day( intime ) f3, count( cardno ) f4 from stoprd a where  ( '",
                                  DATE_FORMAT( dtStart, strFormat ),
                                  "' <= a.intime and a.intime < '",
                                  DATE_FORMAT( dtEnd, strFormat ),
                                  "' ) and a.cardkind = '",
                                  strValueCard,
                                  "' group by year( a.intime ), month( a.intime ) ) g on c.f1 = g.f1 and c.f2 = g.f2  and c.f3 = g.f3 left join ( select year( feetime ) f1, month( feetime ) f2, day( feetime ) f3, sum( feenumb ) f4 from feerd where feekind like '",
                                  strValueCard,
                                  "%' group by year( feetime ), month( feetime ) ) h on c.f1 = h.f1 and c.f2 = h.f2 and c.f3 = h.f3" );
        when 4 then #Person
            set strSql = concat( "select feeoperator f1, sum( feenumb ) f2 from feerd where feetime between '",
                                 DATE_FORMAT( dtStart, strFormat ),
                                 "' and '",
                                 DATE_FORMAT( dtEnd, strFormat ),
                                 "'" );
    end case;

    SET @sql = strSql;
    PREPARE dyncSql FROM @sql;
    EXECUTE dyncSql;
    DEALLOCATE PREPARE dyncSql;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `InconformityInfo` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`test`@`%`*/ /*!50003 PROCEDURE `InconformityInfo`( strPlate varchar(16 ), strCardID varchar( 32 ) )
BEGIN
declare strType1 varchar( 32 );
declare strType2 varchar( 32 );

-- DECLARE HANDLER syntax Â£∞ÊòéÂºÇÂ∏∏Â§ÑÁêÜÁöÑËØ≠Ê≥ï
-- DECLARE
-- { EXIT | CONTINUE }
-- HANDLER FOR
-- { error-number | { SQLSTATE error-string } | condition }
-- SQL statement

-- DECLARE cursor-name CURSOR FOR SELECT ...;
-- OPEN cursor-name;
-- FETCH cursor-name INTO variable [, variable];

begin

    if exists ( select cardno from monthcard where cardno in ( select cardindex from carinfo where carcp = strplate ) ) then
        set strType1 = 'ÊúàÁßüÂç°';
    elseif exists ( select cardno from savecard where cardno in ( select cardindex from carinfo where carcp = strplate ) ) then
        set strType1 = 'ÂÇ®ÂÄºÂç°';
    elseif exists ( select cardno from tmpcard where cardno in ( select cardindex from carinfo where carcp = strplate ) ) then
        set strType1 = 'ËÆ°Êó∂Âç°';
    end if;
end;

begin
declare a int default 2; -- Temporary variable Scope
set @x = 'sjkdfsd'; -- Session Variable
    if exists ( select cardno from monthcard where cardno in ( strCardID ) ) then
        set strType2= 'ÊúàÁßüÂç°';
    elseif exists ( select cardno from savecard where cardno in ( strCardID ) ) then
        set strType2 = 'ÂÇ®ÂÄºÂç°';
    elseif exists ( select cardno from tmpcard where cardno in ( strCardID ) ) then
        set strType2 = 'ËÆ°Êó∂Âç°';
    end if;
end;

begin
    select a.cardindex, a.carcp, b.username, b.userphone, c.strType1, d.a, d.b, d.c, d.d, d.e from carinfo a 
    join userinfo b on a.carcp = strPlate and a.cardindex = b.cardindex 
    join (select strType1 from dual) c
    join
    ( select a.cardindex a, a.carcp b, b.username c, b.userphone d, c.strType2 e from carinfo a 
    join userinfo b on a.cardindex = strCardID and a.cardindex = b.cardindex 
    join (select strType2 from dual) c ) d;
end;
end */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `MakeLicense` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = gbk */ ;
/*!50003 SET character_set_results = gbk */ ;
/*!50003 SET collation_connection  = gbk_chinese_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`test`@`127.0.0.1`*/ /*!50003 PROCEDURE `MakeLicense`( in ID varchar( 50 ) )
BEGIN 
               if not exists ( select AdministrativeID from License where AdministrativeID = ID ) then 
                   Insert Into License ( AdministrativeID, KeyContent ) values ( ID, NULL );
               end if;
             END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `OperateCarInfo` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`127.0.0.1`*/ /*!50003 PROCEDURE `OperateCarInfo`( in CarID VARCHAR(50), in CarModel VARCHAR(50), 
                                                in CardID VARCHAR(50), in DriveID VARCHAR(50) )
BEGIN
    declare n INT(10) default 1;
    declare strSql VARCHAR( 1024 ) default '';

    set strSql = concat( 'select carid into n from carinfo where carcp =\'', CarID, '\' and cardindex =\'', CardID, '\'' );
    SET @sql = strSql;
    PREPARE dyncSql FROM @sql;
    EXECUTE dyncSql;
    -- select n;
    DEALLOCATE PREPARE dyncSql;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `StartTimer` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `StartTimer`( in bStart bool )
BEGIN
/*
    If bStart = 0 then 
        BEGIN 
            Drop table if exists tmpcardintime;
            Drop event if exists DeleteDataTimer;
            -- SET GLOBAL EVENT_SCHEDULER = FALSE;
        END;
     else 
        BEGIN
           CREATE TABLE if not exists tmpcardintime ( 
            idtmpcardintime int(11) NOT NULL AUTO_INCREMENT,
            cardno varchar(45) NOT NULL,
            intime datetime NOT NULL,
            inshebeiname varchar( 30 ) default null,
            invideo1 longblob,
            PRIMARY KEY ( idtmpcardintime) 
          ) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=gb2312;
        
        -- SET GLOBAL EVENT_SCHEDULER = TRUE; 
      END;
    END IF;    
    */
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `SurplusSpace` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`test`@`%`*/ /*!50003 PROCEDURE `SurplusSpace`( in bSub bool, in nID int)
BEGIN
    declare nUnit int;
    if bSub then 
        set nUnit = -1;
        if exists ( select usedSpace from parkinfo where usedSpace > 0 and parkindex = nID ) then
            update parkinfo set usedSpace = usedSpace + nUnit where parkindex = nID;
        end if;
    else
        set nUnit = 1;
        if exists ( select usedSpace from parkinfo where parknum > usedSpace and parkindex = nID) 

then
            update parkinfo set usedSpace = usedSpace + nUnit where parkindex = nID;
        end if;
    end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Test` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`test`@`%`*/ /*!50003 PROCEDURE `Test`()
BEGIN
 select * from tmpcard;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-08-01 16:17:09
