<?php

require_once($tpldata["functions_dir"] . "functions-phstchrs-operations.inc");

#dumpvar($_SESSION);

switch($_GET["r"]) {
	case "Data Download":
		$tpl = file_get_contents(str_replace(".tpl", "", $template_file_fullpath) . "-downloaddata.tpl");

		$classesInfo_arr = get_teachersStudentGrades($_SESSION["phssy"], $_SESSION["teacherId"]);
		#dumpvar($classesInfo_arr);

		preg_match("/\t*<tr id=row.*\/tr>/s", $tpl, $matches);
		$row_html = str_replace(" id=row", "", $matches[0]);

		$rows_html = "";
		foreach($classesInfo_arr as $row) {
			$new_row = $row_html;
			foreach($row as $key=>$value) {
				$new_row = str_replace("{" . $key . "}", $value, $new_row);
			}
			$rows_html .= $new_row;
		}

		$tpl = str_replace($matches[0], $rows_html, $tpl);
		$tpl = str_replace("{teacherId}", $_SESSION["teacherId"], $tpl);
		$tpl = str_replace("{phssy}", $_SESSION["phssy"], $tpl);

		break;
	case "Grade Completion":
		$tpl = file_get_contents(str_replace(".tpl", "", $template_file_fullpath) . "-gradecompletion.tpl");

		$classesInfo_arr = get_classesGradesSummaries($_SESSION["phssy"]);
		#dumpvar($classesInfo_arr);

		preg_match("/\t*<tr id=row.*\/tr>/s", $tpl, $matches);
		$row_html = str_replace(" id=row", "", $matches[0]);

		$rows_html = "";
		foreach($classesInfo_arr as $row) {
			if($row["countStudents"]) $row["avgq1Score"] = round($row["sumq1sScores"] / $row["countStudents"], 2);
			$new_row = $row_html;
			foreach($row as $key=>$value) {
				$new_row = str_replace("{" . $key . "}", $value, $new_row);
			}
			$rows_html .= $new_row;
		}

		$tpl = str_replace($matches[0], $rows_html, $tpl);

		break;
	default:
		$tpl = file_get_contents($template_file_fullpath);

		$classList_arr = getClassList($_SESSION["teacherId"], $_SESSION["phssy"]);
		#dumpvar($classList_arr);
		$classId_selopts = "";
		foreach($classList_arr as $value) {
			$classId_selopts .= "<option value=" . $value["classId"] . ">" . $value["courseName"] . " " . $value["semester"] . "." . $value["period"] . "</option>\n";
		}
		$tpl = str_replace("classId_selopts", $classId_selopts, $tpl);

		$tpl = str_replace("{teacherName}", $_SESSION["cn"], $tpl);
}

?>