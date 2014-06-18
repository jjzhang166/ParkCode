<?php
include_once __DIR__."/"."base.php";

class Register extends Base
{
	public  $device = "";
	public  $order  = "";
	private $mysql  = null;
	private $fault  = null;
	
	function __construct()
	{
		parent::__construct(); 
		$this->mysql = parent::hadle();
	}
	
	function status($client,$serial)
	{
		return parent::status($client,$serial);
	}
	
	function post($prefix,&$object)
	{
		if( !is_array($prefix) || !is_object($object) )
		{
			return -1*abs(parent::code("传入参数不正确"));
		}
		$client = $prefix[0];
		$serial = $prefix[1];
		$this->device = isset($object->{'device'})? $object->{'device'}:$client;
		$result = query($this->mysql, "select `client` from `client` where `device`=\"".$this->device."\"");
		if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0]) )
		{
			return $this->status($result[0][0],$serial);
		}else
		{
			$result = query($this->mysql, "insert into `client` (`device`) values (\"".$this->device."\")");
			if( false === $result )
			{
				return -1*abs(parent::code("写数据库错误"));
			}
			$result = query($this->mysql, "select `client` from `client` where `device`=\"".$this->device."\"");
			if ( !is_array($result) || sizeof($result)<1 || !is_array($result[0]) || sizeof($result[0])<1 )
			{
				return -1*abs(parent::code("读数据库错误"));
			}
			$log = "insert into `log` (`client`,`serial`,`remote`,`moment`,`credit`,`type`) values (\""
						.$result[0][0]."\",\"".$serial."\",\"".$_SERVER['REMOTE_ADDR']."\",\""
							.strftime("%Y-%m-%d %H:%M:%S",$_SERVER['REQUEST_TIME'])."\",null,\""."register"."\")";
			$result = query($this->mysql,$log);
			if( true === $result )
			{
				return 0;
			}
			return -1*abs(parent::code("写数据库错误"));
		}
	}
	
	function get($prefix)
	{
		if(!is_array($prefix))
		{
			return $this;
		}
		$client = $prefix[0];
		$serial = $prefix[1];
		$result = query($this->mysql, "select `client`,`device` from `client` where `client`=\"".$client."\"");
		if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0]) )
		{
			$this->order  = $result[0][0];
			$this->device = $result[0][1];
		}
		return $this;
	}
}

?>
