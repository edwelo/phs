<?php

//connection to the mysql server

$sy = ""; //school year
$csy = (date("n") > 6) ? $sy = (date("Y") + 1) : $sy = date("Y"); //current school year, July - August

$phssy = $sy - 1;

$fy = ""; //fiscal year
$cfy = (date("n") > 9) ? $fy = (date("Y") + 1) : $fy = date("Y"); //current fiscal year, September - October

$_SESSION["phssy"] = $phssy;

$ordinal_numbers = array("", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th");

//grade level names
$gradeLevelName[9] = "Freshman";
$gradeLevelName[10] = "Sophomore";
$gradeLevelName[11] = "Junior";
$gradeLevelName[12] = "Senior";

$db = new mysqli("phsmysql.moe", "mysql", "mysql");

$tpldata["functions_dir"] = "functions/";
$tpldata["templates_dir"] = "templates/";
$tpldata["templaters_dir"] = "templaters/";
$tpldata["includes_dir"] = "includes/";
$tpldata["graphics_dir"] = "graphics/";
$tpldata["menus_dir"] = "menus/";
$tpldata["data_dir"] = "data/";

$tpldata["bgcolor"] = "";

$tpldata["home_link"] = "./";

//$tpldata["topmenu_items"] = array(); //will be defined in the unit set up script, set_unit.inc

$tpldata["unit_abbrv"] = "";
$tpldata["unit_fullname"] = "";
$tpldata["topmenu_item"] = "";

$tpldata["location"] = "";

$tpldata["leftmenu"] = "";
$tpldata["leftmenu_item"] = "";

//the popup div top position set by css
$tpldata["popup_top_value"] = 100;
$tpldata["popup_left_value"] = 100;

//client_ip
$clientip=$_SERVER["REMOTE_ADDR"];
$tpldata["client_ip"] = $clientip;

if($clientip) $tpldata["bgcolor"] = "#345";
if($clientip == "127.0.0.1" || $clientip == "::1") $tpldata["bgcolor"] = "#666";
if(strpos($_SERVER["SCRIPT_NAME"], "moeweb0")) $tpldata["bgcolor"] = "red";

$hrefpre = $_SERVER["QUERY_STRING"];

$xy13t1t2 = "xy13=" . $_GET["xy13"];
if($_GET["t1"]) $xy13t1t2 .= "&t1=" . $_GET["t1"];
if($_GET["t2"]) $xy13t1t2 .= "&t2=" . $_GET["t2"];
$tpldata["xy13t1t2"] = $xy13t1t2;

$getpre = "";
if($_GET["xy13"]) $getpre = "<input type=hidden name='xy13' value='" . $_GET["xy13"] . "' />\n";
if($_GET["t1"]) $getpre .= "<input type=hidden name='t1' value='" . $_GET["t1"] . "' />\n";
if($_GET["t2"]) $getpre .= "<input type=hidden name='t2' value='" . $_GET["t2"] . "' />\n";

$tpldata["hrefpre"] = $hrefpre;
$tpldata["getpre"] = $getpre;

$tmp_arr = explode("&", $hrefpre);
unset($tmp_arr[count($tmp_arr) - 1]);
$tpldata["main_back_link"] = implode("&", $tmp_arr);

?>
