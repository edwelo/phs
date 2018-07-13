<?php

require_once($tpldata["functions_dir"] . "functions-phstchrs-operations.inc");
require_once($tpldata["functions_dir"] . "functions-phstchrs-operations-grades.inc");

###############################

$tpl = file_get_contents($template_file_fullpath);
$terms_arr = array("q1m"=>"q1midterm", "q1e"=>"q1grade", "q2m"=>"q2midterm", "q2e"=>"q2grade");

//save
if(is_numeric($_POST["classId"]) && $_POST["form_id"]) {
	$tmp = save_student_grades();
}

unset($classId);
if($_GET["classId"]) {
	$classInfo_arr = getClassInfo($_GET["classId"]);
	if(is_array($classInfo_arr)) $classId = $_GET["classId"];
}

if($classId) {

	//get class roster info
	$classRosterInfo_arr = get_class_roster_and_grades();

	//absence counts
	$stuAbsCounts_arr = count_absences($classId, $classInfo_arr["quarterInfo"][1], $classInfo_arr["quarterInfo"][2]);
	#dumpvar($stuAbsCounts_arr);

	//update classRosterInfo_arr with stuAbsCounts_arr
	foreach($classRosterInfo_arr as $key=>$data_arr) {
		$q1ma = $stuAbsCounts_arr[$data_arr["studentId"]]["q1m"]["A"] + round($stuAbsCounts_arr[$data_arr["studentId"]]["q1m"]["T"] / 3, 2);
		$q1ea = $stuAbsCounts_arr[$data_arr["studentId"]]["q1e"]["A"] + round($stuAbsCounts_arr[$data_arr["studentId"]]["q1e"]["T"] / 3, 2);
		$q2ma = $stuAbsCounts_arr[$data_arr["studentId"]]["q2m"]["A"] + round($stuAbsCounts_arr[$data_arr["studentId"]]["q2m"]["T"] / 3, 2);
		$q2ea = $stuAbsCounts_arr[$data_arr["studentId"]]["q2e"]["A"] + round($stuAbsCounts_arr[$data_arr["studentId"]]["q2e"]["T"] / 3, 2);
		$classRosterInfo_arr[$key]["q1ma"] = $q1ma;
		$classRosterInfo_arr[$key]["q1ea"] = $q1ea;
		$classRosterInfo_arr[$key]["q2ma"] = $q2ma;
		$classRosterInfo_arr[$key]["q2ea"] = $q2ea;
	}
	#dumpvar($classRosterInfo_arr);

	//class roster
	$tpl = preg_replace("/<!-- class list.*\/class list -->/s", "", $tpl);

	$tpl = str_replace("{courseName}", $classInfo_arr["courseName"], $tpl);
	$tpl = str_replace("{semester}", $ordinal_numbers[$classInfo_arr["semester"]], $tpl);
	$tpl = str_replace("{period}", $ordinal_numbers[$classInfo_arr["period"]], $tpl);

	if(array_key_exists($_GET["action"], $terms_arr)) {

		$mode = "edit";
		$tpldata["back_menu_link"] = preg_replace("/&action=.*/", "", $hrefpre);
		$table_html = file_get_contents($template_file_fullpath . "-endterm.tpl");
		$table_html = str_replace("{form_id}", $_GET["action"], $table_html);
		$table_html = str_replace("{classId}", $classId, $table_html);
		if(substr($_GET["action"],1,1) == "1") {
			$table_html = str_replace("{qtr}", "1st", $table_html);
		} else {
			$table_html = str_replace("{qtr}", "2nd", $table_html);
		}
		$table_html = str_replace("{qtr}", "1st", $table_html);
		$table_html = str_replace("{score}", "{" . $_GET["action"] . "s}", $table_html);
		$table_html = str_replace("{letter}", "{" . $_GET["action"] . "l}", $table_html);
		$table_html = str_replace("{absence}", "{" . $_GET["action"] . "a}", $table_html);
		$table_html = str_replace("{behavior}", "{" . $_GET["action"] . "b}", $table_html);
		if(substr($_GET["action"],2,1) == "e") {
			$table_html = str_replace("{term}", "Grades", $table_html);
		} else {
			$table_html = str_replace("{term}", "Mid Term", $table_html);
		}

		preg_match("/\t*<tr id=row.*?\/tr>/s", $table_html, $matches);
		$row_html = str_replace(" id=row", "", $matches[0]);

		#dumpvar($classRosterInfo_arr);

		$f1 = $_GET["action"] . "s";
		$f2 = $_GET["action"] . "l";
		$f3 = $_GET["action"] . "a";
		$f4 = $_GET["action"] . "b";

		$rows_html = "";
		foreach($classRosterInfo_arr as $row) {
			$studentId = $row["stuid"];

			$new_row = str_replace("{studentId}", $studentId, $row_html);
			$new_row = str_replace("{studentName}", $row["studentName"], $new_row);

			$new_row = str_replace("{" . $f1 . "}", $row[$f1], $new_row);
			$new_row = str_replace("{" . $f2 . "}", $row[$f2], $new_row);
			$new_row = str_replace("{" . $f3 . "}", $row[$f3], $new_row);
			$new_row = str_replace("{" . $f4 . "}", $row[$f4], $new_row);

			$rows_html .= $new_row . "\n";
		}

		#printsql($rows_html);

		$table_html = str_replace($matches[0], $rows_html, $table_html);
		$table_html = str_replace("{classId}", $classId, $table_html);

		$tpl = str_replace("{table_html}", $table_html, $tpl);

	} else {
		$mode = "roster";
		$tpldata["back_menu_link"] = preg_replace("/&classId=.*/", "", $hrefpre);
		$table_html = file_get_contents($template_file_fullpath . "-roster.tpl");
		$link = preg_replace("/&action=.*/", "", $tpldata["hrefpre"]);
		$table_html = str_replace("{q1mlnk}", $link . "&action=q1m", $table_html);
		$table_html = str_replace("{q1elnk}", $link . "&action=q1e", $table_html);
		$table_html = str_replace("{q2mlnk}", $link . "&action=q2m", $table_html);
		$table_html = str_replace("{q2elnk}", $link . "&action=q2e", $table_html);

		preg_match("/\t*<tr id=row.*?\/tr>/s", $table_html, $matches);
		$row_html = str_replace(" id=row", "", $matches[0]);

		#dumpvar($classRosterInfo_arr);

		$rows_html = "";
		foreach($classRosterInfo_arr as $row) {
			$new_row = str_replace("{studentId}", $row["stuid"], $row_html);
			$new_row = str_replace("{studentName}", $row["studentName"], $new_row);
			$row["sscore"] = ""; if($row["q1e"] && $row["q2e"]) { if($row["q1e"] + $row["q2e"]) $row["sscore"] = round(($row["q1e"] + $row["q2e"]) / 2, 0); }
			$row["sletter"] = "";
			$row["sabsence"] = ""; if($row["q1eabs"] + $row["q2eabs"]) $row["sabsences"] = $row["q1eabs"] + $row["q2eabs"];
			$row["sbehavior"] = "";

			foreach($row as $field=>$value) {
				$new_row = str_replace("{" . $field . "}", $value, $new_row);
			}
			$rows_html .= $new_row . "\n";
		}

		#printsql($rows_html);

		$table_html = str_replace($matches[0], $rows_html, $table_html);
		$table_html = str_replace("{classId}", $_GET["classId"], $table_html);

		$tpl = str_replace("{table_html}", $table_html, $tpl);

	}
} else {
	//class list
	$tpl = preg_replace("/<!-- class roster.*\/class roster -->/s", "", $tpl);

	$tpldata["back_menu_link"] = preg_replace("/&t1=.*/", "", $hrefpre);

	$sql = "SELECT
				c.classId,
				e.name AS courseName,
				d.semester,
				d.period,
				COUNT(*) AS countStudents
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
	#$rs = db_query($sql);

	$rs = get_classesGradesSummaries($_SESSION["phssy"], $_SESSION["teacherId"]);

	preg_match("/\t*<tr id=row.*?\/tr>/s", $tpl, $matches);
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