CREATE DATABASE  IF NOT EXISTS `streetroadpark` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `streetroadpark`;
-- MySQL dump 10.13  Distrib 5.6.12, for Win32 (x86)
--
-- Host: localhost    Database: streetroadpark
-- ------------------------------------------------------
-- Server version	5.6.12

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
-- Table structure for table `tabadministrativeinfo`
--

DROP TABLE IF EXISTS `tabadministrativeinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabadministrativeinfo` (
  `AdministrativeID` varchar(6) NOT NULL,
  `AdministrativeName` varchar(45) NOT NULL,
  `AdministrativeComments` varchar(45) DEFAULT NULL,
  `AdministrativeParentID` varchar(6) NOT NULL,
  `AdministrativeType` enum('Province','City','District') NOT NULL,
  PRIMARY KEY (`AdministrativeID`),
  UNIQUE KEY `AdministrativeName_UNIQUE` (`AdministrativeName`),
  UNIQUE KEY `AdministrativeID_UNIQUE` (`AdministrativeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabadministrativeinfo`
--

LOCK TABLES `tabadministrativeinfo` WRITE;
/*!40000 ALTER TABLE `tabadministrativeinfo` DISABLE KEYS */;
INSERT INTO `tabadministrativeinfo` VALUES ('510000','å››å·çœ',NULL,'0','Province'),('510100','æˆéƒ½å¸‚',NULL,'510000','City'),('510107','æ­¦ä¾¯åŒº',NULL,'510100','District');
/*!40000 ALTER TABLE `tabadministrativeinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabdetectorinfo`
--

DROP TABLE IF EXISTS `tabdetectorinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabdetectorinfo` (
  `ParkReceiverID` varchar(13) NOT NULL,
  `DetectorID` varchar(3) NOT NULL COMMENT 'æ¯ä¸ªæ¥å—ç®¡ç†çš„æ¢æµ‹å™¨IDç¼–å·å”¯ä¸€ï¼Œåˆ†æ®µç®¡ç†\nR0 1-30\nR1 31-50\nR2 51-75\nR3 76-99',
  `DetectorChannelID` tinyint(3) unsigned DEFAULT '0',
  `DetectorComments` varchar(45) DEFAULT NULL,
  `Threshold` smallint(5) unsigned DEFAULT '0',
  `DelayTime` smallint(6) DEFAULT '0',
  `DetectorReset` bit(1) NOT NULL DEFAULT b'0',
  `ReceiverDetectorID` varchar(16) NOT NULL COMMENT 'ParkID+ReceiverID+DetectorID\nTrigger==>ParkID ReceiverID DetectorID',
  PRIMARY KEY (`ReceiverDetectorID`),
  UNIQUE KEY `ReceiverDetectorID_UNIQUE` (`ReceiverDetectorID`),
  KEY `ReceiverDetector_idx` (`ParkReceiverID`),
  CONSTRAINT `ReceiverDetector` FOREIGN KEY (`ParkReceiverID`) REFERENCES `tabreceiverinfo` (`ParkReceiverID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabdetectorinfo`
--

LOCK TABLES `tabdetectorinfo` WRITE;
/*!40000 ALTER TABLE `tabdetectorinfo` DISABLE KEYS */;
INSERT INTO `tabdetectorinfo` VALUES ('5101070001001','006',1,NULL,0,0,'\0','5101070001001006');
/*!40000 ALTER TABLE `tabdetectorinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabdeviceregisterinfo`
--

DROP TABLE IF EXISTS `tabdeviceregisterinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabdeviceregisterinfo` (
  `DeviceID` varchar(128) NOT NULL,
  `DeviceComments` varchar(45) DEFAULT NULL,
  `StartTime` datetime DEFAULT NULL,
  `EndTime` datetime DEFAULT NULL,
  `DeviceState` enum('Available','Unavailable') NOT NULL DEFAULT 'Available',
  `UnitID` varchar(9) DEFAULT NULL COMMENT 'Company ID==>TabUnitInfo\nhttp://www.nacao.org.cn/ ä»£ç æŸ¥è¯¢',
  `SerialNumber` varchar(1024) DEFAULT NULL,
  `Register` varchar(45) DEFAULT NULL,
  `UnRegister` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`DeviceID`),
  UNIQUE KEY `DeviceID_UNIQUE` (`DeviceID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabdeviceregisterinfo`
--

LOCK TABLES `tabdeviceregisterinfo` WRITE;
/*!40000 ALTER TABLE `tabdeviceregisterinfo` DISABLE KEYS */;
INSERT INTO `tabdeviceregisterinfo` VALUES ('359732008920329',NULL,'2013-01-01 00:00:00','2014-01-01 00:00:00','Available','771237583','1234567890',NULL,NULL);
/*!40000 ALTER TABLE `tabdeviceregisterinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabfeeinfo`
--

DROP TABLE IF EXISTS `tabfeeinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabfeeinfo` (
  `RecordID` bigint(20) unsigned NOT NULL,
  `Prepayment` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Payment` smallint(5) unsigned NOT NULL DEFAULT '0',
  `PrepaymentOperator` varchar(45) NOT NULL,
  `PrepaymentTime` datetime NOT NULL,
  `PaymentTime` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `PaymentOperator` varchar(45) DEFAULT NULL,
  `PrepaymentUserID` bigint(20) unsigned DEFAULT NULL,
  `PaymentUserID` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`RecordID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabfeeinfo`
--

LOCK TABLES `tabfeeinfo` WRITE;
/*!40000 ALTER TABLE `tabfeeinfo` DISABLE KEYS */;
INSERT INTO `tabfeeinfo` VALUES (7,0,5,'æœªçŸ¥','2013-08-06 11:37:58','2013-08-06 11:52:58','æœªçŸ¥',1,1);
/*!40000 ALTER TABLE `tabfeeinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabgroupinfo`
--

DROP TABLE IF EXISTS `tabgroupinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabgroupinfo` (
  `GroupID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `GroupName` varchar(45) NOT NULL,
  `GroupComments` varchar(45) DEFAULT NULL,
  `GroupParentID` bigint(20) NOT NULL,
  `GroupRight` bigint(20) unsigned DEFAULT NULL COMMENT '64 right bits',
  `UnitID` varchar(9) NOT NULL,
  PRIMARY KEY (`GroupID`),
  UNIQUE KEY `GroupName_UNIQUE` (`GroupName`),
  UNIQUE KEY `GroupID_UNIQUE` (`GroupID`),
  KEY `GroupUnit_idx` (`UnitID`),
  CONSTRAINT `GroupUnit` FOREIGN KEY (`UnitID`) REFERENCES `tabunitinfo` (`UnitID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabgroupinfo`
--

LOCK TABLES `tabgroupinfo` WRITE;
/*!40000 ALTER TABLE `tabgroupinfo` DISABLE KEYS */;
INSERT INTO `tabgroupinfo` VALUES (1,'æµ‹è¯•1',NULL,0,NULL,'771237583');
/*!40000 ALTER TABLE `tabgroupinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabhistoryfeeinfo`
--

DROP TABLE IF EXISTS `tabhistoryfeeinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabhistoryfeeinfo` (
  `RecordID` bigint(20) unsigned NOT NULL,
  `Prepayment` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Payment` smallint(5) unsigned NOT NULL DEFAULT '0',
  `PrepaymentOperator` varchar(45) NOT NULL,
  `PrepaymentTime` datetime NOT NULL,
  `PaymentTime` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `PaymentOperator` varchar(45) DEFAULT NULL,
  `PrepaymentUserID` bigint(20) unsigned DEFAULT NULL,
  `PaymentUserID` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`RecordID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabhistoryfeeinfo`
--

LOCK TABLES `tabhistoryfeeinfo` WRITE;
/*!40000 ALTER TABLE `tabhistoryfeeinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `tabhistoryfeeinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabhistoryinoutimageinfo`
--

DROP TABLE IF EXISTS `tabhistoryinoutimageinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabhistoryinoutimageinfo` (
  `RecordID` bigint(20) unsigned NOT NULL,
  `EnterImage` longblob,
  `LeaveImage` longblob,
  `AddedTime` date NOT NULL,
  PRIMARY KEY (`RecordID`,`AddedTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
/*!50100 PARTITION BY LINEAR HASH (MONTH(AddedTime))
PARTITIONS 12 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabhistoryinoutimageinfo`
--

LOCK TABLES `tabhistoryinoutimageinfo` WRITE;
/*!40000 ALTER TABLE `tabhistoryinoutimageinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `tabhistoryinoutimageinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabhistoryinoutrecordinfo`
--

DROP TABLE IF EXISTS `tabhistoryinoutrecordinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabhistoryinoutrecordinfo` (
  `RecordID` bigint(20) unsigned NOT NULL,
  `LocationID` varchar(16) NOT NULL,
  `EnterTime` datetime NOT NULL,
  `LeaveTime` datetime DEFAULT NULL,
  `EnterPlate` varchar(45) DEFAULT NULL,
  `LeavePlate` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`RecordID`,`EnterTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
/*!50100 PARTITION BY LINEAR HASH (MONTH(EnterTime))
PARTITIONS 12 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabhistoryinoutrecordinfo`
--

LOCK TABLES `tabhistoryinoutrecordinfo` WRITE;
/*!40000 ALTER TABLE `tabhistoryinoutrecordinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `tabhistoryinoutrecordinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabhistoryloginfo`
--

DROP TABLE IF EXISTS `tabhistoryloginfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabhistoryloginfo` (
  `LogID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `LogInfo` longtext COMMENT 'IP@ClientID@Serial@Credit@Type@SQL',
  `LogDateTime` datetime NOT NULL,
  PRIMARY KEY (`LogID`,`LogDateTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
/*!50100 PARTITION BY LINEAR HASH (MONTH( LogDateTime ))
PARTITIONS 12 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabhistoryloginfo`
--

LOCK TABLES `tabhistoryloginfo` WRITE;
/*!40000 ALTER TABLE `tabhistoryloginfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `tabhistoryloginfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabhistoryuserloginoutinfo`
--

DROP TABLE IF EXISTS `tabhistoryuserloginoutinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabhistoryuserloginoutinfo` (
  `LogID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `LogUserID` bigint(20) unsigned DEFAULT NULL,
  `LogTime` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `LogType` enum('Login','Logout') DEFAULT NULL,
  `LogClientID` varchar(45) DEFAULT NULL,
  `LogIP` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`LogID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabhistoryuserloginoutinfo`
--

LOCK TABLES `tabhistoryuserloginoutinfo` WRITE;
/*!40000 ALTER TABLE `tabhistoryuserloginoutinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `tabhistoryuserloginoutinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabinoutimageinfo`
--

DROP TABLE IF EXISTS `tabinoutimageinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabinoutimageinfo` (
  `RecordID` bigint(20) unsigned NOT NULL,
  `EnterImage` longblob,
  `LeaveImage` longblob,
  `AddedTime` date NOT NULL,
  PRIMARY KEY (`RecordID`,`AddedTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
/*!50100 PARTITION BY LINEAR HASH (MONTH(AddedTime))
PARTITIONS 12 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabinoutimageinfo`
--

LOCK TABLES `tabinoutimageinfo` WRITE;
/*!40000 ALTER TABLE `tabinoutimageinfo` DISABLE KEYS */;
INSERT INTO `tabinoutimageinfo` VALUES (7,'ÿØÿà\0JFIF\0\0\0\0\0\0ÿÛ\0C\0\n\n\n\r\rÿÛ\0C		\r\rÿÀ\0à€\"\0ÿÄ\0\0\0\0\0\0\0\0\0\0\0	\nÿÄ\0µ\0\0\0}\0!1AQa\"q2‘¡#B±ÁRÑğ$3br‚	\n\Z%&\'()*456789:CDEFGHIJSTUVWXYZcdefghijstuvwxyzƒ„…†‡ˆ‰Š’“”•–—˜™š¢£¤¥¦§¨©ª²³´µ¶·¸¹ºÂÃÄÅÆÇÈÉÊÒÓÔÕÖ×ØÙÚáâãäåæçèéêñòóôõö÷øùúÿÄ\0\0\0\0\0\0\0\0	\nÿÄ\0µ\0\0w\0!1AQaq\"2B‘¡±Á	#3RğbrÑ\n$4á%ñ\Z&\'()*56789:CDEFGHIJSTUVWXYZcdefghijstuvwxyz‚ƒ„…†‡ˆ‰Š’“”•–—˜™š¢£¤¥¦§¨©ª²³´µ¶·¸¹ºÂÃÄÅÆÇÈÉÊÒÓÔÕÖ×ØÙÚâãäåæçèéêòóôõö÷øùúÿÚ\0\0\0?\0ø¾ŞĞn8Î*üV{‡ŠÚÜ\0EhEm„ r+I©$™V.\rh[ÃÁjx­pNNjİ½¶3ô+³8½5emÆçZQDr)¶°rE][ã¨©½ô);ìrş*¸K;lòp+Èõ	Ìó»uæ½âÙ·ˆ@\\’ÙÂÕæ³d©EwS|°&\r%t@ÈÌÜœNŒÜõ©,.Í=AÆ:šW¾Æ÷Ğ›L´NµĞ”òâ$»Y$YSƒëV¾ÚÛvç>ø¬Ô^è•¶‚<¥÷5š÷\r’3š–æRÄóÀªIö­1ºwD±ÎÌ[æ«)ló×õªÉ	9ÍHœ\nq×@Õ­BI@-úÔ+r\n1#¥#>7÷ÍW\0‡4]ŞÄ©v&,][\rQ™³òüS	½DxïU¢ÜÑIŞT¶;ĞdbzÓã­\0ç>ÕK]ÅÒÃÃ?÷H÷Å.ÿ\0jˆ:R‡çÖ±RcM­‰Rá‚ã¸ïRE*ããëUX`Ôˆ¬›;qN\Z7¹8»Ü˜ëKsÓY>MÔôŸnîô›}HIs]—ìîög=+FïT2ÂnƒÏFç$îà~µ,Òüœ7{­Jû7e×»Ü>øüéñß0ã?(¬¸¤’ß…=§Ù¥nPŠFáÔù\n\'Ú®éÚ»Ç¸g­r‘ÌTŠ»È\\“LÉEò³ĞàÕ\0ˆ:78õ©4ÍTÜ‰rìT\rÜ£5ÇÚŞ¬6Œ7aŞ\ráˆŸ›â³¶÷]^ç­øw\\1\"(>lhw\0ùşäÒê~\"\r;¬M¼¨nÙô¯?ÒõákjW#<ÔSëd·\rùS§«*oC¹Ò¯n<Iâ›==eØnŒ±çåîyÿ\0?×êËMVÒÒÖÛKÓ˜,`+’Ç,@Áúô¯¼¬\rIoãÇš€¨n…sßüÿ\0õëĞ ø—}eop¶n|éPƒ;cåÏ‡6«Ç•COãÁ¤¼±\\æcä\'Ø}k^?ˆôûY$`²ŞE\Zƒß§ç^àFx¬gÔõGûUÕÙw·UçôçÖ½Dñl~&ñ”P\"­¾}£œ¶2>oóøVJZoÜq[§¹ô‘\ZZÚÅnNdûÍç5¬‘ìMÌx÷®[Ãóq™!‘Ëp[·ÿ\0ªµ­®Æ¡+\rÁb–`İ@ãÅ-[Dß›ViÄûA\'µ<adF½cÙNu+™!-b89êçÓÚµ-y€5¶ µ‰)‹\'$ş”Æ‡tqéVcM;Òmu&6‹Ğ¢±í>´æµWBJ·š²#\n29£dìUÕ´3\rªòvƒP>’œ‘!VÇM¼5kW\r1LtÇİ®œnÌÓ”u0¤Òz‘øUI4é\'=«¤0*&A´¾•J7‘¢JJıNe¬™6ŒûÕI-Š\r¿•u/\näğ2G\\T/h„\0)j¶2äV9VRƒÖ¡n¦ºgÓÕò@ëÜuªréªû†[éB•ì(Ç­Ì#.z\Z®Ñ8æ¶¤Ó6‚TÕi,$ú{ÖŠ§»d7æA,¹â¨ÎÒdò@ö8­y,$Œ·qÔU9m‰ùvš9¬·\'’Ú4f	ÎÖªSNÑ»mÅi=›rq^*ŒĞ›qäw¢2rÕ‹t¬ŒÇ˜–9Z¡u9±È«%¹ı«*xs¼Ôùµ¸’P††MÄÛG\'uf\\Ê§<t­‰íñœsYWv§µ5%{\r¦®–¦EÑV^:úÖØÊ°ÅnÍ	¸Î+&âœäô6¯¨´’»0.S úµ‰pÜ;®\Zèîa8|\ZÅ¹·Á%…_:aŞñ0.c{\nÈ¼ˆ>µ¿ynr}«â“úÖmu7å¶·9Ë¸÷}kŸ½„ş¸®ªê«(ê;VÕ¶ÒHëZ\'Ê¬;¶s7)Á¬‰Si+]Í¾ÒÃµdÜÁÁõi•Œ+˜ğÍÜU7L‚;Ö´Ğîİš¡2`°ïT»\Z/3è{XGZÓ†Ü€qÖ¢¶„ƒŠÒ·BÀ¨<®Ìt[AÈ«ö¨»}=éÉne—ŠsÛ•¯\rïOMrò½‰áÂsĞT~‘«Œ‚OzÇ’ycFÇ5w¨Hæ´Œvd$Ù‹\"·ÔrÙ*àç¯jóû»ÑØ)éŞº‹û²û†s¢¹Ù3ó};Öê6V*:ÑÄ9^Öœ°ªÔ‰µ_8ÀêI$Ú\0‘M+h&öc£Pcµ#¨@ÌNFÍ&>ö\n‚wrpÇ\"„µÔ»´6W¶:T@FÍ+PNê®Ñ†9©q³Ğii Dí“éü¨YÊ¨7•_­0\rRµ®BÚÈ¥óÏ­D]{T@qšQ’+;sŠBç$Ğ0Aş”Òp¬EÛ·V•à;\0§MÈiCdg¡9˜À÷¡zÒ¯J:­¿hCiD¿#.x¥À¤\nM%‡ ƒæPxêqH«·ëJ>QSî€à}iŸz“œÕ6í`Å!`3íC(`A¨êR¹I\\vÿ\0jš9\n©ÅSYyçR† c5IX,¥±£Öî\rOÎKàõ—\r<1ÇŠ¨êC6\"»PXv¥[½ÏÓå¬d‘”3R@Ä7š5µĞïedvúEËGÑ°™æº:ñÒ3’ ‚W=}«…Ó¤1A×“]&…(€™È¢ñkPV}OUO¶É—liX£½k±øMw*ji†\nX³4¥¶sœ×Š[k\\<®pPMnhŞ4’Ò~Ìß¾a´àßüı+%®bÛ	õ„^*{O4ZÜG9(m¸Åt×7ÂÑÈ\0S-Ï\'×Šù“Á¾)to-²C4Œı~¿çÖ½K@×¢!mÂFœ—¨=«Ÿ‘+©n)­ -.µˆ‘E~P¬kJİ„Al63Šát¯¤¨³Ï y$Ä6öç’1ĞñíÖ¶´Û©gºQ1˜üçĞW<U÷.÷¹ÖCp	Û*Üy9¬›I£V<ƒØÖ„‚IÎ¡9©kBR¾äåı=iÃ9ãŞ’U…8d€HéYù®š°Ğ¸<SrjeU9æ˜È£#œúæšin+8îBW$JˆÆ0ÀsŠµ³©¨ñU“WtTò—Ÿz‡ÊÂ±<çWCæñQy_x5iº±W×B¥Vx‰É#š¾aÈ& e<Š„E¯¹A¢\nyZ[~K•xÆrÙëMòÍ)Bûâìd<[\'Š©-¾¿7®k^xK1Àüª«\'¨â©$Ğ¯}‰-¿xÅSšÍ6>T[’Æ¸n+>X°[?4ô4o¢0§²#—>šXãÒM\0ñüª”–ÊZµõ#KêVK‡zÊ¹°á±ĞW_sf>lÆ²î\"Û!ÀüqPû™ÍÛTq÷ +wJÈ¹Óƒ«•>¢»˜\'k*{~Xš‹]î\\|ö8Ë½?\nW9¬KÍ<í ×osoó0#ŸjÆ»¶\06\"´µ–…+Gc…º³#\'‘ukÃõÚ]Záõ¬+Û\\@âšvĞwj\'ygÁãšÂ»´ ·\Zínm÷#qÈ¬+¸Hq‘W`M3‹¼´ÚOumÇ®ÊæØÄ\raß[pFßÂˆ\ZE3•\0CqÍgM~U¿sÜ8¬»ˆq“Ú­\ZŸD[[•ëZVÑ*˜d÷¨`…r­Æ›sš½ö­{“G íOk˜Õ0Ùüª[¸ïY×’²£Q¦­©›«y\07\0Ù®?U¿›Ë<*MI¤¶sX2ù_?•oÆ÷8«^ã.ns×“Y“—;›¢Õ‡R –æ™Ï&Õµ¢W*nè«å>3Šˆ–İšÕØ¢ôçµQ‘¶©õíM&µe$·+™™¤ó<SŠA#š®‡Ôn-ÕÆ”}Å˜ôè7rúŠk\\dtÀ¨<â«5w¹q’B8æ›@9?1 Õ¢˜­qFzûÓê>-‡°ÁïJ9SƒIB8<t50ÜdxÛßò¥ŒeZ—vT‘L\r´1”ãyn]î‡3ç¦EÉ$¶¦.ğoÿ\0]>3‚~•\\Újkoºi¹*1ŞœNÑQæ²ˆD]Ç‘B¶3Ş’Ã\"¬­	ĞÓKIKü\"’ÑXI$.òz\nmQkÖå®iU6‚3×Ò1}i£œÿ\0úê‰÷I¶ÒïàŒu¦Ñ1IhîU…ˆ„]§·zÔr>o»Ş«ñøÕ‹s°ƒÔSµ!¤¸\'8§ŠØ³ÔÉŒ(ÈÀù±\\ÄSg­Ì1““øRIKS+XèTòã½_²Ô<¤%[-+Œ¶ºÜíqÒ®-ùP@\"•¾È$––=A×…¼ÌòœB­z‡<khbŒT\0O|WÏöº“g äÕÒiº»m	¼‘ìÕ\r&ù‚JjîçÕZGÆİL¸ó\"•®f X‹İÏùü+±ğÏÄvÔ\\L~V~FFr=ıÿ\0Ï×äm/ÄK#Vflå‹tÇa^‰á‘åÆMìÀl¡Çÿ\0^°åVmng^ësë­\'ÄpÈÑ‰1ä¼…äÀu­‹/FrÆÉj:nêß…xŸ†ZOİ[EùH¤røÈÏüö¯WĞ^5œyndQÂ¾Æ¹_ce¶¬ô8% ªã§½YV;8ÈëŠÅ²™“Œ0Àï[¶S¤Tór«‚×Qñü¤ş´ÕFù94<ûÓ•ÈàRV¶¡(s?Ê»i€œT’c6ÔUV±šT.»1ÍM»<SJîn;Ózl4ìU1aÈ=j‡jºXá–¢$Å\n\"‚M]]r§Öª•Èb[)ïP)eìqW{°Oİi\nâ«47¯Ôš‰×+ÅB‹A$®eJ›äU9b,ãñ­Óæz®Ø­U8‰_±’ñ‚GJTÁlÖ¼ê7·¡¬ù•H9Óo±:½«„Ü9íY³Z‡$çšÜxAÈ5›,{w~t(ÙÙ„}éjs×QmSíYsCÃ\ZègM¤ŒVUäEƒÜRÑ-®¼§7wË¹íÅbÜGÎqÇzénc`§œZÈ¸ˆa²3D|Ùi¶ö9{¨wnvŸ¥b_@y\0ôæº›´ùMbİD9=ª“5wjÉ­Ô!=+\nöC\Zëo\"PÛÒ¹û¸99§½¬%k3™º·ÚH¯zÂ¼€«·®¦î!–‚8¬[¸99«Vè8\\ä¯`È&²&‡¨é]5ôyTu¬;¸Êg#§àÚv>ƒ…WƒVTâxu§Ÿ”0\"´úšót\Z–?cêwÑ\0Ê€V/<Ã­Jç.Õ¡,ÿ\0õªÖû‰y”n•¤v9ÀµU`ê[«±È^Oó¬ù.kÒ¯•¸ê-îÑFú7–B\0ÂõoI¶´´Iîï$Àqc«¹è1Şª+1ëTîffÏ ­V«”—«-no\Z|ñ·Åe\\9\nyÇ­YšL+ùÖt“’¬qÇó«w‘£åzùŒì:qĞS?SÒÄdÓYÉ.?½Yì´*B2äÒiHÏzEj-\'¹(JQJ\\\n0)ò0¸€w¡FIÍ 8$RŒšŸ!Œu¦ƒRÔT#HŠXšAi	ÀÍ8®1é±W`7ço½IEÄ•‚Š( ¢5ıÚ’zÔå0ïJBAW\'½=ÉJÄôQE\"ˆP6	T!\\ƒëVeèWQ’ÿ\0Oğ©“êeo²¶©¥BÍH½éËÖıûØØéDlÄí­(ûˆ2iaCËQrùlì‰bš”qQÄÓÍP£ÑõÔ³o8‰Hïšk\\3u5xÅ%ï¸øÙĞ§JrJå‰İQR©+ÒjjZÍ‚@jÑKõ„áXşUÍ‰H¥INx<Õ¥Í°®÷gck¨”ƒı+½ğŸ‰şÇXÙÃaœúW[]7İÜsõ®ƒDÖ$·u;úcÔò÷‘õoÃïµ‰XÃ:`‚É óú×Ñ>×ì\"¶A\n¾îäp3ßM|\'¢xŠöuŠHç)2«\'Ê=¸¯tøwâ;¨·<“3³ ÂÀ\'úŸ­rÎ>ë¹š´¹õ]¯‡éØõ­«IüÈÉÎÚ¯%ğ®®df?.à§ò\rz•ªÄçj·Ì£$f°~f“œV«©¾\0@æ•\\c“ÍG«.AÜx§rW$ò*7©F7œ‚;P6Fi¥‰úĞ_†4¢Ò÷Qp×šàˆS ÒçhÍD	Xõ¥i}?:ĞÅ­Gî6z\n¨[å$}ªÁ˜/AÅ@X;O4“³°%%ª “ï\Zã}{ÔÍ’N8ö¨›æÎ{Õ=È¾ºÛå-éUe]¤Î*Û€rçPJTæZ)mïdÉÆ©ÌŸ>sŒÕæGáU	Ü¡m ›I¤\\îÇ~ÕQãRÄ‘WäB3Î¨Ì>SJ-¦Ë‹OS>ár[mgÏlı+VeÜ+>Dù˜vªö»\"­tcÜ&TÖ<ñŸ™­éãëéYwığ:T¤öD\'+Z\'=w,{VEÜ$s]ÜxgŞ±îã,jí¦£û69›…ÁqéY7òØü+¡¹µÎóµ•rŸ)(±TÛC—»…¾qŞ±.aàšéï£$’+îCzši^èQ½ô9›Èˆ\rÚ°ocà×Sy\raİ[ä8«ŠJå§c”½€‚yÍc^DpÀŒzfº{¨Hfâ±/#Îì»I.Â‹Mè{©;5Fæù”1LÔSj‹ àXš¿³d6z\nê…7ĞÕİ+¢ÍÎ«å©y®sVÕHÈÍS¹ÖÌùeâ².&iÉ9®„½à‘}eóc8äÓÒ1ô$zÔZzïûİ«)0BìFIéYM»”’½Ê“·¸OzÎq°Üš’òà<è:Õ;ƒ„­4AÉdWy1ÖªÉ/ÈS#‘’Aâ •†qéVìš´F»nCj\Z–˜Ä”‘	Ü`%‡^”`S²U6ûæzTÆ:jW İ´€›5*!s”Í¥r1õ£áÕQ´ô¤J#&°CMUÛš \'>”-©ç8§/A«Ø­åûÓ”qƒV£·A­=t÷##8úVwÛ(…ÜN)Á=y­´ÒÊØ\\š±Œä6Ÿ¨Í7$åY˜¾_½*§\\Šİ\Z€çËısLm\ZEÉØxô)_q¤ÙFEGå’G+Lé¤~–¡T(¿):Ä¦AÛŠf¡©öÒù½¿*w²‘	Q¶ª²×Š¸èzõ¦l4+[P²kR­\"4=óN‰N>eæ¥ié9ã5W±ZÅÌıÁ©6üİ8©\Z3Çò¤íSÍro`¢š3“š7zVhç?…FNM<¸QNÃ°3úSW%‰ëÛ”¨zç¥;YÊÃä})ÔÖuN§ê‚	-³æŠØÓGïy8‘nkBÚr½?*¸ì4ÏIĞnb†$ùÉíÖ½WÂZãÄƒÉqÓnWÏšUùE,~PyÅz\'†5˜â!‹ZÆqRØÆJçÔş\rÕ®åˆQ\07Åz…âüåO=<ÓÀÃşz×ÊV¾+kÙ¬LUpY‘ŠçÛ¿çé^±àY$\rÄï` .z?Ÿùúóò-\\‰QGÓ:]á’¬@uçŒÕó0#=}«ğæ£›tVù°1ãë]<DJ	\rrr;²·º,†İ½HéŠhP¥\"€yéíHFNĞsWO¨“[\\“q`ÛED1>´sî>¢—q“S¿ÂRòMs€(ß½ØôÍ#6º>”GAÁßR-¸Z™R–\rœ\ZF{zÖY’»[¶ßŸ†jÛ†oâïV\'våù•V\'9ô5¢ÔJzÜ„®XÕI#ÚÍÆ*áP¼*	rÇ8éŞ¢,™J<¾e\'²sU&“ÜúUÉFÅb;T7)Ç½V¶ÔKWÊÌÉñÍRœdÜV™ÈÉ#ğªS@£8â„’Ğ¤İ¬Œ›•Çl{úÖMÊâCÅoOU†>•›<yC‘‘Tíry]Ì+ˆ²ÅbOÌõÑÌœk*ænb?ZWOa»É®SœºŒ–n¹¬‹¸¾n9ÿ\0Zè§·Æî»dİF0İóÍW5µ+¥ÑËŞÆØ`GjÃº‹¸Íuwq¨÷¬È²IîÆÓ}N^ò<â±o-Ç>†º{¨AVâ°¯!ÈcÜTÅÙXÍ;œÍÒmCÆA¬;¸€É®¦á6æ°î£?—ó¦›hÛetu\Z½âF_®Föi.[\'…=ªåæ¡çrr=«)d3\0¯IFÈÖmêI)Ç5‚$8ûµ=ËtÚ½M.Ÿj×rc„\'hó\rÉë}‹:xÂìÜ(MW»½SëLÕ\'xSÊCkâä}İß…OMD•ÕŞ€Óä’zzT2¾\Zc:¦8=)Å¶ÊŠ¾¤,rI©©ãµ1—â”mÃ¸í@CKÜt{yÇ_zk*ô^¾Ôí»“ï×¡6‚A<÷¥æ4®¬ÈÚ&9÷§,8Rnõ$v¬Ä#½iiú<—lUAo^*|î8ÆÛ^_\rÏZ–nv‘]à™euÚ¤ƒÉÈ®ÓAø_-Óe“ä£õ„ñŒltÓ¤äy$\ZÒ©ù\rhÁá‰;=kİaøhbÀ$ğp¸«±|;C\Z,Lu¯;ëŠìİa_Ú<&\n>ãòS„¤fÈ\\a^ıkğÿ\0÷„¼XSÀ•b?\0DCŒ)î1SõÔÑ¬0Îö±àvŞ|¡?J³„‹8¯s_ÔîzñíQHKAŸqšO¢eÇ\n“<‚ÏÂx%Y3Z1øe$(8öë^š|\"è­µA#¨ª7‡]rÒ²x«»\\§‡µô8áˆ™¾è¦áHU\0ûWxt©ïj7±e‘ŸÂ…VIŞá\Z:]£Êõ/ìİ„÷â¹Ëãfùr}«ÚåÑË†ãŠËŸÃ*Å¾Qjè§ˆèÎYaõ<vÈ¬Çn\0¡4bÙ5ê7 ÇµRVÜ0 jèX„BÃò½v<Ñ´G\'îÔ¥§ş;^–Ú(ÁíUßÃÛ³À¢5…ì“Øóa§s¿­9¬Ì@ü¿w ¨SˆÀÅUo—İÆG­hª¦bè´ÎÀBÉÀf=*¶1]­Ï†˜zŠË›ÃÍógš¸ÔMºm-NiÇ4•¯6$@äŠ¡%›©<\ZÖ3LVqÑ”áÎÓ”üSŠIZŞâÖ\"L© uïíRÒ\0“ÜÒĞV\nn4P3AD£\0b®ÂØAÏ\"³Ğ’zÔŠÅAÁëQ±ÆœG$)®£Ã3Hò…ÜB÷>ÕÅBåXñÇÖ¶ôVK@aèjlùE{£è	iÏ;FVePz¶3^× D¶x.£ñÍ|‘¢üE¾²”xĞg³`ô¯døqã‰¯¥Fº2~ğÓõÿ\0#WŒR”·>¡ğµÜ’K;ø\'â½6Ğ«À;1ƒüëÈ|%«ZÉåì”níî+ÔôÙ•âp\'Û½sOš×b‹VV42Ç¶\r2c#Ò¢PBšÅ\nSåv>\\“ĞsÅ/s”Å«ƒÓµéV\"î®1±–ç¥/˜åZäŠ\n`ùSú/î\r#Ù©àmmÍÉ¨ñ3š¨îhçÌ¬G#c€~µAÉ<Õ’¡AÛÖ™äåyüªúX†ÕôEwÆ8ªî:Sìc)ÒÀğj5{‘{»”æƒr1-’{U7P21ÅhJ›ĞñÈéU8 õ¢Ù…¬îgÉROj©*n=kM×r‘Td‹%‡j¥g¸Úêg8ûÊ?„â³\'Œ¦Gë[]Á*¡qu=)«3HÉ8Ù˜7+†ÀZÍ,ƒ[“[|ääc½gOÇ5šLÎ\rŞç;t¸bqYW1pÄs]$Ğ‡-•Åe\\ÀT’@©æ}GeÍs—¼€ÃzVì?y}k©º…‰pF\rb^C¸f´Rºº&é-Zò,ÆÂ°î Æàk©¹€üÆ°®á\'wzUó_@ROFr×pà0#&±.`ç¨ï]5ôg ¬K«SÎ)Y½†µĞäÌ¦@rx«V!s‘Èõ¬ˆ®<¡Göƒì#8Íz‰_©Ôİö-Ët’Îzc<Ö´7‘ÃÅ>ÿ\0Zåb$14’ŞH€y46›Ğm]Y/ï¾ÕrçÓYòÈ2qÖ›ü¤M¡æù¥Ô#îêÆ*î8©U6©ÇSR#,jp¿ZoZ7«\rXÕN@Á§*ŸóšT<Sâ¤Í4Õí\"½HS’K8È=zUË[€v~ğmÎ«wq!!‰»€:;Ö¨¡YtàäÚ±Ïè~šéÏÈØô½Àÿ\0[t“È8“.9nİûW |:øF·/~@Øwş,õÿ\0>¿ŸÒ¾øIª+Ï²*ò_¿ ¯¶5¶Õ3Ù¡…T½ê‡‚è?\nc2€îÇ°®ÂEe…§]£?¥{Ì^	$f4*½­+øh$#~y¯\"U&îÛw:á(%hƒJ¹-Âİ³È«CÁêYˆNqšö‘áv€¶áíP7‡YG°ëŸOVoY;4xãxcÊŒm@Àw\\SF…¸–dÁéÀ¯TŸCVİòƒŠÇŸL¹Êí¡M¦l¢­¡Ác+«ƒià†º,aÁÙ‚;+ĞeÑŠÄX(5Bm)Ywr+6ú‹“CƒºÒÓŒ(ÎHÖDÚ\ZıâÔpkĞ\'ÓFBšÍº°2ğ[“¶á(İÚçŸİhÑ‚Ì¨öéYÏ£)NQs]äºSĞŸlVUÅ‘QÓ8íé[Âm«)	C™XäWD[åzÕS¡¨-¹3ô®Õm2€wôªÒÚukOjîdà¥Ğàîôu…õ–ú:9oƒõ¯@¹ÓIRqk)´ìó‚W×º©æO²8™t`¼úÔO¢æ6\0sîk·–ÄÇhÛÚ {3ŒúÖ‘¨õ3öIš)PrœúUWÒ5èÃJÜºUtÑ•‹\rœûÖ¬g*m»Øó‰´ ªI\\VdúZ6~Qšô«ı`eÁ>™‡>6·ËÈî+UU=™œé&ÚGŸÜèÂE$.+\ZëÃÀ†ùxèÿ\0ÙÛ3‘‘T.4ÎN€;ÖÑ¨ú3	PæW{Sy È…°‡µ‹=«DH+ŠõÛ/~p7f¹ícÃÂUb‘]t«tg¨ö<ï„àV­ş”ö¤äqYe6’}kº2æZÚ§`¢Š+AWõ 8ïÅ4)=¨P{TÙdM7\nÒ†DÁÛY(IÎjÕ§Ş9éQmHk¡¿¦È\0 óŠëü;|öÓy±;FøûÊzW	g\'ïNuº nç8íPÈK]O ¾xÎíçKvvwŒœsœ÷?çÿ\0¯õ?oší!€±c´œØñ_ÃİE-$v‰ˆg\06x?OÖ¾ªøC¬Ëygæ\\•WŒ…CıášÂjëRl¯kÉm‡qéRªsÓŠ©i6ääeOzµÎ[¯šäÕÅ•ûƒKÉÇçMU8<:šVSŒ§½*£²ñM&ÙJÉ\"’»Rì5`ñœô¨HÀ¤¥¬£¢±*7ÇLò*fB£ç½0•2ŞµZ_s$—1¥%=#&šWoÒš¶ÅòÙ“”Ësš†TB¥HãµXPÇJaˆüÇ9ZkÜ\\É+¢“Œ1ªÓ b{U×Ldf¡’?óÅJ}*IêÌæB3éÚ©ÊŸ) çšÔdÁÇ¥U–g\"µm¬ÕÌ©ÀUj¡\"äÖ¼ÑuªO\nÙZI¶½à½öØÇıÑøV\\Ñ7$\nß–&‡qYÓ¡br9¥¯Qi±ÏOo‚Ø¬{¨¸b+§Ø£>Ó‘u;‰JÉêiÈæ.£Ü¬ù«êdãŠéîmÈcïXwq1Ï¤¯º3r²Ôåï¡Úc§jÃ¸„r@ÅuWÑcvz•‹uU¸Å+®ŒÒ1IİôC,\0ÅbİG÷’º{Ø3»°îá œ{V‰«j6¹›±ãhâPF8¥Ëoö¤„\'?ıjbI\Zäçšô®º‘z]–Â`¥B] õ_Îm…{S(Q3ReÈçˆ4<Ü\n¯$*WA‚sŠJÍ\Z+=FÄY×®K\n\'½,0í\\W--·œş´¯}GnRKK30bV´­´ÂGtzU»|\00+°ğï†ÍÓ¢l.OEëK•êm\n|ÎÈƒÁŞŸU¼?$Œ€\0½ëêO…	”¤1í‰\\=)>|(Yc”‡,@ÃœãğÍ}gà/‡ñÚ-¿îğª;ŠùúØ‰U—*=¬<#‡ƒRİ™^	ğYÆ’4^pçµê\Z_…¶E,:g¦+ Òtxã\0²œ-lÛB±©*{{TRÃ·ñ•qÌåÛBQÜ\08ìj&Ğñàyë][Y™J€:Ó.-BŒ¨ùzV²Ãõ3…T•?¸Ò—Ìùpvç$•Îê6k\";·HèZ•ĞòAa´\\ÕªÅo\"¶Œ.xÍyÓ§dz”$™Æ]ZÆ™\\e…eÍ¦©•¤Pr:f·¦·2)-’EBÑFíÙÆ=«Ï’±è¸¨­ÎnX—G­g]Ú«7qœşá[óÛğÙ\ZÎ{bTäóŠÉ&¾&4NêĞÃ Õµ6z\nè.¬™ÖfWOjÇkfL°ŸzÒ.ú2$¯rˆ´L¶TYZ†•ºMØüzßHˆlçvMEz ñĞUYGb}äî_û,`zÕ´ì+bºi•Tc©ªR.ÕÖ’œ¬îR»Üæ¦´$m¥R—H|Çå]B[oäE,–À©ÊşU¤%Ü¾U}8é¥‡İ¨I\'ø3æºÑdO;OÖ¡– Nj•NÄ(­i4­ÀägëR&´“°ÖßÙòG§µ+ E#½iÏ¥4Öˆæo´Á´ñŸ­s7úhS +€{×uxG$ÿ\0úë»{7kHÊÏSšJÏUvp·\ZqŒ‘ëíT¤±KÆºËË`‡Z¡-˜9Àâºá=Œ%¯frrYäµy¦Ï×a5’¾Fj«ià+Öº¡Q$bã¡åÚ¾Œ9Àlz×\rªé¦	_½¯UÑˆÀW­hÂD~95Ù	¸«}Zm¦í©æ,6çÒ¢x·sŞµµ=5­ä~¬Ò»Ojô£%%s‰®Œ† 96j¸ç~Ş§­5üÎç?…8Êû™Å¤‹jıGSOY9ë´Õ1»?.\n–ßî¶iØ¹¥kpAÚN}+¤Ñ/BH™çÇn \n±opñ0!ÈÇqQa5¡ô?ƒ%¶h¾qåïêÀgŒ×ÒuUQn±#PF9%¿¯zøKHñ¶¥§®#™p0UYxÍzçÃ¯‹·‰\'—3#»£“ééş]&İĞœ¥\'ª?Dtf…­ù¾cc‘è{Ö¸®Ñ^-ğ“ÆÇÄv)$²—`f\nríşµ{-œãÀÀ®FÓ2ok’î8çó¤F}*EŒ6AéKQïv\\}õ©¦§Æ§0àg&£Ø{òjŞªÈ¥V?ÃéLØFqWB)†\"ÌNi¨5£Y•1ÍE÷N*éƒ‚3Q›vËz”Õã¨lï¨lSŠîÉjQ^)6TÓnèÎ÷Ø£$D!5Y‘ìkI­Ilš‰í°HªÓ¨ÓMİ™N„‚G^õXÅÙíZ¦\"sòãÚ 6›‹r3ëNİ	µïÊbËÁöªn™Åm}‰¼Ç÷éš«=¹(}iÛMÌã¢÷ŒImÁ/Êj…Ì\rÉÆ\roIjõÍS¸ƒÍŞØ»Ç©ÎL¹S“Y–ä+‡­t×6Ü·zÌ¸dR:SSrÒêrwQV5ä”œ}k¬¹¶1QòŠÆ¼·ÁcØúÖV\Z’hä/`ÛÇğšÃº€`ƒ]uİºpFr1ƒXJ[Î¥FíJ;•Õ·\rXWPqÓüó]…Ü#,Ãò¬ØrXc>”-]9™ó“9fÉëQ¨Å-=#fè+ÕÑ½N‘63ƒŠ|CÔàR¢§â¤„4\\¸®¨#BO4k¹ºf£PÃ©Í[µ‰Ïn´;aĞÀY±ßJèt##|€û\nv‰¥ã ú×[¥Ù\'L\nÉ»-ŠC4M\ZK™ÕghıGµ}ğ£áŒÓ:(S-ÃÎß»şË|9Ğ¢¹Ô¡8÷/€0>éÏöëú×İ~}‚Â’Ø	æ|÷9¯Yß•\nQ¦¹Û4>ü4şÍµƒÍA•²Ş¯bÒtÕµŒ¶Ğ\0áF*í††-aUTãØUÈáùpFŞØ¬èáÜuf5*¹=á·qŸxÕåUG{#|õ\'¥9Aãó®ô’9ÒĞ¦3U.ÀXÂç9«<ƒøš†Hƒ9\'æí@Ò2/-÷\0Cw¹½RÁ$¹e\0yayõİë]„Ñ`:å³ŠÇ¸³%O8ï^mx¸y¨­O:Õ´áÁ,F[¾y¬Y uÈ\nsŸJíï´ã\0ueÎ±/lü¶\'¦8¯z6næŠHæ~Í¸ã8íÍg]Aåo\0Àõ¿2ª9ÀéY7Ğ„ÜpqkètÅ;jsOvq÷¹¬û‹MêÁ¸÷­­OšÃÇ5Ÿ;¯Ò®7BµÙ†# ‘š¬Ñ¤Å_e˜ö5Ri|¢F3W\r¬ÙJ12gƒç?ÅUšß9´¤ î8ÅWY”xúÑuÔÊÖèWÃ®y§½˜ÚyËUøœa‡jHã\r–ÎjRHªm#0YÇİı*7ÓDŠNŞ}kdº÷\0”Ù$HséJåÙìs“Y¢É™s…ÜWI4Dr6â¹ëëC¹€=8®ŠRWi‰SVÕœî©/ÎÛAÁ¬‹œí<f¶®¡hÁÎHô¬¹¢ŒZëƒ¾æƒ½Œi!Êœj”‘˜t5®é´•5Z•OËºµ„ÙÉ¹‘örÅ·íPù@7h¬{™»\nkGµˆ­t¦®O\"q1o VŒñ\\Æ¡¦+‡Êîü+¶ÜÙ‡­PÃr\0úVô¥hêa%¥¬yˆü?æDì©Ïzó«Û3nå½}©ià£‚¸˜¯3ñN‚y\"¯>€W}:œºt<Êôôº<õƒ.xæ“«SBcréP•Ú+µE3‰;ŒØ7gÓ¨£5°íbZ)»LsN5•ŒìOlårİ­í&ı­Øl?ˆ¬(¢qÆÑøšßÑtY¦ÎjºSè$µÔâµgŒ†ıÖÑ€Ş ŸóÛñû“ÀúèÕ¬£s!aŒæ¿=~ø\\‹Ï´ÈP\"`K|ÛãÓÌş?vüóVÅ\'a»r‚¿ˆ®jŠ2W[œòÒV=Iaİ‚qÓµ!´\r„‡$Ù\r´™Á¥ë€µp¯19=‹h«Îâi¦ØÜı)ÓJU^ıê•A<\ZÑ.€­ğŒ1*Ó\ncTŒç±¨‹6ÖÛŒÒºfo]l.ĞTÔÒ¨£ĞR3n¶M3põ’cVèÇQ×\0S7 8Èõ¦ÎzcÚ ?95´_»d+ßNƒÚL“Ş£\'\nip=y¨ÏSRÚåmĞ‚C€EVy1šUù‰ªåCrãBØ™s7¡„08ªÿ\0üêìŠFqÁª’+n<sW®Ì\ZçÑîQ¸ûäv¬û† v­)×šÎ‘I¹èiÆÉèKß•Ó	¬»€Jœs[ŒezÖd±ã>ªãä¶æŞXF6óX—j_!šè®!ÆÑøV-Ì%³ƒŒt«“¾‚vÙİÚ\n•‡tÅt÷¶ıÁæ±. Úãu©RqZ­îr÷‰…#ĞÖ\rô|’+ª½‡—ãÖäY,µ;±­Ï™R_ziûÇëş5mmd#iÂÍÉÆ+×ò=5h•™Û=\0©â@r;\n¹Ÿ´Ã*@€ü¢„“ĞIİhA®[Ù«oL´n[µT¶€3dõ5­k8ÁÏ¥JÑ•îÍel`u®çÂº7Ú\n’s¿îÍsz‘=Ë„DÜO­{ïÂ/	\'RèFæUÀò¢¸ëO•3Ztùä{Wì×ğ‰#.åÜíùóş9ûƒÃ\ZVVà\0+Ìş	xU4Í1_`R@Ø£ø}Í{e  w¯2…?iQÍ›W©öc°¾IŠˆ@¤·Ò­PFAê¸+XáRfl±à‘ùScb„ûUÇ\\†*´‘OôÅ`ÕˆÊêÌ¯#…grj\"Ş`TîàššHwQ¬{K“Ÿ^ÕŒŸCd•ˆî¤É q‘ÖªKj\Z#ÇÌ_ò×Ó¶*-ÂïaÆEa4š**Ç-¬[ya_oÊ\0QŸ\\Öå”zûWc©À&‹Éa›qµğmV\\gÕáÕ§«g±F«åLáîtõYŒJÊ»´òÜñÛší¯-B´˜PO¨¬;È–ù\\úW˜âº”\'c‰¿¶EWàî êkv–,0k³Õ-I gdğ:Šæu\\ÈW4-ìi«Øç¥ÁGJ£:|¹=kBé6ä/ öª2F@9Ím¥ÌÚ²ÔÎ™OÍÜŠ§EÛâ­»’X‘ô!\n­Üš9yŒu[0DÇ&ƒr±†H§FÊWxâ©_\0Í€qS¹Ñk-¦½ìI§¡2(ı*Œ,£8=úWEie€¿İ«÷m©*Û¶@b=¸¬«Û¼qÒº!3€?\Z§©[*Äädv¨O•]–¤ÚĞáotıÙÆ9é\\åı›}EvóFrËX:•±27zèŒš–¦rzÚG%4AÇZÍœ’Ä[·ˆ£wó¬§@ÎIäW š8ÜZzng‡)8õ§n‘K4x-¶«<L,vš´“;\"VoZ¥$DÅ[ƒŞ¡¼õ­•“ĞËdÌ{ëmÊX\näu­9$†N6æ»Ã‘y¬mRÄ26+[ÆJ:óWLğ_é†ŞáÊ€3é\\û¡RÀkÓ<W¥ívÇ\"¼öî\"Œäö¯RŒù•Ïq´™D©\"|ı\rKLò“9Ú+¥3+´€íR)ÚA©»FsJ_jL.kÚI\ZÇ’2Ç¥tš>®	Hò6úf¸ˆ›nïz»kqåA?-+-Èk™Ûá]}[R‚åòƒ˜õù{×Üµ»{ˆ`kw.ŠBõw¯ÍoêÍox’‡e ä‘ÜW×ß³\'Œ$¼½0‰¤d´»êôÿ\0>ç9+FèÎ¢µşGÚ`ÆîÍÈ¨Ãá[êEtˆ+9l9ì3S2m¯;šÍ¡«lF‡p¦ò}ªB3Hî•1ÜÍBïr,g9éIƒ´¯ëR8\0Qmäã¿Zz=k£Æ*&?)¦ê¦£ÀÙÏŞ§Z7\ZÚÅ`)OçO1ƒŸ˜Ò<||»‰­!kh¼wD_ww58¦îÏJa@½z\ZSÑÜ®Ä=ÊFy¨>¼\ZºúT¡²;UÙÇfZ³z”›5FUùÛ§(ËëTdŒ¶yü*ítš&Qv3^3‚G&¨Ê¼kU—\0š§<`ƒíS{2b’Õ.IïTf@w`V»)çëT§‹‚+KYhRm+n`ÜÀXcYp‚¹Ç5ÑÌƒ/ÇİëX÷±õÀ÷+¥Ì-¥ìs—±X7ql$±È5ÒİÄHe<V-Ü<éE´fªö¹ËjQî«ê1–şuÔßB»X¢°/bà¯S¢’zgfî|å\n€ÓÖ¬¬bláqî)Æ%TœæŸo–eD]Ì{{W¯m.v©jîˆ\0¨Ün5^;F‘±[P­ª°q—‡&’ÖÙØå¸¦-­Ykmmlà1À®GÒ†õ$sPÚB7tà\nët1®\n„\'÷‹osXŞ[„tgšáV‰ÏñÂ×Õÿ\0|\'ˆ÷íÊœ.G>çñÍx§Ã½æYR8¢1©!|Îà§ã_V|!ğk‰ó+ü¥†9ú}8ÿ\0=üœCĞë£\'ûŸBøÀÀÇA]º E\n:\nÈğı’ÚZ¢¨Ç}+bº0±´J®ò\n(¢»F•f£`3ÛÕ68ÅW‘¸ãÒ³q¶ÅDFPTƒÀªÌ½A©š\\b ’L®vîô7Šc<¯z†e*9è\r$—`ÆåFpÛ@\'4äa$y\'ñƒ\\îÛ«­J3Û	îAãµJ{@¥½;b´àäÜÊ şï+ÜÕ3lV3“—È®\n”î›:iM­ŞÇ3¨Û••‰ÈéX7 Hí´åk¬Öaia\0A9Å`ËiØ\\0ô¯¥;=ìS“q»9ÍJÃÎLä‚£‚ó®7Pµ>g)È<\Zô)Ø:3ÈÎÃù×+¬B¨%Ú3ÆGã\\î6Gu7öYÃ\\Yª³™¬ùPû¸•½|:ãåšÁ½<¶j’¿ºSNîæ5Ì^\\‡=EUÛ»xn{t«ŸëIã\'ëU$;\\ñòúÓz;ÚÑÑB2ØïëVRËÌä€séRÅ—>•~ÖÜğ¢…3D´¹\r›P \n9ÍhCe…ˆÜ;ö«¶¶«óRHC`ç›¶£·FŒÏ³Ÿ˜ôªWéò\0ykQÙB¶ãŒÖ6£w–Ú£‘Y-#piìŒ{ˆAÍsúŒ^fáĞ­mÍ1•˜¬»¨ö™9<ŠéƒWÔÏ–Íœ…å¹ÜV\\¶¸ÜG&·õºFºV|–Å‡#>µÓsi¥ÌGƒ‚3‘TÈõ­û‹OfËmÇ±®¨8³I¥¡ËÁÅVxòO8=ëPÛ|¤7Öª:`‘Z/tÊV½ŠzŠ‚æğ¸ïW¤„òOZ‡iÉœVŠÍ´ÑçŞ&Ó£Œ~>•äzÕ‰†iA9æ¾ƒÖ­CÀäÒ¼sÅVE&íà×~zn\"–—Gç`céH’	Çj–â.H#ƒT„l	ÛÍz‘I£ÊÕ«ò}=iÀäqLCŒœT˜¢ÖZÕ‚­Z‡$’NLÕe;XCWíäÈ\rÂ„ØÑì^ig‚Gİâ¾³ı˜ô),om®ZA3!\"Ÿ˜œkå¿NMÆ}‹û0O¡q·q\'•mû¸Âÿ\0{±#è¥e;ò¾Æww–ÇØ‘‘o’€“S°ÛœSlß|jG è:UŒWšŸ¼É–Åm›³ƒ’{zRªî$\n‘•@ÇJlJK½½iGVRV»+‘ŠUPÙÏJš›Œr*4$b„ô¹”mÍb „qLü0}jbM4¦sëUÊ¾Ğ&®FœàsQ0,7g\"¬ã:Šâ$`\Zqoí&Şˆ¯´2·\Z\'\\6jÎÀ€ïP”(?…ik±rµ¡ğŠg5>Üò*6@rOZok°NËB”ÿ\07•]— ñÍhKØÕT”N/@MßS>aÀf©HUÉö­9Ôœ‚{Õàš,„•›HÌ‘O^£Ö³ç\0dçœt­ió’§¥gL dãšÑ$ô*6z’§\rYc!ˆ­¹€~nµ“:ä0¥%Êô)İhs—˜ùÇ`+\Zxñ»ú×GyÃ0ëX7‰´:õâª:nc{;œÕèùˆ¬;Ô‰®òK0=kñŠÎVÙ.ûŸ8Åm„%Û\'ĞšÚSJµ&8ÔÜÊ¼¶3±{Ÿò*Ã±.N@§¼Şilvé^¶sÑ¶¶+ÛF†fv%˜r3ëZ––æsœdT:u‰˜–n‚·¬-YœÆ¨BIíQ-YªŠKÌ—OÓPcpİ]¦ƒÒÏF98Éè£Ö°­md\02}kÕ¾x*ãQ’	Q›$°çÕËRJ(ªjJZìzÃ-»D¨ZO-¾f\0’:ÿ\0ŸjúÃánŠÊ;6£`çûßçüûùWÂÏ„GÂb8ç¿©¯£|§ı–/0®ÒÀ_Jñœ½¤¹QÜ ¡ŞçamÄéŒTÔ(Ú1E{P*±å·vQTï5­Upş5hH·¸â©ÏsfÁ$Jãõ¯Çè£›8äíäõ¬–ñı¼Q4bPXUA,k7$iwİ)ÚsÏ5·bÉêÇ¯µpòøÖŞ8ˆÌÌìÚW\"ªÜÍ†8ÉÂ„×ä“gM5Ï³;+{ƒ0“%p­ÍIê%Œ48¯.½ñ.¡hT?¾À¯^}jÆ‘âÙL­6Cp@SŠáS]N™FÉ³Õ%¹O%‚7$ç tªsİ–rÁ€Uâ¹X|H“Dá$FNj¼ş$Œ¦D\0tŞqEIè:1W7õ¶íOÍÇNƒ¹¬™Ù\"ì±ªrøŠ#UpWÉ<Ödº²±b“Ù¹8®\n—^ó;éû±ÕèWÔ%XÃòAœ~µÍê´¨AõİüêıåÚÜ¬¤1+÷rF3YÌÄí¯>ÉÜõé¸òß©¨¬¤uÍ^+1Ç>•ÒŞÈ<Â=k1á±5J*×:.’ÔçÒÔ 9=j·bı3ZòÛ²–Ú*5·ç4¹IQ¾¨¯ekóV½½²¦j½œ[_ùVœHªrj$¯°¾èHÂ8‚ƒ“ôëTdvÁÛW¦·.I\0\0\0ªÌ¤.3šIueleÜJJ³tìs÷ÎK¿µtw¿ê2 ¯ûµÎÜÛìæšŠÔ¸¥$fI¹FsÒª\\9 úúÕëˆc=êƒ¡ÆÅRÑ‹¥©pœ’:\Z¥!=ÁŞµ¦ˆ`’:U	ã,œtÍvS•Îi¥{”$ëÇãPìÎ	ïROÀuïQ¬Š	$ô®”¢ÕŒ[V·rc\0r¼ÕI!ë3V¥“;±÷jmÆi¤ÖÆ÷^¥à68ª&3õ­–Øèpxª\r	%ñĞV‘iîG;fMüàeõâ¼£Æv#Ò½†çıS\'¥p4²\r0>Õ½9(ÎÇ=t§cÂ¯á++U&éÒ·õ{m³ÉÆEa2‘šö Ïèõ¼Ó€ôïE*µ¢»vÉaU\0î­#UÈ==ª”19è+NÎ?›\'îÔ NF×†læBÁvÆ½Xµö‡ìÉá™lm#g—†+†#ßçüŸô=L£GQƒƒ³{WÔ¿ü]q=í­”k\')”áF=;nÙ‰JM4‘Ÿ2§ÙZKn‡!·uç¥_?J©£DZ\"€uÇZ¿³ç¯¥yİ42‡¼­b2€õˆ¾XnwSŠ¶İØâ…éMJì®„.Ã‚:Šœ÷qR²(ÅDJguG.¶D+üDO–Ävê*:²Ü³T;~r;V­Y\nQ¶£ñOÖ™¿ÚÍ{\nh]¼æ“å°{½7ÍŸzk®õ#Ö…šHÎKsÆx§u°î¯ÊBÑŒäúÔõ«åVÁã¹¨=Í9JÊÆ*ê÷Dnj¤ˆAb~ï­Yf ‘PHÄ\0ãµkxŞAÌ›³)Î0ETœ`g­]~\\½ª”ÌpÒWiÊ&n2¾†|ää˜ªŒ“ééWæG$äc5FáNÆàÃŠ›=ÑpæµÙ—7Ë»×§µfL9«<Tû\nÏš=jÚw¥{½Œ9¹İÈ¬;Äó7°5Ğİ@À0Ç>µwa“Ò‹ëcGnVÎbí6†ÇjÅ¼¹ÛŒ\Zé¯-XƒÛ5whWw<Ñ&­n¢Š’•–ÇÎë“nÜóŠÓL•ãó6@İ7f·´¯–o>eRŠ~Qß5´º`˜dW ”¯fwEÙê`éÚ[²°ÆÕõ®‹M±(B(foSÉ4Øcg&8×88úWM hîŠZ@1ëPô‹¹¢wÜ·á-=ÊÉp #å>¼û×Ñßtq{ ’(·Œ„L-yÿ\0Ã¿\n¾¨şcBÍ	\0GŸâó_Wü8ğ¬zf˜\\J’°Â½=Mx¸šÉ+-ÏJ4Ş·Øê| ˆ­ÆS¿@:×ªiv~RF3’NJÃğÎ–¶Ö ¹GsÖº›$ÀcS…¥­ÌkO{h¢›\'ú¶ã<tõ¯dóÌİgX6øŒn•‡ŞõäšïˆõMQ®­íKEÊ´ÀsÇüÿ\0_I×E“.ÒïÆÎµÁêvLn&W›Ê¶ùkÈ?…gRª‚7§kY=ÛDÓ!g‘‘	9sƒÇ5e«Ék$‚Kƒµ—vÅäuõÿ\0ëÿ\0Zîïü=jZiNï•³Ñ‡¦+‰ñ•§Ø$òº¢ã9Çßç½p:ú;Âq#²ñò³Ë°<¡NwÇù¹mñ=>\rÒˆ?02J1ôâ¼sSÔ#·‰¥¶i¦ÜI \0nù÷®2ÿ\0\\Õoõ‚+[¸-—ª?ıçë•”£m™»J*ëä{®¿ñlŞ\Z,ÇòrØŠÇ³ñËJÒÈn88ØÒù\0xşuç–‘^Gg+2B\0-¹‰4ûs¨O°F%âàÏŸÊ¥¨¤k\nmõ=‚Ë\\çsùÒ.ÃŒ	aõµàÕnFeeÂß.>•â¶ší–$°;Ø>HgÇèÿ\0ı{šg‹5ˆgkmVĞ	qÕT¾˜\'ƒı?,Ì¡xèĞ£²ĞöYoã·Vg2mÆ².<P\"bKg©¯=»Õ.%İfÆpªUˆÀõõ,3\\È‘G4†Tn3gŸÒ¹9.¬Ú:nìôÿ\0øH\"šÀ„rUK_ÍPª~LuÉÚ¬–î©ÉŒ°@?/áZŠ¯åã§Ğæ¸İ8ÛCÕ£$’dï?˜çœJBpsQÙÆ\Zi#Æ\0hÅlU“î+´´;‘–S,FzÓ±¥_kl½ëLX‚zN2ŠŒÚ1²²\"XğÄõ½^\\*€:UeRd*½jİ¼d§\"¥÷¹NzÆÄ©ÇzÏÇÚµLyf©Ï¬“»²!´gİ&baÜV5ÌYÖåÛ(Lnã½dNê¹È4Eól+èdL‹°ÔÖ]ÌHŠ­^ÔnfİŒz×%­¨Ş‚uR‹9gY-XëÙ°O9\\Ö]ÍÚ$d“€++SñC#ÌOZæ5R7Î»)Q´<Ê˜…Õ›×wà3x¬éuP3È®^ãÄi“sy=+.$€ínk¾8f·F²:ÙuÒ¹…BuâsšáÛYg?{ wÍ8_±\r½«¢4M{{hîv	â0…²A÷§Åâ4¶ò3^q©0v9†¡‡V*Çiûg*·×cÔò%ˆCœW-â_:)8Å?CÕÌŠ7Z·©6Çq\\’§ÊìoÍÏâ{o&wPì3\\œ¹Wn+Ò|g§²n8“ÎkÏ¤A¹úf½ZNñ<Š‘Ô¥¸ç­K‰	ò)‘©‘°_m>Ønb#Õs\"ä *í«NÆ5•€$ñ‘Y*qĞqZºÊ	4=$	­ÏNğ‡lîïBìAÀË¹Ï®Oùõ5öOÁ#EğÀDÑşaş½Wæ`ÿ\0¯ó¯‡ü3{yñ-ª™gf#n?^Øõ¯­ÿ\0g]SûDÓ_4ó1 ù’\rÊƒû£éÈÿ\0õóÊá¥äÌœ[gÖ:UÊMn›AÁPG»:»ÉÈ\Z=¦-‘±€\0=x­/³.8×¿3IhW\'-Ñ–\"c3B©Éâ´…²z\ZG¶P²qT¤ì\'+iÜASV\"™ïšÒhˆb0qM#®:\nZ—©˜°»ƒ…¦}–Fn}kT&3Å&¿5j-î\r.¦[ZºHÍ ´br;Ö‰LĞ±Îì\n9Qò$îeWÉàÒN¥Åh8RŒ=* ‚	Íi»h.^]ÊFÛÖ˜ÖÊÿ\0z®\0Hë@ çœÑË¡.=.g½¢Œpj¹µÁéZN9;ª´úPµ¹	+ìe4\0–ø{ÕWˆmp*Ñ•~cƒœÕI¢Èf­”_AítfM\nÜb³^ }kZéA^9ªOÊ}*T[Ü”®İúòG×³î£fİ@­‹•\'që>tÊWËt[·Câ0#`8¬´Æášé§]ÈØô¬ØÆN*,Óº!n´9»è@ß`]&ç>µÒ]©*ê:×=v0ÍÇ{\\bìÏ;‹Nê\0-Ê*ÅµˆòŠô_SŞºY, ÒìÖ\0¢K¶æGg9ïòßTZi]Îä±ÏC^ºÕ]\ZFWÜÊ²±Xw\r™?Jî|!áoí7YòÔ‘vosXÚ‡¸+\r{oÃMn-ÙUá{–®,KäîwaáÏ5&EøqáeHPùAwcî+Şü;¦y{vÿ\0\nà°éšä¼¢@(£’z~•§ùH>\\ ë_7çQ³Ù©jjÌØÒm¼¨qMkÆ\0^*­´b(TÁ«Q}Ú÷¨EF)İõUg¼J¨ÉêÃ’Çç\\õåà!Ò6Ç8-[Îj\nã§b†½«ÛXFí#eûí\'Ú¼Ç[×u\rBé¾ÏGC&Wñüÿ\0{ymå˜ŒŸïg­s\ZÜP¥»œa½qŞ¼Šµ¯±èS¥eg¹Â^Ïq–BåİOÍ“Ğ×«h)¨É!¹Û*AI#üÿ\0w3ÅAËıâ}>ñ¬k£xÎY»WªìÒ;éÓ´vÔágğ”\rŸ*o\"5ãËT5Lx,ÆìĞßÎ„Ÿ¸¡TÇÕKn¾ióÜã­Y·tÜÀøÖ^ÑÚ÷fë	«Xæm<-u-$Æ`ÃºöúÕÛ_<dÂ¸şâ©âº¨¥ˆd‘œÖ…œ©àGÔVN¼™QÃÛS–°ĞÉ“÷ÿ\0z\n±yá[{„*cb¤’	ÇÒ»XD.¥Š+éÆkBŞ(¦ÄRy=ö#ØêÛ¹åÒ|1‰¢y£Œ+c¢àãéŞ£_Io\0€&»×ğ¯^M=HbÁÕ)\\+ÓîqŠNµ·F”à¬yí®€ÁpÀŒu$:¯œÈ\nƒ¼cüûW -†Ş–<7F],-ËaGÌAÖ³ö—_äkÊìrV–Î—n…P­l-¶¶77÷kF=#lœ¯CÜSŞÇ°¥qŞ²“¼lv|ZœÅÄ®ß&WµUhÊ¹fò®†âÏœdzÕ6„\0ßáYEÙ+1³Z˜ñº¤ŒHÜÕ~\"ğ8úÕ{›U@[‘Ó4¶²uæ©ê™¤¤š½‹²à\0b³îÈ#>•nI€{VıñŒìMcÜæ¯b­ä¸wÁákŸ¼ÔV3\'9zæ—S¿2 ÷ä×;¨Ê/Î3ÜWT‹ÔÂn×Q1õípÊ­µIç¥pz¾ªè[qÏ ÖjŠ©o#mŞØ®*öÆK‰X±ã°¯R“ƒÔòä¥/ˆåµMVG,G>õÍ]ê‰–‚»k¯wc¯jÍi	m ëÅwR«Ï>tß6§s$­’	Üjº‰Æ{é^„Ş¬¤Û‘L>	hÀ%@QÀ­ı¼-¸½‹±ÃÄ’*’ié<‘qŒ}9®Ş_	:¡)8FoJA&<}qQ\nÑ{ªrG)&dF\0g5_k¦pkµµğÑ²œÑs¡]Û®ˆÕŠv!Á³–Óµ)-œá¹×Øê	y	ÁÎ;zVLš˜Ò§Z´!±œç¥c(ÆHºJIÚæ_Œ,wÂÄ€‘‘Á¯\"½çuí¾ ƒ}¡ç-^?©¦Ë—¶K£\Z÷Næ*[y<{U„ˆ)ÏV=O­:­ÛB1##µw¥c—bÓhÚµ¯§Ú3úÑc§âB[§µwğ«ßÉ¼q/ÏËÊÇGáŞ³ºÜÊö4~´ÔáıØrß.:¯ò¯¼şÜùV–ğGiÌ’„a¹ïúWË¾øK=­äYŒÎó“å9\\)^ù8è?ı}óõ§Ã/Í¦Û !£$–n—ùúòÔœz1«Zç°ÚÌ\Z5=@ŠœtªöQ4HA5b¸ÖºÜĞ:g:RÒb‡u°\"\'QŞ”Ğğ©_¡¦TÕSvº&J;²Ì ®qL^§Šs¦ŞzŠB~cO›Ş¹ëF3a­1¤bpOSQƒŒÓR}ÆµÜøÅ1”€Ç#n>´÷íQãi,XÖz§3¹]Á©GÎ~î=iÏzæ¢ÁÜÛNÚ­H’³#`9=j9BY^wP0Ã\ZwvĞÎ)Úì¥/Ì	ÕY9R*ô€)lU9F})Æî%µÔ ã\0ÕöäÖƒ¢©\\Ç”úU-‰VOC\"p\Z¡2ä5iÎ€!çšÍ•7nST¹šÔ‹»ÜËŸ\0`ş9¬AB—#œšÜ¼oOjÃ½\\ô8¬ïth“ZõñÀnÕx™ô®ì\'¿ZÁ¾@ÔŒ‚1JÖ•Ñ	(³˜°Csp÷ò{{\nÒºº[„#7¨Z5ÒìVIİWpÊ©<šÊşÑg\0ç{u¯bMhTRzZ\r£y£Ì}ÒÈÁKĞdãò¯¨şøs6NW’kç?X–‰å\\åƒµ}©ğƒÃÍı›\0n˜=xXú—Ğ÷pš\'\'Ğôic»I#­vö°dd\0ªºU‚C¸÷@µ‘0­øb£\rG•Ö­ÌÁ T¡•äğ*=¿.j)Ÿju®åh»œv¾…mBü…*¼/­bO*( `SßLAeêsz­ì‘#.Î$¯¯¥pW¨Ş‡}*}†jºš#yjÜc$œ×«ê›UÜÎOŞÇéVoî¥cØ<óY’@YIÛ’Oëšò¥;œhò«³ô¨ŒŒxöÉ¬[ˆ•Ie;Aëò×T4)ç;’#(\'¶*+	Üfp©ƒëŸÎ§^[³²›Š[œT¶‡½S’uŒäd]%æƒöbÄ+p}+’¿Ú›Šå½Í`›wHÑ5{¢õ¶¦\0Én=\rhYj*F7d\ZánnÚ¸7Ê<ÔKâ6pZŸgsk6ô=bÊàí3È­[+İœ¸\nóÅeßkÑœr{WeêÍåù½Á¨•ã£!½m#´¶½ù0ie¹Êóšæìõ·fpM]KÎ>læ¢ÎÆv×CEOsŠ|q	›îş\"ªA)•\Z®Ú@ñ¨àñúVqVºfÏ—QñY\'¹ª×0Hû¾µ­iO$uúÔĞo\ròpzĞ—2ºJç+}ìáT}:ÖTöì¨yëê+¤Ô,Ê?N+\"e;J?àT•ís²÷NZı¶‚¬\nËK¢ƒ®ó­-[‰%çpö®VæıPFÓéWtõF­%&lAQçÏë\Z˜¶Öù8JçYùŠîãëX:†¤­¸	7NìÑİÙŠ¾Â½Ù’_˜ç\'¡ª:„Š\\9Ï¥cM©|ä’:÷ªòj¹Vù²*ÔÕnbâ¤X½”LHùvûÖD‘Æ7Ó.õğ½ºÖkİ´¬Ù$Šé‚iXÉÅY–2¸zæ¥¸ªÆ¼óÅ_²‹róÈ¡ŞÂT’Z¡ÖÖ*ìØZ»Ÿü® \\P!Ï`jÔK\0A>ô7)lfé$íX}&…•OÒ±fÑ²Ì8µ¢ÕÆ6’)MÄRÈ/ê* å®§$©+]£=$FçŠÌ¿ÒŠ±(>_Jéço— Öl€±#­wÂ¬ˆÍÃK	j¡H)Éª_c$,«ƒ]+é­.vñôªSØßozŞ/™^æÊ×hâõÛ c`xïÅx¹òŞÊ¤tc_Ek6ãÉù†Aà“_?ø™uk¸ÁÎÇ+šêÂ½N\nñÒæ$@ä÷£bN1Š©{I•µae¹w£õ¯BöGŞ¶:øvóX‘Å¾ÅÙ¿ü^ÃßükĞôx§J”$ZxŸ{s´\0ö#?q¾\nñ)Ğï‡Ú– oSŒß>µô/Ã¿‰º^¥wl—2åß9ÛJöÓğÿ\0\nÉ¹ßE¡šv=áVsc/~ò›– œ\0U?ÙçŸ€¯§¼,Aµv¦ÕF0kÏüyeªÂ­ciÈ?ÖKíê=kÑ´\"³1%Øç$W›=û\ZFÑºŠ5Æœ\Zwf›\Zù|\0TwQNRsëšQwAË×¨ÜÒtÉõ©w&šŞj»Ù•}.BÃÁàÿ\0õéÎö4FIæ´[™Æ×|Ä>­Fÿ\0|Õ“†íŠ¯\"üæ¦I±^íŒß>ôÍ¼œñR)¬Ã$cñ§=Xâ­¢ ÆqAUe8æ•‚†ö¦U-Lâìíb(Èoz—<?úÔ»ÿ\0vW{\r¾TÙ95ciãñ«$áM@áB»gw±¤õ‘6{\\¡.?„şZQ† ö«³yT¥Æî+FšNäÙîÊR®ˆéTîAÕ¢ê¿$Õ€0ÄŠKm—±‘>6·5Bo½Z³ ÁÈ¬›ƒò±Z¤õ2å2®#?6zÖÚë[“0Ëù¬;Ç2=jU“ÔŒ+°ßs×cƒk£½qÏ©®rù\n’{+f›“Ob¶z{~Ú„Ë½²ªsÏ9íVl‚¯p_°Ís³^Glq¼´¤÷­¯C%ÜëÊ’HÚ9?Jôå¢}©ÓWßcØ¾ZjëöP€|”ûû}{ŸÏïßè+§é0!1@r+äÙëÁIÿ\0	5¼.áŸhygœ{vÿ\0?ÜZmŸ•îøÀö¯¤=¦#ÉÃ“¥M.å‹hÂ\'¹«q²˜±…©T`b½\ZjÊÇ)\\`ãŒäÕKŸºÙã½]c€Mg^0Y‰¨š±T÷1u	#MÜsŒ×-¬]o¹­}NRÅ¶yÆk–Ô§E,I–ÆzñêÊí¤{tc±HDÓ¿–ŠÓItš7„Úå”H2z½)şÓ¾Û\'•\"%ÿ\0[!}«Ğì­Ş-±¨P3Ml2¨îÈÄb\\\"1ÃñZB¼\0!GJçõ´·‚3³÷‘]£<*Œ‹€+ˆ×®<¨ŞGEˆò©<k|L#éĞÇï¿xóİxÅ‡\np£\'ÜW—ëvéµ‚>Ïå]ïˆ¯£`NF7Zój‘ªÉ’ xéƒÍxm«ŸG’Ñœ¾±!»ã<W3-øBùoÖ—[ÖQ¥*>m¤Ÿ¥r·ºä«uïë[Áß Ó²:{/y~§Ö½Ã~/Y‚Û”Ç¨÷¯\n[ğ€I+êksEÕ¶\\FÂF\\NzU:vWhÕZKŞè}c«‘”±Æ{×AozqŸÆ¼ŸCÖƒ( \'Ö»\r?Vs=EcmtâµG i7>‚jèí³&á¸cıšóİ\Zøy»ñ¸>S]î™r\Zd&²pHÁ½M›d*¼ŒRÍk¹IQ“ê;Ó­Jº€ã wZÕ	#8Î}RŠØÍÉ\'s“¾±ç-=½«“Õ-°•ÈõõèW‡ó3’GÒ¹*˜åSÂçŸN•É4Ñ×NocÌõ¦€\0$×Ÿj—¦7`\0=«°ñlZÜ\"äFWyÏzóMN~_9=\r\\~‡c´wêV¼Ô6«\nç®u“Î?\ZKËİÁ95‹$ù&ºéSºÔçsÕØµ%Ærj›\\¯ Ş«Ü]€óÛŞ ŠU\r¢µPè`ê[H—{ÃÆ–ŞÔô\"¦€ïLµ©cf$Ç\"‹èBm«‘ZX€:UÕ³1ZÓ´B`jt‘+¸æ°œÜ\rùoŸ¼Ş»€üc\\»G“šé/!™¬;èaÇúá‘÷G­kMÙXÎwF$·ÏÎãRÁ~àœÜĞö‘ÈÛwŒTofP0È÷ æºãkêr9I&‹Ñê~fàÜãÒ­[Iœ}+šg6ìH8úÕ»;¾	ÎM<º#>¶gO\\ak>ò,œ(È–r‡ğ©!zÕ{Ñ&VkCW²’K]¬8=\0¯¼]oö}vıB…ù>¹Ç5ôş¤e«ñÛŠùÇÇÖ‚ÜŒÌŠsÛ‚Eváçw<œCJG-l›I5¯¦İùlWÖ©EÔÆ3S}àe$¯VÉèÏ15Ôôoxv/H–ñs0RI-€=Ïùâ»K_ƒº®—;¤(NèÂÀÍz‡Ï×>uàıN}á\'Šä¨u=ÆzWÔŸ\r|{i¨A\n^ù«D¢HëxîOÿ\0X¬gí÷ª¹»ğ£Xñ6Š °·õã¹n7Böˆ<ş~¾™úÂ·ZÄ*×(Ç+œ…Ípğş¯F±È’ÌHÉ#+€:ê?ÏJôı#O[o#%Ô`sè+‘ÊÊÍjiÓBú| â\ZïnM:ã¥.ÍÀàT(¦š}Fá¹¦†¤ †lÒ8©êâ%£°İ£¡¨ñœçŒS±ò‘@AÏ5jÛ‰êüˆÉqéQº’Yºcõ©ö+İj\'g-ôªŠ]Ë&ô+(Ãznq»ğ©Jã\"£<Š—Ë¡&Ö£\0…>”÷)¦ÿ\0Ë:¥t¤Wg\'#<zS7ã ËSÃ=Å@Çµ¢÷ºï$4ƒÆŞ•Ÿ|ôa›Z†AMºÜm]ersÇ¥Sus*ÜÃp«ÅZo[¶ÑJRNAU9¾`8«òà.MgÊvî=qDUÕ†íc:ãæ\r»?0éY3®ÕcŠÓ›‚y¬é›‚;ã¥[6İ™+…>üVÈÈjÜ¸9È\'¯ZÅ»\\úÒk•Ø-ih`İÆy?†+ì7ÍÏJè/È½3\\ıÛ«9ÛïéKšú1E^|§‚%ÃM)lrk×~hñŞ8Ô¤;¢RR0O\0ƒÉ¯ ²dP7`Ôñ_D|3ÑÅ­œ¹bÒ!ıêõj4ôgR·]Ïª?eİŞêWz³Eò\0!Œ°çƒÏáş>ù?QÀA\0`W—üğÿ\0ö_…c™Ód’ØÇAÛüÿ\0>§ÕákÉÃÁ9Î~gf&Wj=’B\0æ@üë…ñ§‰uYµĞ¼>ª/YC\\]·İ·Sœ}Mzİ‘Å«Øêõ-^ËLC%İÌp(Ë¶+Î<Gñ—A°–¦mBN˜·Œ‘íÏùıEiéíüıjê}Vå‡Ìen?/óüë§¶ğ®‘¥&-la‹ÂóY8Á&åvuAÆ]O¾ø›âİ~F]Â•=$¹vQ~?bI¦|O¸fw]3N‰¹9}Ì3ë_Cê¨©;6ôÛÅq×ö-y(9*„ŒşuåMò?…3º”¤Öß×™…áEñÛ[}«1ƒÌ€ä~¯ùÇ·=…¾ã«ˆ2ëpBÁ’5É¥nh‹+5Ú }iÜø‹OÓlüë©ÖÆrçÙ„¨úÅ}Ç4›ø`¯ø³ËµŸ…¾9hJYøÒXÔ£Œuö¯ñÏÂ¯G¨®>!^s\ns××Ú½_âíKáß‰’)ÄûNÀœ¶8éÏ§æ;‘Ÿ›|[ûRËzÒÏmm#ï\'l¥	U0ã=0=øí«Êrø`›ÿ\0\n:°êtÓœåoºú™%ğ‡Œ4vÜxîâî3üª\0w$ŸÎ¸BÇ]»vx–äeÁ ™â/xd’é\'2Ÿ¼…GÊ9÷ïŠäçø£\ZÚÈÒFêÌqò|Äsüë…R­5ïSWÿ\0	Ñí!=ªµo4t“é÷Ğîi5¸n²1ƒ)×Œçÿ\0¯Y²É©Ú¢	S€ÎA>¼mãñ¬(<mc©¶G‰ó÷Jò>¹Åi[;²Y¤ó’sZyJî5‚m[¿™uìµHãÍh¡;´s+ñëOÓõÿ\0!ÊËow¦abâ3UÚæá¶ÈÊW¸jk-~æ~i$Ï±5ÎùdµEÚºÑ=>ggá¯Ø4«÷\n™éæ½½z–…ª£ÛYctìV@Ù¯1ğûizÄB;Ûk•ŸŞÄ¤œõç¯­u	¼-w8–Ô^hÓ‘-„äsŒ}ÖÈ®IÂ†Ú§ò:=µXEs+ú¯áùÌ„%±ÆkÓ4‰ÌVÑ ‚ï^¢ü9ñ>“\"K ø¬_ä[ê0ªdzo_Ãœvùêm>\"kşE‹ÅŞ;oâ¾ÓAš5É§¨ïÔzg	Qv¼]ÿ\02%Z2g¹éØ=‹¾k¤¶…¥Œ”.½y÷Ãÿ\0è>/[JÔ£Oùâçlª}ÔóŞ½;M€2leç9Åg\nRRjJÌåœÚWf&«o\"ÛH@ÀÇQŞ¼ÓÅ!…¶ä=AÎ+Ú5;\\Û•=Î0;Wxß÷qŞNxÇ<ÿ\0…cˆ¥É«:°•¹İ™á>1¾‘!›÷aÙ‰]¤‘øšòıGQ*¯“Åwş<¹ L¹*Çó¯!Õ.IÎ=éĞ¦ç§Z¢i$õ(ßŞrvj€¸c¹IÉªSß™$b§Uä½D$l×tc}Äª-[e‰n°ä@§A1<îúW=>¢ZVX³ÇµKo<­üDÕÕ<Î/oK¹ØÙÜÆ —qZöÚİœLSÏBàdª°c½yù€\\BcvÜ§®Nk¢ğÛZé–4YÊ$Êó?\ZÆT#vşãJX‰ÉÚ1ÓÌèoş$iZX0„¹3çŒ,\0¦YøœjèÏI°ô,¬£õ¨cHnÙšcæ¥ÈÅSÔ5;=>ÒVûLQü§pÈü?Ï_®9Õ:MÚÎåûjºûÉ\Z2¬,÷ÈÒ0$B#!‡¶sT&’ÊH¥K:¾Ü\'–£i>ä×qñ\'K·;šàHÄàçùUY>%é2€Í3$]8MßÖ»#IïÉ§¡ÉRRëQıçCt#WcÈÙïÇ_jÏj´Œ“ÈBó´?¥RƒÅÚuÒ†IÃ)?JÔ‡W³‘>i¾‡&µ‹¶?·ÛoæR3KpK+7<çÕ(f†Ü•¤aÀÁÿ\0\Zd’Ç3¹‹$g¡â¤ÓÛË˜ıjİš³@©ßy?¼[=kXƒx“L\0m\r\'\'×¡­«}jY³¾ÚT>›N?>•oOpp1ZÖvI.WqõÇtş‰têE_šæ\'öı£A\"Jå‘ó3kÅ>%„›ÄRËS ÆŞ€äñú×{oã[‰¼M}¤ŞÚAwi»Dnƒåçüÿ\0“×Z|-ğ×‹®.ìmté¬æd\rö‹#•YŒo~0k¦5Oßîysœ–’î|ñ§À³ B+¥]^Z„H÷ÉÆÕ\'ëwâÁWáÅÌwNŞv—3ìŠny\'ø[Ğÿ\0?Ï4´yd’8–a+0PËÛŸZín2Ö\'+ŠÖæ‡Ãû›IÄæ\rÃ,*K ñßµ{×Àˆ`ÓuiyÉBTœa‚Ôïzÿ\0ú«¸øe¤èÚ¯‡¬ü¸îb€™9ïg¯=qfÓ~Xê¶P¼–öï,D2¼ˆ£zƒ:×4êı‰}â§ÌÚ×ùş°³µ¶ÑüÃ\"î2“É˜ô®–5åëYúFºuº¦íÅGëZÑ…PwW\ZÓ­Íe>a\0<Rƒ”÷ÛR*pÇ#Úª.Ä]ípÈÆ{TdäÓ‚zóK°R‘vÓ\"“<RõÉ¤ªô(MÀëŞ¢vÎHëS5(\rÅ	=ñ_oÈOåQ7J°äöÿ\0ëÔ%q‘œZO_x„õ#Îj#üy9éR7SHS«Ng\"£.ndWwd<qQsR°$?¡¦2mïšÓN„EébŒ1áG­Bãï|Ù;m#¦qP–]§¡ìLŸDA\"|‡ERb72şµpü¡ŠüŞÕM×\"®:hŒİ®V•r¤ƒÈ¬éÆKÍhNp¸Î3Ú¨ÊFY©(ÊÁ£¹—p»ù«:áp¬\"´f]Ùæ³%ãpÎ\rWÔ[îe^r¬¤ákì–v­ë°@+Ö±n‘¶¾5M&\'{¨ô9ûá…lõ=Ís·\0åµt—ŠX1šç®T¼²ˆÁb½vŒÔÙ1ß]ÏğÉ†+È^U%Qƒ\\WÒ?	4éu^Y#S4-´²\0Š\'¨à~œ}3ó„`İ)b\n¡Ï=?Ïø×¬ü4øÄ<#iâ\r\"ñ‰¬\'ÛËŒ3´Œx\\ŸîóƒÛÔgºpnıÑèAû9§-Vçê‚í`µğõ”Vì­qªåGJÔ—PµµyãŒ´q_$şÄ¿¼Gqk¨è^\"µ½kaµí.æÓ·#Ù8Ï¯®C7¨xÃCQñ­íä–7wv¤K\n0øÉíşsëSB„i®Fî»®¦µa%Qó\'®¿Öç¥ø“ÇÚ7‡4›«ÛFÜ$([hpI=€ğ²å5«!©‚ÜæéŸ9Ébvÿ\0ã¸?|ÃûCéº…Ÿƒæ6¸Ú³ËÂ“ëÏ=:r8lÇéÙé´Ï3‚¶Ğ©üVµ9.·v.$©N£ø••½®Ëæz•E Ú¤ã$zT´Œ	V\r\\ãG3ª@gŸœíıª‚iFK€$\"4·5Ò½œŒÌ}{µÍêÚ5ÕİÑ@ä)êíşÏ¯JWÔï£+é{>(ñÍ®k$6›®®mÄc Jù÷Ä‡Ä¾6¹š	#œÉ*–ã*BôÎ^‡\'ŸC×æú’×Ã)¦[b(ÊybFj»áqz\"Ô­‚Å¨Â»ñ‡^r­UNšOš_pÖ!Â<´to«ÿ\0²>UÑ>\0é“Ü*êÓ]Üd—ûKåW¯öÉïë§<oÅ?Å§ø“MÓáÓ,SOÔ#eŠ—hb£xãŒœwç¦Ü©î|MÓÛjkÚ`+ÿ\0ë¯—?k¯ê\ZÍÎƒ­h:¬PÁip”ƒrŒ}O>çİ[JucíydìrU¥YIJ¥Úï¯æxïÇ/‚Ëkáí7Å6lÈ•m¤„µ”ç\n¨Áı{dWÏ_½UÈÈ\'ñçŠ÷ßøÛT½³²Ó&ÕßUµµŸÏ™\0IŒúşñÏ]iˆ×R>~ó–ÇÔ“]°”•ÔÄ©»èîd}ˆÊXJõêŸ mgOÁ\0bŒùÈï\\,í…»Æ¤y²Zöß„ö6>ğk\\^ËVa›æ_\\ıÏ¨ókÎğiô£%\'wc3QÓÊå¢b¬¡~ğdÕGÒÖåsù»ŠÓ¿×m/æy|Õ|ôÏAEŒ¢k…•<î8¯>Ï–öhö°Òn6˜´½Ó.ˆƒq‘ÛÓüÿ\0úıkA¼2,k’Ã `œÖ‡,¢Õ¥û,Ğæc)½k®¶Ğ›E\r½ä=\rsT¨›×FuÙ}ƒÓ< ¬pÀìÇ&½#I„X^<ò§šóÍLÅ±vŒ‚s×mz“\Z¿ŒúV<ÒræG™R)İËTÌï|ÑüNŸnÓh:üyk}BÌy¼çÀûÃ\'õ5»ğ¯âZêúdúˆ®`ÓüE¥Êmo!•Âî ü®3Œ† ×Q¦E¾Ô¸n¼ç×ˆücø7\'Å\Zx‚×DÚê	k\nK,Í·fl±ÀèzwÈ8>•ªÅóôë»ÿ\0†şºMM©j¿­¯¢ßSèIuı&[fcªÚ‘	‘x>Ç5ã_u­7d¥5K6uW	×Ÿóšòş	éâ·-©üL¾gî\"BÀ}2Ey§‹ÿ\0aûıâY›Çz”Â#òÛ[×œğÍÆ;ıhÆÑÃò¯Ş~ô°Ñ¥Nî»ì®ÿ\0öÕş^}ãñ¿ˆ`¸yåhäpÅÆx<ÿ\0œ×•kZ’Æ\n´Š¥ú fµµŸ‡—>•Úk‘väËD~;““øıkœ¼ÖWK´’§G~]¾V”‚Ã9éÓœuıkš*QWŒ¹‡Z­V®ãsœÖ5u±Ó®n”È‰”€ÜO\0dôäk®ñ/…´OXè:5­Ôš¿Š#Œj ÔİLq@îËX”öQ{òO\'jğ¦M–ì·ÖxŸ ÂX\0w61Óßÿ\0×ß¡·‹ì¶³°›O—Ïh¥‚w/\"ºc!¶kÒ„R’G›*“«Z0Ú6wóÛòÿ\0‡+ÜC\Zcb©>¸ëUUÊ‚Äí5rRd\n†8+Ú›o¹Ô©ÇR(.$’x¥ŸÄñÚàÒ0ÀQÉ¬}oV{f’Şó÷ßZ§ jP[İù“\"d‘’F{ÖjÛìW´tã¢65Û­fÃDšúgxãA¸\0H	×Ÿóéßš‹ÁŸ4ßŠŸ\ro. Ô¢‹ÅZp–îìÜ¾S`ÉQƒÀç¿9$të<Kweâ/ê6ËpÄ‘|±tqÿ\0ÖşŸOÓ÷‡nçx‘äAÄ!ÙW9ÚŞ£<óŸñê¥¤ÛZú5iV›wv}: 3¬¯”Ñ¥:cüõÿ\0<»ìàNdî;÷­­RıµÍBãRš4æä)p§ÓüúÖQP	Ïá]•¢NÖ‘ÙøsNRµ%2 ·‡ŸÖª_Ø\\hs–„’	ä7¦}Ïøôßt³¢hñKq\"›‡,Å{±4ßŞ¥ä†ÔJøÁ\n:ñ®yM9Xè¥\nheé\"\rùSÒº&é%sßw Šá×Jx\\³õÒèå‘×ŠÎqñ;i¾Œô5ÀVÎ>•¹¤Í‰À?JåôÖ,­{[†ˆ“’zW›8¹3i5%dyÔÖ‚Óâv£@Îe“;€ôÿ\0ŸqøıeğÁ³Fì÷vëœA*@ÜTv?Ïóú×ÌúçŒ¼9áOXêz­ä‰<Sy¯qÖI zd~c‘‘^Ë¦şİ>	ĞâOì?	kº£…\0fßbœÄdş•éÓçt—*g‹:ªäéÅ´}ãoƒºg~xŞÊâ$ši–$Nq\"«2}Àÿ\0†¾øYá{=^I`ºuà>T…¾R®3’Àôêzç ÷ÎOŞ_³Æ)ş1ø7Ç:ÔÚhP%’¬pJrÌ6ËŞ‡å‡qŒğ·Ç«ŸÛø±æ·¸–ÛQ–.VÎs!ÜH/´rHç¹çŸ½ƒ²¥8/f÷g4”¢ù:ÿ\0ÃşGØ?´»x´¹-ÓÉeE13Ï³×ñöãÙl,Eª\r¹züÚøAãíNHŸIÍø¾7p›K¯\"Ep€ÃŸlà§Œ6~oÑ¯«Ÿé_“ö×€s×?¯ó?S\\õhÊš¼‡É(êô¹³\ndúŠWmÇ¯*#+x¤x†Ö<·Ø›>Q‹éKå‘î)Â\\Ú‘>s»Ç:Äj1zƒ‘KJçMPA>ôŒF²ò1M#Ëšf5HÑ1£•l­ïHË¸:ÓÊ“ØÓ|¬çœbš²Ú*íÀeÆO­7 ©š-…†xéLdò~\\cji³4ÊÅF2)™ÅY}ïóšD„3Ò¢\r7¨â•îŠGHâšëòôùE^òTuÁüi¦1+N—3iı“3c0 /9íQW€§¶â·Q»#8«PÚ úûÓæM\rÇemYìflì…ßİj%Ò/]Nmİ@õè¶ˆØÈİõfìª&\0\03ôÛÓc.SÌ[Aº9!TêMg]i/Ã°_aÒ½ñ°¬Y²Gzä¯ØÉ3İ…(IŞÌpŠ9‰tµ,pÄã¯5F],!=Çl×A2„ãŠ£$ca\'­^©4ŠåÓM~M*İ£p¹ûÁEf¾™n¡¿t„zÇñ5ĞJ¸‘=zÕ)mcE(İ«\\Í7k£›¸ÓcÁ%;VeÕ¢\n€÷Et— 2k&êg=j—ö³æ|Ö9o‹?³4/!¼²iñ¼k¤g¨úãñ>¹9í¿f¿ÙîÍvïÄRD·%f²OÊ¾üwÏ£~ÒŞ6±ñ®»c¡Yš+óåuçsvËÿ\0¯Ò½¯à>‚š7‚¬”G°Ê<İ§¶ÎÇ­vVr8Ùë\'øå\nFUšÕhtú[(’­Ö!\n¡W}…tQÈ›”Œzâ‰mã•6²=*²½¹&\"Hô©§OÙ­yÍTwÙş\'Äm&-_ÁZÅ¼‘¤¡­Ø…u29è~•ƒğ=—ş(£\\|‘Ä8ÿ\0wÒ»J¶i×1wxÙ0Ey¯Àû°¶÷v¼†GB	èUÏô\"ºÕ\'äÓü×êoE§‡«º?Îÿ\0’=ZŠ(¬ª’[7xÀÏÕ²@ëU&¸Æîµ/bá{èY·Tî37¡ ÕxoZ(\\‚Ş™ª÷zŠÈ	‡jç•D¢k´ÎÇ\Z-­Áy%„\nS~ŞO¿ùõ÷¯	ñ_‚TKëoİN…ÔsÃÀqş}ëécVB¬†4à¿L×›ê¶6w-)E½p{cÆ¼J•3¶ç¿F\\Ñå’¹ñ×‹>FÆÚY,˜õT9> Çëø×–_ü Ôìî%ß|DJxıØæ¾Ù×<\'…Ş+Çç¹`}¿úÿ\0ã^s¬xFP\\¼şh\0‚ÁGç[G(«s*0né0Ùü<0]y¯/Ú@\0‘‘ßüktéHœ|Ò8ç§å^­qà€¤âVUÏT\0ãğ?J¡7†KbFÛıâ£š•Š“v‘¢£=æ“xU5\"Fu¢¨ÎÂ­/„æ[fX^HÆĞ “Óœæ»ÅÑ€»‰ïŠ±\rˆNá·Ò‡Y´ìÍyt9ÿ\0†^Ô4¿G{5ôÓGûŒÄ\0{cßüúçÛZí¯m<Xvx<ô5ÅèÊIULœÒ½+Ãú šTvEëšãšæ³ã>HéØí´Œ‘F`ª(b=+µğûÛ¨–Kˆ„®p±3€Äúc<šÆĞ4ä@#o s\\OÅohV¿\nï¬î-Êë­r\0“G7Ìñ÷\09ÉÛÇ/V\ZÖ*r^Èğ1¸¹ab­.gmvÑêì—²ùüYĞ5é¼aã{«-èG¤hCeİÊr\'œç1/²÷>¼v57Á½J^jr®÷¹Õ%‰O–ŒBöï^û\'ê:×´Ÿı®e¸Ñ¬í†­ó7dŒ¿Ìy9ùN}x?í7²ü/Ö­`ğ.“cfÅ#1»›‡] ³çç,F}«ÛÅBJ2Škd“]÷×îkĞÊ—¿)4¯~Ué}[Òÿ\0Ëµô½UÓõhÆ™u™11^O8âßµT¸«´O^O¥&³ãï¦˜X·±\'²A˜â#üçùù¿ˆï¦&^Kü&¾Z½YUŠ‚=Ì>ØŞ£êy?Å(¢k‰Ë\0¥ÔdıkÃ/ „jÖÆå	€IÎ;\nöÏJÓÇ/šÛºc«Å<H…m$m9ÉïZa£mº^í\\]5üc¦Zj\r:[…Wfl(î¹#±8Ïn~µ?Åëù¬5»ù”«Bú£I R[jHœvÔcÛé\\³3^FùfÈ,ô5¡>¥7‰<\'­5À2İÛY¤ ²ıà„.?!ú×½A.TÇ‡Q+©_U¢íæK§ê±_F|·ÎÎ<øU•»*¤/Şõ®CÂÄŞ;]ÆvÆÊ9#óş:éŠ•ëJ¢JN(é„œ£sëKi.$lòÍš|:\"ôäéZÁÆpy,[29Ïµ+èii6%Ÿû­ˆN\0îsIsà[}A]ØírzŞõ³`ˆË€qï[VVªãh~+	T’vFËXó;Ÿ‡áä»G\0a¨Í^[wS#y¤åÀëC†á9”)½j5ğÄX\'íœôÀÀŸ·kFËXT×5>ÖÁäK½[‡GT	Î:âº¸t(-Û²{æ¥6ñ©Ê‘Y*½Q§\',tĞáo4|“ÇZ]?K1qÆº©ìA\'ÓÖ›ˆ¹÷­áZëSF•Øí2ÉBü§¶\"³\rô5RØˆÔŠĞ³-,½qëQ)7ª%¦•Ñèÿ\0³×ü;©xºîê÷J¶¸»U–xÃ±Á>½¹ıOÔ}ac¤ZXŸ.+X•ğ¤j1ù\nùgáDíc¬´êp	€z÷¯«ô©Íı¼í‚@>ŞÕI7›<:ªÕ„ÚÅÄZ?Ã?ê{V0,%ŒÉÀ~­^ğ§á~‘£x/J¸q}²ö»šV@]™ÀcŸ¦Ïn“ã=òéŸuHO2j³TÇ«¾?’šè¬-–ÇO³¶@AoJGp^„½Ú:uçşdÆÊhßåÿ\0dÙønÎŞc\'ÙâWèv Á¹åï<p\0§*¡Å;¥q+½Åki_½.ÀÇ½\0î£½…©\Z`ƒ”¡>é¥Œc4ÒqJ7ÖånÇd\0jòÀÚNÖñLÈ(ãÓ˜ãšJ?/XÜ]ëƒµü\n¡$’Çó§Á\0u¦3ïB—Fh¹Ç<Ñ€A’‚¬„Ú2p0\rG~µ.	^F*9FFÁøÑ¤îK·)˜Wpã\"™ÔÖåN:R`xSùVñIhÄÜºˆ­µ[Ş‘iÍJãjäv¤…FÓïPÛ½‘švÔ}°Á>õzİ7ªğÃ‘óV´ 08éN+›Pæ²ÔšÊ=ªäö<æ«İÈKÖÑhÚ1Ú±î~sÜv­-Ü”îÌ}^çl,¹jæ.-œö­mZ@eaÓV,¸R@8õK Ü¬Šo÷S˜aÎ*ëŸ^µJr	$UEİ™îŒë¡»waYóƒƒÜúúVŒëÉ÷Bu,Xİ}êâ¹ù]·2nr3ëëYÓ\'\\óZ“ ù¶ô¬©—­g¦¶Né¼²İë±ÚäHn&Q#?;‰ÎsííşOß¾\Z°\Zvcn½#ˆ/é_|²\ZïŒtÖòÀD}ù®2+ïu˜ô\0VÕ$§ˆåşSÚ­RÃÂ/­ßèKEWIæˆTç½ygmWCñşµa»\ngy>ğÏüëÕ+Ï¼R‡Hñö›¨c\\Ä!c÷ƒÿ\0=EÌåëò×ô:°ÏŞqîš=‚p(Ó%;S=«©]İLXdgVÅÉY9rêzûT×—EÙ‚˜ù…b^_‹g)¸\0Â¹jÎÇm*wf›Oˆæuo—XÂC²ùÎFNTc¨ïUSS1î\rÊƒ‘ÏQPÍv\\¸~î{Šóe;îuÆ›‹iìgjûË2Œ\0’é\\úÊp$7§¯½v×—‘¬ÓÆO?.¥`]<rË ê¹İŸzóçmÑİJn=ò)s\"tnœ×;yc6%\r´äzäW¡êÖÑ˜§ÌÃ±®zK@ÊÃ\0ú{Vi&¼şwm}5É=}¶Ö|š)mä¯Ô×o=rv€zğk>höîVV±]K‹Ôân4’©‘×Şª(ºWŠéµ+YZhT3€œf¶¼5áu7ÌUÄ~•qJ7¹Rn*í™ğ2!hİ¹?3Œï^³áİ\n5‘)—§Œ\nŸKğëXJˆ‹½T¦»Ââ	7HØG\\’:oóúVMÊNñ<ùÎÉ´gJ‘ÛP›Cp\0äšš?†\Zì$m{J·Ôc–1*|Ê=__Î§¼Òî-wäyŠUÇl+Ó¼;¥Åe§CÈ‘¶ƒŸzß\rJ¥Óµ¾G5yû\Zi§«>ñïÃM3áÿ\0ƒ…<-ÛÜx–ía•Œ…b³uì:`ñóä“˜üAiÿ\0µ…†ƒR[±>ßùgàcÿ\0ç+ÒtØÓÅ>;Õ¼IrTišR›;Vn…×>cıqŸòx½Joˆ>:¸Ô$­#|FO@£§éüı:öcÓå;ÿ\0_ÖÆ¹s‚ƒ©-’»~okÃş7.ÇáP,ƒ¿˜!eÉ€1ßô¯3ñ†š-nœÀà“ÜWÔz“°h•q\Z®ßq^ñOÊŒç§¼Šô}ŠMša+:·GÏ7ƒteq·ã¯zñßÚ,ÂL:p:×¸xîm­•sÆ:×j¨¥Ÿqâ´Ã½Ùß8·IO$TÄu=E[ğÜqVïL8!í¼ÆS÷]Àúã¸ÿ\0õÕİRÕåøà×?q6—yi¨E¸,R\0ø=Tõã¿jö)Ï·SÃ­N÷k¡¦–Ëa+Æ¼8â­ù`ÄGqŞ›w²æAqíI\0`=*[rŒ‘D•™´RqºE_(†>µ\"C»g\"¯‹pùÈÀõ¥K`‡®jâÓÓ©pOqÖiµIÏ9­;uÈéõªğF¹=š¯[&Ö‡½D‘Ñ5¹¥g#“Ú¯†.¼~µVÖ2ì*í¿ÈØÏZó¥fÎ¨TH„äı*»#‰>l•ëí[gRõ¨d€ÊµqZ#&í¡œ‚@äÓ]\Z5 }áW–	Í1ãßÕ:¨[b9µ+ÚC½²y5±i\nœšÎ·WY³h¸ä+Eki±n6¹ÓøNêM*õ.‹Ï¾ßŸùïõ×ƒC/{È\Z7Lão‡ùñ¤3[H\0ÜÊ/=Á¯´¾\Zùz§‡ôx‘–AtŠÅ”çå,xÿ\0õWU(İ6|î!8T8ÏÚwPU?<(²ˆÅïÛ.]ªŠ~cõf#êk·ğ¶ ÷Ú\\QÌÊn#P¬qØ×Æ?µ—Æ¨~Ø:U…¼.¡Ç›„ÈA![qÎ2˜ägÙ¾¶ğ\"ùºE½Ğ!›b†ÇR:×]wË¯_ëîõ\"¢QQŠíÒÏ}zy|ÎÃÓ–<uäS”†RG_á¥Aö«ámH‰Í4N?\ns¹çò¨‰\'4õ¶†jû‹$AÍDx¬;ŠINÒ¤u¤ITnæ«û£O[\n©åƒób˜Ò¸»ëMoİ¸ST`b¥ÛdDšJÈZ`R½4ÿ\0©¡UqÍ-Q1Ot0)>´ƒœNÓêM!9=*Óë`D,Ù§àî%ºĞƒóæ—nr=(òDÅ;ŞCU\0\'ŞÆz)Ç t¡2s‘ëWÖ·Â3ËÈçŠtq|ŞŞ´ğ£oËRÃXÎ…¬†’Z’Áo»\0Ö­”\0±Ç¦\rTµ‹æùI­‹HHFÀãÖµŠv\"é¢¼e9Çµ`^¶Èİ·g«nğî\rÏá\\Æ·\'•NrOåY¥Ô‹\'±Ï\\ÉæÉ!ÏzÏ¸$¶x­Èp¦¨ÎûkĞKTÙZDù˜æ©L@\'š»!ëëT®FsÕ”n·\Z»V(Hœ¿\'Õg\\p¤ç“Z2\rÊËÉ\"³nW!Æµ§Ä…¬–†l§p`zšÍ–0„ç§Ò´¦FÏ>XŸzÁ«\n2IGìl÷Ş\'¸iT¢®ÔÇ~¼×ÚĞœ¥|§û*ÙZ.µ}qn!BBŸ­}IXûÔÑ—5iËĞú<~¼ŠÖ´QrŠj:½8¾cÈ\nã¾\'éÏ?‡Mä*Z{)à¥G\rú“Ğö5Ğ%Ä2C\"‡Ô«)kZrp’’*2”4]™àÁâ\r\'G\r\"(3ÉnNdÂ¼+XĞüEğ¯[’ïN†mKÃîÅÑ¢ËKo“ÊİÏ×®ğ÷Æm\'Z¶>{ıeáƒúƒøœ\ZuW+r†©ş¦òQ—¿kôê‚âAó‚@ïÖ¸=hL÷nÍ1QÎÑÙÿ\0?ç5Ø½å­ği`dVEqz£âL3»GóõäİÏOe¯Rzê¥å€vjQª0ŒnÚ@ê2d\\ÌÑ‚pOEgMtVF,H\0Àş*óıæw{4âï¹³w6ôw³µs÷:€YÚ2y`N=@§&ªÑ+.30kST¸2’’FÄîÖ§{Üˆ.G®Åù&2I;qÍgÜÌ«€£ñÅAÛ«*–Ü@ÁëN”‹ áº*ãm¨İÜÍ¼\\W,¸å@¬Ã—O†$uş•­.3åŒç¡âµ¼\'áñª\\6å>Pàä`UEÚ÷*:Fò3´¯\rÖxÚ00~÷5ê>\Zğì\Zucïc×½YÓt¨wÊ íZ¶¤JÎ‰óëÇJÉ»œíó&ˆôİ$¾Ş¹R0NZì`²EŒ¡PTt+\r¥““Úº[kuó`/ó®ü5¬ókÕIÛ±˜š@¸F0F=+?ÄÒÉ¡è&ÊÁ™µKöû-špä}‚Œ’}«GWñF•áè¶Ï1šcÂZÛ©’i¢¨äÿ\0õê¶‰¥İŞß¾½¬Åå]l1ÛZä0µ\'\'8ûì1»é^Í,<aïµoë§sÍu\\ôèŸõ³O_ÀÆñ—oáßE¡[ªSc°±\',O©\'\'ñ«<2486İ¬ş½@íš&‚MoYg#tjpAçüızøöÚ\"®+Î’öõÜŞÈôªÔ•:^Ê÷oWêGwl«lás^ãË5\nò•îÀvçü+Û5¥K	¶HÅyWÍ²vş\"20+1QpI9ji·#æ_[ù°Ê8=@ö¯Õávß‘ó:÷ÏÁ\ZDÁycÈÔ×‰kP4kŒà…æ¸0Éõ=éÅ¤ïø{ª[n\'1×ÈkŒ\"‹a³Øó^ƒ\0]Ç®Zÿ\0MYÛæŒ+×§&µg•84º\\«àË¡wms¦ÏÌñşöşúÃéş}kYc1·İ?VµÓc†X¦A‰a;5²n ™›Î>Sc%±Á5¼ÿ\0yïDäOÙ·lGşµi\"O<}*Í¶‹-Ü)%“Åy‘±È3R¶yn§íW0û4Gúf²Qå*3‡ÃÌR†0qÅ]‰8éëPK$p¦]ÂñŸœàşF¢ŠşŒçFì6°5w“ÔèŠkW±³ÉU\0U¸]²2séXÖ7QÏ’%Bª2HaZ±K¿O¦á\\³ƒ¹-õ5àaåœh#,=êŠ]C\Zgí…í—ô½€ït•eéÄg&±QhÓTÑv8W¯œ#æcey~	´Ó¯®sĞA6k Ó¾x·Q#ÉĞ&>kÙú’Oş¼Æœ\nU©ÅYÍ\'êŒ¬FíÀUÈ­ŒjIàwÍt×Ş°ğ¬b_øËCğäAIhÅÀyOĞ63øg¨ôç—Œ¿4ÙL\ZD:ßÄ}ErQ[:[‚?¼ÅTcşúüsÏj Ò¿C–x…¤[ô_®ÆÏ…¬îõËæƒJÓçÔ]ÈŒ˜)ø·AëŸş¶}ªÿ\0ã5—ìÑğñµs§ã+˜¾“¡Ú±‘Ë’pH€N3ôÆ{×ÏÚ‡ÆŸŠ\"·6:™¦|6ÒIıl×;OQÓh=¸}@ç\'Â³Òõ5;™\'Õ5™y“R¾s$¤ŸBzzqïë]Pp¥{»ß¶ç\rJR«/{m?¯ó<›â®ªh·º©y#·ˆuK¹µÛ‰,²¹Î=8éÇ^¹ şŠ~ÎŞ\"Ä¾ÑîÁ^Ü+ú8?|#ûLÂÍ¦x~EÍ3ùcáÁür+éÏØ›Äü?m£KC=¨ûÃ–Q€\'®ÏjÖ\r×£ÌÖÌã­wS{ŸTFÊãÒ‘ä¿Uîw+6~j„Ü1Ï5ÉĞÎı	Ú@2?JŒÍœT‰ïAÈç4ìş\"cÄì:\nh9bE,iëSE95JòßİC6²ÿ\0hÆV·õ¥KrªÅ€jq¿-‰åÖÈ¬E\n˜àU‘m»8œ°IéÕVW¸­­™SiRC~ôİ¤Å^	ÇQQ9<â…)8­Šû	Í7iô«\"ÜŠO%¹è+HÇ•ÌŠíì3êiÊ\n“éV–1‚š±lõ÷¨å*Ú²ºG–ÆsW ˆñøÒGÜóÍ_··;†áŠÕ\'r[oBKHN>ğı+OË1ÂNqÎ),­\\têM>ğmRñšÓáÚ£\"å•3¹w\nâõ‰L·3cîg8÷®»P$NGnõÂÜÌ$-úf°Z¶˜Ò²¹E¾ñªÓ&A\"®§>ÕNGÜ8â­íq^Ë™Ùzš¦ün­[,OÒ¨Ì>f‘T“JÈQ|¨§pÛ½gÍ’OLUû€qÏZ¡1Èı8¨·H™Æ÷ÔÌ¸;w{V\\ß–kFáñŸj¦{œgšpI²Ö‘½Nı“aH¤ŸXù)÷†:óüó_OÀF	Í|¹û2´ĞŞ;ÈÃmÄ#hö?JúnÑòpFr+Ï¦”+TK¹ôØÇÏ%/$i¡ààÔ‹ÓYxéÚ¥WÉ¯FgÑ-™¦3‚º‘	\\l¸~Ï\rrZ×€´-UÚYl\"IÏüµv±úã¯~¾¦ºi\'\'¥T‘¸cX¶îuSºÙc¨x-w­ÔĞÈ	;·u×·ù&±®¶l¢eCxGğMßÔW¥ê\0;|ß1^â¹RØHÂB6°nqŞ¼ÙÍÆç­FÖ¿S‚›ÅhJİèŒëŒ–·›\'ò\"²/üeáECöÆÔl\0Ë@_;ŒûWO«ÙŒGÍy®böÊ)ãehÕ”AµWÖ&ÑÃßU7÷™öŞ4ğ#9Ûâß-‡T¸€¯ó`x‡Â2—xÃLÈûÂY‚ÿ\03YòxvÆã™c¡âúV5ïÃêCtú‹îè|Ç?Ëüjı¶_š/åcGJÉ.fßªÿ\0äN‘æğõÄ™µñv‹æ77¨LÔğÃ¦Û 3x›Gqê.”\nâàŸ‚&\\Øù«ÜŸÃ¥jè¿|8I…­—<6]ÿ\0Nj¡W½ï¹™‡ïã¢³^¿ğáywMâİå[Äçõ­›OˆĞlÄMâkïy$¾,Öe¯À¯iìÂßÃ\\\0A‘7äş5¹ü\'¦•xsMW\0d›U?Ò…S»Rr)ÆµT´òı©FÚÀªÁµk‹Ÿkk9NñÚv•ûDh×M Ğ¼/â-bR03hÈ‡ñ­Û{]6ÑJÁ§ÙÀ	ÿ\0–P(®ŸA½dH–#‘»iÈíX<Eşêşvÿ\0/Ô¹á—&îşº~	ºo‹~$ëÑ«i~°Ò-Øq.¥xKø\nŒş•ÑXøÄÚº+øƒÅS èm4ÔTB1İ±“ëù{ç±ÒåÏ#ò­˜Ğ À¯r^h.X¥çoólğªMÁé¿õı~V1ti>;ì­f ¾i¯V<÷?™õ«ú³8³pƒ,Ü\n»UnQÙˆŠÖMÉjÌÔå9óÍİù™Ú-ŠÛ®SÉ>µräî—•%¼Qb98 Z1br}+’j6H¹OšnM™\Zš”±ÔcQ^câxÈ³r>ø,ùü+Óµ)U®âwN•æ#\n†Y$|  ¼,uö>ƒ/MÅÜùÛÇ1E%»ÈÃ£àÁóş}kÇ<Egv#’9Å{ÿ\0‹´øâ{ˆ‚ƒd©ês^3â[@­&\0äŸÊ¸èÍì{%Íıjyuâ\0Xc5<@¡Ïàk¦Ôm\0ÜT÷çŠÄšNs^6¶<Æ´Ô§m\0“¯«ÙÇ*áÀ#Ş‘$µyS||şu­í¡œZ^ë0ŸI‹æòÙ fçrpjş›}â&\\Ùø†íS#m ~`Ô—6åK×Ò¢·,¹İiûICş	ŸÕâŞÆå§ÄE+£¤ê‘×–jséĞVÅŸÄ(§R5?xu‹p|«o½îqøşuÊ*Œù«i†@Î*¥WM’4…Ò»:Y|c¢À	¶øs Ü’9Ş¥?jÇÄ‡ê~øng®ö¨ü6Uc2:b®ÃnIzšŸ¬JÚ¤_±¿Qm¾)ø•¾[/„¾\rµç$Óî\0ıvZ·Äÿ\0Šyhì´¿hÄ\ZŞÚG+øœÿ\0]C9ÛÅh@ÀŒh-ÿ\0$~ïø#Oçoò3f×ş/ß±ÓL“¥C€3Ø‘‘ÿ\0ê¬ëk\Zû³xƒâŠµ¥\'æŠK¿.?ÁVºÄ9ãŠ•á\ZÆUå6ŸäŠú¥î¿¯‘Ëè¿<§³:èİËœù×¤ÌüõûÄ×ome\r´-‘`UŸÊ™o\ZÙôÍJ# 5_´”ãiI°öpŠÑåDg¥?NU3a¾TÎ	ô¢Ip»‰Üj+	Õd$¨#=)+;£:‰$Î#ã½°½¶Ğ­¶«–’FÜİ¶©ÅzÇì]â½ñ6¡mp«ö›[4A |dñøó“ÃøŞÎ¿ø`Ï³$Ì%9à+Ôöı+´ı4y.<Wâ-BÄrğGCù`ş?Ÿ«A¯bãê|İi^£oKa£Lu÷§¤ls…İVí´·Û†¥hC§V¯lW*Oves*;bÜ•4vyÏZÕ6ã•\"DçÖ­™­Q›³d“éO[STşU¢sÅ(©OÈ¦QK^\\ÈíA]¤Œb¬íÈÃ>ô¡FÇVõª»[™§ÌW1íRsLÛƒ&¬šo•…aÖ´Ô¹G±[gŞãéHa^ T”qš£&¯¹AG4Õ‰AÉ<zTÛG\\sé@L3Öî;\"$L=¨\n>”ÿ\0º9Í9W®sEì´–qD¶éŒâ®ÛÅ¸ä¥W†<kFÕ@**à•ˆVr.[Ãµ	êj¥ÛeHÏ5 ØHÍf\\7\\p=¿½U-…%Ôå<Kw²!Ÿ˜óÇjäå;XàVÖ°ş}ÓÉÅdËŞ?¥d¢Ç—¡A¾RGLvªnv“íëZ/_çU¥‡ïsÚ­jõ2v[t3AÈéT¤;\\€zV„‰»¶3š®É¼±ŸJ¦®ŠÙÚæUÇ ŸÇ5B`pI\0‚¤;ã­jMP8ªsÄzVj+[™Ê)ësA÷¸ÇµGålçhAZKiœå¿J«}…”âÕ®$ÎûáÅ®âmŞÜíä‹vÆI¯£ ~W¶Úù+Á7ÒÃö	B’ Dg|r ÿ\0Ÿóßê=ô\\XA 9%æ¼ˆû“Õî}ehóB-tÓó7ã|dÔÁÂ’	ª‘7Ê{T•èÅõ<Æ‹BSƒÏãQ´À—“UD‡œŠvì¹­i%‰]ó•ÅWnwŸZyqQ>îqŠ‘qV3.b,ŒÀıæÍbjaX¸v÷®†d%Y}Š²¯ /sÓÿ\0¯\\µcu¡ÛI¸´q—Öû‡ u¸®vïKBX) zÕÜİZ”|`óŞ²/,Z9º¯¨®ç¡N£Zœ(´ØXÁõ¤6™Pv‚Àõ®¢M9^BÊNx¨Í€\nxğ¨qrGE®Ì-;M@%q¹9 zÖÒ¿ácA†ç?J[XşÎ‡3Áïš¯=áé‰\0®zõÎù®5Û.­éNĞTäsT\'ºÚ¬Ãîã,i²Üynï¤şõy¨>Œp@==ÿ\0JÍ»=Yµ8ìiØß+1s–CÚºÿ\0ÎæÉ)/OÆ¼îÆñYÊ1\0@^õØø~ıc’İÉû®Ç€})+7}‘½X7¬zş2…P µµäŠã<?w½˜àƒÈ>µÓÚ>Tòs×ôxYéd|~&—,™|°ªù™óšY	XÛ¿Ìÿ\0Î»%\'±ËèÙz,|Ôúd=\r<œkhìd÷9ßAhåf?6>î:Šó¿Ü\'•!‘HiÚ=kºñœWWW2Œ\nóÏ&è¶€z“íÅ|ÆaïM´}v	ASV½úÿ\0À<{ÆSÈ˜SûÂª3Šñ]uÚY¥Ï6:×°x¼¼‚âD©eÀöâ¼ƒ[åîÂ’OV®\Z7½Vnêç#y±·/S\\Ş¢¾\\¤gŞº;Œovë\\ş¬–àq^­4îyóiû¬Ï\'\ríV¢¸T@:Ö@¼ÎI#Ö§K¤ÎÈ®‹v9›ÖèÒ•‘—rOjŠ!æ’:c½Uû``@*qVlœ9<àÔ7w©º’ê\\†1Ñ†3Vc´çš‚#Å\\ÉluÍO3fğ®Z†\r¨pjÌ¥vƒïUmäy8Åh@\nd±Íb´ø‘²JÂˆ\09è}ªx’zb›½\\·#a\0r;ÑÊÚ/—[H–8³Âö«Ü  ÓíJ¨!©Â2Ã¨#Ÿ[!·ÑÕnxœX`zÔr·MU7\0¯aZ¥mº1×Wj ÍW´›÷»—\0ç?Z¯;Ï94í=ƒI´ãŠÚ\nÏS†£²w)xîI¯ÂÎÁ<íEåÀU\\Húÿ\0úúW×ÿ\0³7Âñào	Yy‘„wO1Ïvv9-õÉ?ãkÀ~xB×Äßl34¬#ŒyñÆ Çßj· ïùtÏÍ÷E…ŠØÛG\0\0z0ıİ5çÍT—=FÖËó%\n>n8ô§lìqŠ(2¸Â Ï4Õÿ\0ëÓNG½&\nş%eaôsšRI¤Çjl`	¥¤ÅúP•€Œ¸³Q–áñÔT\nŒÿ\0‘Hªx¢	½Çò˜Êƒ”Ìäc5,d°9íQ½1MúÒİi¸Á,M?o½  g4rµ¹…*Œ‘Ş’¤…úRŠ»°í“æö§d™$Õ;dùG¥iÛ©Tç¹Íob;‰0\n®	ïXú¥È†\'õa‚¦´e•C;{×5¯Ş|n8?Î¢NÂês³¸°9Ï5Q×r¸ÏZµ#î%±Šª[ã§¥$ï¡–­´Êr.Iã]ÈS’gÖ¬JIb	àUw9ßéBRZ±4ìõ)I³åÁö5YûU©AIõª®@^M>¢‹{²Âmİ¼YÓ.3úÖ„‡$çŸz¨Hu<Ğ½ä*÷¹_ËZ±uYA5»81&ùë\\Î§&V@ÍDİô±œ`Û¹¯áF(¼)£Ü;e¯ã²¨åN_n+é/_­öƒnàÉòlWÆuËßÛn}Î’9L¿§è:×Ô¿	5hî¬Mº°yú×•R<‰=İÏ°²q’]ÏV†Bñ†•<Mœæ³¬&YXmÅ^LEuÒmœmi`w\0{“@û§‘IO\0ZÖ\Z»‹ayÍ¸¤­€WÜ1bÇƒéTÍ±*ÀvûÃÖµpMTš3‚Àd¹¨jêåE´ŒKÛRQ‚Œ¦{ÖtÖ?è²Ätõ®ŠDó#ú­Pñ9ÏNEpN»Gl\'²9µVŸÆFxïL½€Eü gƒ[²ÚşíeÙ¶E\';dÕ\rF4«gr¸ÁSØã5…ùSGr—3ĞænÌÂ`¸ÏzÄ¿Ù¶·-ŒŒVåÈ4…	ÆZæµ	ÛÍ˜p>è®;ëc¶.ÎÅYn™7–\'Ö³n%[zÔFóp-œŒç5Ÿ,ÒHìÅÙW?tt®wgs²”-{šVó1}ëÃ/={WA¦jƒhFÁBİøÁ®®Ê1Ëd1éVmµ_*\"»r=GOÊ²Üëåº±ï¾ÔVê\rË‰ÀÈ>µèVn\\«uÎ8¯\ZøYp×Hd$8‘ñÜÿ\0…{%¢•Î1ŠöğKSäó$•F‘ª»BàœÔf%$àv¨£ŞKmªÈˆã\r{±÷•’>áê>!òÔWRB*HşMÙªW²€è(oÙÄ!Èåu¹B×ƒœşuå)Ô7NYI;OO_jô\\x%vb\0xçˆïU^|6àsŠùLDıöÏ±ÁÇÜ¹ç¾*rVL|Àãç^Q®Ä\\•Qòö÷®çTÕŞúk”Uo‘¶’GlW!«#1cÛ57­ÙÙk=Î6ûOc`I#;×\'ªG½¢½\nK˜¢Cæm8şz×©[aØpsÈÅz‘”Ç­{œDÈÑÊß5$r6~n•­ubwŸ”ÕYl‰CzÖşÑò”ã¹*ÍÏ«crI=k}ÑÈAàŠÒÓd84ùn†š¾‡KjYÁÇ\"´ìc,NOJËÓƒÏ\"¶íQB¼×3vã.Æ½ºÆ[½YAÏ¡µB:\Z·d95Œ›eèİ“#Hæ9«pÇåsLB\ZLƒSÇ&àÀ)­S÷u.RqZBÙ\'<})Î7sšb«Œt¨d—–ÇJ…»£ı¤O¸Åf»…b\0É«&bªPõõªìU­cÍm\nÒ»sŠÒO!]ñ–r{UÜ†c½]ŸÂ_	¿‰üc§G,[ìÖ@ÌOBG=;ÿ\0õÿ\0=è®gfqb$¡+ŸJ~Ì?\rÛÂş\Z¥ô\nš¦ ŞdØQ2Hüúç­{PWª–‘v¶B«„U\0W«¶Nç¡IÀÁ¤Œ.1i6ãœÓ£_âÍOBS—15—\'\"AEQÆÆ:æ‘WviÌr¦‘AÁ\"™q·Q´„eM<®9À1Ò˜·#_›=©‰»ø¿*•\r7ğ§n£ŒÜ€7–Xw¦[-)]6ãœÒ…#Ö¥ÊäÚÚ1(¢€2p*D\n95vŞ *¬i»5vİvñù\nÛáD©$ì]¶Fï÷jë‘àu¨lã]¥±Í,ïÉã·Z­…¢w*Í/–:Æ¸­NW’å˜\0âº]bàGçÕÈÎARØæ¥+½IzGMÊ¬ÙV8æªî<ô©™†5ciÍRQKBor»¨\rxµQÃ|Ã½X‘UvÆO5\rEƒ·ÂT•q»5JQ½¹ãrY7nõQØ(-Š\"­±ŠM¿\"‹™‡áQÃlõ§¹;ºñôJÛ#oïJ¸évÂú™7ï„bN8Êj~lMoj3ä7?v¹-ZnK1X]­{•-K³¤ROir\03Dc2î<‚IÈ^z×¸ü2=Q£|¤†aNx®;övğõ¶¡à[Xà‘-¯\"Ëôûç±?çÿ\0­ÙéºMçöœ¨È°Ë\"Á÷Óüöç’’§^œÜ{õÜú¥.Y¸´{DnÎAïZ‘±=ëÒî\ZâÆÃæƒjÙ³rëJÎœf‹€æÍ6¹Ïİ\\–%RÕ€”¸ıi)ëó.=(EíÀgÛÀ5Mm¶£dúõ­WSUš0Ä“ÍsN:hmíc\Zh‚+\r½;W9y2Ê:ôã1]-æWÍôÌjF8ÜnÂ¬‡½ë’tís¿¦ç)©NmüÇÇ^ÃÓšç/$Rr\0ô æºm~UG03\0¡‹Æ8şuÇ\\±mãÜãĞzW6¬ìzq|Êæ=Ã/Ìƒ€=+:i¶ÆÁ?:±rŞ\\§#F1YWWX²åĞï§+;]_î5ZÏU[‹……ïpx<\Z§~\ZL°\'Õ\r’¬R#\'§>õœbœ®vÓ£é?‚Ñ‡‰\råÆáĞœ\n÷{{P‘{×‹şÌvÆ\rÜ]È73ËVõ5íÌáH½}	AÍŸšÔoàºÃŠ¨”UkÕQÏçT.µ…PçpÀí^„ëBVy1¥9½·7J™æ±§¿PO\"³u-h×ç•ÎÜjbpàsšñêbù¶=|>MJ>0Õ·)8bÄñ5å\ZÔê|Îùá³]Oˆ¯›ä;Ú¸FL#SÉã´ç+¶}„,qÚ­ªDòº.ÜŒëŒ×%~2®½v\Z»—´Â¸İB6\nr9Ï5|«pº’Ğãu4¸)ÎÓY;7Ÿ¥jêGk•ÏáY»£B|ébO¥p¼ş5×­g­Ê7:_Ú”Öki.wƒ]‘oâ;[ÜE6ÃÏ— ?çüú\ZĞ“C[ˆİ^3ƒÁ r*¥5MûÃqV¹ãzæœ``ã€j¥‚ù2Šôh+ı(]Ë \\®zál-Ë¸\'Jê¥Q4ìg(ÚLê´¤S[Vék#JŒ¨Àæ·íâ,Ü\nÂm³ª)nY¯µ^EVL\n‚(ÇF«pÂ2xİPõÔ¶’WCœÂ§@NïZDeF!†}³Q½À‹ æ´ZèLš“Jv£ŒûÕc\"ÈŒ¤ÓŒb7°¨\0}qøyYÉËÊµüLyfÜI>ÕŸj°à—l}j´ùqT•ãddïÑ9åÏäï_Q~ÌÙe&»sóy¸X€=\0è?Ïø“ó&“§6¥ªYÀ¿›2¦\0ÈÁ<äzŸc÷÷ÃM=Ã6°F›Ğyì{×u(Ú7{&2£“PGi…]£œS×ı®µ»pjPÛ–­YQwCOÌ¬=*\Z´V %T°ûŞ†Ÿ-·\"bˆ¸ç­GXúšr6ÓL.3ÓÖšD;[AiàûÒÔxù¥	]ØHCÆŠBp)¾gµRE$·sP³íGnô»Ë†ÛòŠÜ·ZÑi¹7²÷Hé@Å(]¤ç­\0äTÆ6Õ’!¡{ÒbœàT_Ş»ï¿áWíO&©@ƒ­hÛ©,k[\\‹§Ì]·Q‰ª—n\'œÕÉÈ¿JË½œCOİê(`»ş·p$œ®r©ÓëX“8ÈÉ©î\'ß#³0$ÕœîI99#Š…£Ğ–Ø×aÈïU¤pzsR3€2N?\n¢Y°İÉ÷Å7¢&6[‰¸œÕiæNŞµ/÷ªq»Ò“²Ø’9\' ª²KÃµJÏ’MT’@ØP»O§­%.ˆwŒW¼œå»U;û¯)OLÕ§}ˆÆ°oå!‰-‘ıÚºŠÉ$Eú#\'RŸƒ“ïÅr:¥ÎC8·¨ÜáX‚kÔîÒ7sr>µ‹²V3æ³²4ş|J]QKd1As„lo¯ùÿ\0£ÅüĞÜ,¢R×w$Œrô&¾\0Ğõ+\0ıá÷NkŞ¾|j¹º´‹LÔ7#_’R9ì=GùôÏœ©J”›‡ÂÏ´¢ãUs»gxbñî,Ø¹\0‘øó]´»r3Æ+Ì¾x†=SIYJ°ç•èÖÃjmÉ!x©§+½NzÑä“Fº×¨©±VÒMÊWÓŠµ»‚:W|ô97ÔE]ÀœóA\\RÇÜR·İ5¢ÓA_Q€g¥(RG5%3ıšwÜiP¤à`UycØ­´U“1Ú¡˜€Üâ¥ìTvĞÂ¼BèPõ®[Yòö0e\\î±®²ø…ŞÙÚ8üë•Ô •Ğç‘ÅpÔz³Ó¢Öç¬¹•T““®NùÍ¼®½q]^®…Œ€7’	õ®Jş<£ïW™«z­)_e¡Ï_M¿w<šÉ¸n2zUÛäh«ó“Á¬[†,Å3Ç¥büØ÷+4¤Ëè$`Æ$n¨ãëNh	csÚ­[¦Œ9¨Ö¦ğ³ÔúoöX¸Vøel?å¢¹ŸZô}cXM>İ‰<Õàß³_Š³Zÿ\0CœàHæ{vc÷‡ñó×©ëş\"kGÉ”#Ø9Úz\ZôV)Â…–ç…[íqòrø]™Äülı©ô„ºSO¨Ü¼“?É‚Ìíôãÿ\0¬:Åÿ\0à¢µ©æOéPi0ä…šäïr9ÁôãëÎ1»wã/ƒ.<_â‰ïdYg`‹JF@çùş¾üğV¿\0.µglÆÊ¬6•ÛÍEKó×wòéùİ\\+ œh¥ëmTci?ğPŒÚ-Á’öçMÔ£>MÌwsĞÿ\0=?¬~\0şÓ^*ø¯¦¤ú×„L‰³‰àœ¶óêqÏAşî|OÁß²™ö¨ä¼´F§,glƒøóÉ¯§ô;[	éqZÚDˆbLn­kTÃÊ>älÿ\0®‡!V7E.š->jÇE¨Ü}ª2T2uÊ·_Æ¸]føÀ_8í[Ö>.¶ûZCs…˜à2ËøúW9âÈc.Í-?Jóy­­‡myZØæî.šrÜpyÍr^1Öm´k?:v›;W×±©ëÚE´²Ü8ÂºOZñ­wT}oR–êâV–$\'åUöÓJ<ÏĞÉŞ:ZçŸ|Nø‡â‘º=-VÆ?¿ŸóÏÿ\0¨âš„Úæ½4¯¨_]Ü³C9ÇåşÇèBÂ+œ¡]ËÓB?éí&0î\rz´\'}”yõ(ÎN÷~‡–ø\n-_C¹YİÜ[:œãyÃsßüÿ\03Ÿ²şj7úç† mV4ûP%27\0Íúÿ\0úú×è±µdÛ¿o 1ïÛ5ëö¾,±Ò´ã4ÒÅoh	U!OóşX¹ûEkô©ISåfwí\"°†éÆPÎkÆtB]-“œşdÖÄ?‰’xÒùììÁÂ3ó8Ûúÿ\0õ¸¬ı!Aõ§‡„¡Ì‡4İ×Cµ2`‘À®–Ş yjçô)€Ítº±`ÔI´ît+F<¥…€=©Tcå¥X)ò€ÓUäSæ»‘Ş°S”™WVØ‹Æ˜bÎàK$€;Õ9eÉ®ŠwZIÆâÆ˜ëÈjH¶«°ç5\\9õ;NêèÛS­L@\'oj‹0`ÙäÂ§@5]H\0ó¿qÆ\\WDa}õ;ƒzZê1ˆ`\0ç¨;¸?çúó÷¶j-ì ŒtXÀı+ã¿€šwÙµk[©O™)Ü`;~y¯³•r¡£ù†+º6qHùìEG9»	*OÍ€iaßÆhhÊçĞw¦(ÆîqœÕ­t96Ü”°íãi¤uæšãü)¥ºĞâ¾Èsk ¾¾ÔÀùëÒ€·4…phå°ìpø4ÜĞOiÅ[Óaˆf˜½>n”ğsÒ£=M$D½äBòÌOåQò\ZymÀñëM\0Z^ô;î 9 ĞE\0àS¿ó ‡©§ ŞĞTMMnpJúÓ[HÏšû`Œ¶@éZvÊ¡€\0â³í\0ú\ZÓ¶!`\'ïw«KK‚]Hî$Á>ÜW=®İ4Qm\',yÚµçŸ†\'é\\†¯yçLÙo˜d:T-tÚ™’go\\Šªà1=ÅK,™ÈÏ_z«3íN;ÓQKc6úH¡I*yõªûÏ4÷‘rÄtªí\"¨ëÍ$—BuÖã.%ûËT¤=OaR³ç<óTäWp œ~T$“Ğr™¾`İj\07r?†‘æä“Á4…‚ÆÏœÒµ®\'ª³ Ô.€B3€;Ísš…ÁÚÄ·=8«×÷<¶#Ö¹Ûë¢ªÌ¤~5M»Ššv»2uœ­qšá\0r{kgS¸Ú¤ç9>¾õÈêw€\0à´~$[[um(Vâº¿OåŞÀûö°n½}k€ÏzÛÒ&°N=ñÒ‹{ºí)ò»ßSí_ÙçÄtfİˆvÙéŒ_óÿ\0×?FÛ>PÁÏ_jø»àN°mµX„dF0ÏSÔ\\ÿ\0Ÿ°t›€È2:€s^,o\Z3Ó«¤Ó6­˜¬3WÔ¸ö¬¸eóÂâ´b;°k¾³¹Â••Ë˜ë´‘‘K]&BvæcæÅ<ŒwÈõ¨¶à9¦†„vÆIíÚ«ÎÀ©©¤ùªÓ7Èİê]ÍRĞÊºQ$NŒõÌ_¨ÜçŒp+¬ºev$;æ¹\raö	¸Ûéëë^}Wfzw¥Yvó&Éäkš–&dmÇ\'Ô÷®ÏTds&×\'©m)	’\0È¯>mÅ>ç§$qšË,lÅ@®jŞf¸¸`€¤äã¥tšÀ2¹\\sÉ5OHÓ3#`CSO»:©Í(¾äp[yÅ˜8gû7æ%F	\0óø×I§è­rÎCs]V›à±*eo”‚B¢´TÕ‚#óÇ€´ù¯ª^6·+¯?çõçÔ<Mö£Ê¸Pà|ß•7ÃŞ@Ìª’E¹€ÉB3ô¯C°ğü+”LO8q‘ô®ŠtM\ZĞæ«ŒTæ¤˜õ-\"ºß±qÆrÎZ¨±E\Zùq•ŒƒÁ@8¯¤<CğÓNÕÂ²Â±0$±Qõ®Vøb#V\"Ã“µL}Í9aV‡U,Â•eï3Î”açï(êg]‰œœœóÚ½‡÷v*ñÉ¹Šã;€¬]OÃ\"	.r¬¦5çßÚ¹%NTúLjú6â\'¡¨5=UZÚDf€\0Ï^´šãËoa¶‘Ğ{×*·$?6IëŠ‡-N¶£Q_c–ñ.•>£4ŒÎÌªù\0tïóşO«èòY†‘NAìJö²ß¸eOSÕÉø‡NV…ÈÕ¥Å¶ÕØòG™Ã¹$äpEG6¨c\\Z:‘±sXRÙçwa^¥5Ìµ9¤İ‰Ä0W\rês‚+VÕ¯5T1M+‰æ<pkEmó•<ûĞlÿ\0¢ŒVè§ZVåLÊ²¶òÁà9;EtÚYUÆyôªii…Âô­¶©ã¥LµF\nQGO¥Ê N+©ÓäLgvEpvW	3]N™x0xæ¸jA#¡JëC­I“ƒŒvªrH±¶IÍS’èGËóéQùŒêy5Ïoy\Z§k6M#«”æ˜Ü-WF ğ*deÉ¨®¸Ç[³hîÃB·šŒàÎE8^µµ®sÍ¤õ{‘C©Í2Î2t!€\0òsø\neÄÃiù·cô«šíP™€ò·‚ä®FÎ?kİ³SJ.Ì÷¿hÇIÓmähö–]Ø\'¨5ô¿…uõ	UË \Zò[£§êÓ5\r2T ¡@A÷xçüÿ\0ú«²ø[¨y–·¬Ãr|ÃçüşµÑN*Ìù©7~fw!¹$÷¦ºõÉ©£|F}©­0EáyúÖë›—A(õ¹MŞ´ªwn¤sÎ)µzúf\nLĞkK»û£\n(¨\\n¨©JânÃËïP³)ßCK÷…BNkHÄ¶ˆAÉ&‚wéM-Á4¸TF\\¤u1É¤¦‡Î>´Ö}»ªu`¬Äêx«\'øÕXß“ŸÂ­Àş¼f´Š±’Z\\Ñµ@TóÍ]™„q\0§“Tí!²w\nmİÏÌØˆéŞõM¤‡\rŠ:…È† äóŠã®fœ³’ÆµõÛ¿—nüÑ³Œ×0ò‘Õqìk(Úí¶b¼İqùÕ9&ËZ%¸Ig@:‚ÄÕÔ @s,÷Øÿ\0\Z·;-8½¬Ní´UY¤¾cúV}Çˆ´û`Zk¥\\`·ZÇ»ñænrn|À:ì9¨ç]Iör½ŞÆô€MP–ãibN3Ú¹ï‹:5¹%%’E<Û’Oàk›»øË§şLd¸%à:ÍÔ[¡ZW²=YZBAÉ¨îîDHÀ±ã7¿šĞ’‚Ú8ñÃ19?­rÚ¯ÇİBT>_ÙJ“ù/Ê›œŞÈ¯e+ót=ªşìHÍ·8­rÚ–£\Zy§xa»n=ı+ÂµŒºµÜ{^í6áÈ ãÛŸçëÆkn¦ÜÒj6Œ€\r ÷ÿ\0>Ş¼æ•I_•\Zr%¬™îš¶»l‘»4Êg©Åq\Z¯ˆí7úBºõÊõëÆ5Ip\n}¤8<È?Æ¹ËVVb\"Vw$ê~´”+[@ŒÖG±©*5©¥Ì€FG¥dÛÊ<¾jí›áòÕ¥ìÎ¸»=Qî	µ„µºŠ8ßº²`òOü?ÇóûÃ÷şu¬R› r;q_ÔŞÖö£l:0nyéÿ\0Öÿ\0\'î…ÚÊê\Z\r¼¡²çõ¯\Z‰£Ú‹æ¤š=V¸W¬¥P1Û¥eØËº>:»ùm¢·¦ûœ\\­£N?^ÆŸUao—ÔTèù&»S¹¯¨úˆ;\Zp|c40jĞ-ÕYËdƒÒ®<Õk•ùN:õ¤ÙI¾†dñçws\\v¥f› Lwæ»9¸‰›’sÕÍŞ¯•s!á‘ëÎš¹İFZ³»Bœœxë\\n­ée\ns†úık·Ö£Ànx\"¹c²GÎy¯5ß¡êÂ\\É¶ÎBæ¸»!©ÎP+gGÑƒm!\nàôèh\r&6›ÌUÃãW[ è;¶3€@?wEODW´ŠDºw†–kxcxÊycq=2k¯Ò4Õe*‰±Gõ5nÃMƒrƒë[v~[0ÁÀ*×¥JÇ˜ëè-…šÄ¤à‚>•£n¥8ÛÏİ¨ùªŸ(\"­Â“‚¥wÁ$¬pÊm½E‡RzÕ;‹x%&&MÅ»\n™İŠ›\n%cÚß<Ï4£ä\\àzb†Ò\")²·ˆ,á´„9Û’Dc[\'^qñ{[¿²ˆüÅtøÈÎ•v(¼\"¶â»·¡#·ë^]®ŞJÆmÑ–O”şö¯>«‹:)soÔò_@bvVÂ¨9?Lp+‡3*Ü2!åHÎ;W¡x®Õg†R\nÇ);F_s^f!x¯äÙ†7¯ùşµÊâ¯©îP¬ï®çY\n#[œ&€µÅø°˜¢\nª7$’zŠïôû7’%ãcÒ¸\ZZ8óÊò£ß¥L û“\'\'Ìy±€®N2úõË]7$•Òkd|ŸÆ¹«†VRSŞ½\n*ËS\Z’ådÛ‰ÄP3zuª2JU˜cq©\n™cÚk¯‘KS8Îú\"Õ¤èèqúÕè¦ b²àUxÅMkp²6Pç7l»jlÚ?ojÜÓ¦ÁnHqÏ½kY‘·Í8èÙºÓfthë\"rqíS[J1Ò³íNäÆrjÌBO,+‹‘«¤Ê”¤Õ‹ÑmÛi\rÓŠjÎ«x©n<=kHAÈ‡x¯tcƒ•^F\'pş\Zšy€RÉª –VxƒÁ­á	&rÎıÈFy­X/mí-Õ]^Yf;R»·8QÍeÄ3#e‡ã^óû5i—º^´ºÍ¶…¢åYdUŞŒz>}=”é&îÙÇ‰œ¡q_×Oëî+~Îš¹›IÖôY¼ÁŸ64¸Yry=9ÿ\0ëç;³x\nûû?^òˆÆï”œõæ»Uğ]¦¥«\\j³höšeÌÀe`byÉb1“Íy^³¦cx¬ÜC+DÑHpÃüÿ\0Nzj8ûK­.¿ÂŒåwÎ}\n…-ËéMigZÏÑîÆ¡a¸Ã«˜a¸c§½*m4Uû\r\'4v>Ôê‹:.?¼ÀU9õ{;ub÷1®=Z—2¾ Ya#­È¬Y|g¢[uøê$Õ	>#hq+<²ç¦#oğ¡Î+VTbí¢:ƒõ¨üŞÆ?Å\r?æXm\'™}Bš«\'Ä™¥V0é·˜Ø4ã;ìMäwfÍ0·ÊOQ^{7ÄMLî+m`öfÍc]|GÔrVK»kwì çj#w°’M^ç¬1´ÒyŠÌÁIõé^+yñHT½ÖªÄ“äŒíúâ°£ø§ß±UÔo¥ûŠÅ?JŸyè“»ú÷ÖèH3§ıïÖ¨Ëâ-2w^!>ƒ©¯—ÆP³˜­à¸¸Ïñ…rjXuëŒù:Ì¤ôfŒ¯z|²}	”TzÅ\'4›c†™Éÿ\0d\n_Š:U›ØíŸP¥yCi&&?Ø©»½‰É÷â²¢ğ5[ñ\Z\\Ç\nJÆœÄóø`ì©¶ÒRA]3Øßã}´ ùZ|…{1¬;ÏwR<‹¬X=È\näµo‚>#–Š}]â.0D(0ãÏùü*ı!±€Ëy¬ÜÜàgn@&‡E%ïHÍUQ•’¿ÈŸVø“¨ÎâS,Qv 1#ô®KTø©\"9Î¢±“N0k¨“á]•¼êáŒ»9ªÇáNˆÃæ·ÜGPİMB„×aª«[£‚ŸâD2‘ş›pÿ\0Ä“Èõ¬»Ï-Ğ&(g”u\nŒûæ½šßÁz5¢º|$ç’ñƒS\r*ÊØ0ŠÎİú&kE\ni·wèOµm^ÇÏÿ\0Û7·€Éo¤\\`pXDsøÿ\0ız‚[/^ïk=E=d?+èWŠîãÏ²Š«!òË“hœSæ§ü¤ûy´ôG‚Cá?H¬.­cü\rŒA`Íğ›[ÖnåYÄ–Ñ—x\\vÿ\0?Ñw2s¸{”ØÆ#<´£8NWQJÆN¤’i6|ı}ğT±µ%ot}Ç×õ÷ª	û?é´×WWQ¹ç\nrIï^ı{ ]Û{swÓ¯ÍÎÑÕR­m¥9¨¤äÏ‚²OtØş.\0ıj…×Ã_Z…Û§¡\n1Ôsë+Ó/î9$×#«]msÈ¨öÏ[1mZç\r¨øSF€7—§Â¤)Wük“Ô¬-S8…F8\\\nìµ;å°{ûÕÂê—€±õ¬½¤å¹¤`ì¬mÛÈppkBÙ¶õã5‰k \0dÖ½zÖ-=Ñê]7n§Q¡^4rpqÜ¸?Oÿ\0]}‹ğ^7z\ZÄäoŒ±‡#5ñ%”%Ú—<nNq_S~ÏZªÆòÄXyj^§#¿ä+ÎÅÂË˜ô¨?İ´­4kŸ2\0¥²Àq‘Ú¶Q·\nä4+ÜF¹oşµu’ïcğ¯>‹¾¬Î¤zšÉ÷—wÒ­+ìçÒ³Ğ…`OJ²”>õéSz]·¶…¨É#Ô¾ô1É5oÃSÃqZ)[r¢´“jœœÕ9&-š‘İ¾eş÷z©-Êoa:éS)Y]•}\"@Ó,w¬á™¥\\\r˜H­™%\09¬»˜Ã»éÁ®\'+£²“å{¶©šÏ*¿½Ü=G¥aC§ÎöùTtµĞÄÆáîcµUˆ8¡m¯é\\òNçc’‡ºfXé¼Ø9Àï]†‰¦¤àä¾µ^ËMØ¾y+ ²@‘Œ©T~™éÂìÂsº²/[Û„‰TòN­£…a°g÷¨’O-”9 t)’NNYF@à„ó^¤l¶<õ¯RÔXÉ.À°ªÓÎcè»œsÉÀ¦Ev\\\"üêk.úèÅY+pAéIÊÀ““$Õ¯i¬ÍpÑR¸ë“ô®qu;¯%ŒOæ! òyÓéHÛµ1æÍ¹deÇLmç¥hXÚG–<oeç¶kUGL\"¢¬ÕÌ½Jé®Å¼NPPAÇ\'\'®+’ñ\røö¡;“$0¯A½²?g‰¼¬É¸Çaë\\ßˆt·HÏLë\\ó¿-Îˆ[sç¯\\œüÛ¿Èüÿ\0­yÍ¤Í5Ø \0Àä™®ßâ³Éoª,1gdg‚:EyÅœ	z$<¢²ŠosÑQŠHõüÛtÚÙ=Ô÷¬è¯+ùËÛ?)à\ZÜğÍ©¸¸ ˆÔ¿Ö¶u ÜÙº·!Ó§½BN&I¤ï¼ùsÅvOm1W\'œãô5ÊÈ¸VÜ+Óş éËì‹œãŒzcç²@9®ÊæºdÊÍ˜7# €9¨’àÆ1·‘ZrÀ«Ï¥gM\0ÜJœ\ní]º-;èB÷›£pƒ/éÒ›¦Œ	,­0ÀÉïíV­Tn\'¸ªQ½Â2—SjŞ@ÀókNÊu9Ïõ®l»Bsü>ıE\\ÓoC·\r{Š‡OFÑÕÙÚçam*Iæ´-çÊ¦¹»IÉ;sÆ8­›}y®NSxIìh‰7«ş•28…J\Z«ÀÊ26n©bãªV›[“eyªRIÇ=Ÿ4û…ª‰>ıÙ_Ö¶R|ÚÊ[²Ü<±È# >Ó‚ŞµõïÂ¯/‚¼5kaŸ-ÑE1ı$ÿ\0Ÿå–¼¢Ükş$²°;€‡9?§ùëõşğ«Äb SVÉJ€BF¥w¥î>ç‰‰¨œ¹[5›â®«(\"\rãø@Gé\\^³i«x‚ö[¹±nÍÆĞ@÷¿çëÙEğPm»ñEÓc¨…:µÁÛlO©_\\ç³OÇè*#ºœœñz%ı}ç¦]x“HµX#Öb¶…3–.‘ô#üñéQÜk÷.¥gñ1çûŒò¯@‡á† ûösÎìßÌÖ…¿€ü=ıŞ“lƒ±ŒÖœ±›»fp’Hòªiî@“V¾ºsÕ@w¥4OoÊÅ¦ß\\ƒÜ@ÄÎ½Î\rÊÜ0Ò%€QSùÇÂÅ›¹;2•¶±â1Zj2¢ˆ|36\0Ú<Ü)XƒAñl¤ù:M­ªôıô™?Ê½“r}©I8Îó­iÙj.iGXOoàÜ8id³µôÏŸçWÃMZpDúáÕ£P¯Fc€rj=ãu§uµ]õgKğˆ<$6µ{!=•¶Ö=·Ár²]fà\0C	$-‘Üsşy>§>¶ÌNEBíÏ@EÑİÍ$ıÖq£ávŒJ·¸èÊW¯×Ö®é	ÒôÑòÀº€+¤İ€ü`š„¨ØäÒNIÚæ~Î/[±hPL$¯û t«ñÄˆNÔ	Qù‡9¥RçjâŠ\\­{ÅÈ\"W¨\'ÔŠÔ±¶mŠ1è+:ÔüİkZ<¨›§<hjÚÓ½ˆïîJØ=8í\\oˆ.D²,ióó[×÷F5vİ¸Šâ5	÷1Œg·zÍ\'tU´÷ˆ%•pÊ[š¢î4²ÍŒóU$˜„Õrôfv{´:IzÖ©;íw¥yŠ©ä…Rš_¼3Å5$äâ­* lœúUI¥Pç\"¢y\rÎcT¥—vá»éI«¦f­m­#oÀ÷¤’ä l}j$}¡‹+6úçfí¤Oì–Âµ¤W·»·àW3¨Ş\rÏƒšµ}v\n0İÏzå5;Ù[km#½a%¥Äâ÷*j7¸,	æ¸í_Qz•¥}}…lóÖ¸íjóä|M+-{šFíYZ¦ 0ÜõıkÕ¯TÁÁõ­=J|«Ø®3UºœnÍ$šÕšBN\'ui6ãÁÏ½lÛ\\mBŞ®ZÊë\rnZMÁëVÓGzŠ^ò7-n~rqø\Z÷Ï€ş\"Îıal®ö‘€sĞg¿ùõ¯mfÄ˜Æ9¯Iøg¨µ›YX”òÜ}Nx¹qQ½&waŸ¿nŒû÷O¿YUdŒeH\0ÜWa¦Ü©…v£­y¨™-á•euÒ»-ì4n7cØzz×ZæíhÑÙÀrcV#“jrk\ZÎàrEh,„÷®êsèr8[BÙ›=8©c”2{¯j ²ièÛ…n§ ¹l>ir¸=+\"Dò“hlc$’y5¡4ƒi“Ö²§R¬Nzõ”İÎŠ*Ã”‰Sæ³¯e*ì=æ*ÜglŠ3TuwÃ‚§heëø×?vuÇIhP²·Xç•Çf¥\r¬vğ›—ùì\0Fxªvü¡<3\08­kÙÄ²Û»?İ\0‡õ«…¤¬K—Y† Òolıì;\ZÒM /Ì¤JÀ‹P•­™›%Bã \ræ½Vşdˆ¿/ló[E¤Œ$Û•®nÉq#Ì[<ÍÜU[ËÆ¤w“y8ÏEâ˜yŠÊÄŒá—8ö¬ùüF÷£\n>x?çŠ™ÎÃŒ[[Ú‚Ï±Å1$®”tçÖª[Nv¼-¹“ª±äñØÕm6o>`CpÀçÕ§miæFèxã ¬•NecX(­Ë6›á.Ë»<cÖ­Ç’Ù	İª@ë\r¹D=ºûÕ3¬ÛÙÃ!2\"…ìMK’¬Y½•Ø ,Hb0êæüG¨Ú,2ÂYKc¦\0®3ÆŸ4mİÁ¸FÀÀø Åx¾µñîÂæâI·«1äpN¶+\Z•Û^ê;ğø\Z’^òf´ÄÔï`Êçƒjä-ü*mX™œ’yâ³.~-[êw$C2HÌrN¯Ûøòİ³ç8tUà`}©\'$®×àz\n„’ô=#ÃzVöqüàãæ;?Z¥âoÙiÒÎÎû@”ƒœWx¯ãÄúl‹œ‰Û‚ÎÜŸ¦?óŒù&¹ñ*òñ&vZC¹¤yëO¥\rNnÉ<*Šæ©-Î£ÅºÔZ•ìÒF6)f\0OZãÊä6qÚ¹™üIpùß(#<m\\Zu¾¼Ën<†»aJPF9y›F”¶üàr*±µùH<ÓW\\‡ÌØ>´øuçB3]1r9b¦ˆo”ƒRÇf°†nôùp3VR?5/¯Ù‘ìîŒòW\r¿‘Š£ùü§ŠÕ’Ğä€2*Œ–æ9I\nr+K¯²b“¾†¥…Ëo\nk§Ó¶mlÕÉXó!ÈÁ®ŠÂBéXM³²IjtÊ¡[pÿ\0ëÔÎ{T+81çÒªÍp2ØéXRV¹¥åĞW˜š!#pİU\Zl‘jh—Î]„ÀÛ×9à~5ÓÊz#rzŸAşÊ\ZŸ‰eÔŠf+bP1¸ã¯á‘ùŸÇì=ÊH mÀ¯ı|,tA;ªù’\rÁ”zóş¯Zöàò«Á¯C•GNÇÏÖ|Òl–G	ÆiÁ\rŠ…I\0ÓwÏ4ÔRVF\Z_˜°¯AIQ¸\"˜²=©¥ØÓİì8¹çŞ“Ì!HëQ–Îx¤G\\qÍ÷Bi#&˜Ò…éÍ1°Ù\'¯­BÄzÉ%¹º$yTç+Ç­WY0¸êhy:¨ÅE¼(Ærkd…Òìq|Å1˜:ÔO2äƒÖ£ó\nóš6cO•êNó6®*8¨9?V7wdcÍ×´;¤÷,ù«N†BIÅg	²ÄcV ›“‚?\n6Ø$”csfÑğpW Š¹ypÑÇ·?AT´ö\03H<U{Û¿™™ãC¶ÌQ×â35«åHXİ“ô®Jk‚û?SWuíDÍp@Á÷¬	%É`Üæ¥m¨_^D>I÷\n¨×!•º‚*9î6)\'½R’ç‚KP™›|®×&y”+æ©\\]|Ç=ı*nøàş5NI€Qk‰FêÄÓL	\'_j¢Òƒ•ÅC5×˜ª‹q…9ïM]nRvÔ¹-Âª²çÒ°/¯Uw\0Ù#ïT—Ú‚àqø×7©İ–—•\rùŠ™5±›ÕùµG®Ns\\½ıùmÄ·cT»`ç\\¶£¨7géX½\"˜+ŞËb®©{·+¼ë\\f«¨\\nÏ½]Ö5\0üã=+Ô¯Àß“JkFjİ’(êwàRÜW¬j8İÎkGUÔ€ßŠã5;ÒÄ¶yíJÚšÁ]ŸÿÙ','ÿØÿà\0JFIF\0\0\0\0\0\0ÿÛ\0C\0\n\n\n\r\rÿÛ\0C		\r\rÿÀ\0à€\"\0ÿÄ\0\0\0\0\0\0\0\0\0\0\0	\nÿÄ\0µ\0\0\0}\0!1AQa\"q2‘¡#B±ÁRÑğ$3br‚	\n\Z%&\'()*456789:CDEFGHIJSTUVWXYZcdefghijstuvwxyzƒ„…†‡ˆ‰Š’“”•–—˜™š¢£¤¥¦§¨©ª²³´µ¶·¸¹ºÂÃÄÅÆÇÈÉÊÒÓÔÕÖ×ØÙÚáâãäåæçèéêñòóôõö÷øùúÿÄ\0\0\0\0\0\0\0\0	\nÿÄ\0µ\0\0w\0!1AQaq\"2B‘¡±Á	#3RğbrÑ\n$4á%ñ\Z&\'()*56789:CDEFGHIJSTUVWXYZcdefghijstuvwxyz‚ƒ„…†‡ˆ‰Š’“”•–—˜™š¢£¤¥¦§¨©ª²³´µ¶·¸¹ºÂÃÄÅÆÇÈÉÊÒÓÔÕÖ×ØÙÚâãäåæçèéêòóôõö÷øùúÿÚ\0\0\0?\0üşµ‡#9­+xÈ\ròâ µˆ°°ïZ0ÅŸ”V<Şñ‚½î>Ş>8\n¿`–ö¨à‡ø‡J»77v´‹Œ´ØTŒqƒŒÕ¸ĞxÍW¶OŞ8ym¦µŞí×¯CëTî¤ `t­Œm¬Û¡ûÆ¤ZBNèÂ½¶y‰~Ù¬9í‚†ÇWKy)‰E`]³ÂˆïpÒæ\\œÓ6J—’qI3Ú‡-tì†¢~t2ç§Z±@£œƒ3ììèN>\\u¥wqë¹[#8Ï4Æ*³šs¯ÊBÔQ§î˜°«¸Û}ÁİO3(‹ozˆœn¦dúÒ·/S(¡IäâšìŠZ:søÔ¢Ò$\"´lëóg¥$18‰§L\0‘±Œ{SVAb¹=)pOj‘T’ŠWMŒW®(¹W tlpqM6gÖ¥•jf1T˜ÒÖì)’}ßÇühMû¹éK\ZlÏ­P¯Ì¬FÎZ›Oò¨¦Ÿ»÷¿\nwĞÅ§ÔJ)blïÔ¨›³è(Nêákì6š[\rŒS©“S+ô•-·Gç<ô¨Âÿ\0‘K\0Ç›ü\\tõ¬âšÜ¸n+uûÙ¦Æw´lÏiêŞX+üUZßRW˜‡îŸïT;óÁÛ‰ïMÁÎ;Ô·q¤„¢Š‘¢+\Z¶zö¤X*í§gŠÀÛL\nÌvÒô3Ü’Ù7Æ¬Œmãô¦ÛÄUZxÈ¢ìmˆ³RE•LãZc¨äÔ `	€Z¾†+Ü,!$jàZfHÑ»æı3PÕµ7°ìŒã>˜ëRÅŒ\Z$T„EìÈJÊÅ…Æ8éW!2ß7Ş³Cèh.z“J÷%&tÖú­­¯Ì±ùŒ1Ãp)’ks\\Í–8SØtÎy§•ÍZ³vbAçŞ‹¤8û¨ô\nê6¶eà7<ä `	üOJö]Å¶3ÇK?±D@TL_õÿ\0<×Îú<’ÀÙ v¯OğuêÌBHÀ0Ç‚*¹T¯vs¸F>ólöKMj¾ÍæÍÏIi®‹OY\"%—hö9®sÃ¶ó`’ÿ\0u\0®®Òh¡,»Ã{Šã[Ù¢!g­É„lPÔõ>İêì2¬ùÙÎ*)c%Ï4Ôl¬9\ZØÊšåk6h1îkm¢o›\"©Iî\\Ñt´4ºjÌÅš0ˆØïY³ƒË/Nõ»,_1ÀÍQh+ğ:Ò×séû»åÄyÜ*Ï¸‡\0äWE<k`f².\"ûÜñÚœmĞI}«˜71¢±î!\nIÒÎœ:w¬¹íÔ©4)(êh½åsœ±ÀÀ¬Ëµ<àgŞº+‹m¡‡jÊßİèV¾„Å4ıÓ¸¶ÎMf\\)d8®ŠX	oZÉ¸·*í‘W{nW›9Ù#Ãk>âÀ‘[—üäb©MÚsÓÖ‹¢£-,b²\r¦³åN\\\n×’=ŒGQTæ‹åcÖ›/É™/7T,»»óW¤¨êj³¡Rjv.6K”õ»h0J>•¥¾ğX“Ú ‚…ÛÚ®À¤GÏ U_±¢kQöÈ9>•j!Éâ˜‘€8«Vê£#¨³z±lµ$¶D9ÏŞô¡£aœÀS„EWšäÛTŒĞº·­‡´›c`y>µ“|ë’zô·Ú°f±gÔBNxö­”_SDÒ[¸Õg&²nf]­–Ü}j;»¼³¤ÕEF—>Í%hîB]pÁ†	nØ©&„G=O­IAèO­C;—=öv4·\\ÅZÈdc&¤š|Æ|¢™Îj\'~O­$‰W¸ÊŠI«®yÇJI¤ŞqUñÉ«‹æv)Ë Ú(¢ CHùqDcÓ€ç)Û>Õqo úÛ|¨íØTœóÏ­[•!ÅT*Tx\"“Ñ’Ø~ôcµ>ïj\n)\\w<âšÊ\0Í>“ĞP;QN(G½&Ş=ªî]Æ†P¹Ï‚>¾iâ<ô4°¸ZÎ¹7BQKƒŒö¥U,+RÈ‘CsQUœ}áùÒc<:3p¾Ä\":sS&Ò	\\ryÅ8À¨ ŠÎ\nÃŠKa*¿É%Ç¨ÇæiÊ…³Š•òûÖ–mô¨Õ§[†œ°¤gx\'ŠÂ\nå5r1‘óçv;b›ºî5Z¦´`Ç³<c­l \0ßãS$J àÆ–Š¦¹§•Å\nÈQVŠ\0àdúR.JÃÚ¨°Wc1úS‡İ8j‰¤›\r:5ÆïzÏí™E!ÔRÒ–´5ŒìÕwûæ”}ã¿ö¦œg”Ò0“¸è·äìüjÃïUw?/õ26X†ã@˜cV\0;šËUÛš³fHfÀô©[–·;M>É¢Æ@<e+ª³Òî4ÿ\0.q{ŒpÃË¯·Zó%Ÿ=NHõ®›H×dP¹nŸâ©I™«ì{O‡<WQ¨¿IH\0\0×¤ë_B$†`ÈG5áº>µÂ‚®7z+^Âú$œ3C(l @\'éšO}Lgj}Óõ`Q‘LÇ’;kMHpsÔ×œøVy.P8!˜–İØÈÛãº²’²ºz“\"ù‰$;pGj£,9fÀÈ5§\"­U(r{ÔÙµ©J¥âe\\FƒéYòC»w<VÌñ\rÌéÚ©Ká•MA$\'½Œâ›Ö³§·=nËÌåx¬ùíğ¤õZ¤íğì=µFĞ\0z{ÖT°¨İ•É½k¡×*Ø—=®ÒÄ­EÒv‡=s\ZàÖ]Í¹$‘Şº˜3¸Ÿ½YSG÷‡qUZÈ¨«+ü±\0¤/JÌ¹‰dSÅoÍ+Æ²î¢[Š\Z{0Õ/xæ§~lu5“4AY²yõ®ŠêØüÅk2k_•DJzjÌ9!8¬é¡å…lË	R0*„°}ãßÒ©ØÕk±’ğ(VªO*Àô­g9=ª„©‚G­5}™]`J/Z¿\n–Œ¯\\õ¨`‹<7\\Uø!œ\Z«hiô%\n¼SÕöç§4óo°»íU.ãÆ\\¹ãÖš±ËBÃj«d³)¹í[_ó¶tê«}ÊÊ+\n[†eãƒ[$¢®I2[‹ö•Îy÷¨¦»\n©¨¶¶îµ–Ò»T¥ozâˆ‡HïWí\"zŠKM8Ÿ½ÔÕÙU`„¯\n)ró\Z¥u£3dp#å×œ*©´\ZFÜÄŠbŒ\Z•¡p g\"¡vÂ¤Îw\nÈÚÛ¾î*£e¹QV*<†FùÔœÙÎîÔï/=)ğÄ¥5+R/r Œzh=AÇµO\'î+Î}i±)vääu4íĞ·Ãg”s÷©«Ş§kaÙˆúÔ^S)+ŒŸj!¤„Ó\ZN@õ¡Wp5 ¶cS%¨ç©®åL}©vœãÖ”z{¿ü³•Z\Z\\˜éš.‡ÈÌ=‡ŸjJècÑ% ŒcéGöÇ $zô§uk„`Ù€±3\nÙŸ«v-\rğp¤gÚ¬\rÿ\0Z’hµJV»G2¶ÌyúÓã³b¼‚=«¨ÃüÃñjBŸ—5Ÿ´ÑƒKSKu=±N[\r¢»ô„Éùy>µ/ö,X4¹ÍcI5¹Ä2@mq“ÔWtt@ê~QY×:;ÂŠ®~Æ|[1œõ¦0,\nãp5»6ÑP2j²é„·Ì¦®-=ˆ³[£)bUéJ÷5¦l‡İMû	UÆ?\Z9˜-´2ñÍ3ZÀzM6Gy¦ìúå\ZtcœÕ¡fyÉéMkgNÙúU· 7¡[4”ó¦•\"šhi¢<ädsô§Ò&–¢	«Üe?÷İ~^Ÿızš)«‘Æ;Sc\r.yiVVÈjâWE6H–AÏçUü¹½[şú¢árRêF#éB:ãwÚ¢ ôæ¹ìcÎÉZ1´àsH“´:Ô¡BôªIê1Z¨[©£ŒG…ôoÊ	^†¡©îóM h±o.Ö9<VµÌqäıìzVg ó“šĞ³…‡<ŠVèg}·NÕÑm8>İ«¨±Ôlæoô©¼¶#åİÀ8¬ßhZ]üí\ríòÙesç:ä/ùÿ\0>Ş…¢iZNŸ*Å(Kø	ÚdA€ã×ô¨o[XÎêíu/øGÆö\ZTèx‚Aò¼N8#ë\rzî…®ÛêjY€r§?çµqZ/…ü4¦k[P’+Dô®ëÃúÿ\0=¼IôE\0\ZMÅ=™šŒWWsamØõái­‹qÏãZ\"ËÂç|§ùÖ•ü‰…–¦,ñ—¢©ËÌA­im±‘ÔÕ9-ó»Œ‘Z¤’»\Zk•™3[‚	Î\rfÜFFñÔÖÜ¶Ã-“Ö¨Íi¹‰SŠˆ®rbï©ÏÌœ°ïšÎ¹ƒïzšè\'µù›k:âÔòzâ©i£/S•º•›½fË2Çµu6ÙÜ1Ó¡¬¹­rÅKz†¬æn!ŞF+\"êÛ*}ı+¨¸¶ÚXvìk2Kr7qÇ¥$›z²œ®¬r·Ù¬‹ˆöî\\ş5Ô][ä²ç§zÊ»²HÏãDnb¢r÷1)É\'í]\rÕ±\nËYÛc5QÑjÍã-nbJ¸*¤É•oQZóÛıãØ~•Ÿ4\\5S./¡ìDF}êÜJG\0Óc#½.ıƒÚµµ´F·kH–å_—““Y÷¨‚&,ø4Û­Cb·ÍÏò®vúşFÜwqèj¢•õ½ô)_Ç‡l\rdÈX$ÃÔT—W.ÍÉíKn\ZD%‡¬­l¶dÛ¼‡-úÕû;EÇAD1¬{ŠTŸÊVÏJˆùäY…\0Äà-PÔnHB;µ]+¶\0¤íş,Ö%ãîœç‘MunC¼óAsH÷¡FCTÙdFÌB±üª»Jî<²9«Dpy¦¤J‡*0i´*!e\'½*HccsV<°«#¤(…\0#êi%x‹•£dd¨#ŞŸ\0Üû½*_-}*DBùö£mB)Äg­K£ÌxŠİĞ¼/-éÜPíí]ÎƒğúI†9ÉÆqXN¤b®Î¨Rrv<öÏÃòÏ‚	ö®“JğCIÆŞOJõá¼°HÃŸ ®«ş¶AˆÁÇµyõ1KìkÒº<^/´ «!üM„È81şuìø|ÊÍ˜Á#ÔS×Â¿6L`}+Vmhl°Î×<¦ÏÂ8à\'Íì*Òø1˜“êĞø}bçbŸÂ¥\Z!ÁÚ½}ª%ˆ’ÔVêÑä‡Á¤.Bğ=ª³xa‹òùõ\"½„è¡\"?)æ«É£(]Û?ñÚ˜bn½áÆšêy<¾•Q€ˆœÿ\0tU4PTŠö6Ó\"ò°@ç¾+&ëFŒ–\nÇlVŠ¹3£}Qå¢Ë<Triï¹‚•èòè\\1ÛÅg¾ˆŠÌ@Ç¿jÖ¯¡“¥Ö\'Ö²¹¤<ší&ÑPƒ•ú\nªt]§wjİTM ïcŒ—IŞËŒUfÒ@Ú\rwIËcô¨çÑB/\0ş£Q-„é¥º<úm+cŠˆXç<]œÚZe¸ªí¥íÏËÖµF–¦JÑÉgåıj#b\n·ÉÏ­uÍ¢’O¥@ÚVÜñøQíEì¬qÒYe›j/°\0y5ÕI¥’N\\é…[G×mh¤×S›ÙÉ3›:y ô\"ª¶šU®¹´ÖP£ÚnÕá\n~ÒÛ‚ƒ[œ‹iß{ªIjS>ÕÖ=‰äTäÓ±œŒ·¡ªAò>‡0Ğà85\r¯ú×E.˜ÅHÀ&³d°t\'¾+jsF6º*Òn7û=iZ2¡†ĞÒŠÔĞ…fÚÁ>”3ïŒÚšÑêÙü)¨»¤×­EÚz˜kğ’G÷ÅczÑÿ\0,ÿ\0\Z<¶ô­E­¬‚&ë–«\nøôªÑ}ãô«IéXC©¤u£Õ·f§·£õâ«D:çš’›Ñ‰›ºn¯-«‚ü§èº‹#‘U^lg¢šò‹QÃ`Õ«S\"¸ØÄ{æ“dò©+ŸPxoW±EÖéDœe9¯Pğî½J°3Ì—ó¯’|={xË†rÊ1À5ì~Õd#iK¨ tÉ<ŠWW9”m&äî}\n©O¼ÅC,\0çhçùÕQ=¬Ee-8=«aíÊ±ËnVî&´ÔÆeÚqU^Üœ+j[~¬*›Ä~o—\rZhÇğèÌ)¡İ“Œş5R[|äÍn´±cŠ¡4*w1â†”tE;%e¹ÏÍm´OJÎš\"Á°}ğ\Zè¥µ$7§­gMo÷¿˜¨RV´±Í\\Â~nx¬Éb%[Òº;¨F¬Ùí·©ù\nOFÌcutÎbâ. ¬™­ˆuÙpvŸÎ³%¶e<U-bî¬ÎZâ\0s¸t¬«¨qŸJèî !ÛµeİÛäŒQt…™ËÏjNá{V5Ä;wœuõõæº«‹r\nÈº·Æã­)÷9™â8ozÎwÎ·®mÈÉê+2âAöª]ÙIèz€gu$š„Šæ%×î«2mPØbk¦VÔÕjjjÁÙ„f²÷0#ğªfè<¹ÜqD·lÀ¨o–Ÿ*İÂ 2¿-Ç¥\\1QYFBG\'zÂA–g9ÙÍ-îÇmÍ9’;KBI%Û ö¬eœ´ØÎ0i/õ&ºöQÀªbNã¥A¤Ñ°n¿vë¼aEdÉ.âŞô»°†¡f\0OZ:\r“-·½<6ĞF9¨V_zœğ˜¤\nıH³»xô \"†,\'½:Š¢’\0£–¤*	«vÖ;ÎİI;‚w+ÛÚ™‰ë]g†ü,÷2d,AŠÓğ‡ƒŸRs	‘—©¯¡~|-{—Iß÷+Áf’?»^}|Li­Nê§%à/‡]d¸\nF3^Ç¡ü5–ÚL«ÙTcó¯^ğwÃ$µµF1mfäoô®ÚF‡sÆ%#@À¯UgYÛdzŠ¦­Ôğ˜¼&±.ß!ƒwùO4©á-ù-^0E{Áğ½¶Ó¾ Hé“Ò ŸÂŠw>ÅÀê=kšÎ,é„£Êõ<N\n,jO•»F(_ÄÊÁ£g¸¯X}BïˆÂ€u¬»gS•#Ôu¡;3hİ&®y¤ŞŠ5ÆÌàöªO ©bØ#Ú½2ãGŒ©ù«ÿ\0Eš)[cy‹ÔzjÊRInÖ±Ã\\hKón••>˜€8Úp+Ò“HÜ»«*ëMT.\nk8¸·Ê„”O7›IAéT$ÓZ2wâ»k‹O)Ø•À¬‹¸‹)µÕ±J)¦q·Vg.VsÙ|¤q]³éªë’sP\\ék°ár;ñ[B¢æ2Š±ÁËséNÁIÉäVåÖœ…ˆÇ\"˜–Í°‚3[s7±QÏÜéè„•ª3Ø1FÈ\rïšé.,Ûqâ kP“ÖˆÚ÷Lˆ§ªg&Ø`şuØºü¹ÅuRÛ\"«ddÕmó£Õ¿?CtÀx@0j´ \0®•¬DÀ†©ËgµˆÆMÔRVf\0Ó<ÂHTGJÉ9\0šê-¬ó’E)ÒyÎÜıN+N}m9Õ”ÚoÊ~^=@ª²iã•®ÜiÆÅ»VuÖšª§&—;¸¢»îqiÁsøU9,”dÍu“[HÁ¬ãm’xÍi©Z(ç$³SÉãéT§°W\"º{›Qƒ•ª¯f¸È&µOª0•;¶ìp÷Ú`Ur=«{vPÃšô;›d<~5¨é€nãõÑ	½™ÏìšMœ‹®ëBô«—Ù¸çMzWD™Ì×Q´U6öÛÂ–BıŸ˜Ï4{Ò,˜5E=6¯^µ®	Rm’Ç2ò*EmÕ]Y9éùT¨všÍj®hµ4m8$~5zÎ%ş&bGzÆY\nı+WJ¾Š	3(wZ“ºG[¡Éä¾æİÇp3^Ñà©m¼Ø|·\"H“€¯ë^e­Åæ* ÀÏzôï‡ú¦wxN¤òÆ#S´*î<tïôÿ\0\Z•İËU}«¼5oÁ”–)¶ã˜ú:óŞ·Zó¿x·Ãğ[[Ã§I1‘\0û±à°öé]î¬=ê?ú4‘…ÆYÆ¬\'®Ç<æœ­ĞˆÛ69^*´–Çqà}\rl™•ƒc^IeH÷¬í ı§»tŒ­ğOuúUI,:ázÖôì2xæ¨Í£©ª‚é Œ¾Ó0&´*íYòYœ¶às[³sÇ\"¨ËÂ6ZÑE5Ê.v¯cóNcYRØíÎ3]²(Åf\\(\0úc¥O³K[ŠOŞ{ìöjwÖ±nìö“ÇNÕÒ\\¶sŠÈœnvb8.6)ËÌç®¬B±•bİ[&â{×MxU÷Ö±\'‹—®Ñ²eß©Ï][ •dÜ@›[Ï¥t7`1=«.â3ëS£CŠVæ9›»`?ÃéY3Û¨İ]äcœ}ÚÆœHïD_6‚ƒW±„ä†$*2riìrÅj6lwÏJíµ™Ú´WrÔªÁA5VŸæ61š,G?rgí5\"¹HÈ\rUàüÕ\"J$ÈÃS¦Å¦Â‚G¥8!¨DÈ£â¥\r‘€r)ù;N†£1©mØçÖœ÷¢…9WršmM’¤zSßA7bˆqÅZ†Ñ›Ú¤µ·%òW•½i¦8&³z!Å_C&ÏJ27·¥wğ)ºpÍv<\0sSøkÃBòt‰8àWÑŸ\r¾=ëÁVàgvu{Ÿzà¯]S:éÒRÛ¡7Â¿…‰,ğ+À\\	\0G¹ô¯§|#àˆ¬#Cc*Î0£Õ£ğçáä:T¡?r£îËR}+×4m4;‘`QÂíq^;^ÒM³ºU9–Æ‰áV`\'eÇÊ«Y¼0Â&‘•b#½ñë]v™b5Âğp§ü!„Ëm+2áAëµÖ¨#Q¶pç@ŠVya\\íYÛ}G­RÔt…Š\"RMÄuƒùW¡.1f2¿?^}ı+œÔ-¿’Ù‹$–8Œ}k	S²7…U7dÏ7»EHÉÚÏ§ZÀ½µe“;sF1]Ö¹¢nŒ%½Ğ_-²»×ùş•Éß	\n¼»(G×/qèwÒMë“¼¹~_LÔF\"„VµÕ ™»¸ U4$$‘²éÆOqY=v:Ş–ÆÚ:–QÁ—:pêG5ÑÏh_sÉâ²®,É-–éÒ¢\nÌÅ#—¸¿˜?W;}l‘–Ú=ë´¾µ\06F~‚±¯­âF+H»j7fÓ‰Í…XâaŒPÂ«&õş*Ò¹³!}ê´vâ2ÎİGjŞ)K©2î¶2nô¤bXŒşõ],bTq·æõ­«‘”80¬Ép™\0óÚµ…ììÌÒ‹ÖæLÖ`³|¦³çÓğy?†+påÑñÛÒªJÅ˜ŠM´ïs;4îÌ¯ì¡‚ãéPÉ¤*î+“[…ŒãÒ“ìü8úUÆM­K”Væzb¸ ”—\Z$ewt>µ¶lœçõ¨\'†UR»wUóëk©ßDÌH¬%#ï\n±²`äqëVLÎáƒCDÈ‡&Öñdî¯bŒÖË†\n0+\ZîØnnr\rmNËny¬9æ y«‹g?ºÌ;˜_Yo\0Üzÿ\0mNáê„‘–bzŠé§µˆmj¬fKm•-Öª}Œ\0ÄzÖË‚ ‚*.¹­7G>·¹Šö`ô¬KN§åæ»¤‚ªKl³+qŠÖ.Ú‡#±æ\Z—€Ø\"°$…£,3È¯OÔôàw|¼W«é[A \Zê§4q8[c—uş”ÍÂ­<aXŸZ‹Ê¦¶r]QÍÈí¡¦¤˜ëRR*ùmª!\nic“¦ ¥ªÚ¸-	’L/ŞúÔÑO·j˜lJ•\"¥$ö5‹¾æµ­øŒç¡ö®«Ã¾#´K€—1´‰×õë„Œ€yéV­.DgÚ“]I”n}Sà?‰šV—$LÖw—Â/^qøšú#@ñêÑf5(‡FON+à¯ø±l&eÛ·pùØãõ‡ÃÏi—¶È&¼-v0qG’{gØtúdTÊz¤yó¦¢ÏanÎ;ÔR 8¦éZ„w¶ÛaÆà@¬”lµ5VQ\\¦t¨9ö¬ùvî8ük]¢8 ŸÒ¨ÜGû¶ï•;;™YÛS2dà85›w°|Š×”1nòªSÁ¸6*£h²Ş«İ1$‡“íÖ³f@©­—I!:õ¬ùâÜIÇ©ö«.^¦ÖÃ3YsÁA<WE<3—q!]µÒø™¤b¥¯c˜¸µùÛŸzÈ»Œsê+¨¸@ã¥d\\Û–?J=ÛŠ	+œ½Í°;¸ëÍdİÃòÃ¥t÷1m$;ŠÇ¸Œ6ìŒÑtÖÃİXå®¡ÊÀâ±®-Àk¨š=ÄƒÓéY7Pì(Ñ!ÂÈáKgp4Ú(®¥¡Ü•ˆZR}…qö©JƒÔSFƒæâ™Ÿ,»•‘V-Ü*°<w¨CVm äçêiEû¬˜¶DˆÏÛ&¦DØïíOŞ‹¸)ühO½APVÔJ=iC0§(Ç•Ë¸ˆZµeçé)-­ÍÃ+¨Ñ´ØĞ…+‘Ğ“FIÜ‚ÎÉcSò“ôÑèº4·Ó¨	•\'qSZX£Kµ½ƒáwşÕp’HŒò?	\\‘êq\\µ&£4¢ÛV4~x¦¸ò–$¤„ø×Ù¿\n~- ™ã*@ùˆ^€vğoáe½¬\"Ib2c9-À\\õú×ĞöÖÜE\Z,j¬ãŠñu¤îIµÉÔ£¤iqGl’¥¹g\'\n§¿<VÔVÅK«à’\0Ê¾Øÿ\0=jk{U$7šŠª1û¦Üjå¼xRÑFAzãÖ»#I@ænÛ“%´qçËË€ÌÜRÄ`$‚J”9ÇaïPÆ×B€©ëÔšt°>Š ŸâïVüÉ|ŒmİŒ‰]š<²¯¯µ“s`.šDg÷•~ï±­‹9¥kIµœ`•àc5^!a±™\0$1dW<İúâ£tš9COŠ©ü»@VÏ<â¹ÛAt÷~fÇ\\ñ…íúW£ßé¦â\r€ØX†O=k—Õ4 ÊÂ7Û)\\<e­y•´MXôéOG©çZ¤I û6éQ‡B9Ïµc^Û:+FV\'Åv7\Z{¦àëµ”ãñ¬«Ør¼Œû\Zà”µÑYÑº²zÛñ9eÂí8nõJæÌ©\'8Èé[Ó\"¨8ÛÖ³®1å•b±Rmİ‹•·©Ê_F#-¸šÏ–Ğ¼eÀÍkj‘…nAÇ\\Õ#:„*\rm¾ˆQ,L«uÚäŒûVSDó\"·.¤Uêk&yËe¸¥M´ô1nV´LÙñ·|Õs\0|÷5§3(ûÕQÊ°8\'\"»,ä‡%Í¾æI‰¢fĞÓ#¶.Ü\n´í–`i\"p™ç¯qO­É´®5mvŒÉ§›2ämõl•Ù~aŞ¡A$T6şÉ¢ÓKnP{7@@äĞÖ[Ğœp*óÊŒÓf˜2ñPÜ’%+]7Qc .1Yw.cÈÛŞºS\nÍ»\\Öeõ²sÇJŞ3wI‰Á5vr÷ò—B\"±$ääŒâº[«PAãéX×!z½[ÆWz³‚¹…<Yvã½Cåmã<zV¬ªõNæØqŞ»`ÓVfƒwÔ¢cURO>õTÅœ‘Ò¯²¨[¥UòÈèyúP®£sÈ®Ô\n¡5t\"ì ÔoØkH»°qfD‘	‘”ãëŠÂ½Ór$~®½baŒç­R»´§¸µ¢’NæºG¬éÆÖfà€kÉ•Ò½CZÓÒæ&¿7jóíCO0HèF9à×\\\'}IE«™»³’iÏ5+Å´v¨ÀÍmÉìsÙ­Æ¬˜ÍÛ”ÓÈ¦7İ4Ö€[u9_4\n*S¶Â,FìCz{RÀ\09Î})-¡3»šŞĞ<-6³9íÚÆL’œ~U¥Êº·¼Q´™°pá^±ğ‰5i¯ã¹µ3B±ò×\0q@Oçø~xÚO„´Å\06é¥\\`ïùH÷ızõï	ùVRÉDå©Âş_€¤ª$ôF2’––=çáæ¥%í¸Søãé]Ø1Šäü\r}nšl0Âª#QŸ”uÏ­vŠ7\'<ÖmÙ´sÁ»µÔÏxò[&©K–3É­w„’ØZ§*\rŒIãÚ¦7¹^¦TĞõÇzÏt8=k\\¨Nœ“UçL©\0f³Ôµ%i©…2[åàÕ	â)çÖ¶§RªÀÕEÍT¶)ÊòÔç§‹Ë\'+šËº„n8®–î,À{VUÄ1êjÓI\rİİ&s7@|r=k*á	@Ít7Py{ù¬‹˜°¬qF–±)ré}jñ>B‡wÁ\0q]-äc1È¬k˜ÔØÑ­¡\\Ìæç@k.åN{WCw*{šÆš-û±Ú¡É-ÊƒW³g›?\n‘• ù‰ÇjMxë])4v§b:‡Êfs¼å{SR…&¨±±Ææ©¦;\Zh!QAmÛ¿Ù©K±>¤f\0½[4áÔÒõÏäCV£I!\"@	\"¬[Û<í…äÓâ´fêqZÖˆ#éS¸¬[Ò´Õ¶.\'µlAóLzUK\0ebº=NO3[>‚¥y•ÜÑğµ“=ÒÑUIbkíOÙËáµİÌ1ê\ZŒFÕ|±\\ÃÛ<¾5ğ{ÀĞ\\êy·g”œ.½ëş}ıkôáo„ ÒôËhc…Tp«ÎöîI5äÖŸ<¹m¡éÂ*Rhì<á„µ·ä+µpR5^¡®–M8\\‰UÀÙXsW¬-$EİócJ¸¶ÁUŠgw­uP¢¡‚U“g;˜-Œp,H:²ğ>¦¡¸H‘$”«@FÛšè4!Ã‚ÄŒzV\\ºr lD?Qô§%Ê´5ŒÔîæÌëãˆrìeƒqÏµ-ì&Í•‘É¹RwŠ±/”¡F\'³÷EVw‘~ğ09äûW5¬µ5ŒİÉA3#!fp‰ß«zRY»ìš)_xÀ*UÅe	g…Ël(\0¹=½Å^FcòîŞ@$/Mß•eÌíw¹~Í¤ìfêEÀQ\rÀù\'±íÚ±µ.cy¨ŒaÏ×C=¤^p™U£#¯|Õ7¹{¨ˆ2Ù9:‘\\uõ‘ÓNÉoêp:Õ¹–<\0G^sÖ¹ËËf“vŞë6‰ä)_‘•¶²“kÛŒ#¯¢wÔõi;ÇS‡¹²QÔ}ë6çO!IÚŞØ®ò1šÍ¸´•ëëXs>¨ÙËc…¼°«øt®wR´ÙENr=1şMwÚ²;@Ü+—¾€8bç¥\\dù¬‚É;¿¸ä&+ÏËƒéY÷b>J¯Í[:…¾æe w¬‹µ!IÏJê…¶3šIû¦%Å “wATŞß\0‚kFY	Œ¨!Û‘Åo´ìÈµ›»3äƒ¨İ“MÙ²ppOz±€ïééS#ä‘T´.ñ’µˆmá‘Cd‚*a2ù.¤ã­=ù$–¬Ë¶u$.k5¨MYÙ\r36øTŠÌê@æ¨BÌf;†N?*×·‰Èg¶•¬(­5di@p½i“@$kj+eó|”Ù-•ã\'Æ¹¹lô2İuõ¨Ëœ}kêÀ0}+­Ô¬Œ¥p=k6xT£v5×ãª1¨µ±ÄÜXÈ¬ÄsT¤…ğrã]%ì~[0êMeİŒcŠêŒİ¬·9\'î³@Tsß½@ÊI\\ûÖ„€m<dT<cÚ·„ZÜMs»² Á\\cš|aNxüé22@ÈíI(§+ƒZ¦ö\"JÚ\nÑ®\0 ’ÙÈæ§,@cŠc­ÚˆÉ9XÎ1\\Æ£b£\'×â=/~\\{×¢Î`n9®wW²ŞŒ1[¦âÌgï±åRÀcr*!Æk[TƒdÒ.	!«7f+®-5Ìq^Û‘S—¥!¥^”à¬Ú(­´ú\Z’€Çğ¡nsÖ˜‡kş•	˜¥ÊÓeÈøÉ­[à„dí±ÑÉ8<Ôèİ±[µaüZ£ªÓüD-IÇœœóüë¯ğÎ¯q«L±³ÆîN…E\'#’z\nò¨¥)õ­­TÖ|¡äà0# Jò2’²vÜû¯á,¶¶60[}¸jsDbŸöI<ã§Î½“ÉÚ¤çœ_%üñœ°2¨K(m£<zş?ıjúÊÒs<:àà|£½a8»İÑÖìƒË^ËU^\"	îkL¦½ê³Æ	5ŞĞr¶3¥ˆ\0NÀZ¨ºpsÆ+ZA·qÛøU£gfÂĞ”L®¯¡—=§™¸©ÏµfËlQá[s#.zóYWQ±-ƒšI4k%Íï[S\"xÕ”‚?JÉ¹·-ÏLVÔ±í$zqTn0£š\"¾òb“Üç®`lısX·0dõÒ]È{\ZÅ¹Å7²+•;œíä £µ‡<@Üæº+¸ÈÖMÒ‘{Ô4ì’1iI«œİÅ°ÃsÍcÏMİÀ®Šå0÷«\Zâ\"¤ñJ1]77„bö<yı~•,cÌÜÀ¤E=½êÄ.%ù>¸®ø»©Æú†4RKÔö“€¸_QK{ËùV¤ò£Ãn4+35y„BFp)¦ÙUzµGñ«ñé\nñïgUJ´i¦4–s€8«pZ”<Ç¦†\"›»Tgw|îÖk±kMÈáƒÌÎìŒzUûdê[­1`ÛĞb·tm:ç;Û¨ÇjNÉ™>•£¼¸ ì¦½3Á>î— ¹\0\\ŸóÅsz<\r<¡`åÁä(â½«á‰vn¢İ;Ân?ÿ\0ç¯-IhÑµ>]QôÀO X®å³1&õŒM/Ê:àÉ¯¯ôK?³Â¢%\"<lŒ\Zñ…¾ÖŞÚ69È»Y€êHí^û¡Û3(‘ÇA…Ò¼êq¼¯ÔŞ¤Ü’lÛ³‹Ê\\§äÂ„\\d÷§‘^¼6<Ò´Ñî\'œfª¼PJÔv5jæE”ş5Ê£NlÕ=\rc±›5°!”d®>î:{ÔÙèT3*î^„szÓ’}Àóò*»\0íÃé\\î)›S”’ÜÉ¹²	–Û½3óTFA.˜?SŒVÁ…a‰\0µ–È’+¢¹%\rntS©mÌµ˜•\'®Nê*œö¢Y°ª2O\\Ö«$aÈ)èÅ8¨İ)ŠE;ÔgAÿ\0ë×$Ô™½;^èå5;vŠşDÀ‘B†Ü?\ZÈš\\¼Ø®á¢ÅÉ&<›‹zšÃºŠ7Üca\"q†¯:¥7k±©w¡ÊßZ(†ÆîõƒqoË98ö5Ùê\Zpu.HãEs3âU8û×#ƒİ³º›çZZà“\\¾¥jäVMÊ}«¹*«ıkXµŒÀå{ñ’hÓdTtzw©Á¶CµFJç.-7“¿\0õÜİÚå‰+•ì\rs·öè¨àÇ­]9\nQŠêr·6Šv15wjñ3Ojéf`ŒT+/QÜç½n®ŒíÈ´0\n•ÎG4Ç-Î1Ÿj»,[‰44bEÚFjÓrZ	.åd˜dıêAl×Ä«VÖYl•­HmV0½ªbù^£Ûİ_y‘@S}kVÚ…ËÒ´-­Ç;À51³E=)I¶½F¢–†w—ç+ávã§i‰	ä0ùEhL±íZåP„cœb¡JIlU½İNú–WÀ¥eÜiìœ€+ ¼	’ZÈ¾tu$ŸZŞ\ZW]Nk6íÜå¯ Ë6F@¬;ÈJk¥ºp2	æ²n R‡Zê§+hDà–†ÇåıîOÒª˜r[+Áï[G‚sÎ{Õsjv“•Ó=nq8ë¡“ä•R?½Å4 L÷­O#qP·„õ®…¢¸8§	FÁâ«¢lÍ[xr:ò(1‚¹ÅRqŠ¹–Û”ep™\n3ïY÷nG$sZ2GÄtô¨ÛæŒ©¡I½ÈjúHóX#8^}k•69êÚİš²HÈõ¯4Ômü©¦ºéI½\Z‘±˜OŞâ£Ü£v>õ8ŒMò×ÒµoS=z	İ?Z6|ùíÖ€Ê¹Å1õ¤EÖ‰–”iÊêÇçÒ‘1ƒJ‘¡9#9ï[1±Êt>•¥¤Å™”Ÿ—*¼L€€>_zÚÑİ®”ÜñJ/Vö¤™œšJçĞ³Õ¤0\\¦ ,P%Â©¹İ±GL¨éøız×ØÖ%d³VE#pšùà5®§~ñMÖ:R«ó¾Pyç¯ãùAŸ¨tè+`\nö+9=¬r/‰À6s“UÂ’ÍƒŠĞu$»U	Ó“S{î(Å£>E%I*¼Éµ3ÔÖƒÆÁH\"©KÉÚ“·Rã\rÌÛ—<¡Æ5™>\0À;½Mk\\[;oÏ+éY¯hÛ[ŸÆ…}Åy\'¡‰rxÈêj‹ \0“ÍlÏfX‘Ñª”–d)=éAßvšŞÆÂB;Ö5Ò€‡«¤¸±,YØğAéëNıû§1rÙfã±®Ón}+¦»²TÉÇµ‡}j “ÜTs7Ğ”­«9Û¬dŸZÅº\0†Çå]\rí¸Q‘Y€«\Zi¦ô5N7¹áş´øÁç±§lò·n¨ó]JËs£})\n‘Œ­Xµ…@;ù*j¤W.2İV ŞÊŞa©_d]I¤g*jCµ°{f ·ÚO­[’PÎ[×¥=‘pj:²Ÿ—åg=*Í¹l—‘Å>8•“sòGj³ihó9Âà~t5hƒÕ¶:Úpİ1ï]‡ôhœn“$úVnŸ¥a÷H>Zë4ÖXØ\rSık\'µa++#³ğİ½Ò ¶Ó¢È—‚‘Oëş~•í_	ü#©‹´»¹g¶[äL}Ïù>}ğÖç-ÆÆR>áRAïÎkéß†ö/~ˆÃ‚Hî3^}i;Z;İ›IÛğ·ÃKcn’ã3H2d#ø{^½§[ü§Ú+•ğfšéhğı9ôô®ŞÚ/-h·«3¨ÚêL(éEß±ÊWòùfõâ£‘º`Ò­²ä\Z€IædƒsRã{šFFt¤*…ÎÜ½WÉƒ*Ãp=ëFò&U$²À&³®&kƒ*mÇ;NqXºfªJÀíû¥e8ç =*•ÅÛD,K³ŒgŠHåi-ºääcƒÅbêWæ/1É*8‡\'ò®iv7§kê]¼£¹RhŠîgÆÉâ¦q±I\0Éëõ¬©¯$šÙ6yleàùÄãÛ\"§Ó\"•¦w¹ERÁ~hÛŒñôé\\ºİÙ\nK’÷Ø-šs²7A‰—Ó?Ö³aÓ¾ÏöòÈT\'¨¡­ë»€öR¢	ù°Ş‚°®o¤¸ÁŒ(5ÛzûÖ5`¢¬ØéÍÉ3\"şHYX»`«/os\\üÖiS,;bºû›ÆB*‰\0äŠçäF`Ë\'’Nìt«Ïœ.´=\nS’nÌç¯íU .@°îq*À­túË$YKyj ñÏ­r:›y[‚¾ô5ƒ…¶;iÉÉ\\æµkq:…#õÆ_Äd$Ç¥w\Z“œ¿.¾9®KRãŠÍ.]Í,·G/~Ì:JÁdÉ95Ğj	c×•³HXíü\rtAY]×.Å+˜¼¸°^­U¬ÔÆ\\òGLV„ —+Œâ¢3»\nqÍ;;hDWAğ«;dÜÖ­ƒ3ƒ),müá“ĞV¢G´/>‚³“³Ø¦’c~Ï”%x\"˜ÒªFC1õ©§u$7©]©)¸rhiµ`²I•¦pNqŒÖEİÈ\\©«’oÈ5“¨1U#ôãÍ-Âé™w·÷`äÖnötl·µX›åÎ*‰V=Àä×L\"¬g¼¬P¹@sY’¦KÆµ.œ<Öc>âN8®ŠvÜçm4Ê%rME,Ga¥Yuå±Æ*ÛCäVÉ¾‡‹iÆåFµİj±€!l.3WZN§µ/˜¦3‘‘Zİµ¡Ïf–…	mYW8ªfb#ÿ\0¯[D\0§Ò©È”ñIèÅ%s!à*0:ƒÊXmäzVĞÂ¶ãT÷V±qKQ5ecR¶Âà¯\"¼¿_²òf|Œ×°\\\"´osÿ\0×¯=ñE72õ­©Í&rÕWZ~ëÔâ£¦*ÕÂìw_<â½Å=NHì3Ê¦…‹y§Òsìkar¡Ê¤’éR*0;i°Üu=«jbsY;õî:+V\',8ô®‹Ã.¶÷ÑJÊÌ»?JÇ¶\"VÇU5é¿´˜WPI£H¥¸R1ç¸_}À=?Z”ßD}ğ?^ñ6£5¤7èÿ\0Ùh0AåÇùéè;tïôÅšn\r‘Åx÷‚/d!VúO.ãËacœöè=? +Ø´‰\ZHqÎ8Å`î÷3²İı˜ËsíQI\0\nA\0ûUà1Ò¡c…&¡u3…‘”è9Ò©ÍpØ£(È?Z¤ê@5qõ.)=›,;U€«:XW¶kVã‘Áªr\rÙ^¦¥¶ZÚÜÆšß9#§zÍ,’éÚ·.—‘Óµe¸r­èäê´òf-Äjƒı«&îîÀ­ÛÕ“×•p0§Ô\Z¦º¢S×S™-ÅÔŠÄ½„G¿•Ó]áw‘ÔVâŒ>yªæÒìÍ4İ‘ÌŞA¹IíXw2îãŠé/8GÍaİ¯\nú’Z†•ˆš°¶¤FÈ9&­ÃfÈÀc\0t­Q§osÕÖÛnçm¹UÌ}?G%K1ñ§¼K†ŠÔ–)±ïKm£E·Ì’CÏi%dB}Lû(Nã•a“`cœµX0ôU©ÖÔƒµ†jÖ‹ŞkjÈlmÚg/º«;D†q¹½=j®•d£s¿ÈŠ3“Şµ\"™]Ê ,O”›e¶šĞµbŒÇ\'«­ğ¾Šš´Ùòş[‚8µaé\Z{Ï!Ï_JöÏ…^3\0>öW8CøÖU\'ËšÂ\'Wà/y·–’Opélb^:u\'¯åí_V|=ğêÛ@$0ùdq\Z·_­p~ğ˜ƒR„I‰\\&>S€€ŸÊ¾ƒğ’¶Ê ùFyûÕäÔ›•’:áîê¶±Ùx~Ña|ÛT}ër¨é”·ÉêÆ¯W£AZİäÂ¡–äG•U2?¢Šš²¼G®Cáı2[©…QÜ±àWJ!q¨=´&Iü»PNJİO Ìjş$¼‚#öyvõ%Ù6ƒíÏ5Äx£Çïm}ö«{v*g»9À\'`õä+Ë¯ş&É}·‘ÉpSn~Õ(Üïëµzéı2>hô6PoÌöû/D-^kÛ©n<µÿ\0õÒE®E™i“K*G´~5óÕ§‹µiÀ’Î{EcÅıÓ3êœçß×&¬Çâ)ğ#ê÷L3¶5÷ØTd:W;ŸTl{V§ãk&â%úİı	®XøbÑ¢¢*„Ãˆ×{“ï+Š±]4ºÜ»»™dpON§#®tQİéÉ\0¹™Ú?*Hàóøwú×¥ÎıÔvR©å{şI¾/£Íå–ºŒ“À[våşx­íÄóŞÆÛ\'¸…!em¹üëÍ|O«=‚<ãVŠÆåÊ1ñ… œşÈÚ|@»º¥Oë—p…šÚp„{	qéJÆÎÎæ­(ÚP‹hú;ûZàA\"›–t#ò:†]mcµeY•G;WòÅxœ-‘Ék©I‘Öx8=7+Ú¯iŞ;¼ÖÜÜ¤+‘´D\0?JÎ|Ö»\nu Ÿ‘ê1ê±ÉÜNò~ñàš«¨j~{°Fê\0,=yãë:´R¿Ú,.“1›ŒzûT/âVH\\ğwHAüñ\\®=NšuŸ»©Õ^_ùjÛIÀã%«œÔ%i>ùãÒ³Çˆ£¸”©fdK\ZK«õ \rÇ&¹½œ›ÔîÃÏ¢#¹‘•[Šçod¯½ªõıò°òÃò:æ±§}ÇÍM›v}È¶Òkc6æÈL­·¯jÌ–ÕãÎÑŠÜ•IÇİ¨C‚µi;´wè`µ É$ı)‰nHå1ısZÒÚáÎM=-Cäæ´û7A»{¬¯cnÀ­(Ó{ÛXUÖ­´A]¾jÇ•µsNVåIíD£9æªy%r	Ü=«TrjÏºÊ7Z[\"”Rº3%·9r;×?¨BÅˆ®¨.skP€lı3R´wf)I#•¸·\'=½Åf\\¬Šp~ítwP?†³å·ÍtÓjÖ%oÊ~hCn#¨â«µ¾sĞÖ´¶û7+\ZÏ—÷hMm3RÔÎ’¥<\nÌ•\n3`ô­9%ûÙíX×·A	æ·„[º8%$îÚ ÉA<Ô±3“ŠÏkìg‘‘ÛV]P„šêQ¶†RšZR:( œı*»¸n1X¬gÔ‡ZpŸZ¯g%î£8½MéÖ9cö¬ùm²H¬´ÖX–<÷©`ÕR]ÃqÕ7Ëa©Ü.ä&¹OY™\"b0EuîÊQˆÃgµbê¶ùEÇ_ş½LSûD;4ìxî¡—#ã¨5œ±§ut:ì\"åÇÓùÖ˜zW¥x\\óÜyY\\‚\rI\Z}íÔãótæ’3ó\ZÑFÁĞ‘	Ï54pïÎB­×­Û»\0ÊÃšks;Y«Âä¦C{WOáã$—Q’8#æSƒ×Ö¨xzŞ;–nÅz·Ãoé77(ú ºkidÃˆ×\0×Ÿ|Tó$õFmÃfzçÁ™­ìf´t’i0Üdo2BÇÛ’qŸ×Ş¾­Ò›dŞ0qô¯,øUmá}.8`Ñ¬‘vôšP¹>­ß?×é^½<¾•Œİ­£ù™$­dö	i*y¨dLîâ¬”\n¹#5ã(vŠ„šzAüF{Œ³næ«J¸SíWæ!Ç¸ª3tj¸²R³(<y\'ÖªJª¨xı+Mã\0>Oİª3)*üt«½İ¬\\·Ós*hƒ)5™2Vş¯\'S‘Ÿ|ÖeÂ±$\rK¿q-:˜×1\\c¬{¨Ö\\â·n	O–²f\\—$ã”4ìKÜço!Â¾OZÄ¹@ŒGŞjèî¢[šÃš#¹˜ô¬ÛkqI(;£›¿Lo+éy+ŠèµúçõÏÜÀøÓR¼oaFWÕ£Ç>Ï(l…8úUorÒlµR–ÓÖ¢¹FO-é^ŠV;mYûÒ“Vm¡qÈÂŠ·c£ÌøvàUÔÓZGØ\"¥İìL_.†t™ĞƒpíVàÓ\'Şr¤\Zì¼?áT··JÏc0£ĞÔ—²Eä„u#.;{f®×Ğ¸ÉIû§*m&òğxö­Ÿi/+1Ú)-l¥º—hS½:×iá­Êf2ƒÚ±–š3X»|+¢Ç32‰$sß§Óïÿ\0\n´=GRÔ#6ğ˜bŒó[€>ƒ½qŸ\r<&oïà¦È³&>fŞ‚¾ªømáÃcg#2\0I /_ ¯/UÇáGe*r½ä¯À[k¯•Ë»ş•ëÚ5ˆŠ&ùrz\rÜW=á]!\"™÷rTÁõæ»;X€—$çéYĞ‹“»&u÷bhÁ—\\ÓÎqÆ(¦È¡‘ƒcó^¤U•2ÿ\0P™c)fYIæG8Dÿ\0\ZòïˆrG5¬©x_Z»û©9\nû£®;çé^¥slÄìˆQÎ…ÃëKöæĞ	n¤^íÓ>PÏ8õªæ².r•®x¥çƒï\r©¼Õ¡Å¿1E;ÿ\0«ëÊ¯÷°O=p7\'Qµ»¸H,Ğ Ùp«¾EÈªc“Ó¾yüıŸWğöäÓŞÜ]Ş\\·šLîğ£§áëîk—ÔoàµÇØ´Èö–ÛæI!2ëSë\\Ä¶Ş—:éS¼¯}RØòITÚ š[İfø¶ï´jÿ\0¸DëŸ“®=3y¬—¿ñ6¥vd¸»´†Ñ\\Fş<ã¿éÆ9ôjv&Y¯®^7l¨òbŞO±ÇAÅxş¹ã+kû‹‹m:;—”åx€íğ.ãğ¬áUµd¯òş´7£ÚR_×õ¹Ñ¦¼tè˜Éâ}FÙ˜ãÊÓâ‡}ï××¥rZÿ\0ì®Y¬®õ·’\\ãÏº¼U‘†xÆê;qß[SÒ<e6¦E®ƒo©Cs5×–[#¾WÏ½lé\nÖ ·3k~¶´”}Ç³XnÊzîèy\'SéVœ!ïÉ¯•„”b›¨ì×Ÿ@Òl4»y\'ÃSÓí®]1ö•¼G‘sß\'v^½:Öõ­5´“âø.®*g^?|\09ö5‰ÿ\0Dwq´²Y¡\\äJ<¸É?îÓüö©4ß‡Ö¿j @Äèüğ:ÿ\0j%8ÔÕ»µó.4ßÇª^lëìş%\\RÖ{:}ÇÅ«\"3cœ`Œgç«ßÛúUÄê“h2İİmùÎVSÇ|;Û§Ö¸‹ŸƒizòøH5M4»ü¾SDè¹ÿ\0h¦qïì+>ÿ\0áO‹ü2DºN²÷À8ùe”zdÏ#ë÷Š.ñ÷bşäzAñ^ck,Ğß\\[¿{kÈÔÈ\0í•\'?äûÖt>3µÖ¡Í¶µg+©ùÑÿ\0pPq÷˜æ¹\r5/êßûRÑm5“ÊFS¹Tô0uëïïÌË§As¨İØÜ)ÓuNLq®Uúôn‡é×šÍ¨EÙêiNœ/Í\'¥ºnjÛø‹RÒ¯»%Ô\0ó$dÇ#·ëızg×&¼ˆ›jŸ½Hÿ\0<W; [Ü²Ï\rôx™r‡*Ã+R+dÒ.#-¸YÎv,›pùàû_ñ®y¾i=,vÓ÷eÊº—$¹Ú…Øöç4ÈdyçŸJ–h¾ybşà#½>Á7HËë\\Ír¦ÑèRŸ*³Ø}²3‘Ò‡´!OëZPÚ6E:yi+%)7g±q|×ochLÏ°¥† ÑûUÙ!vÈâ¢Š<îì*om\r »1–‹¶Cü@UÕEºõåæ«Û&Æ“qàş•bİ0ñ“Ş´Wè\\¢Ò²#òÄ{À?7^•™{K¤V»ÆáÏqÚªMÒ~\\æ³}ÉnÊ1b#ÇNµBæ?”°ëZ×e8\"²\'FEmİ+5m]Î}uhÈ»Œ2¾:õ¬K¹L}N¥lÍ!†sÅršÎ¢Š¯·$û×U8¶ÒHÂsäVD7wÊàŒäÖ%æ¥¡Ç­g_ë\rpqîk–Ôµy8èÓ¡¥¬yõ+¨-V¦½Ş¼ª!ÍaÜê¥‹ô®~ûRuÜ7Ö5Æ©\"†;È¯B4û\\ªI½YÓ=ø;›½fÏ¨œüÍŸ¥s\r«ÈIË6~‚˜uòMj¡®¦\\íèÎ€êä«tô¨éÁ+Ò±Öá±ÃdT‘İR0\r7nÊå¹µ‹òO½%¶¨Q‰$ƒY—Ø;MR»èzÕ¤„¤÷;İ?WŞpOváÕâ$×¦j!_k63Åt–W[Õ”}+	Ó¹¼e¥ÎCÅv„LÏ”×\ZÊU›Šô_Û–…±Ú¼şa‰\Z´¥¬lsIY²(şà£GZUè~§ùÒ•ĞeŠ»EIäŠšJ´l2	l•ôªK¨=-:ıì¤ó#põ®ûÂ^*Ô¤¸XEÌ±ÁŞ%o•¹î>¸®H·ŠIÑnŒlpvŒñÍ{¯Ãxô+››[CafZ\\ó¾	ôÇ<uıhI\'v®c9¨;òÜöß‚w‘,qù¶®7·˜’pßçúû×Ñö“¬ÉÓy÷€4}`ò-äSÇ—\' `uÈÇ5èğ Ï½cR¢“ÕO™+ÈÊäcš®Á¹ÁÈ«2(9Á%ª¾3Ş±æòm\"©ËnnÕÊ\nºS\0‚*³²º8Zï°ù•µ3¦BAÅQ•8ç¥i·\\U	®îø¨¾º	ßFfÜÃ‚H_¥f\\GóÎmN¹R*Ê¹hb:UG••¹˜s’ç“Y\nı:úÖÍ×Ş<ûÿ\0:ÎŸ‘M_fM6íÊÎnó!I¬k“Œó]¢€‚vôãëX7nVéËm{®ïS¿R@ç¥s×€Ç×Ow·ZÂº‰‹7jtµˆ½ôG\r†\"\\ei,´Ø®g\'ËØ¹ïŞºMDFà€P\009¦é6+$êÍÌdƒ;WVúnÎäi À55¦ŒĞÊ¯9®§OÑæ¹yİPÃmåßücÖ¬[Z\rEÄ0!òğ>ìî=ÍkÅÑyœıÄ2É‘”ÈÁaK‰Ñ0$¤úšŞ¿··³s¸4)`s’:ÒGi\'Ì\\şéTÕÑq\\©Ë¡•o[F¸c]Ç„<9.¢ÈenûŠ?,šç­íÕ¦çå¸¯iøo¤£F±¤]@$úı}k’«q^gE(«Şç¥|1ğºÇ™ÔK\"T\'î¯Óükèèû-QBåÉËsÒ¸Ïè`U\0İĞW­hšc\0W\'œØ¯nSg²ÓŠÕ›z\rŠâVl3ÏÖºKdÚ=GëT4˜ï|tùEiÇ’qÛ½z”ch«LİÉj9¥FÌØ\n½ÍHNMeê;•ˆçoA]hÆ*å[‹Ç”6~H}ÿ\0‹Üÿ\0…p>/ñl:R¼QàÈÃä‰KJŞÔ¦šâRï9Ú:,}s·:\\\næUUŞy$®Iük‚¥U¬NÊtí«<¾æ{ë«ã<0y²¸9i›j ôÇZÃ»ó÷Éö–!ùš>?*ômjc“d£×©æ¸»˜£O0;eÈãkÍö’wJÓZ#’›DX¡d—çËoùŸƒøÖ^¡¥ÃvHŸMÓX¶±gıyÍusÏ;‚H¾23µÍj:M´ÓËqmadgnÙvëÕ‡?şºÎ5\\o©ÕF1RübçÀÚ %I|Czó6s%»‚Àû‘úT6ÿ\0\ntÅœËk®^Ë6:J@Àç²ë]¼/£Ì¶G\0ğ#`q×¹©g,©\Z!=ÂŸ¯­fêİ®Gù*1œ¯c|\'<LUoĞÇ¹%ƒrŸÇµh	Ÿ\"E,,8)ó1ééŠé¬®Õ3óc?Â+BÒá7“µyàãŒÒö­ô%EòÙ¯OêÇ/§xU£òÂ@¯n¿òÌò\0Ç§×úÖ£èŠ 5ªM»^¼s=kªb`at`\05§k6ñ·r²ı*«zÈ–ˆà-<c«\rÌRx[ø$@6“Ü ÿ\0…g¿ÃÈÚÚhÖ@¹e#$zL×¨¦•œòD¾öÑ€jë*rõ>ÚÚ!:|Î×Øò‘á7¶f82\r»”c )×ZÜYK±†eÆµwòiæQ”ÏÎ¬:J«6ŸæG,r Á;F9}êNfäÎˆA-c¡ç‰£;3³HğÈ4÷ŠâAÎ;Wn¶;Ôü¬aP,\'çœù›}\rck¾cÊÚTŒ\Z¯yjüš·šÄ£œu;TSÛ¬b²v¹Ó–§%$ÈqÒ«:RĞÉn;r­f½¸·¨«‹¾Æ±’nÉXÊ‹”Uè¢ÉëQK	‡<Ô–Ò§4œ­­Á¥]‘TüÄjˆ•ÃqÍJ²õ¬ûçm§&±æiêa&ìgÜ”cšÀ¿»HãaıjíõÖÀÃ<šæï¥.İšİFëC	{½L}Jôm“\'ŸJãõi\ZD\'q­t—è›{×?«OåFë\Züİ‰õ®úZS•Ó8­^vŒ²©üë•º39=k°“Ly]İÉb}j¬ºFî×¡\Z©+3Îtùõgß¬¥˜æ³¥Óä˜`©5é©á3±aïLÆ’|«Ï|µJ¼V¦Wrw¹æcM%NFi±élÄ§Jôÿ\0øEşGÊÊ¢Odà\'5ª®·E:®Ézº[ ùH«Ë§º±Áİï^?…$(I\nĞÖd)»¿)êiÂ­Ö¬•E¥®çœòäŞù¦Í¥8V&»ˆôm»³ŒûÓn4Â¹Ûó-häö%R÷u8ìÇEf¯i—²ÛJBHíœ×JºI}Û8µUm7lÄ2cñWÎÚÔ\\¥}i…Íƒ‘Çæ·JDÏ‘kÒïà1ÚÈ½ñÖ¼æÿ\0+3{ş”©îÚ2©äTqâ¦KRüçŠ…IŠ¹hX©ãé]Án,Q*W{ÕÛ{V—æEİW,¬-åd)”º0G§ç]_‡,-çq´>cªJÁAÇ¹©»­]:K(`\ZHÆ7\nõOXØê!]*>ßêCÛğíTmôİ&\"Ÿh³Khİ‚î‡\'ñÉ=?â½ÏáGÃë‹ÈSQ´¹·’İÎa€ìO±Á¤Ş¦.úhwÿ\0	õ·¶€+.-Š(8`sé“ß¯ùÅ{\r¼ÁÓršÇĞ¼<tØ8-üx9­Øã+¸ÕÏ&˜é­,Æ²‚Hô¨ØœŸNõ$€¡#4×RÃ©^bÕhº¥SƒƒÇ¥Bñü¹ÀaWÏ9¨$\\â·‹»±_\"‹ ÚÇ5V|l#½^~r*œê¤œ6M9&ĞœtÔÉ¸Rr;VmÌdd“Òµ¥$nÇQYÒ“ RŠl˜;û¦ÔyVõ‘p³ÀÖİÚ7rEbÎJ³/ëWË¹›´^¦5ê|Äç­c^¢àÿ\0z·oó¢°ï#!˜õÍf›»½Ù…zƒkgƒŠÃºsÔ×Az_Õ…r¤nçw½gñås—ÆÏıïS].„`tL…ì8V/öh…pWŸzê4[h-ôÌí\nÃ©=Oê«;X¶ïÔ½wvÓYwÚˆq£°íšK[±ai\'XŒÓ‰%ô’»Œğî2jØŠ1ƒ“Î:U¶–ˆV_Ó¡k†g+äâ¬_:B®ƒÛp©`‘4ø\nŸ•±k>{ä“\'Š”îŞš\ZEó6ºèö¦êå‹¸à?:úCá\'‡ÌlNBğzZùûÃ6ÏurJ±wnÿ\0€ï_`ü\nğÜ1é–å—Ì—p`Ç‘Îrqşz×•Š¨ãcÓÃÁ·wĞõßh†$‰ÜaB£ú×¢éÖÂ(¶…\0	³´]4®ÕnIÒZÂ×hÆI®*oVkZ§ÙLÑP«t&¢E`¼ãğ©\"~ õí^Š²8eÔ|	8Àõ®zúD¸FVmÀğ@éW5Nfuÿ\0d+¼‘Ê’¯§ãXÖ«Ê´6¥Ê·QÅå´d‘´ğT×9|Ë\n:«;°É;¸«zô„2G6Ğ?å£œı+Ô/4 İ;g†\0ğ\nñå;¥*rv¹W[½\"&%H\\>sõôÿ\0õ×%rşz;.2y\"µ/m£¼º¸XàóX_f!¶CE$“µq\\üölô”9:ÙÚ¥¼—\0ˆî^§?(şb°î,å`sw(ô^¯Jé®-¤l RAôÖMÆ9ÉØp9ëPå}äMó&gH\n)ıóH0Î\0şU\Z‡Ùò†÷=é/l$\nëó¾•…rÍ$’qØÔ¥Ì´eÙ7¥ÎÂÛSFlç#¥iZ_&ãë^g°Ñ¥]‡ÅQS»8<SP×r¬âõ=fÒí™\0=»ŠÔ³»×¥yæâuœ…gÀ#½tĞ^«®P°#·jÆIÅèB‚o™»­îåÎì0ô«bğmÇ‘\\u¦¥ÏŞÈ«ë¨q´6E\r¯´‰QÔÕyG-TX`ÍWkâ\\·÷¨2î\\•Ì½ÓUÚâÃl\ZV“b1Ÿj™ls—Ç#ŒÓìÜ¼yÇ¯ÛÆ[<dU©ö3qµÚ1®-+eqÛ¥eİD¢\"«œ•Õ]ÚŒ°Ù¬+Ë&Pç\0ã9¡7ñJíZG#w¸9\0šÊ•˜J\'½t3Æx\'\'¦V²¯¡[¥5.¨êKMvúvüêkÂŒÀÔZVFËÏCYfù#9jwoKÉI­N„j!Iõ¬İGQ\\¸~²fÕrBk\"ëRŞNæÀ÷¤¢­©Ïk=Hu+Â€#³ÍÀ*[uQ½Ôw;êk<ê<‘ø×Tl•‰šR~Cî¥%ŸwZÉº’üÔ“^}ák\"îÿ\0ïÉ­á&–†Íİ\"¿‡Eä‰9J«qxÄ‘Ô\nb6AsÉ­bÛÜÅÂ\r”Œî=ºŠz&ÿ\0»ŒÕP§5b&rİk4“ÙŠ)+»bŒ`g€{zÔÉk	°ôœ÷À!ñM‹ZIÀÏÒµŠÓV(ìË×ö+,,sŒwÍa¾–¤¶1øÖ¬Zœr7`šPb|ò?\nÚ-\'c™§\'siq©#8j¥w§1Ê©³v„’ÃYÅ$ÉıæÒºßs6µFbÛy<8Áöª×q¬ÌxüklØKpØŸ­Cq¥I.{ŠÒ2OVÈ”4½?X¶òíÜ‘‘Œ\nòmD‡™Àè\r{fµnÂÖCŒ€+Æ5‡Ú¦8Û‡5ÑEë¹Ã=’‰£8­[HÈà¨=\rBNjåµ±(XEuEês­]BğÕ“¬Û¢=ª,ª\03.íÃ9Ï9÷®¢ãá?Ùf†æÂüùdo	2ä^xç¯ùÈ¯\"Óo.´ë•–epzvoc^±á‰ÖÖqIm«X=Íœª\0Áùà>Üàƒş{VmIkgÊâôØõïøGÄštJÚ¤–3ÇÖ\\=ğGùü+Ø|\ráM2ÖDûD7Ö7js˜˜¢¹øĞpÏ­r_ş!êWú5¨Ø—º8b¨÷\'FyÀ$pG}3ıÚöÍ\ZÒâku˜\" |q¡¸ú¥g)s|VB’wKç¡ÑiëöxB³–ÇCVU±#T6±’Ÿ7Íøu«*§ VIûÅ­$A+‘œqÕ\n’=êçÙšGû„ŠTÓ&\'…sôZ§¦æSÒ^éO.zUyFs†ã½oÃá½JáY…¶Ä^»˜PŸ\\®íÀ.?ÚŸ7/RâÛVG;/\nvœçÚ¨ÊHS¢ºKh7r9â³æÒiÎıkKó+&\rn›9©¾éÖ|Õ[oZéäÒ	89>õ[û\r7°f`qKšÛjDl™Æ\\ääcX·Q0½Ä›¶n?SU&ğô9ÎŞzóÍKšëpµÓ<Æâ7\0åO5u;Øg®?\Zõ¹|?oÉ(±$ÿ\03Y×:,*ÌŞR‘ÔáqUÏìGCÇ¯`‘ÁE‹cŒ)Ía]YJæ)ıÔ-ü…{|ºT,N#\0úÕA§ª3\'+56ôHqfxIVDòÔ“»\0\n·qrĞÛ˜IÚÄuªX¥6i½Ç^AsYg7SåØ¶ãMzp•šfê:–tÅ72|Ê:VåšÛY\\$²¢ÌPä#tª¶Í•´·\'i¬ô¼rHÌrÜã5[êÈºwL»­ê\rªİ›(#`àQºÌ0\0¬Èf\0’Ä¨÷«ö×{V1ÇñS›_d¸ÅCc½ğR,p¨F`Ü\r£\'?Nõ÷¯ÁÏ›-	L{¤(â+ã„:_Úµk	°YİÂÂ¡r	Ï_óë_¢^ÓÃIµ‹$şèn>õãb½ù¨­;Ó§swN‹\\cj¦ß—½hA	8ÇËŠ†ÕB.\0È=êÜ\'õ´#ec’MU °ö¦€qSr;úÕiÅ©èB}ÌËÙHã=k˜½U;ö³Ó®†úQ‰ùW­r\ZÑ`vğ	ê;×™^VĞôhÆMhsººFU¦8w5ÍİÄÌÛQ|Ö#øˆúÖÎ¤\ZGmÇÒ¥Ñ|;>¤“ä@8.G?€®)%×¦ù4¦-¾‚÷Qà/ÊÜ^GàZèlş8ˆI9\n®\0Ãığ3è+¿Ğü3&1{ó·-é[wVÚ[’û@ÏS]”è7y=O:x¦ådy]Ï„ µV€C\r¸úW!«x~dÙ\Z©>œW¬ë×Q¬N‹ÈñÆ:Wk7,Î9ÉÀ¸«B0vêwa½åvyOˆ­Ú<nŒ×j²l2qĞW¦øŠ`$2d‚yŸˆg2Ä3Ú°„£µµ;ãÙËjW›ö¬)57Wù[ëšŸX½Á`Xd?Zåç¿Æş˜5Õ­ÊrmìvÚ?ˆšŞ@á·míšô]Årœ° wÏ5óÜZ™GÈ%\ZßĞüPğHÛ\0ô5¦Ş¨¤¼Ï¢­u1òíuæ¯Çze†â§Ú¼·C×Ä‘#,‚Enœ×e§ê!Ó­`ãºm¹ÒAx\\ã§&·,×zñŒz×Ò†8=k¥ĞåÎì“ƒÒ±tô\"ZGFt¶Ğ‡‹€3ëZöVª#“ƒÜ\Z§¥Bgœzß·µU‹ççŞ³åIlbäí{™w–gœr¹ô¬{ë0QÆÍÙ ô\"»6µgP§îõ•w§ã\'Û¨¬Ú²Ğ¥Qµdy®£f°(d\\Hã&¹ÛâB·µz«`\n¹Q‡#=kñf4~Ä•TÒÜî©;êqZÌwé\\İÂ†lŸJß×¦Âp+‹¾œl5kO¨=!«m@Ä[æéY—z‰|üßZ­vNå±¤»f,	ÇÖº”,KŞöe›«¾[¨4ìrªÒ]aˆİíU%½;ñ“ZFšHæœ”U‰®îÏÍÍgH[“Æ¤oœnÎ}é‘#¹ÁëZ-V†s©e¡Ä\\Ö¬$+“R¤G;TdÕûxç¯z§Ñ)Yñ©RF0*Ø®â§qZ²@§;x5JhXãŠÎ*Ú ³‘spÅ1Yí9·_ZÓ–\0IÏŸ%«|ÛGÕ\r™K¶B.ä·+\Zµk©¶	gg¼R… zÒG\\õ5¬,İ¬cÍ¹º.ÖPyÉö¤Œ’ÿ\0+dVm´›W\'ÿ\0×W-åËdqõ¡¦„ÛŒM«wè0=éoƒ4D:çŞª[³ã• \Z=¯Î8¥¤¶!İÆç+¨Æï &8¯Ö“ËÔnW!kè½B4h$	ÆAÍx‹íü_¨ÉBùR}1]TU¤pTI-4ù“\rÉ«vs˜†È5Œcå4¨„\ZïZ«3é£Ñ¼?¢iúı”ë\"•Ó	+g¨>ŸçšÛ“á½Í»>b„cÌw‘øµÁxoR›I¸I{ `Y©ñ_CøWY´†îİ¾×5Î›>V8Y¤»ñ×Ó¯µG$–±1O••şü>Ö´VG¶Öf1g&Û…B1Üs?Îké‡š~­\r®É¤\00Pp¸ôÇ§ø~y¾\rğÖ™®9¶I\rËé;Gµ¶ã§ÿ\0¯ñ¯Xğö€4ËT¶yV\\‡Æ3şqXÊ¥ş%ø£ed­9?Ñ×sb\0%±š´‘|ı2)b‰bPj±y­ck¶Ğ¢õĞ’Ş\0ç Èï[Z|×UlmûÖö›h1¸G¨¡[a»¶>TòmÈ`Aşµ’ã©Æ=½+VõşvÂƒX·÷+yI°(\\®é’½Ô`êwi8ã5—‚	ÍZgX‚Ò `I$š´ùS¹2²Ğ¦ÃÌzUVLZ‡kÿ\0*¬Ê~`X×¥ØJÎúÌƒ,:z§$`g\"µp@;€ëTŞ¬Äşõ­º!\'Í±™<9$úÖdñ†õ­©”e‰ªÆ0j[46Òv1\Z\"ÇT+f¨\ZE#œV²A½Êç¡¨¯`DÊ§’:Ô^×{¶’÷‘ón«Üèõ•œv^3Ç½\r³NÏ+œv\0ÓÍ°…Có{×§î¨ØëƒnæM›8`êvãûé\"¶µÛœ¾qJšúğZFñC…\'9p9®cQ»òƒ\råÙºóOGª.ÎûšçÏ(àŠì|!¢6£*\"G¹	ıã7@;×Ÿ[Ê]‰P2=kİ~é‹cáûgr^yÿ\0|ÙìlPígbÚV=ÇözĞMïŒ-bh¤2ğ08Î~½¿/^~ŞÓ-Qó?ì¡¡É=åæ­ fW;#\'¦ÑÓ‰?ç“õ5´~XÀé^KWªüù·F=1Æ>µ<``‘Ş£(qÒ¤Œ{×DV§+ØVáIjœÒ\0y>¦¬ËÓµeİÈ\n‘ùTÏb º˜ú¼ê±JœŒW}rÈYµt\Z­ÉËs€8®7To7yÉÁ=y%vîzøvÔyJ¶·W[YF2	ç¨¯GğŞ’n±$‘ì·LSÔû×\'àÏçûDÈG÷Gaõ¯Sµ€FFB/cU‡3¿Bq5lùbË!HÔF£ø»š¡¨Émj½·?ækP&åÆvnµRö¡İQCz÷¯a+GCË„’z}®_Íy#ùP˜bdÜ®?ÏJòÿ\0_ù!”Î äôë]×oÙ%èïÎqØö?çù×‹k:„-ÊÒ´cÑ‡8Í|íxsM¦}&¥.T¤ÕŒ_êHÎÄÉƒp9¯0ñ.³\Z³á”¸Í?Å<…™â•—$^qªê¶ò!u`Xgçüë\nT.îÎùTVÓr=_V\r+ä€zqø×5wx’\Z©_js±}ù÷¬vÔ‹‚	 W¡\Z:hssİÙ3[ûAIê+FÖğ7C\\‚\\\0y­+K°\0ù¾oZ>MÅ§vÏQğíÿ\0•\Z.vã°¯BÑõ“i;óï^¢ë€šô-\Zÿ\0Ì@CGËRw7æŒµ¶§¨Yê~cšëô;æWB‡ +Ì¬nw€Aæ»§Ñ€pªÁ‰ük+F[0’V=oO”´JGJèôö,Bœ\nät™En=0k°Ó#rrq\\®-ìq©;3bŞNqĞvæ²õx.LQ®å;Àï]5•³È‹³©jëÃÆ>lv­gNé«\n‰;\\ó}n¹e¤÷ÍyŸ‰JªÊ{ã½kÄp¸’h‰w*@â¼ƒÆP4I88vïÚ¹n¢ízßºµ<ŸÄò5È$\\Mô›w`ó]\'ŠnÈ•Æ9®âå‹’Ü\në„/ª.¤“WèE+í=k\Zæ|tJµ}u±°î.ˆ-Ï&»TO>öZ	=ĞBCU$$î«ÜÜí$“š…gHÎkhSKcJúMšÖ×?5_•I¬8\\ÙÇz½\ràˆüÜŸZNšjäs+ìoB†İïR¢o$qYqŞ‡‰\n*a|ÊÆúæ¦Íèáï+¶_1Emí¥Rº»…IãÚ¨Ïz~f-»µš×ä¹Ç>Õ0£&ÇÎ¯©r{ØÊ¶ÔnSYÏ¨ª«\r„zÔS_D3ûèÁéËTYÖáYÕƒ`õ¼iufMó¦Ëfş\'H÷§\"Å\"áV1˜  © jI\n“µÊE&µ§O[¤Î~xÅ\\Ó¹…ãû½;Óm¥;xo¯˜ú×ÌAÎĞ;ƒLƒUMçn@5ºƒz´g*°êõ:›)gœâµ m;y®^=fî|fµ,µ›9\"Ünâ_÷œ-bé¶ŞŒ˜¾uk–gù÷¯Zñ?ˆöMˆ¤v-8üëÚíï-®Klš6¸q^[ñJÏ:¤7Jİ–À¤>™®Š~ì’g5F—º\"ÊÄ³\rÜŠÙÿ\0„VGDx”äÿ\095Ÿ£Æ×Êµw³–K¸D¤\0sƒ×{ô®Ô®ì=¹\"†ák§…Ü@äÄ»±Üúê}«èo€òÚGé× ÚÏpA¶ºn#Ÿ<”-Ğ0ã¿¿nÉ>Úiú²Íc<‹o,qÈĞã#%pNzàúÃÒº;¯v“[¿ö\\ÒÚFdY×iÚs•c}úş¢¹Ü“ÌI8«\\ôßxfŞÄE9Ü$a…`~éäW]mhÈ <ÏFÆ+ÂZ%Å¾›ö{›‰&1(Y\0Ëıq]U¤_\'&³”R÷S¸×=“¸È¡!N~Ò>HÇJHà=*ı´G(QsÑËË¹nÒßœ·A]IäZ3‚SÓ­I v«×Œ6ôÛJé´Ùtù-Ÿ¥sZµÉis•_ş½t7Î‘C#·AÒ¹	\\ÊÎÍ×µ(r§q%¦¥fQƒÓŠ„¦X“Ò§·yã§ñTlsZ§ñ—¼ˆzUfV\0îzÕ­‡\'â¢”¤w§ªZ\n/R—88ªò)ÚÕi†	5Yşá¨Jæz¤Ìù#Ü<Õ?#xaşMiJ¼—5vìå°3ÖŸ/+½Å¹ŠFÅ-ÜÖ=ü–\nzWC{”Êã­s—ä$u­’kB\"û³Àí£vÈúTWd‘”ş4ø-ä”ğMGs¦˜W=k®\r³Ò•4Ÿºròå[yk—»Ÿ38-É®’k2!vä·Ö¹i£arTü§Şº•º2]ì^ğİ´sŞ¢Êp¥‡Şï_Gx7KhvnD%ÕvÆÇøFyã>Õâ¾Òà¸Ö¬Öv;Øíô¯sğ|òkso<}¢á-‚Ò ÁGoÿ\0_|œ¬îº\ZÒ‡5EÔû“öuğïöW„a”ä™rW?Â3Ÿëÿ\0ëë^º£h=ëÁZXÒ¼=g\0\0mŒ\nİ®\nIÙÉîË«.i±1€p3íMÁtäSëÆ~+|fÔ´ílxKÁ\Zzêş$|	¦oõ6™ÏŞ=ÛÛ·zëŒ\\İ‘Š¿Evz½ıü6;Í2D¸å€\0~5å^-ı¡üá=Ñ]ëñÜOÚDiØœôÇ~ãÖ¸Ø¿f¯üBÍçÄ^_3ßb¶!\"Ns´ßA\\÷ºìÙà\rÆ¾Nmrãø®—Ì=r~÷¾OãIÓ§5QßÓş	Ö•:pßŞü>û%¬şØv\Z™x3\\ñÃ•ÂÖêüã‚gòéøW-Å?¾)v}á]˜¤íIu†Ês×hõí_dÁ iÚDf;[ Ê±ÆÊ²uiİ“cã8®¡MóF	úëş_©Ó\Z©IJ“·{Ù¯ºÇÍv?´­ñ_3SÑt…èb‹ËÀú¬Zìô¿|q™í)³¹VÈ\nõı.Í¤¹Ğd±«©^E§Û³Êâ4Nx=êÖ\"÷—$Rô&W”´İù#Çµo‚ßµX·¿Ä©´ÿ\0_%›§ã\\‰¿f¿_†MOâ® ñºí\'œõõ\'óÚ»ÿ\0ˆ?´\nè°M›n²J¼,¤’[è=?åŸ|YñÆş,šT€\\Îß3\"ûg·ÓŸÇ6ÿ\0Xœ•©Ù|áNT×ïZ_uÌŸ~Ëº~Ÿ+5÷Ä}Bäîû›ò?Ÿçÿ\0ë®Zø[áıi#0ÕføƒåGæßçó­WÁş)Ö\"šçR¿xÚ¥£Èã‰ãsÿ\0ëÏø‡À÷ğ¤óé·RH©\'Ê%Ë“Ï®Î;æ¡^MŞdVÄA>XÉÙz$l^èºB!‡ûróÄù¸]Ätõæ¨Â9¥lqÿ\0	EÑCĞ4@ÿ\0*ñ×Õ.%–fyËØeoá>˜íUåÖ$gùdl¯@â©Qœz˜{^·g­Éá6$EâkyŸ¨Y¬åR‘T®|\'pX%¥ö™<‡øe¸hsÿ\0}¨¯6³ñ>¥jß,¬ã=ÿ\0…wÕXµ&â0­Ü‘JIÓ\\Ú3x8ÏE\'‘£7uø¢WşÎ†éO_±^Å6?ŠÌÆöÀ°¹Ò5H02wY»(üT\ZÑ]*Y‰5B‰TùŠ·Ö«¦’Öz•Õ¾\0ÁfşµÇ9ój­~Æñ¥V×Œ¿¯¿ô9»oéÖLVk´…—\0¬ÙŒşMŠô/øÛLºØ‚şÛ\'€LÊ3í×üæ¨ÙøçX™ÕuH´ıjãf¡cqîqŸóíÏMoàï†Ş+Œ¾¯à{(\\œ™tĞ?¹À<ÿ\0úèµ\'Ş&Ÿ–§zuiÇšÉ¯Çü÷M8Œ£«+€ÊTƒ‘^‰á;ƒ»| ^3¥~Í~»–i<+ã¯xnñÈıÅùY£Îzó×Œç¿¹®³KøOñ«Â¤Ú6¯¡x¾ÙÛœbv\\ğ0}‹Ó¸9á\Z2–“·®‚x‹Å_O_óØú3ECq\Z”ïßÚ»­íµON‹_5iu¿~ëÆ\nÔ´€O´ZÆ]	Ïe=zg‚yÈùK{‡Âß‰~ø6‹¬[_HÌañ >êyïù\ZåT\'É­ÏvşWÓ#WP¼äpjôÖ*˜(?‹\'­V°#r³¬0{V„Œ|’J ñ°ñø×eÆQi}Fù®3ñM²†oá<G¥xÁÙrO º{×Ğ~-³Jé_>üA\"Ö	^L‡\0“í÷y5i¨Tv=ªÒèùëÅRï–NÀWpê²k©ñtá¥m­ÆãŸ¥qZ„¸‰ÎyÇzì¥wSJ²Vq];û¶iXéŞ³®gÚ‡»Sne>k’\rS¹l¦sş×ã]Ğ¦yš¥{Èá÷u¨Ruƒœ{T ù0õ¤[IN2Ø®˜R‘Ííb½ãV+Ô‚<îõªë¬‡fÆN*8­cE&W,=0Ë\nÈŞRl_öOò­U8§«m)k²õæ£«Oö{\r>{™Ç\0*şgùÖ¸Òuı9ÀÔ-­mŸ“íI=¸+Ÿ}a”H›C‡oO¥W›\\–Ş”ÔŸëR’OÜZNÚ´¿¯ë¡Ğ;Í·ÌPOY6Œ}\0ş¿–*¯Ú~É;—òşë€GS5Ëé÷Z×‹,uI¬.ã†kL³C™%ú‡^{â¸;Í^÷Ï™gy¼Äb’#±¥8IË¢9=ªÕ]ÿ\0]tÓ¾!E¡K#Ãk§Írqƒ4`äôÛj\rkÇ¯­D¿h0)PlDã‰5á~kÜÌ:tÍMlìeP[Åi**JÍê\\j¤¶×¿SÕVò-Ê‘RÚ´Xg©ï\\…¥œn|¹0İAíUšşëO“1{õ>Ï•XÑ5%¢;ì“q;{ÔÙ[Î»Z5Ú:ñÖ±ìµä»QÎzÙÓeÇæ¬õµ®kB].kØèZmØ\"âÉ&$}º\ZÑ·ğİ¼N°D!^Ê¤Ÿçš4ÌĞVº¸º;ŠÎœ›{±º0³8Å±Ğî5¹tÛ…u½F™Z WÔsşZè#ø	ªøÊŞòM&æ;Ñjª&Hˆ+»8èI\'Ã§ãXzo‡îõo‰Aj@‘âÙ±Ÿ- ŸóøıÁû<øû&]buÿ\0k¶s¿İs“P?§’zÕùïĞófùŠ>Õg_èL.Œì‘°b`$–çå?7ùöÁ­£^Á£jf/éSY€„ª]ÀÊ¥†@ÎGÔ{ç§#?¨·v‘]Ì«,1Èvëœšâş!|Ñ<c£\\‰4Ø/ÜKi*\r²\'û8ä0•œ+§¤Ñ†­Y?™‰ğûKƒÄ^Ó®í®VîÆ[5D¸·z~ıq]·‡­g´´‚ÆI”óx`¥xÂ:ûà/Åx¼!,òKáEçé²LsäÊ3”?Sß¦}_§şÊ°d\nİöÒ’÷{¦M­\"8í¶‚@Ú4ä‹ktÇ¥[!İê[{`ÀŸçY¥.†7±´\'ozÔ³µ9Éù})–¶¹9«sO³ù”fµ…Ó±-ßbÍ¿—>sÅT¹}+bçF#½+éöÆäà.>ñ=*îDzÜæµÉÛåNÓœ“íX;˜’;ÕË¹ÍÔÒ>p	ãéUJp®ìMÈñÒ˜Êš°¨T“œçÚ˜bÈ<ÖìBêÖEf\\1ÇJ®Ñ€X\nµ$[	‘ëQ?ïJ)¶dìú/Ñxªïn9=}ªãÄÊƒzš…ºtÈ­bí±)§¤Ì÷·f,[ŠØCfÄğÄsSÚÛy‡$dS5dÊ•<½ÉºŠ9İEŠ‡_zço	ŞÛG5Ğ_`ç×5Ïß)Rä•ŒôØ­6<JËldçæâ¨êÆWl©ëŠ·k2ˆÊô«v¢<’ßzªœœ^§²’w9;›Wh4B+“¼ÑäË<\Zõiì¢·ŠYØ`œ*dŸ`Sì+×~şÆúç¼?ˆ5YåÓà“æÎ+Øœ¿ç=k²3Šİ˜{7ñ£æ¯³O3l$q_W~Î\Z,\Z¿Š´«rˆ€”€rîqşzısæ^øM¢]øË^ğç‰ZòŞ]2UHÖ\'1ä3³ŒõÆ2>œäú·À;\rö…“Ãzv¥.Ÿ§ª”‰\ZY\n¨bª[¶väí=ºn9ít=¥)8ô_Ûu5Ãsÿ\0İôë§õıi¾m$A@À÷8Ö¼ßâ§‹õÿ\0‡>›UÒ¬ˆ`¶_ß[¹Û\"ŒıàT|ßL~}+æ»?ÛâÇŠ&ß¢ø+{@2É¹}ù=qÏ#ƒŒŒŒÏC\nç©$—wcË$Û’O³>ºñï‰WÂ¾ÔKuB±“ıâ+’øCáxt›GœÇ»P»Qu{pë—f~Bg°ñïÅï>?ÖçĞ4}jêÖŞ»è£0Z)\\å¶Ì=2xèN3ÓîO‡iÒ$¸oâpŸ÷ÈÅDÿ\0wïÍÛ±Õìœ(ºÖğ>íÎ¾‘À*r2)iŒd¥dq£:âáæb8ÅcÏ\0,Ìà–éÎEtMi‘Ä?\Zªújnêàsº²q¹´ec›Ä£MG†ÚÛ÷çî¢úû“\\æ«àïø­d–ëTŠÍ[+¶ NÑíØŸóõï Òí&º•šÊ6±É­9ôøÚˆJùk%-ÇbÄ*NôÖ½Ú>XñçÂ)¼!y§,÷ÒÍ¤İŸ&Kğ£t’w7·¹öÉê[kğé4ı-4µ–;İ-°Ë<`e³×w¯ùü=¢ãF‚îÂæ±æ‰Æ×VÇa^âm&ûáüÂ}&iÉ_	2Tdğ·ùú¹ISŠI\nå‰“æ—½ç·_é¾=ğfi¢´¢âÕYùÏÍÛ×?çÛåïÀoûÃ:”ÚeÅ¬íå…íÑÙ) ôW>¤6G×œæ¾¯Õ>\"èºœ¶š­¼ºt¬˜“x\rc_\nüVğ>•á/\ZßßÙ‘©ÚKºtg_İ£Ó#©Éÿ\0$œí…œ*É©6pÕ¡:o÷É´q?\Zt\Z^¦$M¸#¹‡•aŒ“Ç¹Çÿ\0¯çhòù§\"º+€‰q,„¨ós»l{UV™œHYz×CºÑliN›·-Ê‘é†(Ø°é^‰ğ£H:ŒwŒAÄê£¹?Ëüõ®ÊnI9½?ÁŞ\'°ğ¶‰%¼|Í2î`SÏë\\U$ù·;)AE§©­â­.(îDùdEmÊpT¢³­Q£Í!€õ¬«¿½ÄÏ+!=	ëU“Ä‘Ï‘\"´`rHŒWiÍêÑèÑn\nçcm£C{µ 1êtz„–’€ık†Òüaeb¡ã™ZA‚±ó¹½8ÇùÍ{¯…?³üE C{jUƒí#Oç\\•”é®g±Ú¥²i–ü(¬\'U“æLçµzç‡g1È¦6Øãû¾¹¯6Ñ¬¿ÓV £qÉ°ÿ\09¯FÑ ò\\·R0Eeu¹5lÓOcÔ4+£y·¾AyoŒ4s(pGã\\gÿ\0e\nx¶vÕ¼9$Şñ27™¡§ˆ_“ó¨ã©Ïê}MuŞfc!*ãïÜW¤én­¼·;²V”å$ıíO.Î)ò»/#Èÿ\0gŠ:Î¡ªj¾ñÚ-¿4QóÎ8Kè:$«Óœz~8äWĞ–°¬@ŒOC_şİ\Z«¤Çàß\Zøn[‹[<¶’ŞXKåJÑÆ[Ğ^äc8\0üûañö…¼‘ ±ÔüSzŞ\\†8üé^ÌpüŞüZI÷Ğå|ø‡\'·mì›_ğ?Ë_#ôçÇö±.›#¶Ğr0xµòïÅƒÙæF8S•/ùä~áZ¥ïÇ©´É$½âİÂ.càœòªÃ8ÏœşŞq}?ÆÔmš‡©<Ÿí6–Nıùã§ùïæWÁûIßÚE[»:ğõÕZ[›~)KÈª@Px®R¼ıËa³ïVR÷V¸šä1Ù¾6èàÏPÆ©/L{µ[½zÑ¬ŞUŞ±Hbš5Ï<1Á?ˆ­)ÑQj’~†’©ÎÛ‰‚Ò%Õ|>ğÇ†.<7ãxëË¸Ñô¤:v‡¦I;/Ûu¹#BV¨ëµAbzçŒ44¹ÚM&é¯¬Y¿w#qÛëÿ\0Ö¬\r€Öë)wû441Hw*3pÌ ô\'$zV±„¤½ß/–§›ˆ”êÓP‹qwOMìíóµŸ“f±…,¢…vÌn_îš¢ò1—“š±#¬®[<µVemiÍË¡ª§¦â9—+ÍdßßÅlÅ‚Â¯jS´’\0¸d÷®iç–GfRO¥5ïliÏ§‘ÖX…¸|³d\nŞÕôõ¸Ğ.„KˆÎ1×éšàôë¹ãÎoéúÔñ‡R¹R1´ÖÖºĞçœ—¸q\Z^³á­r+ë&Ù=¼Êûî¾ÓÑ¿.£‘Ú´5oŞŞj÷+7W/ºD‹…\\(\0cğÏ¦IÅ3UÒå–G•Wïy5ŸÙ]„gÚ·O[œşÎò× Ë«qn0ŒÒ¡¶ssÔ»W\n».Ñù½«OÃúQo6hşQĞ\Z–ú•ö;iÑÅc\0Bƒ‘X-‚)Õ†­kK¨Ê~àÚ\0ÀÅQşÌ’á™¤,Içšçr|×gM:*1»g-a‘0=k´ÑX…äıj„úK\'µ]Ò£uàöªø“*àtÖsº°ç½kÇ¨lç$Ö‚ò­ˆíC¯°~FÍó;D·àÿ\0øwáÿ\0Ä;_k·-°ˆE-´ æDİÉCıá×}FA¯«|=ûf|ÒàGãÈâIf3c9ŒœkÃ¿g?\nø·ãbÇÅúLzÂ[Å¤o+ÇµNr~Rwî}xú\\ı„¾ZÇåGàDGn-ıÆG¿ß­åÈ¢£4Ï\ZqŠªûèbKûlüóOøM\Za’s›qÏ\'ıj–ßöãø&Ï±|Mvû¾\\:|sÇ\'ed]ÿ\0Á=şßBËa³¡Í‚¶7ìHÿ\0¾÷VßğLı\"D•tÏêëîó-¯àŠ]êßxo\n\n’3ƒ¼ó™„h½ì]5\nÏOÈô¿Ú¿I}[örğŒ¼9İj–W–×v2¢dWV`;68çJòÁ@ã›¾&ğTö·şìËip³	e`¡ÏlõÇ]<\rû1xgEK€âÁmmc™¸-²ºœÜõ¯Ì‰ú¶•ÿ\0	Ş«-«Çui3+yI>nŒ{ÿ\01øô¨Ùò%xtïıl/g)B<Šúy÷ÿ\0‡>äğ×í‹à-zæ8%÷N‘ˆ\02¬£\'\0±9#ùwïRGwoÖò	a•£ŒÈ\"¿\'ş\ZÚßêš¾§a¤øwQjvMm‹e‹› `\03ëœğ2@oÕÏ\nXKeáí&Öáv\\Airö‚óURœcdõ&jTİ¤¬nYÛ‚Gô­í2éÊ¨éYÖ6ÛØÒ¶Æ!‡o|t®hèaÌÊ7G;†}Írş%¸òàò9æº‰ÌÃ }k„Õåw²88ÇšVOK™™$““ØSpzÕ¥·àÿ\0œĞ±níBOäTš–å\'Œm$ö¨ÂrÕ¢Ğcüj‹µªºWd7e¡GnGN)¾_ËıkA¢¥4E“B“ìgÎ¦i‡—Z‡ì œkPÀ1Ç\'õ©­,”å˜p:æœlô¶ĞÎò>ÏÈ9ö¬mAÈ\'{WE©°B@íÚ¹{ö\r¸ş”=o©*;¶Ì+æÆîùíX7 ¶TœVÍÛd7ÿ\0\rbİÈy$p+;h8ÁKTx5»sïëZ–†?d[gw¾kRØ¸n\ZÁè}%Úgyğ¯N^øá­6xÖKi®Á”7BÓü÷ığ~£iö?²£\"´lT #åö¯Î…6™ñ@ÔsòÅ>\0ıkè‹^$Õ¼\rªI¨YêY™eDå\\À>Ÿ‡?×Š­IB¤\Z=a©×¡È­wó_ğ.ı°ô‰ÇåºğÂÄg“OAvCm_5\\¯ß=Aµğkö{ø—©k:tû­2Ö{K¥¸‰.|W ©]Ã‚1ŞİÈÙC>¿uw}wqæêz¡f3dğ:v^ıÿ\0Bşé+¢xGF´Ú—l€ıp3_Q,TéÓ…8ÛÎë}Ï\n„\\)J¢mjÖû«køhÌO¯‰µ_İéòépG}tŸäÎH\'•çúÂßC¦Ácgk¡ÙÅa4îK`c<\nú&HRT*êO­Rk&…²„•¬#Q«´–½5·æs¨ÂÍXø7ã§ÀïxsÄ~Ö5‡ÓnlVı	6LãawtÓ¶;Šû?ájùz¨NYgçÅq¿µ‹Ş|1yGß¶fÈ0\ZºO…âóMº•1å»¬À¯B¬ Š™´âª$—MØÊø_gÙ¿ı¶Ç Ñ@9QPp…Ws¼È¤ğ£­Xª>Á2ç“ßÖ‘Q*‰7ƒµHü½êí»‰aù«*k”nâF0O¿¥Ai;F’1ÚßwŒâ°sQ5Q¾¦¥ÙÚ~a´v\"¸X™-¦–î2p23ô®‘õO>?-¾òŒŠÃÔõ\'D‘A#œúWzŠÖ:èÆJWçøãÃQ]ná­¦&:7µy\'Š>Âèæ9>ÑjÉ‰#‘@`ŞşÇü÷¯¥5é`¿ixĞ©®ZğöŸr²yÀÃ¯ı}kÊUÒÕìTjEs­|OğGM¾y\ZE.A?»7rAüÏæk‹¼øMclØÄ™ì>˜Î+êísÁ16÷ŠwpH8Ï§ãï\\£à©ÕX™·œ\'lzçüş5ÓS^êz¨Ò¶‹ğÔğX|+\0=1S¬C\rÒ½VãÂ2só§Íg]øn%AX¹­~±ÌírãF×±ç) )bO#éW­ü3¡SüEu‹¤, áI©¡µØcz^ÚjèÊ4õvg+aàİ÷åùsÉ5ê~„èĞˆa>X=Tt?…aZ7—¸]†­Lî[oÌ~\\ŠÎJr¼Íé­N·DŞ÷©(\'+ÏéúDa™[®T1Çl× éaå~lŒäW¢h±¬`÷ï\\ñåë¡…Mzß„“†`ï\'·»}ã;?_é6<²İêÒ´v¶v‘ï¸`ªK2î€2I+Ì|Yã]ká¯„âñ]Ï‡ç†]—íFssg!_fpA pFFGïìñOø­ñkÅÚ¾·<#­®›¥’?Ñì”‚UøJ–Ç|•ÚkÙÃ`ç8ûY-<»ÿ\0À<zõRTÚºÿ\0†«ùyâTÒ|Yñ¯ÁÕ!ñØYİjorr±³/BT©ÆGµìP^Ecsk8£”»\0c·å^+à[c¯şÕ:ÕÙ·Zèº]®Ÿ»Ñœ™èUè(×\rÜQ#<6¯ºb:\0Ü‘ZcªrBKkùïşEFš“„»¯ÍÉ¯Á¢ÇõAå€8#p8Àôÿ\0?Ò¾mø…x×lÏ -Ë|ìOÿ\0õ«¿ñ‡ÄK§¸	 !OPßy½+Ä¼SâQy¿$ìäOá_5^r©Ré½*<”¹d¾óÂş!Û¢_H@€yµ†—©âM>ÎîC\rŒÒíšAü#¯Jô¯Ên|ÇşÄÖ¼Ö{†¶¹Y”ídmÀû×fIi!b`ã{i¡ÒxŞÎÚfhP Œ”ÏuÇ¸­ax£Â¯áy4£´pÉrnm‰r²«  ãİş<€)Ş\"ñ¿€6ÕBÉ±Ó±õªQø‚×RÓ-Ä©w¶Wq.bŒ£ÎzãéÖ½JNM¥ºÿ\0VıO˜¨ç	EôÖÿ\0¥l\\G4~bcæõş\ZA…Ëg5ÏjÑİA©Ü¤seár…U¿CúVÅ„í5²´ˆCÈ=ªœ\\Uûôæªz•±‘œı+?û=Cã‚­[¹X¸¨YOsIG›T\\UÛDijªä*€iëÎ©ÁüiVM„gô­fF\\}ñU(Ä¨ÂÊí‰oğ@bjoìøJ²²(úU»â$òÒµ­m!v9SYJnÆ‘„Z²9vÒ¡-ÂòOf-0v­vi–ì­òSE§Á`ª\rsóİu:TiÚÌãbÒY¿‡>õ~ßH$ë´W@bHxüª)e\'#š¬ÒØÍÇ‘XÄŸKTSŞ©%ÖÀëbæ|‚p\0ªhyb+Hóêa¥ÛìX²ƒc+N&\n1Y1Íåä1VlØÌÄP¤ì+óFö=öqñ\nøSâ|WÌ!¿¶6ŒÊ22çÓ¿>ı_¶çºmB_;†R£wâ¿;<9xtËènİÃ\rƒÜöÿ\0?İÿ\0µvÔü?jÒ#yjË ş%\"ºìçŞèò*¨©sw:Û8ÁäŠè4ÛAåJÌ\0sŸZÎ³·A7·­t‹û<pãæ‘~f”n“9í} ı²ÊIá‡~s•ÔõëkwŒ7Æ8u8ìC`û\ZÓ²Ğ4½(ºYivVøùw$\n	ÇĞV?ítu¯Ÿ\n45]éaöVQÙ@RªOâu³\0ràWEEhGMïş_¡ÕSHÂ>_«9áU0…@­H·±\'µU¶ñZöPç\'µs(¤ìk÷4ôË|œŸ½éS]¼ªKeò`sÜŒqU\'?)ô©ì	\\ÊÖ.ü‹gÀùœ``× Q>n2sŞµµ›³5Û(â4ùFz“Y‹X‘ÂŠ\"­«šBlÛÆ3L#Ç5(\\s´Š>\\\Z¤Á«¥dG· úSB\0NOÊN6Ôk“òŠ»7tg°ÁóòÔOÓıjÉ çÖšqGA«ZÖ*ÇóÓ¿zXüˆÊ•ÁïRZÚí-!z‚òV;ƒ\ZQºFIêúWä1cßŞ¹IŠ—g¥t×¼ïÇÿ\0ª¹]Lá±ÜR•ìTn•š0.d9>õ‹|Ä¸­ùG u¬k™‰àñJÒjå_{#j7{Ö¬ç\0ã‰i(8\0úVµ©Hñ©qg±ÒzöR1n=;ÿ\0ŸçÒ½‹ãO£ñÆ‘¢D\"#0›<Ç?Èÿ\0+Æô«8İ³)\">§ŒÕÙüJe™- M¤¢I\'5TpôêN2šÕR¼ãEğËJ7>*ĞíTnónV3IQÉü;óŸĞı>1¼q(ÀUğïìÇ§Wâ|\r.ã´ÔvG_Ë?Ÿç÷=¹>‚·©%*¶]]rR„\Zîşÿ\0øbZ(¢¨à9OŠ\Z?ößu›U\\–·c 5ÃşÎ÷¾~n‡?ñå\Z÷hÉCü«Öîí…ÔÂÜ¤ŠQ¾„^ğVFÑ¼K©i›;ÙíöŒp„î_Ô¼ò>§ªæ§%ÚÏôıNºôgOº¿İ}xÅPzq\\§ •‹|á£`¸lŸj»qv©¼d‚=«kòeÈùË€Vs|¦ôâîP¸½û,±G1ß’D€}ÆéÏµ#Ìc’áÕ‹D1Ûß×õFşø†x†6g†=³YÂùâ}ÀPÙ#ûÃ¸¯>O]ÎïfÜt\'‘¤…ÚQ&Ø]xOçXÚÅÛ<e’ãy`yüjÅíêÚä„ÆSoéX7¤J¢L/?÷Ğ®9¾czm­ZüVåÕÈÁÏ\"¹{ë‡V$çÜ×Y¨t<n|ş™¬‹‹DÚÙ`3ÁÍp¸Æ;£¾•fÖ¨àu	å”¹ØÁG©×?z©ÊœƒÍwº¥¢#²ÃŞ°o4¥•IÇ¶jâ¢ÕÑÕó+®§ŸÜDÄ¶EdM¥ä»Ew—\ZZ\0ÃÒ³ßNP¼€Òµ·*¼IS¶—8Ÿì­»Š­%©€¤{âº«Û-¨î@`U-.ÅµFewïùÖÑm­\rã(ò^Æ%†ŒòÎFqÿ\0?Â½kÁ¾NT…*\'’Æá?Ë)óæŒì½Mz¶‡áÓ:âŒ;ìçğ55\'wÊqN«æ»èSĞü0’F=Rzfº6ğı¬6íÙRG]›PòsÆ@#­tzO†%})Ú\ZX[îºí%½1]‰d/u[dù†Y¡È¬Õ&å¯SSVrlğÚ-¼wÃ{-]îM:-‚[:3(5ûªê¹*G‡ŒíSÂ~É>Ò®¾&M¯Dš€¸°²ó®^ú2›\'|«È\0¥àä½·}ó\r×¦=«Ê?hMJ/|,×çÓáßUÔYAå \r$Òƒ§~O¯ã_OI´¹zô·ëşåaeJj\nÒ©¥ïeïi­úz»w<»övÔ…Í§Œ¼Q,3oñ>»s5¸ÆsnÊ™#€9aÏ¥hüEøˆÓX\\èzJ«aÿ\0Òn÷ºà^œÿ\0:ÙÓ|ÿ\0\n×álXÚÊÏ`TiäãÔ–\'Üçšó?iòêÄ°$¹óã«çóøÚuæ–ËEè´ÓÔú-:tù«^öi/–‹îVùœ†¬·E_ïw¯>Õ¦y»¹ızú\"ûÁ\r%¤nõÆ{7·ÿ\0Z¼_Çº(³TUrÜ}xÇá^o5š±Òæê»Ç¡äº»ƒç§ZàµÛtWr:ûW ëj`W­ •šï¤ô0Ò×SŠ™KïŒEgG–—Ìv®£,\'ëş{ÖµÌ{%ÆìU5©Utç‘cİ$CxÇp:Ò»éK“cÅ­b¶³áÙ¦ÖbÔ¢b†x‚JW£¸$îúÿ\0õş•j5ØvÖ¶Ÿp·š<DÈÃpük=—qÎ*çQ¯vÁB”T.·+Kn²+°ê*¢Ûƒ¸7è1ZÉ\Zqša¶»ŠJVÕ<’½‘;‰àU¨bÜIíS‹=ÌÆ­Ál+ĞVÉ®]L’l­n“ÏãZVó’	TÉïVaŒ²|£¥cn¬ì¤”t‰«oy„Æy©cºİ¹ªEĞUØ\"`û×,£­ĞEÙÙ	+°è3Uf‹Œä\Z··ky¨Úİv·TÉ%º1œœŠ/uÇzl‘€ù~•ua*®1‘ùTf2Ù^Âµƒ¼Iqwò*ÛÀ@aëZVQnO^µP!Vy­dêqM;îKå[\ZÖ‘n@ |Äøï_hü»7²ÜâEF3Ğ‚GëÖ¾9ÓbÜÖÛÆ«êïÙæêÜx~ÁY–3\Záİ˜\0Ãqçô?­uÒ’I¦yX¤ÓMCéVÊ	bœZÛÓTÜjöqtPL„ã°ãŠàµOŠZˆ~Ém?öáÉZ©çğÿ\0==k£øs¯ŞêÚ¾»«Ù6ÚÖİÆÿ\0x(˜·¾\0ÿ\0<`¤å{hrÆ;ë¯âxåÕÉñ?íAã}Udßo¢i°iQ89Şø÷Oç]ò.WµçPßèz·‰e\nn<Aª\\^ïPy]åW9ö¸úõ¯I·Ãä*ê½Rì¿àşfõnª5ÚËîÓó-ZF¸>¢¶l`f\'9ÅgZÂ¡HĞÙÄ\"ƒ\'qÛŞ³‰ºaî×(¬mRëìÖ²98 `VŒÒfëş5ËëwFY™3ò¯oz—+èAÇ,ÌÇ\'­!QØş´¸ùH<Ò(æ’Úæ¨~ZQVª\0õÍ.1œw®„’3»q³\"ÂàµÀ3V\0Äl½sH#Ô»ìŒ”YŒ(Îiaƒ\rÀÜÍÒœFZ»i–ŒüîÇ­$¶ùV›™|˜˜VäƒçîkZíø*:c\0V%Æpç¥Lv¬]·2î†ü+™ÕòÅÈÁÅt3à1# îkÖ0ar§ÃÖ•Ó\"öZêq÷Î¨ÎIæ°®¤ß“•¥«Ì‰#XrÜ¤Ö¦.É“İ3Åíänë[6#ø¬[=¸°­‹&ùzãÒ¥®w¹íÅ¦¯syo-Y\0ıïZÍµ”Ë;§8#õ=ºä6O_Â³‹İfùJıŸ\n»¶qŠíÃÅFìç¨ß>‡Ö±´&ûÅZÅÙR¢;h‘së“šû*ß3ë_)şÈPÆ/ukˆÇ‘\0\0`rkêhd+_­pÅşöG~-;Åy\"ÕŠ*ZèNèóà­x7‰‰ğ·Æ{†EÄ7Öév¹lîul6^„ôã™?7¼‘y¯ı¢­†i¢xŠ5%,.U.0?å›şgüğz°öç³ë§ù~\'N\Zj5ş¿éóÓ[ÏËq\nH‡*êcO®Gá¾¼š¾„±yd–Çalç+ÕOå]c>+šúµØÊpp“‰“­).3‚½rr\\ùHÙ;r~•Öß¿Èç£\Zá50G›ÇŠä®ôÜê£¦SVÖ®®ïde„qóÿ\0ë‚MAŸækŒ“Pß\\3HÊòÙ$u¬»™Èc–àväNWê{*Õ’4…éJ3’c9v=Fj…ôìÊÊ@#¨#­f¾¢Ğ3dãœuÅVûyrW<ûT\'{´JŠH}ÕŞÀ{c¸¬Æ¾gdŠ}ì›yÈ9¬%¾uİ¿×ƒíC´´-;;=³áÜ—9úÖMÜ»¤t\0cÔÔ‹u½Øsø\Z­qˆÉ94á-Mi;+.¦uÈdféòúU	q;œ{Õ÷&e`T¥ÓôÃs7\0\'JÒR_q¤m¹>†|:Cİ.nb}:WWá‰V\"»Íµyjè4ˆ¡@ŠZBrÄœcÚ½Ã:Ri.&	ºB6íoO§­`æÖÌç©6¢ÒdøF;q\nÄ¹ã’ÕØxSAeæ]…@Ç·½&“f´»”*“yé]¶XA(¨à0+z4ù§ç%R°ÓÔ!@2§©ĞÕ;,éú˜È[\nTã¸îk¥Š?¼ŠwÔ\nci+2Ã··µz.•õG,+Y5.¥›{ˆå€4_0oÖ¼kÆ¶Ÿğ³>4èº\n¶ı/Ã)ı¥ÃLàˆ2p9Áì>—«j6¾ğş¥¬]ÈÆÒÒ&”©ç è;’x\0{×#ğ—C¸ğï…/õí^/+\\×fkû¬œ”\rŸ.?ø\nàc×=zØó(7/ëúÿ\0‚aMòÉû7®ŞzéŞû_£[¦qÿ\0üD%¸¶ğí«m‰NûŒtö_óÿ\0Ö0ü:ğÉû2Êà˜e\0d‘ëYqèx‹Å·7302Cór3ÇçõçŞ4M×JÓâ‰c*2{šğ=›­Y¾‡ÑbjC\rF4!«ëæúœ‰4dkQùD`‚0Ê}Jùâ&œYç}œ…ÎqÛšúëÆ(¿Ùsè‡zù£âJ\"5ËmvœƒÏjÃMS•ÉÀ6Óæ>\\ñ…«ÂÎØ+´àŸojá.gkÕ<bÃêyv¯+¿¶Ò\\ÕPzrs†®=OP‡–=«>î<DÁyâ¶oİ«5‘÷«¾)¥cÌœ9QKÂÖ—6ÎÙxŸ`eI88ü1øV‹!±Ï^Õ‘£ZM¥k\r1ÿ\0S6#qŒ÷ãõ®¦{@73ôÒÕ×9ËI.fºáˆdç“Sä´ØÁ_céVÖ\"cÉçÖ³m/C®3Vå*›”¤¶G¯y[•”TL7ËN· ’MØ¬¨ñW!x9äÕtm¹Ï\"¬	v®\0üi¶º˜ó4IÂ¯[&ääâª@ß(ÈÏµXT#œäTN*×-6—1,‘sƒùSJrEJ«´qM\0©\'95Ïk-K›pîROÑ\\Ô…‹.,O$± úÓŠ½õÙ¶V¥Yµµ*vŸ½RÛDy‰­h†ÓÜšÖš¶ænOn„ÚZìnkŞÿ\0gÿ\0‡ÏñÁîî¯î!Òào(Áä6zğ¯\rµ€ï`¯§?dÍA4ß‡—Şq`SdrX@ï‘®GÖ»(Æ÷—dy¸Õh§æ{—‡¼# ø*ÁeZr2çş×¿ëYÿ\0´‰_Àÿ\0/¢ß³W×\nÙBƒ†-+`×¢ç×ñ=MSÅºn©â;Û}Ã¶?¾v»+Í·Õò‹?iˆÿ\0i¯ŒúyÒ™í<!¡Iÿ\0Øä{éIå#øWiàuÁãpxsI¦õ8é7\nÑ«òëëø­üŸä}1àí%tOXéªÛ…¬)yçO>õÒ[[äíİYV!Qø%–@\n“ô­ûğ=ë&äÛ9áÙ\ZVQlÀ?•kÊ<¸BõÀç>µ_LŒ™±ÏÖ–æBû‰8ÏjqM-J[×·F¤|œ‘õ®BFó³1c×\'­kø†èo0nÆ0p+ˆõÛü51Z+!iİ–éN\n9çŠf>µ0‹šÖ6¾¤EE¡#l\0úÓ¶d±\rÇ­(\nö4è×vïJ¡Ëái!Ÿ.\nã~´\0JLãÒ„MÇ”{IŠMZäBg›€qşÕ[™Ä+ÇaŠ’Ñ~Ïn[3~‚©ÜËÃ9¤ßDeËÌìŠW2ƒ“Ÿ›ùÖMÜ„nmØzgpŞ•—;‚\ZÅ_¦ÌËºèÄšçõCòa[Wm´±=	¬\rNE!‡N:T¿„Ê7ìp\Zë“+úç­ayªÇn~jÙñ;,Àƒ\\¢Ëór*ÊöÅ¥ÔòëIv’:ÖÍ£eFxÅcBNI«ÖÓm\\ÍtÆ=Z0{‘ÏÍŒ“œVO‡¦3O;)Q;9ŞS¨9©ÊÙ;)ê*Æ>Øe”£ß5½«K¹ŠøÙö¿ìhò#ëJÁ˜„r~¹ı?Zú¾ÆE|™û%\\¬:•ú€FèU}A õõd2ßæ|5$F½ä¢ßcD6\"¤ª°ÉÁäóVPaq]gšÕ…¬_ønøkPÒ§PÉs ÏcƒŠÚ\'4›†3Ú¶ÛQ+­O”şøÛPğ?ˆfğö§¹um;÷pn åuÏR8Í}%£ø†Ç\\µY-§ªx ı+Œø¹ğKHøoË»éºõ¯Ím©[²!ì¨ö¯¿Ñş)ü4,ÓY¯ˆícû·ºn|ı¼õNç¿çÔšª^iÙùqjª÷·]tÿ\0‡>º>j8…qºÍ³“gƒŞ¼‹Aı©ìm×ìúÄÏep¼<:œ-¸İÓƒÆ}×Ôg¹´ø¤ø’İdµ¸…‰ÿ\0,ƒô5çU„çØÚ”7OËÔÃ¿µ9gkwÇNõ‰t®UÔÇjë¯b>YÈ#F+½iÆ2kÊöV±ëÂª’ºg/vN=g‹’¹çVÄÑì[ƒÏÏvé“Ğ{RP’vKCH5Qz\nìÍ¼îù}*Ä_)\"¯yØBZ¡!.ì`ÑYÅnÑdÄÇu>Wó\"#µ	nOŞ?•\\µ³ysÍ[µÌ\"š¹–-‹JÀÀöô®§Â:B´‚f9ÁÊç¥2×N;°G9åuZ>œ¨«ó«Ïd×=ºØÖúrÃ²“–RCÒ¶ •Àï!C÷ü+27Í²Ç\ZÑG\\äŸz¿¡$wrÛÁ|õ©Ö]Ÿ-®ÙØéöqÃ2;.vsÏ<ö®‚ÓÈ#Ë:Ö–„9-¹‹/Ş#¥hË­iúLfkËÈ-uiä\n?S^®ÚMI«Úú›Vò+£ŒôÀ«HÀåq^[¨şĞ²œÚØË>³~ü4øZO~ tär=Gr3Ÿ|H… 1Ÿè’ü²HuìŠz…ì™ü³ßÚÇIéë¡ÇË)\'%ÓÍOäIâ9#ø©ã8|9k™¼;£L·:¼Ãı]ÄÃ>]°8ù€?3`öÔVßÄTZ[TÉ$`*Öï†¼1¦x#AM;J·[khl¬Ç–f=É<“\\•İ™×u®Wt1Ÿ›?çüÿ\0??;C–_×ço#¿—?3~ìHüáU?éS®çc¸Â»™dH‰V#€Œš~›l¶6„…€U	;K!;½«\npöPóæëÔr{5¼ScÇYˆ;†qõá,RX§f0]Ü†½›ÄÅ°û7Ã€{W’xÁìß`çn2}3^>.nr×¡ô88rÓI?ëÌù«Æ†8ÕÁ\\©Î=ı+Ê5kr<Á€2N+Ú¼md½ö÷ÏÒ¼£\\àŒ`úUÑÑm©­{$ìyŞ¡ÌÜrkO•˜ ğkªÔ-·ÀcÒ¹Û«p$8İ©äÎVVd–x\'§­«EWˆo;œpHÛŠÃµ_-¾n¿Î´£æ6ŠÅN®•$g´åy4y˜Û/š üÊ:­T‘¤·q™Œ°à8ÚOnõ¦—×+·÷˜r²§ÊÃúV¤^9Ô-B¬÷6Ú”xËÔm¿“(ÈãŠµËg¹<óŒ_:_#‰Y—!²9è<›Õ[ë~\ZÔwGwá[Xœ›6öH·gºÜ{ş&´•ğöhƒK\'ŠôÍã–€%ÊƒéÀ>Ÿ§½§ËûxCY_ğÿ\03Ïš\"™ç§jh-—\'×5ŞÍàŸÍ`ñş¯fàİÉÓ!G¥D~èÎÃÉø—¦m¹°’2O½B¢Òÿ\0‡4u£?İz?ò9>`H8õa”®J{WXŸ\nôøa%ş%èÃ\"lÎŸÃİH3|PÑö¯$ÅhÍ‘ùÓåvĞÚ-%¯äÿ\0Èåaf”cúÕ¤Bª+¢‹Ã~	³,n~)Bèxÿ\0EÒçÏùÅ5î¾iù3xÓÄZƒ¶ºkÆ_ï\'ùâ²t”¶fR«÷~‰ş¦ÀK\Ztw6ûYd–5ÀÏ\r“ŠÕ‰¿	l²m<â_\\§İûp(§õéø:’Ûöˆ–Ñ¼1ğ‹DÓ&QòÏ¨J>AïëëW\nkV5‰RÖ0‡ùßğ Ğô›İfEM;KÔ/òÀfÚÕÜ|Œwÿ\0#>¢ü\rñ]ä+-İµ®…h^MFuVè3=§>mñßãF¼#H5­7Ã¶ì\0dÓ-Fäë÷KgÛß‡<½ÿ\0„uÏÌÓx·Æ:¾¼Ï¶iHñ³óëyaM§uùœòuªs$”WÏõ±îº¢ü!ğH|YãTñ%Ò›NÑÆà9BIäÉçÜæ•×íuz¶LømàÈ4»4ùc¼Ô8ÉË`w\'õ%¹ãw•è>Ğ´,¬Q8.7¤õ?SùšèM¼q+túâ”jEŞÉ4õ¨î·µÿ\0MoÄ±ø‡â=ÏÛ|q¯\\kl¤”µe¼yÎpƒë{qêNìÁ§¥ïÄı9cA[Hcu³»Ëõ§Í±÷(8$ã&º_ÙGJ‚_%ä\'y{\'Xúsúcñì¡\'96ö<ìMéû«cî]8ƒ”å&\0éÎ+¨±‡-ÓŠç\"·’\'‘ï&@Û\\{ô®»I_5‡)æ±ø£¹ÖæŠå ÇsÖ³îg(ùÀQùUË¹6ğ8Àí\\ö½såÛVå zsU¾ˆˆ³îS5Äz“ÔÕrvñŞœoJ‰IİŠ9mğ„¤šimûÆ¤B;ñšEl&?ŠŸ‡ræ­EnBÓH@tâ¥Q€@9SÚ¢EäãŒõ§ì8Æî>”¬–ƒW[±²89Q×½KkbTıëP…Œu=kFİD1·õ¦¢–¦?nÃ&“\nFp=«.i2š·3à1¬ÙäÊ–¥Úû–Ÿ*)O*… }ìõ¬ÉŸ’\0çÖ¬ÜJHßjË¹ŸjœEãµÈék¯çÚÆHõ®nö^­ûß7*ÏsÖ¹ëë¢€ò1ë\ZWïqü.ç-âÃ˜Zó»QmQÜ°İëšìü]¬A\r´ÆI”1‚GzùËÆ9{[‰¢µo0ƒ‚{W,gi5Ôy´:•*Õ¸(üj²÷«6á”Gõİw(•:\Zcæµu\'€+;E»7)ş&TÛ£\"¬}¹ŠÅ˜?ö’lÎsŠÚ„÷FiJí¾§İ³*Ç`a!ò]öü§€ÔWÕvo¹ä	õ¯‰¾k3Oa`QÙ%·!›’23ŸÎ¾ÏÓnÖñ:¶C(5æÍ56ÙèÔÖ)§¡º˜Ëcñ§†#¡ÅU‰Ær9§ß•$sZEÙYœMs‘LfvƒÍ@·\0{zI&\'p}kE2XùcŠ¡/ÈNjÕWFI<×6Qº9xÃ,ŒcD±Ô”´@¬GĞ‘ÅxgŒ¿dÏ_Ï5Î•>£áéÛ$>›>Ğ2rp=Æ~¤ÿ\0y³ô•Â|¹À¬;¸BàÜ¤}áX9ÊIıç];Zïä|­?Àßød³h_/g…:A©À²çÓ-QI}ñ³Ã‘Ö¾ñkêLRŸoóùWÑZ”~[20$\0HãµsWĞ«PÜ+â§²ŸÈëä¼R_}—ù\Zÿ\0\Züi¦Gÿ\0o†By¶S±í×îão¦k¯íáü2êŸµkW=|•ßşëwv?1 {ŒÖ$º{[åT£ ê*~¶“Öåø%Ãï;É¯FÑÃCñûáöÁ#è>!²lr>ÍŸÓ<Ô±|Zøi:oÛâwr3jÙú×Fö¹-½VT=¤PÇõ¬é´[yC‡‚2§¶Áş¾³Iï~D<<¥ª›ûÌáñ7á‹­¨kØÏ\0Ú¾ïı´aø¹ğêÌ£G6¿#À.¥]°ğı–×-iãĞùb­éÚpß}¤.x!\0ÅWÖ(u‹ü	†£MJnŞ¦|_\Z¼!\'ìŞ$œ‘Ón<TÉñëCXÈ²ğŸˆ¯;\"Éüë©¶Š)hf9\n3ZK$qŸ,…Ç°Mü0ÓåşC†RÑÍıÿ\0ğ)¾9ø¦à0Ò¾\Z>ÁÑ¯®[ß°LUë/\ZüfÕf	m¢h:R‡{)íœŸ_n+¦µÔÙ®	gbÊ9]ÜVå¬èß¼úµ1Çr¾XÓ­¿àT°;»ú«şw97áßÅŒkßŞÂ\rÇziH‹ÆxÁ\n=û¾Ç=÷‡?f?$w­\\j\Zô¬q¨\\FÏQ¸í‚z}Nz?İ)µñ¹”rI÷8®×M™X‘]ôq¨ù¶ôĞòêÅÒÖ;ßgòáïè~ŒG¥ivÖJŠ0>½}kv ‚RÙÎÑRO95ÙÌåw\'vy²½õ*ê,LLªyéXÖ\Z`F ·R+Níÿ\0xG­®½sM)3®p…—R{F çPÚHĞ•PŞÄÖÒ¨ëŞ©ê0#E»•`xeëVéó+˜ÓÄ@¼T|ÀsÚ¼›^Q2ã+·œ\ZõoY& çwJó/å„›†#·Jù|L’¨Õ®ÂYAã\r5Qçˆ¨Ü~d÷¼“Ä$R1ë^åâë…ÚìÃp	ëù×‹xŠ}ï)^Xštçwc¢¢RW{¡i‚}k˜º‡÷¬:W]tLÙÏ«şÜ¹bz—+±äÍin†(C“·©«6íœƒÚ– ö¤Š<>GOåZ«4d¢’q/”İÇ|\ZÏ‘7}*ÚÏ±H\'j†eO9©WW%µkÈ˜†_z³\n(gËşéÇò¨Ğ9¦H‰\\gŠ¾g°F*jÅÈµ+ˆ2O$xàcK·zşçãïçüôªŒ1Û4¶Ğ©Èè*\\´îe*0jÖ×ĞÑMBñ³ºîyPŒÍÁ•,·RJ§s‘˜æ³d!s¶­#á½BæJè¸Q†ö	d\03qØ\n‘\'b¨¢*2\Z¬[…Y0Gÿ\0^±³¾†´c™<vQ¨èúTæ1ØsÚœƒpùG-½³nÉã(rwîZŠ¾ˆ[x1’z/5}~e®AÉÅ>‚\rV¯dEœ·CÓ<ûS&—*İÀ§<Ÿ/9oÇ­P¹‘°à\nÖ7kC)A«´Q¼ã‚VÊ) µí?±·‚¥¶Ö..äÄ­išEáwÈr@ôÀş‰ñY¡–T‘auY1ò–è½}Yû6ëZO…üÑİ—[†Ş²©9c_ò;©Z1“<,C¼”?á¢b·ó	*2sŞº=:!±cÀÇï^bŸôK6æ;¦^ ªõ©÷?ôæP¶öê7Äâ….‰¨Üô‰À.Y—Èj7fêêFİòô\\öÈß|dx$O°¤!úbLçñ®f‰ª·Ù¢ïœçó©‚•ØEE«·cÒ‚©ãŠF1éŠñÛŸ‹´m©[ÅìŒ}xÍU‰òl$kYçƒ…iÔ¶Šàà—MpI‘ˆ`q×4ÿ\0=UK3¢êY€¯Ÿ$ø’fMíË(8çô¬Ù<g5ŞY,5†p‰°:iMnˆŠmİè}&­fœµÌ@¸9ªw>+Ó ÎûØÂvaÈ5à÷:õôaĞï\Z#ÔÊ1UuÛ/ÜZéNe*1ó¸õ<úûè_³mÚäocß?ádx~Õ—Ì½ ÁsúŠ£¨ügĞ‚ÉäË+•?pFx}ŸÂ¯ˆÌÜL‘D„g¨¥Ecğ;ÆºÛ4ÒêZ\0J}æı?ÏêtT½Şu÷4“’G©_|w±ZÈıÈ~3íšæo~>°.‘YE^A/»\'ëÚ°ÇìÏ«ËŸ´øšePpv(U÷©_öd±•¸Öo$şaş\n•8ï+³8Ê-İ\\ÌÕ¾>İ*2ìµŒöi$é\\¦§ñÛS¸Y\0Ô£EA“å&Ü®k·_Ù§Âq\'7wä%ç?†)Ãà/ƒ­Ó¼ÑĞùÄ¶ZQ…]nRÑ5¯àx©ñƒR»Üµ.ÀÆRM£¯\\f¸İOâ4÷LÁ¥¸©ÁÌIıké—øcá»alœu½eê:¤Àó>\0ä¸Èü(Ÿ²„nÓ3Œ¤¤Ÿê|³wâ;«ˆeuŠmÍÿ\0=w=³\\­ù¸±åã•ê~4»†æúS\nª	\0Ü×wƒ+:v’æµ‹^ìô»q´qÚ¦VUõZ:Õ²€GÉù—µm¬•Î˜İËSCN‹Íç¨íXºçú%çš£§;}Oa[Vs¬qœœUmZÊ=BÑûÀåH§Eİ•«zGşÎ{†›-Ì`JËlzœóùWØÕ¡¡[H£i¯ƒ¿gFM=u+uuó6¥›$¸úÿ\0ã_^|ñÛ­ï`c´«çƒßÛüÿ\0rW·]ÏJ/\rÉƒË \Z•á…Q·—tcØïVa0Ígts(è<¿¥*6G=ª7£†CŒôªnÚ\r$Ö…ªªÇ àGšÌô„€¤÷­#µÌ(Mœ\re]î\nØ¸õ­µ\0£©î+:âÜÄA¬\'Üì¤ÖÇ;¨[	\0\'\'·5Ï\\Û,¥r3Ò»;›5u!²ËŞ±o¬‚d§®)GCº¾›]å‹,™p>üÖeæŸ…İ{]ÙD½+îĞa·p\rbÒŒNªmsYœ¤–3‘TŞËwInÀ×_ı”;ù¬û‹ ÌËœÄTèŞ†‹I5ùPD¾H-V6Ş`Ò‘·Œã5jxşÎá›<uQüU™vVËò“Åa%Ë¹ºÓM\Z`Ü‘Æj#¨mÊƒ•õ¬¸ïÜÈÀíUg•‚’\regÜºp³¹¹iv‹\"«7ÎÇø»Öö›>äxÉ ©Æ3Íp–ó†HÉ‚:Öõ†£®ÍÄÓO•¶tI;hQÒµ\0“åùOzô6O.äó’z{W‹hš°GË8òØ€=c^‘áû–‘Ñ¥—xÀOJé£Q¦yXš:ºHÊ äã¾)LøRÒ¨[\\$m£¡5y i:W¹M¹#ÂqQÜÙ™†îİ«>Ç¥Bmİ_=¿‘«ñç ÒI¦)5cEzUMLjÀU”àéŞ©ê<¦\\óÊº¯hÜå¦½äy‰ui¾İ,1¡îUÈäŸ_óşOâÂä|µè\"†#u$¨¹sœqÀ¯:ñÖšd `Œ‚}1_#YsTrGÛRÕ&••ñ£dÆ8\'µã^#a¬Èö¯gñˆUPØ/Œ`WŒjğù¡Á] qïJŞ¼¶*«ÓS»æCƒÍdİ½ëZôr:õFhSÉ\'ô¯V>òº8å«­rêQ¬sQ}´*sŠƒX”Ääô¬¶³¹ÁâºRMjq¹ivt‘İ‡Ï9ÅJ—K&@9õ\rÁPÙcšÊ^H¥e­‰Ñ6Ù»§ÖŸ\ZüÙ5WósÏµ[µ©æ¢/¡¬UİÉ’%*r»©LJ£ sB³n =jÕ¼;òı«5¦ì¦µ¹R+Q#r1VÖÓ„ş5f(ÂğLÉ€@ªRº+áWHÍlôÆ*Ô1ª¨8æ¤Hä÷«6Ğ†ÇœQ‚Itl6¼qVÕ×ÛÅW•Jğ8¥U…IàT?‹BZwvd¢Læšó¹SÏÒ¢€_>Ô;RÃ¡í[F\nJè—~[ w\n¦ò˜~µ)“*qÆ*”Ë3}ÑéU\rì™Ï95¡Ñx\'Ã7.Õ¤´°„Êa*eçÙÿ\0<vÅ{õŸÃÏØÙCooiek\0‹qaêsÆNhı“<&ÃM®Ê»¤»•}Ğ§Ÿóøõ¯¥¬,T…ÊÓÕèÇİ[&x3›”Üº#çà‡µë§iµ‘§ÛF>`ãÓ=±×ÿ\0¬9ÖÔgı[WÔ>Íq¬ÜÚÚÆ ï„…İ×9ãŸóÓœı$È¶–Ì¡F[­`ê·BŞ	67túÖnwÙXærwÑÀ{+\Zu½JóËàùÒ“O»ø3¤ÜËøÄKÉçÜ×¥HÁ¤b;šnFq“Ÿ¥Z½´v%Ù«3Ït¿‚^µ™¤›L†c7d×MiğûÃÖü®“ÇªÖôxİÈÍOÜçÛ­iï5¹)tF}¿†t»rÅ4ûucßËéøV„60FIX£8 â¥[-ƒ¶œÛqÇ_J—®†±iîˆÒ2WjaŠ’ßO‰ÙšHÒEÆG&–ÈÏ&­²ˆ£m§h“JÚÜÏYGMˆ§>fW j¡ ã`áGJ°ÓòßÎ©Í&qM-n-×)RåğNH¬ë‰0¿Zµq(9üûV]Ì˜,3‘éCŠ@¢¡±BöNO¥a]Üg+Úµ.™J7=kåÆòúÔòédDUôZ×Ó|­“^=ñ?ÅÚ@7ñ† ñßü+»ñ·‰E°‘³‰pdãÖ¾yñ®×—2»u$šçšu_\"zu:£/#šÔîŒ¬ìOÌOZçn%*ÅGJÕ¿o™¹ç5ƒy0,GjÙ.]äô=VÔ…‘õ¡Ü t¬;;‘\"ğk^ÏÓºv=y\"ÂpA=*í¢¤ÈI$U8òAôû\"QJª‹ÖÌÑ|:‡ğ±…·‰á	*¡’6R`{_U|\"Ôÿ\0°õ‡³»VI$;•¿…î+å/„rËãí?²¿ByÀ?ç½}Q<o£êºt«–Š<6à@Ğ{óéJqæĞè‡»Ë®çĞv/«»¨Íi ÚIÍh«}¦[Ìœ\r¿•oZK€Aæ¼ø+hÈiD³ùâ›a8ı¸Ï)æÎ9Åt­‚è]½x¦<a—ÿ\0jB<Šh-rª Ul;ÕiT2“Ş®m[=MUd%ê—5\":jgÊ\0äÖ³¯-Ê Œç[rA•<U‡oÈã$æ¹äº3¶œ“G9-¦ÂÜsY7VVcÓı+¨•C;¾œÖ|¶ä1®U\rN¸>WsHâp%y#¾3X—V¬®ÅHhÉÈö®¹í„İ@İIî+œ¿Y¶ƒÉ¬g§Âo%ï#ë÷€’¿0ãò®vëir õ­Ùä# 8É<W7|K³àu®}T¬Îê:nS’u/*„÷ê…;JI˜¨#Ó­f]?-»¿z%f®¨lîhñ$òM\\¶ÔØMœ¸ÁúW&÷K°Ù¢‹WUb2\nÇgch_äz~—«˜îwü®@Èì}kÚ|\Z~Ñom$u-Û¥|Ááûÿ\0µjPŒîËp‡¡úşõ]Ñ\n)N@5½ßcÏÆİFÑ;ë2ª£#‘W\Zõ‡Ê0gÀ§nHÁ52Kğ}+Ü„¹U‘ó2Š¾¥¿4ºóÉ§À9>´ÛhKg â¬¬{r\0Ål“‘ÊÚZ\"A\'Ë‘ŒÖF¨ß»“œÖŸ¼géXú‹ïY­*’å‹*Š÷´<û_•ì@$¨ÎáÓ½y‰ïw»åˆèş\"•–9€b+Ê5éŠJË »×ÌKF}…¹n·<÷ÅAe•˜˜õ?Ê¼—\\‰–Y†Üšô?êèn&p`&¸=mŒ°9>µP”^¬ÊJZ¾çuy­š©yeˆ\nÕ»ˆùŒ¨ëš~QíŒy«¾œÖı%tïĞóMb=Á†:W4öá_¯N™¯BÕìXc ×)5Ùå–º\\µÓcQw×S/Ë ¢ˆdd$zV˜µù6í#Ú¨Ü@ab@È5qnÚ‰E+¶liì\nÍÒ¶ ƒšæôÙ›ıšèl¤fíš†l›Z½`È9éV­~áThÙ]¡rjT[¨¬Z´‡	5\'Øš8÷´a©Àø#Ÿ	*ß1â¥u$dsjW¾…§)-t\"DËp â¬Ç¹ÍCn¹$õíVFM8\'ª%h†¢\rÇ´âE=HØ~\\‘Ş«»|Ü”ã\rnD¥¥Ó	¯úÔ{ÎÒİ¡Û9\'“Q³aH“T“[ìdİõcÃ5V¼ˆ¼,ªˆUTêI8Àÿ\0\'èzË)RÀ5u	43âo‰\Z%–‘Ã!eİPHÏ§8üÿ\0>ªæ•Î\ZÒQMËKg|%ğğğÿ\0‚t«\0>hbÏ«w?‰Íz^›¬W;{V‹f¶ğª (ª1Šéí”[Û Zímjx]\ZAwr2rr{Jå5û•2˜ƒr§$kröçË†IËĞWs1’Vn›SX¥Ì>[\0Oz‰.ØjU<ö\"¶ébI£MÚsŒÔ\"\\|¸â„˜wª±.-r–¼Îr=i¨ü§jpPgŠ’Á>Õ=Ñ-Å\"åšˆòíÎ;SfŸvN=ñA`ƒãŠ«=È\n@ãñ«²±ãb)d\0·<Õ	¥äŸá©%•U°÷¬éæÜ­Gó©Nú!_]nn àµ›q*•aº¦šMªØæ²nå<ÿ\0:RŞÄİ-Ê—sF3“X\Z½ê[BìçkJös\Z±\'‘^Cñ;Å¬-ä¶‹h\\üÀYÎ|«MÍb¹¢q>=ñLš¾£,Šø€pzœŸóÅyµôû™€=kOUÔ\ZBÌq˜®fêá¹ üÕ;E[©wæÑ/%òËwV%Ón&®^N[±5‹5Á[5¢}I²‹³;íZ!Ëô®–ÛW‡z¼ŞÂå¼WC¥âló×Ş­ÇVÛĞôamÙÙA­F»Ñ¤®Ù Öm®šp9äÖÍ¶šˆœÑt•‰Uc%dz·ìó¯Ùéßì%ÔY ÏlsÛ¯ë;ıq®LÓİ!B²Gæ”p@çõ+á=ò;\"¯	$d26q‚3‚\r}7ğwâiñŞŠĞÜLQÓÎÇÉÃØş_çŠ—³—;z…%ÏİHøãıX\nF0ñ]u¤¸Êö¯\'øâE’øÙÜ‚pp	û­^£oÁ$+¿záQ#N&8ëòÔµ¹H,Cç+ØWL^¶9Öˆq@	÷¤<çµ8Œ\ZJ±ÙròŒq»Ò dÚ7c+V1ÏJŸäù*¢ÊµÑ]ÕNâ Ä“ÔV‡¼tªÎ3\"²·C(;3!íBHqĞş•Vh@qÏz×x·g›we#vÓŸZæqG¡ucšÕ# 3!8T×?{>P…\\¸ç“Šé/x1€+à+	cwc\\óVÑ´Şš­>øo÷{W?©0\0í\'Ğê“şñ„ƒ´nï\\ÅÙó7ÃŒ×\"Ñ¶Î¸=vaİL0ëYo¹ç‘ZäG»OJÂ»¹v¨P*\"•›:`Ò)]\\ùJÀôïXs]Ÿ0ÕéK±MgÉæ$šˆÛ™ĞvßS©ğeâ¸¤ “õÿ\0?}ğ¶u¥Á.1¹Gñ&›*ÛÏ‚‚@NïN•÷ŸÁ»?+ÁzlŒ2ÒF¸=?JëÃÅór^>n\\Ÿ]â-?‚qÇj–;5N§59p:š„İ(ïŠú£|w4äL«´b£•Â8¨d¾\0ñYW:’Y²{b³XÅn]:R“.\\İa<Ö%ÅÈ•eËmÀ¬ıC[XÃ“Û5u«–	eô9â¼Šµù›HõéašW0¼_t˜—kärœ:òŸ}ö!ÏBk±ñ%à2“€t9í\\£t®ÏŠò®å©îErÁjy–½¤7Û¤œ|ÈNzô®nîØ3óÛÒ½WÃ=\0ô®+Pp•yÍk~‚srÜäu+—\n8®fPñJÜåk¯Ô[÷m”×1<`–\rÖºé%k•ÕŠ&´#9ÿ\0f²gÑ‘ˆQ´÷­èãP;w«v¶‹0$ó“šÙN1ÒâQVægÚ+î>•}¥|1^¨4„xøE úqYW¾[ãN5ĞÍÇ[WmE!\\cœgÖ·ôÒpFsUõ}<Y^·S1SéãsZ¿‹Q-4fÍ™=zƒVÖ\"ÄœñQÚÇˆÀuh[Ã°95œcÌµ4Në–Åx¡rùªhâ‘^=Z†0Ip;TñC´µ?ĞqŠë±Z(Xƒ¾µ#Æª0JkHÈXg5\rÔ¡“\0Ö‰·¤Lå®‹©\"áA^«P8)mØ• ö©\0W,¹\0÷­Væn*Ú½A<ÔmÑœæ§hvó÷©&®ÜÓ”Ny¥©U“xùz\Z÷ÏÙ#Ã ®µ®H	i]!B=?Ï\'Á\"6ÁÃ1\n¹8Î¾Íø\rá¤Ğ<\r§Ú“‰[,rMváÛŒdÙåâe¢‹={HfŞr:VÔÒ\0˜=«3K‹ËŒ”·7*ˆäŸ”vÅi/#Í[\\Ê×¯”«Dø¬!)¯—×‹ss#îÏÍW©ö¢v-k¹*›å5<M€AªÑyÎjd*ªôêE¢¶,)Ûß…:2rqš®ß9Âò*º¨l¸ qG6–fiëk7€3Ş®Z®3\'¥Qƒ÷„qW\Z`±íÎš²’oP–@Ä€j¤¬~`9ô¦I1åªÒÏ•#¢ÔFäéªd:å°k6yù=Çjši·g³.fÆşx[]\'hèA<Ãæ\0çšÌºœA\'Ö5Æ	>µ“ªêvúm¬“ÎûFpIö¢éjÂ\Z¤¬sŞ6ñhÚdÏ¸™ˆÂ¨ç>¿•|áâI®®šC#Ë“Şºßx¹µ›ùß\"±TPxü»Wœj9gÜx®zpæ•îkË¢3îe<÷¬KÉ0¬3V.f,_šÄ»¸ÁqÖºyz¢âìÙVòàa†zÖ-äÁr3V.®v“ÜÖ5ÅÂ	¨H›İ=‰Ë`sÚº-2óìò.xûµçšf±,J§¦{×tƒÌd‚:Vé_IÒ’Oİ=MœI°ç\"µo?-qŞÔwÇå?QĞûW_›ãëšË•üÈIÅ‚œ{ÕÏ\nx¦ãÂzÔW–·	T•b§=­eÌì™Á¬fßtTôÇz‰$áfjª´ïsíÿ\0…×Y¾nB‰”©:Œñş~¿LıUi1xD|†PA¯Íÿ\0ƒº³ÛßZå·”nr=ùÿ\0ëşƒøT\Z¯‡­gÜ§r·æJ×Ğô\\¹à¥Øê­›}H«ñ9&³#%0@­É+•çŠŞ¡ËÜ{2míJ«œÒÿ\0g»â•>ín%¢\ZW’:Ô+vcS1É£aô¦™i‘Q!*ÏZ†xöÀ\0=*TûÔã÷Z©®†QøYFXBäõ•}Ğrwqš×¾ßZÌ»ÁÓ5„´V:(¶™Ëê•oá¹çh¤gq´“­uº†LM“ƒk•Ô’9‡—Ş¸*;3Ô¦rº¸óXó:W-¨Ê)äûWK¨†*øê:û×+¨DZ.}k‘ö;)òÙõüÂP@lø¬+Œ~ø5~ır[å¬)e`ÄÕ\nËDtÓ¶©ç”£œ7J®x˜Æ¥Ió31¨•ÌfìiòÛÔë¥¦¢H³‘@cÇ¼şUú%ğñĞø;I(0­kú\nü÷‚ÜùÈÜ¸Èë_m|ñ4ZÇÃ=&E|´yL;ä?§ÿ\0\\õ®Ê5Ÿß÷œ”\\ğéuOúıF¾¿),sŠæ/|oil¼¨:±#¹Ïx™í¢p„ã\'==«áÏÚOÇÚî¸Òi:uì¶–ØÌÂÁ`zşŸ†Â®*s—-#,.Z¥iŸ\\x¿ö§ğ\'ƒšc«x›OµÙ÷£óÃ8öÚ9¯?·¿Â«¯)|a\Z“Àg·/ç·üñ_›7>{©e5Äw3»fëÉõêï£êsß\r¯nKí¢>»Ğb·%ûÉ›ÏJ\ZSƒù¿øëf…ñWÃ4„Ë¢ø‹OÕ##!a¹B,ç¸­k‹¿İîç°æ¿1>ü½‹^Šğí‘Ã+\"mç#¿_Ïùd7İ7\Z-‚Ås¨IvÀÄ­œcŞ±«N0ºŒ®CŒZ÷^OúêokÓ»‰\0nEq7’…İıêë7‹å`¹mÕÄøŠG´2 ãßø±\\KGËÔ˜¹IµÔÀÕ&\r¸g5ËŞ[Œ1ëJĞ¹¸gnµ™ªİE§ÚË4ò,q§1ë]+a+Ó–‡;ª¤a[,ú’\0å^,ø¥á¿\r\\I\rÅádÎøí×qSØŸoZÒñv³q«´¨c¶äº×kiİ£nç×¯ç]´iGW&sÔ¨Ò´¿­ñ÷Y»×G²†Æ.ÓN7È} ÿ\0>Õ•ñGÇ2\\ï]nGV<£Â¥•X±ğ\0†\\şÒè~	‰@TwµÖãE/‡ï0‚œŸ¾ÏZøMâÍCÄ°:jVñùÈ>YSøğ3œvÿ\0>Ä÷ú–•Û³>õr~zUš$qª\0\ZŸÆ_´ıN‘]×v6Xû\nñªI¹û§dck·¢<ÏÆ’G¤cGŞG8=¿Î*¦’C0ÏµÎÏªÍ¨ÜKq1GmßAØV“xP€zP,,÷9œ®ÏAÓÕR3šµ\0RÄ\ZÉÒ®ˆ2xÅlZ.AÅrÊüÚ•·,T\\‘ÅB£ilU¼áHª²H»ËÏ­8¶^·» Ál®*6M¹R*]ÛAÒıÓ[&¯¡²!M¢2Aà{P¸õúÒ)?0ûÄS¢U’1í[-Ù”»\\%M©œçUÀ?Z±+¶\0Ïë=²¯“ÍRæÚFUš[›şÑ¿·ü]¤XmÜ0‘óÓjòsê8ÇãÏ¿Üşµ[{xáNp8é_+~ÍºC_ø†óQ‘x¶ıÚ±Œœ{ÿ\0â~·Ñ`ò¶“ó;\Zôl“GÏ×n¤œ¢ôFğs;r}sXºÕàŠU;™¸æ­]]H\'€;×%«_®XÈVqøµ0W[İ¹˜ÓbrXŸJª_,qÔT±Ë·‚2Mo/\"ZÜº´àáFjª¸\'ƒÍ*1]ÃvO½f®•‰WnëRÈ9ÎzÒä¦ª$¹ÈéRÛ9wù‡Ş®:»WMÜÓ„€‡<\ZS&àpr\rW–P€€sëUšAÏ<Ô(½È‹—RI&ùORYJ£sQ´ä‘Ö©ÏtÜŒşN÷Ôq²Wk¹O¥eÍ(ùÈÀ©n.2OÒ²/nÈËcÛ­TR{…õ »Ÿib8÷5åüb°ÿ\0 Ã*É!ûØì+±ñ‰£Ò4Ù#Í+‘í_:ëÚ³İO4¯–g$’z×<š›ågLRJıLíRõìœäğkš¿—%ƒ6=êıÍĞ*NqX·a‰­cdŸ)	.WrÓıó:VÔ£,«wwDçÂ°¯®FÖ\'¥JwÑ;İ•/J‚Äk\Zâ@œÕ‰îİÏ=«2æBXœÑª\ZŠØ×½­ç-Œèk­ğ¶ ·ví#Ì^3Y—¶¢æÙ]ÍŠw…ô«›KÏ4¡ÇNOQ]¶¼/}Q´S•âÖ§g¦]9ÁÈ\0õŞi÷be5ÃGhd`Ç‚+£Ò™£@¡²+´õLÖ×^gFemÙÅs®Vé™El[«în*Õ®—Í¹€ÀíSk¢W»Òæ·u«­9âx	“Gùÿ\0&¿B¾kßÚ>‰Ÿ&@ãŒdšø;ÃštvÒÆX¿Zúûö}ÔAàßÃäàŸâ®	Á$Îú;;F ÊŸCW-e=­fØÌ¯\0şnÄŒ;w5z“$õFCjE¨!œ/©úWNÆw¸Ü»­.ĞÇšZEP·0©šzRäôÉ†bn¹ö§±§B«É¹\\ÖDàüüí=h`… Õ[„Ş¤£õ¬f½ÖT4¹ÉêŠŞs¹ ı+›Õ0»ùãÖºíF1“ôÅr\Z¬{·/¨À®+îzP÷¬Î7R“¹È®bì†è+©¿¶vß¸3\\åäN85ÊÎèÆ+DqZË.»pÀË^ÌÊşõÔøQ¤}œ×%ör×\r‘Æª1Û•›S|¾é$qæ2ÀTğX4ÀñZ:IŒŒšél´vdu¦‘J­ãîœhÓd°2=…zÿ\0Àİzã@šâÑ¾Ç1Ì‘“ÀcÎáïş}Î=·„7çv\\¿¥u>ğÑÓKH#bAÇŠ¨ŞÍivW´½7ïøÿ\0Lè<k<“™~bU†é_>xÃÁ¢öòyŞÙÎßlŸóŸ¥€×öÏWIùY?á^âOj6-™­ƒ!:tÏôÿ\0?r£(ü:x|dT\\[±àÿ\0bóôN=jY|?²}Å“æQu®êM\ZìanQyÁ$céY±o†ä¬  ÎÏSşqW%¹U$¥+&3J‚=s\noZ¹q­—\\±Àôé/íL€¥ˆÇ­a:‰U¤ÁV8g¡¤à›mîaEï\Zºgn´ë¶1²Ï`qúƒZ:ö¤š„FEp®T¿JàçalÕTx€ª:†95„áÖ/S)ÇŞ\Zêúµ½‚ÈÎØÚy¯\'ñg‹%Õ§-—•äEuš²›ùH#v9×+«è[‘†?\ZºP’v“9Ütiœ}Î¢²Zñºš—YÓ^ŞYd¢°^7L·~ø¯V	Z÷9_»¥€ê+`õ©­|K\n.âTë\\˜–G¤Ô~K”n:U¨+Y„d¢u—ß$·\r«6qÉí\\uİıÆ£reÌ®	+»ø~”Ô„“À©’Ü“ÅJ¥³šSoQm·\0IëÒ·4ß—â²b‹`ÁÆ_·—o8â©¥+8¥©×iwesšèlfÜÅ³\\Nz#aÅu7À$â¸åsHÏ[œ\Z3ÓÕY0HäÕ9nDNìæ¡IÙĞóšˆ•{]´[iÀ$f”JYN8ªfbOCúTœ²®RK«3wÔy—€£yÆÁ¤£‡¥9Á8ô®¸®]YšIÇ˜o™øãß­QRwtÅXvÆ}=jÜÈ‘s¨¼ÖĞƒr9\\šO˜úgöyğûhşG‘BÍ1,~§úãë^óe7—ÉäŠóÿ\0‡¶Úh£<úv®ÖIÊÆ@ş]{+õ»ê7Q¼A)İ‚F®aå.Kt\'µM¬ß(ŒÌ98íY¢L¼ûÕS¶ì‰Ï¢EÕääñO2)ïT#|V#`Q¸ëúU-X4ŞÚ–‘ÊŠ“U7‘Æï”ö¤KŒSKMŒ“wåEÅ\'<uõ«ÖãË‹$õ¬Ë2ïAW$¹%qŞÁÉò“Is··ëUvÉçôªÍ?r*	eï•-[VLŸ+&\nÄõÒ©]NCûÔR\\\0§½g\\\\@<ÑêTc¦¢Ü]|¤ä÷¬mCPŞŞI$}±¨ËKqs¿<ûq^añ+ÅÉoØÛ¾ç`DŒİJÉÉ$Ñk]Î;ÇŞ-—UÔ®XJÆvÇ8\0w¯:¼¼ß»-øU»ûÍÛ²ÅÉêIÍs×sN\rT ’Óqï±\rİÙ;ˆ5…yp\0 j{‹¤œ{â±îç\rš»[aèİŠ·w!wŠÆ¸¸Ü¯œcûÆ¦º˜·ç<šÉ¹›p>•6{»hT¹õ5—q19çŠ³q(;«*îu\nÔ1«Ïg\nÈÜlZ…^‚²md\nr\ri[6åİŞ…©×}nkÂ¥ÇL}+RÒ2¼æ±¬¤È œ`Ö¬.»pN)Æ(¨ÜÛµPW•³cˆ²:šç¬dc5³m.9Í\\P”u»:­\"ëk†¯ ¾kÛu˜P¶È˜m\'=[#üÿ\0~nÒåúf½Ká¬Ú~¯ÁK®Húúÿ\0Ÿñåª›ƒ7ÂÉór³îíà<AG<u­E8<W-áÛßµZÄè3•mô®ª&¡…y°—FtOCNÑòõæ¬Vu¿İ«k?÷¿1]±Ö79om	¨#9¢Šhc€Æ*/¼¯ïR`†ãÖ›Û°*ÑVÔ£,x%Ú©Éè8ªûDX¹ãhªR¦23‘ïYOsH;œæ¥„‰ˆàÍqº‹8,[rHÅvúµ¾a‘Aê=9®ZşÛrsŠóç4=\nR¶ç#|<İÒÇ¥r:ÂüÇ9QŸÏüâ»-E£·BOs·Šä5iVæbª¤’{z×4»Q¼]ÑÄjĞïâ²ìtÆ–Q…Ç<Ÿjêï4w–\\@<gwNÑâˆâ4 ÿ\0õ4SÑY›·\'\"=DIa@á\0nõÓYi,×\r\Z•z°íVôm\'¹F2+¦µ±ÿ\0G\\/=ø®ˆ¨ÛRodT³Ñ£XU±¹Ët=…t:6—‡àç8qÛÒ’ÊĞ*$÷®ƒL€¡;†[“éD4ÔÆSåV‰~ÆÕ&i6[ğô©o4›y¡kgEd#aV,á0Ò(ÇÖ®C’2ì2Xtô®¨ìqJ¢½ÎXğ-›ò¢Ú„rã\'ÔW?Ãx®dœ414€td\"½ªRvğÔöJ+xï?\Zå”mFé‘D¡ÍcHâ\'™â7ş‰#(ÃÊÇµp:Ï‡şËopÒlÏA×“Í{ö­hPXÆóÎyÚ+Êüi$v—wl¦UŠŒ3XNKÌÑU“vlğ¯@ñ+áºw®=Yá‘ù?S]î½	\r,c•Üsüë…¿•C²çw5ÇÉ”*sGBÔP€nàu¨ol”Û‡5¡ ¯©Z¿„*J¸Êâµå³±”ªµ+Hòé¹m@Ojâ¯lJ“í^ƒ­¶n¥â¸ÍF@²0ï+xk±Œ¥)l`,;sÇ4ÓzÕ‰r¬Hnµœ¹#=+ĞM³†ín2HT+TP¸!€ÍM+†‰ojË·vÜùÈ ñPÒa+7tk\"sO\0ÅUßÁ§+’ÇnMBm!6»š6lDƒšé4éÊ!9æ¹[MÀüş¼Ö½œåFké &ÑÑ‡2¯\'Šµpêk\"Şáš2zj¹k!Ürk8İlt¹{¥Â€´årrŠ`\n;³R.Ğ¹5¤Rİ²o¥Øÿ\0­$¤Æ094¼sL‘¾L¢¶‰›¿BùÖ§ƒtÓ¨ø–ÁeI’;{VCË…8àâ½àfŸöÏ™IÊÄ\'<dšê¢›•®p×j0”Oª<=µÒ#È €«ôÀéVî/Æí»€*šµ€F„ûóÖ²5kğAA†µ»\\Í¼¤s\\™$.z†¢û@$ç-TãqÂü¹õ§	ŠŒgµRíĞ¸µ%æ_I°:í©’~:ò=+(JYúœS•÷‚jöØ¹^†ÚùÁn=@§#Hg	sÜU»Y¾b[¥BWfIëyšq0A¤’ìàæ¨Ét[qã5\\Üeˆ&´³{“Ú[—ÍÖìÜ}*»İ.SUZç`9 š©-Ò¨#<ÖvĞ¹+2{«À8İÅdÜÜ’z‚qL¸¹äôæ²o¯Dq»³ëR£Œ·FŠ¼O§Ìä˜Œ\"“ŒŸJùóWÖe»¸šI@ó‹‘œàÖÿ\0¼Lúô…XˆáWßMyıİÙËFMaºÚ3K»X‚örÀšÄ»»Ú»AéS]]à‘»ŠÃº¸\r¸çÖ·æ{$$ì´Ğê}Ù$ÖEÍÀPyçµ:òá€bMc\\O…#<Ówjä½†\\İd¸Ï5“s>àÃ?I<Ø•™sp\089¤»šÂ7Ü‚âm¡¹â²f”ÈæŸq>ö\'<vª¬ß)£DZ^íq·—yâµlåëøŠçíß>æµ¬%NãëUõ±«VĞÜ‚LsœÖ•´Áœş‡\rÊï tşu¡k.ô§F“¾‡Ee8\n~lûVÍ´ª\0ÏõËYK“œÖİ«äzT?\"×6­Mƒã¡æ»o\n_{èœ0Æàâ¼óNœ(ùtšÚExrÈÆr=)É7éË–IŸxü-ÖEŞ‘¶ÑõêVS‰\"Ü?*ùßà^°¥´áÕÎxü?J÷m&çå<\Zñ>ÊÎù¥cz6ØŞÕeN5J#•<Õˆ\\“¾õÕqÉ#“­8ìv¿\nãœRÆå	ïšë·Td´Ğ™ş_š¢N`ñFæ`ØéD}é%dÍ\"îĞÇ`c!†k6|FjãKœ…üêÁ-ÈÆõ¬¦ÑPæ2u(\0åÈÈÅs·+°9`c¥u\ZŒÍ%¼ƒn[C\\ôñb¥~`y5É;=úJÑ8­RÈ|Á†xçµÏKao•¹æ»}^0V\nƒî+iêKJNN:õâ¹o©×s@æÓKi<Ã‘µFjm6ÁKå“j†ô­äÓö_jµgb7’F1Ó”B/dÊoK\\n™jà.ÑœcĞGfŠ¥p»qÖ«Ú[şóéZ°Â“0~QÔV‘]0r{°³UÜJï?Ê´•ğë‘ƒ>ôÛw9e`œmÖ•“3q“ÀµŠ²ĞQwÜÑVòÛ\nÜp:Óá¸ò”G¶“ĞÕ»—Y	,T\nSÔúÕXµMñ1…†å†SÖ®>LÅ««’kwo\nDÀ$lŒ@¨£Õ\nAå¬†<(Åszî¯9¾‘îaS UWÒ¡»×RîtQ¶8—Aã-U\'wk“™XÃñN¢ÿ\0Ú\ru¤P‡iÃ‘µçZ¾ Òº–Vã§½w^\"Ùu©İË\0ÛQŒ\rpº½‚¢¹W¡5ÏvİÛ4¶ÿ\0‡<ÛÄ°±F‘Hçïsş}+Í®áÛ3däæ½\'Ä¥¡Y7òkÍ5)€˜ñÖ±§ï]3x^Z£¡ğææsÛw­ªiò%³1^HÎk3ÂÒ!àµ×êPyú~U²ê½*¥x±Jó’<G^‰‘¤b01Ç­yö¨\n3f½cÄ–Œ¯\'ËƒŞ¼¯Z÷¯»¡5ÕNVV\n®ıidİë1Õ•›}kWÉR6ƒŠ©pAãŠŞ2º8µùˆ\"êÛNqLKr„äŠT•UH=G%ÒíZZïA9+]\r–ğC(Œr+NÔ‚€µŠa&â+NÚ`±(pV©Ìö/BÊÌGzÒ·*€Ù÷¬{i\0\'ŒÖ•±<“ÍdÓ‘i»6mÚÊ@úv­vR	Ö%»óÁéÚ¯ZÌ¡áÅa(ólmÚÔĞY3m;O®jhfê²*²ºüÀ­O\Z(İ¸wÅm[jU¬·¹c{ $rµÓ….*C0Û·õª“ª`óÍ>mlD®Ş\'<ë^ãû;idÒ¯o]FéeÌn9ã¦?Ïÿ\0^¼æV-½Â/rkêÏ‡:Hğ÷…mbûªP68Ï?¯ÙJ1ló1nñ±ÚÜß­ĞV\rÅßšä–À¢ÿ\0QQ$Ö+\\Ç’MmìyÉ$®h­Ér@lâ”L{7åYK Ï\rœT‰:Çj’f	½/´Ÿï\n<öPNî+8O»8 Šà¼1ô¥e{ãmÙ«í!?7â*ô2yhwV5£ã-sÒ¬µÆÁß(¦½İˆ²“E·¹,dÓÀçveÉ:³0ÎE1¯†6ç\0qYjÍWeé.É\rÉöõªR]uÃ\n¯%À“»\"³\'¿88?…RM IJ7.ÍvNNr?•yßÄ-ŒMkƒ,ìu>ŸJØñˆF“bò¯!S±[¦kÂ|G¬Éä‘å21%‹æ²iÊVF”àÓs(jº‰•İËnÉééX7ySÈãµ>òì8 úV%ÍÊœ®xíÅik+!9XK›¾¹?bİ\\»ksëNº¸ùÛdKp„‘)Û³W6ŒŠâà± k:æqÏ<\nuÔ äY“L»[Ÿ­+ÙX-Ğ†æã!”+&æà¶@?>æà*•›,¼:Ğ•ËØVo¼}*¾ï¼M8¿ß4Ú¦í±´cÕŸÿÙ','2013-08-06');
/*!40000 ALTER TABLE `tabinoutimageinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabinoutrecordinfo`
--

DROP TABLE IF EXISTS `tabinoutrecordinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabinoutrecordinfo` (
  `RecordID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `LocationID` varchar(16) NOT NULL,
  `EnterTime` datetime NOT NULL,
  `LeaveTime` datetime DEFAULT NULL,
  `EnterPlate` varchar(45) DEFAULT NULL,
  `LeavePlate` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`RecordID`,`EnterTime`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8
/*!50100 PARTITION BY LINEAR HASH (MONTH(EnterTime))
PARTITIONS 12 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabinoutrecordinfo`
--

LOCK TABLES `tabinoutrecordinfo` WRITE;
/*!40000 ALTER TABLE `tabinoutrecordinfo` DISABLE KEYS */;
INSERT INTO `tabinoutrecordinfo` VALUES (7,'5101070001001006','2013-08-06 11:37:58','2013-08-06 11:51:41','å·A88888','å·A88888'),(10,'5101070001001007','2013-08-06 11:58:55',NULL,NULL,NULL),(11,'5101070001001006','2013-08-06 12:01:37','2013-08-06 14:55:15',NULL,NULL);
/*!40000 ALTER TABLE `tabinoutrecordinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tablocationhavecarinfo`
--

DROP TABLE IF EXISTS `tablocationhavecarinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tablocationhavecarinfo` (
  `LocationID` varchar(16) NOT NULL COMMENT '510107+0001+001+001\nAdministrativeID+SelfNumber+ReceiverID+DetectorID',
  `EnterTime` datetime NOT NULL,
  `EnterImage` longblob,
  `RecordID` bigint(20) unsigned NOT NULL,
  `LeaveTime` datetime DEFAULT NULL,
  `Prepayment` smallint(6) DEFAULT '0',
  PRIMARY KEY (`LocationID`),
  UNIQUE KEY `StateDataID_UNIQUE` (`LocationID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tablocationhavecarinfo`
--

LOCK TABLES `tablocationhavecarinfo` WRITE;
/*!40000 ALTER TABLE `tablocationhavecarinfo` DISABLE KEYS */;
INSERT INTO `tablocationhavecarinfo` VALUES ('5101070001001006','2013-08-06 12:01:37',NULL,11,'2013-08-06 14:55:15',0),('5101070001001007','2013-08-06 11:58:55',NULL,10,NULL,0);
/*!40000 ALTER TABLE `tablocationhavecarinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabloginfo`
--

DROP TABLE IF EXISTS `tabloginfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabloginfo` (
  `LogID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `LogInfo` longtext COMMENT 'IP@ClientID@Serial@Credit@Type@SQL',
  `LogDateTime` datetime NOT NULL,
  PRIMARY KEY (`LogID`,`LogDateTime`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8
/*!50100 PARTITION BY LINEAR HASH (MONTH( LogDateTime ))
PARTITIONS 12 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabloginfo`
--

LOCK TABLES `tabloginfo` WRITE;
/*!40000 ALTER TABLE `tabloginfo` DISABLE KEYS */;
INSERT INTO `tabloginfo` VALUES (1,'<Data><LocationID>5101070001001006</LocationID>                                            <DateTime>2013-08-06 09:45:04</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 09:45:04'),(2,'<Data><LocationID>5101070001001006</LocationID>                                            <DateTime>2013-08-06 09:47:26</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 09:47:26'),(3,'<Data><LocationID>5101070001001007</LocationID>                                            <DateTime>2013-08-06 09:47:58</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 09:47:58'),(4,'<Data><LocationID>5101070001001006</LocationID>                                            <DateTime>2013-08-06 09:48:42</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 09:48:42'),(5,'<Data><LocationID>5101070001001006</LocationID>                                            <DateTime>2013-08-06 09:48:58</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 09:48:58'),(6,'{\"Message\":\"ç”¨æˆ·ç™»å½•å¤±è´¥ã€‚\nåŸå¯†ç é”™è¯¯ã€‚ã€‚\"} SP:UserRecord','2013-08-06 10:36:51'),(7,'{\"Message\":\"ç”¨æˆ·ç™»å½•æˆåŠŸã€‚\"} SP:UserRecord','2013-08-06 10:37:45'),(8,'{\"Message\":\"ç”¨æˆ·ç™»å½•æˆåŠŸã€‚\"} SP:UserRecord','2013-08-06 11:21:17'),(9,'{\"Message\":\"ç”¨æˆ·ç™»å½•æˆåŠŸã€‚\"} SP:UserRecord','2013-08-06 11:25:53'),(10,'<Data><DeviceID>359732008920329</DeviceID><Accessor><IP>192.168.1.109</IP><ClientID>359732008920329</ClientID><TypeCode>ConfigInfo</TypeCode><UserID></UserID></Accessor></Data> SP:QueryConfigRecord','2013-08-06 11:27:57'),(11,'<Data><LocationID>5101070001001006</LocationID>                                            <DateTime>2013-08-06 11:28:21</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 11:28:21'),(12,'<Data><LocationID>5101070001001006</LocationID>                                            <DateTime>2013-08-06 11:28:27</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 11:28:27'),(13,'<Data><LocationID>5101070001001007</LocationID>                                            <DateTime>2013-08-06 11:28:42</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 11:28:42'),(14,'<Data><DeviceID>359732008920329</DeviceID><Accessor><IP>192.168.1.109</IP><ClientID>359732008920329</ClientID><TypeCode>ConfigInfo</TypeCode><UserID></UserID></Accessor></Data> SP:QueryConfigRecord','2013-08-06 11:34:44'),(15,'{\"Message\":\"ç”¨æˆ·ç™»å½•æˆåŠŸã€‚\"} SP:UserRecord','2013-08-06 11:34:57'),(16,'<Data><LocationID>5101070001001006</LocationID>                                            <DateTime>2013-08-06 11:36:04</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 11:36:04'),(17,'<Data><LocationID>5101070001001006</LocationID>                                            <DateTime>2013-08-06 11:37:58</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 11:37:58'),(18,'<Data><LocationID>5101070001###006</LocationID>                                            <Plate>å·A88888</Plate>                                            <Pay>0</Pay>                                            <Operator>æœªçŸ¥</Operator>                                            <Time>2013-08-06 11:37:58</Time>                                            <Image/>                                            <Accessor><IP>192.168.1.109</IP><ClientID>359732008920329</ClientID><TypeCode>TabletNormalData</TypeCode><UserID>1</UserID></Accessor>                                            <UserID>1</UserID></Data> SP:TabletNormalRecord','2013-08-06 11:38:37'),(19,'<Data><LocationID>5101070001001007</LocationID>                                            <DateTime>2013-08-06 11:38:46</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 11:38:46'),(20,'<Data><LocationID>5101070001001006</LocationID>                                            <DateTime>2013-08-06 11:51:41</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 11:51:41'),(21,'<Data><LocationID>5101070001###006</LocationID>                                            <Plate>å·A88888</Plate>                                            <Pay>5</Pay>                                            <Operator>æœªçŸ¥</Operator>                                            <Time>2013-08-06 11:52:58</Time>                                            <Image/>                                            <Accessor><IP>192.168.1.109</IP><ClientID>359732008920329</ClientID><TypeCode>TabletNormalData</TypeCode><UserID>1</UserID></Accessor>                                            <UserID>1</UserID></Data> SP:TabletNormalRecord','2013-08-06 11:53:12'),(22,'{\"Message\":\"ç”¨æˆ·ç™»å½•æˆåŠŸã€‚\"} SP:UserRecord','2013-08-06 11:56:13'),(23,'<Data><DeviceID>359732008920329</DeviceID><Accessor><IP>192.168.1.109</IP><ClientID>359732008920329</ClientID><TypeCode>ConfigInfo</TypeCode><UserID></UserID></Accessor></Data> SP:QueryConfigRecord','2013-08-06 11:56:40'),(24,'<Data><LocationID>5101070001001006</LocationID>                                            <DateTime>2013-08-06 11:56:41</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 11:56:41'),(25,'<Data><LocationID>5101070001001007</LocationID>                                            <DateTime>2013-08-06 11:58:55</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 11:58:55'),(26,'<Data><LocationID>5101070001001006</LocationID>                                            <DateTime>2013-08-06 12:01:37</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 12:01:37'),(27,'<Data><LocationID>5101070001001006</LocationID>                                            <DateTime>2013-08-06 14:55:15</DateTime>                                            <Accessor>Localhost</Accessor></Data> SP:SensorRecord','2013-08-06 14:55:16');
/*!40000 ALTER TABLE `tabloginfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabparkinfo`
--

DROP TABLE IF EXISTS `tabparkinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabparkinfo` (
  `ParkID` varchar(10) NOT NULL COMMENT 'AdministrativeID + SelfNumber\n510107 0001\n510107 + 0001\n\nTrigger==>AdministrativeID + ParkSelfNumber',
  `ParkName` varchar(45) NOT NULL,
  `ParkSpace` smallint(5) unsigned NOT NULL DEFAULT '0',
  `UsedSpace` smallint(5) unsigned DEFAULT '0',
  `ParkSelfNumber` varchar(4) NOT NULL DEFAULT '0',
  `ParkComments` varchar(45) DEFAULT NULL,
  `ParkParentID` varchar(10) NOT NULL,
  `UnitID` varchar(9) NOT NULL,
  PRIMARY KEY (`ParkID`),
  UNIQUE KEY `ParkID_UNIQUE` (`ParkID`),
  UNIQUE KEY `ParkName_UNIQUE` (`ParkName`),
  KEY `ParkUnit_idx` (`UnitID`),
  CONSTRAINT `ParkUnit` FOREIGN KEY (`UnitID`) REFERENCES `tabunitinfo` (`UnitID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabparkinfo`
--

LOCK TABLES `tabparkinfo` WRITE;
/*!40000 ALTER TABLE `tabparkinfo` DISABLE KEYS */;
INSERT INTO `tabparkinfo` VALUES ('5101070001','è‚¿ç˜¤åŒ»é™¢',2000,0,'0001',NULL,'0','771237583');
/*!40000 ALTER TABLE `tabparkinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabreceiverinfo`
--

DROP TABLE IF EXISTS `tabreceiverinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabreceiverinfo` (
  `ParkID` varchar(10) NOT NULL,
  `ReceiverName` varchar(45) DEFAULT NULL,
  `ReceiverID` varchar(3) NOT NULL,
  `ReceiverChannelID` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ReceiverComments` varchar(45) DEFAULT NULL,
  `ParkReceiverID` varchar(13) NOT NULL COMMENT 'ParkID+ ReceiverID \nTrigger==>ParkID ReceiverID',
  PRIMARY KEY (`ParkReceiverID`),
  UNIQUE KEY `AIID_UNIQUE` (`ParkReceiverID`),
  UNIQUE KEY `ReceiverName_UNIQUE` (`ReceiverName`),
  KEY `ParkReceiver_idx` (`ParkID`),
  CONSTRAINT `ParkReceiver` FOREIGN KEY (`ParkID`) REFERENCES `tabparkinfo` (`ParkID`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabreceiverinfo`
--

LOCK TABLES `tabreceiverinfo` WRITE;
/*!40000 ALTER TABLE `tabreceiverinfo` DISABLE KEYS */;
INSERT INTO `tabreceiverinfo` VALUES ('5101070001','è¥¿é—¨','001',1,NULL,'5101070001001');
/*!40000 ALTER TABLE `tabreceiverinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabtmpfeeinfo`
--

DROP TABLE IF EXISTS `tabtmpfeeinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabtmpfeeinfo` (
  `RecordID` bigint(20) unsigned NOT NULL,
  `Prepayment` smallint(5) unsigned NOT NULL DEFAULT '0',
  `Payment` smallint(5) unsigned NOT NULL DEFAULT '0',
  `PrepaymentOperator` varchar(45) NOT NULL,
  `PrepaymentTime` datetime NOT NULL,
  `PaymentTime` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `PaymentOperator` varchar(45) DEFAULT NULL,
  `PrepaymentUserID` bigint(20) unsigned DEFAULT NULL,
  `PaymentUserID` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`RecordID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabtmpfeeinfo`
--

LOCK TABLES `tabtmpfeeinfo` WRITE;
/*!40000 ALTER TABLE `tabtmpfeeinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `tabtmpfeeinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabtmpinoutimageinfo`
--

DROP TABLE IF EXISTS `tabtmpinoutimageinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabtmpinoutimageinfo` (
  `RecordID` bigint(20) unsigned NOT NULL,
  `EnterImage` longblob,
  `LeaveImage` longblob,
  `AddedTime` date NOT NULL,
  PRIMARY KEY (`RecordID`,`AddedTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
/*!50100 PARTITION BY LINEAR HASH (MONTH(AddedTime))
PARTITIONS 12 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabtmpinoutimageinfo`
--

LOCK TABLES `tabtmpinoutimageinfo` WRITE;
/*!40000 ALTER TABLE `tabtmpinoutimageinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `tabtmpinoutimageinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabtmpinoutrecordinfo`
--

DROP TABLE IF EXISTS `tabtmpinoutrecordinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabtmpinoutrecordinfo` (
  `RecordID` bigint(20) unsigned NOT NULL,
  `LocationID` varchar(16) NOT NULL,
  `EnterTime` datetime NOT NULL,
  `LeaveTime` datetime DEFAULT NULL,
  `EnterPlate` varchar(45) DEFAULT NULL,
  `LeavePlate` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`RecordID`,`EnterTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
/*!50100 PARTITION BY LINEAR HASH (MONTH(EnterTime))
PARTITIONS 12 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabtmpinoutrecordinfo`
--

LOCK TABLES `tabtmpinoutrecordinfo` WRITE;
/*!40000 ALTER TABLE `tabtmpinoutrecordinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `tabtmpinoutrecordinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabtmploginfo`
--

DROP TABLE IF EXISTS `tabtmploginfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabtmploginfo` (
  `LogID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `LogInfo` longtext COMMENT 'IP@ClientID@Serial@Credit@Type@SQL',
  `LogDateTime` datetime NOT NULL,
  PRIMARY KEY (`LogID`,`LogDateTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
/*!50100 PARTITION BY LINEAR HASH (MONTH( LogDateTime ))
PARTITIONS 12 */;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabtmploginfo`
--

LOCK TABLES `tabtmploginfo` WRITE;
/*!40000 ALTER TABLE `tabtmploginfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `tabtmploginfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabtmpuserloginoutinfo`
--

DROP TABLE IF EXISTS `tabtmpuserloginoutinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabtmpuserloginoutinfo` (
  `LogID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `LogUserID` bigint(20) unsigned DEFAULT NULL,
  `LogTime` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `LogType` enum('Login','Logout') DEFAULT NULL,
  `LogClientID` varchar(45) DEFAULT NULL,
  `LogIP` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`LogID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabtmpuserloginoutinfo`
--

LOCK TABLES `tabtmpuserloginoutinfo` WRITE;
/*!40000 ALTER TABLE `tabtmpuserloginoutinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `tabtmpuserloginoutinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabunitinfo`
--

DROP TABLE IF EXISTS `tabunitinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabunitinfo` (
  `UnitID` varchar(9) NOT NULL,
  `UnitName` varchar(45) NOT NULL,
  `UnitComments` varchar(45) DEFAULT NULL,
  `AdministrativeID` varchar(6) NOT NULL,
  `UnitAddress` varchar(500) NOT NULL,
  PRIMARY KEY (`UnitID`),
  UNIQUE KEY `UnitID_UNIQUE` (`UnitID`),
  UNIQUE KEY `UnitName_UNIQUE` (`UnitName`),
  KEY `UnitAdministrative_idx` (`AdministrativeID`),
  CONSTRAINT `UnitAdministrative` FOREIGN KEY (`AdministrativeID`) REFERENCES `tabadministrativeinfo` (`AdministrativeID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabunitinfo`
--

LOCK TABLES `tabunitinfo` WRITE;
/*!40000 ALTER TABLE `tabunitinfo` DISABLE KEYS */;
INSERT INTO `tabunitinfo` VALUES ('771237583','å››å·å‰é€”é«˜ç§‘',NULL,'510107','æµ‹è¯•åœ°å€');
/*!40000 ALTER TABLE `tabunitinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabuserinfo`
--

DROP TABLE IF EXISTS `tabuserinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabuserinfo` (
  `UserID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `UserName` varchar(45) NOT NULL,
  `UserComments` varchar(45) DEFAULT NULL,
  `GroupID` bigint(20) unsigned NOT NULL,
  `UserPwd` varchar(128) NOT NULL,
  `UserAddress` varchar(512) DEFAULT NULL,
  `UserImage` longblob,
  `UserTelephone` varchar(45) DEFAULT NULL,
  `UserIdentity` varchar(18) DEFAULT NULL,
  `UserState` enum('Login','Logout') DEFAULT 'Logout',
  `UserJobNumber` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`UserID`),
  UNIQUE KEY `UserID_UNIQUE` (`UserID`),
  UNIQUE KEY `UserName_UNIQUE` (`UserName`),
  KEY `UserGroup_idx` (`GroupID`),
  CONSTRAINT `UserGroup` FOREIGN KEY (`GroupID`) REFERENCES `tabgroupinfo` (`GroupID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabuserinfo`
--

LOCK TABLES `tabuserinfo` WRITE;
/*!40000 ALTER TABLE `tabuserinfo` DISABLE KEYS */;
INSERT INTO `tabuserinfo` VALUES (1,'Test',NULL,1,'dGVzdDEyMw==','äººæ°‘å—è·¯',NULL,NULL,NULL,'Login','12345');
/*!40000 ALTER TABLE `tabuserinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabuserloginoutinfo`
--

DROP TABLE IF EXISTS `tabuserloginoutinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tabuserloginoutinfo` (
  `LogID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `LogUserID` bigint(20) unsigned DEFAULT NULL,
  `LogTime` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `LogType` enum('Login','Logout') DEFAULT NULL,
  `LogClientID` varchar(45) DEFAULT NULL,
  `LogIP` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`LogID`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabuserloginoutinfo`
--

LOCK TABLES `tabuserloginoutinfo` WRITE;
/*!40000 ALTER TABLE `tabuserloginoutinfo` DISABLE KEYS */;
INSERT INTO `tabuserloginoutinfo` VALUES (1,1,'2013-08-06 10:37:45','Login','359732008920329','192.168.1.109'),(2,1,'2013-08-06 11:21:17','Login','359732008920329','192.168.1.109'),(3,1,'2013-08-06 11:25:53','Login','359732008920329','192.168.1.109'),(4,1,'2013-08-06 11:34:57','Login','359732008920329','192.168.1.109'),(5,1,'2013-08-06 11:56:13','Login','359732008920329','192.168.1.109');
/*!40000 ALTER TABLE `tabuserloginoutinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary table structure for view `viewconfiginfo`
--

DROP TABLE IF EXISTS `viewconfiginfo`;
/*!50001 DROP VIEW IF EXISTS `viewconfiginfo`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `viewconfiginfo` (
  `DeviceID` tinyint NOT NULL,
  `UnitID` tinyint NOT NULL,
  `UnitName` tinyint NOT NULL,
  `ParkID` tinyint NOT NULL,
  `ParkName` tinyint NOT NULL,
  `ReceiverID` tinyint NOT NULL,
  `ReceiverName` tinyint NOT NULL
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `viewfeeinfo`
--

DROP TABLE IF EXISTS `viewfeeinfo`;
/*!50001 DROP VIEW IF EXISTS `viewfeeinfo`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `viewfeeinfo` (
  `RecordID` tinyint NOT NULL,
  `Prepayment` tinyint NOT NULL,
  `Payment` tinyint NOT NULL,
  `PrepaymentOperator` tinyint NOT NULL,
  `PrepaymentTime` tinyint NOT NULL,
  `PaymentTime` tinyint NOT NULL,
  `PaymentOperator` tinyint NOT NULL,
  `PrepaymentUserID` tinyint NOT NULL,
  `PaymentUserID` tinyint NOT NULL,
  `LocationID` tinyint NOT NULL,
  `UnitName` tinyint NOT NULL,
  `UnitID` tinyint NOT NULL,
  `AdministrativeName` tinyint NOT NULL,
  `AdministrativeType` tinyint NOT NULL,
  `AdministrativeID` tinyint NOT NULL,
  `ParkName` tinyint NOT NULL,
  `ParkID` tinyint NOT NULL
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `viewinoutrecord`
--

DROP TABLE IF EXISTS `viewinoutrecord`;
/*!50001 DROP VIEW IF EXISTS `viewinoutrecord`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `viewinoutrecord` (
  `RecordID` tinyint NOT NULL,
  `LocationID` tinyint NOT NULL,
  `EnterTime` tinyint NOT NULL,
  `LeaveTime` tinyint NOT NULL,
  `EnterPlate` tinyint NOT NULL,
  `LeavePlate` tinyint NOT NULL,
  `EnterImage` tinyint NOT NULL,
  `LeaveImage` tinyint NOT NULL,
  `Prepayment` tinyint NOT NULL,
  `Payment` tinyint NOT NULL,
  `PrepaymentOperator` tinyint NOT NULL,
  `PrepaymentTime` tinyint NOT NULL,
  `PaymentOperator` tinyint NOT NULL,
  `PaymentTime` tinyint NOT NULL
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `viewwholefeerecordquery`
--

DROP TABLE IF EXISTS `viewwholefeerecordquery`;
/*!50001 DROP VIEW IF EXISTS `viewwholefeerecordquery`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `viewwholefeerecordquery` (
  `RecordID` tinyint NOT NULL,
  `Prepayment` tinyint NOT NULL,
  `Payment` tinyint NOT NULL,
  `PrepaymentOperator` tinyint NOT NULL,
  `PrepaymentTime` tinyint NOT NULL,
  `PaymentTime` tinyint NOT NULL,
  `PaymentOperator` tinyint NOT NULL,
  `PrepaymentUserID` tinyint NOT NULL,
  `PaymentUserID` tinyint NOT NULL,
  `LocationID` tinyint NOT NULL,
  `UnitName` tinyint NOT NULL,
  `UnitID` tinyint NOT NULL,
  `AdministrativeName` tinyint NOT NULL,
  `AdministrativeType` tinyint NOT NULL,
  `AdministrativeID` tinyint NOT NULL,
  `ParkName` tinyint NOT NULL,
  `ParkID` tinyint NOT NULL
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `viewwholeinoutrecordquery`
--

DROP TABLE IF EXISTS `viewwholeinoutrecordquery`;
/*!50001 DROP VIEW IF EXISTS `viewwholeinoutrecordquery`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `viewwholeinoutrecordquery` (
  `RecordID` tinyint NOT NULL,
  `LocationID` tinyint NOT NULL,
  `EnterTime` tinyint NOT NULL,
  `LeaveTime` tinyint NOT NULL,
  `EnterPlate` tinyint NOT NULL,
  `LeavePlate` tinyint NOT NULL,
  `EnterImage` tinyint NOT NULL,
  `LeaveImage` tinyint NOT NULL,
  `Prepayment` tinyint NOT NULL,
  `Payment` tinyint NOT NULL,
  `PrepaymentOperator` tinyint NOT NULL,
  `PrepaymentTime` tinyint NOT NULL,
  `PaymentOperator` tinyint NOT NULL,
  `PaymentTime` tinyint NOT NULL
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `viewwholelogrecordquery`
--

DROP TABLE IF EXISTS `viewwholelogrecordquery`;
/*!50001 DROP VIEW IF EXISTS `viewwholelogrecordquery`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `viewwholelogrecordquery` (
  `LogID` tinyint NOT NULL,
  `LogInfo` tinyint NOT NULL,
  `LogDateTime` tinyint NOT NULL
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `viewwholeuserloginoutrecordquery`
--

DROP TABLE IF EXISTS `viewwholeuserloginoutrecordquery`;
/*!50001 DROP VIEW IF EXISTS `viewwholeuserloginoutrecordquery`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `viewwholeuserloginoutrecordquery` (
  `LogID` tinyint NOT NULL,
  `LogUserID` tinyint NOT NULL,
  `LogTime` tinyint NOT NULL,
  `LogType` tinyint NOT NULL,
  `LogClientID` tinyint NOT NULL,
  `LogIP` tinyint NOT NULL
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Dumping events for database 'streetroadpark'
--

--
-- Dumping routines for database 'streetroadpark'
--
/*!50003 DROP FUNCTION IF EXISTS `GetLocationIDByDetectorID` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` FUNCTION `GetLocationIDByDetectorID`( strID char( 16 ) ) RETURNS char(16) CHARSET utf8
BEGIN
	declare strLocationID char( 16 ) DEFAULT null;

	select ReceiverDetectorID into strLocationID 
	 from TabDetectorInfo where DetectorID = Right( strID, 3 );

RETURN strLocationID;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `DeviceRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `DeviceRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#<Data><Device><DeviceID/><StartTime/><EndTime/><SN/><Comments/><UnitID/><Operator/></Device><Accessor/><Data>
	#<Data><Value/></Data>
	# ( '','','' ), ( '', '', '' )

	declare strValues LONGTEXT default ExtractValue( txtXml, '/Data/Value' );
	declare strSQL LONGTEXT default null;

	if ( ISNULL( strValues ) || 0 = LENGTH( strValues ) ) then
		set txtXml = '{"Message":"SQLè¯­å¥ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	if ( 1 = nFlag ) then  #Register
		SET strSQL = CONCAT( "<Data><SQL>Replace into TabDeviceRegisterInfo( DeviceID, StartTime, EndTime, SerialNumber, UnitID, DeviceComments, Register )
							   Values ", strValues, "</SQL></Data>" );
	else if ( 0 = nFlag ) then #Unregister
			SET strSQL = CONCAT( "<Data><SQL>INSERT Into TabDeviceRegisterInfo( DeviceID, Unregister ) Values ",
								 strValues, " on Duplicate key Update Unregister = VALUES( Unregister ), DeviceState = 'Unavailable'</SQL></Data>" );
		end if;
	end if;

	CALL ExecuteSQL( strSQL, nFlag );
	
	INSERT INTO TabLogInfo( LogInfo, LogDateTime ) VALUES( CONCAT( txtXml, ' SP:DeviceRecord' ), NOW( ) );
	set txtXml = CONCAT( 'è®¾å¤‡', IF ( 0 != nFlag, 'æ³¨å†Œã€‚', 'æ³¨é”€ã€‚' ), 'æˆåŠŸã€‚' );
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `ExecuteSQL` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `ExecuteSQL`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#<Data><SQL/><Accessor/><Data>
	declare strSQL LONGTEXT default ExtractValue( txtXml, 'Data/SQL' );

	if ( ISNULL( strSQL ) || 0 = LENGTH( strSQL ) ) then
		set txtXml = '{"Message":"SQLè¯­å¥ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	SET @STMTSQL = strSQL;
	set @Result = null;

	PREPARE STMT FROM @STMTSQL;
	EXECUTE STMT;
	DEALLOCATE PREPARE STMT;

	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( txtXml, ' SP:ExecuteSQL' ), NOW( ) );
	set txtXml = @Result;
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GroupRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `GroupRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#<Data><UnitID/><Accessor/><Data>

	declare strUnitID VARCHAR( 9 ) default ExtractValue( txtXml, '/Data/UnitID' );

	if ( ISNULL( strUnitID ) || 0 = LENGTH( strUnitID ) ) then
		set txtXml = '{"Message":"å…¬å¸æœºæ„ä»£ç ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	#set strSQL = CONCAT( 'Select GroupID, GroupName, GroupRight From TabGroupInfo Where UnitID = ', strUnitID );

	#CALL ExecuteSQL( strSQL, nFlag );
	

	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( txtXml, ' SP:GroupRecord' ), NOW( ) );
	set txtXml = ( Select CONCAT( '{"List":[',
											   GROUP_CONCAT( CONCAT( '{"GroupID":"',GroupID,'"' ),
													         CONCAT( ',"GroupName":"', GroupName, '"' ),
															 CONCAT( ',"GroupRight":"', GroupRight, '"}' ) ), ']}' ) 
				   From TabGroupInfo Where UnitID = strUnitID );

	if ( txtXml is null ) then
		set txtXml = CONCAT( '{"Message":"æŸ¥è¯¢æ— è®°å½•æ•°æ®ã€‚"}' );
		set nFlag = -1;
	end if;
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `MaintainDb` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `MaintainDb`(  in nFlag TINYINT )
EXITBODY:
BEGIN
	# show warnings;
	# show errors;
	case nFlag
		when 0 then Call TransferTmpRecord2History( ); #Temp record to history record
		when 1 then Call MaintainInOutRecord( 5 ); # ä¿ç•™æœ€è¿‘5å¤©çš„æ•°æ®ï¼Œä¸è€ƒè™‘æ—¶é—´
		when 2 then Call MaintainHistoryInOutRecord( 365 ); #ä¿ç•™æœ€è¿‘1å¹´çš„æ•°æ®ï¼Œä¸è€ƒè™‘æ—¶é—´
	end case;
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `MaintainHistoryInOutRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `MaintainHistoryInOutRecord`( in nDay int unsigned )
EXITBODY:
BEGIN
	Delete From TabHistoryInOutRecordInfo Where Date( EnterTime ) < DATE_SUB( CURDATE( ), INTERVAL nDay DAY );
	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( 'å®šæ—¶ç»´æŠ¤å†å²è®°å½•æ•°æ® ', ' SP:MaintainHistoryInOutRecord' ), NOW( ) );
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `MaintainInOutRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `MaintainInOutRecord`( in nDay int unsigned )
EXITBODY:
BEGIN
	#ADDDATE ADDTIME DATE_ADD DATE_SUB 
	Delete From TabInOutRecordInfo Where Date( EnterTime ) < DATE_SUB( CURDATE( ), INTERVAL nDay DAY );
	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( 'å®šæ—¶ç»´æŠ¤è¿›å‡ºè®°å½•æ•°æ® ', ' SP:MaintainInOutRecord' ), NOW( ) );
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `QueryCommonRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `QueryCommonRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#<Data><DataType/></Data> è·å–å„ç§è®°å½•æ•°æ®
	
	declare strDataType VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/DataType' );

	if ( ISNULL( strDataType ) || 0 = LENGTH( strDataType ) ) then
		set txtXml = '{"Message":"è¯·æ±‚æ•°æ®ç±»å‹ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY; 
	end if;

	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( txtXml, ' SP:QueryCommonRecord' ), NOW( ) );

	if ( UPPER( strDataType ) = 'UNITINFO' ) then #å…¬å¸ä¿¡æ¯ UnitInfo
		Select CONCAT( '{"List":[',
						   GROUP_CONCAT( CONCAT( '{"UnitID":"', UnitID, '"' ),
										 CONCAT( ',"UnitName":"', UnitName, '"'),
										 CONCAT( ',"UnitAddress":"', IFNULL( UnitAddress, '' ), '"}' ) ), ']}' )
			into txtXml From TabUnitInfo;
	elseif ( UPPER( strDataType ) = '' ) then
		set nFlag = -1;
	elseif ( UPPER( strDataType ) = '' ) then
		set nFlag = -1;
	else 
		set txtXml = CONCAT( '{"Message":"æ— æ•ˆæ•°æ®ç±»è¯·æ±‚ã€‚ã€', strDataType, 'ã€‘"}' );
		set nFlag = -1;
	end if;

	if ( txtXml is null ) then
		set txtXml = CONCAT( '{"Message":"æŸ¥è¯¢æ— è®°å½•æ•°æ®ã€‚"}' );
		set nFlag = -1;
	end if;

END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `QueryConfigRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `QueryConfigRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#<Data><DeviceID/></Data>
	
	declare strDeviceID VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/DeviceID' );
	declare curDateTime DATETIME default now( );
	declare strSQL TEXT default '';

	if ( ISNULL( strDeviceID ) || 0 = LENGTH( strDeviceID ) ) then
		set txtXml = '{"Message":"è®¾å¤‡å·ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY; 
	end if;

	if ( not Exists ( Select DeviceID from TabDeviceRegisterInfo where DeviceID = strDeviceID ) ) then
		set txtXml = CONCAT( '{"Message":"è®¾å¤‡ã€', strDeviceID, 'ã€‘æœªæ³¨å†Œã€‚"}' );
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	if ( not Exists ( Select DeviceID from TabDeviceRegisterInfo where DeviceID = strDeviceID and DeviceState = 'Available' ) ) then
		set txtXml = CONCAT( '{"Message":"è®¾å¤‡ã€', strDeviceID, 'ã€‘å·²è¢«æ³¨é”€ã€‚"}' );
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	if ( not Exists ( Select DeviceID from TabDeviceRegisterInfo where DeviceID = strDeviceID and 
		 DeviceState = 'Available' and ( StartTime <= curDateTime and curDateTime <= EndTime ) ) ) then
		set txtXml = CONCAT( '{"Message":"è®¾å¤‡ã€', strDeviceID, 'ã€‘å·²è¿‡æœŸã€‚"}' );
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	if ( not Exists ( Select DeviceID from TabDeviceRegisterInfo where DeviceID = strDeviceID and 
		 DeviceState = 'Available' and ( StartTime <= curDateTime and curDateTime <= EndTime )
		and UnitID is not null ) ) then
		set txtXml = CONCAT( '{"Message":"è®¾å¤‡ã€', strDeviceID, 'ã€‘æ— å½’å±å…¬å¸ã€‚"}' );
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	if ( not Exists ( Select DeviceID from TabDeviceRegisterInfo where DeviceID = strDeviceID and 
		 DeviceState = 'Available' and ( StartTime <= curDateTime and curDateTime <= EndTime )
		and UnitID is not null and SerialNumber is not null ) ) then
		set txtXml = CONCAT( '{"Message":"è®¾å¤‡ã€', strDeviceID, 'ã€‘åºåˆ—å·æ— æ•ˆã€‚"}' );
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( txtXml, ' SP:QueryConfigRecord' ), NOW( ) );
	Select CONCAT( '{"List":[',
						   GROUP_CONCAT( CONCAT( '{"DeviceID":"', DeviceID, '"' ),
										 CONCAT( ',"UnitID":"', UnitID, '"'),
										 CONCAT( ',"UnitName":"', UnitName, '"'),
										 CONCAT( ',"ParkID":"', ParkID, '"'),
										 CONCAT( ',"ParkName":"', ParkName, '"'),
										 CONCAT( ',"ReceiverID":"', ReceiverID, '"'),
										 CONCAT( ',"ReceiverName":"', ReceiverName, '"}' ) ), ']}' )
			into txtXml From ViewConfigInfo Where DeviceID = strDeviceID; 

	if ( txtXml is null ) then
		set txtXml = CONCAT( '{"Message":"æŸ¥è¯¢æ— è®°å½•æ•°æ®ã€‚"}' );
		set nFlag = -1;
	end if;
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `QueryImageRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `QueryImageRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#<Data><RecordID/></Data>
	
	declare strRecordID VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/RecordID' );

	declare strSQL TEXT default '';

	if ( ISNULL( strRecordID ) || 0 = LENGTH( strRecordID ) ) then
		set txtXml = '{"Message":"è®°å½•å·ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	Select CONCAT( '{"List":[',
						   GROUP_CONCAT( CONCAT( '{"RecordID":"', RecordID,'"' ),
										 CONCAT( ',"EnterImage":"', TO_BASE64( EnterImage ), '"'),
										 CONCAT( ',"LeaveImage":"', TO_BASE64( LeaveImage ), '"}' ) ), ']}' )
			into txtXml From ViewInOutRecord Where RecordID = strRecordID; 

	INSERT INTO TabLogInfo( LogInfo, LogDateTime ) VALUES( ' SP:QueryImageRecord', NOW( ) );

	if ( txtXml is null ) then
		set txtXml = CONCAT( '{"Message":"æŸ¥è¯¢æ— è®°å½•æ•°æ®ã€‚"}' );
		set nFlag = -1;
	end if;
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `QueryInOutRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `QueryInOutRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#<Data><LocationID/><EnterStartTime/><EnterEndTime/><LeaveStartTime/><LeaveEndTime/><Plate/><Operator/><Limit/></Data>
	# group_concat_max_len max_allowed_packet

	declare strLocationID VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/LocationID' );
	declare strEnterStartTime VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/EnterStartTime' );
	declare strEnterEndTime VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/EnterEndTime' );
	declare strLeaveStartTime VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/LeaveStartTime' );
	declare strLeaveEndTime VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/LeaveEndTime' );
	declare strPlate VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/Plate' );
	declare strOperator VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/Operator' );
	declare strLimit VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/Limit' );
	declare strImage VARCHAR( 1 ) default ExtractValue( txtXml, '/Data/IncludedImage' );

	declare bImage boolean default TRUE;
	declare strSQL LONGTEXT default '';

	select GetLocationIDByDetectorID( strLocationID ) into strLocationID;

	if ( ISNULL( strLocationID ) || 0 = LENGTH( strLocationID ) ) then
		set txtXml = '{"Message":"è½¦ä½å·ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	if ( 0 = LENGTH( strImage ) || '0' = strImage ) then
		set bImage = FALSE;
	end if;

	set strSQL = '<Data><SQL>Select CONCAT( \'{"List":[\',
											   GROUP_CONCAT( CONCAT( \'{"RecordID":"\',RecordID,\'"\' ),
															 CONCAT( \',"LocationID":"\',LocationID,\'"\' ),
													         CONCAT( \',"EnterTime":"\', EnterTime, \'"\' ),
															 CONCAT( \',"LeaveTime":"\', LeaveTime, \'"\' ),
															 CONCAT( \',"EnterPlate":"\', EnterPlate, \'"\'),
															 CONCAT( \',"LeavePlate":"\', LeavePlate, \'"\'),';

	if ( bImage ) then
		set strSQl = CONCAT( strSQL, 'CONCAT( \',"EnterImage":"\', TO_BASE64( EnterImage ), \'"\'),
															 CONCAT( \',"LeaveImage":"\', TO_BASE64( LeaveImage ), \'"\'),' );
	end if;
	
		set strSQl = CONCAT( strSQL, 'CONCAT( \',"Prepayment":"\', Prepayment, \'"\'),
															 CONCAT( \',"PrepaymentOperator":"\', PrepaymentOperator, \'"\'),
															 CONCAT( \',"PrepaymentTime":"\', PrepaymentTime, \'"\'),
															 CONCAT( \',"Payment":"\', Payment, \'"\'),
															 CONCAT( \',"PaymentOperator":"\', PaymentOperator, \'"\'),
															 CONCAT( \',"PaymentTime":"\', PaymentTime, \'"}\' ) ), \']}\' ) 
				   into @Result From ( Select * from ViewInOutRecord Where LocationID =  \'', strLocationID, '\'' );


	if ( 0 <> LENGTH( strEnterStartTime )  && 0 <> LENGTH( strEnterEndTime ) ) then
		set strSQL = CONCAT( strSQL, ' and EnterTime between \'', strEnterStartTime, '\' and \'',  strEnterEndTime, '\'' );
	end if;

	if ( 0 <> LENGTH( strLeaveStartTime )  && 0 <> LENGTH( strLeaveEndTime ) ) then
		set strSQL = CONCAT( strSQL, ' and LeaveTime between \'', strLeaveStartTime, '\' and \'',  strLeaveEndTime, '\'' );
	end if;

	if ( 0 <> LENGTH( strPlate ) ) then
		set strSQL = CONCAT( strSQL, ' and ( EnterPlate = \'', strPlate, '\' or LeavePlate = \'',  strPlate, '\' )' );
	end if;

	if ( 0 <> LENGTH( strOperator )  ) then
		set strSQL = CONCAT( strSQL, ' and ( PrepaymentOperator = \'', strOperator, '\' or PaymentOperator = \'',  strOperator, '\' )' );
	end if;

	if ( 0 = LENGTH( strLimit ) || '0' = strLimit ) then
		set strOperator = '1';	
	end if;

	set strSQL = CONCAT( strSQL, ' limit ', strLimit, ' ) a</SQL></Data>' );

	INSERT INTO TabLogInfo( LogInfo, LogDateTime ) VALUES( CONCAT( txtXml, ' SP:QueryInOutRecord' ), NOW( ) );
	#set @Result = 'Test';
	CALL ExecuteSQL( strSQL, nFlag );

	set txtXml = strSQL;
	set nFlag = 1;

	if ( txtXml is null ) then
		set txtXml = CONCAT( '{"Message":"æŸ¥è¯¢æ— è®°å½•æ•°æ®ã€‚"}' );
		set nFlag = -1;
	end if;
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `QueryReportRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `QueryReportRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#<Data><UnitID/><ParkID/><PaymentStartTime/><PaymentEndTime/></Data>
	
	declare strUnitID VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/UnitID' );
	declare strParkID VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/ParkID' );
	declare strPaymentStartTime VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/PaymentStartTime' );
	declare strPaymentEndTime VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/PaymentEndTime' );

	declare strSQL TEXT default '';
	declare strWhere TEXT default '';

	if ( 0 <> LENGTH( strUnitID ) ) then
		set strSQL = CONCAT( ' UnitID = \'', strUnitID, '\'' );
	end if;
	
	if ( 0 <> LENGTH( strParkID ) ) then
		set strSQL = CONCAT( IF( 0 = LENGTH( strSQL ), '', CONCAT( strSQL, ' and ' ) ), ' ParkID = \'', strParkID, '\'' );
	end if;

	if ( 0 <> LENGTH( strPaymentStartTime ) ) then
		set strSQL = CONCAT( IF( 0 = LENGTH( strSQL ), '', CONCAT( strSQL, ' and ' ) ), ' PaymentTime between \'', 
							 strPaymentStartTime, '\' and \'', 
							 IF( 0 <> LENGTH( strPaymentEndTime ), 
								strPaymentEndTime, NOW( ) ), '\'' );
	end if;

	if ( 0 <> LENGTH( strSQL ) ) then
		set strSQL = CONCAT( ' Where ', strSQL );
	end if;

	set strSQL = CONCAT( '<Data><SQL>Select CONCAT( \'{"List":[\',
						   GROUP_CONCAT( CONCAT( \'{"UnitName":"\', IFNULL( UnitName, \'\' ), \'"\' ),
										 CONCAT( \',"ParkName":"\', IFNULL( ParkName, \'\' ), \'"\'),
										 CONCAT( \',"PaymentOperator":"\', IFNULL( PaymentOperator, \'\' ), \'"\'),
										 CONCAT( \',"PaymentTotal":"\', PaymentTotal, \'"}\' ) ), \']}\' )
			 into @Result From ( select UnitName, ParkName, PaymentOperator, sum( Payment ) as 
			PaymentTotal from ViewFeeInfo ', IF( 0 = LENGTH( strSQL ), '', strSQL ), 
					' Group by UnitName, ParkName, PaymentOperator with rollup ) Total</SQL></Data>' );


	INSERT INTO TabLogInfo( LogInfo, LogDateTime ) VALUES( CONCAT( txtXml, ' SP:GetReportRecord' ), NOW( ) );
	#set @Result = 'Test';
	CALL ExecuteSQL( strSQL, nFlag );

	set txtXml = strSQL;
	set nFlag = 1;

	if ( txtXml is null ) then
		set txtXml = CONCAT( '{"Message":"æŸ¥è¯¢æ— è®°å½•æ•°æ®ã€‚"}' );
		set nFlag = -1;
	end if;
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `SensorRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `SensorRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#IP@ClientID@Serial@Credit@Type
	#<Data><LocationID/><DateTime/><Accessor/><Data>
	declare curDateTime DATETIME default CONVERT( ExtractValue( txtXml, 'Data/DateTime' ), DATETIME );
	declare strLocationID VARCHAR( 16 ) default ExtractValue( txtXml, 'Data/LocationID' );
	declare nRecordID bigint unsigned default null;

	if ( ISNULL( strLocationID ) || 0 = LENGTH( strLocationID ) ) then
		set txtXml = '{"Message":"è½¦ä½å·ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	select RecordID into nRecordID from TabLocationHaveCarInfo where LocationID = strLocationID;

	if ( 1 = nFlag ) then -- Enter
		if ( nRecordID is not null  ) then
			Set nFlag = 2; -- entered
			set txtXml = '{"Message":"è¯¥è½¦ä½å·²æœ‰è½¦ã€‚"}';
			Leave EXITBODY;
		end if;

		-- First enter
		start transaction;
		insert into TabInOutRecordInfo( LocationID, EnterTime ) VALUES( strLocationID, curDateTime );
		set nRecordID = LAST_INSERT_ID( );
		Insert into TabLocationHaveCarInfo( LocationID, EnterTime, RecordID ) Values( strLocationID, curDateTime, LAST_INSERT_ID( ) );
		commit;
	else if ( 0 = nFlag ) then -- Leave
			if ( ( nRecordID is null ) or -- tablet left
				 ( exists ( select LeaveTime from TabInOutRecordInfo where RecordID = nRecordID and LeaveTime is not NULL ) )  ) then -- sensor left
				Set nFlag = 3; -- left
				set txtXml = '{"Message":"è¯¥è½¦ä½å·²æ— è½¦ã€‚"}';
				Leave EXITBODY;
			end if;

			start transaction;
			update TabInOutRecordInfo set LeaveTime = curDateTime where RecordID = nRecordID;
			update TabLocationHaveCarInfo set LeaveTime = curDateTime where LocationID = strLocationID;
			commit;
		end if;
	end if;

	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( txtXml, ' SP:SensorRecord' ), NOW( ) );

	if ( 1 = nFlag ) then -- Enter
		set txtXml = ( select CONCAT( '{', 
						GROUP_CONCAT( CONCAT( '"LocationID":"', LocationID, '",' ),
									  CONCAT( '"State":"', CONVERT( nFlag, CHAR ), '",' ),
									  CONCAT( '"RecordID":"', CONVERT( nRecordID, CHAR ), '",' ),
									  CONCAT( '"EnterTime":"', EnterTime, '"' ) ) 
						,"}" ) from tablocationhavecarinfo where LocationID = strLocationID );
	else if ( 0 = nFlag ) then -- Leave
			set txtXml = ( select CONCAT( '{', 
					GROUP_CONCAT( CONCAT( '"LocationID":"', LocationID, '",' ),
								  CONCAT( '"State":"', CONVERT( nFlag, CHAR ), '",' ),
								  CONCAT( '"RecordID":"', CONVERT( nRecordID, CHAR ), '",' ),
								  CONCAT( '"Prepayment":"', Prepayment, '",' ),
								  CONCAT( '"EnterTime":"', EnterTime, '",' ),
								  CONCAT( '"LeaveTime":"', IFNULL( LeaveTime, '' ), '"' ) )
					,"}" ) from tablocationhavecarinfo where LocationID = strLocationID );
		end if;
	end if;
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `TabletManualRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `TabletManualRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN

	#ExtractValue( '<Data><a>test</a></Record>', 'Data/a' );
	# strRecord <Data><LocationID/><Plate>å·A12345</Plate><Pay>10</Pay><Operator>å¼ ä¸‰</Operaor><Time>2013-03-15 12:12:34</Time><Image/></Data>
	declare strLocationID VARCHAR( 16 ) default ExtractValue( txtXml, 'Data/LocationID' );
	declare strPlate VARCHAR( 45 ) default ExtractValue( txtXml, 'Data/Plate' );
	declare strPay VARCHAR( 45 ) default ExtractValue( txtXml, 'Data/Pay' );
	declare strOperator VARCHAR( 45 ) default ExtractValue( txtXml, 'Data/Operator' );
	declare strTime VARCHAR( 45 ) default ExtractValue( txtXml, 'Data/Time' );
	declare image LONGBLOB default FROM_BASE64( ExtractValue( txtXml, 'Data/Image' ) );
	declare nUserID BIGINT UNSIGNED default ExtractValue( txtXml, '/Data/UserID' );
	declare strSensorTime VARCHAR( 45 ) default ExtractValue( txtXml, 'Data/SensorTime' );
	declare nRecordID BIGINT UNSIGNED default null;

	select GetLocationIDByDetectorID( strLocationID ) into strLocationID;

	if ( ISNULL( strLocationID ) ||ã€€0 = LENGTH( strLocationID ) ) then
		set txtXml = '{"Message":"è½¦ä½å·ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	select RecordID into nRecordID from TabLocationHaveCarInfo where LocationID = strLocationID;
	
	if ( 1 = nFlag ) then -- Enter
		if ( nRecordID is null  ) then
			start transaction;
			insert into TabInOutRecordInfo( LocationID, EnterTime, EnterPlate ) VALUES( 
											strLocationID, strSensorTime, strPlate );
			Insert into TabLocationHaveCarInfo( LocationID, EnterTime, RecordID, Prepayment ) Values( 
												strLocationID, strSensorTime, LAST_INSERT_ID( ), strPay );
			insert into TabInOutImageInfo ( RecordID, EnterImage, AddedTime ) values( nRecordID, image, DATE( strTime ) );
			insert into TabFeeInfo( RecordID, Prepayment, PrepaymentOperator, PrepaymentTime, PrepaymentUserID ) 
						   VALUES( nRecordID, strPay, strOperator, strTime, nUserID );					
			commit;
		else
			Set nFlag = -1; -- æœ‰è¿›å…¥è®°å½•æœªå¤„ç†
			set txtXml = '{"Message":"è¯¥è½¦ä½æœ‰è¿›å…¥è®°å½•æœªè¢«å¤„ç†ã€‚"}';
			Leave EXITBODY;
		end if;
	else if ( 0 = nFlag ) then -- Leave
			if ( nRecordID is null  ) then
				Set nFlag = -1; -- è¯¥è½¦è¾†æ— è¿›å…¥è®°å½•
				set txtXml = '{"Message":"è¯¥è½¦è¾†æ— è¿›å…¥è®°å½•ã€‚"}';
				Leave EXITBODY;
			end if;

			start transaction;
			delete from TabLocationHaveCarInfo where RecordID = nRecordID;

			update TabInOutRecordInfo set LeavePlate = strPlate, LeaveTime = strSensorTime where RecordID = nRecordID; -- æœªçŸ¥
			update TabInOutImageInfo set LeaveImage = image where RecordID = nRecordID;
			update TabFeeInfo set Payment = strPay, PaymentOperator = strOperator, 
							  PaymentTime = strTime, PaymentUserID = nUserID 
					where RecordID = nRecordID;
			commit;
		end if;
	end if;

	set txtXml = UpdateXML( txtXml, '/Data/Image', '<Image/>' );
	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( txtXml, ' SP:TabletManualRecord' ), NOW( ) );
	set txtXml = CONCAT( 'è½¦è¾†', IF ( 0 != nFlag, 'è¿›å…¥', 'ç¦»å¼€' ), 'è®°å½•æ“ä½œæˆåŠŸã€‚' );
	#set txtXml = CONCAT( '{"LocationID":"', strLocationID, '", "State":"', CONVERT( nFlag, CHAR ), '"}' ); # RemoveRecord


END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `TabletNormalRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `TabletNormalRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN

	#ExtractValue( '<Data><a>test</a></Record>', 'Data/a' );
	# strRecord <Data><LocationID/><Plate>å·A12345</Plate><Pay>10</Pay><Operator>å¼ ä¸‰</Operaor><Time>2013-03-15 12:12:34</Time><Image/></Data>
	declare strLocationID VARCHAR( 16 ) default ExtractValue( txtXml, 'Data/LocationID' );
	declare strPlate VARCHAR( 45 ) default ExtractValue( txtXml, 'Data/Plate' );
	declare strPay VARCHAR( 45 ) default ExtractValue( txtXml, 'Data/Pay' );
	declare strOperator VARCHAR( 45 ) default ExtractValue( txtXml, 'Data/Operator' );
	declare strTime VARCHAR( 45 ) default ExtractValue( txtXml, 'Data/Time' );
	declare image LONGBLOB default FROM_BASE64( ExtractValue( txtXml, 'Data/Image' ) );
	declare strUserID VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/UserID' );

	declare strExistPlate VARCHAR( 45 ) default null;
	declare nRecordID BIGINT UNSIGNED default null;

	select GetLocationIDByDetectorID( strLocationID ) into strLocationID;

	if ( ISNULL( strLocationID ) || 0 = LENGTH( strLocationID ) ) then
		set txtXml = '{"Message":"è½¦ä½å·ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	select RecordID into nRecordID from TabLocationHaveCarInfo where LocationID = strLocationID;

	if ( nRecordID is null  ) then
		set nFlag = -1; -- left
		set txtXml = '{"Message":"è¯¥è½¦å·²ç¦»å¼€è®°å½•å·²ç»è¢«å¤„ç†ã€‚"}';
		Leave EXITBODY;
	end if;
	
	if ( 1 = nFlag ) then -- Enter
begin
#declare EXIT HANDLER FOR SQLSTATE '23000' ROLLBACK;
		select EnterPlate into strExistPlate from TabInOutRecordInfo where RecordID = nRecordID and EnterPlate is not NULL;
		if ( strExistPlate is not null ) then #Exists( Select ... )
			set nFlag = -1; -- entered
			set txtXml = '{"Message":"è¯¥è½¦è¿›å…¥è®°å½•å·²ç»è¢«å¤„ç†ã€‚"}';
			Leave EXITBODY;
		end if;

		start transaction;
		update TabInOutRecordInfo set EnterPlate = strPlate where RecordID = nRecordID; -- æœªçŸ¥
		insert into TabInOutImageInfo ( RecordID, EnterImage, AddedTime ) values( nRecordID, image, DATE( strTime ) );
		insert into TabFeeInfo( RecordID, Prepayment, PrepaymentOperator, PrepaymentTime, PrepaymentUserID ) 
						   VALUES( nRecordID, strPay, strOperator, strTime, strUserID );

		update TabLocationHaveCarInfo set Prepayment = strPay where LocationID = strLocationID;
		commit;
end;
	else if ( 0 = nFlag ) then -- Leave
begin
#declare EXIT HANDLER FOR SQLSTATE '23000' ROLLBACK;
			select LeavePlate into strExistPlate from TabInOutRecordInfo where RecordID = nRecordID and LeavePlate is not NULL;
			if ( strExistPlate is not null ) then
				set nFlag = -1; -- left
				set txtXml = '{"Message":"è¯¥è½¦å·²ç¦»å¼€è®°å½•å·²ç»è¢«å¤„ç†ã€‚"}';
				Leave EXITBODY;
			end if;

			start transaction;
			delete from TabLocationHaveCarInfo where RecordID = nRecordID;
			update TabInOutRecordInfo set LeavePlate = strPlate where RecordID = nRecordID; -- æœªçŸ¥
			update TabInOutImageInfo set LeaveImage = image where RecordID = nRecordID;
			update TabFeeInfo set Payment = strPay, PaymentOperator = strOperator, 
							  PaymentTime = strTime, PaymentUserID = strUserID 
					where RecordID = nRecordID;
			commit;
end;
		end if;
	end if;

	set txtXml = UpdateXML( txtXml, '/Data/Image', '<Image/>' );
	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( txtXml, ' SP:TabletNormalRecord' ), NOW( ) );
	set txtXml = CONCAT( '{"LocationID":"', strLocationID, '", "State":"', CONVERT( nFlag, CHAR ), '"}' ); #RemoveRcord


END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `TransferTmpRecord2History` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `TransferTmpRecord2History`(  )
EXITBODY:
BEGIN
	declare Exit /*continue undo è¯­å¥æ‰§è¡Œåé‡‡å–çš„åŠ¨ä½œ*/ 
		Handler for SQLEXCEPTION /*sqlstate, sqlwarning, not found, condition_name*/
		begin #å‡ºç°æ»¡è¶³çš„å¼‚å¸¸åï¼Œè¦æ‰§è¡Œçš„è¯­å¥
			show warnings;
			rollback;
		end;

	#è·å–å®Œæ•´è¿›å‡ºè®°å½•çš„RecordID
	Create temporary table if not exists TabRecordID
		( RecordID bigint unsigned NOT NULL, PRIMARY KEY (  RecordID ) ) ENGINE = InnoDB;
	delete From TabRecordID;
	Insert Into TabRecordID( RecordID ) 
			select RecordID From TabTmpInOutRecordInfo where LeavePlate is not null; #å®Œæ•´è®°å½•

	if ( 0 < ( select count( * ) from TabRecordID ) ) then
		start transaction;
			#è¿›å‡ºä¿¡æ¯
			INSERT INTO TabHistoryInOutRecordInfo ( RecordID, LocationID, EnterTime, LeaveTime, EnterPlate, LeavePlate )
				SELECT a.RecordID, LocationID, EnterTime, LeaveTime, EnterPlate, LeavePlate 
					From TabTmpInOutRecordInfo a, TabRecordID b
					Where a.RecordID = b.RecordID
			   ON DUPLICATE KEY UPDATE
				EnterTime = IFNULL( a.EnterTime, TabHistoryInOutRecordInfo.EnterTime ), LeaveTime = IFNULL( a.LeaveTime, TabHistoryInOutRecordInfo.LeaveTime ), 
				EnterPlate = IFNULL( a.EnterPlate, TabHistoryInOutRecordInfo.EnterPlate ), LeavePlate = IFNULL( a.LeavePlate, TabHistoryInOutRecordInfo.LeavePlate );

			#è¿›å‡ºå›¾åƒ
			INSERT INTO TabHistoryInOutImageInfo( RecordID, EnterImage, LeaveImage, AddedTime ) 
				SELECT a.RecordID, EnterImage, LeaveImage, AddedTime 
					From TabTmpInOutImageInfo a, TabRecordID b
					Where a.RecordID = b.RecordID
			   ON DUPLICATE KEY UPDATE
				EnterImage = IFNULL( a.EnterImage, TabHistoryInOutImageInfo.EnterImage ), LeaveImage = IFNULL( a.LeaveImage, TabHistoryInOutImageInfo.LeaveImage );

			#æ”¶è´¹ä¿¡æ¯
			INSERT INTO TabHistoryFeeInfo( RecordID, Prepayment, PrepaymentOperator, PrepaymentTime, PrepaymentUserID, 
										   Payment, PaymentOperator, PaymentTime, PaymentUserID ) 
				SELECT a.RecordID, Prepayment, PrepaymentOperator, PrepaymentTime, PrepaymentUserID, 
										   Payment, PaymentOperator, PaymentTime, PaymentUserID
					From TabTmpFeeInfo a, TabRecordID b
					Where a.RecordID = b.RecordID
			   ON DUPLICATE KEY UPDATE
				Prepayment = IFNULL( a.Prepayment, TabHistoryFeeInfo.Prepayment ), 
				PrepaymentOperator = IFNULL( a.PrepaymentOperator, TabHistoryFeeInfo.PrepaymentOperator ),
				PrepaymentTime = IFNULL( a.PrepaymentTime, TabHistoryFeeInfo.PrepaymentTime ),
				PrepaymentUserID = IFNULL( a.PrepaymentUserID, TabHistoryFeeInfo.PrepaymentUserID ),
				Payment = IFNULL( a.Payment, TabHistoryFeeInfo.Payment ),
				PaymentOperator = IFNULL( a.PaymentOperator, TabHistoryFeeInfo.PaymentOperator ),
				PaymentTime = IFNULL( a.PaymentTime, TabHistoryFeeInfo.PaymentTime ),
				PaymentUserID = IFNULL( a.PaymentUserID, TabHistoryFeeInfo.PaymentUserID );

			#åˆ é™¤è¿›å‡ºè®°å½•æ•°æ®ï¼ŒTabTmpInOutRecordInfoçš„åˆ é™¤è§¦å‘å™¨åˆ é™¤ç›¸å…³çš„å›¾åƒé¢„æ”¶è´¹ä¿¡æ¯
			#Delete a.*, b.* From TabTmpInOutRecordInfo a, TabRecordID b where a.RecordID = b.RecordID; æ³¨æ„è¯­æ³•
			Delete a.* From TabTmpInOutRecordInfo a, TabRecordID b where a.RecordID = b.RecordID;

			#æ—¥å¿—
			INSERT INTO TabHistoryLogInfo ( LogID, LogInfo, LogDateTime )
				SELECT LogID, LogInfo, LogDateTime From TabTmpLogInfo;
			Delete From TabTmpLogInfo;

			#ç™»å½•æ—¥å¿—
			INSERT INTO TabHistoryUserLoginoutInfo ( LogID, LogUserID, LogTime, LogType, LogClientID, LogIP )
				SELECT LogID, LogUserID, LogTime, LogType, LogClientID, LogIP From TabTmpUserLoginoutInfo;
			Delete From TabTmpUserLoginoutInfo;
		commit;
	end if;

	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( 'å®šæ—¶è½¬ç§»è¿›å‡ºè®°å½•æ•°æ® ', ' SP:TransferTmpRecord2History' ), NOW( ) );
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `UnhandledSensorRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `UnhandledSensorRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#IP@ClientID@Serial@Credit@Type
	#<Data><LocationID/><Accessor/><Data>
	declare strLocationID VARCHAR( 16 ) default ExtractValue( txtXml, 'Data/LocationID' );
	declare bAll boolean default FALSE;

	declare strIn LONGTEXT default null; 
	declare strOut LONGTEXT default null;
	declare nRecordID BIGINT UNSIGNED default null;
	declare dtLeaveTime DATETIME default null;
	declare strEnterPlate VARCHAR( 16 ) default null;
	declare strLeavePlate VARCHAR( 16 ) default null;

	select GetLocationIDByDetectorID( strLocationID ) into strLocationID;

	if ( ISNULL( strLocationID ) || 0 = LENGTH( strLocationID ) ) then
		set txtXml = '{"Message":"è½¦ä½å·ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	set bAll = ( '0' = strLocationID );

	if ( bAll is FALSE ) then
		select RecordID into nRecordID from TabLocationHaveCarInfo where LocationID = strLocationID;
	else
		select count( RecordID ) into nRecordID from TabLocationHaveCarInfo;
	end if;

	if ( nRecordID is null || 0 = nRecordID ) then
		set txtXml = '{"Message":"æ²¡æœ‰æœªå¤„ç†çš„ä¼ æ„Ÿå™¨è¿›å‡ºè®°å½•ã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY;
	end if;

	if ( bAll ) then
			if ( ( select count( * ) from TabInOutRecordInfo a, TabLocationHaveCarInfo b 
				   where a.RecordID =  b.RecordID and a.EnterPlate is null ) <> 0 ) then #å¹³æ¿æœªå¤„ç†è¿›å…¥
				set strIn = ( select 
							GROUP_CONCAT( CONCAT( '{"LocationID":"', b.LocationID, '",' ),
										  CONCAT( '"State":"1",' ),
										  CONCAT( '"EnterTime":"', b.EnterTime, '"}' ) ) 
							 from TabInOutRecordInfo a, TabLocationHaveCarInfo b where a.RecordID =  b.RecordID and a.EnterPlate is null );
			end if;

			if ( ( select count( * ) from TabInOutRecordInfo a, TabLocationHaveCarInfo b  
					where a.RecordID =  b.RecordID and a.LeaveTime is not null and a.LeavePlate is null ) <> 0 ) then
				set strOut = ( select 
						GROUP_CONCAT( CONCAT( '{"LocationID":"', b.LocationID, '",' ),
									  CONCAT( '"State":"0",' ),
									  CONCAT( '"Prepayment":"', b.Prepayment, '",' ),
									  CONCAT( '"EnterTime":"', b.EnterTime, '",' ),
									  CONCAT( '"LeaveTime":"', IFNULL( b.LeaveTime, '' ), '"}' ) )
						from TabInOutRecordInfo a, TabLocationHaveCarInfo b 
						where a.RecordID =  b.RecordID and a.LeaveTime is not null 
							  and a.LeavePlate is null );
			end if;
	else
		begin
			select EnterPlate, LeavePlate, LeaveTime into strEnterPlate, strLeavePlate, dtLeaveTime 
			from TabInOutRecordInfo where RecordID =  nRecordID;

			if ( strEnterPlate is null ) then #å¹³æ¿æœªå¤„ç†è¿›å…¥
				set strIn = ( select 
							GROUP_CONCAT( CONCAT( '{"LocationID":"', LocationID, '",' ),
										  CONCAT( '"State":"1",' ),
										  CONCAT( '"EnterTime":"', EnterTime, '"}' ) ) 
							 from TabLocationHaveCarInfo where LocationID = strLocationID );
			end if;
			
			if ( strLeavePlate is null and dtLeaveTime is not null ) then
				set strOut = ( select 
						GROUP_CONCAT( CONCAT( '{"LocationID":"', LocationID, '",' ),
									  CONCAT( '"State":"0",' ),
									  CONCAT( '"Prepayment":"', Prepayment, '",' ),
									  CONCAT( '"EnterTime":"', EnterTime, '",' ),
									  CONCAT( '"LeaveTime":"', IFNULL( LeaveTime, '' ), '"}' ) )
						from TabLocationHaveCarInfo where LocationID = strLocationID );
			end if;
		end;
	end if;


	if ( strIn is not null && strOut is not null ) then
		set txtXml = CONCAT( '{"List":[', strIn, ',', strOut, ']}' );
	elseif ( strIn is null ) then
			set txtXml = CONCAT( '{"List":[', strOut, ']}' );
	elseif ( strOut is null ) then
			set txtXml = CONCAT( '{"List":[', strIn, ']}' );
	end if;

	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( txtXml, ' SP:UnhandledSensorRecord' ), NOW( ) );

	if ( txtXml is null ) then
		set txtXml = CONCAT( '{"Message":"æŸ¥è¯¢æ— è®°å½•æ•°æ®ã€‚"}' );
		set nFlag = -1;
	end if;
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `UploadInOutRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `UploadInOutRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#å¤šè¡Œ
	#<Data><Row><LocationID/><State/><RecordID/><EnterTime/><LeaveTime/><Prepayment/><Payment/> 
	#<EnterPlate/><LeavePlate/><PrepaymentOperator/><PaymentOperator/><EnterImage/>
	#<LeaveImage/><PrepaymentTime/><PaymentTime/><PrepaymentUserID/><PaymentUserID/></Row></Data>
	
	declare strLocationID VARCHAR( 45 ) default null;
	declare strState VARCHAR( 45 ) default null;
	declare strRecordID VARCHAR( 45 ) default null;
	declare strEnterTime VARCHAR( 45 ) default null;
	declare strLeaveTime VARCHAR( 45 ) default null;
	declare strPrepayment VARCHAR( 45 ) default null;
	declare strPayment VARCHAR( 45 ) default null;
	declare strEnterPlate VARCHAR( 45 ) default null;
	declare strLeavePlate VARCHAR( 45 ) default null;
	declare strPrepaymentOperator VARCHAR( 45 ) default null;
	declare strPaymentOperator VARCHAR( 45 ) default null;
	declare strEnterImage LONGBLOB default null;
	declare strLeaveImage LONGBLOB default null;
	declare strPrepaymentTime VARCHAR( 45 ) default null;
	declare strPaymentTime VARCHAR( 45 ) default null;
	declare strPrepaymentUserID VARCHAR( 45 ) default null;
	declare strPaymentUserID VARCHAR( 45 ) default null;

	declare nRows int default ExtractValue( txtXml, 'count( /Data/Row )' );
	declare nItem int default 0;
	declare txtMsg Longtext default '';
	declare bEmpty boolean default true;
	declare bSuccess boolean default true;

	declare nRecordIDCar bigint unsigned default null;
	declare nRecordIDRec bigint unsigned default null;

	declare dtEnterTime, dtLeaveTime DATETIME default now( );
	declare dtPrepaymentTime, dtPaymentTime DATETIME default now( );
	declare nPrepayment, nPayment SMALLINT UNSIGNED default 0;
	declare nPrepaymentUserID, nPaymentUserID BIGINT UNSIGNED default 0;

	declare strDateTime VARCHAR( 45 ) default null;
	declare bExistRecord bool default false;

	if ( 0 = nRows ) then
		SET nFlag = -1;
		SET txtXml = 'æ— æœ‰æ•ˆæ•°æ®è¡Œã€‚';
		lEAVE EXITBODY;
	end if;

	MYLOOP: while ( nItem < nRows ) do
		set nItem = nItem + 1;

		set strLocationID = ExtractValue( txtXml, '/Data/Row[$nItem]/LocationID' );
		select GetLocationIDByDetectorID( strLocationID ) into strLocationID;

		if ( ( ISNULL( strLocationID ) || 0 = LENGTH( strLocationID ) ) && bEmpty ) then
			set txtMsg = CONCAT( txtMsg, 'æœ‰è½¦ä½å·ä¸ºç©ºçš„æ•°æ®ã€‚' ); #ç¬¬ä¸€ä¸ªå‚æ•°ä¸èƒ½ä¸º nullï¼Œå¦åˆ™ç»“æœä¸º null
			set bEmpty = false;
			set bSuccess = false;
			Iterate MYLOOP; 
		elseif ( 16 <> LENGTH( strLocationID ) ) then
			set txtMsg = CONCAT( txtMsg, 'è½¦ä½å·é•¿åº¦ä¸æ­£ç¡®ã€LocationID = ', strLocationID, 'ã€‘ã€‚' );
			#Leave MYLOOP; break
			set bSuccess = false;
			Iterate MYLOOP; #continue
		end if;

		set strState = ExtractValue( txtXml, '/Data/Row[$nItem]/State' );
		set strRecordID = ExtractValue( txtXml, '/Data/Row[$nItem]/RecordID' );
		set strEnterTime = ExtractValue( txtXml, '/Data/Row[$nItem]/EnterTime' );
		set strLeaveTime = ExtractValue( txtXml, '/Data/Row[$nItem]/LeaveTime' );
		set strPrepayment = ExtractValue( txtXml, '/Data/Row[$nItem]/Prepayment' );
		set strPayment = ExtractValue( txtXml, '/Data/Row[$nItem]/Payment' );
		set strEnterPlate = ExtractValue( txtXml, '/Data/Row[$nItem]/EnterPlate' );
		set strLeavePlate = ExtractValue( txtXml, '/Data/Row[$nItem]/LeavePlate' );
		set strPrepaymentOperator = ExtractValue( txtXml, '/Data/Row[$nItem]/PrepaymentOperator' );
		set strPaymentOperator = ExtractValue( txtXml, '/Data/Row[$nItem]/PaymentOperator' );
		set strEnterImage = FROM_BASE64( ExtractValue( txtXml, '/Data/Row[$nItem]/EnterImage' ) );
		set strLeaveImage = FROM_BASE64( ExtractValue( txtXml, '/Data/Row[$nItem]/LeaveImage' ) );
		set strPrepaymentTime = ExtractValue( txtXml, '/Data/Row[$nItem]/PrepaymentTime' );
		set strPaymentTime = ExtractValue( txtXml, '/Data/Row[$nItem]/PaymentTime' );
		set strPrepaymentUserID = ExtractValue( txtXml, '/Data/Row[$nItem]/PrepaymentUserID' );
		set strPaymentUserID = ExtractValue( txtXml, '/Data/Row[$nItem]/PaymentUserID' );

		select Count( * ) into bExistRecord from TabInOutRecordInfo where RecordID = strRecordID;

		case strState 
			when '-1' then #Leave
				set dtLeaveTime = CONVERT( strLeaveTime, DATETIME );
				if ( dtLeaveTime is null ) then
					set txtMsg = CONCAT( txtMsg, 'ç¦»å¼€æ—¶é—´æ ¼å¼ä¸æ­£ç¡®ã€LocationID = ', strLocationID, 
										 ' LeaveTime = ', strLeaveTime, 'ã€‘ã€‚' );
					set bSuccess = false;
					Iterate MYLOOP;
				end if;

				set dtPaymentTime = CONVERT( strPaymentTime, DATETIME );
				if ( dtPaymentTime is null ) then
					set txtMsg = CONCAT( txtMsg, 'æ”¶è´¹æ—¶é—´æ ¼å¼ä¸æ­£ç¡®ã€LocationID = ', strLocationID, 
										 ' PaymentTime = ', strPaymentTime, 'ã€‘ã€‚' );
					set bSuccess = false;
					Iterate MYLOOP;
				end if;

				set nPrepayment = CONVERT( strPrepayment, UNSIGNED );
				set nPayment = CONVERT( strPayment, UNSIGNED );
				
				set nPrepaymentUserID = CONVERT( strPrepaymentUserID, UNSIGNED );
				set nPaymentUserID = CONVERT( strPaymentUserID, UNSIGNED );
				
				set strDateTime = '2000-01-01 12:01:01';
				#nRecordID is null è¯¥è½¦ä½è¿˜æ²¡æ–°è½¦è¿›å…¥ï¼Œåä¹‹æœ‰
				#æ˜¯å‡è®¾æ‰€æœ‰è¿›å‡ºè®°å½•éƒ½æ˜¯å®Œæ•´çš„æƒ…å†µä¸‹æ‰å¯èƒ½æ­£ç¡®
				start transaction;
				select RecordID into nRecordIDCar from TabLocationHaveCarInfo where LocationID = strLocationID;
				select RecordID into nRecordIDRec from TabInOutRecordInfo where LocationID = strLocationID and 
				EnterTime is not null and EnterPlate is not null and
				LeaveTime is null and LeavePlate is null and RecordID <> nRecordIDCar;

				if ( nRecordIDRec is not null ) then #æ‰¾åˆ°è¿›å…¥è®°å½•
					Update TabInOutRecordInfo set LeaveTime = dtLeaveTime, LeavePlate = Left( strLeavePlate, 8 ) where RecordID = nRecordIDRec;
					Update TabInOutImageInfo set LeaveImage = strLeaveImage where RecordID = nRecordIDRec; 
					Update TabFeeInfo Set Payment = nPayment, PaymentTime = dtPaymentTime, PaymentUserID = nPaymentUserID, PaymentOperator = Left( strPaymentOperator, 30 )
					Where RecordID = nRecordIDRec;
				else #æ— å¯¹åº”è¿›å…¥è®°å½•
					Insert TabInOutRecordInfo( LocationID, EnterTime, LeaveTime, EnterPlate, LeavePlate ) 
					Value( strLocationID, strDateTime, dtLeaveTime, Left( strEnterPlate, 8 ), Left( strLeavePlate, 8 ) );
					set nRecordIDRec = LAST_INSERT_ID( );

					Insert TabInOutImageInfo( RecordID, EnterImage, LeaveImage, AddedTime ) 
					Value( nRecordIDRec, strEnterImage, strLeaveImage, DATE( strDateTime ) );

					Insert TabFeeInfo( RecordID, Prepayment, Payment, PrepaymentTime, PaymentTime, 
									   PrepaymentOperator, PaymentOperator, PrepaymentUserID, PaymentUserID ) 
					Value( nRecordIDRec, nPrepayment, nPayment, strDateTime, dtPaymentTime, 
						   Left( strPrepaymentOperator, 30 ), Left( strPaymentOperator, 30 ), 
						   nPrepaymentUserID, nPaymentUserID );
				end if;
				commit;
			when '1' then #Enter
				if ( strEnterTime is not null && LENGTH( strEnterTime ) <> 0 ) then
					set dtEnterTime = CONVERT( strEnterTime, DATETIME );
				end if;

				if ( strPrepaymentTime is not null && LENGTH( strPrepaymentTime ) <> 0 ) then
					set dtPrepaymentTime = CONVERT( strPrepaymentTime, DATETIME );
				end if;

				if ( strPrepayment is not null && LENGTH( strPrepayment ) <> 0 ) then
					set nPrepayment = CONVERT( strPrepayment, UNSIGNED );
				end if;

				if ( strPayment is not null && LENGTH( strPayment ) <> 0 ) then
					set nPayment = CONVERT( strPayment, UNSIGNED );
				end if;

				if ( strPrepaymentUserID is not null && LENGTH( strPrepaymentUserID ) <> 0 ) then
					set nPrepaymentUserID = CONVERT( strPrepaymentUserID, UNSIGNED );
				end if;

				if ( strPaymentUserID is not null && LENGTH( strPaymentUserID ) <> 0 ) then
					set nPaymentUserID = CONVERT( strPaymentUserID, UNSIGNED );
				end if;

				set strDateTime = '3000-01-01 12:01:01';

				start transaction;
				if ( !bExistRecord ) then
					Insert TabInOutRecordInfo( LocationID, EnterTime, LeaveTime, EnterPlate, LeavePlate ) 
					Value( strLocationID, dtEnterTime, strDateTime, Left( strEnterPlate, 8 ), Left( strLeavePlate, 8 ) );
					set nRecordIDRec = LAST_INSERT_ID( );

					Insert TabInOutImageInfo( RecordID, EnterImage, LeaveImage, AddedTime ) 
					Value( nRecordIDRec, strEnterImage, strLeaveImage, DATE( dtEnterTime ) );

					Insert TabFeeInfo( RecordID, Prepayment, Payment, PrepaymentTime, PaymentTime, 
									   PrepaymentOperator, PaymentOperator, PrepaymentUserID, PaymentUserID ) 
					Value( nRecordIDRec, nPrepayment, nPayment, dtPrepaymentTime, strDateTime, 
						   Left( strPrepaymentOperator, 30 ), Left( strPaymentOperator, 30 ), 
						   nPrepaymentUserID, nPaymentUserID );
				else 
					update TabInOutRecordInfo set LocationID = strLocationID, EnterTime = dtEnterTime, LeaveTime = strDateTime,
						                      EnterPalte = Left( strEnterPlate, 8 ), LeavePlate = Left( strEnterPlate, 8 )
						   where RecordID = strRecordID;
					
					update TabInOutImageInfo set EnterImage = strEnterImage, LeaveImage = strLeaveImage
						   where RecordID = strRecordID;

					update TabFeeInfo set Prepayment = nPrepayment, Payment = nPayment, 
                                      PrepaymentTime = dtPrepaymentTime, PaymentTime = strDateTime, 
									  PrepaymentOperator = Left( strPrepaymentOperator, 30 ), 
                                      PaymentOperator = Left( strPaymentOperator, 30 ), 
                                      PrepaymentUserID = nPrepaymentUserID, PaymentUserID = nPaymentUserID
                           where RecordID = strRecordID; 
				end if;
				commit;
			when '0' then #Whole
				if ( strEnterTime is not null && LENGTH( strEnterTime ) <> 0 ) then
					set dtEnterTime = CONVERT( strEnterTime, DATETIME );
				end if;

				if ( strLeaveTime is not null && LENGTH( strLeaveTime ) <> 0 ) then
					set dtLeaveTime = CONVERT( strLeaveTime, DATETIME );
				end if;

				if ( strPrepaymentTime is not null && LENGTH( strPrepaymentTime ) <> 0 ) then
					set dtPrepaymentTime = CONVERT( strPrepaymentTime, DATETIME );
				end if;

				if ( strPaymentTime is not null && LENGTH( strPaymentTime ) <> 0 ) then
					set dtPaymentTime = CONVERT( strPaymentTime, DATETIME );
				end if;

				if ( strPrepayment is not null && LENGTH( strPrepayment ) <> 0 ) then
					set nPrepayment = CONVERT( strPrepayment, UNSIGNED );
				end if;

				if ( strPayment is not null && LENGTH( strPayment ) <> 0 ) then
					set nPayment = CONVERT( strPayment, UNSIGNED );
				end if;

				if ( strPrepaymentUserID is not null && LENGTH( strPrepaymentUserID ) <> 0 ) then
					set nPrepaymentUserID = CONVERT( strPrepaymentUserID, UNSIGNED );
				end if;

				if ( strPaymentUserID is not null && LENGTH( strPaymentUserID ) <> 0 ) then
					set nPaymentUserID = CONVERT( strPaymentUserID, UNSIGNED );
				end if;

				start transaction;
				if ( !bExistRecord ) then
					Insert TabInOutRecordInfo( LocationID, EnterTime, LeaveTime, EnterPlate, LeavePlate ) 
					Value( strLocationID, dtEnterTime, dtLeaveTime, Left( strEnterPlate, 8 ), Left( strLeavePlate, 8 ) );
					set nRecordIDRec = LAST_INSERT_ID( );

					Insert TabInOutImageInfo( RecordID, EnterImage, LeaveImage, AddedTime ) 
					Value( nRecordIDRec, strEnterImage, strLeaveImage, DATE( dtEnterTime ) );

					Insert TabFeeInfo( RecordID, Prepayment, Payment, PrepaymentTime, PaymentTime, 
									   PrepaymentOperator, PaymentOperator, PrepaymentUserID, PaymentUserID ) 
					Value( nRecordIDRec, nPrepayment, nPayment, dtPrepaymentTime, dtPaymentTime, 
						   Left( strPrepaymentOperator, 30 ), Left( strPaymentOperator, 30 ), 
						   nPrepaymentUserID, nPaymentUserID );
				else 
					Update TabInOutRecordInfo set LocationID = strLocationID, EnterTime = dtEnterTime, LeaveTime = dtLeaveTime, 
                                                  EnterPlate = Left( strEnterPlate, 8 ) , LeavePlate = Left( strLeavePlate, 8 ) 
                           where RecordID = strRecordID;
					update TabInOutImageInfo set EnterImage = strEnterImage, LeaveImage = strLeaveImage
						   where RecordID = strRecordID;
					update TabFeeInfo set Prepayment = nPrepayment, Payment = nPayment, 
                                      PrepaymentTime = dtPrepaymentTime, PaymentTime = dtPaymentTime, 
									  PrepaymentOperator = Left( strPrepaymentOperator, 30 ), 
                                      PaymentOperator = Left( strPaymentOperator, 30 ), 
                                      PrepaymentUserID = nPrepaymentUserID, PaymentUserID = nPaymentUserID
                           where RecordID = strRecordID; 
				end if;
				commit;
			else 
				set txtMsg = CONCAT( txtMsg, 'æœªçŸ¥çŠ¶æ€æ•°æ®ã€State = ', strState, 'ã€‘ã€‚' );
				set bSuccess = false;
		end case;
		
	end while;


	if ( !bSuccess ) then
		set txtXml = txtMsg;
		set nFlag = -1;
	else
		set nFlag = 0;
		set txtXml = null;
	end if;
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `UserRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `UserRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#<Data><GroupID/><Accessor/><Data> UserSelect
	#<Data><UserID/><UserOldPwd/><PwdOldMD5/><UserNewPwd/><PwdNewMD5/><Accessor/><Data> UserUpdate

	declare strGroupID VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/GroupID' );
	declare strUserID VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/UserID' );
	declare strUserName VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/UserName' );
	declare strUserPwd VARCHAR( 128 ) default ExtractValue( txtXml, '/Data/UserPwd' ); #Base64
	declare strPwdMD5 VARCHAR( 512 ) default ExtractValue( txtXml, '/Data/PwdMD5' );
	declare strUserNewPwd VARCHAR( 128 ) default ExtractValue( txtXml, '/Data/UserNewPwd' );
	declare strPwdNewMD5 VARCHAR( 512 ) default ExtractValue( txtXml, '/Data/PwdNewMD5' );

	declare dtFeeStart VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/StartTime' );
	declare dtFeeEnd VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/EndTime' );

	declare strTabUserName VARCHAR( 45 );
	declare strTabUserPwd VARCHAR( 128 );

	declare strMsg LONGTEXT default '';

	declare nPrepaymentSum SMALLINT unsigned default 0;
	declare nPaymentSum SMALLINT unsigned default 0;


	case nFlag when 0 then #UserSelect
				set txtXml = ( Select CONCAT( '{"List":[',
											   GROUP_CONCAT( CONCAT( '{"GroupID":"',GroupID,'"' ),
													         CONCAT( ',"UserID":"', UserID, '"' ),
															 CONCAT( ',"UserName":"', UserName, '"' ),
															 CONCAT( ',"UserPwd":"', UserPwd, '"'),
															 CONCAT( ',"UserPwd":"', UserJobNumber, '"'),
															 CONCAT( ',"UserPwd":"', UserAddress, '"'),
															 CONCAT( ',"PwdMD5":"', MD5( FROM_BASE64( UserPwd ) ), '"}' ), ']}' ) ) 
				   From TabUserInfo Where GroupID =  strGroupID );

			    set nFlag = ( 0 != FOUND_ROWS( ) );
				
				if ( nFlag is FALSE ) then  #SELECT 1 IS TRUE, 0 IS FALSE, NULL IS UNKNOWN;
					set txtXMl = CONCAT( '{"Message":"è¯¥ç»„ä¸å­˜åœ¨ã€‚"}' );
					set nFlag = -1;
				end if;
			   when 1 then #UserUpdate
				select UserName, UserPwd into strTabUserName, strTabUserPwd from TabUserInfo where UserID = strUserID;

				if ( strTabUserName <> strUserName ) then
					set strMsg = 'ç”¨æˆ·ä¸å­˜åœ¨ã€‚';
				end if;

				if ( MD5( FROM_BASE64( strUserPwd ) ) <> strPwdMD5 ) then 
					set strMsg = CONCAT( strMsg, '\nåŸå¯†ç æ ¡éªŒé”™è¯¯ã€‚' );
				end if;

				if ( MD5( FROM_BASE64( strUserNewPwd ) ) <> strPwdNewMD5 ) then 
					set strMsg = CONCAT( strMsg, '\næ–°å¯†ç æ ¡éªŒé”™è¯¯ã€‚' );
				end if;

				if ( strTabUserPwd <> strUserPwd ) then
					set strMsg = CONCAT( strMsg, '\nåŸå¯†ç é”™è¯¯ã€‚' );
				end if;

				set nFlag = ( 0 = CHAR_LENGTH( strMsg ) );

				if ( 0 = nFlag ) then
					set txtXml = CONCAT( '{"Message":"', strMsg, '"}' );
					set nFlag = -1;
				else
					update TabUserInfo set UserPwd = strUserNewPwd where UserID = strUserID;
					set txtXml = CONCAT( 'ç”¨æˆ·ä¿®æ”¹å¯†ç æˆåŠŸã€‚' );
				end if;
			   when 2 then #UserLogin <IP/><ClientID/><TypeCode/>
				select UserName, UserPwd into strTabUserName, strTabUserPwd from TabUserInfo where UserID = strUserID;

				if ( strTabUserName <> strUserName ) then
					set strMsg = 'ç”¨æˆ·ä¸å­˜åœ¨ã€‚';
				end if;

				if ( MD5( FROM_BASE64( strUserPwd ) ) <> strPwdMD5 ) then 
					set strMsg = CONCAT( strMsg, '\nåŸå¯†ç æ ¡éªŒé”™è¯¯ã€‚' );
				end if;

				if ( strTabUserPwd <> strUserPwd ) then
					set strMsg = CONCAT( strMsg, '\nåŸå¯†ç é”™è¯¯ã€‚' );
				end if;

				set nFlag = ( 0 = CHAR_LENGTH( strMsg ) );

				if ( 0 != nFlag ) then
					update TabUserInfo set UserState = 'Login' where UserID = strUserID;
					Insert into TabUserLoginoutInfo( LogUserID, LogType, LogClientID, LogIP ) values( strUserID, 'Login', 
													 ExtractValue( txtXml, '/Data/Accessor/ClientID' ),
													 ExtractValue( txtXml, '/Data/Accessor/IP' ) );
					set txtXml = CONCAT( '{"Message":"ç”¨æˆ·ç™»å½•æˆåŠŸã€‚"}' );
				else 
					set txtXml = CONCAT( '{"Message":"ç”¨æˆ·ç™»å½•å¤±è´¥ã€‚' , strMsg, 'ã€‚"}' );
					set nFlag = -1;
				end if;
			   when 3 then #UserLogout
				update TabUserInfo set UserState = 'Logout' where UserID = strUserID;
				Insert into TabUserLoginoutInfo( LogUserID, LogType, LogClientID, LogIP ) values( strUserID, 'Logout', 
													 ExtractValue( txtXml, '/Data/Accessor/ClientID' ),
													 ExtractValue( txtXml, '/Data/Accessor/IP' ) );
				set txtXml = CONCAT( '{"Message":"ç”¨æˆ·æ³¨é”€æˆåŠŸã€‚"}' );
			   when 4 then #UserFee
				select sum( Prepayment ) into nPrepaymentSum from TabFeeInfo 
					where PrepaymentTime between dtFeeStart and dtFeeEnd and PrepaymentUserID = strUserID;

				select sum( Payment ) into nPaymentSum from TabFeeInfo 
					where PaymentTime between dtFeeStart and dtFeeEnd and PaymentUserID = strUserID;

				set txtXml = CONCAT( '{"PrepaymentSum":"', CONVERT( nPrepaymentSum, CHAR ), 
								     '","Payment":"', CONVERT( nPaymentSum, CHAR ), '"}' );
			   else
				set txtXml = CONCAT( '{"Message":"æ— æ•ˆç”¨æˆ·æ“ä½œç±»å‹ç ã€‚ã€TypeCode=', CONVERT( nFlag, CHAR ), 'ã€‘"}' );
				set nFlag = -1;
	end case;
	

	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( txtXml, ' SP:UserRecord' ), NOW( ) );
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `VehicleShiftRecord` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ALLOW_INVALID_DATES,ERROR_FOR_DIVISION_BY_ZERO,TRADITIONAL,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `VehicleShiftRecord`( inout txtXml LONGTEXT, inout nFlag TINYINT )
EXITBODY:
BEGIN
	#<Data><SrcLocationID/><DstLocationID/></Data>
	
	declare strSrcLocationID VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/SrcLocationID' );
	declare strDstLocationID VARCHAR( 45 ) default ExtractValue( txtXml, '/Data/DstLocationID' );

	declare dtSrcEnterTime, dtDstEnterTime, dtSrcLeaveTime DATETIME default null;
	declare nRecordID bigint unsigned default null;

	declare strDetectorID VARCHAR( 3 ) default null;

	select GetLocationIDByDetectorID( strSrcLocationID ) into strSrcLocationID;
	select GetLocationIDByDetectorID( strDstLocationID ) into strDstLocationID;

	if ( ISNULL( strSrcLocationID ) || 0 = LENGTH( strSrcLocationID ) ) then
		set txtXml = '{"Message":"æºè½¦ä½å·ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY; 
	end if;

	if ( ISNULL( strDstLocationID ) || 0 = LENGTH( strDstLocationID ) ) then
		set txtXml = '{"Message":"ç›®çš„è½¦ä½å·ä¸ºç©ºã€‚"}';
		set nFlag = -1;
		LEAVE EXITBODY; 
	end if;

	Select EnterTime, LeaveTime, RecordID into dtSrcEnterTime, dtSrcLeaveTime,  nRecordID 
	from TabLocationHaveCarInfo where LocationID = strSrcLocationID;

	set strDetectorID = RIGHT( strSrcLocationID, 3 );
	if ( dtSrcEnterTime is null ) then
		set txtXml = CONCAT( '{"Message":"è¯¥è½¦æœªè¿›å…¥ã€', strDetectorID, 'ã€‘å·æºè½¦ä½ã€‚"}' );
		set nFlag = -1;
		LEAVE EXITBODY; 
	elseif ( dtSrcLeaveTime is null ) then
		set txtXml = CONCAT( '{"Message":"è¯¥è½¦æœªç¦»å¼€ã€', strDetectorID, 'ã€‘å·æºè½¦ä½ã€‚"}' );
		set nFlag = -1;
		LEAVE EXITBODY; 
	end if;

	Select EnterTime, RecordID into dtDstEnterTime, nRecordID from TabLocationHaveCarInfo where LocationID = strDstLocationID;

	set strDetectorID = RIGHT( strDstLocationID, 3 );
	if ( dtDstEnterTime is null ) then
		set txtXml = CONCAT( '{"Message":"è¯¥è½¦æœªè¿›å…¥ã€', strDetectorID, 'ã€‘å·ç›®çš„è½¦ä½ã€‚"}' );
		set nFlag = -1;
		LEAVE EXITBODY; 
	end if;

	start transaction;
		update TabLocationHaveCarInfo set EnterTime = dtSrcEnterTime where LocationID = strDstLocationID;
		update TabInOutRecordInfo set EnterTime = dtSrcEnterTime where RecordID = nRecordID;
		delete from TabLocationHaveCarInfo where LocationID = strSrcLocationID;
	commit;

	INSERT INTO TabLogInfo( LogInfo, logDateTime ) VALUES( CONCAT( txtXml, ' SP:VehicleShiftRecord' ), NOW( ) );
	set nFlag = 2;
	set txtXml = CONCAT( '{"LocationID":"', strSrcLocationID, '", "State":"', CONVERT( nFlag, CHAR ), '"}' ); #RemoveRcord
	
END EXITBODY ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Final view structure for view `viewconfiginfo`
--

/*!50001 DROP TABLE IF EXISTS `viewconfiginfo`*/;
/*!50001 DROP VIEW IF EXISTS `viewconfiginfo`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `viewconfiginfo` AS select `a`.`DeviceID` AS `DeviceID`,`a`.`UnitID` AS `UnitID`,`b`.`UnitName` AS `UnitName`,`c`.`ParkID` AS `ParkID`,`c`.`ParkName` AS `ParkName`,`d`.`ReceiverID` AS `ReceiverID`,`d`.`ReceiverName` AS `ReceiverName` from (((`tabdeviceregisterinfo` `a` join `tabunitinfo` `b`) join `tabparkinfo` `c`) join `tabreceiverinfo` `d`) where ((`a`.`UnitID` = `b`.`UnitID`) and (`b`.`UnitID` = `c`.`UnitID`) and (`c`.`ParkID` = `d`.`ParkID`)) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `viewfeeinfo`
--

/*!50001 DROP TABLE IF EXISTS `viewfeeinfo`*/;
/*!50001 DROP VIEW IF EXISTS `viewfeeinfo`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `viewfeeinfo` AS select `a`.`RecordID` AS `RecordID`,`a`.`Prepayment` AS `Prepayment`,`a`.`Payment` AS `Payment`,`a`.`PrepaymentOperator` AS `PrepaymentOperator`,`a`.`PrepaymentTime` AS `PrepaymentTime`,`a`.`PaymentTime` AS `PaymentTime`,`a`.`PaymentOperator` AS `PaymentOperator`,`a`.`PrepaymentUserID` AS `PrepaymentUserID`,`a`.`PaymentUserID` AS `PaymentUserID`,`b`.`LocationID` AS `LocationID`,`e`.`UnitName` AS `UnitName`,`e`.`UnitID` AS `UnitID`,`f`.`AdministrativeName` AS `AdministrativeName`,`f`.`AdministrativeType` AS `AdministrativeType`,`f`.`AdministrativeID` AS `AdministrativeID`,`g`.`ParkName` AS `ParkName`,`g`.`ParkID` AS `ParkID` from ((((((`tabfeeinfo` `a` join `tabinoutrecordinfo` `b`) join `tabuserinfo` `c`) join `tabgroupinfo` `d`) join `tabunitinfo` `e`) join `tabadministrativeinfo` `f`) join `tabparkinfo` `g`) where ((`a`.`RecordID` = `b`.`RecordID`) and (`a`.`PaymentUserID` = `c`.`UserID`) and (`c`.`GroupID` = `d`.`GroupID`) and (`d`.`UnitID` = `e`.`UnitID`) and (`e`.`AdministrativeID` = `f`.`AdministrativeID`) and (`d`.`UnitID` = `g`.`UnitID`)) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `viewinoutrecord`
--

/*!50001 DROP TABLE IF EXISTS `viewinoutrecord`*/;
/*!50001 DROP VIEW IF EXISTS `viewinoutrecord`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `viewinoutrecord` AS select `a`.`RecordID` AS `RecordID`,`a`.`LocationID` AS `LocationID`,`a`.`EnterTime` AS `EnterTime`,`a`.`LeaveTime` AS `LeaveTime`,`a`.`EnterPlate` AS `EnterPlate`,`a`.`LeavePlate` AS `LeavePlate`,`b`.`EnterImage` AS `EnterImage`,`b`.`LeaveImage` AS `LeaveImage`,`c`.`Prepayment` AS `Prepayment`,`c`.`Payment` AS `Payment`,`c`.`PrepaymentOperator` AS `PrepaymentOperator`,`c`.`PrepaymentTime` AS `PrepaymentTime`,`c`.`PaymentOperator` AS `PaymentOperator`,`c`.`PaymentTime` AS `PaymentTime` from ((`tabinoutrecordinfo` `a` join `tabinoutimageinfo` `b`) join `tabfeeinfo` `c`) where ((`a`.`RecordID` = `b`.`RecordID`) and (`a`.`RecordID` = `c`.`RecordID`)) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `viewwholefeerecordquery`
--

/*!50001 DROP TABLE IF EXISTS `viewwholefeerecordquery`*/;
/*!50001 DROP VIEW IF EXISTS `viewwholefeerecordquery`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `viewwholefeerecordquery` AS select `a`.`RecordID` AS `RecordID`,`a`.`Prepayment` AS `Prepayment`,`a`.`Payment` AS `Payment`,`a`.`PrepaymentOperator` AS `PrepaymentOperator`,`a`.`PrepaymentTime` AS `PrepaymentTime`,`a`.`PaymentTime` AS `PaymentTime`,`a`.`PaymentOperator` AS `PaymentOperator`,`a`.`PrepaymentUserID` AS `PrepaymentUserID`,`a`.`PaymentUserID` AS `PaymentUserID`,`b`.`LocationID` AS `LocationID`,`e`.`UnitName` AS `UnitName`,`e`.`UnitID` AS `UnitID`,`f`.`AdministrativeName` AS `AdministrativeName`,`f`.`AdministrativeType` AS `AdministrativeType`,`f`.`AdministrativeID` AS `AdministrativeID`,`g`.`ParkName` AS `ParkName`,`g`.`ParkID` AS `ParkID` from ((((((`tabtmpfeeinfo` `a` join `tabtmpinoutrecordinfo` `b`) join `tabuserinfo` `c`) join `tabgroupinfo` `d`) join `tabunitinfo` `e`) join `tabadministrativeinfo` `f`) join `tabparkinfo` `g`) where ((`a`.`RecordID` = `b`.`RecordID`) and (`a`.`PaymentUserID` = `c`.`UserID`) and (`c`.`GroupID` = `d`.`GroupID`) and (`d`.`UnitID` = `e`.`UnitID`) and (`e`.`AdministrativeID` = `f`.`AdministrativeID`) and (`d`.`UnitID` = `g`.`UnitID`)) union select `a`.`RecordID` AS `RecordID`,`a`.`Prepayment` AS `Prepayment`,`a`.`Payment` AS `Payment`,`a`.`PrepaymentOperator` AS `PrepaymentOperator`,`a`.`PrepaymentTime` AS `PrepaymentTime`,`a`.`PaymentTime` AS `PaymentTime`,`a`.`PaymentOperator` AS `PaymentOperator`,`a`.`PrepaymentUserID` AS `PrepaymentUserID`,`a`.`PaymentUserID` AS `PaymentUserID`,`b`.`LocationID` AS `LocationID`,`e`.`UnitName` AS `UnitName`,`e`.`UnitID` AS `UnitID`,`f`.`AdministrativeName` AS `AdministrativeName`,`f`.`AdministrativeType` AS `AdministrativeType`,`f`.`AdministrativeID` AS `AdministrativeID`,`g`.`ParkName` AS `ParkName`,`g`.`ParkID` AS `ParkID` from ((((((`tabhistoryfeeinfo` `a` join `tabhistoryinoutrecordinfo` `b`) join `tabuserinfo` `c`) join `tabgroupinfo` `d`) join `tabunitinfo` `e`) join `tabadministrativeinfo` `f`) join `tabparkinfo` `g`) where ((`a`.`RecordID` = `b`.`RecordID`) and (`a`.`PaymentUserID` = `c`.`UserID`) and (`c`.`GroupID` = `d`.`GroupID`) and (`d`.`UnitID` = `e`.`UnitID`) and (`e`.`AdministrativeID` = `f`.`AdministrativeID`) and (`d`.`UnitID` = `g`.`UnitID`)) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `viewwholeinoutrecordquery`
--

/*!50001 DROP TABLE IF EXISTS `viewwholeinoutrecordquery`*/;
/*!50001 DROP VIEW IF EXISTS `viewwholeinoutrecordquery`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `viewwholeinoutrecordquery` AS select `a`.`RecordID` AS `RecordID`,`a`.`LocationID` AS `LocationID`,`a`.`EnterTime` AS `EnterTime`,`a`.`LeaveTime` AS `LeaveTime`,`a`.`EnterPlate` AS `EnterPlate`,`a`.`LeavePlate` AS `LeavePlate`,`b`.`EnterImage` AS `EnterImage`,`b`.`LeaveImage` AS `LeaveImage`,`c`.`Prepayment` AS `Prepayment`,`c`.`Payment` AS `Payment`,`c`.`PrepaymentOperator` AS `PrepaymentOperator`,`c`.`PrepaymentTime` AS `PrepaymentTime`,`c`.`PaymentOperator` AS `PaymentOperator`,`c`.`PaymentTime` AS `PaymentTime` from ((`tabtmpinoutrecordinfo` `a` join `tabtmpinoutimageinfo` `b`) join `tabtmpfeeinfo` `c`) where ((`a`.`RecordID` = `b`.`RecordID`) and (`a`.`RecordID` = `c`.`RecordID`)) union select `a`.`RecordID` AS `RecordID`,`a`.`LocationID` AS `LocationID`,`a`.`EnterTime` AS `EnterTime`,`a`.`LeaveTime` AS `LeaveTime`,`a`.`EnterPlate` AS `EnterPlate`,`a`.`LeavePlate` AS `LeavePlate`,`b`.`EnterImage` AS `EnterImage`,`b`.`LeaveImage` AS `LeaveImage`,`c`.`Prepayment` AS `Prepayment`,`c`.`Payment` AS `Payment`,`c`.`PrepaymentOperator` AS `PrepaymentOperator`,`c`.`PrepaymentTime` AS `PrepaymentTime`,`c`.`PaymentOperator` AS `PaymentOperator`,`c`.`PaymentTime` AS `PaymentTime` from ((`tabhistoryinoutrecordinfo` `a` join `tabhistoryinoutimageinfo` `b`) join `tabhistoryfeeinfo` `c`) where ((`a`.`RecordID` = `b`.`RecordID`) and (`a`.`RecordID` = `c`.`RecordID`)) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `viewwholelogrecordquery`
--

/*!50001 DROP TABLE IF EXISTS `viewwholelogrecordquery`*/;
/*!50001 DROP VIEW IF EXISTS `viewwholelogrecordquery`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `viewwholelogrecordquery` AS select `tabtmploginfo`.`LogID` AS `LogID`,`tabtmploginfo`.`LogInfo` AS `LogInfo`,`tabtmploginfo`.`LogDateTime` AS `LogDateTime` from `tabtmploginfo` union select `tabhistoryloginfo`.`LogID` AS `LogID`,`tabhistoryloginfo`.`LogInfo` AS `LogInfo`,`tabhistoryloginfo`.`LogDateTime` AS `LogDateTime` from `tabhistoryloginfo` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `viewwholeuserloginoutrecordquery`
--

/*!50001 DROP TABLE IF EXISTS `viewwholeuserloginoutrecordquery`*/;
/*!50001 DROP VIEW IF EXISTS `viewwholeuserloginoutrecordquery`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `viewwholeuserloginoutrecordquery` AS select `tabtmpuserloginoutinfo`.`LogID` AS `LogID`,`tabtmpuserloginoutinfo`.`LogUserID` AS `LogUserID`,`tabtmpuserloginoutinfo`.`LogTime` AS `LogTime`,`tabtmpuserloginoutinfo`.`LogType` AS `LogType`,`tabtmpuserloginoutinfo`.`LogClientID` AS `LogClientID`,`tabtmpuserloginoutinfo`.`LogIP` AS `LogIP` from `tabtmpuserloginoutinfo` union select `tabhistoryuserloginoutinfo`.`LogID` AS `LogID`,`tabhistoryuserloginoutinfo`.`LogUserID` AS `LogUserID`,`tabhistoryuserloginoutinfo`.`LogTime` AS `LogTime`,`tabhistoryuserloginoutinfo`.`LogType` AS `LogType`,`tabhistoryuserloginoutinfo`.`LogClientID` AS `LogClientID`,`tabhistoryuserloginoutinfo`.`LogIP` AS `LogIP` from `tabhistoryuserloginoutinfo` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-08-06 15:25:11
