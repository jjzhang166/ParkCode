<?php

function connet($host="localhost",$username="root",$passwd="root",$dbname="road_park",
		$port=3306,$socket=null,$flags=0)
{
	$link = mysqli_init();
	if ( $link
			&& mysqli_options($link, MYSQLI_INIT_COMMAND, 'SET AUTOCOMMIT = 1')
			&& mysqli_options($link, MYSQLI_OPT_CONNECT_TIMEOUT, 30)
			&& mysqli_real_connect($link, $host, $username, $passwd, $dbname) )
	{
		return $link;
	}
}

function disconnet($link)
{
	if ( !is_null($link) && is_a($link, "mysqli") && mysqli_close($link) )
	{
		return true;
	}
	return false;
}

function query($link,$sql_query)
{
	//echo "[".$sql_query.";]<br>\n";
	if ( is_a($link, "mysqli") && mysqli_real_query($link,$sql_query) )
	{
		if (mysqli_field_count($link))
		{
			$result = mysqli_store_result($link);
			if ( false != $result )
			{
				$revert = array();
				while ( $row = mysqli_fetch_array($result) )
				{
					array_push($revert,$row);
				}
				mysqli_free_result($result);
				return $revert;
			}
		}else
		{
			return true;
		}
	}
	echo mysqli_error($link);
	return false;
}

?>
