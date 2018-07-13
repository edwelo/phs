<?php

	//show the whole schedule

	//load the list

	unset($teachers_arr);
	$tchrassigntbl = "phs.tbl_teacherassignments2013"; //phs.tbl_regtchrassigns2013
	$sql = "SELECT a.teacherId, CONCAT(b.firstName, ' ', b.lastName) AS teacherName FROM $tchrassigntbl a, phs.tbl_teacher b WHERE a.teacherId=b.teacherId ORDER BY teacherName";
	$rs = rsmany($sql);
	foreach($rs as $value) {
		$teachers_arr[$value["teacherId"]]["teacherId"] = $value["teacherId"];
		$teachers_arr[$value["teacherId"]]["teacherName"] = $value["teacherName"];
	}

	$sql = "SELECT teacherId, COUNT(courseId) AS classes FROM $tchrassigntbl GROUP BY teacherId";
	$rs = rsmany($sql);
	foreach($rs as $value) { $teachers_arr[$value["teacherId"]]["classes"] = $value["classes"]; }

	$sql = "SELECT a.teacherId, COUNT(b.studentId) AS students FROM $tchrassigntbl a LEFT JOIN phs.tbl_regclasses2013 b ON a.taId=b.taId GROUP BY a.teacherId";
	$rs = rsmany($sql);
	foreach($rs as $value) { $teachers_arr[$value["teacherId"]]["students"] = $value["students"]; }

	foreach($teachers_arr as $value) {
		$full = $value["classes"]; if($full > 6) $full = 6;
		$xtra = 0; if($value["classes"] > 6) $xtra = $value["classes"] - 6;
		$value["full time workload"] = "<div style='width: " . (6 * 30) . ";'><div style='background-color: tan; width: " . $full * 30 . "px; height: 12px;'></div></div>";
		$value["extra workload"] = "<div style='background-color: tan; width: " . $xtra * 30 . "px; height: 12px;'></div>";
		$data["rs"][] = $value;
	}
	$data["rownums"] = "y";
	$data["atn"] = "clccn";

	$tpldata["hrefpre"] = $hrefpre;
	$tpl = $printstr . basichtmltable($data);

	unset($printstr);

?>