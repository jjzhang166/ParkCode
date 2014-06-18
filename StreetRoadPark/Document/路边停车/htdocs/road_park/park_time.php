<?php
include_once __DIR__."/"."mysql.php";

class Time extends Base
{
	public $time    = "0000-00-00 00:00:00.000000";
	private $mysql  = null;
	private $fault  = 0;
	
	function __construct()
	{
		parent::__construct();
		$this->mysql = parent::hadle();
	}
	
	function status($client,$serial)
	{
		return parent::status($client,$serial);
	}
	
	function post($prefix,$object)
	{
		if( !is_array($prefix) || !is_object($object) )
		{
			return -1*abs(parent::code("传入参数不正确"));
		}
		$client = $prefix[0];
		$serial = $prefix[1];
		if (!property_exists($object,"time"))
		{
			$this->fault = -1*abs(parent::code("没有时间字段"));
		}
		elseif (empty($object->time))
		{
			$this->fault = -1*abs(parent::code("时间为空或不可识别"));
		}
		$result = query($this->mysql, "update `log` set `extra`=\"".$object->time
				."\" where (`client`=\"".$client."\" and `serial`=\"".$serial."\")");
		if( true === $result )
		{
			return 0;
		}
		return -1*abs(parent::code("写数据库错误"));
	}
	
	function get($prefix)
	{
		$time = gettimeofday();
		$this->time = strftime("%Y-%m-%d %H:%M:%S.", $time['sec']).str_pad($time['usec'],6,'0');
		return $this;
	}
}

?>
