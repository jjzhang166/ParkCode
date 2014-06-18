<?php
include_once __DIR__."/"."mysql.php";

class Stay_price extends Base
{
	public  $company = "";
	public  $sum     = "0";
	public  $list    = array();
	private $mysql   = null;
	
	function __construct()
	{
		parent::__construct();
		$this->mysql = parent::hadle();
	}
	
	function post($client,$serial,&$object)
	{
		return 0;
	}
	
	function get($client,$serial,&$object)
	{
		if( empty($client) || !is_string($serial) || strlen($serial)<1 )
		{
			return -1*abs(parent::code("传入参数不正确"));
		}
		$select = "(`client` inner join `company` on `client`.`company`=`company`.`indexed`)";
		$select = "select `company`.`company` from ".$select
				." inner join `log` on `client`.`client`=`log`.`client` and `log`.`client`=\""
				.$client."\" and `log`.`serial`=\"".$serial."\"";
		$result = query($this->mysql, $select);
		if ( !is_array($result) || sizeof($result)<1 || !is_array($result[0]) || sizeof($result[0])<1
				|| !is_string($result[0][0]) || strlen($result[0][0])<1 )
		{
			return -1*abs(parent::code("读数据库错误"));
		}
		$this->company = urlencode($result[0][0]);
		
		$select = "(`client` inner join `config` on `client`.`company`=`config`.`company`)";
		$select = "(".$select." inner join `log` on `client`.`client`=`log`.`client` and `log`.`client`=\""
				.$client."\" and `log`.`serial`=\"".$serial."\")";
		$select = "select `street`.`indexed`,`street`.`city`,`street`.`canton`,`street`.`street` from ".$select
				." inner join `street` on `street`.`indexed`=`config`.`street`";
		$result = query($this->mysql,$select);
		if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0]) )
		{
			foreach ( $result as $value )
			{
				$item = array_combine(array('order','city','district','street'),
									array(urlencode($value[0]),
										urlencode($value[1]),
										urlencode($value[2]),
										urlencode($value[3])));
				$this->list[] = (object)$item;
			}
		}
		$this->sum = sizeof($this->list);
		return 0<$this->sum ? 0 : (-1*abs(parent::code("没有符合条件的结果")));
	}
}

class Stay_detail extends Base
{
	public  $sum     = "0";
	public  $groups  = array();
	private $mysql   = null;

	function __construct()
	{
		parent::__construct();
		$this->mysql = parent::hadle();
	}
	
	function post($client,$serial,&$object)
	{
		return 0;
	}
	
	function get($client,$serial,&$object)
	{
		if( empty($client) || !is_string($serial) || strlen($serial)<1 )
		{
			return -1*abs(parent::code("传入参数不正确"));
		}
		$select = "(`client` inner join `group` on `client`.`company`=`group`.`company`)";
		
		$select = "select `group`.`type` from ".$select
				." inner join `log` on `client`.`client`=`log`.`client` and `log`.`client`=\""
				.$client."\" and `log`.`serial`=\"".$serial."\"";
		$result = query($this->mysql,$select);
		if ( !is_array($result) || sizeof($result)<1 || !is_array($result[0]) || sizeof($result[0])<1 )
		{
			return -1*abs(parent::code("读数据库错误"));
		}
		foreach ( $result as $value )
		{
			$this->groups[] = urlencode($value[0]);
		}
		$this->sum = sizeof($this->groups);
		return 0<$this->sum ? 0 : (-1*abs(parent::code("没有符合条件的结果")));
	}
}

class Stay extends Base
{
	public  $detail  = "success";
	private $fault   = 0;
	private $mysql   = null;
	private $mode    = null;
	private $part    = null;
	
	private $client  = null;
	private $serial  = null;
	private $subtype = null;
	private $user    = null;
	private $station = null;
	
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
		$this->mode   = "post";
		$this->client = $prefix[0];
		$this->serial = $prefix[1];
		
		$this->fault = -1*abs(parent::check($object,"subtype"));
		if(0!=$this->fault)
		{
			return $this->fault;
		}
		$this->fault = -1*abs(parent::check($object,"operator"));
		if(0!=$this->fault)
		{
			return $this->fault;
		}
		$this->fault = -1*abs(parent::check($object,"street"));
		if(0!=$this->fault)
		{
			return $this->fault;
		}
		
		if( !property_exists($object,"enter") )
		{
			return -1*abs($this->code("没有进入当前车位时间字段"));
		}
		elseif ( !parent::is_time($object->enter) )
		{
			return -1*abs($this->code("进入当前车位的时间为空"));
		}
		
		if(!property_exists($object,"station"))
		{
			return -1*abs($this->code("没有当前车位编号字段"));
		}
		elseif( !is_numeric($object->station) )
		{
			return -1*abs($this->code("当前车位编号为空或不可识别"));
		}
		// need check combine database;
		
		$this->station = $object->station; // todo
		$this->user    = $object->station; // todo
		
		$this->subtype = preg_replace("/\s+/","",$object->subtype);
		$result = query($this->mysql, "update `log` set `subtype`=\"".$this->subtype
						."\" where (`client`=\"".$this->client."\" and `serial`=\"".$this->serial."\")");
		if( false === $result )
		{
			return -1*abs(parent::code("写数据库错误"));
		}
		if(!method_exists($this,"_".$this->subtype))
		{
			return -1*abs(parent::code("无法识别的子类型"));
		}
		$this->fault = call_user_func(array($this,"_".$this->subtype), $object);
		if( false !== $this->fault )
		{
			return $this->fault;
		}
		return -1*abs(parent::code("类方法调用失败"));
	}
	
	function get($prefix)
	{
		if( !is_array($prefix) || sizeof($prefix)<2 )
		{
			return (object)null;
		}
		$this->client = $prefix[0];
		$this->serial = $prefix[1];
		$this->mode   = "get";
		$result = query($this->mysql, "select `subtype` from `log` where `client`=\""
							.$this->client."\" and `serial`=\"".$this->serial."\"");
		if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0]) )
		{
			$this->subtype = $result[0][0];
			if( is_string($this->subtype) && 0<strlen($this->subtype) && method_exists($this,"_".$this->subtype) )
			{
				$this->fault = call_user_func(array($this,"_".$this->subtype),null);
				if( false!==$this->fault && 0==$this->fault && !is_null($this->part) )
				{
					return $this->part;
				}
			}
		}
		return (object)null;
	}
	
	private function doing( $suffix, &$object )
	{
		if( is_string($suffix) && 0<sizeof($suffix) )
		{
			$class  = "Stay".$suffix;
			if( class_exists($class) )
			{
				$this->part = new $class;
				if(is_callable(array($this->part,$this->mode)))
				{
					return call_user_func(array($this->part,$this->mode),$this->client,$this->serial,$object);
				}
				return -1*abs(parent::code("指定的类方法不存在或不可调用"));
			}
		}
		return false;
	}

	private function busy($station)
	{
		$result = query($this->mysql, "select `act` from `stay` where `occurred`="
				."(select max(`occurred`) from `stay` where "
				."(`act`=\"enter\" or `act`=\"place\" or `act`=\"displace\" or `act`=\"exit\"));");
		if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0])
				&& is_string($result[0][0]) && 0<strlen($result[0][0]) )
		{
			if( "enter"==$result[0][0] || "place"==$result[0][0] )
			{
				return true;
			}
		}
		return false;
	}
	
	private function _detail(&$object)
	{
		return $this->doing((string)__FUNCTION__, $object);
	}
	
	private function _price(&$object)
	{
		return $this->doing((string)__FUNCTION__, $object);
	}
	
	private function _place(&$object)
	{
		if( "post"==$this->mode )
		{
			if( !property_exists($object,"time") )
			{
				return -1*abs($this->code("没有操作时间字段"));
			}
			elseif ( !parent::is_time($object->time) )
			{
				return -1*abs($this->code("操作时间为空"));
			}
			
			if(busy($station))
			{
				return -1*abs(parent::code("该车位上还有车")); 
			}
			$result = query($this->mysql, "insert into `stay` (`act`,`record`,`station`,`occurred`) values "
					."\"place\",((select (coalesce(max(`record`),0)+1) from `stay`),\""
					.$this->station."\",\"".$object->time."\")");
			if ( false===$result )
			{
				return -1*abs(parent::code("写数据库错误"));
			}
			$result = query($this->mysql, "update `log` set `extra`=\"success\",`order`=\"".$this->station
					."\" where (`client`=\"".$this->client."\" and `serial`=\"".$this->serial."\")");
			if( false === $result )
			{
				return -1*abs(parent::code("写数据库错误"));
			}
			return 0;
		}
		elseif( "get"==$this->mode )
		{
			$result = query($this->mysql, "select `extra` from `log` where `client`=\""
					.$this->client."\" and `serial`=\"".$this->serial."\"");
			if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0])
					&& is_string($result[0][0]) && "success"==$result[0][0] )
			{
				return $this;
			}
			return null;
		}
	}
	
	private function _move(&$object)
	{
	if( "post"==$this->mode )
		{
			if( !property_exists($object,"time") )
			{
				return -1*abs($this->code("没有操作时间字段"));
			}
			elseif ( !parent::is_time($object->time) )
			{
				return -1*abs($this->code("操作时间为空"));
			}
			
			if(!property_exists($object,"refer"))
			{
				return -1*abs($this->code("没有前继车位编号字段"));
			}
			elseif( !is_numeric($object->refer) )
			{
				return -1*abs($this->code("前继车位编号为空或不可识别"));
			}
			// need check combine database;
			
			if( !property_exists($object,"during") )
			{
				return -1*abs($this->code("没有前继车位参考时间字段"));
			}
			elseif ( !parent::is_time($object->during) )
			{
				return -1*abs($this->code("前继车位参考时间为空或该时间此车位无车"));
			}
			// need check combine database;
			
			$from = $object->refer; // to do
			
			if(!busy($station))
			{
				return -1*abs(parent::code("该车位上没有车"));
			}
			$result = query($this->mysql, "insert into `stay` (`act`,`record`,`station`,`occurred`,`from`) values "
					."\"displace\",((select coalesce(max(`record`),1) from `stay` where `station`=\"".$this->station."),\""
					.$this->station."\",\"".$object->time."\",\"".$from."\")");
			if ( false===$result )
			{
				return -1*abs(parent::code("写数据库错误"));
			}
			$result = query($this->mysql, "update `log` set `extra`=\"success\",`order`=\"".$this->station
					."\" where (`client`=\"".$this->client."\" and `serial`=\"".$this->serial."\")");
			if( false === $result )
			{
				return -1*abs(parent::code("写数据库错误"));
			}
			return 0;
		}
		elseif( "get"==$this->mode )
		{
			$result = query($this->mysql, "select `extra` from `log` where `client`=\""
					.$this->client."\" and `serial`=\"".$this->serial."\"");
			if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0])
					&& is_string($result[0][0]) && "success"==$result[0][0] )
			{
				return $this;
			}
			return null;
		}
	}
	
	private function _displace(&$object)
	{
		if( "post"==$this->mode )
		{
			if( !property_exists($object,"time") )
			{
				return -1*abs($this->code("没有操作时间字段"));
			}
			elseif ( !parent::is_time($object->time) )
			{
				return -1*abs($this->code("操作时间为空"));
			}
			
			if(!busy($station))
			{
				return -1*abs(parent::code("该车位上没有车"));
			}
			$result = query($this->mysql, "insert into `stay` (`act`,`record`,`station`,`occurred`) values "
					."\"displace\",((select coalesce(max(`record`),1) from `stay` where `station`=\""
					.$this->station." and `occurred`=\"".$object->enter."\" and (`act`=\"enter\" or `act`=\"place\")),\""
					.$this->station."\",\"".$object->time."\")");
			if ( false===$result )
			{
				return -1*abs(parent::code("写数据库错误"));
			}
			$result = query($this->mysql, "update `log` set `extra`=\"success\",`order`=\"".$this->station
					."\" where (`client`=\"".$this->client."\" and `serial`=\"".$this->serial."\")");
			if( false === $result )
			{
				return -1*abs(parent::code("写数据库错误"));
			}
			return 0;
		}
		elseif( "get"==$this->mode )
		{
			$result = query($this->mysql, "select `extra` from `log` where `client`=\""
					.$this->client."\" and `serial`=\"".$this->serial."\"");
			if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0])
					&& is_string($result[0][0]) && "success"==$result[0][0] )
			{
				return $this;
			}
			return null;
		}
	}
	
	private function _escape(&$object)
	{
		return $this->doing((string)__FUNCTION__, $object);
	}
	
	private function _photo(&$object)
	{
		return $this->doing((string)__FUNCTION__, $object);
	}
	
	private function _confim(&$object)
	{
		return $this->doing((string)__FUNCTION__, $object);
	}
	
	private function _prepay(&$object)
	{
		return $this->doing((string)__FUNCTION__, $object);
	}
	
	private function _pay(&$object)
	{
		return $this->doing((string)__FUNCTION__, $object);
	}
	
}

?>
