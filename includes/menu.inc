<?php

//set or identify the unit
if($tpldata["area"] == "Public") {
	$tpldata["unit_fullname"] = "PHS SIS Public Pages";
	$content_html = "<p>No menu for public pages.</p>";
} else {
	$pattern = "/" . strtolower($tpldata["area"]) . ".*/i";
	$string = file_get_contents("data/units.txt");
	preg_match($pattern, $string, $matches);

	list(, $tpldata["unit_abbrv"], $tpldata["unit_fullname"]) = explode(":", $matches[0]);

	//get the menu items for the unit from the menu-<unit>.txt file
	//these items must exist in this file for the given unit

	unset($tmp, $tmp_arr);
	$tmp = "data/menus-" . $tpldata["unit_abbrv"] . ".txt";
	if(is_file($tmp)) {
		$tmp = file($tmp);
		foreach($tmp as $k=>$text) {
			list($l1menu, $l2menus) = explode("\t", $text);
			$l2menus = preg_replace("/ *, */", ",", $l2menus);
			$menus[trim($l1menu)] = explode(",", trim($l2menus));
		}

		//var_dump($menus);

		$group_html = "\t<div class='group'>\n%s\t</div>\n";
		$l1_html = "\t\t<div class=l1>%s</div>\n";
		$l2_html = "
				<div class=l2>
					<a %s>
						%s
					</a>
				</div>
		";

		$content_html = "<div class='menu_wrap'>\n";
		foreach($menus as $l1=>$l2menu) {
			$tmp = sprintf($l1_html, $l1);
			foreach($l2menu as $l2) {
				$link = "href='?area={area}&t1=${l1}&t2=${l2}' target='_self'";
				$tmp .= sprintf($l2_html, $link, $l2);
			}
			$content_html .= sprintf($group_html, $tmp);
		}
		$content_html .= "\t<div style='clear: both;'></div>\n</div>\n";

		$tpldata["back_menu_link"] = "?area=" . $tpldata["area"];
		if($_GET["t2"]) $tpldata["back_menu_link"] .= "&t1=" . $_GET["t1"];
		if($_GET["t3"]) $tpldata["back_menu_link"] .= "&t2=" . $_GET["t3"];

		$tpldata["location"] = $tpldata["area"];
		if($_GET["t1"]) $tpldata["location"] .= " : " . $_GET["t1"];
		if($_GET["t2"]) $tpldata["location"] .= " : " . $_GET["t2"];
		if($_GET["t3"]) $tpldata["location"] .= " : " . $_GET["t3"];
	} else {
		$content_html = "<p>No menu for this module.</p>";
	}
}
?>