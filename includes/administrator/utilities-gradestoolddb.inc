<?php

function get_termDates() {
	$sql = "SELECT * FROM phs.tbl_quarters ORDER BY sy";
	
	$db = new mysqli("phsmysql.moe", "mysql", "mysql");
	$rs = $db->query($sql) or die("get_termDates: " . $db->error);
	while($tmp = $rs->fetch_assoc()) {
		$ret[$tmp["sy"]] = $tmp;
	}
	return $ret;
}

function get_endTermParams() {

	$termDates = get_termDates();
	$schoolYears = array_keys($termDates);
	
	#var_dump($_POST);
	
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

function addSYtoGradesTable() {
	$sql = "UPDATE phs.tbl_class a, phs.tbl_grades b 
			SET b.sy = a.year, b.sem = a.semester WHERE a.classId=b.classId";
	$tmp = db_query($sql);
}

function check_for_existing_data($phssy, $sem, $qtr) {
	
	$sql = "SELECT
				COUNT(*) AS N, SUM(IF(c.q2grade > 0, 1, 0)) AS Ny, SUM(IF(c.q2grade = 0 OR c.q2grade IS NULL, 1, 0)) AS Nn 
			FROM
				phs.tbl_student a, phs.tbl_enrollment b, phs.tbl_schedule c,
				phs.tbl_class d, phs.tbl_teacher e, phs.tbl_course f
			WHERE
				a.studentId=b.studentId AND b.enrolId=c.enrolId AND
				c.classId=d.classId AND d.teacherId=e.teacherId AND
				d.courseId=f.courseId AND 
				d.year=${phssy} AND d.semester=${sem} AND
				c.q${qtr}grade > 0 AND c.q${qtr}grade IS NOT NULL";
	$ret[] = get_sqlResult($sql);
	$sql = "SELECT
				COUNT(*) AS N, SUM(IF(a.q1es > 0, 1, 0)) AS Ny, SUM(IF(a.q1es = 0 OR a.q1es IS NULL, 1, 0)) AS Nn
			FROM phs.tbl_grades a, phs.tbl_class b 
			WHERE a.classId=b.classId AND b.year=${phssy} AND b.semester=${sem}";
	$ret[] = get_sqlResult($sql);
	
	$sqla = "SELECT
				a.studentId, d.classId 
			FROM
				phs.tbl_student a, phs.tbl_enrollment b, phs.tbl_schedule c,
				phs.tbl_class d, phs.tbl_teacher e, phs.tbl_course f
			WHERE
				a.studentId=b.studentId AND b.enrolId=c.enrolId AND
				c.classId=d.classId AND d.teacherId=e.teacherId AND
				d.courseId=f.courseId AND 
				d.year=${phssy} AND d.semester=${sem} AND
				c.q${qtr}grade > 0 AND c.q${qtr}grade IS NOT NULL
			GROUP BY d.classId, a.studentId";
	$sqlb = "SELECT
				a.studentId, b.classId
			FROM phs.tbl_grades a, phs.tbl_class b 
			WHERE a.classId=b.classId AND b.year=${phssy} AND b.semester=${sem} 
			GROUP BY a.classId, a.studentId";
	$sql = "SELECT COUNT(*) AS N FROM ($sqla) t1, ($sqlb) t2 WHERE t1.classId=t2.classId AND t1.studentId=t2.studentId";
	$tmp2 = get_sqlResult($sql);
	$ret[] = $tmp2["N"];
	
	addSYtoGradesTable(); //updates tbl_grades sets sy to the year from tbl_class
	$sql = "SELECT COUNT(*) AS N FROM (SELECT studentId FROM phs.tbl_grades WHERE sy=${phssy} GROUP BY studentId) a";
	$tmp = get_sqlResult($sql);
	$sql = "SELECT COUNT(*) AS Ne, SUM(b.rCount) AS Nm 
			FROM phs.tbl_enrollment a LEFT JOIN 
				(SELECT studentId, 1 AS rCount FROM phs.tbl_grades WHERE sy=${phssy} AND sem=${sem}
					GROUP BY studentId) b
			 	ON a.studentId=b.studentId 
			WHERE a.year=${phssy}";
	#printsql($sql);
	$tmp2 = get_sqlResult($sql); $tmp2["Ng"] = $tmp["N"];
	$ret[] = $tmp2;
	return $ret;
}

$tpldata["jsScript"] = "oldToNewDB.js";

list($tpldata["sy"], $tpldata["semester"], $tpldata["quarter"], $tpldata["qeDate"]) = explode(":", get_endTermParams());
$tpldata["phssy"] = $tpldata["sy"] - 1;

$sy = $tpldata["sy"];
$phssy = $tpldata["phssy"];
$sem = $tpldata["semester"];
$qtr = $tpldata["quarter"];

$data_counts = check_for_existing_data($phssy, $sem, $qtr);

$tpldata["N0"] = $data_counts[0]["N"];
$tpldata["Ny0"] = $data_counts[0]["Ny"];
$tpldata["Nn0"] = $data_counts[0]["Nn"];
$tpldata["N1"] = $data_counts[1]["N"];
$tpldata["Ny1"] = $data_counts[1]["Ny"];
$tpldata["Nn1"] = $data_counts[1]["Nn"];
$tpldata["Nm0"] = $data_counts[2];
$tpldata["Ne"] = $data_counts[3]["Ne"];
$tpldata["Ng"] = $data_counts[3]["Ng"];
$tpldata["Nm3"] = $data_counts[3]["Nm"];

#dumpvar($data_counts);

$tpl = file_get_contents($template_file_fullpath);

$searchStr = "name=semester value=${sem}";
$replaceStr = $searchStr . " checked";
$tpl = str_replace($searchStr, $replaceStr, $tpl);

$searchStr = "name=quarter value=${qtr}";
$replaceStr = $searchStr . " checked";
$tpl = str_replace($searchStr, $replaceStr, $tpl);
?>
