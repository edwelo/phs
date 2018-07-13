<?php

if(!$stuid) { //begin show student list
	$printstr .= "<br />\n<br />\n<br />\n<span class=alert1>Student not specified. Cannot continue.</span><br />\n";
} else { //end show student list and begin show transcripts

	$transcript_arr=student_transcript($stuid);

	$tpl = file_get_contents($template_file_fullpath);

	$tmp_arr = get_records("phs.tbl_course", "", "", "departmentId, name");

	foreach($tmp_arr as $record) {
		if($record["departmentId"] != 15 && $record["departmentId"] >= 1) {

			$class_grade="";
			foreach($transcript_arr as $class_record) {
				if($class_record["coursename"] == $record["name"]) {
					$key = "x" . $class_record["grade"] . substr($class_record["sem-per"], 0, 1);
					$record[$key] = $class_record["ltrgrade"];
				}
			}

			$tableRows .= "<tr>";
			$tableRows .= "<td>" . $record["departmentId"] . "</td>";
			$tableRows .= "<td>" . $record["name"] . "</td>";
			$tableRows .= "<td>" . $record["x91"] . "</td>";
			$tableRows .= "<td>" . $record["x92"] . "</td>";
			$tableRows .= "<td>" . $record["x101"] . "</td>";
			$tableRows .= "<td>" . $record["x102"] . "</td>";
			$tableRows .= "<td>" . $record["x111"] . "</td>";
			$tableRows .= "<td>" . $record["x112"] . "</td>";
			$tableRows .= "<td>" . $record["x121"] . "</td>";
			$tableRows .= "<td>" . $record["x122"] . "</td>";
			$tableRows .= "</tr>\n";
		}
	}

	$tpl = str_replace("{tableRows}", $tableRows, $tpl);

	$printstr .= $tpl . "<br />\n";

} //end show transcript


?>