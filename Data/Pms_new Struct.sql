CREATE DATABASE  IF NOT EXISTS `parkadmin` /*!40100 DEFAULT CHARACTER SET gb2312 */;
USE `parkadmin`;
-- MySQL dump 10.13  Distrib 5.5.16, for Win32 (x86)
--
-- Host: localhost    Database: parkadmin
-- ------------------------------------------------------
-- Server version	5.5.21-log

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
  `zkname` varchar(45) NOT NULL DEFAULT '未知',
  `zkflag` varchar(45) NOT NULL DEFAULT '未知',
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
INSERT INTO `parkdongleinfo` VALUES ('5101070001','成都武侯区肿瘤医院','�EF���(S�X��~�i��B\0vT��x@�xG/');
/*!40000 ALTER TABLE `parkdongleinfo` ENABLE KEYS */;
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
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pmslog`
--

LOCK TABLES `pmslog` WRITE;
/*!40000 ALTER TABLE `pmslog` DISABLE KEYS */;
INSERT INTO `pmslog` VALUES (1,'查看进出记录','select a.cardno, a.cardselfno, a.endtime, b.username, a.cardcomment,  c.carcp, c.carmodel,                           d.inshebeiname, d.intime, d.outshebeiname, d.outtime, d.cardkind                           from monthcard a                           inner join userinfo b on a.cardno = 1118066 and a.cardno = b.cardindex                           inner join carinfo c on a.cardno = c.cardindex                           inner join stoprd d on a.cardno = d.cardno and inshebeiname = C入 and intime = 2012-03-12 14:01:15','2012-03-12 14:01:18'),(2,'查看进出记录','select a.cardno, a.cardselfno, a.endtime, b.username, a.cardcomment,  c.carcp, c.carmodel,                           d.inshebeiname, d.intime, d.outshebeiname, d.outtime, d.cardkind                           from monthcard a                           inner join userinfo b on a.cardno = 1118066 and a.cardno = b.cardindex                           inner join carinfo c on a.cardno = c.cardindex                           inner join stoprd d on a.cardno = d.cardno and inshebeiname = C入 and intime = 2012-03-12 14:03:22','2012-03-12 14:03:45'),(3,'查看进出记录','select a.cardno, a.cardselfno, a.endtime, b.username, a.cardcomment,  c.carcp, c.carmodel,                           d.inshebeiname, d.intime, d.outshebeiname, d.outtime, d.cardkind                           from monthcard a                           inner join userinfo b on a.cardno = 1118066 and a.cardno = b.cardindex                           inner join carinfo c on a.cardno = c.cardindex                           inner join stoprd d on a.cardno = d.cardno and inshebeiname = C入 and intime = 2012-03-12 14:03:20','2012-03-12 14:03:54');
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
  `cardkind` varchar(50) DEFAULT 'EMID卡',
  `cardfeebz` varchar(30) NOT NULL DEFAULT '现场选择',
  `cardselfno` varchar(50) DEFAULT NULL,
  `cardstate` varchar(30) NOT NULL DEFAULT '启用',
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
INSERT INTO `tmpcard` VALUES ('1113554','EMID卡','小型车','未知','启用',0,0,0),('15395143','EMID卡','小型车','未知','启用',0,0,0),('9400338','EMID卡','小型车','','启用',0,0,0);
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312 COMMENT='黑名单';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `blacklist`
--

LOCK TABLES `blacklist` WRITE;
/*!40000 ALTER TABLE `blacklist` DISABLE KEYS */;
/*!40000 ALTER TABLE `blacklist` ENABLE KEYS */;
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
  `parkname` varchar(30) NOT NULL DEFAULT '新建停车场',
  `usedSpace` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`parkindex`),
  KEY `shebeiid` (`shebeiid`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `parkinfo`
--

LOCK TABLES `parkinfo` WRITE;
/*!40000 ALTER TABLE `parkinfo` DISABLE KEYS */;
INSERT INTO `parkinfo` VALUES (23,104,2000,'最外围',0),(24,105,1000,'停车场A',0),(25,106,500,'停车场B',0),(26,107,500,'停车场C',12),(27,114,400,'停车场A1',0),(28,115,200,'停车场A2',0);
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
  `shebeiname` varchar(30) NOT NULL DEFAULT '未知',
  PRIMARY KEY (`cardsetind`),
  KEY `roadconind` (`roadconind`),
  KEY `cardno_starttime_endtime` (`cardno`,`starttime`,`endtime`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=71 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cardright`
--

LOCK TABLES `cardright` WRITE;
/*!40000 ALTER TABLE `cardright` DISABLE KEYS */;
INSERT INTO `cardright` VALUES (1,'1118066',108,'00:00:00','23:59:59','B入'),(2,'1118066',109,'00:00:00','23:59:59','A入'),(3,'1118066',110,'00:00:00','23:59:59','B出'),(4,'1118066',111,'00:00:00','23:59:59','C入'),(5,'1118066',112,'00:00:00','23:59:59','C出'),(6,'1118066',113,'00:00:00','23:59:59','A出'),(7,'1118066',118,'00:00:00','23:59:59','A2入'),(8,'1118066',119,'00:00:00','23:59:59','A2出'),(9,'1118066',120,'00:00:00','23:59:59','A1入'),(10,'1118066',121,'00:00:00','23:59:59','A2出'),(11,'1105986',108,'00:00:00','23:59:59','B入'),(12,'1105986',109,'00:00:00','23:59:59','A入'),(13,'1105986',110,'00:00:00','23:59:59','B出'),(14,'1105986',111,'00:00:00','23:59:59','C入'),(15,'1105986',112,'00:00:00','23:59:59','C出'),(16,'1105986',113,'00:00:00','23:59:59','A出'),(17,'1105986',118,'00:00:00','23:59:59','A2入'),(18,'1105986',119,'00:00:00','23:59:59','A2出'),(19,'1105986',120,'00:00:00','23:59:59','A1入'),(20,'1105986',121,'00:00:00','23:59:59','A2出'),(21,'1109682',108,'00:00:00','23:59:59','B入'),(22,'1109682',109,'00:00:00','23:59:59','A入'),(23,'1109682',110,'00:00:00','23:59:59','B出'),(24,'1109682',111,'00:00:00','23:59:59','C入'),(25,'1109682',112,'00:00:00','23:59:59','C出'),(26,'1109682',113,'00:00:00','23:59:59','A出'),(27,'1109682',118,'00:00:00','23:59:59','A2入'),(28,'1109682',119,'00:00:00','23:59:59','A2出'),(29,'1109682',120,'00:00:00','23:59:59','A1入'),(30,'1109682',121,'00:00:00','23:59:59','A2出'),(31,'9400338',108,'00:00:00','23:59:59','B入'),(32,'9400338',109,'00:00:00','23:59:59','A入'),(33,'9400338',110,'00:00:00','23:59:59','B出'),(34,'9400338',111,'00:00:00','23:59:59','C入'),(35,'9400338',112,'00:00:00','23:59:59','C出'),(36,'9400338',113,'00:00:00','23:59:59','A出'),(37,'9400338',118,'00:00:00','23:59:59','A2入'),(38,'9400338',119,'00:00:00','23:59:59','A2出'),(39,'9400338',120,'00:00:00','23:59:59','A1入'),(40,'9400338',121,'00:00:00','23:59:59','A2出'),(41,'1113554',108,'00:00:00','23:59:59','B入'),(42,'1113554',109,'00:00:00','23:59:59','A入'),(43,'1113554',110,'00:00:00','23:59:59','B出'),(44,'1113554',111,'00:00:00','23:59:59','C入'),(45,'1113554',112,'00:00:00','23:59:59','C出'),(46,'1113554',113,'00:00:00','23:59:59','A出'),(47,'1113554',118,'00:00:00','23:59:59','A2入'),(48,'1113554',119,'00:00:00','23:59:59','A2出'),(49,'1113554',120,'00:00:00','23:59:59','A1入'),(50,'1113554',121,'00:00:00','23:59:59','A2出'),(51,'15395143',108,'00:00:00','23:59:59','B入'),(52,'15395143',109,'00:00:00','23:59:59','A入'),(53,'15395143',110,'00:00:00','23:59:59','B出'),(54,'15395143',111,'00:00:00','23:59:59','C入'),(55,'15395143',112,'00:00:00','23:59:59','C出'),(56,'15395143',113,'00:00:00','23:59:59','A出'),(57,'15395143',118,'00:00:00','23:59:59','A2入'),(58,'15395143',119,'00:00:00','23:59:59','A2出'),(59,'15395143',120,'00:00:00','23:59:59','A1入'),(60,'15395143',121,'00:00:00','23:59:59','A2出'),(61,'222656',108,'00:00:00','23:59:59','B入'),(62,'222656',109,'00:00:00','23:59:59','A入'),(63,'222656',110,'00:00:00','23:59:59','B出'),(64,'222656',111,'00:00:00','23:59:59','C入'),(65,'222656',112,'00:00:00','23:59:59','C出'),(66,'222656',113,'00:00:00','23:59:59','A出'),(67,'222656',118,'00:00:00','23:59:59','A2入'),(68,'222656',119,'00:00:00','23:59:59','A2出'),(69,'222656',120,'00:00:00','23:59:59','A1入'),(70,'222656',121,'00:00:00','23:59:59','A2出');
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
  `feekind` varchar(30) NOT NULL DEFAULT '未知',
  `feeoperator` varchar(30) NOT NULL DEFAULT '未知',
  `cardno` varchar(50) NOT NULL DEFAULT '未知',
  `timelen` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`feeindex`),
  KEY `feetime` (`feetime`),
  KEY `cardno` (`cardno`)
) ENGINE=InnoDB AUTO_INCREMENT=26 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `feerd`
--

LOCK TABLES `feerd` WRITE;
/*!40000 ALTER TABLE `feerd` DISABLE KEYS */;
INSERT INTO `feerd` VALUES (1,0,'2012-03-12 14:09:23','计时卡收费','停车场管理员','9400338',0),(2,0,'2012-03-12 14:09:25','计时卡收费','停车场管理员','9400338',0),(3,0,'2012-03-12 14:09:27','计时卡收费','停车场管理员','9400338',0),(4,0,'2012-03-12 14:09:31','计时卡收费','停车场管理员','9400338',0),(5,0,'2012-03-12 14:09:33','计时卡收费','停车场管理员','9400338',0),(6,0,'2012-03-12 14:09:35','计时卡收费','停车场管理员','9400338',0),(7,0,'2012-03-12 14:09:37','计时卡收费','停车场管理员','9400338',0),(8,0,'2012-03-12 14:09:39','计时卡收费','停车场管理员','9400338',0),(9,0,'2012-03-12 14:09:41','计时卡收费','停车场管理员','9400338',0),(10,0,'2012-03-12 14:09:43','计时卡收费','停车场管理员','9400338',0),(11,0,'2012-03-12 14:09:45','计时卡收费','停车场管理员','9400338',0),(12,0,'2012-03-12 14:09:46','计时卡收费','停车场管理员','9400338',0),(13,0,'2012-03-12 14:09:48','计时卡收费','停车场管理员','9400338',0),(14,0,'2012-03-12 14:09:49','计时卡收费','停车场管理员','9400338',0),(15,0,'2012-03-12 14:09:51','计时卡收费','停车场管理员','9400338',0),(16,0,'2012-03-12 14:09:53','计时卡收费','停车场管理员','9400338',0),(17,0,'2012-03-12 14:09:54','计时卡收费','停车场管理员','9400338',0),(18,0,'2012-03-12 14:09:56','计时卡收费','停车场管理员','9400338',0),(19,0,'2012-03-12 14:09:58','计时卡收费','停车场管理员','9400338',0),(20,0,'2012-03-12 14:09:59','计时卡收费','停车场管理员','9400338',0),(21,0,'2012-03-12 14:10:01','计时卡收费','停车场管理员','9400338',0),(22,0,'2012-03-12 14:10:03','计时卡收费','停车场管理员','9400338',0),(23,0,'2012-03-12 14:10:04','计时卡收费','停车场管理员','9400338',0),(24,0,'2012-03-12 14:10:06','计时卡收费','停车场管理员','9400338',0),(25,0,'2012-03-12 14:10:07','计时卡收费','停车场管理员','9400338',0);
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
  `operatorname` varchar(50) NOT NULL DEFAULT '未知',
  `operatorphone` varchar(50) DEFAULT NULL,
  `operatorsex` varchar(50) DEFAULT '男',
  `operatoraddress` varchar(50) DEFAULT NULL,
  `operatorpassword` varchar(50) DEFAULT '123',
  `qxgl` tinyint(1) NOT NULL DEFAULT '0' COMMENT '权限管理',
  `cardgl` tinyint(1) NOT NULL DEFAULT '0' COMMENT '卡票管理',
  `exitgl` tinyint(1) NOT NULL DEFAULT '0' COMMENT '退出系统',
  `datagl` tinyint(1) NOT NULL DEFAULT '0' COMMENT '数据维护',
  `setgl` tinyint(1) NOT NULL DEFAULT '0' COMMENT '高级设置',
  `sfgl` tinyint(1) NOT NULL DEFAULT '0' COMMENT '查询报表',
  `operatorright` varchar(50) NOT NULL DEFAULT '普通用户',
  `sysinfo` tinyint(1) NOT NULL DEFAULT '0' COMMENT '系统日志',
  `feerate` tinyint(1) NOT NULL DEFAULT '0' COMMENT '费率设置',
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
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `operator`
--

LOCK TABLES `operator` WRITE;
/*!40000 ALTER TABLE `operator` DISABLE KEYS */;
INSERT INTO `operator` VALUES (1,'系统管理员','','男','','85236997123456',-1,0,-1,-1,0,0,'超级用户',-1,-1,NULL,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,'18804'),(2,'停车场管理员','','男','','aaa',-1,0,-1,-1,0,0,'普通用户',-1,-1,NULL,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,''),(3,'维护人员','','男','','aaa',-1,0,-1,-1,0,0,'超级用户',-1,-1,NULL,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,'17338'),(4,'大门一班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,''),(5,'大门二班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,''),(6,'大门三班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,''),(7,'后门一班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,''),(8,'后门二班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,''),(9,'南门一班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,''),(10,'南门二班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,'');
/*!40000 ALTER TABLE `operator` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `feerate1`
--

DROP TABLE IF EXISTS `feerate1`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `feerate1` (
  `rparkid` int(11) DEFAULT '0' COMMENT 'Í£',
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
  `freet` int(11) DEFAULT '0' COMMENT '¿íÏÞÊ±¼ä',
  `fdtimestar` time DEFAULT '00:00:00',
  `fdtimeend` time DEFAULT '23:59:59',
  `dldwt` int(11) DEFAULT '0',
  `dldwf` int(11) DEFAULT '0',
  `dlxianfee` int(11) DEFAULT '0',
  `dwdwt` int(11) DEFAULT '0',
  `dwdwf` int(11) DEFAULT '0',
  `dwxianfee` int(11) DEFAULT '0',
  `firstjstime` int(11) DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `feerate1`
--

LOCK TABLES `feerate1` WRITE;
/*!40000 ALTER TABLE `feerate1` DISABLE KEYS */;
INSERT INTO `feerate1` VALUES (5,0,13,14,15,16,17,18,19,20,21,22,23,24,0,0,0,0,0,0,0,0,0,0,0,0,27,28,11,12,'00:00:00','23:59:59',25,26,0,0,0,0,29),(5,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(5,2,240,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1440,140,0,0,'00:00:00','23:59:59',120,10,0,0,0,0,0),(5,3,60,40,120,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,5,'00:00:00','23:59:59',0,0,0,0,0,0,0),(5,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(5,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(6,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(6,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(6,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(7,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(7,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(7,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(7,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(7,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(7,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(21,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(21,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(21,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(21,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(21,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(21,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(21,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(21,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(22,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(22,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(22,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(22,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(22,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(22,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(22,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(23,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(23,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(23,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(23,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(23,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(23,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(23,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(24,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(24,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(24,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(24,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(24,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(24,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(24,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(25,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(25,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(25,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(25,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(25,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(25,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(25,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(26,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(26,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(26,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(26,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(26,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(26,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(26,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(27,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(27,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(27,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(27,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(27,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(27,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(27,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(27,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(28,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(28,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(28,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(28,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(28,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(28,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0),(28,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'00:00:00','23:59:59',0,0,0,0,0,0,0);
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
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(1) NOT NULL DEFAULT '0',
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
 if ( ( '计时卡' = new.cardkind ) && Exists( Select Table_name from information_schema.tables as a where a.table_name = 'tmpcardintime' ) )  then
    insert tmpcardintime( cardno, intime ) values( new.cardno, new.intime );
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `parkadmin`.`UpdateStoprd`
AFTER UPDATE ON `parkadmin`.`stoprd`
FOR EACH ROW
BEGIN
 if ( ( '计时卡' = new.cardkind ) && Exists( Select Table_name from information_schema.tables as a where a.table_name = 'tmpcardintime' ) ) then
  if ( old.invideo1 is null && new.invideo1 is not null ) then
    update tmpcardintime set invideo1 = new.invideo1 where cardno = old.cardno and intime = old.intime;
    elseif ( new.MayDelete ) then
    delete from tmpcardintime where cardno = old.cardno and intime <= old.intime;
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
  `carcp` varchar(50) NOT NULL DEFAULT '未知',
  `carmodel` varchar(50) NOT NULL DEFAULT '小型车',
  `carpic` longblob,
  `cardindex` varchar(50) NOT NULL DEFAULT '0',
  `carhaoma` varchar(50) NOT NULL DEFAULT '未知',
  PRIMARY KEY (`carid`),
  KEY `cardindex` (`cardindex`),
  KEY `carcp` (`carcp`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `carinfo`
--

LOCK TABLES `carinfo` WRITE;
/*!40000 ALTER TABLE `carinfo` DISABLE KEYS */;
INSERT INTO `carinfo` VALUES (1,'未知','小型车',NULL,'1109682','未知'),(2,'渝F41093','小型车',NULL,'1105986','未知'),(4,'未知','小型车',NULL,'222656','未知'),(5,'未知','未知',NULL,'9400338','未知'),(6,'未知','小型车',NULL,'1118066','未知');
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
INSERT INTO `feeratebackup` VALUES (28,0,0,0,0,7,0,0),(28,0,1,1,2,0,0,0),(28,0,2,0,0,0,0,0),(28,0,3,0,0,0,0,0),(28,0,4,0,0,0,0,0),(28,0,5,0,0,0,0,0),(28,0,6,0,0,0,0,0),(28,0,7,0,0,0,0,0),(28,0,8,0,0,0,0,0),(28,1,0,0,0,7,0,0),(28,1,1,1,2,0,0,0),(28,1,2,0,0,0,0,0),(28,1,3,0,0,0,0,0),(28,1,4,0,0,0,0,0),(28,1,5,0,0,0,0,0),(28,1,6,0,0,0,0,0),(28,1,7,0,0,0,0,0),(28,1,8,0,0,0,0,0),(28,2,0,0,0,2,0,1),(28,2,1,1,2,6,0,0),(28,2,2,3,5,1,2,0),(28,2,3,6,1000,2,3,0),(28,2,4,0,0,0,0,0),(28,2,5,0,0,0,0,0),(28,2,6,0,0,0,0,0),(28,2,7,0,0,0,0,0),(28,2,8,0,0,0,0,0),(28,3,0,0,0,7,0,0),(28,3,1,1,2,0,0,0),(28,3,2,0,0,0,0,0),(28,3,3,0,0,0,0,0),(28,3,4,0,0,0,0,0),(28,3,5,0,0,0,0,0),(28,3,6,0,0,0,0,0),(28,3,7,0,0,0,0,0),(28,3,8,0,0,0,0,0),(28,4,0,0,0,7,0,0),(28,4,1,1,2,0,0,0),(28,4,2,0,0,0,0,0),(28,4,3,0,0,0,0,0),(28,4,4,0,0,0,0,0),(28,4,5,0,0,0,0,0),(28,4,6,0,0,0,0,0),(28,4,7,0,0,0,0,0),(28,4,8,0,0,0,0,0),(28,5,0,0,0,7,0,0),(28,5,1,1,2,0,0,0),(28,5,2,0,0,0,0,0),(28,5,3,0,0,0,0,0),(28,5,4,0,0,0,0,0),(28,5,5,0,0,0,0,0),(28,5,6,0,0,0,0,0),(28,5,7,0,0,0,0,0),(28,5,8,0,0,0,0,0),(28,6,0,0,0,7,0,0),(28,6,1,1,2,0,0,0),(28,6,2,0,0,0,0,0),(28,6,3,0,0,0,0,0),(28,6,4,0,0,0,0,0),(28,6,5,0,0,0,0,0),(28,6,6,0,0,0,0,0),(28,6,7,0,0,0,0,0),(28,6,8,0,0,0,0,0),(28,7,0,0,0,7,0,0),(28,7,1,1,2,0,0,0),(28,7,2,0,0,0,0,0),(28,7,3,0,0,0,0,0),(28,7,4,0,0,0,0,0),(28,7,5,0,0,0,0,0),(28,7,6,0,0,0,0,0),(28,7,7,0,0,0,0,0),(28,7,8,0,0,0,0,0);
/*!40000 ALTER TABLE `feeratebackup` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `license`
--

DROP TABLE IF EXISTS `license`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `license` (
  `AdministrativeID` varchar(50) NOT NULL COMMENT '(区号) + 停车场编号\n\n510107 + 0001\n\n510107 + 9999',
  `KeyContent` blob,
  PRIMARY KEY (`AdministrativeID`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `license`
--

LOCK TABLES `license` WRITE;
/*!40000 ALTER TABLE `license` DISABLE KEYS */;
INSERT INTO `license` VALUES ('5101070001','UE1TWuY2dBvFzgp4xxrpwF5ja0kLFWiDCSqganFX6WA9UsOD+fIv2RKQzcXpNcxJXK6Zhy6ckRiApYkljSDOf/Uq3RltHTs/zn3VurgbG2XyNO1Gwpx/AEhxAYXm3yW3vfEUA7vzKersXPmxwZKGdlG0tnvFu+bYzpKP7UNA9TXF+mgv6Jftm19UhX3+pEKdNseDYJAq9lBzIDAd');
/*!40000 ALTER TABLE `license` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `savecard`
--

DROP TABLE IF EXISTS `savecard`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `savecard` (
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `cardstate` varchar(30) NOT NULL DEFAULT '启用',
  `cardkind` varchar(30) DEFAULT 'EMID卡',
  `cardselfno` varchar(50) DEFAULT NULL,
  `cardcomment` varchar(100) DEFAULT NULL,
  `cardcreator` varchar(30) DEFAULT NULL,
  `cardfeebz` varchar(30) NOT NULL DEFAULT '现场选择',
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
INSERT INTO `savecard` VALUES ('222656','启用','EMID卡','未知','未知','停车场管理员','小型车',0,0,0,0);
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
  `invideo1` longblob,
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
  `infooperator` varchar(30) NOT NULL DEFAULT '未知',
  `infokind` varchar(50) NOT NULL DEFAULT '未知',
  `infotext` varchar(150) NOT NULL DEFAULT '未知',
  `infotime` datetime NOT NULL,
  `infopic1` longblob,
  `infopic2` longblob,
  `infopic3` longblob,
  `infopic4` longblob,
  PRIMARY KEY (`infoindex`),
  KEY `infotime` (`infotime`),
  KEY `infooperator` (`infooperator`)
) ENGINE=InnoDB AUTO_INCREMENT=39 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sysinfo`
--

LOCK TABLES `sysinfo` WRITE;
/*!40000 ALTER TABLE `sysinfo` DISABLE KEYS */;
INSERT INTO `sysinfo` VALUES (1,'停车场管理员','换班记录','登录系统成功','2012-03-12 13:55:58',NULL,NULL,NULL,NULL),(2,'停车场管理员','换班记录','登录系统成功','2012-03-12 14:01:00',NULL,NULL,NULL,NULL),(3,'停车场管理员','换班记录','登录系统成功','2012-03-12 14:02:46',NULL,NULL,NULL,NULL),(4,'停车场管理员','换班记录','退出软件','2012-03-12 14:23:47',NULL,NULL,NULL,NULL),(5,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:01:14',NULL,NULL,NULL,NULL),(6,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:03:14',NULL,NULL,NULL,NULL),(7,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:05:29',NULL,NULL,NULL,NULL),(8,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:07:12',NULL,NULL,NULL,NULL),(9,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:10:10',NULL,NULL,NULL,NULL),(10,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:11:30',NULL,NULL,NULL,NULL),(11,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:22:00',NULL,NULL,NULL,NULL),(12,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:23:58',NULL,NULL,NULL,NULL),(13,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:27:37',NULL,NULL,NULL,NULL),(14,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:29:08',NULL,NULL,NULL,NULL),(15,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:30:47',NULL,NULL,NULL,NULL),(16,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:35:48',NULL,NULL,NULL,NULL),(17,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:37:46',NULL,NULL,NULL,NULL),(18,'停车场管理员','换班记录','退出软件','2012-03-12 15:39:14',NULL,NULL,NULL,NULL),(19,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:41:10',NULL,NULL,NULL,NULL),(20,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:47:41',NULL,NULL,NULL,NULL),(21,'停车场管理员','换班记录','登录系统成功','2012-03-12 15:49:36',NULL,NULL,NULL,NULL),(22,'停车场管理员','换班记录','登录系统成功','2012-03-12 16:00:22',NULL,NULL,NULL,NULL),(23,'停车场管理员','换班记录','登录系统成功','2012-03-12 16:06:33',NULL,NULL,NULL,NULL),(24,'停车场管理员','换班记录','登录系统成功','2012-03-12 16:10:31',NULL,NULL,NULL,NULL),(25,'停车场管理员','换班记录','登录系统成功','2012-03-12 16:16:21',NULL,NULL,NULL,NULL),(26,'停车场管理员','换班记录','登录系统成功','2012-03-12 16:25:32',NULL,NULL,NULL,NULL),(27,'停车场管理员','换班记录','登录系统成功','2012-03-12 16:26:48',NULL,NULL,NULL,NULL),(28,'停车场管理员','换班记录','登录系统成功','2012-03-12 16:29:28',NULL,NULL,NULL,NULL),(29,'停车场管理员','换班记录','登录系统成功','2012-03-12 16:35:06',NULL,NULL,NULL,NULL),(30,'停车场管理员','换班记录','登录系统成功','2012-03-12 16:36:48',NULL,NULL,NULL,NULL),(31,'停车场管理员','换班记录','退出软件','2012-03-12 16:46:52',NULL,NULL,NULL,NULL),(32,'停车场管理员','换班记录','登录系统成功','2012-03-12 16:52:49',NULL,NULL,NULL,NULL),(33,'停车场管理员','换班记录','退出软件','2012-03-12 17:00:49',NULL,NULL,NULL,NULL),(34,'停车场管理员','换班记录','登录系统成功','2012-03-12 17:09:14',NULL,NULL,NULL,NULL),(35,'停车场管理员','换班记录','退出软件','2012-03-12 17:15:05',NULL,NULL,NULL,NULL),(36,'停车场管理员','换班记录','登录系统成功','2012-03-13 14:19:58',NULL,NULL,NULL,NULL),(37,'停车场管理员','换班记录','登录系统成功','2012-03-13 15:17:01',NULL,NULL,NULL,NULL),(38,'停车场管理员','换班记录','登录系统成功','2012-03-13 15:18:02',NULL,NULL,NULL,NULL);
/*!40000 ALTER TABLE `sysinfo` ENABLE KEYS */;
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
) ENGINE=InnoDB AUTO_INCREMENT=1975 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `feerate`
--

LOCK TABLES `feerate` WRITE;
/*!40000 ALTER TABLE `feerate` DISABLE KEYS */;
INSERT INTO `feerate` VALUES (23,0,0,0,0,7,0,0,1323),(23,0,1,1,2,0,0,0,1324),(23,0,2,0,0,0,0,0,1325),(23,0,3,0,0,0,0,0,1326),(23,0,4,0,0,0,0,0,1327),(23,0,5,0,0,0,0,0,1328),(23,0,6,0,0,0,0,0,1329),(23,0,7,0,0,0,0,0,1330),(23,0,8,0,0,0,0,0,1331),(23,1,0,0,0,7,0,0,1332),(23,1,1,1,2,0,0,0,1333),(23,1,2,0,0,0,0,0,1334),(23,1,3,0,0,0,0,0,1335),(23,1,4,0,0,0,0,0,1336),(23,1,5,0,0,0,0,0,1337),(23,1,6,0,0,0,0,0,1338),(23,1,7,0,0,0,0,0,1339),(23,1,8,0,0,0,0,0,1340),(23,2,0,0,0,2,0,1,1341),(23,2,1,1,2,6,0,0,1342),(23,2,2,3,5,1,2,0,1343),(23,2,3,6,1000,2,3,0,1344),(23,2,4,0,0,0,0,0,1345),(23,2,5,0,0,0,0,0,1346),(23,2,6,0,0,0,0,0,1347),(23,2,7,0,0,0,0,0,1348),(23,2,8,0,0,0,0,0,1349),(23,3,0,0,0,7,0,0,1350),(23,3,1,1,2,0,0,0,1351),(23,3,2,0,0,0,0,0,1352),(23,3,3,0,0,0,0,0,1353),(23,3,4,0,0,0,0,0,1354),(23,3,5,0,0,0,0,0,1355),(23,3,6,0,0,0,0,0,1356),(23,3,7,0,0,0,0,0,1357),(23,3,8,0,0,0,0,0,1358),(23,4,0,0,0,7,0,0,1359),(23,4,1,1,2,0,0,0,1360),(23,4,2,0,0,0,0,0,1361),(23,4,3,0,0,0,0,0,1362),(23,4,4,0,0,0,0,0,1363),(23,4,5,0,0,0,0,0,1364),(23,4,6,0,0,0,0,0,1365),(23,4,7,0,0,0,0,0,1366),(23,4,8,0,0,0,0,0,1367),(23,5,0,0,0,7,0,0,1368),(23,5,1,1,2,0,0,0,1369),(23,5,2,0,0,0,0,0,1370),(23,5,3,0,0,0,0,0,1371),(23,5,4,0,0,0,0,0,1372),(23,5,5,0,0,0,0,0,1373),(23,5,6,0,0,0,0,0,1374),(23,5,7,0,0,0,0,0,1375),(23,5,8,0,0,0,0,0,1376),(23,6,0,0,0,7,0,0,1377),(23,6,1,1,2,0,0,0,1378),(23,6,2,0,0,0,0,0,1379),(23,6,3,0,0,0,0,0,1380),(23,6,4,0,0,0,0,0,1381),(23,6,5,0,0,0,0,0,1382),(23,6,6,0,0,0,0,0,1383),(23,6,7,0,0,0,0,0,1384),(23,6,8,0,0,0,0,0,1385),(23,7,0,0,0,7,0,0,1386),(23,7,1,1,2,0,0,0,1387),(23,7,2,0,0,0,0,0,1388),(23,7,3,0,0,0,0,0,1389),(23,7,4,0,0,0,0,0,1390),(23,7,5,0,0,0,0,0,1391),(23,7,6,0,0,0,0,0,1392),(23,7,7,0,0,0,0,0,1393),(23,7,8,0,0,0,0,0,1394),(24,0,0,0,0,7,0,0,1450),(24,0,1,1,2,0,0,0,1451),(24,0,2,0,0,0,0,0,1452),(24,0,3,0,0,0,0,0,1453),(24,0,4,0,0,0,0,0,1454),(24,0,5,0,0,0,0,0,1455),(24,0,6,0,0,0,0,0,1456),(24,0,7,0,0,0,0,0,1457),(24,0,8,0,0,0,0,0,1458),(24,1,0,0,0,7,0,0,1459),(24,1,1,1,2,0,0,0,1460),(24,1,2,0,0,0,0,0,1461),(24,1,3,0,0,0,0,0,1462),(24,1,4,0,0,0,0,0,1463),(24,1,5,0,0,0,0,0,1464),(24,1,6,0,0,0,0,0,1465),(24,1,7,0,0,0,0,0,1466),(24,1,8,0,0,0,0,0,1467),(24,2,0,0,0,2,0,1,1468),(24,2,1,1,2,6,0,0,1469),(24,2,2,3,5,1,2,0,1470),(24,2,3,6,1000,2,3,0,1471),(24,2,4,0,0,0,0,0,1472),(24,2,5,0,0,0,0,0,1473),(24,2,6,0,0,0,0,0,1474),(24,2,7,0,0,0,0,0,1475),(24,2,8,0,0,0,0,0,1476),(24,3,0,0,0,7,0,0,1477),(24,3,1,1,2,0,0,0,1478),(24,3,2,0,0,0,0,0,1479),(24,3,3,0,0,0,0,0,1480),(24,3,4,0,0,0,0,0,1481),(24,3,5,0,0,0,0,0,1482),(24,3,6,0,0,0,0,0,1483),(24,3,7,0,0,0,0,0,1484),(24,3,8,0,0,0,0,0,1485),(24,4,0,0,0,7,0,0,1486),(24,4,1,1,2,0,0,0,1487),(24,4,2,0,0,0,0,0,1488),(24,4,3,0,0,0,0,0,1489),(24,4,4,0,0,0,0,0,1490),(24,4,5,0,0,0,0,0,1491),(24,4,6,0,0,0,0,0,1492),(24,4,7,0,0,0,0,0,1493),(24,4,8,0,0,0,0,0,1494),(24,5,0,0,0,7,0,0,1495),(24,5,1,1,2,0,0,0,1496),(24,5,2,0,0,0,0,0,1497),(24,5,3,0,0,0,0,0,1498),(24,5,4,0,0,0,0,0,1499),(24,5,5,0,0,0,0,0,1500),(24,5,6,0,0,0,0,0,1501),(24,5,7,0,0,0,0,0,1502),(24,5,8,0,0,0,0,0,1503),(24,6,0,0,0,7,0,0,1504),(24,6,1,1,2,0,0,0,1505),(24,6,2,0,0,0,0,0,1506),(24,6,3,0,0,0,0,0,1507),(24,6,4,0,0,0,0,0,1508),(24,6,5,0,0,0,0,0,1509),(24,6,6,0,0,0,0,0,1510),(24,6,7,0,0,0,0,0,1511),(24,6,8,0,0,0,0,0,1512),(24,7,0,0,0,7,0,0,1513),(24,7,1,1,2,0,0,0,1514),(24,7,2,0,0,0,0,0,1515),(24,7,3,0,0,0,0,0,1516),(24,7,4,0,0,0,0,0,1517),(24,7,5,0,0,0,0,0,1518),(24,7,6,0,0,0,0,0,1519),(24,7,7,0,0,0,0,0,1520),(24,7,8,0,0,0,0,0,1521),(25,0,0,0,0,7,0,0,1577),(25,0,1,1,2,0,0,0,1578),(25,0,2,0,0,0,0,0,1579),(25,0,3,0,0,0,0,0,1580),(25,0,4,0,0,0,0,0,1581),(25,0,5,0,0,0,0,0,1582),(25,0,6,0,0,0,0,0,1583),(25,0,7,0,0,0,0,0,1584),(25,0,8,0,0,0,0,0,1585),(25,1,0,0,0,7,0,0,1586),(25,1,1,1,2,0,0,0,1587),(25,1,2,0,0,0,0,0,1588),(25,1,3,0,0,0,0,0,1589),(25,1,4,0,0,0,0,0,1590),(25,1,5,0,0,0,0,0,1591),(25,1,6,0,0,0,0,0,1592),(25,1,7,0,0,0,0,0,1593),(25,1,8,0,0,0,0,0,1594),(25,2,0,0,0,2,0,1,1595),(25,2,1,1,2,6,0,0,1596),(25,2,2,3,5,1,2,0,1597),(25,2,3,6,1000,2,3,0,1598),(25,2,4,0,0,0,0,0,1599),(25,2,5,0,0,0,0,0,1600),(25,2,6,0,0,0,0,0,1601),(25,2,7,0,0,0,0,0,1602),(25,2,8,0,0,0,0,0,1603),(25,3,0,0,0,7,0,0,1604),(25,3,1,1,2,0,0,0,1605),(25,3,2,0,0,0,0,0,1606),(25,3,3,0,0,0,0,0,1607),(25,3,4,0,0,0,0,0,1608),(25,3,5,0,0,0,0,0,1609),(25,3,6,0,0,0,0,0,1610),(25,3,7,0,0,0,0,0,1611),(25,3,8,0,0,0,0,0,1612),(25,4,0,0,0,7,0,0,1613),(25,4,1,1,2,0,0,0,1614),(25,4,2,0,0,0,0,0,1615),(25,4,3,0,0,0,0,0,1616),(25,4,4,0,0,0,0,0,1617),(25,4,5,0,0,0,0,0,1618),(25,4,6,0,0,0,0,0,1619),(25,4,7,0,0,0,0,0,1620),(25,4,8,0,0,0,0,0,1621),(25,5,0,0,0,7,0,0,1622),(25,5,1,1,2,0,0,0,1623),(25,5,2,0,0,0,0,0,1624),(25,5,3,0,0,0,0,0,1625),(25,5,4,0,0,0,0,0,1626),(25,5,5,0,0,0,0,0,1627),(25,5,6,0,0,0,0,0,1628),(25,5,7,0,0,0,0,0,1629),(25,5,8,0,0,0,0,0,1630),(25,6,0,0,0,7,0,0,1631),(25,6,1,1,2,0,0,0,1632),(25,6,2,0,0,0,0,0,1633),(25,6,3,0,0,0,0,0,1634),(25,6,4,0,0,0,0,0,1635),(25,6,5,0,0,0,0,0,1636),(25,6,6,0,0,0,0,0,1637),(25,6,7,0,0,0,0,0,1638),(25,6,8,0,0,0,0,0,1639),(25,7,0,0,0,7,0,0,1640),(25,7,1,1,2,0,0,0,1641),(25,7,2,0,0,0,0,0,1642),(25,7,3,0,0,0,0,0,1643),(25,7,4,0,0,0,0,0,1644),(25,7,5,0,0,0,0,0,1645),(25,7,6,0,0,0,0,0,1646),(25,7,7,0,0,0,0,0,1647),(25,7,8,0,0,0,0,0,1648),(26,0,0,0,0,7,0,0,1704),(26,0,1,1,2,0,0,0,1705),(26,0,2,0,0,0,0,0,1706),(26,0,3,0,0,0,0,0,1707),(26,0,4,0,0,0,0,0,1708),(26,0,5,0,0,0,0,0,1709),(26,0,6,0,0,0,0,0,1710),(26,0,7,0,0,0,0,0,1711),(26,0,8,0,0,0,0,0,1712),(26,1,0,0,0,7,0,0,1713),(26,1,1,1,2,0,0,0,1714),(26,1,2,0,0,0,0,0,1715),(26,1,3,0,0,0,0,0,1716),(26,1,4,0,0,0,0,0,1717),(26,1,5,0,0,0,0,0,1718),(26,1,6,0,0,0,0,0,1719),(26,1,7,0,0,0,0,0,1720),(26,1,8,0,0,0,0,0,1721),(26,2,0,0,0,2,0,1,1722),(26,2,1,1,2,6,0,0,1723),(26,2,2,3,5,1,2,0,1724),(26,2,3,6,1000,2,3,0,1725),(26,2,4,0,0,0,0,0,1726),(26,2,5,0,0,0,0,0,1727),(26,2,6,0,0,0,0,0,1728),(26,2,7,0,0,0,0,0,1729),(26,2,8,0,0,0,0,0,1730),(26,3,0,0,0,7,0,0,1731),(26,3,1,1,2,0,0,0,1732),(26,3,2,0,0,0,0,0,1733),(26,3,3,0,0,0,0,0,1734),(26,3,4,0,0,0,0,0,1735),(26,3,5,0,0,0,0,0,1736),(26,3,6,0,0,0,0,0,1737),(26,3,7,0,0,0,0,0,1738),(26,3,8,0,0,0,0,0,1739),(26,4,0,0,0,7,0,0,1740),(26,4,1,1,2,0,0,0,1741),(26,4,2,0,0,0,0,0,1742),(26,4,3,0,0,0,0,0,1743),(26,4,4,0,0,0,0,0,1744),(26,4,5,0,0,0,0,0,1745),(26,4,6,0,0,0,0,0,1746),(26,4,7,0,0,0,0,0,1747),(26,4,8,0,0,0,0,0,1748),(26,5,0,0,0,7,0,0,1749),(26,5,1,1,2,0,0,0,1750),(26,5,2,0,0,0,0,0,1751),(26,5,3,0,0,0,0,0,1752),(26,5,4,0,0,0,0,0,1753),(26,5,5,0,0,0,0,0,1754),(26,5,6,0,0,0,0,0,1755),(26,5,7,0,0,0,0,0,1756),(26,5,8,0,0,0,0,0,1757),(26,6,0,0,0,7,0,0,1758),(26,6,1,1,2,0,0,0,1759),(26,6,2,0,0,0,0,0,1760),(26,6,3,0,0,0,0,0,1761),(26,6,4,0,0,0,0,0,1762),(26,6,5,0,0,0,0,0,1763),(26,6,6,0,0,0,0,0,1764),(26,6,7,0,0,0,0,0,1765),(26,6,8,0,0,0,0,0,1766),(26,7,0,0,0,7,0,0,1767),(26,7,1,1,2,0,0,0,1768),(26,7,2,0,0,0,0,0,1769),(26,7,3,0,0,0,0,0,1770),(26,7,4,0,0,0,0,0,1771),(26,7,5,0,0,0,0,0,1772),(26,7,6,0,0,0,0,0,1773),(26,7,7,0,0,0,0,0,1774),(26,7,8,0,0,0,0,0,1775),(27,0,0,0,0,7,0,0,1776),(27,0,1,1,2,0,0,0,1777),(27,0,2,0,0,0,0,0,1778),(27,0,3,0,0,0,0,0,1779),(27,0,4,0,0,0,0,0,1780),(27,0,5,0,0,0,0,0,1781),(27,0,6,0,0,0,0,0,1782),(27,0,7,0,0,0,0,0,1783),(27,0,8,0,0,0,0,0,1784),(27,1,0,0,0,7,0,0,1785),(27,1,1,1,2,0,0,0,1786),(27,1,2,0,0,0,0,0,1787),(27,1,3,0,0,0,0,0,1788),(27,1,4,0,0,0,0,0,1789),(27,1,5,0,0,0,0,0,1790),(27,1,6,0,0,0,0,0,1791),(27,1,7,0,0,0,0,0,1792),(27,1,8,0,0,0,0,0,1793),(27,2,0,0,0,2,0,1,1794),(27,2,1,1,2,6,0,0,1795),(27,2,2,3,5,1,2,0,1796),(27,2,3,6,1000,2,3,0,1797),(27,2,4,0,0,0,0,0,1798),(27,2,5,0,0,0,0,0,1799),(27,2,6,0,0,0,0,0,1800),(27,2,7,0,0,0,0,0,1801),(27,2,8,0,0,0,0,0,1802),(27,3,0,0,0,7,0,0,1803),(27,3,1,1,2,0,0,0,1804),(27,3,2,0,0,0,0,0,1805),(27,3,3,0,0,0,0,0,1806),(27,3,4,0,0,0,0,0,1807),(27,3,5,0,0,0,0,0,1808),(27,3,6,0,0,0,0,0,1809),(27,3,7,0,0,0,0,0,1810),(27,3,8,0,0,0,0,0,1811),(27,4,0,0,0,7,0,0,1812),(27,4,1,1,2,0,0,0,1813),(27,4,2,0,0,0,0,0,1814),(27,4,3,0,0,0,0,0,1815),(27,4,4,0,0,0,0,0,1816),(27,4,5,0,0,0,0,0,1817),(27,4,6,0,0,0,0,0,1818),(27,4,7,0,0,0,0,0,1819),(27,4,8,0,0,0,0,0,1820),(27,5,0,0,0,7,0,0,1821),(27,5,1,1,2,0,0,0,1822),(27,5,2,0,0,0,0,0,1823),(27,5,3,0,0,0,0,0,1824),(27,5,4,0,0,0,0,0,1825),(27,5,5,0,0,0,0,0,1826),(27,5,6,0,0,0,0,0,1827),(27,5,7,0,0,0,0,0,1828),(27,5,8,0,0,0,0,0,1829),(27,6,0,0,0,7,0,0,1830),(27,6,1,1,2,0,0,0,1831),(27,6,2,0,0,0,0,0,1832),(27,6,3,0,0,0,0,0,1833),(27,6,4,0,0,0,0,0,1834),(27,6,5,0,0,0,0,0,1835),(27,6,6,0,0,0,0,0,1836),(27,6,7,0,0,0,0,0,1837),(27,6,8,0,0,0,0,0,1838),(27,7,0,0,0,7,0,0,1839),(27,7,1,1,2,0,0,0,1840),(27,7,2,0,0,0,0,0,1841),(27,7,3,0,0,0,0,0,1842),(27,7,4,0,0,0,0,0,1843),(27,7,5,0,0,0,0,0,1844),(27,7,6,0,0,0,0,0,1845),(27,7,7,0,0,0,0,0,1846),(27,7,8,0,0,0,0,0,1847),(28,0,0,0,0,7,0,0,1903),(28,0,1,1,2,0,0,0,1904),(28,0,2,0,0,0,0,0,1905),(28,0,3,0,0,0,0,0,1906),(28,0,4,0,0,0,0,0,1907),(28,0,5,0,0,0,0,0,1908),(28,0,6,0,0,0,0,0,1909),(28,0,7,0,0,0,0,0,1910),(28,0,8,0,0,0,0,0,1911),(28,1,0,0,0,7,0,0,1912),(28,1,1,1,2,0,0,0,1913),(28,1,2,0,0,0,0,0,1914),(28,1,3,0,0,0,0,0,1915),(28,1,4,0,0,0,0,0,1916),(28,1,5,0,0,0,0,0,1917),(28,1,6,0,0,0,0,0,1918),(28,1,7,0,0,0,0,0,1919),(28,1,8,0,0,0,0,0,1920),(28,2,0,0,0,2,0,1,1921),(28,2,1,1,2,6,0,0,1922),(28,2,2,3,5,1,2,0,1923),(28,2,3,6,1000,2,3,0,1924),(28,2,4,0,0,0,0,0,1925),(28,2,5,0,0,0,0,0,1926),(28,2,6,0,0,0,0,0,1927),(28,2,7,0,0,0,0,0,1928),(28,2,8,0,0,0,0,0,1929),(28,3,0,0,0,7,0,0,1930),(28,3,1,1,2,0,0,0,1931),(28,3,2,0,0,0,0,0,1932),(28,3,3,0,0,0,0,0,1933),(28,3,4,0,0,0,0,0,1934),(28,3,5,0,0,0,0,0,1935),(28,3,6,0,0,0,0,0,1936),(28,3,7,0,0,0,0,0,1937),(28,3,8,0,0,0,0,0,1938),(28,4,0,0,0,7,0,0,1939),(28,4,1,1,2,0,0,0,1940),(28,4,2,0,0,0,0,0,1941),(28,4,3,0,0,0,0,0,1942),(28,4,4,0,0,0,0,0,1943),(28,4,5,0,0,0,0,0,1944),(28,4,6,0,0,0,0,0,1945),(28,4,7,0,0,0,0,0,1946),(28,4,8,0,0,0,0,0,1947),(28,5,0,0,0,7,0,0,1948),(28,5,1,1,2,0,0,0,1949),(28,5,2,0,0,0,0,0,1950),(28,5,3,0,0,0,0,0,1951),(28,5,4,0,0,0,0,0,1952),(28,5,5,0,0,0,0,0,1953),(28,5,6,0,0,0,0,0,1954),(28,5,7,0,0,0,0,0,1955),(28,5,8,0,0,0,0,0,1956),(28,6,0,0,0,7,0,0,1957),(28,6,1,1,2,0,0,0,1958),(28,6,2,0,0,0,0,0,1959),(28,6,3,0,0,0,0,0,1960),(28,6,4,0,0,0,0,0,1961),(28,6,5,0,0,0,0,0,1962),(28,6,6,0,0,0,0,0,1963),(28,6,7,0,0,0,0,0,1964),(28,6,8,0,0,0,0,0,1965),(28,7,0,0,0,7,0,0,1966),(28,7,1,1,2,0,0,0,1967),(28,7,2,0,0,0,0,0,1968),(28,7,3,0,0,0,0,0,1969),(28,7,4,0,0,0,0,0,1970),(28,7,5,0,0,0,0,0,1971),(28,7,6,0,0,0,0,0,1972),(28,7,7,0,0,0,0,0,1973),(28,7,8,0,0,0,0,0,1974);
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

--
-- Table structure for table `userinfo`
--

DROP TABLE IF EXISTS `userinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `userinfo` (
  `userid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(30) DEFAULT '未知',
  `usersex` varchar(30) DEFAULT '未知',
  `useradress` varchar(50) DEFAULT '未知',
  `usercorp` varchar(50) DEFAULT '未知',
  `userphone` varchar(50) DEFAULT '未知',
  `userhaoma` varchar(50) DEFAULT '未知',
  `userpic` longblob,
  `cardindex` varchar(50) NOT NULL DEFAULT '0',
  `Comments` varchar(250) DEFAULT '',
  PRIMARY KEY (`userid`),
  KEY `cardindex` (`cardindex`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `userinfo`
--

LOCK TABLES `userinfo` WRITE;
/*!40000 ALTER TABLE `userinfo` DISABLE KEYS */;
INSERT INTO `userinfo` VALUES (1,'未知','未知','未知','未知','未知','未知',NULL,'1109682',''),(2,'未知','女','未知','未知','未知','未知',NULL,'1105986',''),(3,'','女','','','','',NULL,'',''),(5,'未知','未知','未知','未知','未知','未知',NULL,'222656',''),(6,'','女','','','','',NULL,'',''),(7,'未知','女','未知','未知','未知','未知',NULL,'1118066','');
/*!40000 ALTER TABLE `userinfo` ENABLE KEYS */;
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
  `shebeiname` varchar(30) NOT NULL DEFAULT '新建控制器',
  `video1ip` varchar(30) NOT NULL DEFAULT '127.0.0.1',
  `video2ip` varchar(30) NOT NULL DEFAULT '127.0.0.1',
  `video3ip` varchar(30) NOT NULL DEFAULT '127.0.0.1',
  `video4ip` varchar(30) NOT NULL DEFAULT '127.0.0.1',
  `ifdoor` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`roadconerind`),
  KEY `shebeiid` (`shebeiid`),
  KEY `shebeiadr` (`shebeiadr`)
) ENGINE=InnoDB AUTO_INCREMENT=44 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roadconerinfo`
--

LOCK TABLES `roadconerinfo` WRITE;
/*!40000 ALTER TABLE `roadconerinfo` DISABLE KEYS */;
INSERT INTO `roadconerinfo` VALUES (32,108,3,0,0,0,0,'B入','192.168.1.24','127.0.0.1','127.0.0.1','127.0.0.1',0),(33,109,1,0,0,0,0,'A入','192.168.1.24','127.0.0.1','127.0.0.1','127.0.0.1',0),(34,110,4,0,0,0,0,'B出','192.168.1.24','127.0.0.1','127.0.0.1','127.0.0.1',0),(35,111,5,0,0,0,0,'C入','192.168.1.24','127.0.0.1','127.0.0.1','127.0.0.1',0),(36,112,6,0,0,0,0,'C出','192.168.1.24','127.0.0.1','127.0.0.1','127.0.0.1',0),(37,113,2,0,0,0,0,'A出','192.168.1.24','127.0.0.1','127.0.0.1','127.0.0.1',0),(40,118,9,0,0,0,0,'A2入','192.168.1.24','127.0.0.1','127.0.0.1','127.0.0.1',0),(41,119,10,0,0,0,0,'A2出','192.168.1.24','127.0.0.1','127.0.0.1','127.0.0.1',0),(42,120,7,0,0,0,0,'A1入','192.168.1.24','127.0.0.1','127.0.0.1','127.0.0.1',0),(43,121,8,0,0,0,0,'A2出','192.168.1.24','127.0.0.1','127.0.0.1','127.0.0.1',0);
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
  `shebeiname` varchar(30) NOT NULL DEFAULT '未知',
  PRIMARY KEY (`shebeiid`),
  KEY `parentid` (`parentid`)
) ENGINE=InnoDB AUTO_INCREMENT=122 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `treeview`
--

LOCK TABLES `treeview` WRITE;
/*!40000 ALTER TABLE `treeview` DISABLE KEYS */;
INSERT INTO `treeview` VALUES (104,0,1,'tcc','最外围'),(105,0,104,'tcc','停车场A'),(106,0,104,'tcc','停车场B'),(107,0,104,'tcc','停车场C'),(108,0,106,'kzq','B入'),(109,0,105,'kzq','A入'),(110,0,106,'kzq','B出'),(111,0,107,'kzq','C入'),(112,0,107,'kzq','C出'),(113,0,105,'kzq','A出'),(114,0,105,'tcc','停车场A1'),(115,0,105,'tcc','停车场A2'),(118,0,115,'kzq','A2入'),(119,0,115,'kzq','A2出'),(120,0,114,'kzq','A1入'),(121,0,114,'kzq','A2出');
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
  `cardstate` varchar(30) NOT NULL DEFAULT '启用',
  `cardkind` varchar(30) DEFAULT 'EMID卡',
  `cardselfno` varchar(50) DEFAULT '未知',
  `cardcomment` varchar(100) DEFAULT '未知',
  `cardcreator` varchar(30) DEFAULT '未知',
  `Inside` int(10) DEFAULT '0',
  `EnterMustCard` int(10) DEFAULT '0',
  `LeaveMustCard` int(10) DEFAULT '0',
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
INSERT INTO `monthcard` VALUES ('1105986','2012-01-31 09:39:01','2012-02-29 09:39:01','启用','EMID卡','未知','未知','停车场管理员',0,0,0),('1109682','2012-01-31 09:39:03','2012-02-29 09:39:03','启用','EMID卡','未知','未知','停车场管理员',0,0,0),('1118066','2012-03-07 11:51:40','2012-04-07 11:51:40','启用','EMID卡','','未知','停车场管理员',1,0,0),('1118550','2012-02-06 17:06:24','2012-03-06 17:06:24','启用','EMID卡','未知','未知','停车场管理员',0,0,0);
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
/*!50106 SET @save_time_zone= @@TIME_ZONE */ ;
/*!50106 DROP EVENT IF EXISTS `DeleteDataTimer` */;
DELIMITER ;;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;;
/*!50003 SET character_set_client  = utf8 */ ;;
/*!50003 SET character_set_results = utf8 */ ;;
/*!50003 SET collation_connection  = utf8_general_ci */ ;;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;;
/*!50003 SET sql_mode              = '' */ ;;
/*!50003 SET @saved_time_zone      = @@time_zone */ ;;
/*!50003 SET time_zone             = 'SYSTEM' */ ;;
/*!50106 CREATE*/ /*!50117 DEFINER=`test`@`%`*/ /*!50106 EVENT `DeleteDataTimer` ON SCHEDULE EVERY 10 MINUTE STARTS '2012-03-22 14:49:17' ON COMPLETION PRESERVE ENABLE COMMENT 'Delete Stoprd Data' DO DELETE FROM Stoprd WHERE MayDelete */ ;;
/*!50003 SET time_zone             = @saved_time_zone */ ;;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;;
/*!50003 SET character_set_client  = @saved_cs_client */ ;;
/*!50003 SET character_set_results = @saved_cs_results */ ;;
/*!50003 SET collation_connection  = @saved_col_connection */ ;;
DELIMITER ;
/*!50106 SET TIME_ZONE= @save_time_zone */ ;

--
-- Dumping routines for database 'parkadmin'
--
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
#数字转字符串 :
#newstr=concat(n,'');
#字符串转数字:
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
    
    declare strMonthCard varchar( 6 ) default '月租卡';
    declare strTimeCard varchar( 6 ) default '计时卡';
    declare strValueCard varchar( 6 ) default '储值卡';
    
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

-- DECLARE HANDLER syntax 声明异常处理的语法
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
        set strType1 = '月租卡';
    elseif exists ( select cardno from savecard where cardno in ( select cardindex from carinfo where carcp = strplate ) ) then
        set strType1 = '储值卡';
    elseif exists ( select cardno from tmpcard where cardno in ( select cardindex from carinfo where carcp = strplate ) ) then
        set strType1 = '计时卡';
    end if;
end;

begin
declare a int default 2; -- Temporary variable Scope
set @x = 'sjkdfsd'; -- Session Variable
    if exists ( select cardno from monthcard where cardno in ( strCardID ) ) then
        set strType2= '月租卡';
    elseif exists ( select cardno from savecard where cardno in ( strCardID ) ) then
        set strType2 = '储值卡';
    elseif exists ( select cardno from tmpcard where cardno in ( strCardID ) ) then
        set strType2 = '计时卡';
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
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`test`@`%`*/ /*!50003 PROCEDURE `MakeLicense`( in ID varchar( 50 ) )
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
    If bStart = 0 then 
        BEGIN 
            Drop table if exists tmpcardintime;
            Drop event if exists DeleteDataTimer;
            SET GLOBAL EVENT_SCHEDULER = FALSE;
        END;
     else 
        BEGIN
           CREATE TABLE if not exists tmpcardintime ( 
            idtmpcardintime int(11) NOT NULL AUTO_INCREMENT,
            cardno varchar(45) NOT NULL,
            intime datetime NOT NULL,
            invideo1 longblob,
            PRIMARY KEY ( idtmpcardintime) 
          ) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=gb2312;
        
        SET GLOBAL EVENT_SCHEDULER = TRUE; 
      END;
    END IF;             
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

-- Dump completed on 2012-03-22 16:25:06
CREATE DATABASE  IF NOT EXISTS `pmshistory` /*!40100 DEFAULT CHARACTER SET gb2312 */;
USE `pmshistory`;
-- MySQL dump 10.13  Distrib 5.5.16, for Win32 (x86)
--
-- Host: localhost    Database: pmshistory
-- ------------------------------------------------------
-- Server version	5.5.21-log

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
-- Table structure for table `tmpcard`
--

DROP TABLE IF EXISTS `tmpcard`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmpcard` (
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `cardkind` varchar(50) DEFAULT 'EMID卡',
  `cardfeebz` varchar(30) NOT NULL DEFAULT '现场选择',
  `cardselfno` varchar(50) DEFAULT NULL,
  `cardstate` varchar(30) NOT NULL DEFAULT '启用',
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
INSERT INTO `tmpcard` VALUES ('1113554','EMID卡','小型车','未知','启用',0,0,0),('15395143','EMID卡','小型车','未知','启用',0,0,0),('9400338','EMID卡','小型车','','启用',0,0,0);
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmshistory`.`tmpcard_ai`
AFTER INSERT ON `pmshistory`.`tmpcard`
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmshistory`.`tmpcard_au`
AFTER UPDATE ON `pmshistory`.`tmpcard`
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmshistory`.`tmpcard_ad`
AFTER DELETE ON `pmshistory`.`tmpcard`
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
  `shebeiname` varchar(30) NOT NULL DEFAULT '未知',
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
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`stoprdid`,`intime`),
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (month( intime ) %31)
PARTITIONS 31 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd`
--

LOCK TABLES `stoprd` WRITE;
/*!40000 ALTER TABLE `stoprd` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `carinfo`
--

DROP TABLE IF EXISTS `carinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `carinfo` (
  `carid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `carcp` varchar(50) NOT NULL DEFAULT '未知',
  `carmodel` varchar(50) NOT NULL DEFAULT '小型车',
  `carpic` longblob,
  `cardindex` varchar(50) NOT NULL DEFAULT '0',
  `carhaoma` varchar(50) NOT NULL DEFAULT '未知',
  PRIMARY KEY (`carid`),
  KEY `cardindex` (`cardindex`),
  KEY `carcp` (`carcp`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `carinfo`
--

LOCK TABLES `carinfo` WRITE;
/*!40000 ALTER TABLE `carinfo` DISABLE KEYS */;
INSERT INTO `carinfo` VALUES (1,'未知','小型车',NULL,'1109682','未知'),(2,'渝F41093','小型车',NULL,'1105986','未知'),(4,'未知','小型车',NULL,'222656','未知'),(5,'未知','未知',NULL,'9400338','未知'),(6,'未知','小型车',NULL,'1118066','未知');
/*!40000 ALTER TABLE `carinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `savecard`
--

DROP TABLE IF EXISTS `savecard`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `savecard` (
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `cardstate` varchar(30) NOT NULL DEFAULT '启用',
  `cardkind` varchar(30) DEFAULT 'EMID卡',
  `cardselfno` varchar(50) DEFAULT NULL,
  `cardcomment` varchar(100) DEFAULT NULL,
  `cardcreator` varchar(30) DEFAULT NULL,
  `cardfeebz` varchar(30) NOT NULL DEFAULT '现场选择',
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
INSERT INTO `savecard` VALUES ('222656','启用','EMID卡','未知','未知','停车场管理员','小型车',0,0,0,0);
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmshistory`.`savecard_ai`
AFTER INSERT ON `pmshistory`.`savecard`
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmshistory`.`savecard_au`
AFTER UPDATE ON `pmshistory`.`savecard`
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmshistory`.`savecard_ad`
AFTER DELETE ON `pmshistory`.`savecard`
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
-- Table structure for table `log`
--

DROP TABLE IF EXISTS `log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `log` (
  `idlog` int(11) NOT NULL AUTO_INCREMENT,
  `txt` blob,
  PRIMARY KEY (`idlog`)
) ENGINE=InnoDB AUTO_INCREMENT=61 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `log`
--

LOCK TABLES `log` WRITE;
/*!40000 ALTER TABLE `log` DISABLE KEYS */;
INSERT INTO `log` VALUES (60,'delete from stoprd where stoprdid in ( select stoprdid FROM stoprd where ( cardno like \'%(%)%\' or outvideo1 is not null ) and inshebeiname =\'C��\') as tmp');
/*!40000 ALTER TABLE `log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprdtmpid`
--

DROP TABLE IF EXISTS `stoprdtmpid`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprdtmpid` (
  `idstoprdid` bigint(20) NOT NULL AUTO_INCREMENT,
  `id` bigint(20) NOT NULL,
  PRIMARY KEY (`idstoprdid`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprdtmpid`
--

LOCK TABLES `stoprdtmpid` WRITE;
/*!40000 ALTER TABLE `stoprdtmpid` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprdtmpid` ENABLE KEYS */;
UNLOCK TABLES;

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
  `cardstate` varchar(30) NOT NULL DEFAULT '启用',
  `cardkind` varchar(30) DEFAULT 'EMID卡',
  `cardselfno` varchar(50) DEFAULT '未知',
  `cardcomment` varchar(100) DEFAULT '未知',
  `cardcreator` varchar(30) DEFAULT '未知',
  `Inside` int(10) DEFAULT '0',
  `EnterMustCard` int(10) DEFAULT '0',
  `LeaveMustCard` int(10) DEFAULT '0',
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
INSERT INTO `monthcard` VALUES ('1105986','2012-01-31 09:39:01','2012-02-29 09:39:01','启用','EMID卡','未知','未知','停车场管理员',1,0,0),('1109682','2012-01-31 09:39:03','2012-02-29 09:39:03','启用','EMID卡','未知','未知','停车场管理员',0,0,0),('1118066','2012-03-07 11:51:40','2012-04-07 11:51:40','启用','EMID卡','','未知','停车场管理员',1,0,0),('1118550','2012-02-06 17:06:24','2012-03-06 17:06:24','启用','EMID卡','未知','未知','停车场管理员',0,0,0);
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmshistory`.`monthcard_ai`
AFTER INSERT ON `pmshistory`.`monthcard`
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmshistory`.`monthcard_au`
AFTER UPDATE ON `pmshistory`.`monthcard`
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmshistory`.`monthcard_ad`
AFTER DELETE ON `pmshistory`.`monthcard`
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
-- Table structure for table `stoprd9`
--

DROP TABLE IF EXISTS `stoprd9`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprd9` (
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
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`stoprdid`,`intime`),
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (month( intime ) %31)
PARTITIONS 31 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd9`
--

LOCK TABLES `stoprd9` WRITE;
/*!40000 ALTER TABLE `stoprd9` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd9` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprd8`
--

DROP TABLE IF EXISTS `stoprd8`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprd8` (
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
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`stoprdid`,`intime`),
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (month( intime ) %31)
PARTITIONS 31 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd8`
--

LOCK TABLES `stoprd8` WRITE;
/*!40000 ALTER TABLE `stoprd8` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd8` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprdxtmpid`
--

DROP TABLE IF EXISTS `stoprdxtmpid`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprdxtmpid` (
  `idstoprdid` bigint(20) NOT NULL AUTO_INCREMENT,
  `id` bigint(20) NOT NULL,
  PRIMARY KEY (`idstoprdid`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprdxtmpid`
--

LOCK TABLES `stoprdxtmpid` WRITE;
/*!40000 ALTER TABLE `stoprdxtmpid` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprdxtmpid` ENABLE KEYS */;
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

--
-- Table structure for table `userinfo`
--

DROP TABLE IF EXISTS `userinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `userinfo` (
  `userid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(30) DEFAULT '未知',
  `usersex` varchar(30) DEFAULT '未知',
  `useradress` varchar(50) DEFAULT '未知',
  `usercorp` varchar(50) DEFAULT '未知',
  `userphone` varchar(50) DEFAULT '未知',
  `userhaoma` varchar(50) DEFAULT '未知',
  `userpic` longblob,
  `cardindex` varchar(50) NOT NULL DEFAULT '0',
  `Comments` varchar(250) DEFAULT '',
  PRIMARY KEY (`userid`),
  KEY `cardindex` (`cardindex`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `userinfo`
--

LOCK TABLES `userinfo` WRITE;
/*!40000 ALTER TABLE `userinfo` DISABLE KEYS */;
INSERT INTO `userinfo` VALUES (1,'未知','未知','未知','未知','未知','未知',NULL,'1109682',''),(2,'未知','女','未知','未知','未知','未知',NULL,'1105986',''),(3,'','女','','','','',NULL,'',''),(5,'未知','未知','未知','未知','未知','未知',NULL,'222656',''),(6,'','女','','','','',NULL,'',''),(7,'未知','未知','未知','未知','未知','未知',NULL,'1118066','');
/*!40000 ALTER TABLE `userinfo` ENABLE KEYS */;
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
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`stoprdid`,`intime`),
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (month( intime ) %31)
PARTITIONS 31 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd1`
--

LOCK TABLES `stoprd1` WRITE;
/*!40000 ALTER TABLE `stoprd1` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd1` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprd0`
--

DROP TABLE IF EXISTS `stoprd0`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprd0` (
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
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`stoprdid`,`intime`),
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (month( intime ) %31)
PARTITIONS 31 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd0`
--

LOCK TABLES `stoprd0` WRITE;
/*!40000 ALTER TABLE `stoprd0` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd0` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprd3`
--

DROP TABLE IF EXISTS `stoprd3`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprd3` (
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
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`stoprdid`,`intime`),
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (month( intime ) %31)
PARTITIONS 31 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd3`
--

LOCK TABLES `stoprd3` WRITE;
/*!40000 ALTER TABLE `stoprd3` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd3` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprd2`
--

DROP TABLE IF EXISTS `stoprd2`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprd2` (
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
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`stoprdid`,`intime`),
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (month( intime ) %31)
PARTITIONS 31 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd2`
--

LOCK TABLES `stoprd2` WRITE;
/*!40000 ALTER TABLE `stoprd2` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd2` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprd5`
--

DROP TABLE IF EXISTS `stoprd5`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprd5` (
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
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`stoprdid`,`intime`),
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (month( intime ) %31)
PARTITIONS 31 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd5`
--

LOCK TABLES `stoprd5` WRITE;
/*!40000 ALTER TABLE `stoprd5` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd5` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprd4`
--

DROP TABLE IF EXISTS `stoprd4`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprd4` (
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
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`stoprdid`,`intime`),
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (month( intime ) %31)
PARTITIONS 31 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd4`
--

LOCK TABLES `stoprd4` WRITE;
/*!40000 ALTER TABLE `stoprd4` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd4` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprd7`
--

DROP TABLE IF EXISTS `stoprd7`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprd7` (
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
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`stoprdid`,`intime`),
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (month( intime ) %31)
PARTITIONS 31 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd7`
--

LOCK TABLES `stoprd7` WRITE;
/*!40000 ALTER TABLE `stoprd7` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd7` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stoprd6`
--

DROP TABLE IF EXISTS `stoprd6`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stoprd6` (
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
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`stoprdid`,`intime`),
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (month( intime ) %31)
PARTITIONS 31 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd6`
--

LOCK TABLES `stoprd6` WRITE;
/*!40000 ALTER TABLE `stoprd6` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd6` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'pmshistory'
--
/*!50106 SET @save_time_zone= @@TIME_ZONE */ ;
/*!50106 DROP EVENT IF EXISTS `SplitDataTimer` */;
DELIMITER ;;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;;
/*!50003 SET character_set_client  = utf8 */ ;;
/*!50003 SET character_set_results = utf8 */ ;;
/*!50003 SET collation_connection  = utf8_general_ci */ ;;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;;
/*!50003 SET sql_mode              = '' */ ;;
/*!50003 SET @saved_time_zone      = @@time_zone */ ;;
/*!50003 SET time_zone             = 'SYSTEM' */ ;;
/*!50106 CREATE*/ /*!50117 DEFINER=`test`@`%`*/ /*!50106 EVENT `SplitDataTimer` ON SCHEDULE EVERY 2 MINUTE STARTS '2012-03-22 14:48:39' ON COMPLETION PRESERVE ENABLE COMMENT 'Split Stoprd Data' DO call CallSplitStopRD( ) */ ;;
/*!50003 SET time_zone             = @saved_time_zone */ ;;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;;
/*!50003 SET character_set_client  = @saved_cs_client */ ;;
/*!50003 SET character_set_results = @saved_cs_results */ ;;
/*!50003 SET collation_connection  = @saved_col_connection */ ;;
/*!50106 DROP EVENT IF EXISTS `SplitDataXTimer` */;;
DELIMITER ;;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;;
/*!50003 SET character_set_client  = utf8 */ ;;
/*!50003 SET character_set_results = utf8 */ ;;
/*!50003 SET collation_connection  = utf8_general_ci */ ;;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;;
/*!50003 SET sql_mode              = '' */ ;;
/*!50003 SET @saved_time_zone      = @@time_zone */ ;;
/*!50003 SET time_zone             = 'SYSTEM' */ ;;
/*!50106 CREATE*/ /*!50117 DEFINER=`test`@`%`*/ /*!50106 EVENT `SplitDataXTimer` ON SCHEDULE EVERY 2 HOUR STARTS '2012-03-22 16:16:51' ON COMPLETION PRESERVE ENABLE COMMENT 'Split StoprdX Data' DO call DeleteDataStopRdX( ) */ ;;
/*!50003 SET time_zone             = @saved_time_zone */ ;;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;;
/*!50003 SET character_set_client  = @saved_cs_client */ ;;
/*!50003 SET character_set_results = @saved_cs_results */ ;;
/*!50003 SET collation_connection  = @saved_col_connection */ ;;
DELIMITER ;
/*!50106 SET TIME_ZONE= @save_time_zone */ ;

--
-- Dumping routines for database 'pmshistory'
--
/*!50003 DROP PROCEDURE IF EXISTS `CallSplitStopRD` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`ROOT`@`localhost`*/ /*!50003 PROCEDURE `CallSplitStopRD`()
BEGIN
    call SplitStopRd( 'stoprd0', 'C入' );
    call SplitStopRd( 'stoprd1', 'D入' );
    -- call SplitStopRd( 'stoprd2', 'D入' );
    -- call SplitStopRd( 'stoprd3', 'D入' );
    -- call SplitStopRd( 'stoprd4', 'D入' );
    -- call SplitStopRd( 'stoprd5', 'D入' );
    -- call SplitStopRd( 'stoprd6', 'D入' );
    -- call SplitStopRd( 'stoprd7', 'D入' );
    -- call SplitStopRd( 'stoprd8', 'D入' );
    -- call SplitStopRd( 'stoprd9', 'D入' );
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `DeleteDataStopRdX` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `DeleteDataStopRdX`()
BEGIN
    set @curdate = NOW( ) - interval 2 hour;
    
    insert into stoprdxtmpid( id ) select stoprdid from stoprd0 where  intime <= @curdate;
    delete stoprdxtmpid, stoprd0 from stoprd0, stoprdxtmpid where stoprd0.stoprdid = stoprdxtmpid.id;
    
    insert into stoprdxtmpid( id ) select stoprdid from stoprd1 where  intime <= @curdate;
    delete stoprdxtmpid, stoprd1 from stoprd1, stoprdxtmpid where stoprd1.stoprdid = stoprdxtmpid.id;
    
    insert into stoprdxtmpid( id ) select stoprdid from stoprd2 where  intime <= @curdate;
    delete stoprdxtmpid, stoprd2 from stoprd2, stoprdxtmpid where stoprd2.stoprdid = stoprdxtmpid.id;
    
    insert into stoprdxtmpid( id ) select stoprdid from stoprd3 where  intime <= @curdate;
    delete stoprdxtmpid, stoprd3 from stoprd3, stoprdxtmpid where stoprd3.stoprdid = stoprdxtmpid.id;
    
    insert into stoprdxtmpid( id ) select stoprdid from stoprd4 where  intime <= @curdate;
    delete stoprdxtmpid, stoprd4 from stoprd4, stoprdxtmpid where stoprd4.stoprdid = stoprdxtmpid.id;
    
    insert into stoprdxtmpid( id ) select stoprdid from stoprd5 where  intime <= @curdate;
    delete stoprdxtmpid, stoprd5 from stoprd5, stoprdxtmpid where stoprd5.stoprdid = stoprdxtmpid.id;
    
    insert into stoprdxtmpid( id ) select stoprdid from stoprd6 where  intime <= @curdate;
    delete stoprdxtmpid, stoprd6 from stoprd6, stoprdxtmpid where stoprd6.stoprdid = stoprdxtmpid.id;
    
    insert into stoprdxtmpid( id ) select stoprdid from stoprd7 where  intime <= @curdate;
    delete stoprdxtmpid, stoprd7 from stoprd7, stoprdxtmpid where stoprd7.stoprdid = stoprdxtmpid.id;
    
    insert into stoprdxtmpid( id ) select stoprdid from stoprd8 where  intime <= @curdate;
    delete stoprdxtmpid, stoprd8 from stoprd8, stoprdxtmpid where stoprd8.stoprdid = stoprdxtmpid.id;
    
    insert into stoprdxtmpid( id ) select stoprdid from stoprd9 where  intime <= @curdate;
    delete stoprdxtmpid, stoprd9 from stoprd9, stoprdxtmpid where stoprd9.stoprdid = stoprdxtmpid.id;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `SplitStopRd` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `SplitStopRd`( in strTableName varchar( 32 ), in strChannelName varchar( 128 ) )
BEGIN
    set @MySQL = concat( 'Insert Into ', strTableName, '( cardno,inshebeiname,outshebeiname,invideo1,invideo2,invideo3,invideo4,
           outvideo1,outvideo2,outvideo3,outvideo4,intime,outtime,childrdindx,feebeizhu,
           feenum,feetime,feeoperator,feefactnum,carcp,username,cardselfno,carkind,feekind,
           cardkind,parkid,feezkh,feezkyy,carcpout,MayDelete ) 
           select cardno,inshebeiname,outshebeiname,invideo1,invideo2,invideo3,invideo4,
           outvideo1,outvideo2,outvideo3,outvideo4,intime,outtime,childrdindx,feebeizhu,
           feenum,feetime,feeoperator,feefactnum,carcp,username,cardselfno,carkind,feekind,
           cardkind,parkid,feezkh,feezkyy,carcpout,MayDelete FROM stoprd where ( cardno like \'%(%)%\' or outvideo1 is not null ) and inshebeiname =\'', strChannelName, '\'' );
           
    prepare STMT from @MySQL;
    execute STMT;
    deallocate prepare STMT;
    
    set @MySQL = concat( 'Insert into stoprdtmpid( id ) select stoprdid FROM stoprd where ( cardno like \'%(%)%\' or outvideo1 is not null ) and inshebeiname =\'', strChannelName, '\'' );
    prepare STMT from @MySQL;
    execute STMT;
    deallocate prepare STMT;
    
    delete stoprd, stoprdtmpid from stoprdtmpid, stoprd where stoprd.stoprdid = stoprdtmpid.id;
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

-- Dump completed on 2012-03-22 16:25:22
CREATE DATABASE  IF NOT EXISTS `pmsparthistory` /*!40100 DEFAULT CHARACTER SET gb2312 */;
USE `pmsparthistory`;
-- MySQL dump 10.13  Distrib 5.5.16, for Win32 (x86)
--
-- Host: localhost    Database: pmsparthistory
-- ------------------------------------------------------
-- Server version	5.5.21-log

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
-- Table structure for table `savecard`
--

DROP TABLE IF EXISTS `savecard`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `savecard` (
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `cardstate` varchar(30) NOT NULL DEFAULT '启用',
  `cardkind` varchar(30) DEFAULT 'EMID卡',
  `cardselfno` varchar(50) DEFAULT NULL,
  `cardcomment` varchar(100) DEFAULT NULL,
  `cardcreator` varchar(30) DEFAULT NULL,
  `cardfeebz` varchar(30) NOT NULL DEFAULT '现场选择',
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
INSERT INTO `savecard` VALUES ('222656','启用','EMID卡','未知','未知','停车场管理员','小型车',0,0,0,0);
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmsparthistory`.`savecard_ai`
AFTER INSERT ON `pmsparthistory`.`savecard`
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmsparthistory`.`savecard_au`
AFTER UPDATE ON `pmsparthistory`.`savecard`
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmsparthistory`.`savecard_ad`
AFTER DELETE ON `pmsparthistory`.`savecard`
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
-- Table structure for table `tmpcard`
--

DROP TABLE IF EXISTS `tmpcard`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmpcard` (
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `cardkind` varchar(50) DEFAULT 'EMID卡',
  `cardfeebz` varchar(30) NOT NULL DEFAULT '现场选择',
  `cardselfno` varchar(50) DEFAULT NULL,
  `cardstate` varchar(30) NOT NULL DEFAULT '启用',
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
INSERT INTO `tmpcard` VALUES ('1113554','EMID卡','小型车','未知','启用',0,0,0),('15395143','EMID卡','小型车','未知','启用',0,0,0),('9400338','EMID卡','小型车','','启用',0,0,0);
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmsparthistory`.`tmpcard_ai`
AFTER INSERT ON `pmsparthistory`.`tmpcard`
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmsparthistory`.`tmpcard_au`
AFTER UPDATE ON `pmsparthistory`.`tmpcard`
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmsparthistory`.`tmpcard_ad`
AFTER DELETE ON `pmsparthistory`.`tmpcard`
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
-- Table structure for table `monthcard`
--

DROP TABLE IF EXISTS `monthcard`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `monthcard` (
  `cardno` varchar(50) NOT NULL DEFAULT '0',
  `starttime` datetime NOT NULL DEFAULT '2006-06-01 12:00:00',
  `endtime` datetime NOT NULL DEFAULT '2006-06-01 12:00:00',
  `cardstate` varchar(30) NOT NULL DEFAULT '启用',
  `cardkind` varchar(30) DEFAULT 'EMID卡',
  `cardselfno` varchar(50) DEFAULT '未知',
  `cardcomment` varchar(100) DEFAULT '未知',
  `cardcreator` varchar(30) DEFAULT '未知',
  `Inside` int(10) DEFAULT '0',
  `EnterMustCard` int(10) DEFAULT '0',
  `LeaveMustCard` int(10) DEFAULT '0',
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
INSERT INTO `monthcard` VALUES ('1105986','2012-01-31 09:39:01','2012-02-29 09:39:01','启用','EMID卡','未知','未知','停车场管理员',1,0,0),('1109682','2012-01-31 09:39:03','2012-02-29 09:39:03','启用','EMID卡','未知','未知','停车场管理员',0,0,0),('1118066','2012-03-07 11:51:40','2012-04-07 11:51:40','启用','EMID卡','','未知','停车场管理员',1,0,0),('1118550','2012-02-06 17:06:24','2012-03-06 17:06:24','启用','EMID卡','未知','未知','停车场管理员',0,0,0);
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmsparthistory`.`monthcard_ai`
AFTER INSERT ON `pmsparthistory`.`monthcard`
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmsparthistory`.`monthcard_au`
AFTER UPDATE ON `pmsparthistory`.`monthcard`
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
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `pmsparthistory`.`monthcard_ad`
AFTER DELETE ON `pmsparthistory`.`monthcard`
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
  `shebeiname` varchar(30) NOT NULL DEFAULT '未知',
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
  `intime` datetime NOT NULL,
  `outtime` datetime DEFAULT NULL,
  `childrdindx` int(10) unsigned DEFAULT NULL,
  `feebeizhu` varchar(30) DEFAULT NULL,
  `feenum` int(10) unsigned DEFAULT NULL,
  `feetime` datetime DEFAULT NULL,
  `feeoperator` varchar(30) DEFAULT NULL,
  `feefactnum` int(10) unsigned DEFAULT NULL,
  `carcp` varchar(30) NOT NULL DEFAULT '未知',
  `username` varchar(30) NOT NULL DEFAULT '未知',
  `cardselfno` varchar(50) DEFAULT NULL,
  `carkind` varchar(30) NOT NULL DEFAULT '未知',
  `feekind` varchar(30) DEFAULT NULL,
  `cardkind` varchar(30) DEFAULT NULL,
  `parkid` int(11) NOT NULL DEFAULT '-1',
  `feezkh` int(10) unsigned DEFAULT NULL,
  `feezkyy` varchar(30) NOT NULL DEFAULT '无优惠',
  `carcpout` varchar(30) DEFAULT '未知',
  `MayDelete` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`stoprdid`,`intime`),
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
) ENGINE=InnoDB DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (month( intime ) %31)
PARTITIONS 31 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stoprd`
--

LOCK TABLES `stoprd` WRITE;
/*!40000 ALTER TABLE `stoprd` DISABLE KEYS */;
/*!40000 ALTER TABLE `stoprd` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `carinfo`
--

DROP TABLE IF EXISTS `carinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `carinfo` (
  `carid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `carcp` varchar(50) NOT NULL DEFAULT '未知',
  `carmodel` varchar(50) NOT NULL DEFAULT '小型车',
  `carpic` longblob,
  `cardindex` varchar(50) NOT NULL DEFAULT '0',
  `carhaoma` varchar(50) NOT NULL DEFAULT '未知',
  PRIMARY KEY (`carid`),
  KEY `cardindex` (`cardindex`),
  KEY `carcp` (`carcp`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `carinfo`
--

LOCK TABLES `carinfo` WRITE;
/*!40000 ALTER TABLE `carinfo` DISABLE KEYS */;
INSERT INTO `carinfo` VALUES (1,'未知','小型车',NULL,'1109682','未知'),(2,'渝F41093','小型车',NULL,'1105986','未知'),(4,'未知','小型车',NULL,'222656','未知'),(5,'未知','未知',NULL,'9400338','未知'),(6,'未知','小型车',NULL,'1118066','未知');
/*!40000 ALTER TABLE `carinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `userinfo`
--

DROP TABLE IF EXISTS `userinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `userinfo` (
  `userid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(30) DEFAULT '未知',
  `usersex` varchar(30) DEFAULT '未知',
  `useradress` varchar(50) DEFAULT '未知',
  `usercorp` varchar(50) DEFAULT '未知',
  `userphone` varchar(50) DEFAULT '未知',
  `userhaoma` varchar(50) DEFAULT '未知',
  `userpic` longblob,
  `cardindex` varchar(50) NOT NULL DEFAULT '0',
  `Comments` varchar(250) DEFAULT '',
  PRIMARY KEY (`userid`),
  KEY `cardindex` (`cardindex`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `userinfo`
--

LOCK TABLES `userinfo` WRITE;
/*!40000 ALTER TABLE `userinfo` DISABLE KEYS */;
INSERT INTO `userinfo` VALUES (1,'未知','未知','未知','未知','未知','未知',NULL,'1109682',''),(2,'未知','女','未知','未知','未知','未知',NULL,'1105986',''),(3,'','女','','','','',NULL,'',''),(5,'未知','未知','未知','未知','未知','未知',NULL,'222656',''),(6,'','女','','','','',NULL,'',''),(7,'未知','未知','未知','未知','未知','未知',NULL,'1118066','');
/*!40000 ALTER TABLE `userinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'pmsparthistory'
--
/*!50106 SET @save_time_zone= @@TIME_ZONE */ ;
/*!50106 DROP EVENT IF EXISTS `DeleteDataSplitTimer` */;
DELIMITER ;;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;;
/*!50003 SET character_set_client  = utf8 */ ;;
/*!50003 SET character_set_results = utf8 */ ;;
/*!50003 SET collation_connection  = utf8_general_ci */ ;;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;;
/*!50003 SET sql_mode              = '' */ ;;
/*!50003 SET @saved_time_zone      = @@time_zone */ ;;
/*!50003 SET time_zone             = 'SYSTEM' */ ;;
/*!50106 CREATE*/ /*!50117 DEFINER=`test`@`%`*/ /*!50106 EVENT `DeleteDataSplitTimer` ON SCHEDULE EVERY 1 DAY STARTS '2012-03-23 01:00:00' ON COMPLETION PRESERVE ENABLE COMMENT 'Delete Stoprd Data Split' DO call DeleteDataSplit( ) */ ;;
/*!50003 SET time_zone             = @saved_time_zone */ ;;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;;
/*!50003 SET character_set_client  = @saved_cs_client */ ;;
/*!50003 SET character_set_results = @saved_cs_results */ ;;
/*!50003 SET collation_connection  = @saved_col_connection */ ;;
DELIMITER ;
/*!50106 SET TIME_ZONE= @save_time_zone */ ;

--
-- Dumping routines for database 'pmsparthistory'
--
/*!50003 DROP PROCEDURE IF EXISTS `DeleteDataSplit` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`test`@`%`*/ /*!50003 PROCEDURE `DeleteDataSplit`()
BEGIN
    set @curdate = NOW( ) - interval 180 day;
    
    delete from stoprd where intime <= @curdate;
    delete from garageingarage where DateTime <= @curdate;
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

-- Dump completed on 2012-03-22 16:25:24
