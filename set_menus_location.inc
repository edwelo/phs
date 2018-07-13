<?php

//set or identify the unit

$pattern = "/" . $_SESSION["user_type"] . ".*/i";
$string = file_get_contents($tpldata["data_dir"] . "units.txt");
preg_match($pattern, $string, $matches);

list($tmp, $tpldata["unit_abbrv"], $tpldata["unit_fullname"]) = explode(":", $matches[0]);

//get the menu items for the unit from the menu-<unit>.txt file
//these items must exist in this file for the given unit

unset($tmp, $tmp_arr);
$tmp = file($tpldata["data_dir"] . "menus-" . $tpldata["unit_abbrv"] . ".txt");
foreach($tmp as $k=>$text) {
	list($l1menu, $l2menus) = explode("\t", $text);
	$l2menus = preg_replace("/ *, */", ",", $l2menus);
	$menus[trim($l1menu)] = explode(",", trim($l2menus));
}

$tpldata["topmenu_item"] = "";
$tpldata["leftmenu_item"] = "";
$tpldata["l3menu"] = "";
$tpldata["main_menu_link"] = $hrefpre;
$tpldata["back_menu_link"] = $hrefpre;
$tmp = trim($_GET["t1"]);
if(array_key_exists($tmp, $menus)) {
	$tpldata["topmenu_item"] = $tmp;
	$tmp = trim($_GET["t2"]);
	if(in_array($tmp, $menus[$tpldata["topmenu_item"]])) {
		$tpldata["leftmenu_item"] = $tmp;
	} else {
		$tpldata["leftmenu_item"] = $menus[$tpldata["topmenu_item"]][0];
	}
	$leftmenu_item_str = strtolower(str_replace(" ", "", str_replace("\\", "", $tpldata["leftmenu_item"])));
	$tmp = trim($_GET["t3"]);
	if($tmp) { $tpldata["l3menu"] = $tmp; }
} else {
	$tpldata["topmenu_item"] = "Main Menu";
}

$topmenu_item_str = trim(strtolower(str_replace(" ", "", str_replace("/", "", $tpldata["topmenu_item"]))));

$tpldata["location"] = $tpldata["topmenu_item"];
if($tpldata["leftmenu_item"]) {
	$tpldata["location"] .= " :: " . $tpldata["leftmenu_item"];
	$tpldata["main_menu_link"] = preg_replace("/&t1=.*/", "", $hrefpre);
	$tpldata["back_menu_link"] = preg_replace("/&t2=.*/", "", $hrefpre);
}
if($tpldata["l3menu"]) $tpldata["location"] .= " :: " . $tpldata["l3menu"];

?>