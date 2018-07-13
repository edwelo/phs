<?php

$tpl = file_get_contents($template_file_fullpath);
$flds_arr = array("q1m"=>"q1midterm", "q1e"=>"q1grade", "q2m"=>"q2midterm", "q2e"=>"q2grade");

//save
if(is_numeric($_POST["classId"])) {
	if($flds_arr[$_POST["form_id"]]) {
		if(substr($_POST["form_id"],2,1) == "e") {
			foreach($_POST["d1"] as $stuid=>$score) {
				if($score) {
					$sql = "UPDATE phs.tbl_schedule SET " . $flds_arr[$_POST["form_id"]] . " = $score WHERE classId=" . $_POST["classId"] . " AND studentId=$stuid";
					#printsql($sql);
					$tmp = db_query($sql);
				}
			}
		} else {
			foreach($_POST["d1"] as $stuid=>$comment) {
				if($_POST["d2"][$stuid] || $comment) {
					#$data = $_SESSION["teacherId"] . ":" . date("Y-m-d") . ":" . $_POST["d2"][$stuid] . ":" . $comment;
					$data = $_POST["d2"][$stuid] . ":" . $comment;
					$sql = "UPDATE phs.tbl_schedule SET " . $flds_arr[$_POST["form_id"]] . " = '$data' WHERE classId=" . $_POST["classId"] . " AND studentId=$stuid";
					#printsql($sql);
					$tmp = db_query($sql);
				}
			}
		}
	}
	#dumpvar($_POST);
}

if($_GET["classId"]) {

	$sql = "SELECT
			a.studentId,
			a.firstName,
			a.middleName,
			a.lastName,
			a.gender,
			a.birthDate,
			b.grade,
			b.year AS sy,
			d.semester,
			e.name AS courseName,
			d.semester,
			d.period,
			c.q1grade AS q1e,
			c.q1abs AS q1eabs,
			c.q2grade AS q2e,
			c.q2abs AS q2eabs,
			c.q1midterm AS q1m,
			c.q2midterm AS q2m
		FROM
			phs.tbl_student a,
			phs.tbl_enrollment b,
			phs.tbl_schedule c,
			phs.tbl_class d,
			phs.tbl_course e,
			phs.tbl_teacher f
		WHERE a.studentId=b.studentId
			AND b.enrolId=c.enrolId
			AND c.classId=d.classId
			AND d.courseId=e.courseId
			AND d.teacherId=f.teacherId
			AND d.classId='" . $_GET["classId"] . "'
		ORDER BY a.lastName, a.firstName, a.middleName";
	$rs = db_query($sql);

	#dumpvar($rs);

	$tpldata["courseName"] = $rs[0]["courseName"];
	$tpldata["semester"] = $rs[0]["semester"];
	$tpldata["period"] = $rs[0]["period"];
	$tpldata["edit_date"] = "";
	$tpldata["today"] = date("n/j/y"); if($_GET["date"] == $tpldata["today"]) $tpldata["edit_date"] = $_GET["date"];
	for($i=1; $i<=9; $i++) {
		$tpldata["-" . $i . " Days"] = date("n/j/y", mktime(0, 0, 0, date("n"), date("j") - $i, date("y")));
		if($_GET["date"] == $tpldata["-" . $i . " Days"])  $tpldata["edit_date"] = $_GET["date"];
	}
	$tpldata["-1 Day"] = $tpldata["-1 Days"];
	if($tpldata["edit_date"]) {
		//class roster edit
		$tpl = preg_replace("/<!-- class list.*\/class list -->/s", "", $tpl);
		$tpl = preg_replace("/<!-- class roster.*\/class roster -->/s", "", $tpl);

		$tpldata["back_menu_link"] = preg_replace("/&date=.*/", "", $hrefpre);
		$tpldata["edit_dateday"] = date("D n/j/y", strtotime($tpldata["edit_date"]));

		preg_match("/\t*<tr id=row.*\/tr>/s", $tpl, $matches);
		$row_html = str_replace(" id=row", "", $matches[0]);

		$rows_html = "";
		foreach($rs as $row) {
			$new_row = $row_html;
			$row["studentName"] = trim($row["lastName"] . ", " . $row["firstName"] . " " . $row["middleName"]);
			foreach($row as $key=>$value) {
				$new_row = str_replace("{" . $key . "}", $value, $new_row);
			}
			for($i=1; $i<=10; $i++) {
				$new_row = str_replace("{day" . $i . "}", "{" . $row["studentId"] . "_d" . $i . "}", $new_row);
			}
			$rows_html .= $new_row;
		}
		$tpl = str_replace($matches[0], $rows_html, $tpl);

	} else {
		//class roster
		$tpl = preg_replace("/<!-- class list.*\/class list -->/s", "", $tpl);
		$tpl = preg_replace("/<!-- class roster edit.*\/class roster edit -->/s", "", $tpl);

		switch($_GET["action"]) {
			case "q1m":
				$tpldata["back_menu_link"] = preg_replace("/&action=.*/", "", $hrefpre);
				$table_innnerhtml = file_get_contents($template_file_fullpath . "-midterm.tpl");
				$table_innnerhtml = str_replace("{form_id}", $_GET["action"], $table_innnerhtml);
				$table_innnerhtml = str_replace("{qtr}", "1st", $table_innnerhtml);
				break;
			case "q1e":
				$tpldata["back_menu_link"] = preg_replace("/&action=.*/", "", $hrefpre);
				$table_innnerhtml = file_get_contents($template_file_fullpath . "-endterm.tpl");
				$table_innnerhtml = str_replace("{form_id}", $_GET["action"], $table_innnerhtml);
				$table_innnerhtml = str_replace("{qtr}", "1st", $table_innnerhtml);
				break;
			case "q2m":
				$tpldata["back_menu_link"] = preg_replace("/&action=.*/", "", $hrefpre);
				$table_innnerhtml = file_get_contents($template_file_fullpath . "-midterm.tpl");
				$table_innnerhtml = str_replace("{form_id}", $_GET["action"], $table_innnerhtml);
				$table_innnerhtml = str_replace("{qtr}", "2nd", $table_innnerhtml);
				break;
			case "q2e":
				$tpldata["back_menu_link"] = preg_replace("/&action=.*/", "", $hrefpre);
				$table_innnerhtml = file_get_contents($template_file_fullpath . "-endterm.tpl");
				$table_innnerhtml = str_replace("{form_id}", $_GET["action"], $table_innnerhtml);
				$table_innnerhtml = str_replace("{qtr}", "2nd", $table_innnerhtml);
				break;
			default:
				$tpldata["back_menu_link"] = preg_replace("/&classId=.*/", "", $hrefpre);
				$table_innnerhtml = file_get_contents($template_file_fullpath . "-roster.tpl");
				$link = preg_replace("/&action=.*/", "", $tpldata["hrefpre"]);
				$table_innnerhtml = str_replace("{q1mlnk}", $link . "&action=q1m", $table_innnerhtml);
				$table_innnerhtml = str_replace("{q1elnk}", $link . "&action=q1e", $table_innnerhtml);
				$table_innnerhtml = str_replace("{q2mlnk}", $link . "&action=q2m", $table_innnerhtml);
				$table_innnerhtml = str_replace("{q2elnk}", $link . "&action=q2e", $table_innnerhtml);
		}

		preg_match("/\t*<tr id=row.*?\/tr>/s", $table_innnerhtml, $matches);
		$row_html = str_replace(" id=row", "", $matches[0]);

		$rows_html = "";
		foreach($rs as $row) {
			$row["studentName"] = trim($row["lastName"] . ", " . $row["firstName"] . " " . $row["middleName"]);

			$row["sscore"] = "";
			if($row["q1e"] && $row["q2e"]) {
				$tmp = $row["q1e"] + $row["q2e"];
				if($tmp) $row["sscore"] = round($tmp / 2, 0);
			}

			$row["sletter"] = "";

			$row["sabsences"] = "";
			if($row["q1eabs"] + $row["q2eabs"]) $row["sabsences"] = $row["q1eabs"] + $row["q2eabs"];


			if($row["q1e"]) {
				$row["q1elg"] = "F";
				if($row["q1e"] >= 65) $row["q1elg"] = "D";
				if($row["q1e"] >= 70) $row["q1elg"] = "C";
				if($row["q1e"] >= 80) $row["q1elg"] = "B";
				if($row["q1e"] >= 90) $row["q1elg"] = "A";
			}
			if($row["q2e"]) {
				$row["q2elg"] = "F";
				if($row["q2e"] >= 65) $row["q2elg"] = "D";
				if($row["q2e"] >= 70) $row["q2elg"] = "C";
				if($row["q2e"] >= 80) $row["q2elg"] = "B";
				if($row["q2e"] >= 90) $row["q2elg"] = "A";
			}
			if($row["sscore"]) {
				$row["sletter"] = "F";
				if($row["sscore"] >= 65) $row["sletter"] = "D";
				if($row["sscore"] >= 70) $row["sletter"] = "C";
				if($row["sscore"] >= 80) $row["sletter"] = "B";
				if($row["sscore"] >= 90) $row["sletter"] = "A";
			}

			$new_row = str_replace("{studentName}", $row["studentName"], $row_html);
			$new_row = str_replace("{studentId}", $row["studentId"], $new_row);
			$new_row = str_replace("{q1e}", $row["q1e"], $new_row);
			$new_row = str_replace("{q1elg}", $row["q1elg"], $new_row);
			$new_row = str_replace("{q1eabs}", $row["q1eabs"], $new_row);
			$new_row = str_replace("{q2e}", $row["q2e"], $new_row);
			$new_row = str_replace("{q2elg}", $row["q2elg"], $new_row);
			$new_row = str_replace("{q2eabs}", $row["q2eabs"], $new_row);
			$new_row = str_replace("{sscore}", $row["sscore"], $new_row);
			$new_row = str_replace("{sletter}", $row["sletter"], $new_row);
			$new_row = str_replace("{sabsences}", $row["sabsences"], $new_row);

			if($_GET["action"] == "q1m") {
				list($chk,$comments) = explode(":", $row["q1m"]);
				if($chk=="on") { $chk = "checked"; } else { $chk = ""; }
				$new_row = str_replace("{chk}", $chk, $new_row);
				$new_row = str_replace("{comments}", $comments, $new_row);
				$new_row = str_replace("{q2m}", $row["q2m"], $new_row);
			} else if($_GET["action"] == "q2m") {
				list($chk,$comments) = explode(":", $row["q2m"]);
				if($chk=="on") { $chk = "checked"; } else { $chk = ""; }
				$new_row = str_replace("{chk}", $chk, $new_row);
				$new_row = str_replace("{comments}", $comments, $new_row);
				$new_row = str_replace("{q1m}", $row["q1m"], $new_row);
			} else {
				$new_row = str_replace("{q1m}", $row["q1m"], $new_row);
				$new_row = str_replace("{q2m}", $row["q2m"], $new_row);
			}
			$rows_html .= $new_row;
		}

		$table_innnerhtml = str_replace($matches[0], $rows_html, $table_innnerhtml);
		$table_innnerhtml = str_replace("{classId}", $_GET["classId"], $table_innnerhtml);

		$tpl = str_replace("{table_innnerhtml}", $table_innnerhtml, $tpl);
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