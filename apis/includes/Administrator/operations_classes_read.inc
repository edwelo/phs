<?php
//scheduling
//eo180728

function get_data($dbLabel, $sql) {

	if($_GET["a"]) {
		echo "$dbLabel: <pre>" . str_replace("<", "&lt;", $sql) . "</pre>";
	}

	if($rs = $GLOBALS["db"]->query($sql)) {
		if($_GET["a"]) {
			echo "<p>$dbLabel success with " . $rs->num_rows . " records</p>";
		}

		while($tmp = $rs->fetch_assoc()) {
			$ret[] = $tmp;
		}

		return $ret;

	} else {
		if($_GET["a"]) {
			echo "<p>$dbLabel failed: <br />" . $db->error . "</p>";
		} else {
			echo "$dbLabel";
		}
	}

}

//Get Teachers

$phssy = 2017;

$sql = "SELECT 
				c.abbrev AS dept, a.teacherId, 
				CONCAT(a.lastName, ', ', LEFT(a.firstName, 1)) AS teacherName 
			FROM 
				phs.tbl_teacher a, phs.tbl_class b, phs.tbl_department c 
			WHERE 
				a.teacherId=b.teacherId AND a.departmentId=c.departmentId AND 
				b.year=${phssy} AND persid_moe IS NOT NULL AND 
				persid_moe > 1 
			GROUP BY a.teacherId ORDER BY dept, teacherName";

$dbLabel = "GET_THIS_YEAR_TEACHERS";
$teachers = get_data($dbLabel, $sql);

unset($tmp2);
for($s=1; $s<3; $s++) {
	for($p=1; $p<5; $p++) {
		$key = "${s}${p}";
		$tmp2[$key] = array("courseId"=>"", "courseShortName"=>"", "numStudents"=>0);
	}
}

foreach($teachers as $row) {
	foreach($tmp2 as $semPer=>$value) { $row[$semPer] = $value; }
	$data["sched"][$row["teacherId"]] = $row;
}

//Get records from temp tables

$sql = "SELECT 
			a.teacherId, a.courseId, a.semPer,
			c.name AS courseName, c.nameAbbrv AS courseAbbrv, 
			c.grade, c.departmentId, 			
			SUM(IF(b.studentId, 1, 0)) AS numStudents 
		FROM
			phs.tmp_scheduling a LEFT JOIN 
			phs.tmp_scheduling_students b ON a.schedId=b.schedId,
			phs.tbl_course c
		WHERE a.courseId=c.courseId 
		GROUP BY a.schedId";

$dbLabel = "GET_TEMP_TABLES";
//$temp_tables = get_data($dbLabel);

/*foreach($arr as $key=>$row) {
	if(isset($arr2[$row["teacherId"]])) {
		$arr[$key][$arr2[$row["teacherId"]]["semPer"]] = $arr2[$row["teacherId"]]["courseAbbrv"] . " (" . $arr2[$row["teacherId"]]["numStudents"] . ")";
	}
}*/

//get courses

// $sql = "SELECT 
// 			a.courseId, a.name AS courseName, a.departmentId, a.grade
// 		FROM phs.tbl_course a, phs.tbl_class b
// 		WHERE a.courseId=b.courseId AND year=${phssy}
// 		GROUP BY a.courseId ORDER BY name";
// $rs = $db->query($sql) or die("courses: " . $db->error);
// 
// $dbLabel = "GET_COURSES";
// $courses = get_data($dbLabel, $sql);

$sql = "
SELECT
	a.teacherId, b.courseId, b.name AS courseName, b.nameAbbrv AS courseNameShort, b.departmentId, a.semester, a.period
FROM
	phs.tbl_class a,
	phs.tbl_course b
WHERE
	a.courseId=b.courseId AND
	a.year=${phssy}
";

$dbLabel = "GET_COURSES";
$courses = get_data($dbLabel, $sql);

foreach($courses as $row) {
	$teacherId = $row["teacherId"];
	$semPer = $row["semester"] . $row["period"];
	if(isset($data["sched"][$teacherId][$semPer])) {
		$data["sched"][$teacherId][$semPer] = $row["courseId"];
		$data["sched"][$teacherId][$semPer] = $row["courseNameShort"];
	}
}

/**
 * SQLs used to clear and populate the temp tables
 
DELETE FROM tmp_scheduling;
ALTER TABLE tmp_scheduling AUTO_INCREMENT=0;
DELETE FROM tmp_scheduling_students;
ALTER TABLE tmp_scheduling_students AUTO_INCREMENT=0;

INSERT INTO tmp_scheduling (year, teacherId, courseId, courseNameShort, semPer, classId)
SELECT a.year, a.teacherId, a.courseId, 
	b.nameAbbrv AS courseNameShort, 
	CONCAT(a.semester, a.period) AS semPer, a.classId 
FROM tbl_class a, tbl_course b
WHERE a.courseId=b.courseId AND year=2017;

INSERT INTO tmp_scheduling_students (year, studentId, classId, scheduleId)
SELECT a.year, c.studentId, a.classId, b.scheduleId
FROM
	tbl_class a, tbl_schedule b, tbl_enrollment c
WHERE
	a.classId=b.classId AND b.enrolId=c.enrolId AND a.year=2017;

 */

?>
