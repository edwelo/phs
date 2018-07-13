<?php

function get_termDates_old() {
	$tmp = file("data/quarters.txt");
	foreach($tmp as $str) {
		$str = trim($str);
		if(substr($str, 0, 2) == "sy") {
			list(, $tmp2) = explode(":", $str);
			$theKeys = explode(",", $tmp2);
		}
		if(is_numeric(substr($str, 0, 4))) {
			list($sy, $tmp2) = explode(":", $str);
			$theValues = explode(",", $tmp2);
			$data[$sy] = array_combine($theKeys, $theValues);
		}
	}
	return $data;
}

function get_termDates() {
	$sql = "SELECT * FROM phs.tbl_quarters ORDER BY sy";
	
	$db = new mysqli("phsmysql.moe", "mysql", "mysql");
	$rs = $db->query($sql) or die("get_termDates: " . $db->error);
	while($tmp = $rs->fetch_assoc()) {
		$ret[$tmp["sy"]] = $tmp;
	}
	return $ret;
}

function get_midTermParams() {

	$termDates = get_termDates();
	$schoolYears = array_keys($termDates);
	
	if($_POST["sy"] && $_POST["semester"] && $_POST["quarter"]) {
		if(in_array($_POST["sy"], $schoolYears)) $sy = $_POST["sy"];
		if($_POST["semester"] == 1 || $_POST["semester"] == 2) $sem = $_POST["semester"];
		if($_POST["quarter"] == 1 || $_POST["quarter"] == 2) $qtr = $_POST["quarter"];
	}

	if(!$sy || !$sem || !$qtr) {
		$sy = $_SESSION["phssy"] + 1; //the phs db year is one less than the actual sy
		$sem = 1;
		if(date("m-d") <= "07-31") $sem = 2;
		$qtr = 1;
		if(date("Y-m-d") >= $termDates[$sy]["s" . $sem . "q2e"]) $qtr = 2;
	}
	
	$qeDate = $termDates[$sy]["s" . $sem . "q" . $qtr . "e"];
	return $sy . ":" . $sem . ":" .  $qtr . ":" . $qeDate;
	
}

list($tpldata["sy"], $tpldata["semester"], $tpldata["quarter"], $tpldata["qeDate"]) = explode(":", get_midTermParams());
$tpldata["phssy"] = $tpldata["sy"] - 1;

$sy = $tpldata["sy"];
$phssy = $tpldata["phssy"];
$sem = $tpldata["semester"];
$qtr = $tpldata["quarter"];

$sql = "
SELECT
	a.studentId, CONCAT(a.firstName, ' ', a.lastName) AS studentName, b.grade AS gradeLevel, e.name AS courseName,
	d.semester, d.period, c.q${qtr}ms, c.q${qtr}ma, CONCAT(f.firstName, ' ', f.lastName) AS teacherName
FROM phs.tbl_student a, phs.tbl_enrollment b, phs.tbl_grades c, phs.tbl_class d, phs.tbl_course e, phs.tbl_teacher f
WHERE a.studentId=b.studentId AND b.studentId=c.studentId AND c.classId=d.classId AND 
	d.courseId=e.courseId AND d.teacherId=f.teacherId AND 
	b.year=${phssy} AND d.year=${phssy} AND d.semester=${sem}
ORDER BY semester, gradeLevel, studentName, period
";
#printsql($sql);

$rs = db_query($sql);

if(is_array($rs)) {
	//records exist
	
	$data["rs"] = $rs;
	$data["tblstyle"] = "bodypanel";
	$html = basichtmltable($data);
	
} else {
	//no records
	$html = "<p style='color: #c74;'>No scores found for this mid term</p>\n";
}

$db->close;

$tpldata["content"] = $html;

$tpl = file_get_contents($template_file_fullpath);

$searchStr = "name=semester value=${sem}";
$replaceStr = $searchStr . " checked";
$tpl = str_replace($searchStr, $replaceStr, $tpl);

$searchStr = "name=quarter value=${qtr}";
$replaceStr = $searchStr . " checked";
$tpl = str_replace($searchStr, $replaceStr, $tpl);

#dumpvar($_SESSION);

?>
