<?php

require_once($tpldata["functions_dir"] . "functions-phstchrs-operations.inc");

function save_student_absences() {

	$db=new mysqli("phsmysql.moe","mysql","mysql","phs");

	foreach($_POST["absinfo"] as $stuid=>$absinfo_arr) {
		if($_POST["date"] == date("Y-m-d", strtotime($_POST["date"]))) {
			if($absinfo_arr[0] || $absinfo_arr[1] || $absinfo_arr[2] || $absinfo_arr[3] || $absinfo_arr[4]) {
				if($absinfo_arr[0]) $absinfo_arr[1] = "";
				if(!$absinfo_arr[0] && !$absinfo_arr[1]) $absinfo_arr[2] = "";
				$absinfo = trim($absinfo_arr[0]) . "|";
				$absinfo .= trim($absinfo_arr[1]) . "|";
				$absinfo .= trim($absinfo_arr[2]) . "|";
				$absinfo .= trim($absinfo_arr[3]);
				if($absinfo == "|||") {
					$sql = "DELETE FROM phs.tbl_absence_phscouns WHERE classId=" . $_POST["classId"] . " AND studentId=" . $stuid . " AND absenceDate='" . $_POST["date"] . "'";
				} else {
					//check if the record exists
					$sql_record_check = "SELECT * FROM phs.tbl_absence_phscouns WHERE classId=" . $_POST["classId"] . " AND studentId=" . $stuid . " AND absenceDate='" . $_POST["date"] . "'";
					$rs = $db->query($sql_record_check) or die($db->error . "<br />" . str_replace("<", "&lt;", $sql_record_check));
					if($rs->num_rows) {
						//record exists, do an update
						$sql = "UPDATE phs.tbl_absence_phscouns
								SET
									absenceInfo='" . $db->real_escape_string($absinfo) . "',
									modifiedBy='" . $_SESSION["persid"] . "', modifiedDate='" . date("Y-m-d") . "'
								WHERE
									classId=" . $_POST["classId"] . " AND studentId=" . $stuid . " AND absenceDate='" . $_POST["date"] . "'";
					} else {
						//record does not exist, do an insert
						$sql = "INSERT INTO phs.tbl_absence_phscouns
								SET
									classId=" . $_POST["classId"] . ", studentId=" . $stuid . ",
									absenceDate='" . $_POST["date"] . "', absenceInfo='" . mysql_real_escape_string($absinfo) . "',
									createdBy='" . $_SESSION["persid"] . "', createdDate='" . date("Y-m-d") . "'";
					}
				}
				#printsql($sql);
				$tmp = $db->query($sql) or die($db->error . "<br />" . str_replace("<", "&lt;", $sql));
			}
		}
	}
	$db->close;
}

$tpl = file_get_contents($template_file_fullpath);

if($_GET["classId"]) {

	//get class info
	$classInfo_arr = getClassInfo($_GET["classId"]);
	#dumpvar($classInfo_arr);

	$tpldata["courseName"] = $classInfo_arr["courseName"];
	$tpldata["semester"] = $ordinal_numbers[$classInfo_arr["semester"]];
	$tpldata["period"] = $ordinal_numbers[$classInfo_arr["period"]];

	//which quarter are we in?
	if($_GET["quarter"] == 1 || $_GET["quarter"] == 2) {
		$quarter = $_GET["quarter"];
	} else {
		$quarter = 1; if(date("Y-m-d") >= $classInfo_arr["quarterInfo"][2]["start"]) $quarter = 2;
	}
	$start = $classInfo_arr["quarterInfo"][$quarter]["start"];
	$mid = $classInfo_arr["quarterInfo"][$quarter]["mid"];
	$end = $classInfo_arr["quarterInfo"][$quarter]["end"];

	$tpldata["quarter"] = $ordinal_numbers[$quarter];
	$tpldata["prevqtrlink"] = preg_replace("/&quarter=\d/", "", $hrefpre) . "&quarter=1";
	$tpldata["nextqtrlink"] = preg_replace("/&quarter=\d/", "", $hrefpre) . "&quarter=2";

	if($_POST["classId"] == $_GET["classId"] && $_POST["date"] && is_array($_POST["absinfo"])) save_student_absences();

	$tpldata["classId"] = $_GET["classId"];

	$sql = "SELECT
			a.studentId,
			a.firstName,
			a.middleName,
			a.lastName,
			b.grade
		FROM
			phs.tbl_student a,
			phs.tbl_enrollment b,
			phs.tbl_schedule c
		WHERE a.studentId=b.studentId
			AND b.enrolId=c.enrolId
			AND c.classId='" . $_GET["classId"] . "'
		ORDER BY a.lastName, a.firstName, a.middleName";
	#printsql($sql);
	$rs = db_query($sql);

	//get the start date parameters of the quarter
	$w = date("w", strtotime($start)); //w is day of week 0 to 6
	list($y, $m, $d) = explode("-", $start);
	settype($m, "int");
	settype($d, "int");
	settype($y, "int");
	if($w > 1) $d = $d - $w + 1; //sets d to the date at the start of the week

	//set attendance days and start dates of each week in the quarter
	unset($attendanceDays_arr, $weekStarts_arr);
	$ws = 1;
	for($i=0; $i<70; $i++) { //day 1 to day 50 in the template file, excluding weekends
		$theDate = date("Y-m-d", mktime(0, 0, 0, $m, $d + $i, $y));
		$w = date("w", strtotime($theDate));
		if($w > 0 && $w < 6) $attendanceDays_arr[] = $theDate;
		if($w == 1) $weekStarts_arr["w" . $ws++ . "d1"] = $theDate;
	}

	//check if a valid edit date has been specified
	unset($edit_date);
	if(in_array($_GET["date"], $attendanceDays_arr)) $edit_date = $_GET["date"];

	//load the absences for the class roster
	$absences_arr = array();
	$sql = "SELECT * FROM phs.tbl_absence_phscouns WHERE classId=" . $_GET["classId"];
	$rs2 = db_query($sql);
	if(is_array($rs2)) {
		foreach($rs2 as $value) {
			$absences_arr[$value["studentId"]][$value["absenceDate"]] = $value["absenceInfo"];
		}
	}

	if($edit_date) {
		//if an edit date has been selected,
		//edit the student absences for that date
		$tpl = preg_replace("/<!-- class list.*\/class list -->/s", "", $tpl);
		$tpl = preg_replace("/<!-- class roster.*\/class roster -->/s", "", $tpl);
		$tpl = str_replace("{edit_date}", $edit_date, $tpl);
		$tpl = str_replace("{dateday}", date("l n/j/y", strtotime($edit_date)), $tpl);

		$tpldata["back_menu_link"] = preg_replace("/&date=.*/", "", $hrefpre);

		preg_match("/\t*<tr id=row.*\/tr>/s", $tpl, $matches);
		$row_html = str_replace(" id=row", "", $matches[0]);

		$rows_html = "";
		foreach($rs as $row) {

			$studentName = trim($row["lastName"] . ", " . $row["firstName"] . " " . $row["middleName"]);
			$new_row = str_replace("{studentName}", $studentName, $row_html);
			$new_row = str_replace("{studentId}", $row["studentId"], $new_row);

			$tmp = $absences_arr[$row["studentId"]][$edit_date];

			$absent = ""; $tardy = ""; $excused = ""; $comment = ""; $edit_designation = 0;

			if($tmp) {
				list($absent, $tardy, $excused, $comment) = explode("|", $tmp);
				if($tardy) $tardy = "checked";
				if($absent) { $absent = "checked"; $tardy = ""; }
				if($excused) $excused = "checked";
				$edit_designation = 1;
			}

			$new_row = str_replace("{absent}", $absent, $new_row);
			$new_row = str_replace("{tardy}", $tardy, $new_row);
			$new_row = str_replace("{excused}", $excused, $new_row);
			$new_row = str_replace("{comment}", $comment, $new_row);
			$new_row = str_replace("{edit_designation}", $edit_designation, $new_row);

			$rows_html .= $new_row;
		}
		$tpl = str_replace($matches[0], $rows_html, $tpl);

	} else {
		//show the class roster and attendance
		$tpl = preg_replace("/<!-- class list.*\/class list -->/s", "", $tpl);
		$tpl = preg_replace("/<!-- class roster edit.*\/class roster edit -->/s", "", $tpl);

		foreach($weekStarts_arr as $key=>$value) {
			$tpl = str_replace("{" . $key . "}", date("n/j", strtotime($value)), $tpl);
		}

		$i=0;
		foreach($attendanceDays_arr as $date) {
			$tpl = str_replace("{date" . $i++ . "}", $date, $tpl);
		}

		$tpldata["back_menu_link"] = preg_replace("/&classId=.*/", "", $hrefpre);

		preg_match("/\t*<tr id=row.*?\/tr>/s", $tpl, $matches);
		$row_html = str_replace(" id=row", "", $matches[0]);

		$rows_html = "";
		foreach($rs as $row) {
			$studentName = trim($row["lastName"] . ", " . $row["firstName"] . " " . $row["middleName"]);
			$new_row = str_replace("{studentName}", $studentName, $row_html);
			$new_row = str_replace("{studentId}", $row["studentId"], $new_row);
			$t = 0; $a = 0;
			foreach($attendanceDays_arr as $key=>$date) {
				$mark = "";
				if($absences_arr[$row["studentId"]][$date]) {
					list($absent, $tardy, $excused, $comment) = explode("|",  $absences_arr[$row["studentId"]][$date]);
					if($tardy) { $mark = "T"; $t++; }
					if($absent) { $mark = "A"; $a++; }
					#if($excused) $mark .= " e";
					#if($comment) $mark .= " c";
				}
				$new_row = str_replace("{day" . ($key + 1) . "}", $mark, $new_row);
			}
			$ta = $a + round($t / 3, 1);
			$new_row = str_replace("{tT}", $t, $new_row);
			$new_row = str_replace("{tA}", $a, $new_row);
			$new_row = str_replace("{tTA}", $ta, $new_row);
			$rows_html .= $new_row;
		}

		$tpl = str_replace($matches[0], $rows_html, $tpl);
	}

} else {
	//class list
	$tpl = preg_replace("/<!-- class roster.*\/class roster -->/s", "", $tpl);
	$tpl = preg_replace("/<!-- class roster edit.*\/class roster edit -->/s", "", $tpl);

	$tpldata["back_menu_link"] = preg_replace("/&t1=.*/", "", $hrefpre);

	$sql = "SELECT
				c.classId,
				e.name AS courseName,
				d.semester,
				d.period,
				COUNT(*) AS numberEnrolled
			FROM
				phs.tbl_schedule c,
				phs.tbl_class d,
				phs.tbl_course e
			WHERE
				c.classId=d.classId AND
				d.courseId=e.courseId AND
				d.teacherId = " . $_SESSION["teacherId"] . " AND
				d.year = $phssy
			GROUP BY d.classId
			ORDER BY d.semester, d.period";
	#printsql($sql);
	$rs = db_query($sql);

	preg_match("/\t*<tr id=row.*\/tr>/", $tpl, $matches);
	$row_html = str_replace(" id=row", "", $matches[0]);

	$rows_html = "";
	foreach($rs as $row) {
		$new_row = $row_html;
		foreach($row as $key=>$value) {
			$new_row = str_replace("{" . $key . "}", $value, $new_row);
		}
		$rows_html .= $new_row;
	}
	$tpl = str_replace($matches[0], $rows_html, $tpl);

}

?>
