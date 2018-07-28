<?php
error_reporting(E_ALL ^ E_NOTICE); //get rid of undefined variable notice

require_once("../functions/functions-db.inc");

$phssy = trim($_GET["phssy"]); 
$sem = trim($_GET["sem"]); $qtr = trim($_GET["qtr"]);

$proceed = true;

if($sem != 1 && $sem != 2) $proceed = false;
if($qtr != 1 && $qtr != 2) $proceed = false;

$sql = "SELECT DISTINCT(sy) AS sy FROM phs.tbl_grades";
$tmp = get_sqlResults($sql);
foreach($tmp as $row) { $phssyArr[] = $row["sy"]; }
if(!in_array($phssy, $phssyArr)) $proceed = false;

if($proceed) {

	//update tbl_schedule with studentId
	$sql = "UPDATE phs.tbl_schedule a, phs.tbl_enrollment b SET a.stuid0=b.studentId WHERE a.enrolId=b.enrolId";
	$tmp = db_query($sql);
	//populate the classStuCode field
	$sql = "UPDATE phs.tbl_schedule SET classStuCode=CONCAT(classId, '_', stuid0)";
	$tmp = db_query($sql);
	
	//update tbl_grades with sy and sem
	$sql = "UPDATE phs.tbl_grades a, phs.tbl_class b SET a.sy=b.year, a.sem=b.semester WHERE a.classId=b.classId";
	$tmp = db_query($sql);
	//populate the classStuCode field
	$sql = "UPDATE phs.tbl_grades SET classStuCode=CONCAT(classId, '_', studentId)";
	$tmp = db_query($sql);
	
	//update tbl_schedule with matching records from tbl_grades
	$sql = "UPDATE phs.tbl_grades a, phs.tbl_schedule b 
			SET b.q${qtr}grade=a.q${qtr}es, b.q${qtr}abs=a.q${qtr}ea
			WHERE a.classStuCode=b.classStuCode AND a.sem=${sem}";
	$tmp = db_query($sql);

	//insert records into tbl_schedule from tbl_grades
	$sql = "UPDATE phs.tbl_grades a, phs.tbl_schedule b 
			SET b.q${qtr}grade=a.q${qtr}es, b.q${qtr}abs=a.q${qtr}ea
			WHERE a.classStuCode=b.classStuCode AND a.sem=${sem}";
	$tmp = db_query($sql);

	$sql = "SELECT 
				a.studentId AS stuid0, a.q${qtr}es AS q${qtr}grade, a.q${qtr}ea AS q${qtr}abs, 
				a.classId, CONCAT(a.classId, '_', a.studentId) AS classStuCode
			FROM phs.tbl_grades a LEFT JOIN 
				phs.tbl_schedule b ON a.classStuCode = b.classStuCode 
			WHERE a.sy=${phssy} AND a.sem=${sem} AND b.classStuCode IS NULL";
	#echo "<pre>"; print_r($sql); echo "</pre>\n";
	$tmp = db_query($sql);
	echo json_encode($tmp);
} else {
	echo json_encode("Could not proceed");
}
?>
