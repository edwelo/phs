<?php

require_once($tpldata["functions_dir"] . "functions-studentinfo.inc");

$tpl = file_get_contents($template_file_fullpath);

if($_GET["stuid"]) {
	//student form
	$sql = "SELECT
			a.studentId,
			d.semester,
			d.period,
			e.name As course,
			CONCAT(f.firstName, ' ', f.lastName) AS teacher
		FROM
			phs.tbl_student a,
			phs.tbl_enrollment b,
			phs.tbl_schedule c,
			phs.tbl_class d,
			phs.tbl_course e,
			phs.tbl_teacher f
		WHERE
			a.studentId=b.studentId AND
			b.enrolId=c.enrolId AND
			c.classId=d.classId AND
			d.courseId=e.courseId AND
			d.teacherId=f.teacherId AND
			b.year='" . $phssy . "' AND
			a.studentId = '" . $_GET["stuid"] . "'";
	#printsql($sql);
	$classData_arr = db_query($sql);
	#dumpvar($classData_arr);

	//check if student id is valid
	$valid = false;
	foreach($classData_arr as $value) {
		if($value["teacher"] == $tpldata["cn"]) $valid = true;
	}
	if(!$valid) {
		#php redirect to this file without stuid in the URL
	}

	//insert student bio data
	$tpl = preg_replace("/<!-- student list.*\/student list -->/s", "", $tpl);
	$stubio_arr = student_biodata($_GET["stuid"]);
	foreach($stubio_arr as $key=>$value) {
		$tpl = str_replace("{" . $key . "}", $value, $tpl);
	}

	//insert student class data
	foreach($classData_arr as $value) {
		$tpl = str_replace("{teacher" . $value["semester"] . "." . $value["period"] . "}", $value["teacher"], $tpl);
		$tpl = str_replace("{course" . $value["semester"] . "." . $value["period"] . "}", $value["course"], $tpl);
	}

} else {
	//student list
	$tpl = preg_replace("/<!-- student form.*\/student form -->/s", "", $tpl);
	$sql = "SELECT
			a.studentId,
			CONCAT(a.firstName, IF(a.middleName, CONCAT(' ', a.middleName), ''), ' ', a.lastName) AS studentName,
			a.gender,
			a.birthDate,
			a.placeResidence AS residence,
			b.grade
		FROM
			phs.tbl_student a,
			phs.tbl_enrollment b,
			phs.tbl_schedule c,
			phs.tbl_class d,
			phs.tbl_course e,
			phs.tbl_teacher f
		WHERE
			a.studentId=b.studentId AND
			b.enrolId=c.enrolId AND
			c.classId=d.classId AND
			d.courseId=e.courseId AND
			d.teacherId=f.teacherId AND
			d.teacherId='" . $_SESSION["teacherId"] . "' AND
			b.year='" . $phssy . "'
		GROUP BY a.studentId
		ORDER BY studentName";
	#printsql($sql);
	$data = db_query($sql);

	#dumpvar($data);

	preg_match("/\t*<tr id=row.*?\/tr>/s", $tpl, $matches);
	$rows_html = "";
	foreach($data as $key=>$value) {
		$row_html = str_replace(" id=row", "", $matches[0]);
		$row_html = str_replace("{no.}", $key + 1, $row_html);
		$row_html = str_replace("{studentName}", $value["studentName"], $row_html);
		$row_html = str_replace("{gender}", $value["gender"], $row_html);
		$row_html = str_replace("{age}", student_age($value["birthDate"]), $row_html);
		$row_html = str_replace("{residence}", $value["residence"], $row_html);
		$row_html = str_replace("{responsibleAdult}", $value["responsibleAdult"], $row_html);
		$row_html = str_replace("{phone}", $value["phone"], $row_html);
		$row_html = str_replace("{studentId}", $value["studentId"], $row_html);
		$rows_html .= $row_html;
	}

	$tpl = str_replace($matches[0], $rows_html, $tpl);

}
?>