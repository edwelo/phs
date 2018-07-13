<?php

######
# functions for phstchrs/operations-grades.inc
# eo 130918
######

function count_class_absences($classId) {
	$absences_arr = get_class_absences($classId);
	$startDate = "2013-08-06";
	$endDate = "2013-10-12";
	foreach($absences_arr as $record) {
		if($record["absenceDate"] >= $startDate && $record["absenceDate"] <= $endDate) {
			list($absent, $tardy, ) = explode("|", $record["absenceInfo"]);
			unset($type);
			if($tardy) $type = "T";
			if($absent) $type = "A"; //this needs to come after tardy, A overrides T
			if($type) $absences_counts[$record["studentId"]][$type]++;
		}
	}
	return $absences_counts;
}

function save_student_grades() {
	#dumpvar($_POST);
	//base sqls
	$sqlupdate = "UPDATE phs.tbl_grades SET
				" . $_POST["form_id"] . "s = {v1},
				" . $_POST["form_id"] . "l = {v2},
				" . $_POST["form_id"] . "a = {v3},
				" . $_POST["form_id"] . "b = {v4}
			WHERE
				studentId = '{studentId}' AND
				classId = '" . $_POST["classId"] . "'
			";
	$sqlinsert = "INSERT INTO phs.tbl_grades SET
				studentId = '{studentId}',
				classId = '" . $_POST["classId"] . "',
				" . $_POST["form_id"] . "s = {v1},
				" . $_POST["form_id"] . "l = {v2},
				" . $_POST["form_id"] . "a = {v3},
				" . $_POST["form_id"] . "b = {v4}
			";
	$db=new mysqli("phsmysql.moe","mysql","mysql","phs");
	foreach($_POST["students"] as $studentId=>$grades_arr) {

		//check if record exists, to determine whether to insert or update
		unset($tmp);
		$sql = "SELECT * FROM phs.tbl_grades WHERE studentId='" . $studentId . "' AND classId='" . $_POST["classId"] . "'";
		$rs=$db->query($sql) or die($db->error);
		if($rs->num_rows) { $sql = $sqlupdate; } else { $sql = $sqlinsert; }
		$sql = str_replace("{studentId}", $studentId, $sql);

		unset($letter_grade);
		if(is_numeric($grades_arr["score"])) {
			$sql = str_replace("{v1}", "'" . $grades_arr["score"] . "'", $sql);
			$letter_grade = "F";
			if($grades_arr["score"] >= 65) $letter_grade = "D";
			if($grades_arr["score"] >= 67) $letter_grade = "D+";
			if($grades_arr["score"] >= 70) $letter_grade = "C";
			if($grades_arr["score"] >= 75) $letter_grade = "C+";
			if($grades_arr["score"] >= 80) $letter_grade = "B";
			if($grades_arr["score"] >= 85) $letter_grade = "B+";
			if($grades_arr["score"] >= 90) $letter_grade = "A";
			$grades_arr["letter"] = $letter_grade;
		} else {
			$sql = str_replace("{v1}", "NULL", $sql);
		}
		if($grades_arr["letter"]) {
			$sql = str_replace("{v2}", "'" . $grades_arr["letter"] . "'", $sql);
		} else {
			$sql = str_replace("{v2}", "NULL", $sql);
		}
		if($grades_arr["absence"]) {
			$sql = str_replace("{v3}", "'" . $grades_arr["absence"] . "'", $sql);
		} else {
			$sql = str_replace("{v3}", "NULL", $sql);
		}
		if($grades_arr["behavior"]) {
			$sql = str_replace("{v4}", "'" . $grades_arr["behavior"] . "'", $sql);
		} else {
			$sql = str_replace("{v4}", "NULL", $sql);
		}
		$rs=$db->query($sql) or die($db->error);
	}
	$db->close;
}

function get_class_roster_and_grades() {
	$db=new mysqli("phsmysql.moe","mysql","mysql","phs");
	$sql = "SELECT
				t1.*, t2.*
			FROM
				(SELECT
					a.studentId AS stuid,
					CONCAT(a.lastName, ', ', a.firstName, ' ', a.middleName) AS studentName,
					a.gender, a.birthDate, b.grade, b.year AS sy
				FROM
					phs.tbl_student a,
					phs.tbl_enrollment b,
					phs.tbl_schedule c
				WHERE
					a.studentId=b.studentId AND
					b.enrolId=c.enrolId AND
					c.classId = '" . $_GET["classId"] . "') t1
				LEFT JOIN
				(SELECT * FROM phs.tbl_grades
				WHERE classId = '" . $_GET["classId"] . "') t2
			ON t1.stuid=t2.studentId
			ORDER BY studentName";
	$rs=$db->query($sql) or die($db->error);
	while($tmp = $rs->fetch_assoc()) { $ret[] = $tmp; }
	return $ret;
	$db->close;
}

function get_class_info() {
	$db=new mysqli("phsmysql.moe","mysql","mysql","phs");
	$sql = "SELECT e.name AS courseName, d.* FROM phs.tbl_class d, phs.tbl_course e WHERE d.courseId=e.courseId AND d.classId='" . $_GET["classId"] . "'";
	$rs=$db->query($sql) or die($db->error);
	$ret = $rs->fetch_assoc();
	return $ret;
	$db->close;
}

?>
