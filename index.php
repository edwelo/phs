<?php
	ini_set('display_errors',1);
	error_reporting(E_ALL ^ E_NOTICE); //get rid of undefined variable notice
	date_default_timezone_set("Pacific/Palau");

	session_start();
	if($_POST['log_action']=="logout") {
		$_SESSION = array(); session_destroy(); $uid=""; $cn="";
		unset($persid, $_POST);
	}
	
	//default log action
	$tpldata["log_action"] = "login";
	
	//client ip
	$tpldata["client_ip"] = $_SERVER["REMOTE_ADDR"];

	//global variables ($db, $tpldata, $clientip, etc)
	//require_once("globals.inc");

	//authentication
	if($_POST["username"] && $_POST["password"]) {
		require_once("authenticate.inc");
	}

	//which area are we going into
	$areas = array("Administrator", "Counselor", "Teacher", "Student", "Registration", "Public");
	if(in_array($_GET["area"], $areas)) {
		$tpldata["area"] = $_GET["area"];
	} else {
		$tpldata["area"] = "Public";
	}
	
	$tpldata["back_link"] = "?area=" . $tpldata["area"];
	$tpldata["unit_fullname"] = "PHS SIS " . $tpldata["area"] . " Pages";

	//set $uid
	if($_SESSION["uid"] && $_SESSION["cn"]) {
		$uid = $_SESSION["uid"];
		$tpldata["cn"] = $_SESSION["cn"];
		$tpldata["log_action"] = "logout";
	} else {
		unset($uid);
		$tpldata["cn"] = "Anonymous";
	}
	
	//get the content
	if($_POST["log_action"] == "login") {
		$content_html = file_get_contents("login.tpl");
	} else {
		if($uid) {
			if($_GET["t1"]) {
				if($_GET["t1"] == "Menu") {
					require_once("menu.inc");
				} else {
					$t1 = strtolower($_GET["t1"]);
					
					$func = strtolower($tpldata["area"] . "_" . $_GET["t1"]);
					if(is_file("includes/${func}.inc")) {
						require_once($func . ".inc");
					} else {
						if(is_file("includes/${func}.inc")) {
							require_once($func . ".tpl");
						} else {
							
						}	
					}
				}
			} else {
				if(is_file("templates/" . strtolower($tpldata["area"]) . "/welcome.tpl")) {
					$content_html = file_get_contents("templates/" . strtolower($tpldata["area"]) . "/welcome.tpl");
				} else {
					$content_html = "<h1>U N D E R &nbsp;&nbsp; C O N S T R U C T I O N</h1>";
				}	
			}
		} else {
			if(is_file("templates/" . strtolower($tpldata["area"]) . "/welcome.tpl")) {
				$content_html = file_get_contents("templates/" . strtolower($tpldata["area"]) . "/welcome.tpl");
			} else {
				$content_html = "<h1>U N D E R &nbsp;&nbsp; C O N S T R U C T I O N</h1>";
			}	
		}
	}

	$main_html = file_get_contents("main.tpl");

	//
	$content_marker = "<!-- insert dynamic content html -->";
	$main_html = str_replace($content_marker, $content_html, $main_html);
	
	//dynamic page data
	foreach($tpldata as $key=>$value) {
		$main_html = str_replace("{" . $key . "}", $value, $main_html);
	}

	//print
	echo $main_html;

?>
