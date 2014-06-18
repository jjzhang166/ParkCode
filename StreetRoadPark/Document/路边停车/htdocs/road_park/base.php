<?php
include_once __DIR__."/"."mysql.php";

class Base
{
	private $mysql = null;
	private $fault = array(0=>"结果正常",
						1=>"请求内容不是JSON格式",
							"没有客户端字段",
							"客户端值为空",
							"客户端未登记",
							"客户端被禁用",
							"客户端未归属任何公司",
						101=>"没有请求序号字段",
							"请求序号为空",
							"请求序号重复",
							"请求序号含有非法字符",
							"请求序号太长",
						201=>"没有请求类型字段",
							"请求类型为空",
							"无法识别的请求类型",
						301=>"软件未注册",
							"软件已过期",
							"软件被禁用",
						401=>"没有认证码字段",
							"无效的认证码",
							"认证码已超过使用次数",
						501=>"没有请求内容字段",
							"请求内容不是一个对象",
							"请求内容为空",
							"没有子类型字段",
							"子类型为空",
							"无法识别的子类型",
							"没有操作者字段",
							"操作者为空",
							"无法识别的操作者",
							"操作者被停用",
							"操作者未登录",
							"操作者无权执行请求的操作",
							"没有照片字段",
							"没有照片校验码字段",
							"照片字段为空",
							"照片校验码字段为空",
							"不可识别的照片校验码",
							"照片与校验码不匹配",
						601=>"没有客户端可接纳的结果数字段",
							"客户端可接纳的结果数为空",
							"客户端可接纳的结果数不为一个数字",
							"客户端可接纳的结果数为零",
						701=>"没有街道编号字段",
							"无法识别的街道编号",
						801=>"没有符合条件的结果",
						1001=>"没有加密类型字段",
							"不可识别的加密类型",
						1101=>"没有时间字段",
							"时间为空或不可识别",
						1201=>"没有用户类型字段",
							"用户类型字段为空",
							"含有不可识别的用户类型",
							"没有用户列表字段",
							"用户列表字段为空",
							"含有不可识别的用户名",
							"含有缺少员工编号字段的用户信息",
							"含有缺少员工姓名字段的用户信息",
							"含有缺少员工证件号字段的用户信息",
							"含有缺少公司名称字段的用户信",
							"含有缺少服务街道字段的用户信息",
							"含有缺少员工类型字段的用户信息",
							"含有不可识别员工编号的用户信息",
							"含有不可识别员工姓名的用户信息",
							"含有不可识别员工证件号的用户信息",
							"含有不可识别公司名称的用户信息",
							"含有不可识别服务街道的用户信息",
							"含有不可识别员工类型的用户信息",
							"只有部分用户信息被修改或删除",
							"没有密码或旧密码字段",
							"加密后的密码或旧密码为空",
							"密码或旧密码错误",
						1301=>"没有操作时间字段",
							"操作时间为空",
							"没有当前车位编号字段",
							"当前车位编号为空或不可识别",
							"没有进入当前车位时间字段",
							"进入当前车位的时间为空",
							"没有前继车位编号字段",
							"前继车位编号为空或不可识别",
							"没有前继车位参考时间字段",
							"前继车位参考时间为空或该时间此车位无车",
							"没有软件识别的车牌号字段",
							"软件识别的车牌号为空",
							"没有软件识别车牌的可信度字段",
							"软件识别车牌的可信度为空或为非法值",
							"没有校验车牌字段",
							"校验车牌为空",
							"没有收费金额字段",
							"收费金额为空或不为数字",
							"没有after字段",
							"after为空或不可识别",
							"没有photos字段",
							"photos为空或不为数字",
							"没有exit字段",
							"exit为空或不符合格式",
							"没有debt字段",
							"debt为空或不符合格式",
						1401=>"没有bytes字段",
							"bytes为空或不是数字或为零",
							"bytes值与照片实际值不相符",
							"没有所请求的照片内容",
							"所请求的照片字节数太大，无法传输");
	
	function __construct()
	{
		date_default_timezone_set('Asia/Chongqing');
		$this->mysql = connet();
	}
	
	function __destruct()
	{
		if( !is_null($this->mysql) )
		{
			$this->mysql = disconnet($this->mysql);
			$this->mysql = null;
		}
	}
	
	protected function explain($code)
	{
		if( is_numeric($code) )
		{
			$code = abs($code);
			return array_key_exists($code, $this->fault) ? ($this->fault[$code]) : "不明原因的异常" ;
		}
		return "";
	}
	
	protected function code($reason)
	{
		$key = array_search($reason, $this->fault);
		return (false === $key)? (PHP_INT_MAX-1) : $key;
	}
	
	protected function hadle()
	{
		return $this->mysql;
	}
	
	protected function status($client,$serial)
	{
		$result = query($this->mysql,"select `exception` from `log` where `client`=\"".
				(string)$client."\" and `serial`=\"".(string)$serial."\"");
		if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0]) )
		{
			return (int)($result[0][0]);
		}
		return -1*abs($this->code("读数据库错误"));
	}
	
	private   function hash_type($hash)
	{
		if( !is_string($hash) || strlen($hash)<1
				|| ord(array_shift(str_split(count_chars($hash,3))))<48
				|| 122<ord(array_pop(str_split(count_chars($hash,3)))) )
		{
			return "";
		}
		$types = array(2=>"sum8", 4=>"crc16", 8=>"crc32", 16=>"crc64", 32=>"md5",
				40=>"sha1", 56=>"sha224", 64=>"sha256", 96=>"sha384", 128=>"sha512");
		$length = strlen($hash);
		return array_key_exists($length, $types)?($types[$length]):"" ;
	}
	
	protected function get_photo( $hash )
	{
		$type = $this->hash_type($hash);
		if(strlen($type)<1)
		{
			return "";
		}
		$hash = strtoupper($hash);
		// if success get photo ,return base64
		return "";
	}
	
	protected function store_photo( $photo, $hash="", $size=0 )
	{
		$type = $this->hash_type($hash);
		if(strlen($type)<1)
		{
			return -1*abs($this->code("不可识别的照片校验码"));
		}
		if( !is_string($photo) || strlen($photo)<1 )
		{
			return -1*abs($this->code("照片字段为空"));
		}
		$data = base64_decode($photo);
		if( 0!= $size && $size != sizeof($data) )
		{
			return -1*abs($this->code("bytes值与照片实际值不相符"));
		}
		$hash = strtoupper($hash);
		// if success store photo ,return 0
		return 0;
	}
	
	protected function is_time($time)
	{
		if( is_string($time) && 0<strlen($time) )
		{
			return true;
		}
		elseif( is_numeric($time) && 0<=$time )
		{
			return true;
		}
		return false;
	}
	
	protected function check(&$object,$field)
	{
		if( is_null($object) || !is_object($object)
				|| is_null($field) || !is_string($field) )
		{
			return -1*abs($this->code("传入参数不正确"));
		}
		switch ($field)
		{
			case "subtype":
				if(!property_exists($object,$field))
				{
					return -1*abs($this->code("没有子类型字段"));
				}
				elseif(empty($object->subtype))
				{
					return -1*abs($this->code("子类型为空"));
				}
				break;
			case "operator":
				if(!property_exists($object,$field))
				{
					return -1*abs($this->code("没有操作者字段"));
				}
				elseif(empty($object->operator))
				{
					return -1*abs($this->code("操作者为空"));
				}
				break;
			case "photo":
				if(!property_exists($object,$field))
				{
					return -1*abs($this->code("没有照片字段"));
				}
				elseif(empty($object->photo))
				{
					return -1*abs($this->code("照片字段为空"));
				}
				break;
			case "hash":
				if(!property_exists($object,$field))
				{
					return -1*abs($this->code("没有照片校验码字段"));
				}
				elseif(empty($object->hash))
				{
					return -1*abs($this->code("照片校验码字段为空"));
				}
				break;
			case "limit":
				if(!property_exists($object,$field))
				{
					return -1*abs($this->code("没有客户端可接纳的结果数字段"));
				}
				elseif(empty($object->limit))
				{
					return -1*abs($this->code("客户端可接纳的结果数为空"));
				}
				elseif(!is_numeric($object->limit))
				{
					return -1*abs($this->code("客户端可接纳的结果数不为一个数字"));
				}
				elseif($object->limit<1)
				{
					return -1*abs($this->code("客户端可接纳的结果数为零"));
				}
				break;
			case "street":
				if(!property_exists($object,$field))
				{
					return -1*abs($this->code("没有街道编号字段"));
				}
				elseif(empty($object->street))
				{
					return -1*abs($this->code("无法识别的街道编号"));
				}
				break;
			default:
				if(!property_exists($object,$field))
				{
					return -1*abs($this->code("没有".$field."字段"));
				}
				break;
		}
		return 0;
	}
}

?>
