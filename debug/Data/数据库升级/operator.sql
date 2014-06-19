CREATE DATABASE  IF NOT EXISTS `parkadmin` /*!40100 DEFAULT CHARACTER SET gb2312 */;
USE `parkadmin`;
-- MySQL dump 10.13  Distrib 5.5.9, for Win32 (x86)
--
-- Host: 192.168.1.51    Database: parkadmin
-- ------------------------------------------------------
-- Server version	5.5.11

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
INSERT INTO `operator` VALUES (1,'系统管理员','','男','','85236997123456',-1,0,-1,-1,0,0,'超级用户',-1,-1,NULL,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,'18804'),(2,'胡建','','男','','aaa',-1,0,-1,-1,0,0,'普通用户',-1,-1,NULL,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,''),(3,'李四','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,''),(4,'前门一班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'9077842'),(5,'前门二班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'9081965'),(6,'前门三班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'9082624'),(7,'后门一班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'9094329'),(8,'后门二班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'9426423'),(9,'南门一班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'9137970'),(10,'南门二班','','男','','aaa',0,0,0,0,0,0,'普通用户',0,0,NULL,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'9481971');
/*!40000 ALTER TABLE `operator` ENABLE KEYS */;
UNLOCK TABLES;

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

-- Dump completed on 2011-12-16 14:43:30
