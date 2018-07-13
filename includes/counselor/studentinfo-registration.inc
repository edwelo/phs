<?php

$tpl = file_get_contents($template_file_fullpath);

preg_match("/<!-- fields:.*-->/", $tpl, $matches);

$tmp = str_replace("<!-- fields: ", "", $matches[0]);
$tmp = str_replace(" -->", "", $tmp);
$tmp = str_replace(", ", ",", $tmp);
$tmp2 = explode(",", $tmp);
unset($tmp);
foreach($tmp2 as $value) {
	list($f, $l) = explode(" ", $value);
	if(!$l) $l = 20;
	$fields_arr[$f] = $l;
}

foreach($fields_arr as $field=>$fieldlength) {
	$tpl = str_replace("*" . $field . "*", "<input type=text name='$field' value='" . $tpldata[$field] . "' size=$fieldlength />", $tpl);
}

$printstr .= $tpl . "<br />\n";

?>