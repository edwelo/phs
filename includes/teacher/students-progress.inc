<?php

$tpl = file_get_contents($template_file_fullpath);

if($_GET["stuid"]) {
	list($tmp1, $tmp2) = explode(",", $_GET["stuid"]);
	$data = get_records2("phs.tbl_student", "studentId", $tmp1);
	if($data[0]["studentId"] == $tmp1) {
		$stuid = $tmp1;
		$deptid = $tmp2;
	}
}

if($stuid) { //student form

	$tpl = preg_replace("/<!-- student list.*\/student list -->/s", "", $tpl);

	//student info
	if(preg_match("/\d\d\d\d-\d\d-\d\d/", $data[0]["birthDate"])) {
		$year = substr($data[0]["birthDate"], 0, 4);
		$monthdate = substr($data[0]["birthDate"], 5, 5);
		$currentAge = date("Y") - $year;
		if($monthdate < date("m-d")) $currentAge--;
		$tpl = str_replace("{currentAge}", $currentAge, $tpl);
	} else {
		$tpl = str_replace("{currentAge}", "invalid birth date", $tpl);
	}

	$tpl = str_replace("{studentId}", $data[0]["studentId"], $tpl);
	$studentName =  $data[0]["firstName"];
	if($data[0]["middleName"]) $studentName .= " " . $data[0]["middleName"];
	$studentName .= " " . $data[0]["lastName"];
	$tpl = str_replace("{studentName}", $studentName, $tpl);
	$tpl = str_replace("{gender}", $data[0]["gender"], $tpl);
	$tpl = str_replace("{currentLevel}", "grade " . $cr_arr[0]["currentLevel"], $tpl);

	$sql = "SELECT
				e.name AS courseName,
				d.year,
				d.semester,
				c.q1grade AS q1score,
				c.q2grade AS q2score,
				c.semscore,
				c.q1abs,
				c.q2abs
			FROM
				phs.tbl_schedule c,
				phs.tbl_class d,
				phs.tbl_course e
			WHERE
				c.classId=d.classId AND
				d.courseId=e.courseId AND
				c.studentID=$stuid AND
				e.departmentId=" . $deptid . "
			ORDER BY
				d.year,
				d.semester";
	unset($data);
	$data = db_query($sql);

	preg_match("/\t*<tr id=row_deptinfo.*?\/tr>/s", $tpl, $matches);

	$htmlrows = ""; $htmlrow = ""; unset($abs_arr); $i=1;
	foreach($data as $row) {
		$row["yrsem"] = $row["year"] . "." . $row["semester"];
		$abs_arr[$row["yrsem"] . ".1"] = $row["q1abs"];
		$abs_arr[$row["yrsem"] . ".2"] = $row["q2abs"];
		$htmlrow = str_replace(" id=row_deptinfo", "", $matches[0]);
		foreach($row as $key=>$value) {
			$htmlrow = str_replace("{" . $key . "}", $value, $htmlrow);
		}
		$htmlrows .= $htmlrow;
	}
	$tpl = str_replace($matches[0], $htmlrows, $tpl);

	#dumpvar($abs_arr);

	$chart_height = 100; $max_abs = 15;
	foreach($abs_arr as $key=>$value) {
		if($value > $max_abs) $value = $max_abs;
		$chart_html .= "<div style='float: left; margin-left: 4px;'>\n";
			$bar_height = round($chart_height * $value/$max_abs, 0);
			$bar_offset = $chart_height - $bar_height;
			$chart_html .= "<div style='width: 6px; height: " . $bar_offset . "px;'></div>\n";
			$chart_html .= "<div style='width: 6px; height: " . $bar_height . "px; background: gray;'></div>\n";
			list($year, $sem, $qtr) = explode(".", $key);
			$chart_html .= "<span style='font-size: xx-small;'>" . $sem . "." . $qtr . "<br />'" . substr($year, -2) . "</span>\n";
		$chart_html .= "</div>\n";
	}
	$chart_html .= "<div style='clear: both;'></div>\n";
	#echo "<pre>"; echo str_replace("<", "&lt;", $chart_html); echo "</pre>";
	$tpl = str_replace("{chart_html}", $chart_html, $tpl);

	//end student form
} else { // student list

	$tpl = preg_replace("/<!-- student form.*\/student form -->/s", "", $tpl);

	$sql = "SELECT
			a.studentId,
			CONCAT(a.firstName, IF(a.middleName, CONCAT(' ', a.middleName), ''), ' ', a.lastName) AS studentName,
			b.grade,
			d.classId,
			e.departmentId,
			e.name AS course,
			c.q1grade AS q1score,
			c.q2grade AS q2score,
			d.semester,
			d.period
		FROM
			phs.tbl_student a,
			phs.tbl_enrollment b,
			phs.tbl_schedule c,
			phs.tbl_class d,
			phs.tbl_course e
		WHERE a.studentId=b.studentId AND
			b.enrolId=c.enrolId AND
			c.classId=d.classId AND
			d.courseId=e.courseId AND
			d.teacherId = " . $_SESSION["teacherId"] . " AND
			d.year = $phssy
		ORDER BY studentName";
	#printsql($sql);
	$data = db_query($sql);

	preg_match("/.*<tr id=row.*\/tr>/", $tpl, $matches);

	unset($table_rows, $table_row);
	foreach($data as $key=>$row) {
		$table_row = str_replace(" id=row", "", $matches[0]);
		$table_row = str_replace("{no.}", $key + 1, $table_row);
		foreach($row as $key=>$value) {
			$table_row = str_replace("{" . $key . "}", $value, $table_row);
		}
		$table_rows .= $table_row;
	}

	$tpl = str_replace($matches[0], $table_rows, $tpl);

} //end student list

$printstr .= $tpl;

?>