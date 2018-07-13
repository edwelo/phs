<?php

if(!$stuid) { //begin show student list
	$printstr .= "<br />\n<br />\n<br />\n<span class=alert1>Student not specified. Cannot continue.</span><br />\n";
} else { //end show student list and begin show transcripts

	$tpl = file_get_contents($template_file_fullpath);

	unset($data, $tlbrows);

	$data["atn"]="lrlllrrrrrrlrr,nnnnnnnnnnnnny,";
	$data["rs"]=student_transcript($stuid);
	$stuname = $data["rs"][0]["stuname"]; $stuid = $data["rs"][0]["stuid"];
	foreach($data["rs"] AS $key=>$value) {
		$tblrows .= "<tr><td>" . $value["year"] . "</td>";
		$tblrows .= "<td>" . $value["grade"] . "</td>";
		$tblrows .= "<td>" . $value["coursename"] . "</td>";
		$tblrows .= "<td>" . $value["ltrgrade"] . "</td>";
		$tblrows .= "<td>" . $value["gpa"] . "</td></tr>\n";
	}

	$tpl = str_replace("{tblrows}", $tblrows, $tpl);

	$printstr .= $tpl . "<br />\n";

} //end show transcript


?>