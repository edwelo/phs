<?php
#eo 2013-07-14
#rev 2018-07-10

$tpl = file_get_contents("mainmenu.tpl");

preg_match("/<!-- td row.*\/td row -->/s", $tpl, $matches);
$l1menu_html = str_replace("<!-- td row -->", "", $matches[0]);
$l1menu_html = str_replace("<!-- /td row -->", "", $l1menu_html);

preg_match("/\t*<div id=l2menu.*?<\/div>/s", $tpl, $matches2);
$l2menuitem_html = $matches2[0];


$i=0;
$l1menuitems_html = "";
foreach($menus as $l1menu=>$l2menus) {

	$l2menuitems_html = "";	

	if(is_array($l2menus)) {
		foreach($l2menus as $k=>$l2menu_item) {
			$l2menuitems_html .= str_replace("{l2menu}", $l2menu_item, $l2menuitem_html);
		}
	}
	
	$l1menuitems_html .= str_replace($matches2[0], $l2menuitems_html, $l1menu_html);
	$l1menuitems_html = str_replace("{l1menu}", $l1menu, $l1menuitems_html);
	
}

$tpl = str_replace($matches[0], $l1menuitems_html, $tpl);

?>