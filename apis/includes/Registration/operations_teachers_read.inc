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
			echo "<p>$dbLabel failed: <br />" . $GLOBALS["db"]->error . "</p>";
		} else {
			echo "$dbLabel";
		}
	}

}

unset($phssy);
if(is_numeric($_GET["year"])) {
	$phssy = $_GET["year"] - 1;
	if($phssy < 2003) unset($phssy);
}

if($phssy) {

	$phssyLess3 = $phssy - 3;
	
	//Get Teachers

	$sql = "
SELECT 
	c.departmentId, c.abbrev AS dept, a.teacherId, 
	CONCAT(a.lastName, ', ', LEFT(a.firstName, 1)) AS teacherName 
FROM 
	phs.tbl_teacher a, phs.tbl_class b, phs.tbl_department c 
WHERE 
	a.teacherId=b.teacherId AND a.departmentId=c.departmentId AND 
	b.year BETWEEN ${phssyLess3} AND ${phssy} AND persid_moe IS NOT NULL AND 
	persid_moe > 1 
GROUP BY a.teacherId ORDER BY dept, teacherName
";

	$dbLabel = "GET_TEACHERS";
	$teachers = get_data($dbLabel, $sql);

	foreach($teachers as $row) {
		$row["active"] = "";
		$data["teachers"][$row["teacherId"]] = $row;
	}

	//Get records from temp tables

	$sql = "
SELECT teacherId, courseId, courseNameShort, semPer 
FROM phs.tmp_scheduling 
WHERE year=${phssy} 
GROUP BY teacherId, courseId
";

	$dbLabel = "GET_TEMP_TABLES";
	$reg_teachers = get_data($dbLabel, $sql);
	
	unset($semPers);
	for($s=1; $s<3; $s++) {
		for($p=1; $p<5; $p++) {
			$semPers["${s}${p}"] = "";
		}
	}

	if(is_array($reg_teachers)) {
		foreach($reg_teachers as $key=>$row) {
			if(isset($data["teachers"][$row["teacherId"]])) {
				$data["teachers"][$row["teacherId"]]["active"] = 1;
				$data["teachers"][$row["teacherId"]] += $semPers;
				$data["teachers"][$row["teacherId"]][$row["semPer"]] = $row["courseId"] . " " . $row["courseNameShort"];
			}
		}
	}

	//convert to non-associative for easier javascript iteration
	$data["teachers"] = array_values($data["teachers"]);

	//Get courses

	$sql = "
SELECT 
	a.departmentId, a.name, a.abbrev, 
	b.courseId, b.name AS courseName, 
	b.nameAbbrv AS courseNameShort
FROM
	phs.tbl_department a,
	phs.tbl_course b
WHERE
	a.departmentId=b.departmentId
";

	$dbLabel = "GET_DEPTS_COURSES";
	$depts_courses = get_data($dbLabel, $sql);

	if(is_array($depts_courses)) {
		foreach($depts_courses as $row) {
			$array1 = array_slice($row, 0, 3);
			$array2 = array_slice($row, 3, 3);
			if(!is_array($data["depts"][$row["departmentId"]])) {
				//$array1["courses"] = array();
				$data["depts"][$row["departmentId"]] = $array1;
				$data["depts"][$row["departmentId"]]["courses"] = array();
			}
			$data["depts"][$row["departmentId"]]["courses"][] = $array2;
		}
	}

	//convert to non-associative for easier javascript iteration
	$data["teachers"] = array_values($data["teachers"]);
	$data["depts"] = array_values($data["depts"]);

} else {

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

UPDATE tmp_scheduling_students a, tmp_scheduling b SET a.schedId=b.schedId WHERE a.classId=b.classId;

 */

?>
