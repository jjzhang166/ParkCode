<?php 
if( ('POST' == $_SERVER['REQUEST_METHOD'] && isset($_POST['json']))
		|| ('GET' == $_SERVER['REQUEST_METHOD'] && isset($_GET['client']) && isset($_GET['serial'])) )
{
	include_once 'road_park/request.php';
}else
{
	include_once 'test.php';
}

?>
