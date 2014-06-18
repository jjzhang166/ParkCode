<?php
include_once __DIR__."/"."mysql.php";

class Config extends Base
{
	public $record = "0";
	public $prepay = "0";
	private $mysql = null;
	private $fault = 0;
	
	function __construct()
	{
		parent::__construct();
		$this->mysql = parent::hadle();
	}
	
	function status($client,$serial)
	{
		$error = parent::status($client,$serial);
		if(0!=$error)
		{
			return $error;
		}
		$select = "(`config` inner join `client` on `config`.`company`=`client`.`company`)";
		$select = "select count(`config`.`prepay`) from ".$select
				." inner join `log` on `config`.`street`=`log`.`order` and `log`.`client`=\""
				.$client."\" and `log`.`serial`=\"".$serial."\"";
		$result = query($this->mysql,$select);
		if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0])
				&& is_numeric($result[0][0]) && 0<$result[0][0] )
		{
			return 0;
		}
		return -1*abs(parent::code("没有符合条件的结果"));
	}
	
	function post($prefix,$object)
	{
		if( !is_array($prefix) || sizeof($prefix)<2 || !is_object($object) )
		{
			return -1*abs(parent::code("传入参数不正确"));
		}
		$client = $prefix[0];
		$serial = $prefix[1];
		$this->fault = -1*abs(parent::check($object,"street"));
		if( 0 == $this->fault )
		{
			$result = query($this->mysql, "update `log` set `order`=\"".$object->street
					."\" where (`client`=\"".$client."\" and `serial`=\"".$serial."\")");
			if( false === $result )
			{
				return -1*abs(parent::code("写数据库错误"));
			}
		}
		return $this->fault;
	}
	
	function get($prefix)
	{
		if( !is_array($prefix) || sizeof($prefix)<2 )
		{
			return $this;
		}
		$client = $prefix[0];
		$serial = $prefix[1];
		$select = "(`config` inner join `client` on `config`.`company`=`client`.`company`)";
		$select = "select `config`.`record`,`config`.`prepay` from ".$select
				." inner join `log` on `config`.`street`=`log`.`order` and `log`.`client`=\""
				.$client."\" and `log`.`serial`=\"".$serial."\"";
		$result = query($this->mysql,$select);
		if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 1<sizeof($result[0]) )
		{
			$this->record = (int)$result[0][0];
			$this->prepay = $result[0][1];
		}
		return $this;
	}
}

?>
