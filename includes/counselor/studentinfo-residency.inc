<?php

if(!$stuid) {
	//$stuid must already be set
	$printstr .= "<br />\n<br />\n<br />\n<span class=alert1>Student not specified. Cannot continue.</span><br />\n";
} else {
	$data["rs"] = get_records("phs.tbl_residence", "studentId", $stuid);
	#dumpvar($data["rs"]);
	$data["tw"] = "100%";

	$printstr .= file_get_contents($template_file_fullpath);
}

?>