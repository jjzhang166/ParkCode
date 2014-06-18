<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Frameset//EN">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>road parking</title>
</head>
<body>
<center>
	<form action="index.php" method="post">
		按照JSON格式填写提交的数据: <br>
		<textarea name="json" cols="100" rows="30"></textarea>
		<br> <input type="submit" value="提交POST数据" />
	</form>
	<a target="_blank" href="phpinfo.php">PHP信息</a><br>
	<form action="index.php" method="get">
		client:<input type="text" name="client" /><br>
		serial:<input type="text" name="serial" />
		<br> <input type="submit" value="提交GET请求" />
	</form>
</center>
</body>
</html>
