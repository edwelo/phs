<?php

$tpl = file_get_contents($template_file_fullpath);

if($_GET["stuid"]) {
	$data = get_records2("phs.tbl_student", "studentId", $_GET["stuid"]);
	if($data[0]["studentId"] == $_GET["stuid"]) $stuid=$_GET["stuid"];
}

if(!$stuid) { //list

	$tpl = preg_replace("/<!-- form.*\/form -->/s", "", $tpl);

	$sql = "SELECT
				a.studentId,
				CONCAT(a.firstName, ' ', a.lastName) AS studentName,
				b.grade AS gradeLevel,
				SUM(c.semcredit) AS earnedCredits,
				AVG(c.semGPA) AS gpa
			FROM
				phs.tbl_student a,
				(SELECT * FROM phs.tbl_enrollment t1 WHERE t1.year = $phssy) b,
				phs.tbl_schedule c
			WHERE
				a.studentId=b.studentId AND
				b.enrolId=c.enrolId
				GROUP BY a.studentId
				ORDER BY gradeLevel, studentName";
	#printsql($sql);
	$data = db_query($sql);

	preg_match("/.*<tr id=row.*\/tr>/", $tpl, $matches);
	$tmp = str_replace(" id=row", "", $matches[0]);

	unset($table_rows, $table_row);
	foreach($data as $row) {
		$table_row = $tmp;
		foreach($row as $key=>$value) {
			$table_row = str_replace("{" . $key . "}", $value, $table_row);
		}
		$table_rows .= $table_row;
	}
	$tpl = str_replace($matches[0], $table_rows, $tpl);

} else { //form

	$tpl = preg_replace("/<!-- list.*\/list -->/s", "", $tpl);

	//load earned credits at each grade level

	$sql = "SELECT
				a.studentId,
				CONCAT(a.firstName, ' ', a.lastName) AS studentName,
				a.gender,
				a.birthDate,
				b.year AS schoolYear,
				MAX(b.grade) AS currentLevel,
				COUNT(*) AS attempted,
				SUM(c.semcredit) AS earned
			FROM
				phs.tbl_student a,
				phs.tbl_enrollment b,
				phs.tbl_schedule c
			WHERE a.studentId=b.studentId
			AND b.enrolId=c.enrolId
			AND b.studentID=$stuid
			GROUP BY b.year";
	$cr_arr = db_query($sql);

	echo str_replace("<", "&lt;", $error_messages);
	if(preg_match("/\d\d\d\d-\d\d-\d\d/", $cr_arr[0]["birthDate"])) {
		$year = substr($cr_arr[0]["birthDate"], 0, 4);
		$monthdate = substr($cr_arr[0]["birthDate"], 5, 5);
		$currentAge = date("Y") - $year;
		if($monthdate < date("m-d")) $currentAge--;
		$tpl = str_replace("{currentAge}", $currentAge, $tpl);
	} else {
		$tpl = str_replace("{currentAge}", "invalid birth date", $tpl);
	}

	$tpl = str_replace("{studentId}", $cr_arr[0]["studentId"], $tpl);
	$tpl = str_replace("{studentName}", $cr_arr[0]["studentName"], $tpl);
	$tpl = str_replace("{gender}", $cr_arr[0]["gender"], $tpl);
	$tpl = str_replace("{currentLevel}", "grade " . $cr_arr[0]["currentLevel"], $tpl);

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

} //end show progress

$printstr .= $tpl;

?>