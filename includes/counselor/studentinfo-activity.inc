<?php

if(!$stuid) { //begin show student list
	$printstr .= "<br />\n<br />\n<br />\n<span class=alert1>Student not specified. Cannot continue.</span><br />\n";
} else { //end show student list and begin show transcripts

	$transcript_arr=student_transcript($stuid);

	$tpl = file_get_contents($template_file_fullpath);

	//get registration data

	//get incidences data

	//get enrollment data

	//get sessions data

	#$tpl = str_replace("{tableRows}", $tableRows, $tpl);

	$printstr .= $tpl . "<br />\n";

} //end show transcript


?>