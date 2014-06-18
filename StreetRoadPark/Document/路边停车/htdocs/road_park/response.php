<?php
include_once __DIR__."/"."function.php";

class Anomaly extends Base
{
	public  $type    = "";
	public  $code    = "";
	public  $detail  = "";
	
	function __construct($code)
	{
		if(is_numeric($code))
		{
			$this->type   = $code<0?"error":"warning";
			$this->code   = (string)$code;
			$this->detail = urlencode(parent::explain($code));
		}
	}
}

class Response_Normal
{
	public $client  = "";
	public $serial  = "";
	public $content = null;

	function __construct($client, $serial, $content)
	{
		$this->client  = $client;
		$this->serial  = $serial;
		$this->content = $content;
	}
}

class Response_Warning
{
	public $client    = "";
	public $serial    = "";
	public $content   = null;
	public $exception = null;

	function __construct($client, $serial, $content, $exception_code)
	{
		$this->client    = $client;
		$this->serial    = $serial;
		$this->content   = $content;
		$this->exception = new Anomaly($exception_code);
	}
}

class Response_Error
{
	public $client  = "";
	public $serial  = "";
	public $exception = null;

	function __construct($client, $serial, $exception_code)
	{
		$this->client    = $client;
		$this->serial    = $serial;
		$this->exception = new Anomaly($exception_code);
	}
}

class _Response extends Base
{
	private $client  = null;
	private $serial  = null;
	private $credit  = null;
	private $type    = null;
	private $ip      = null;
	private $time    = null;
	private $mysql   = null;

	function __construct($ip, $time)
	{
		parent::__construct();
		$this->mysql = parent::hadle();
		$this->ip    = $ip;
		$this->time  = $time;
	}
	
	function __destruct()
	{
		parent::__destruct();
	}
	
	private function base_check(&$json)
	{
		if (!is_object($json))
		{
			return -1*abs(parent::code("请求内容不是JSON格式"));
		}
		elseif(!property_exists($json,"client"))
		{
			return -1*abs(parent::code("没有客户端字段"));
		}
		elseif(empty($json->client))
		{
			return -1*abs(parent::code("客户端值为空"));
		}
		elseif(!property_exists($json,"serial"))
		{
			return -1*abs(parent::code("没有请求序号字段"));
		}
		elseif(0==strlen((string)$json->serial))
		{
			return -1*abs(parent::code("请求序号为空"));
		}
		elseif ( ord(array_shift(str_split(count_chars($json->serial,3))))<32
				|| 126<ord(array_pop(str_split(count_chars($json->serial,3)))) )
		{
			return -1*abs(parent::code("请求序号含有非法字符"));
		}
		elseif (1024<strlen((string)$json->serial))
		{
			return -1*abs(parent::code("请求序号太长"));
		}
		elseif(!property_exists($json,"type"))
		{
			return -1*abs(parent::code("没有请求类型字段"));
		}
		elseif( !is_string($json->type) || strlen(trim($json->type))<1 )
		{
			return -1*abs(parent::code("请求类型为空"));
		}
		elseif(!class_exists((string)ucfirst(trim($json->type))))
		{
			return -1*abs(parent::code("无法识别的请求类型"));
		}
		elseif(!property_exists($json,"content"))
		{
			return -1*abs(parent::code("没有请求内容字段"));
		}
		elseif(!is_object($json->content))
		{
			return -1*abs(parent::code("请求内容不是一个对象"));
		}
		elseif( "{}"==json_encode($json->content)
				|| 0===strpos(json_encode($json->content),"{\"_empty_\":\""))
		{
			return -1*abs(parent::code("请求内容为空"));
		}
		return 0;
	}
	
	private function record(&$json,$ip,$time)
	{
		$error = $this->base_check($json);
		if(0!=$error)
		{
			return $error;
		}
		if(is_null($this->client))
		{
			$this->client = $this->index($json->client);
			$this->serial = $json->serial;
			$this->credit = $json->credit;
			$this->type   = trim($json->type);
		}
		if( is_null($this->client) )
		{//if type is "register",let register class to process
			return "register"==$this->type ? 0 : -4;
		}
		$result = query($this->mysql,"select `company`,`number`,`safety`,`state` from `client` where `client`=\""
				.$this->client."\"");
		if ( !is_array($result) || sizeof($result)<1 )
		{
			return -1*abs(parent::code("客户端未登记"));
		}
		$company = (string)($result[0][0]);
		$number  = (string)($result[0][1]);
		$safety  =   (bool)($result[0][2]);
		$state   = (string)($result[0][3]);
		if("forbid"==$state)
		{
			return -1*abs(parent::code("客户端被禁用"));
		}
		if( !is_numeric($company)|| $company<0 )
		{
			return -1*abs(parent::code("客户端未归属任何公司"));
		}
		$result = query($this->mysql,"select `client` from `log` where `client`=\""
				.$this->client."\" and `serial`=\"".$this->serial."\"");
		if( is_array($result) && 0<sizeof($result) )
		{
			return -1*abs(parent::code("请求序号重复"));
		}
		$select = "select `register`.`state` from `register` inner join `client` on"
				."`client`.`device`=`register`.`device`"
				." and `client`.`client`=\"".$this->client."\"";
		$result = query($this->mysql,$select." and `register`.`start`<=now() and now()<=`register`.`end`"
				." and `register`.`state`=\"inuse\"");
		if ( !is_array($result) || sizeof($result)<1 )
		{
			$result = query($this->mysql,$select." and `register`.`start`<=now() and now()<=`register`.`end`");
			if ( !is_array($result) || sizeof($result)<1 )
			{
				$result = query($this->mysql,$select." and `register`.`end`<now()");
				if ( is_array($result) && 0<sizeof($result) )
				{
					return -1*abs(parent::code("软件已过期"));
				}
				$result = query($this->mysql,$select);
				if ( !is_array($result) || sizeof($result)<1 )
				{
					return -1*abs(parent::code("软件未注册"));
				}
			}
			else
			{
				switch ((string)($result[0][0]))
				{
					case "unused":
						return -1*abs(parent::code("软件未注册"));
					case "used":
						return -1*abs(parent::code("软件已过期"));
					case "forbid":
						return -1*abs(parent::code("软件被禁用"));
					default:
						return 	-1*abs(parent::code("不明原因的错误"));
				}
			}
		}
		if($safety)
		{
			if(!property_exists($json,"credit"))
			{
				return -1*abs(parent::code("没有认证码字段"));
			}
			$result = query($this->mysql,
					"select `counter` from `credit` where `start<=now() and now()<=`end` and `client`=\""
					.$this->client."\" and `credit`=\"".$this->credit."\"");
			if ( !is_array($result) || sizeof($result)<1 )
			{
				return -1*abs(parent::code("无效的认证码"));
			}
			$counter = (string)($result[0][0]);
			if( strlen($counter)<strlen((string)PHP_INT_MAX) && $counter<1 )
			{
				return -1*abs(parent::code("认证码已超过使用次数"));
			}
		}
		else
		{
			$this->credit = null;
		}
		
		if(is_null($this->credit))
		{
			$insert = "insert into `log` (`client`,`serial`,`remote`,`moment`,`credit`,`type`) values (\"".
					$this->client."\",\"".$this->serial."\",\"".$ip."\",\""
					.strftime("%Y-%m-%d %H:%M:%S",$time)."\",null,\"".$this->type."\")";
		}else
		{
			$insert = "insert into `log` (`client`,`serial`,`remote`,`moment`,`credit`,`type`) values (\"".
					$this->client."\",\"".$this->serial."\",\"".$ip."\",\""
					.strftime("%Y-%m-%d %H:%M:%S",$time)."\",\"".$this->credit."\",\"".$this->type."\")";
		}
		$result = query($this->mysql,$insert);
		if( true === $result )
		{
			return 0;
		}
		return -1*abs(parent::code("写数据库错误"));
	}
	
	private function index($client)
	{
		$client  = trim($client);
		$result = query($this->mysql,"select `client` from `client` where `device`=\"".$client."\"");
		if ( !is_array($result) || sizeof($result)<1 )
		{
			$result = query($this->mysql,"select `client` from `client` where `client`=\"".$client."\"");
		}
		if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0]) )
		{
			$client = (string)($result[0][0]);
		}else
		{
			$client = null;
		}
		return $client;
	}
	
	private function types($client,$serial)
	{
		if( is_numeric($client) && is_string($serial) && 0<strlen($serial) )
		{
			$result = query($this->mysql,"select `type` from `log` where `client`=\""
										.$client."\" and `serial`=\"".$serial."\"");
			if ( is_array($result) && 0<sizeof($result) && is_array($result[0]) && 0<sizeof($result[0]) )
			{
				return (string)($result[0][0]);
			}
		}
		return null;
	}
	
	function _post(&$json)
	{
		$error = $this->record($json,$this->ip,$this->time);
		if($error<0)
		{
			$this->client = (is_object($json)&&isset($json->client)) ? $json->client : "";
			$this->serial = (is_object($json)&&isset($json->serial)) ? $json->serial : "";
			$response = new Response_Error($this->client,$this->serial,$error);
			echo urldecode(json_encode($response));
		}else
		{
			$prefix = array($this->client,$this->serial);
			$object = new $this->type;
			if( is_object($object) && is_callable(array($object,'post')) )
			{
				$fault = $object->post($prefix, $json->content);
				if(is_null($this->client))
				{// special for register type
					$this->client = $this->index($json->client);
				}
				$result = query($this->mysql, "update `log` set `exception`=\"".$fault
						."\" where (`client`=\"".$this->client."\" and `serial`=\"".$this->serial."\")");
				if( false === $result )
				{
					return -1*abs(parent::code("写数据库错误"));
				}
	//echo $fault;
				$this->_get($this->client,$this->serial,$this->ip,$this->time);
				return true;
			}
		}
	}
	
	function _get($client,$serial)
	{
		if( strlen((string)$client)<1 || strlen((string)$client)<1 )
		{
			return;
		}
		if(is_null($this->client))
		{
			$this->client = $this->index($client);
			$this->serial = $serial;
		}
		if(is_null($this->type))
		{
			$this->type = $this->types($this->client,$this->serial);
		}
		if(strlen((string)$this->type)<1)
		{
			return;
		}
		$prefix = array($this->client,$this->serial);
		$class  = ucfirst($this->type);
		$object = new $class;
		if( !is_object($object) || !is_callable(array($object,'status')) || !is_callable(array($object,'get')) )
		{
			return;
		}
		$fault = $object->status($this->client,$this->serial);
		if(0==$fault)
		{
			$response = new Response_Normal($this->client,$this->serial,$object->get($prefix));
		}
		elseif (0<$fault)
		{
			$response = new Response_Warning($this->client,$this->serial,$object->get($prefix),$fault);
		}
		else
		{
			$response = new Response_Error($this->client,$this->serial,$fault);
		}
		echo urldecode(json_encode($response));
	}
}
/*
function invalid()
{
	date_default_timezone_set('Asia/Chongqing');
	$mysql = connet();
	query($mysql, "create table if not exists `footprint` "
			."( `server` varchar(20) not null,"
			." `port` smallint not null,"
			." `protocol` varchar(20) not null,"
			." `remote` varchar(20) not null,"
			." `agent` varchar(100) not null,"
			." `rport` smallint not null,"
			." `stime` datetime not null,"
			." `url` varchar(100) not null,"
			." `method` varchar(10) not null,"
			." `data` varchar(20000)  not null)"
			."engine=csv default charset=utf8;");

	switch ($_SERVER['REQUEST_METHOD'])
	{
		case 'GET':
			$input = $_GET;
			break;
		case 'POST':
			$input = $_POST;
			break;
		default:
			break;
	}
	$data = "";
	if(is_array($input))
	{
		foreach ($input as $key => $value)
		{
			$data .= "[".$key."]=>";
			$data .= $value;
		}
	}
	$data = mysqli_real_escape_string($mysql,$data);
	
	query($mysql, "insert into `footprint` (`server`,`port`,`protocol`,`remote`,`agent`,`rport`,`stime`,`url`,`method`,`data`) values (\""
			.$_SERVER['SERVER_ADDR']."\",\""
			.$_SERVER['SERVER_PORT']."\",\""
			.$_SERVER['SERVER_PROTOCOL']."\",\""
			.$_SERVER['REMOTE_ADDR']."\",\""
			.$_SERVER['HTTP_USER_AGENT']."\",\""
			.$_SERVER['REMOTE_PORT']."\",\""
			.strftime("%Y-%m-%d %H:%M:%S",$_SERVER['REQUEST_TIME'])."\",\""
			.$_SERVER['REQUEST_URI']."\",\""
			.$_SERVER['REQUEST_METHOD']."\",\""
			.$data."\")");
	return;
	
	echo $_SERVER['REMOTE_ADDR'];
	echo "\n客户端浏览器和操作系统:";
	echo $_SERVER['HTTP_USER_AGENT'];
	echo "\n客户端端口号:";
	echo $_SERVER['REMOTE_PORT'];
	echo "\n请求时间:";
	echo strftime("%Y-%m-%d %H:%M:%S",$_SERVER['REQUEST_TIME']);
	echo "\n请求的页面:";
	echo $_SERVER['REQUEST_URI'];
	echo "\n请求方法:";
	echo $_SERVER['REQUEST_METHOD'];
	
	if(isset($GLOBALS['decide']['invalid']))
	{
		date_default_timezone_set('Asia/Chongqing');
		$log = array(
				$_SERVER['REMOTE_ADDR'],
				$_SERVER['REMOTE_PORT'],
				$_SERVER['HTTP_USER_AGENT'],
				strftime("%Y-%m-%d %H:%M:%S",$_SERVER['REQUEST_TIME']),
				$_SERVER['REQUEST_METHOD'],
				$_SERVER['REQUEST_URI'],
				$_SERVER['SERVER_NAME'],
				$_SERVER['SERVER_ADDR'],
				$_SERVER['SERVER_PORT'],
				$_SERVER['SERVER_PROTOCOL']);
		switch ($_SERVER['REQUEST_METHOD'])
		{
			case 'GET':
				$input = $_GET;
				break;
			case 'HEAD':
				break;
			case 'POST':
				$input = $_POST;
				break;
			case 'PUT':
				break;
			default:
				break;
		}
		if(is_array($input))
		{
			foreach ($input as $key => $value)
			{
				array_push($log,$key."=>");
				array_push($log,$value);
			}
		}
		process($GLOBALS['decide']['invalid'],$log);
		
		
		
		echo "这不是一个合理的JSON请求.\n";
		echo "\n客户端IP:";
		echo $_SERVER['REMOTE_ADDR'];
		echo "\n客户端浏览器和操作系统:";
		echo $_SERVER['HTTP_USER_AGENT'];
		echo "\n客户端端口号:";
		echo $_SERVER['REMOTE_PORT'];
		echo "\n请求时间:";
		echo strftime("%Y-%m-%d %H:%M:%S",$_SERVER['REQUEST_TIME']);
		echo "\n请求的页面:";
		echo $_SERVER['REQUEST_URI'];
		echo "\n请求方法:";
		echo $_SERVER['REQUEST_METHOD'];
		echo "\n提交的数据:";
		{
			switch ($_SERVER['REQUEST_METHOD'])
			{
				case 'GET':
					$input = $_GET;
					break;
				case 'HEAD':
					break;
				case 'POST':
					$input = $_POST;
					break;
				case 'PUT':
					break;
				default:
					break;
			}
			if(is_array($input))
			{
				foreach ($input as &$value)
				{
					echo $value;
				}
			}
		}
		echo "\n服务器主机名:";
		echo $_SERVER['SERVER_NAME'];
		echo "\n服务器IP:";
		echo $_SERVER['SERVER_ADDR'];
		echo "\n服务器端口号:";
		echo $_SERVER['SERVER_PORT'];
		echo "\n协议版本:";
		echo $_SERVER['SERVER_PROTOCOL'];
	}
}
*/

?>
