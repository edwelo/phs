<?php
error_reporting(E_ALL ^ E_NOTICE); //get rid of undefined variable notice

require_once("../functions/functions-db.inc");

$type = substr($_GET["type"], 0, 1); $phssy = $_GET["phssy"]; 
$sem = $_GET["sem"]; $qtr = $_GET["qtr"];

$sql = "
SELECT
	a.studentId, CONCAT(a.firstName, ' ', a.lastName) AS studentName, b.grade AS gradeLevel, e.name AS courseName,
	d.semester, d.period, c.q${qtr}${type}s, c.q${qtr}${type}a, CONCAT(f.firstName, ' ', f.lastName) AS teacherName
FROM phs.tbl_student a, phs.tbl_enrollment b, phs.tbl_grades c, phs.tbl_class d, phs.tbl_course e, phs.tbl_teacher f
WHERE a.studentId=b.studentId AND b.studentId=c.studentId AND c.classId=d.classId AND 
	d.courseId=e.courseId AND d.teacherId=f.teacherId AND 
	b.year=${phssy} AND d.year=${phssy} AND d.semester=${sem}
ORDER BY d.semester, gradeLevel, studentName, d.period
";

#echo "<pre>"; print_r($sql); echo "</pre>\n";

#$db = new mysqli("phsmysql","mysql","mysql","phs");
$rs = db_query($sql);

if(is_array($rs)) {

	$theKeys = array_keys($rs[0]);

	$filename = ($phssy + 1) . "_s${sem}q${qtr}_MidTermGradesDump.txt";
	if($type == "e") $filename = ($phssy + 1) . "_s${sem}q${qtr}_QuarterGradesDump.txt";
	
	#$print = true;
	
	if($print) {
		echo "<table class=x>\n";
		echo "<tr><th>" . implode("</th><th>", $theKeys) . "</th></tr>\n";
		foreach($rs as $row) {
			echo "<tr><td>" . implode("</td><td>", $row) . "</td></tr>\n";
		}
		echo "</table>\n";
	} else {
		#header('Content-type: application/msexcel');
		#header("Content-type: application/octet-stream");
		header('Content-type: text/plain');
		#header('Expires: ' . gmdate('D, d M Y H:i:s') . ' GMT');
		#header('Content-Length: '.strlen($code));
		header('Content-Description: $filename Download Data');
		#header('Pragma: no-cache');
		header('Content-Disposition: attachment; filename="' . $filename . '"');

		echo implode("\t", $theKeys) . "\n";
		foreach($rs as $row) {
			$theStr = implode("\t", $row) . "\n";
			echo $theStr;
		}	
	}

}

?>
