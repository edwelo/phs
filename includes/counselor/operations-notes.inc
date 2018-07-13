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

unset($noteid);
if($_GET["noteid"]) {
	if($_GET["noteid"] == "new" || file_exists($dir . $_GET["noteid"])) {
		$noteid = $_GET["noteid"];
	} else {
		echo "note " . $_GET["noteid"] . " not found!<br />\n";
	}
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

if($noteid) {
	//note form

	$backlink = "";
	if($stuid) $backlink = "&stuid=$stuid";

	//save the note
	if($_POST) {
		unset($tmp1, $tmp2);
		if(substr($_POST["noteid"], -3) == "new") {
			if($_POST["noteDate"] == date("Y-m-d", strtotime($_POST["noteDate"]))) {
				$tmp1 = str_replace("-", "", $_POST["noteDate"]);
				$tmp1 = substr($tmp1, 2, 10);
				$tmp1 = str_replace("new", $tmp1, $_POST["noteid"]);
			}
		} else {
			$tmp1 = trim($_POST["noteid"]);
		}
		$tmp2 = trim($_POST["notes"]);
		if($tmp1 && $tmp2) {
			if(file_put_contents($dir . $tmp1, $tmp2)) {
				$save_status_message = "<span class=lbl1 style='color: green;'>Note was saved succesfully</span>";
				if($noteid == "new") $noteid = $tmp1;
			}
		}
		if(!$save_status_message) $save_status_message = "<span class=lbl1 style='color: red;'>Note was not be saved</span>";
	}

	//

	//
	if($noteid == "new") {
		$noteid = $stuid . "_new";
		$studentName = $students[$stuid]["studentName"];
		$note = "";
		$noteDate = "<span class=lbl1>Note Date: </span><input type=text name=noteDate value='" . date("Y-m-d") . "' size=12 />";
	} else {
		list($stuid, $noteDate) = explode("_", $noteid);
		$studentName = $students[$stuid]["studentName"];
		$noteDate = substr($noteDate, 2, 2) . "/" . substr($noteDate, 4, 2) . "/20" . substr($noteDate, 0, 2);
 		$note = file_get_contents($dir . $noteid);
	}

	$tpl = preg_replace("/<!-- list.*\/list -->/s", "", $tpl);
	$tpl = preg_replace("/<!-- list recent.*\/list recent -->/s", "", $tpl);
	$tpl = str_replace("{noteid}", $noteid, $tpl);
	$tpl = str_replace("{stuid}", $stuid, $tpl);
	$tpl = str_replace("{studentName}", $studentName, $tpl);
	$tpl = str_replace("{noteDate}", $noteDate, $tpl);
	$tpl = str_replace("{notetext}", $note, $tpl);
	$tpl = str_replace("{backlink}", $backlink, $tpl);

} else if($stuid && !$noteid) {
	//list notes for a given student id

	unset($files);

	$studentName = $students[$stuid]["studentName"];
	$tpldata["stuid"] = $stuid;

	$id = $stuid . "_";
	$dh  = opendir($dir);
	while (false !== ($filename = readdir($dh))) {
		$pos = strpos($filename, $id);
		if($pos !== false) {
			list(, $noteDate) = explode("_", $filename);
			$noteDate = substr($noteDate, 2, 2) . "/" . substr($noteDate, 4, 2) . "/20" . substr($noteDate, 0, 2);
			$files[] = array("filename"=>$filename, "noteDate"=>$noteDate);
		}
	}
	closedir($dh);

	$data["idlink"] = "?" . $hrefpre . "&noteid=";
	$data["tblstyle"] = "bodypanel";

	$tpl = preg_replace("/<!-- form.*\/form -->/s", "", $tpl);
	$tpl = preg_replace("/<!-- list recent.*\/list recent -->/s", "", $tpl);

	preg_match("/.*<tr id=row.*\/tr>/", $tpl, $matches);

	unset($table_rows, $table_row);
	foreach($files as $values) {
		$table_row = str_replace(" id=row", "", $matches[0]);
		$table_row = str_replace("{noteId}", $values["filename"], $table_row);
		$table_row = str_replace("{noteDate}", $values["noteDate"], $table_row);
		$table_rows .= $table_row;
	}
	$tpl = str_replace($matches[0], $table_rows, $tpl);
	$tpl = str_replace("{studentName}", $studentName, $tpl);

} else {
	//list notes by most recent

	$dh  = opendir($dir);
	while (false !== ($filename = readdir($dh))) {
		if(preg_match("/\d+_\d\d\d\d\d\d/", $filename)) {
			list($studentId, $noteDate) = explode("_", $filename);
			$files[$noteDate] = array("filename"=>$filename, "studentId"=>$studentId);
		}
	}
	closedir($dh);

	krsort($files);
	foreach($files as $noteDate=>$values) {
		$noteDate = substr($noteDate, 2, 2) . "/" . substr($noteDate, 4, 2) . "/20" . substr($noteDate, 0, 2);
		$data["rs"][] = array("filename"=>$values["filename"], "studentId"=>$values["studentId"], "studentName"=>$students[$values["studentId"]]["studentName"], "noteDate"=>$noteDate);
	}

	$data["idlink"] = "?" . $hrefpre . "&noteid=";
	$data["tblstyle"] = "bodypanel";

	$tpl = preg_replace("/<!-- form.*\/form -->/s", "", $tpl);
	$tpl = preg_replace("/<!-- list.*\/list -->/s", "", $tpl);

	$tpl = str_replace("{htmltable}", basichtmltable($data), $tpl);
}

$tpl = str_replace("{save_status_message}", $save_status_message, $tpl);

$printstr .= $tpl . "<br />\n";

?>