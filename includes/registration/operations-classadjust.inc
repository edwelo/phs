<?php

$tpldata["sourceTable"] = "";
$tpldata["destinationTable"] = "";
$tpldata["moveButton"] = "";

$thesy = $csy;
$phssy = $thesy - 1;

$sql = "SELECT
			a.classId, a.period, CONCAT(b.firstName, ' ', b.lastName) AS teacherName, c.name AS courseName
		FROM
			phs_reg.tbl_regtchrassigns" . $thesy . " a,
			phs.tbl_teacher b,
			phs.tbl_course c
		WHERE
			a.teacherId=b.teacherId AND
			a.courseId=c.courseId AND
			a.courseId != '' AND
			a.courseId IS NOT NULL";
$rs = rsmany($sql);
foreach($rs as $value) {
	$classes[$value["classId"]] = $value["period"] . "<br />" . $value["teacherName"] . "<br />" . $value["courseName"];
}

if(is_numeric($_POST["sourceClassId"]) || is_numeric($_POST["destinationClassId"])) {
	$_GET["clsids"] = $_POST["sourceClassId"] . "," . $_POST["destinationClassId"];
}

if($_POST["moveclass"]) {
	$_GET["clsids"] = $_POST["moveclass"];
	list($cls1id, $cls2id) = explode(",", $_POST["moveclass"]);
	$sql = "UPDATE phs_reg.tbl_regclasses" . $thesy . " SET classId=$cls2id, modifyBy=$persid WHERE classId=$cls1id";
	#printsql($sql);
	$db->query($sql) or die("moveclass error: " . $db->error);
}

list($cls1id, $cls2id) = explode(",", $_GET["clsids"]);

$tpl = "<span class=lbl1>School Year " . $_SESSION["sy"] . "</span><br />\n<br />\n";
$tpl .= "<form action='' method=post>\n";
$tpl .= "<span class=lbl1>source class id: </span><input type=text name=sourceClassId value='$cls1id' size=3 />\n";
$tpl .= "<span class=lbl1>, move to </span>\n";
$tpl .= "<span class=lbl1>destination class id: </span><input type=text name=destinationClassId value='$cls2id' size=3 />\n";
$tpl .= "&nbsp;&nbsp;&nbsp;&nbsp;\n";
$tpl .= "<input type=submit value='go' />\n";
$tpl .= "</form>\n";

$tpl .= "<hr />\n";

$tpl .= "<table>\n<tr valign=top>\n<td>{sourceTable}</td>\n<td align=center><br /><br /><br /><br /><br /><br />{moveButton}</td>\n<td>{destinationTable}</td>\n</tr>\n</table>\n";

$sql0 = "SELECT
			CONCAT(c.lastName, ', ', c.firstName) AS studentName, b.gradeLevel, b.section
		FROM
			phs_reg.tbl_regclasses" . $thesy . " a,
			phs_reg.tbl_regenroll" . $thesy . " b,
			phs.tbl_student c
		WHERE
			a.studentId=b.studentId AND
			b.studentId=c.studentId AND
			a.classId = {clsid}
		";

$studentsToMove = 0;

if($classes[$cls1id]) {

	unset($rs);
	$sql = str_replace("{clsid}", $cls1id, $sql0);
	$rs = rsmany($sql);

	$tpldata["sourceTable"] = "<span class=lbl1>Source Class<br />" . $classes[$cls1id] . "</span>\n";

	if(is_array($rs)) {
		$studentsToMove = count($rs);
		unset($data);
		$data["rs"] = $rs;
		$data["rownums"] = "y";
		$tpldata["sourceTable"] .= basichtmltable($data);
		$tpldata["moveButton"] = ">>><br /><br />>>>";
	} else {
		$tpldata["sourceTable"] .= "<p class=alert1>No Students for This Class</p>\n";
	}

}

if($classes[$cls2id]) {

	unset($rs);
	$sql = str_replace("{clsid}", $cls2id, $sql0);
	$rs = rsmany($sql);

	$tpldata["destinationTable"] = "<span class=lbl1>Destination Class<br />" . $classes[$cls2id] . "</span>\n";

	if(is_array($rs)) {
		unset($data);
		$data["rs"] = $rs;
		$data["rownums"] = "y";
		$tpldata["destinationTable"] .= basichtmltable($data);
	} else {
		$tpldata["destinationTable"] .= "<p class=alert1>No Students for This Class</p>\n";
	}

	if(substr($classes[$cls1id], 0, 2) == substr($classes[$cls2id], 0, 2)) {
		$tpldata["moveButton"] = ">>>><br />\n<br />\n<form action='' method=post>\n
											<input type=hidden name=moveclass value='" . $cls1id . "," . $cls2id . "' />\n
											<input type=submit value='move this class' />\n
											</form>\n>>>>\n";
	} else {
		$tpldata["destinationTable"] .= "<p class=alert1>Cannot move classes between different periods!</p>\n";
	}

}

if(!$studentsToMove) $tpldata["moveButton"] = ">>><br /><br />>>>";

#$tpl = $tabs_html . $sy_html . $tpl;
$tpl = $tabs_html . $tpl;

?>