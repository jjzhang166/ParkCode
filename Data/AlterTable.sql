History
delimiter $$

CREATE TABLE `stoprd` (
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
) ENGINE=InnoDB AUTO_INCREMENT=472 DEFAULT CHARSET=gb2312
/*!50100 PARTITION BY LINEAR HASH (Day( intime ) mod 5)
PARTITIONS 7 */$$



;MySQL Restart
SET GLOBAL EVENT_SCHEDULER = TRUE


delimiter $$

CREATE TABLE `license` (
  `AdministrativeID` varchar(50) NOT NULL COMMENT '(区号) + 停车场编号\n\n510107 + 0001\n\n510107 + 9999',
  `KeyContent` blob,
  PRIMARY KEY (`AdministrativeID`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312$$

delimiter $$

CREATE TABLE `tmpcardintime` (
  `idtmpcardintime` int(11) NOT NULL AUTO_INCREMENT,
  `cardno` varchar(45) NOT NULL,
  `intime` datetime NOT NULL,
  `invideo1` longblob,
  PRIMARY KEY (`idtmpcardintime`)
) ENGINE=InnoDB AUTO_INCREMENT=46 DEFAULT CHARSET=gb2312$$

delimiter $$

delimiter $$

CREATE TABLE `parkdongleinfo` (
  `AdministrativeID` varchar(50) NOT NULL,
  `BriefName` varchar(256) NOT NULL,
  `DongleHID` varbinary(2048) DEFAULT NULL,
  PRIMARY KEY (`AdministrativeID`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312$$








use parkadmin;
alter table monthcard add column( Inside INT( 10 ) default 0, EnterMustCard INT( 10 ) default 0, LeaveMustCard INT( 10 ) default 0 ); 
alter table savecard add column( Inside INT( 10 ) default 0, EnterMustCard INT( 10 ) default 0, LeaveMustCard INT( 10 ) default 0 ); 
alter table tmpcard add column( Inside INT( 10 ) default 0, EnterMustCard INT( 10 ) default 0, LeaveMustCard INT( 10 ) default 0 ); 
alter table userinfo add column( Comments varchar( 250 ) default "" ); 
alter table stoprd add column( carcpout varchar( 30 ) default '未知' ); 
Alter TABLE operator add column (
  StartVideo tinyint(1) NOT NULL DEFAULT 0,
  StartPlate tinyint(1) NOT NULL DEFAULT 0,
  ConnectDB tinyint(1) NOT NULL DEFAULT 0,
  MonthCard tinyint(1) NOT NULL DEFAULT 0,
  ValueCard tinyint(1) NOT NULL DEFAULT 0,
  TimeCard tinyint(1) NOT NULL DEFAULT 0,
  LedInfo tinyint(1) NOT NULL DEFAULT 0,
  DeviceConfig tinyint(1) NOT NULL DEFAULT 0,
  SystemSet tinyint(1) NOT NULL DEFAULT 0,
  CardRightSet tinyint(1) NOT NULL DEFAULT 0,
  DiscountSet tinyint(1) NOT NULL DEFAULT 0,
  SerialPortSet tinyint(1) NOT NULL DEFAULT 0,
  PlateRecogSet tinyint(1) NOT NULL DEFAULT 0,
  PassRecord tinyint(1) NOT NULL DEFAULT 0,
  FeeRecord tinyint(1) NOT NULL DEFAULT 0,
  DiscountReport tinyint(1) NOT NULL DEFAULT 0,
  DailyReport tinyint(1) NOT NULL DEFAULT 0,
  MonthlyReport tinyint(1) NOT NULL DEFAULT 0,
  YearlyReport tinyint(1) NOT NULL DEFAULT 0,
  SyncTime tinyint(1) NOT NULL DEFAULT 0,
  Blacklist tinyint(1) NOT NULL DEFAULT 0,
  EmployeeID varchar(45) NOT NULL
);


CREATE TABLE `garageingarage` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `CardID` varchar(45) DEFAULT NULL,
  `PlateID` varchar(45) DEFAULT NULL,
  `DateTime` datetime DEFAULT NULL,
  `InOutFlag` tinyint(1) DEFAULT NULL,
  `ChannelName` varchar(45) DEFAULT NULL,
  `Level` int(8) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=gb2312$$；

//Log
CREATE TABLE `pmslog` (
  `MsgID` int(11) NOT NULL AUTO_INCREMENT,
  `MsgKind` varchar(45) DEFAULT NULL,
  `MsgText` varchar(10240) DEFAULT NULL,
  `MsgDateTime` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`MsgID`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312$$

//////////////////
alter table userinfo add column( Comments varchar( 250 ) default "" ); 

alter table parkinfo add column( usedSpace Inside INT( 10 ) NOT NULL default 0 );  
stoprd intime 可以null
////////////////////////////////////
-- --------------------------------------------------------------------------------
-- Routine DDL
-- Note: comments before and after the routine body will not be stored by the server
-- --------------------------------------------------------------------------------
DELIMITER $$

CREATE DEFINER=`test`@`%` PROCEDURE `SurplusSpace`( in bSub bool, in nID int)
BEGIN
    declare nUnit int;
    if bSub then 
        set nUnit = -1;
        if exists ( select usedSpace from parkinfo where usedSpace > 0 and parkindex = nID ) then
            update parkinfo set usedSpace = usedSpace + nUnit where parkindex = nID;
        end if;
    else
        set nUnit = 1;
        if exists ( select usedSpace from parkinfo where parknum > usedSpace and parkindex = nID) then
            update parkinfo set usedSpace = usedSpace + nUnit where parkindex = nID;
        end if;
    end if;
END
////////////////////////////////////

// 显示报警对话框
CommonCfg/DisplayAlert
DisplayAlert=true
RefreshParkspaceTime=60000