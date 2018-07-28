<?php

	$m = array(
		"Administrator"=>"menus-phsmgmt.txt", 
		"Counselor"=>"menus-phscouns.txt", 
		"Teacher"=>"menus-phstchrs.txt", 
		"Student"=>"menus-phsstudents.txt", 
		"Registration"=>"menus-phsreg.txt"
	);

	unset($tmp, $tmp_arr);
	$tmp = "../data/" . $m[$_GET["pn"]];
	if(is_file($tmp)) {
		$tmp = file($tmp);
		foreach($tmp as $k=>$text) {
			list($l1menu, $l2menus) = explode("\t", $text);
			$l2menus = preg_replace("/ *, */", ",", $l2menus);
			$menus[trim($l1menu)] = explode(",", trim($l2menus));
		}

		//var_dump($menus);

		$group_html = "\t<div style='float: left; margin: 0 2em;'>\n%s\t</div>\n";
		$l1_html = "\t\t<div class=l1>%s</div>\n";
		$l2_html = "
				<div class=l2>
					<a %s>
						%s
					</a>
				</div>
		";

		$content_html = "<p style='font-weight: bold;'>" . $_GET["pn"] . "</p>\n<div class='menu_wrap'>\n";
		foreach($menus as $l1=>$l2menu) {
			$tmp = sprintf($l1_html, $l1);
			foreach($l2menu as $l2) {
				$link = "href='?pn=" . $_GET["pn"] . "&t1=${l1}&t2=${l2}&a=1' target='_self'";
				$tmp .= sprintf($l2_html, $link, $l2);
			}
			$content_html .= sprintf($group_html, $tmp);
		}
		$content_html .= "\t<div style='clear: both;'></div>\n</div>\n";
	} else {
		$content_html = "<p>No menu for this module.</p>";
	}
	
	echo $content_html;
?>