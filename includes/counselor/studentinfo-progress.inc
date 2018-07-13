<?php

//select student
if(!$stuid) { //begin show student list
	$printstr .= "<br />\n<br />\n<br />\n<span class=alert1>Student not specified. Cannot continue.</span><br />\n";
} else { //end show student list and begin show progress

	//load earned credits at each grade level

	$sql = "SELECT
				b.studentId, b.year AS schoolYear,
				COUNT(*) AS attempted,
				SUM(c.semcredit) AS earned
			FROM
				phs.tbl_enrollment b,
				phs.tbl_schedule c
			WHERE b.enrolId=c.enrolId
			AND b.studentID=$stuid
			GROUP BY b.year";
	$cr_arr = db_query($sql);

	echo str_replace("<", "&lt;", $error_messages);

	$tpl = file_get_contents($template_files_path . "studentinfo-progress.tpl");

	$ac = 0; $k = 0;
	foreach($cr_arr as $key=>$value) {
		$k++; $ac += $value["earned"];
		$search = "{cc" . $k . "}";
		$replace = "current earned/needed: " . $value["earned"] . "/" . $value["needed"];
		$tpl = str_replace($search, $replace, $tpl);
		$search = "{ac" . $k . "}";
		$replace = "cumulative earned/needed: " . $ac . "/" . $acneeded;
		$tpl = str_replace($search, $replace, $tpl);
	}

	$printstr .= $tpl;

} //end show progress

?>