<?php
//ini_set('display_errors', 'php://stdout');
ini_set('error_reporting', E_ALL);
include_once __DIR__."/"."response.php";
echo "<pre>";
//invalid();
if( 'POST' == $_SERVER['REQUEST_METHOD'] && isset($_POST['json']))
{
	$post = new _Response($_SERVER['REMOTE_ADDR'],$_SERVER['REQUEST_TIME']);
	return $post->_post(json_decode(str_replace(array("\r\n", "\n", "\r"), null, $_POST['json'])));
}
else if( 'GET' == $_SERVER['REQUEST_METHOD']
		&& isset($_SERVER['REMOTE_ADDR']) && isset($_SERVER['REQUEST_TIME'])
		&& isset($_GET['client']) && isset($_GET['serial']) )		
{
	$get  = new _Response($_SERVER['REMOTE_ADDR'],$_SERVER['REQUEST_TIME']);
	return $get->_get($_GET['client'],$_GET['serial']);
}
else
{
	echo "error";
}
echo "</pre>";
?>
