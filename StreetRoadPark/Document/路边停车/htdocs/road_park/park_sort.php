<?php
include_once __DIR__."/"."mysql.php";

class Sort extends Base
{
	public  $street  = "";
	public  $sum     = "0";
	public  $list    = array();
	private $fault   = 0;
	private $mysql   = null;
	private $limit   = null;
	private $after   = "0000-00-00 00:00:00";
	private $photos  = null;
	private $exit    = null;
	private $debt    = null;
	
	function __construct()
	{
		parent::__construct();
		$this->mysql = parent::hadle();
	}
	
	function status($client,$serial)
	{
		$fault = parent::status($client,$serial);
		if( 0!= $fault )
		{
			return $fault;
		}
		if( !is_numeric($this->sum) || $this->sum<1 )
		{
			$this->search();
		}
		if( !is_numeric($this->sum) || $this->sum<1 )
		{
			return -1*abs(parent::code("没有符合条件的结果"));
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
		$this->fault = -1*abs(parent::check($object,"street"));
		if(0!=$this->fault)
		{
			return $this->fault;
		}
		$this->fault = -1*abs(parent::check($object,"limit"));
		if(0!=$this->fault)
		{
			return $this->fault;
		}
		
		if(!property_exists($object,"after"))
		{
			return -1*abs($this->code("没有after字段"));
		}
		elseif( !parent::is_time($object->after))
		{
			return -1*abs($this->code("after为空或不可识别"));
		}
		
		if(!property_exists($object,"photos"))
		{
			return -1*abs($this->code("没有photos字段"));
		}
		elseif(!is_numeric($object->photos))
		{
			return -1*abs($this->code("photos为空或不为数字"));
		}
		
		if(!property_exists($object,"exit"))
		{
			return -1*abs($this->code("没有exit字段"));
		}
		elseif( !is_string($object->exit)
				|| false===array_search(strtolower(preg_replace("/\s\s+/"," ",$object->exit)),array("yes","no")) )
		{
			return -1*abs($this->code("exit为空或不符合格式"));
		}
		
		if(!property_exists($object,"debt"))
		{
			return -1*abs($this->code("没有debt字段"));
		}
		elseif( !is_string($object->debt)
				|| false===array_search(strtolower(preg_replace("/\s\s+/"," ",$object->exit)),array("yes","no")) )
		{
			return -1*abs($this->code("debt为空或不符合格式"));
		}
		
		$this->street  = $object->street;
		$this->after   = $object->after;
		$this->limit   = $object->limit;
		$this->photos  = $object->photos;
		$this->exit    = strtolower(preg_replace("/\s\s+/"," ",$object->exit));
		$this->debt    = strtolower(preg_replace("/\s\s+/"," ",$object->exit));
		$extra = $this->street."|".$this->after."|".$this->limit."|".$this->photos."|".$this->exit."|".$this->debt;
		
		$result = query($this->mysql, "update `log` set `extra`=\"".$extra
						."\" where (`client`=\"".$client."\" and `serial`=\"".$serial."\")");
		if( false === $result )
		{
			return -1*abs(parent::code("写数据库错误"));
		}
		return 0;
	}
	
	function get($prefix)
	{
		if( !is_array($prefix) || sizeof($prefix)<2 )
		{
			return (object)null;
		}
		$client = $prefix[0];
		$serial = $prefix[1];
		
		$result = query($this->mysql, "select `extra` from `log` where `client`=\""
							.$client."\" and `serial`=\"".$serial."\"");
		if ( !is_array($result) || sizeof($result)<1 || !is_array($result[0]) || sizeof($result[0])<1
				|| !is_string($result[0][0]) || strlen($result[0][0])<1 )
		{
			return (object)null;
		}
		$request = explode("|", trim($result[0][0], ","));
		if( !is_array($request) || sizeof($request)<1 )
		{
			return (object)null;
		}
		foreach ($request as $value)
		{
			if( !is_string($value) || strlen($value)<1 )
			{
				return (object)null;
			}
		}
		$this->street  = $request[0];
		$this->after   = $request[1];
		$this->limit   = $request[2];
		$this->photos  = $request[3];
		$this->exit    = strtolower(preg_replace("/\s\s+/"," ",$request[4]));
		$this->debt    = strtolower(preg_replace("/\s\s+/"," ",$request[4]));
		if( 0!=parent::check($this,"street") || !parent::is_time($this->after)
				|| !is_numeric($this->limit) || $this->limit < 1
				|| !is_numeric($this->photos) || $this->photos < 0
				|| false===array_search($this->exit,array("yes","no"))
				|| false===array_search($this->debt,array("yes","no")) )
		{
			return (object)null;
		}
		$this->exit = ("yes"==$this->exit)?true:false;
		$this->debt = ("yes"==$this->debt)?true:false;
		if( !is_numeric($this->sum) || $this->sum<1 )
		{
			$this->search();
		}
		return $this;
	}
	
	private function search()
	{
		$this->sum = 0;
		return $this->sum;
	}
}

?>
