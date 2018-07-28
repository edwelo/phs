<?php

## eo 131026

error_reporting(E_ALL ^ E_NOTICE); //get rid of undefined variable notice

$sql1 = "SELECT a.* FROM phs.tbl_grades a, phs.tbl_class b WHERE a.classId=b.classId AND b.teacherId = " . $_GET["teacherId"] . " AND b.year=" . $_GET["phssy"];

#print_r($sql1);

$sql2 = "SELECT
			d.teacherId,
			CONCAT(f.firstName, ' ', f.lastName) AS teacherName,
			c.classId,
			e.name AS courseName,
			d.semester,
			d.period,
			a.studentId,
			CONCAT(a.lastName, ', ', a.firstName, ' ', a.middleName) AS studentName
		FROM
			phs.tbl_student a,
			phs.tbl_enrollment b,
			phs.tbl_schedule c,
			phs.tbl_class d,
			phs.tbl_course e,
			phs.tbl_teacher f
		WHERE
			a.studentId=b.studentId AND
			b.enrolId=c.enrolId AND
			c.classId=d.classId AND
			d.courseId=e.courseId AND
			d.teacherId=f.teacherId AND
			d.year=" . $_GET["phssy"] . " AND
			d.teacherId=" . $_GET["teacherId"] . "
		ORDER BY teacherName, classId, studentName";

#printsql($sql1);

$db = new mysqli("localhost","mysql","mysql","phs");

unset($value);
$rs = $db->query($sql1) or die("sql1 error: " . $db->error);
#echo $rs->num_rows . "<br />\n";
while($value = $rs->fetch_assoc()) {
	$id = $value["classId"] . "." . $value["studentId"];
	unset($value["classId"], $value["studentId"]);
	array_pop($value); array_pop($value); array_pop($value); array_pop($value);
	$grades_arr[$id] = $value;
}

#var_dump($grades_arr);

$grades_arr_blank = current($grades_arr);
foreach($grades_arr_blank as $key=>$value) {
	$grades_arr_blank[$key] = "";
}

unset($value);
$rs = $db->query($sql2);
#dumpvar($tmp_arr);
while($value = $rs->fetch_assoc()) {
	$id = $value["classId"] . "." . $value["studentId"];
	if(array_key_exists($id, $grades_arr)) {
		$classesInfo_arr[] = array_merge($value, $grades_arr[$id]);
	} else {
		$classesInfo_arr[] = array_merge($value, $grades_arr_blank);
	}
}

$db->close;

$teacherName = $classesInfo_arr[0]["teacherName"];
$caption = "$teacherName Student Grades SY" . ($_GET["phssy"] + 1) . "\r";
if(!count($classesInfo_arr)) {
	$caption .= "... There was no data\r";
}

//set up each line ready for printing to header or to screen
unset($lines);
$no = 1;
#echo $filename . "<br />";
#echo $sql . "<br />"; exit;

//selects whether to print or download

if($_GET["action"]=="download") {

	$filename = $teacherName . "_" . ($_GET["phssy"] + 1) . "_grades.xls";

	header('Content-type: application/msexcel');
	#header("Content-type:application/octet-stream");
	#header('Content-type: text/plain');
	#header('Expires: ' . gmdate('D, d M Y H:i:s') . ' GMT');
	#header('Content-Length: '.strlen($code));
	header('Content-Description: $filename Download Data');
	#header('Pragma: no-cache');
	header('Content-Disposition: attachment; filename="' . $filename . '"');

	$lines0 = "no.\t" . implode("\t", array_keys($classesInfo_arr[0]));
	foreach($classesInfo_arr as $value) {
		$lines[] = $no++ . ".\t" . implode("\t", $value);
	}

	echo $caption . "\r";
	echo $lines0 . "\r";
	foreach($lines as $value) { echo $value . "\r"; }

} else {

	$lines0 = "<tr><th>no.</th><th>" . implode("</th><th>", array_keys($classesInfo_arr[0])) . "</th></tr>\n";
	$lines = "";
	foreach($classesInfo_arr as $value) {
		$lines .= "<tr><td>" . $no++ . "</td><td>" . implode("</td><td>", $value) . "</td></tr>\n";
	}

	echo $caption . "<br />\n";
	echo "<table border=1>\n";
	echo $lines0;
	echo $lines;
	echo "</table>\n";

}
?>
