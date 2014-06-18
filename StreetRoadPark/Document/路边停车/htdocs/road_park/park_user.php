<?php
include_once __DIR__."/"."mysql.php";

class User_area extends Base
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

class User_group extends Base
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

class User_list extends Base
{
	public  $sum   = "0";
	public  $list  = array();
	private $mysql = null;
	
	function __construct()
	{
		parent::__construct();
		$this->mysql = parent::hadle();
	}
	
	function post($client,$serial,&$object)
	{
		if( empty($client) || !is_string($serial) || strlen($serial)<1 || !is_object($object) )
		{
			return -1*abs(parent::code("传入参数不正确"));
		}
		if(!property_exists($object,"groups"))
		{
			return -1*abs(parent::code("没有用户类型字段"));
		}
		elseif( !is_array($object->groups) || sizeof($object->groups)<1 )
		{
			return -1*abs(parent::code("用户类型字段为空"));
		}
		$groups = "";
		foreach ( $object->groups as $value )
		{
			if( is_string($value) && 0<strlen(trim($value)) )
			{
				$result = query($this->mysql, "select `group`.`indexed` from `group` inner join `client` on"
						."`group`.`company`=`client`.`company` and `client`.`client`=\""
						.$client."\" and `group`.`type`=\"".trim($value)."\"");
				if( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0])
						&& 0<strlen((string)$result[0][0]) )
				{
					$groups .= $result[0][0].",";
					continue;
				}
			}
			return -1*abs(parent::code("含有不可识别的用户类型"));
		}
		if( !isset($groups) || !is_string($groups) || strlen($groups)<1 )
		{
			return -1*abs(parent::code("用户类型字段为空"));
		}
		$result = query($this->mysql, "update `log` set `extra`=\"".$groups."\" where (`client`=\""
					.$client."\" and `serial`=\"".$serial."\")");
		if( true === $result )
		{
			return 0;
		}
		return -1*abs(parent::code("写数据库错误"));
	}
	
	function get($client,$serial,&$object)
	{
		if( empty($client) || !is_string($serial) || strlen($serial)<1 )
		{
			return -1*abs(parent::code("传入参数不正确"));
		}
		$result = query($this->mysql, "select `extra` from `log` where `client`=\""
				.$client."\" and `serial`=\"".$serial."\"");
		if( !is_array($result) || sizeof($result)<1 || !is_array($result[0]) || sizeof($result[0])<1
				|| !is_string($result[0][0]) || strlen($result[0][0])<1 )
		{
			return -1*abs(parent::code("读数据库错误"));
		}
		$groups  = explode(",", trim($result[0][0], ","));
		foreach ( $groups as $value )
		{
			if( !is_numeric($value) )
			{
				continue;
			}
			$select = "select `user`.`user`,`user`.`street`,`group`.`type`,`user`.`password`,`user`.`user_hash`"
					." from `user` inner join `group` on `group`.`indexed`=`user`.`group` and `user`.`group`=\""
					.$value."\"";
			$result = query($this->mysql,$select);
			if( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0]) )
			{
				foreach ( $result as $user )
				{
					$this->list[] = (object)array("user"   => urlencode($user[0]),
												"street"   => urlencode($user[1]),
												"group"    => urlencode($user[2]),
												"password" => urlencode($user[3]),
												"hash"     => urlencode($user[4]),
												"photo"    => urlencode(parent::get_photo($user[4])));
				}
			}
		}
		$this->sum = sizeof($this->list);
		return 0<$this->sum ? 0 : (-1*abs(parent::code("没有符合条件的结果")));
	}
}

class User_login extends Base
{
	public  $detail = "success";
	private $mysql   = null;
	
	function __construct()
	{
		parent::__construct();
		$this->mysql = parent::hadle();
	}
	
	function post($client,$serial,&$object)
	{
		if( empty($client) || !is_string($serial) || strlen($serial)<1 || !is_object($object) )
		{
			return -1*abs(parent::code("传入参数不正确"));
		}
		$fault = -1*abs(parent::check($object,"operator"));
		if( 0 != $fault )
		{
			return $fault;
		}
		if(!property_exists($object,"password"))
		{
			return -1*abs(parent::code("没有密码或旧密码字段"));
		}
		elseif( !is_string($object->password) || strlen($object->password)<1 )
		{
			return -1*abs(parent::code("加密后的密码或旧密码为空"));
		}
		
		$select = "(`client` inner join `register` on "
				."`client`.`device`=`register`.`device`"
				." and `client`.`company` is not null"
				." and `client`.`state`=\"inuse\""
				." and `register`.`state`=\"inuse\""
				." and `register`.`start`<=now() and now()<=`register`.`end`)";
		$select = "select `user`.`indexed` from ".$select
				." inner join `user` on "
				."`client`.`company`=`user`.`company`"
				." and `user`.`forbid`=false"
				." and `client`.`client`=\"".$client."\"";
		$result = query($this->mysql,$select);
		if( !is_array($result) || sizeof($result)<1 || !is_array($result[0]) || sizeof($result[0])<1
				|| !is_numeric($result[0][0]) || $result[0][0]<1 )
		{
			return -1*abs(parent::code("登录失败"));
		}
		$user = $result[0][0];
		
		$result = query($this->mysql,"select `indexed` from `user` where (`password` is null or `password`=\""
				.$object->password."\") and `indexed`=\"".$user."\"");
		if( !is_array($result) || sizeof($result)<1 || !is_array($result[0]) || sizeof($result[0])<1
				|| !is_numeric($result[0][0]) || $result[0][0]<1 )
		{
			return -1*abs(parent::code("密码或旧密码错误"));
		}
		
		$select = "insert into `action` (`state`,`user`,`client`,`ip`) values (\"online\",\""
				.$user."\",\"".$client."\",(select `remote` from `log` where `client`=\""
				.$client."\" and `serial`=\"".$serial
				."\")) on duplicate key update `state`=\"online\",`client`=\""
				.$client."\",`ip`=(select `remote` from `log` where `client`=\""
				.$client."\" and `serial`=\"".$serial."\")";
		$result = query($this->mysql, $select);
		if( false === $result )
		{
			return -1*abs(parent::code("写数据库错误"));
		}
		$result = query($this->mysql,"update `log` set `order`=\"".$user."\",`extra`=\"success\" where `client`=\""
				.$client."\" and `serial`=\"".$serial."\"");
		if( false === $result )
		{
			return -1*abs(parent::code("写数据库错误"));
		}
		return 0;
	}
	
	function get($client,$serial,&$object)
	{
		if( empty($client) || !is_string($serial) || strlen($serial)<1 )
		{
			return -1*abs(parent::code("传入参数不正确"));
		}
		$select = "select count(`action`.`user`) from `action` inner join `log` on "
				."`action`.`client`=`log`.`client` and `action`.`user`=`log`.`order`"
				." and `action`.`state`=\"online\" and `action`.`login`<=now()"
				." and `log`.`client`=\"".$client."\" and `log`.`serial`=\"".$serial."\"";
		$result = query($this->mysql,$select);
		if( !is_array($result) || sizeof($result)<1 || !is_array($result[0]) || sizeof($result[0])<1
				|| !is_numeric($result[0][0]) || $result[0][0]<1 )
		{
			return -1*abs(parent::code("登录失败"));
		}
		return 0;
	}
}

class User_logout extends Base
{
	public  $detail = "success";
	private $mysql   = null;

	function __construct()
	{
		parent::__construct();
		$this->mysql = parent::hadle();
	}
	
	function post($client,$serial,&$object)
	{
		if( empty($client) || !is_string($serial) || strlen($serial)<1 || !is_object($object) )
		{
			return -1*abs(parent::code("传入参数不正确"));
		}
		$fault = -1*abs(parent::check($object,"operator"));
		if( 0 != $fault )
		{
			return $fault;
		}
		$select = "select `action`.`user` from `action` inner join `user` on "
				."`action`.`user`=`user`.`indexed` and `action`.`state`!=\"logout\" and `action`.`state`!=\"offline\""
				." and `user`.`user`=\"".$object->operator."\"";
		$result = query($this->mysql,$select);
		if( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0])
				&& is_numeric($result[0][0]) && 0<$result[0][0] )
		{
			$result = query($this->mysql,"update `action` set `state`=\"logout\" where `user`=\"".$result[0][0]."\"");
			if( false === $result )
			{
				return -1*abs(parent::code("写数据库错误"));
			}
		}
		$update = "update `log` set `extra`=\"success\",`order`="
				."(select `user`.`indexed` from `user` inner join `client` on `client`.`company`=`user`.`company`"
				." and `client`.`client`=\"".$client."\" and `user`.`user`=\"".$object->operator."\")"
				." where `client`=\"".$client."\" and `serial`=\"".$serial."\"";
		$result = query($this->mysql,$update);
		if( false === $result )
		{
			return -1*abs(parent::code("写数据库错误"));
		}
		return 0;
	}
	
	function get($client,$serial,&$object)
	{
		if( empty($client) || !is_string($serial) || strlen($serial)<1 )
		{
			return -1*abs(parent::code("传入参数不正确"));
		}
		$select = "select count(`action`.`user`) from `action` inner join `log` on "
				."`action`.`user`=`log`.`order` and `action`.`state`!=\"logout\" and `action`.`state`!=\"offline\""
				." and `log`.`client`=\"".$client."\" and `log`.`serial`=\"".$serial."\"";
		$result = query($this->mysql,$select);
		if( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0])
				&& is_numeric($result[0][0]) && 0<$result[0][0] )
		{
			return -1*abs(parent::code("登出失败"));
		}
		return 0;
	}
}

class User extends Base
{
	private $fault   = 0;
	private $mysql   = null;
	private $client  = null;
	private $serial  = null;
	private $subtype = null;
	private $mode    = null;
	private $part    = null;
	
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
			$class  = "User".$suffix;
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
	
	private function _area(&$object)
	{
		return $this->doing((string)__FUNCTION__, $object);
	}
	
	private function _group(&$object)
	{
		return $this->doing((string)__FUNCTION__, $object);
	}
	
	private function _list(&$object)
	{
		return $this->doing((string)__FUNCTION__, $object);
	}
	
	private function _login(&$object)
	{
		return $this->doing((string)__FUNCTION__, $object);
	}
	
	private function _logout(&$object)
	{
		return $this->doing((string)__FUNCTION__, $object);
	}
}

?>
