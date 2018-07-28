<?php

ini_set('display_errors', 1);
error_reporting(E_ALL ^ E_NOTICE); //get rid of undefined variable notice
#error_reporting(E_ALL | E_STRICT);
date_default_timezone_set("Pacific/Palau");

$areas = array("Administrator", "Counselor", "Teacher", "Student", "Registration");

if($_GET["a"]) {
	$html = "
	<h3>Welcome to PHS SIS App Backend</h3>

	<p>
		<span style='color: grey;'>Look at other modules:</span>&nbsp;&nbsp;
	";
	
	foreach($areas as $area) {
		$html .= "\t\t[ <a href=\"?pn=${area}&a=1\">${area}</a> ]\n";
	}
	
	$html .= "
	</p>
	";

	echo $html;
}

$inc = strtolower(str_replace(" ", "", $_GET["t1"] . "-" . $_GET["t2"]));

if(in_array($_GET["pn"], $areas)) {

	$incDir = "includes/" . $_GET["pn"] . "/";
	
	if($_GET["a"]) {
		require_once("includes/menu.inc");
	}
	
	$db_host = "mysql.moe"; $db_user = "mysql"; $db_pass = "mysql";
	if($_SERVER["REMOTE_ADDRESS"] == "127.0.0.1" || $_SERVER["REMOTE_ADDRESS"] == "::1") {
		$db_host = "localhost";
	}
	
	if($GLOBALS["db"] = new mysqli($db_host, $db_user, $db_pass)) {
		if($_GET["a"]) echo "<p>DB Connect Success!</p>";
	} else {
		if($_GET["a"]) {
			echo "<p>DB Connect Failed!</p>";
			exit;
		} else {
			echo "DB_CONNECT_FAIL";
			exit;
		}
	}

	$func = strtolower(str_replace(" ", "", $_GET["t1"] . "_" . $_GET["t2"]));

	if(isset($_GET["save"])) {
		require_once($incDir . $func . "_save.inc");
	}
	
	if($_GET["years"]) {
		require_once($incDir . "years.inc");
	}
	if($_GET["quarters"]) {
		require_once($incDir . "quarters.inc");
	}

	require_once($incDir . $func . "_read.inc");

	if($_GET["a"]) {
		echo "<p>Resulting \$data array, to be converted to JSON:</p>";
		echo "<pre>"; print_r($data); echo "</pre>";
		$myJSON = json_encode($data);
		echo "<p>JSON to be returned:<br /><span style='font-size: small;'>" . $myJSON . "</span></p>";
	} else {
		//code testing, delete for production
		#if($save_activity) $data["save_activity"] = $save_activity;
		$myJSON = json_encode($data);
		echo $myJSON;
	}
} else {
	echo "AREA_NOT_SPECIFIED";
}

?>