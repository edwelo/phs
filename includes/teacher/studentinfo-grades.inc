<?php

if(!$stuid) { //begin show student list
	$printstr .= "<br />\n<br />\n<br />\n<span class=alert1>Student not specified. Cannot continue.</span><br />\n";
} else { //end show student list and begin show transcripts

	$tpl = file_get_contents($template_file_fullpath);

	unset($data);

	$data["atn"]="lrlllrrrrrrlrr,nnnnnnnnnnnnny,";
	$data["rs"]=student_transcript($stuid);
	$stuname = $data["rs"][0]["stuname"]; $stuid = $data["rs"][0]["stuid"];
	foreach($data["rs"] AS $key=>$value) {
		unset($data["rs"][$key]["stuname"],$data["rs"][$key]["stuid"]);
	}

	$tableRows = preg_replace("/<table.*\/thead>/s", "", basichtmltable($data));

	$printstr .= str_replace("{transcriptTableRows}", $tableRows, $tpl);

} //end show transcript

?>