<?php
//functions
//require_once($tpldata["functions_dir"] . "functions.inc");
//require_once($tpldata["functions_dir"] . "functions-db.inc");
//require_once($tpldata["functions_dir"] . "functions-tables.inc");


//this section is only here for testing purposes. Remove for production
if($_GET["test"]==1) require_once($tpldata["includes_dir"] . "show_values.inc");

//set the unit or organizational entity and the top menu item
//identify the scripts to run based on the menu selections and set the location indicator
require_once("set_menus_location.inc");

//initialize these variables to be used to insert custom css and js
#unset($custom_js, $custom_css);

//set script files directory
if($menu_mode == "common") {
	$scripts_dir = "common/";
} else {
	$scripts_dir = strtolower(str_replace(" ", "", $tpldata["unit_abbrv"])) . "/";
}

$script_files_path = $tpldata["includes_dir"] . $scripts_dir;
$template_files_path = $tpldata["templates_dir"] . $scripts_dir;
$templater_files_path = $tpldata["templaters_dir"] . $scripts_dir;

$tpldata["jsScript"] = "null.js";

//set main html
$main_html = file_get_contents("main.tpl");

//run the scripts, creates dynamic html
if($tpldata["topmenu_item"] == "Main Menu" || !$_GET["t2"]) {
	//no menu item selected, opens main menu page
	$main_html = preg_replace("/<!-- location bar.*\/location bar -->/s", $tpldata["location"], $main_html);
	require_once("mainmenu.inc");
} else {

	if(is_file($script_files_path . $topmenu_item_str . ".inc")) {
		$script_file_fullpath = $script_files_path . $topmenu_item_str . ".inc";
		$template_file_fullpath = $template_files_path . $topmenu_item_str . ".tpl";
		$templater_file_fullpath = $templater_files_path . $topmenu_item_str . ".inc";
	} else {
		$script_file_fullpath = $script_files_path . $topmenu_item_str . "-" . $leftmenu_item_str . ".inc";
		$template_file_fullpath = $template_files_path . $topmenu_item_str . "-" . $leftmenu_item_str . ".tpl";
		$templater_file_fullpath = $templater_files_path . $topmenu_item_str . "-" . $leftmenu_item_str . ".inc";
	}

	if(is_file($script_file_fullpath)) {
		require_once($script_file_fullpath);
	} else {
		if(is_file($template_file_fullpath)) {
			$tpl = file_get_contents($template_file_fullpath);
		} else {
			$tpl = file_get_contents("under_construction.txt");
		}
	}
}

$db->close;

$main_html = str_replace("<!-- insert dynamic html -->", $tpl, $main_html);

//insert custom styles and scripts into main html
//to insert these, the value of the $custom_js and $custom_css variables
//must be set
#if(is_file("custom_css")) $main_html = str_replace("<!-- insert custom css here -->", "<link href='{commons_dir}${custom_css}' rel='stylesheet' type='text/css'>", $main_html);
if(is_file("custom_css")) $main_html = str_replace("<!-- insert custom css here -->", file_get_contents("custom.css"), $main_html);
if(is_file("custom_js")) $main_html = str_replace("<!-- insert custom javascript here -->", 	"<script type='text/javascript' language='javacript' src='../../commons/${custom_js}'></script>", $main_html);

//insert dynamic data
foreach($tpldata as $key=>$value) {
	if(is_array($value)) {
		foreach($value as $k=>$v) { $main_html = str_replace("{" . $k . "}", $v, $main_html); }
	} else {
		$main_html = str_replace("{" . $key . "}", $value, $main_html);
	}
}
?>
