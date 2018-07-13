<?php

function get_teachers() {

	$db = new mysqli("phsmysql.moe", "mysql", "mysql");

	$sql = "SET @latestPHSYear = (SELECT MAX(year) FROM phs.tbl_class)";
	$rs = $db->query($sql) or die("asofdate: " . $db->error);
	
	$sql = "SELECT 
					c.abbrev AS dept, a.teacherId, 
					CONCAT(a.lastName, ', ', LEFT(a.firstName, 1)) AS teacherName 
				FROM 
					phs.tbl_teacher a, phs.tbl_class b, phs.tbl_department c 
				WHERE 
					a.teacherId=b.teacherId AND a.departmentId=c.departmentId AND 
					b.year=@latestPHSYear AND persid_moe IS NOT NULL AND 
					persid_moe > 1 
				GROUP BY a.teacherId ORDER BY dept, teacherName";
	$rs = $db->query($sql) or die("asofdate: " . $db->error);
	
	unset($tmp2);
	for($s=1; $s<3; $s++) {
		for($p=1; $p<5; $p++) {
			$key = $s . $p;
			$tmp2[$key] = null;
		}
	}
	
	while($tmp = $rs->fetch_assoc()) {
		$arr[] = $tmp + $tmp2;
	}
	
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
	$rs = $db->query($sql) or die("asofdate: " . $db->error);
	while($tmp = $rs->fetch_assoc()) {
		$arr2[$tmp["teacherId"]] = $tmp;
	}
	
	foreach($arr as $key=>$row) {
		if(isset($arr2[$row["teacherId"]])) {
			$arr[$key][$arr2[$row["teacherId"]]["semPer"]] = $arr2[$row["teacherId"]]["courseAbbrv"] . " (" . $arr2[$row["teacherId"]]["numStudents"] . ")";
		}
	}
	
	return $arr;
	
$db->close;

}

function get_courses() {
	$db = new mysqli("phsmysql.moe", "mysql", "mysql");

	$sql = "SET @latestPHSYear = (SELECT MAX(year) FROM phs.tbl_class)";
	$rs = $db->query($sql) or die("asofdate: " . $db->error);
	
	$sql = "SELECT 
				a.courseId, a.name AS courseName, a.departmentId, a.grade
			FROM phs.tbl_course a, phs.tbl_class b
			WHERE a.courseId=b.courseId AND year=@latestPHSYear
			GROUP BY a.courseId ORDER BY name";
	$rs = $db->query($sql) or die("courses: " . $db->error);
	while($tmp = $rs->fetch_assoc()) {
		$arr[] = $tmp;
	}

	return $arr;	
}

$tpl = file_get_contents($template_file_fullpath);

$search = "/[ \t]*<tr id=row.*?<\/tr>.*?[\r\n]/s";
preg_match($search, $tpl, $matches);
$tmp = str_replace(" id=row", "", $matches[0]);

$html_rows = "";

$teachers = get_teachers();
foreach($teachers as $row) {
	$html_row = $tmp;
	foreach($row as $key=>$value) {
		$html_row = str_replace("{" . $key . "}", $value, $html_row);
	}
	$html_rows .= $html_row;
}
$tpl = str_replace($matches[0], $html_rows, $tpl);

$courses = get_courses();
$courses_selOpts = "";
foreach($courses as $row) {
	$courses_selOpts .= "<option value=" . $row["courseId"] . ">" . $row["courseName"] . "</option>";
}
$tpl = str_replace("{courses_selOpts}", $courses_selOpts, $tpl);

$tpl = str_replace("{content}", $html, $tpl);

?>
