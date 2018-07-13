<?php

//functions

//print sqls
function printsql($sql) {
    echo "<p style='font-size: small; font-family: monaco, courier; color: red;'>" . str_replace("<","&lt;",$sql) . "</p>\r";
}

//dump a variable helpter
function dumpvarhelp(&$item, $key) {
	$item = str_replace("<", "&lt;", $item);
}

//dump a variable
function dumpvar($var) {
	if(is_array($var)) {
		array_walk_recursive($var, "dumpvarhelp");
	} else {
		$var=str_replace("<","&lt;", $var);
	}
	echo "<pre>"; print_r($var); echo "</pre>\r";
}

//this function generates tabs html
function generate_htmltabs($tabs) {
	if(array_key_exists($_GET["tab"], $tabs)) { $tab = $_GET["tab"]; } else { $tab = 0; }
	$tmp = "<ul id=tablist>\n\t<li>&nbsp;&nbsp;&nbsp;&nbsp;</li>\n";
	$prefix = "t=" . trim($_GET["t"]);
	if(trim($_GET["t1"])) $prefix .= "&t1=" . trim($_GET["t1"]);
	if(trim($_GET["t2"])) $prefix .= "&t2=" . trim($_GET["t2"]);
	if(trim($_GET["t3"])) $prefix .= "&t3=" . trim($_GET["t3"]);
	foreach($tabs as $key=>$value) { $tmp .= "\t<li><a href='?$prefix&tab=$key'>$value</a></li>\n"; }
	$tmp .= "</ul>\n";
	preg_match("/((.*?)(<li><a)){" . ($tab + 1) ."}/s", $tmp, $matches);
	return $tab . ":|:" . str_replace($matches[0], $matches[0] . " class=current", $tmp);
}

//validate date
function validate_date($date) {
	$ret = false;
	if($date == date("Y-m-d", strtotime($date))) $ret = true;
	return $ret;
}

//calculate age
function calculate_age_years($startDate = "", $endDate = "") {
	if(validate_date($startDate)) {
		if(!validate_date($endDate) || $endDate < $startDate) $endDate = date("Y-m-d");
		$startYear = substr($startDate, 0, 4); $startMonthDay = substr($startDate, 5, 10);
		$endYear = substr($endDate, 0, 4); $endMonthDay = substr($endDate, 5, 10);
		$years = $endYear - $startYear;
		if($endMonthDay < $startMonthDay) $years = $years - 1;
		return $years;
	} else {
		die("calculate_age_years error: $startDate = " . $startDate . ", $endDate = " . $endDate . "<br />\n");
	}
}

?>
