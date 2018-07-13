<?php

//directory where notes are kept
$save_status_message = "";

unset($id);
if(is_numeric($_GET["id"]) || $_GET["id"] == "new") {
	$id = $_GET["id"];
}

//

$tpl = file_get_contents($template_file_fullpath);

if($id) {
	//form

	//save
	if($_POST) {
		dumpvar($_POST);

		//
		unset($sql, $incomplete);

		foreach($_POST as $key=>$value) { $_POST[$key] = trim($value); }
		if(!validate_date($_POST["date"])) $incomplete = true;
		if(!$_POST["type"] || !$_POST["title"] || !$_POST["description"]) $incomplete=true;

		if(!$incomplete) {
			if($_POST["activityId"] == "new") {
				$sql = "INSERT INTO phs.tbl_activity SET date='{date}', type='{type}', title='{title}', description='{description}', notes='{notes}', ttlhours='{ttlhours}', location='{location}', ttlparticipants='{ttlparticipants}'";
			} else {
				$sql = "UPDATE phs.tbl_status SET date='{date}', type='{type}', title='{title}', description='{description}', notes='{notes}', ttlhours='{ttlhours}', location='{location'}, ttlparticipants='{ttlparticipants}' WHERE activityId={activityId}";
			}
			if($sql) {
				foreach($_POST as $key=>$value) {
					$sql = str_replace("{" . $key . "}", $value, $sql);
				}
				printsql($sql);
			}
		}
	}

	//

	//
	unset($data);
	$data = get_records2("phs.tbl_activity", "activityId", $id);

	$tpl = preg_replace("/<!-- list.*\/list -->/s", "", $tpl);
	$tpl = preg_replace("/<!-- list recent.*\/list recent -->/s", "", $tpl);

	if($id=="new") {
		$data[0]["activityId"] = "new";
	}

	foreach($data[0] as $key=>$value) {
		$tpl = str_replace("{" . $key . "}", $value, $tpl);
	}

} else {
	//list incidences by most recent

	//load the incidences
	$data = get_records2("phs.tbl_activity");

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