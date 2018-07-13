<?php

//save the data
if($_POST["teacherId"] && is_array($_POST["cls"]) && $_POST["teacherId"] == $_GET["id"]) {
	foreach($_POST["cls"] as $key=>$value) {
		#if($value) {
			unset($tmp);
			//check if record exists
			$sql = "SELECT * FROM phs.tbl_teacherassignments" . $thesy . " WHERE teacherId=" . $_POST["teacherId"] . " AND sem=" . substr($key, 0, 1) . " AND per=" . substr($key, 1, 1);
			$tmp = rsone($sql);
			//if it exists then update
			if(is_array($tmp)) {
				$sec = $_POST["sec"][$key];
				if(!$value) $sec="";
				$sql = "UPDATE phs.tbl_teacherassignments" . $thesy . " SET courseId='" . $value . "', section='" . $sec . "' WHERE teacherId=" . $_POST["teacherId"] . " AND sem=" . substr($key, 0, 1) . " AND per=" . substr($key, 1, 1);
				#printsql($sql);
				$tmp = $db->query($sql);
			//else insert
			} else {
				if($value) {
					$sql = "INSERT INTO phs.tbl_teacherassignments" . $thesy . " (teacherId, courseId, sem, per, section) VALUES('" . $_POST["teacherId"] . "', '" . $value . "', '" . substr($key, 0, 1) . "', '" . substr($key, 1, 1) . "', '" . $_POST["sec"][$key] . "')";
					#printsql($sql);
					$tmp = $db->query($sql);
				}
			}
		#}
	}
}

//load the list
$thedbtbl = "phs.tbl_teacherassignments" . $thesy;
$sql = "SELECT a.taId, a.teacherId, CONCAT(c.firstName, ' ', c.lastName) AS teacherName, a.department, a.section, d.courseId, d.name AS courseName, d.nameAbbrv As shortCourseName, a.sem, a.per, SUM(IF(b.taId, 1, 0)) AS 'N' FROM $thedbtbl a LEFT JOIN phs.tbl_regclasses2013 b ON a.taId=b.taId, phs.tbl_teacher c, phs.tbl_course d WHERE a.teacherId=c.teacherId AND a.courseId=d.courseId GROUP BY a.taId ORDER BY teacherName";
if($_POST["dept"]) $sql = str_replace(" ORDER BY ", " AND a.departmentId='" . $_POST["dept"] . "' ORDER BY ", $sql);
$rs = rsmany($sql);

unset($tmp);

$tmp_arr = array("id"=>"", "teacherName"=>"", "department"=>"", "section"=>"", "taId"=>"", "11"=>"", "12"=>"", "13"=>"", "14"=>"", "21"=>"", "22"=>"", "23"=>"", "24"=>"");

foreach($rs as $value) {
	if(!isset($tmp2_arr[$value["teacherId"]])) {
		$tmp2_arr[$value["teacherId"]] = $tmp_arr;
		$tmp2_arr[$value["teacherId"]]["id"] = $value["teacherId"];
		$tmp2_arr[$value["teacherId"]]["teacherName"] = $value["teacherName"];
		$tmp2_arr[$value["teacherId"]]["department"] = $value["department"];
		$tmp2_arr[$value["teacherId"]]["section"] = $value["section"];
		$tmp2_arr[$value["teacherId"]]["taId"] = $value["taId"];
		$tmp2_arr[$value["teacherId"]]["N"] = $value["N"];
	}
	$key = $value["sem"] . $value["per"];
	$color = "blue"; if($value["N"] > 20 ) $color = "red";
	$tmp2_arr[$value["teacherId"]][$key] = "<div style='float: right; font-size: xx-small; color: $color;'>" . $value["N"] . "</div><span style='font-size: xx-small; color: grey;'>" . $value["taId"] . "</span><br /><div style='clear: both;'></div><span style='font-size: xx-small; color: grey;'>" . $value["section"] . "</span><br /><strong>" . $value["shortCourseName"] . "</strong>";
}

if($_GET["id"] == "new" || is_array($tmp2_arr[$_GET["id"]])) {

	//do the action

	unset($cls_selopts, $sec_selopts, $tmp1, $tmp2, $assignments);
	$taid_arr = array("taid11"=>"", "taid12"=>"", "taid13"=>"", "taid14"=>"", "taid21"=>"", "taid22"=>"", "taid23"=>"", "taid24"=>"");
	$N_arr = array("N11"=>"", "N12"=>"", "N13"=>"", "N14"=>"", "N21"=>"", "N22"=>"", "N23"=>"", "N24"=>"");
	foreach($rs as $value) {
		$tmp1[$value["courseName"]] = $value["courseId"];
		$tmp2[$value["section"]] = "";
		if($value["teacherId"] == $_GET["id"]) {
			$courses[$value["sem"] . $value["per"]] = $value["courseId"];
			$sections[$value["sem"] . $value["per"]] = $value["section"];
			$taid_arr[$value["sem"] . $value["per"]] = $value["taId"];
			$N_arr[$value["sem"] . $value["per"]] = $value["N"];
		}
	}
	ksort($tmp1); ksort($tmp2);
	#dumpvar($tmp1);
	$crs_selopts = "<option>" . implode("</option><option>", array_keys($tmp1)) . "</option>";
	foreach($tmp1 as $key=>$value) { $crs_selopts = str_replace(">" . $key . "<", " value=" . $value . ">" . $key . "<", $crs_selopts); }
	$sec_selopts = "<option>" . implode("</option><option>", array_keys($tmp2)) . "</option>";

	#printsql($crs_selopts);

	$tpl = file_get_contents($templates_dir . "phs-teachers.inc-proposedschedule-form.tpl");

	$tpl = str_replace("{teacherId}", $_GET["id"], $tpl);
	$tpl = str_replace("{teacherName}", $tmp2_arr[$_GET["id"]]["teacherName"], $tpl);

	for($i=1; $i<3; $i++) {
		for($j=1; $j<5; $j++) {
			$tpl = str_replace("{cls" . $i . $j . "_selopts}", str_replace("value=" . $courses[$i . $j] . ">", "value=" . $courses[$i . $j] . " selected>", $crs_selopts), $tpl);
			$tpl = str_replace("{sec" . $i . $j . "_selopts}", str_replace(">" . $sections[$i . $j] . "<", " selected>" . $sections[$i . $j] . "<", $sec_selopts), $tpl);
			$tpl = str_replace("{taid" . $i . $j . "}", $taid_arr[$i . $j], $tpl);
			$tpl = str_replace("{N" . $i . $j . "}", $N_arr[$i . $j], $tpl);
		}
	}

} else {

	$tpl = file_get_contents($templates_dir . "phs-teachers.inc-proposedschedule.tpl");

	//department select options
	$dept_selopts="";
	$sql = "SELECT * FROM phs.tbl_department WHERE abbrev != '' ORDER BY abbrev";
	$rs = rsmany($sql);
	foreach($rs as $value) {
		$dept_selopts .= "<option value=" . $value["departmentId"] . ">" . $value["abbrev"] . "</option>\n";
	}
	$dept_selopts = str_replace("value=" . $_POST["dept"] . ">", "value=" . $_POST["dept"] . " selected>", $dept_selopts);

	$tpl = str_replace("{dept_selopts}", $dept_selopts, $tpl);

	preg_match("/<tr id=tblrow.*>/", $tpl, $matches);

	unset($tmp, $tmp2, $tblrows);
	$tmp = str_replace(" id=tblrow", "", $matches[0]);
	foreach($tmp2_arr as $key=>$value) {
		$tmp2 = $tmp;
		$tmp2 = str_replace("{teacherId}", $key, $tmp2);
		$tmp2 = str_replace("{teacherName}", $value["teacherName"], $tmp2);
		$tmp2 = str_replace("{section}", $value["section"], $tmp2);
		$tmp2 = str_replace("{11}", $value["11"], $tmp2);
		$tmp2 = str_replace("{12}", $value["12"], $tmp2);
		$tmp2 = str_replace("{13}", $value["13"], $tmp2);
		$tmp2 = str_replace("{14}", $value["14"], $tmp2);
		$tmp2 = str_replace("{21}", $value["21"], $tmp2);
		$tmp2 = str_replace("{22}", $value["22"], $tmp2);
		$tmp2 = str_replace("{23}", $value["23"], $tmp2);
		$tmp2 = str_replace("{24}", $value["24"], $tmp2);
		$tblrows .= "\t" . $tmp2 . "\n";
	}

	$tpl = str_replace($matches[0], $tblrows, $tpl);


}

unset($tpldata);
require_once("tpldata.php");
$tpldata["tab"] = $tab;
$tpl = $printstr . $tpl;
unset($printstr);

?>