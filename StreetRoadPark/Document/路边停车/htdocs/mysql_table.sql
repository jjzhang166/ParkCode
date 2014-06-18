create database road_park character set utf8;
show databases;
use road_park;
show tables;

create table `street` (
  `indexed`     bigint unsigned not null auto_increment,
  `city`        varchar(100),
  `canton`      varchar(1000),
  `street`      varchar(10000),
  `renew`       datetime,
  primary key(`indexed`)
  )engine=innodb default charset=utf8;
alter table `street` auto_increment = 1;
alter table `street` add unique(`city`(50),`canton`(50),`street`(150));

create table `company` (
  `indexed`     bigint unsigned not null auto_increment,
  `company`     varchar(10000),
  `renew`       datetime,
  primary key(`indexed`)
  )engine=innodb default charset=utf8;
alter table `company` auto_increment = 1;
alter table `company` add unique(`company`(255));

create table `config` (
  `company`     bigint unsigned not null,
  `street`      bigint unsigned not null,
  `number`      int unsigned,
  `record`      bigint unsigned default 2592000,
  `algorithm`   longtext,
  `prepay`      decimal(10,2) default 0,
  `renew`       datetime,
  primary key(`company`,`street`)
  )engine=innodb default charset=utf8;
alter table `config` add foreign key (`company`) references `company` (`indexed`) on update cascade on delete restrict;
alter table `config` add foreign key (`street`) references `street` (`indexed`) on update cascade on delete restrict;

create table `station` (
  `indexed`     bigint unsigned not null auto_increment,
  `company`     bigint unsigned not null,
  `street`      bigint unsigned not null,
  `number`      int unsigned not null,
  `longitude`   float,
  `latitude`    float,
  `elevation`   float,
  `receiver`    int unsigned,
  `sensor`      smallint unsigned,
  `reset`       bool default false,
  `ignore`      smallint unsigned default 0,
  `renew`       datetime,
  primary key(`indexed`)
  )engine=innodb default charset=utf8;
alter table `station` auto_increment = 1;
alter table `station` add unique(`company`,`street`,`number`);
alter table `station` add unique(`receiver`,`sensor`);
alter table `station` add foreign key (`company`) references `company` (`indexed`) on update cascade on delete restrict;
alter table `station` add foreign key (`street`) references `street` (`indexed`) on update cascade on delete restrict;

create table `client` (
  `client`      bigint unsigned not null auto_increment,
  `device`      varchar(128) not null,
  `company`     bigint unsigned,
  `number`      int unsigned,
  `safety`      bool default false,
  `state`       enum('unused','inuse','used','forbid') default 'unused',
  `renew`       datetime,
  primary key(`client`)
  )engine=innodb default charset=utf8;
alter table `client` auto_increment = 1;
alter table `client` add unique(`device`);
alter table `client` add unique(`company`,`number`);
alter table `client` add foreign key (`company`) references `company` (`indexed`) on update cascade on delete restrict;

create table `register` (
  `device`      varchar(128) not null,
  `serial`      varchar(20000) not null,
  `start`       datetime not null,
  `end`         datetime not null,
  `state`       enum('unused','inuse','used','forbid') default 'unused',
  `renew`       datetime,
  primary key(`device`,`serial`(128))
  )engine=innodb default charset=utf8;
alter table `register` add foreign key (`device`) references `client` (`device`) on update cascade on delete restrict;

create table `credit` (
  `client`      bigint unsigned not null,
  `credit`      varchar(10000) not null,
  `start`       datetime default "0001-01-01 00:00:00",
  `end`         datetime default "9999-12-31 23:59:59",
  `counter`     bigint unsigned default 18446744073709551615,
  `adding`      datetime,
  `public`      bool default true,
  primary key(`client`,`credit`(200))
  )engine=innodb default charset=utf8;
alter table `credit` add foreign key (`client`) references `client` (`client`) on update cascade on delete restrict;

create table `group` (
  `indexed`     bigint unsigned not null auto_increment,
  `company`     bigint unsigned not null,
  `type`        varchar(1000) not null,
  `renew`       datetime,
  primary key(`indexed`)
  )engine=innodb default charset=utf8;
alter table `group` auto_increment = 1;
alter table `group` add unique(`company`,`type`(200));
alter table `group` add index(`indexed`,`company`);
alter table `group` add foreign key (`company`) references `company` (`indexed`) on update cascade on delete restrict;

create table `user` (
  `indexed`     bigint unsigned not null auto_increment,
  `group`       bigint unsigned not null,
  `company`     bigint unsigned not null,
  `user`        varchar(100) not null,
  `street`      bigint unsigned not null,
  `number`      int unsigned not null,
  `forbid`      bool default false,
  `password`    varchar(1000),
  `name`        varchar(100),
  `id`          varchar(1000),
  `id_hash`     varchar(1000),
  `user_hash`   varchar(1000),
  `renew`       datetime,
  primary key(`indexed`)
  )engine=innodb default charset=utf8;
alter table `user` add unique(`company`,`user`);
alter table `user` add unique(`company`,`street`,`number`);
alter table `user` add foreign key (`group`,`company`) references `group` (`indexed`,`company`) on update cascade on delete restrict;
alter table `user` add foreign key (`street`) references `street` (`indexed`) on update cascade on delete restrict;

create table `action` (
  `user`        bigint unsigned not null,
  `client`      bigint unsigned not null,
  `ip`          varchar(128),
  `login`       datetime,
  `logout`      datetime,
  `state`       enum('online','offline','logout') default 'online',
  primary key(`user`)
  )engine=innodb default charset=utf8;
alter table `action` add foreign key (`user`) references `user` (`indexed`) on update cascade on delete restrict;
alter table `action` add foreign key (`client`) references `client` (`client`) on update cascade on delete restrict;

create table `stay` (
  `indexed`     bigint unsigned not null auto_increment,
  `record`      bigint unsigned not null,
  `station`     bigint unsigned not null,
  `occurred`    datetime not null,
  `from`        bigint unsigned,
  `hash`        varchar(1000),
  `judge`       varchar(100),
  `trust`       decimal(6,4),
  `plate`       varchar(100),
  `money`       decimal(10,2),
  `act`         enum('enter','place','photo','move','confirm','prepay','pay','displace','exit') default'enter',
  `operator`    bigint unsigned,
  `renew`       datetime,
  primary key(`indexed`)
  )engine=innodb default charset=utf8;
alter table `stay` auto_increment = 1;
alter table `stay` add unique(`station`,`occurred`,`act`);
alter table `stay` add foreign key (`station`) references `station` (`indexed`) on update cascade on delete restrict;
alter table `stay` add foreign key (`from`) references `stay` (`indexed`) on update cascade on delete restrict;
alter table `stay` add foreign key (`operator`) references `user` (`indexed`) on update cascade on delete restrict;

create table `bigfile` (
  `file`        bigint unsigned not null auto_increment,
  `bytes`       bigint unsigned not null default 0,
  `type`        varchar(100) default "jpg",
  `renew`       datetime,
  `operator`    bigint unsigned,
  `crc32`       char(8),
  `md5`         char(32),
  `sha1`        char(40),
  `sha224`      char(56),
  `sha256`      char(64),
  `sha384`      char(96),
  `sha512`      char(128),
  `data`        longblob,
  primary key(`file`)
  )engine=innodb default charset=utf8;
alter table `bigfile` auto_increment = 1;
alter table `bigfile` add foreign key (`operator`) references `user` (`indexed`) on update cascade on delete restrict;

create table `log` (
  `client`      bigint unsigned not null,
  `serial`      varchar(1000) not null,
  `remote`      varchar(128) not null,
  `moment`      datetime not null,
  `exception`   bigint default 0,
  `credit`      varchar(10000),
  `type`        enum('register','credit','time','config','user','stay','sort','photo'),
  `subtype`     varchar(100),
  `order`       bigint unsigned,
  `extra`       varchar(10000),
  primary key(`client`,`serial`(200))
  )engine=myisam default charset=utf8;
alter table `log` add foreign key (`client`) references `client` (`client`) on update cascade on delete restrict;



create trigger street_bi before insert on `street` for each row set new.renew=now();
create trigger street_bu before update on `street` for each row set new.renew=now();
create trigger company_bi before insert on `company` for each row set new.renew=now();
create trigger company_bu before update on `company` for each row set new.renew=now();
create trigger config_bi before insert on `config` for each row set new.renew=now();
create trigger config_bu before update on `config` for each row set new.renew=now();
create trigger station_bi before insert on `station` for each row set new.renew=now();
create trigger station_bu before update on `station` for each row set new.renew=now();

delimiter //
create trigger client_bi before insert on `client` for each row 
begin 
    set new.`renew`=now();
    if new.`state` is not null and new.`state`="inuse" and 
        not exists (select `device` from `register` where 
            (`register`.`state`="inuse" and `register`.`start`<=now() 
                and now()<=`register`.`end`)) 
    then 
        set new.`device`=null;
    end if;
end; //
delimiter ;

delimiter //
create trigger client_bu before update on `client` for each row 
begin 
    set new.`renew`=now();
    if new.`device` is not null and new.`device`!=old.`device` then 
        set new.`device`=null;
    end if;
    if new.`state` is not null and new.`state`="inuse" and 
        not exists (select `device` from `register` where 
            (`register`.`state`="inuse" and `register`.`start`<=now() 
                and now()<=`register`.`end`)) 
    then 
        set new.`device`=null;
    end if;
    if new.`client` is not null and new.`client`!=old.`client` 
    then 
        update `log` set `log`.`client`=new.`client` where 
            `log`.`client`=old.`client`;
    end if;
end; //
delimiter ;

delimiter //
create trigger register_bi before insert on `register` for each row 
begin 
    set new.`renew`=now();
    if not exists 
        (select `client` from `client` where `client`.`device`=new.`device`)
    then 
        insert into `client`(`device`) values (new.`device`);
        if (select count(`indexed`) from `company`)=1 then
            update `client` set `company`=(select max(`indexed`) from `company`) 
                where `client`.`device`=new.`device`;
        end if;
    end if;
end; //
delimiter ;

delimiter //
create trigger register_ai after insert on `register` for each row 
if new.`state`="inuse" and new.`start`<=now() and now()<=new.`end` then
    update `client` set `state`="inuse" 
        where `client`.`device`=new.`device` and `client`.`state`!="forbid";
end if; //
delimiter ;

create trigger register_bu before update on `register` for each row set new.renew=now();

delimiter //
create trigger register_au after update on `register` for each row 
if new.`state`="inuse" then 
if new.`start`<=now() or (new.`start` is null and old.`start`<=now()) then 
if now()<=new.`end` or (new.`end` is null and now()<=old.`end`) then 
if exists (select `client` from `client` where `client`.`device`=
        coalesce(new.`device`,old.`device`) and `client`.`state`!="forbid") then 
    update `client` set `client`.`state`="inuse" where `client`.`device`= 
        coalesce(new.`device`,old.`device`);
end if;
end if;
end if;
end if; //
delimiter ;

create trigger credit_bi before insert on `credit` for each row set new.adding=now();
create trigger group_bi before insert on `group` for each row set new.renew=now();
create trigger group_bu before update on `group` for each row set new.renew=now();
create trigger user_bi before insert on `user` for each row set new.renew=now();
create trigger user_bu before update on `user` for each row set new.renew=now();

delimiter //
create trigger action_bi before insert on `action` for each row
if new.`user` is not null and new.`client` is not null 
    and (new.`state` is null or new.`state`="online" )
then 
    set new.login=now();
else
    set new.logout=now();
end if; //
delimiter ;

delimiter //
create trigger action_bu before update on `action` for each row 
if new.`state`="online" or (new.`state` is null and old.`state`="online") 
then 
    set new.login=now();
else
    set new.logout=now();
end if; //
delimiter ;

















describe `street`;describe `company`;describe `config`;describe `station`;describe `client`;describe `register`;describe `credit`;describe `group`;describe `user`;describe `action`;describe `stay`;describe `bigfile`;describe `log`;

insert into `street` (`city`,`canton`,`street`) values ("chengdu","jinjiang","cunxi");
insert into `company` (`company`) values ("baoma");
insert into `config` (`company`,`street`) values (1,1);
insert into `station` (`company`,`street`,`number`,`receiver`,`sensor`) values (1,1,1,1,1);
insert into `station` (`company`,`street`,`number`,`receiver`,`sensor`) values (1,1,2,1,2);
insert into `station` (`company`,`street`,`number`,`receiver`,`sensor`) values (1,1,3,1,3);
insert into `station` (`company`,`street`,`number`,`receiver`,`sensor`) values (1,1,4,1,4);
insert into `station` (`company`,`street`,`number`,`receiver`,`sensor`) values (1,1,5,1,5);
insert into `station` (`company`,`street`,`number`,`receiver`,`sensor`) values (1,1,6,1,6);
insert into `station` (`company`,`street`,`number`,`receiver`,`sensor`) values (1,1,7,1,7);
insert into `station` (`company`,`street`,`number`,`receiver`,`sensor`) values (1,1,8,1,8);
insert into `station` (`company`,`street`,`number`,`receiver`,`sensor`) values (1,1,9,2,1);
insert into `station` (`company`,`street`,`number`,`receiver`,`sensor`) values (1,1,10,2,2);
insert into `group` (`company`,`type`) values (1,"manager");
insert into `group` (`company`,`type`) values (1,"worker");
insert into `user` (`group`,`user`,`company`,`street`,`number`) values (1,"admin",1,1,1);
insert into `register` (`device`,`serial`,`start`,`end`,`state`) values ("cd","CE1C70","2013-01-01 00:00:00","2013-12-31 23:59:59","inuse");
insert into `credit` (`client`,`credit`) values (1,"AB3456EF");

select * from `street`;select * from `company`;select * from `config`;select * from `station`;select * from `client`;select * from `register`;select * from `credit`;select * from `group`;select * from `user`;select * from `action`;select * from `stay`;select * from `bigfile`;select * from `log`;
