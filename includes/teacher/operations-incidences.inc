<?php

require_once("functions/functions-phstchrs-operations.inc");
require_once("functions/functions-phstchrs-operations-incidences.inc");

//directory where notes are kept
$dir = "data/notes/";
$save_status_message = "";

//students info
$flds = "a.studentId, CONCAT(a.firstName, ' ', a.lastName) AS studentName, c.classId";
$sql = "SELECT $flds FROM phs.tbl_student a, phs.tbl_enrollment b, phs.tbl_schedule c, phs.tbl_class d WHERE a.studentId=b.studentId AND b.enrolId=c.enrolId AND c.classId=d.classId AND d.year = " . $phssy;
$rs = db_query($sql);
foreach($rs as $value) {
	$students[$value["studentId"]] = $value;
}

//check if a student is specified
unset($stuid);
if(is_numeric($_GET["stuid"])) {
	if(array_key_exists($_GET["stuid"], $students)) $stuid=$_GET["stuid"];
}

unset($id, $iid);
if(is_numeric($_GET["id"]) || $_GET["id"] == "new") {
	$id = $_GET["id"];
	if(is_numeric($_GET["iid"]) || $_GET["iid"] == "new") {
		$iid = $_GET["iid"];
	}
}

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

//build incident category select options
$sql = "SELECT DISTINCT category FROM phs.tbl_incident ORDER BY category";
$tmp = db_query($sql);
$incidentCategory_selopts = "";
foreach($tmp as $value) {
	$incidentCategory_selopts .= "<option>" . $value["category"] . "</option>\n";
}

if($id && isset($_GET["iid"])) {
	//intervention view and edit
	$tpldata["back_menu_link"] = preg_replace("/&iid=.*/", "", $hrefpre);

	#dumpvar($_POST);

	//save
	if($_POST["action"] == "saveIntervention") {
		$tmp = save_intervention();
	}

	require_once($script_file_fullpath . "-intervention.inc");

} else if($id && !isset($_GET["iid"])) {
	//incident view and edit
	$tpldata["back_menu_link"] = preg_replace("/&id=.*/", "", $hrefpre);

	#dumpvar($_POST);

	//save
	if($_POST["action"] == "saveIncident") {
		$tmp = save_incident();
	}

	require_once($script_file_fullpath . "-record.inc");

} else if($stuid && !$id) {
	//list notes for a given student id

	unset($files);

	$studentName = $students[$stuid]["studentName"];
	$tpldata["stuid"] = $stuid;

	$id = $stuid . "_";
	//load the incidences
	$sql = "SELECT
				g.incidenId,
				g.incidentDate,
				g.category,
				g.description,
				g.reportedBy
			FROM
				phs.tbl_incident g
			WHERE g.studentId=$stuid
			ORDER BY g.incidentDate DESC";
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
				g.incidentId,
				a.studentId,
				CONCAT(a.firstName, ' ', a.lastName) AS studentName,
				b.grade AS glvl,
				g.incidentDate,
				g.category,
				g.description
			FROM
				phs.tbl_student a,
				phs.tbl_enrollment b,
				phs.tbl_schedule c,
				phs.tbl_class d,
				phs.tbl_incident g
			WHERE
				a.studentId=b.studentId AND
				b.enrolId=c.enrolId AND
				c.classId=d.classId AND
				a.studentId=g.studentId AND
				d.year = $phssy AND
				d.teacherId = " . $_SESSION["teacherId"] . "
			ORDER BY studentName, g.incidentDate DESC";
	$rs = db_query($sql);
	foreach($rs as $value) {
		$data[$value["studentId"]][] = $value;
	}

	echo $error_messages;

	$tpl = file_get_contents(str_replace(".tpl", "-listrecent.tpl", $template_file_fullpath));

	preg_match("/\t+<tr id=row.*?\/tr>/s", $tpl, $matches);
	$trrow_match = $matches[0];
	$trrow_html = str_replace(" id=row", "", $trrow_match);

	preg_match("/<td>(<a href.*)<\/td>/", $trrow_html, $matches);

	#dumpvar($matches);

	unset($table_rows, $table_row);
	$i=1;
	foreach($data as $stuid=>$rows) {
		$table_row = str_replace("{no.}", $i++, $trrow_html);
		$table_row = str_replace("{studentName}", $rows[0]["studentName"], $table_row);
		$tdfieldrows_html = "";
		foreach($rows as $row) {
			$tdfield_html = "<br />" . $matches[1];
			foreach($row as $key=>$value) {
				$tdfield_html = str_replace("{" . $key . "}", $value, $tdfield_html);
			}
			$tdfieldrows_html .= $tdfield_html;
		}
		$table_row = str_replace($matches[1], substr($tdfield_html, 6, 250), $table_row);
		$table_rows .= $table_row . "\n";
	}
	$tpl = str_replace($trrow_match, $table_rows, $tpl);

}

$tpl = str_replace("{save_status_message}", $save_status_message, $tpl);

$printstr .= $tpl . "<br />\n";

?>