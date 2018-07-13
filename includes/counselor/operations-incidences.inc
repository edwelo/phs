<?php

//directory where notes are kept
$dir = "data/notes/";
$save_status_message = "";

//students info
$students = students_byId($csy); //phs enrollment years are 1 less than sy

//check if a student is specified
unset($stuid);
if(is_numeric($_GET["stuid"])) {
	if(array_key_exists($_GET["stuid"], $students)) $stuid=$_GET["stuid"];
}

unset($id);
if(is_numeric($_GET["id"]) || $_GET["id"] == "new") {
	$id = $_GET["id"];
}

//

$tpl = file_get_contents($template_file_fullpath);

//build $selopts_students
unset($selopts_students);
foreach($students as $key=>$value) {
	$tmp_arr[$value["studentName"]] = $key;
}
ksort($tmp_arr);
foreach($tmp_arr as $xstuname=>$xstuid) {
	$selopts_students .= "<option value=$xstuid>$xstuname</option>\n";
}
if($stuid) $selopts_students = str_replace("=$stuid>", "=$stuid selected>", $selopts_students);
$tpl = str_replace("{selopts_students}", $selopts_students, $tpl);

if($id) {
	//form

	$backlink = "";
	if($stuid) $backlink = "&stuid=$stuid";

	//save
	if($_POST) {
		unset($tmp1, $tmp2);
		if($_POST["statusId"] == "new") {
			$sql = "INSERT INTO phs.tbl_status SET date='" . $_POST["date"] . "', studentId='" . $_POST["studentId"] . "', type='" . $_POST["type"] . "', reason='" . $_POST["reason"] . "', notes='" . $_POST["notes"] . "'";
			$tmp = db_query($sql);

		} else {
			$sql = "UPDATE phs.tbl_status SET type='" . $_POST["type"] . "', reason='" . $_POST["reason"] . "', notes='" . $_POST["notes"] . "' WHERE statusId=" . $_POST["statusId"];
			$tmp = db_query($sql);
		}
	}

	//

	//
	$data = get_records2("phs.tbl_status", "statusId", $id);

	$tpl = preg_replace("/<!-- list.*\/list -->/s", "", $tpl);
	$tpl = preg_replace("/<!-- list recent.*\/list recent -->/s", "", $tpl);

	if($id=="new") {
		$tpl = preg_replace("/.*<input.*\{date.*/", "", $tpl);
		$data[0]["date"] = "<span class=lbl1>Date: </span><input type=text name=date value='" . date("Y-m-d") . "' size=12 /> &nbsp;&nbsp;&nbsp;New Incident";
		$data[0]["studentId"] = $stuid;
		$data[0]["statusId"] = "new";
	}

	$tpl = str_replace("{id}", $data[0]["statusId"], $tpl);
	$tpl = str_replace("{stuid}", $data[0]["studentId"], $tpl);
	$tpl = str_replace("{studentName}", $students[$data[0]["studentId"]]["studentName"], $tpl);
	$tpl = str_replace("{backlink}", $backlink, $tpl);

	foreach($data[0] as $key=>$value) {
		$tpl = str_replace("{" . $key . "}", $value, $tpl);
	}

} else if($stuid && !$id) {
	//list notes for a given student id

	unset($files);

	$studentName = $students[$stuid]["studentName"];
	$tpldata["stuid"] = $stuid;

	$id = $stuid . "_";
	//load the incidences
	$sql = "SELECT
				g.statusId,
				g.date,
				g.type,
				g.reason,
				g.notes
			FROM
				phs.tbl_status g
			WHERE g.studentId=$stuid
			ORDER BY g.date DESC";
	$data = db_query($sql);

	$tpl = preg_replace("/<!-- form.*\/form -->/s", "", $tpl);
	$tpl = preg_replace("/<!-- list recent.*\/list recent -->/s", "", $tpl);

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

	$tpl = str_replace("{studentName}", $studentName, $tpl);

} else {
	//list incidences by most recent

	//load the incidences
	$sql = "SELECT
				g.statusId,
				a.studentId,
				CONCAT(a.firstName, ' ', a.lastName) AS studentName,
				g.date,
				g.type,
				g.reason,
				g.notes
			FROM
				phs.tbl_student a,
				(SELECT t1.* FROM phs.tbl_enrollment t1 WHERE t1.year=$phssy) AS b,
				phs.tbl_status g
			WHERE a.studentId=b.studentId
			AND a.studentId=g.studentId
			ORDER BY g.date DESC, studentName";
	$data = db_query($sql);

	$tpl = preg_replace("/<!-- form.*\/form -->/s", "", $tpl);
	$tpl = preg_replace("/<!-- list.*\/list -->/s", "", $tpl);

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

}

$tpl = str_replace("{save_status_message}", $save_status_message, $tpl);

$printstr .= $tpl . "<br />\n";

?>