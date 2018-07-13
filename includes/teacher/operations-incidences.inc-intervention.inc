<?php

$tpl = file_get_contents($template_file_fullpath . "-intervention.tpl");

$tpl = str_replace("{new_iid_link}", preg_replace("/&iid=.*/", "&iid=new", $hrefpre), $tpl);

//Incident Info
$data = get_records2("phs.tbl_incident", "incidentId", $id);
#dumpvar($data);
if($data[0]["incidentDate"] == "0000-00-00") $data[0]["incidentDate"] = "";
if($data[0]["incidentTime"] == "00:00:00") $data[0]["incidentTime"] = "";
if($data[0]["referredDate"] == "0000-00-00") $data[0]["referredDate"] = "";
$tpl = str_replace("{incidentId}", $data[0]["incidentId"], $tpl);
$tpl = str_replace("{stuid}", $data[0]["studentId"], $tpl);
$tpl = str_replace("{studentName}", $students[$data[0]["studentId"]]["studentName"], $tpl);
$tpl = str_replace("{incidentDate}", $data[0]["incidentDate"], $tpl);
$tpl = str_replace("{location}", $data[0]["location"], $tpl);
$tpl = str_replace("{incidentCategory}", $data[0]["category"], $tpl);
$tpl = str_replace("{incidentDescription}", $data[0]["description"], $tpl);
$tpl = str_replace("{referredTo}", $data[0]["referredTo"], $tpl);
$tpl = str_replace("{referredDate}", $data[0]["referredDate"], $tpl);

//Intervention Info
$incdata = get_records2("phs.tbl_incidentAction", "incidentId", $id);
unset($fields);
if(is_array($incdata[0])) {
	foreach($incdata[0] as $key=>$value) { $fields[$key] = ""; }
} else {
	$fields = $incdata;
}

preg_match("/\t+<tr id=row.*?\/tr>/s", $tpl, $matches);
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

if(!$iid) {
	$tpl = preg_replace("/<!-- intervention form.*?\/intervention form -->/s", "", $tpl);
} else {

}

?>