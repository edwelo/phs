<?php

$data = get_records2("phs.tbl_incident", "incidentId", $id);
#dumpvar($data);

if($id == "new") {
	$mode = "edit";
	$tpl = file_get_contents(str_replace(".tpl", "-new.tpl", $template_file_fullpath));
	$tmp_arr = get_teachers_student_list($_SESSION["teacherId"], $_SESSION["phssy"]);
	$stuid_selopts = "";
	foreach($tmp_arr as $value) {
		$stuid_selopts .= "<option value=" . $value["studentId"] . ">" . $value["studentName"] . "</option>\n";
	}
	$tpl = str_replace("{stuid_selopts}", $stuid_selopts, $tpl);
} else {
	if(is_numeric($_POST["id"]) && $_POST["id"] == $id) {
		$mode = "edit";
		$tpl = file_get_contents(str_replace(".tpl", "-edit.tpl", $template_file_fullpath));
		#echo "id = " . $id . " :: " . $mode . " :: " . $tplfile . "<br />\n";
	} else {
		$mode = "view";
		$tpl = file_get_contents($template_file_fullpath);
		#echo "id = " . $id . " :: " . $mode . " :: " . $tplfile . "<br />\n";
	}
}

$tpl = preg_replace("/<!-- list recent.*\/list recent -->/s", "", $tpl);

if($id=="new") {
	$tpl = preg_replace("/.*<input.*\{date.*/", "", $tpl);
	$data[0]["date"] = "<span class=lbl1>Date: </span><input type=text name=date value='" . date("Y-m-d") . "' size=12 /> &nbsp;&nbsp;&nbsp;New Incident";
	$data[0]["studentId"] = $stuid;
	$data[0]["incidentId"] = "new";
}

if($mode == "view") {
	$incdata = get_records2("phs.tbl_incidentAction", "incidentId", $id);
	unset($fields);
	if(is_array($incdata[0])) {
		foreach($incdata[0] as $key=>$value) { $fields[$key] = ""; }
	} else {
		$fields = $incdata;
	}
	preg_match("/\t+<tr id=row.*/", $tpl, $matches);
	$tablerow_html = str_replace(" id=row", "", $matches[0]);
	$table_rows = "";
	count($incdata) < 5 ? $num_rows = 5 : $num_rows = count($incdata);
	for($i = 0; $i < $num_rows; $i++) {
		$table_row = str_replace("{no.}", $i + 1, $tablerow_html);
		foreach($fields as $key=>$x) {
			$incdata[$i][$key] ? $value = $incdata[$i][$key] : $value = "";
			$table_row = str_replace("{" . $key . "}", $value, $table_row);
		}
		$table_rows .= $table_row;
	}
	$tpl = str_replace($matches[0], $table_rows, $tpl);
}

$tpl = str_replace("{id}", $data[0]["incidentId"], $tpl);
$tpl = str_replace("{stuid}", $data[0]["studentId"], $tpl);
$tpl = str_replace("{studentName}", $students[$data[0]["studentId"]]["studentName"], $tpl);

if($data[0]["incidentDate"] == "0000-00-00") $data[0]["incidentDate"] = "";
if($data[0]["incidentTime"] == "00:00:00") $data[0]["incidentTime"] = "";
if($data[0]["reportedDate"] == "0000-00-00") $data[0]["reportedDate"] = "";
if($data[0]["referredDate"] == "0000-00-00") $data[0]["referredDate"] = "";
if($data[0]["enteredDate"] == "0000-00-00") $data[0]["enteredDate"] = "";
$incidentCategory_selopts = str_replace(">" . $data[0]["category"] . "<", " selected>" . $data[0]["category"] . "<", $incidentCategory_selopts);
$tpl = str_replace("{incidentCategory_selopts}", $incidentCategory_selopts, $tpl);

foreach($data[0] as $key=>$value) {
	$tpl = str_replace("{" . $key . "}", $value, $tpl);
}

?>