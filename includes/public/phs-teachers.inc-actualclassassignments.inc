<?php

if($tchrid) {
	$sql = "SELECT a.studentId, CONCAT(a.firstName, IF(a.middleName, CONCAT(' ', a.middleName), ''), ' ', a.lastName) AS stuname, a.gender, a.birthDate, b.grade, b.year AS sy, d.classId, d.semester, d.period, e.name AS coursename, CONCAT(f.firstName, IF(f.middleName, CONCAT(' ', f.middleName), ''), ' ', f.lastName) AS teacher FROM phs.tbl_student a, phs.tbl_enrollment b, phs.tbl_schedule c, phs.tbl_class d, phs.tbl_course e, phs.tbl_teacher f WHERE a.studentId=b.studentId AND b.enrolId=c.enrolId AND c.classId=d.classId AND d.courseId=e.courseId AND d.teacherId=f.teacherId AND b.year=$phssy AND d.teacherId=$tchrid ORDER BY stuname";
	$rs=rsmany($sql);
	$tmp_arr = array();
	unset($tmp);
	foreach($rs as $value) {
		$tmp[$value["studentId"]]["stuname"] = $value["stuname"];
		$tmp[$value["studentId"]]["sex"] = $value["gender"];
		$tmp[$value["studentId"]]["glvl"] = $value["grade"];
		$tmp[$value["studentId"]][$value["classId"]] = 1; $tmp_arr[$value["classId"]] = $value["coursename"] . " sem " . $value["semester"] . " per " . $value["period"];
	}
	$i=0;
	foreach($tmp as $key=>$value) {
		$data["rs"][$i]["stuid"] = $key;
		$data["rs"][$i]["stuname"] = $value["stuname"];
		$data["rs"][$i]["sex"] = $value["sex"];
		$data["rs"][$i]["glvl"] = $value["glvl"];
		foreach($tmp_arr as $clsid=>$class) { $data["rs"][$i][$class] = $value[$clsid]; }
		$i++;
	}
	$data["atn"]="lllr" . str_repeat("c", count($tmp_arr)) . ",nnnn" . str_repeat("y", count($tmp_arr));
	$printstr .= "<span class=lbl1>student-class matrix for $tchrname</span><br />\n" . basichtmltable($data) . "<br />\n";
} else {
	#$sql = "SELECT d.teacherId AS tchrid, CONCAT(f.firstName, IF(f.middleName, CONCAT(' ', f.middleName), ''), ' ', f.lastName) AS tchrname, COUNT(DISTINCT(d.classId)) AS 'Classes', COUNT(*) AS 'number of students' FROM phs.tbl_student a, phs.tbl_enrollment b, phs.tbl_schedule c, phs.tbl_class d, phs.tbl_course e, phs.tbl_teacher f WHERE a.studentId=b.studentId AND b.enrolId=c.enrolId AND c.classId=d.classId AND d.courseId=e.courseId AND d.teacherId=f.teacherId AND b.year=$phssy GROUP BY d.teacherId ORDER BY tchrname";
	$sql = "SELECT d.teacherId AS tchrid, CONCAT(f.firstName, IF(f.middleName, CONCAT(' ', f.middleName), ''), ' ', f.lastName) AS tchrname, d.semester, d.classId, COUNT(*) AS 'N' FROM phs.tbl_student a, phs.tbl_enrollment b, phs.tbl_schedule c, phs.tbl_class d, phs.tbl_course e, phs.tbl_teacher f WHERE a.studentId=b.studentId AND b.enrolId=c.enrolId AND c.classId=d.classId AND d.courseId=e.courseId AND d.teacherId=f.teacherId AND b.year=$phssy GROUP BY d.teacherId, d.classId, d.semester ORDER BY tchrname";
	$rs = rsmany($sql);
	#dumpvar($rs);
	unset($data, $tmp);
	foreach($rs as $value) {
		$tmp[$value["tchrid"]]["tchrid"] = $value["tchrid"];
		$tmp[$value["tchrid"]]["tchrname"] = $value["tchrname"];
		if($value["semester"] == 1) { $tmp[$value["tchrid"]]["sem1classes"]++; $tmp[$value["tchrid"]]["sem1students"] += $value["N"]; }
		if($value["semester"] == 2) { $tmp[$value["tchrid"]]["sem2classes"]++; $tmp[$value["tchrid"]]["sem2students"] += $value["N"]; }
	}
	foreach($tmp as $value) {
		$value["classes"] = $value["sem1classes"] + $value["sem2classes"];
		$value["students"] = $value["sem1students"] + $value["sem2students"];
		$data["rs"][] = array("tchrid"=>$value["tchrid"], "tchrname"=>$value["tchrname"], "sem1classes"=>$value["sem1classes"], "sem1students"=>$value["sem1students"], "sem2classes"=>$value["sem2classes"], "sem2students"=>$value["sem2students"], "classes"=>$value["classes"], "students"=>$value["students"]);
	}
	$data["atn"] = "llcccccc";
	$data["idlink"] = "?" . $_SERVER["QUERY_STRING"] . "&tchrid=";
	$printstr .= "<span class=lbl1>number of classes and duplicate student count per teacher</span><br />\n" . basichtmltable($data) . "<br />\n";
}

?>