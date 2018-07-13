<?php

if(!$stuid) { //begin show student list
	//$stuid must already be set
	$printstr .= "<br />\n<br />\n<br />\n<span class=alert1>Student not specified. Cannot continue.</span><br />\n";
} else { //end show student list and begin show transcripts

	$tpl = file_get_contents($template_file_fullpath);

	#$sql = "SELECT statusId, date, type, reason, length, notes FROM phs.tbl_status WHERE studentId = $stuid";
	unset($tmp_arr, $fields);
	$fields_arr = array("statusId", "date", "type", "reason", "length", "notes");
	$tmp_arr = get_records("phs.tbl_status", "studentId", $stuid);
	foreach($tmp_arr as $key=>$row) {
		foreach($fields_arr as $field) {
			$data["rs"][$key][$field] = $row[$field];
		}
	}



	$printstr .= str_replace("{incidencesTableRows}", removeTableTop(basichtmltable($data)), $tpl);
} //end show transcript

?>