<?php
include_once __DIR__."/"."mysql.php";

class Photo
{
	public $bytes   = "0";
	public $hash    = "";
	public $photo   = "";

	function valid_format(&$object)
	{
		return true;
	}
	
	function post($prefix,$object)
	{
		if ( isset($object->{'subtype'} )
			&& isset($object->{'operator'})
			&& isset($object->{'bytes'})
			&& isset($object->{'hash'})
			&& is_numeric($object->{'bytes'}) )
		{
			$object->{'subtype'}  = trim($object->{'subtype'});
			$object->{'operator'} = trim($object->{'operator'});
			$object->{'bytes'}    = trim($object->{'bytes'});
			$object->{'hash'}     = trim($object->{'hash'});
			if(isset($object->{'photo'}))
			{
				$object->{'photo'} = trim($object->{'photo'});
			}
			
			$mysql = connet();
			switch ($object->{'subtype'})
			{
				case "upload" :
					break;
				case "download" :
					break;
				default :
					break;
			}
			$content = array_merge($prefix,array(
											trim($object->{'subtype'}),
											trim($object->{'operator'}),
											trim($object->{'bytes'}),
											trim($object->{'hash'}),
											trim($object->{'photo'})));
			$result = process($GLOBALS['program']["photo"],$content);
			if(is_array($result) && !empty($result) )
			{
				return $result[0];
			}
		}
		return false;
	}

	function status()
	{
		return 0;
	}
	
	function get($prefix)
	{
		$output = process($GLOBALS['program']["photo"],$prefix);
		if(!empty($output))
		{
			$this->bytes   = $output[0];
			$this->hash    = $output[1];
			$this->photo   = urlencode($output[2]);
		}
		return true;
	}
}

?>
