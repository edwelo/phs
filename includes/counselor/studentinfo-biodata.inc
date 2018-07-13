<?php

//select student
if(!$stuid) { //begin show student list
	$printstr .= "<br />\n<br />\n<br />\n<span class=alert1>Student not specified. Cannot continue.</span><br />\n";
} else { //end show student list and begin student bio data

	$tpl = file_get_contents($template_file_fullpath);

	foreach($stubio_arr as $key=>$value) { $tpl = str_replace("{" . $key . "}", $value, $tpl); }

	$printstr .= $tpl . "<br />\n";

} //end student bio data

?>