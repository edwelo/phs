<?php

//select student
if(!$stuid) { //begin show student list
	$printstr .= "<br />\n<br />\n<br />\n<span class=alert1>Student not specified. Cannot continue.</span><br />\n";
} else { //end show student list and begin show transcripts

	$stugrades_arr = student_grades($stuid);
	#dumpvar($stugrades_arr);

	unset($tmp, $courses_arr);
	$tmp = file($config_dir . "data/phs/phs_courses_2013.txt");
	foreach($tmp as $value) {
		$courses_arr[] = explode("\t", $value);
	}
	#dumpvar($courses_arr);

	$tpl = file_get_contents($template_files_path . "studentinfo-auditform-summary.tpl");

	$printstr .= $tpl . "<br />\n";

	$tpl = file_get_contents($template_files_path . "studentinfo-auditform-a.tpl");

	foreach($stugrades_arr as $tmp) {
		unset($ctype, $cgrade);
		$sem = trim($tmp["semester"]);
		$crs = trim($tmp["coursename"]);
		$score = trim($tmp["score"]);
		$ltr = trim($tmp["semletter"]);
		$gpa = trim($tmp["semgpa"]);
		foreach($courses_arr as $course) {
			#echo $course[2] . " :: " . $crs . "<br />\n";
			if(strtolower($crs) == strtolower(trim($course[2]))) {
				$ctype = trim($course[0]);
				$cgrade = trim($course[1]);
				$cabbrv = trim($course[3]);
			}
		}
		if($ctype == "core") {
			$search = "{" . $cabbrv . $sem . "}";
			#echo $ctype . " :: " . $cgrade . " :: " . $crs . " :: " . $cabbrv . " :: " . $search . "<br />\n";
			$tpl = str_replace($search, $score, $tpl);
		}
		if($ctype == "elective") {
			$search = "";
			$replace = "";
			$tpl = str_replace($replace, $replace, $tpl);
		}
		if($ctype == "academy") {
			$search = "";
			$replace = "";
			$tpl = str_replace($replace, $replace, $tpl);
		}
	}
	foreach($courses_arr as $course) {
		$tmp = trim($course[3]);
		$tpl = str_replace("{" . $tmp . "1}", "", $tpl);
		$tpl = str_replace("{" . $tmp . "2}", "", $tpl);
	}
	$printstr .= $tpl;

	$tpl = file_get_contents($template_files_path . "studentinfo-auditform-b.tpl");

	foreach($stugrades_arr as $tmp) {
		unset($ctype, $cgrade);
		$glvlsem = trim($tmp["grade"]) . "." . trim($tmp["semester"]);
		$crs = trim($tmp["coursename"]);
		$score = trim($tmp["score"]);
		foreach($courses_arr as $course) {
			#echo $course[2] . " :: " . $crs . "<br />\n";
			if(strtolower($crs) == strtolower(trim($course[2]))) {
				$ctype = trim($course[0]);
				$cgrade = trim($course[1]);
				$cabbrv = trim($course[3]);
				$tpl = str_replace("{" . $cabbrv . "1}", $glvlsem, $tpl);
				$tpl = str_replace("{" . $cabbrv . "2}", $score, $tpl);
			}
		}
	}
	foreach($courses_arr as $course) {
		$tmp = trim($course[3]);
		$tpl = str_replace("{" . $tmp . "1}", "", $tpl);
		$tpl = str_replace("{" . $tmp . "2}", "", $tpl);
	}
	$printstr .= $tpl;

} //end show transcript

?>