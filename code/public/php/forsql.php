<?
	$mysql_host='localhost';
	$mysql_user='root';
	$mysql_password='dudwo135';
	$mysql_db='hurryup';
	
	$conn=mysql_connect($mysql_host, $mysql_user, $mysql_password) or die("fuxk");
	$dbconn=mysql_select_db($mysql_db, $conn);
	
	mysql_query("set names utf8");
	
	$user_id=$_REQUEST['user_id'];
	
	$query="select * from degree where time>SUBDATE(NOW(), INTERVAL 1 minute) AND user_id="+$user_id;
	
	$result=mysql_query($query);
	
	while($row=mysql_fetch_array($result)){
		echo $row[x]." ".$row[y]." ".$row[time];
	}
?>
