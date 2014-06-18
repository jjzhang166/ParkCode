<?php
include_once __DIR__."/"."mysql.php";

class Credit extends Base
{
	public $sum     = "0";
	public $list    = array();
	private $mysql  = null;
	private $fault  = 0;
	
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
		$result = query($this->mysql, "select count(`credit`) from `credit` where public=true"
									." and 0<`counter` and `start`<=now() and now()<=`end`"
									." and `client`=\"".$client."\"");
		if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0])
				&& is_numeric($result[0][0]) && 0<$result[0][0] )
		{
			return 0;
		}
		return -1*abs(parent::code("没有符合条件的结果"));
	}
	
	private function base_check(&$object)
	{
		$this->fault = -1*abs(parent::check($object,"subtype"));
		if(0!=$this->fault)
		{//do nothing
		}
		elseif (!property_exists($object,"limit"))
		{
			$this->fault = -1*abs(parent::code("没有客户端可接纳的结果数字段"));
		}
		elseif (empty($object->limit))
		{
			$this->fault = -1*abs(parent::code("客户端可接纳的结果数为空"));
		}
		elseif (!is_numeric($object->limit))
		{
			$this->fault = -1*abs(parent::code("客户端可接纳的结果数不为一个数字"));
		}
		elseif ($object->limit<1)
		{
			$this->fault = -1*abs(parent::code("客户端可接纳的结果数为零"));
		}
		elseif (!property_exists($object,"encryption"))
		{
			$this->fault = -1*abs(parent::code("没有加密类型字段"));
		}
		elseif(false===array_search($object->encryption, array("","none","des","3des","aes","rsa")))
		{
			$this->fault = -1*abs(parent::code("不可识别的加密类型"));
		}
	}
	
	function post($prefix,&$object)
	{
		if( !is_array($prefix) || !is_object($object) )
		{
			return -1*abs(parent::code("传入参数不正确"));
		}
		$client = $prefix[0];
		$serial = $prefix[1];
		$this->base_check($object);
		$subtype = isset($object->subtype) ? $object->subtype : "";
		$limit   = isset($object->limit)   ? $object->limit   : "0";
		$result = query($this->mysql, "update `log` set `subtype`=\"".$subtype."\",`order`=\"".$limit
							."\" where (`client`=\"".$client."\" and `serial`=\"".$serial."\")");
		if( true === $result )
		{
			return 0;
		}
		return -1*abs(parent::code("写数据库错误"));
	}
	
	function get($prefix)
	{
		if( !is_array($prefix) || sizeof($prefix)<2 )
		{
			return $this;
		}
		$client = $prefix[0];
		$serial = $prefix[1];
		$result = query($this->mysql, "select `order`,`client` from `log` where `client`=\""
									.$client."\" and `serial`=\"".$serial."\"");
		if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0])
				&& is_numeric($result[0][0]) )
		{
			$result = query($this->mysql, "select `credit`,`counter` from `credit` where public=true"
									." and 0<`counter` and `start`<=now() and now()<=`end`"
									." and `client`=\"".$result[0][1]."\" limit ".$result[0][0]);
			if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0]) )
			{
				foreach ($result as &$value)
				{
					$this->adding($value[0],$value[1]);
				}
			}
		}
		return $this;
	}

	private function adding($value,$times)
	{
		$this->sum = strval(array_push($this->list, (object)array(
				"order"=>$this->sum, "value"=>$value, "times"=>$times)));
	}
}

?>
