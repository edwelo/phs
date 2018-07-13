<?php

########
## DATABASE FUNCTIONS - PALAU HIGH SCHOOL
########

function students_byId($sy = 0) {
	#returns array with studentId as key
	$sy--; //phs registrar database enrollment year is 1 less the school year
	$flds = "a.studentId, CONCAT(a.firstName, ' ', a.lastName) AS studentName, a.gender, b.grade AS gradeLevel";
	$sql = "SELECT $flds FROM tbl_student a, tbl_enrollment b WHERE a.studentId=b.studentId";
	if(is_numeric($sy)) $sql .= " AND b.year=$sy";
	$ret=array();
	$db=new mysqli("phsmysql.moe","mysql","mysql","phs");
	$rs=$db->query($sql) or die($db->error);
	while($tmp=$rs->fetch_assoc()) { $ret[$tmp["studentId"]] = $tmp; }
	$db->close;
	return $ret;
}

function student_schedule($stuid,$sy) {
	/*
	tbl_class: classId, courseid, teacherid, roomid (no data), year, semester, period
	tbl_schedule: scheduleId, enrolId, classid, q1grade, q2grade, q1abs, q2abs, semscore, semcredit
	tbl_enrollment: enrolId, studentId, gra#de, year
	tbl_teacher: teacherId, firstName, middleName, lastName
	tbl_course: courseId, name, grade, type
	tbl_room: roomId, name, capacity
	*/
	$sql="SELECT d.period, e.name AS subject, CONCAT(f.firstname,' ',IF(f.middleName,CONCAT(f.middleName,' '),''),f.lastName) AS teacher, g.name AS room FROM tbl_student a, tbl_enrollment b, tbl_schedule c, tbl_class d, tbl_course e, tbl_teacher f, tbl_room g WHERE a.studentId=b.studentId AND b.enrolId=c.enrolId AND c.classId=d.classId AND d.courseId=e.courseId AND d.teacherId=f.teacherId AND d.roomId=g.roomId AND a.studentId=$stuid AND b.year=$sy";
	$ret=array();
	$db=new mysqli("phsmysql.moe","mysql","mysql","phs");
	$rs=$db->query($sql) or die($db->error);
	while($tmp=$rs->fetch_assoc()) { $ret[]=$tmp; }
	$db->close;
	return $ret;
}

function find_student($searchphrase) {
	$concatStudentName = "CONCAT(a.firstName, ' ', IF(a.middleName, CONCAT(a.middleName, ' '), ''), a.lastName)";
	$sql="SELECT
			a.studentId AS stuid,
			${concatStudentName} AS stuname,
			a.gender,
			b.grade AS glvl,
			b.year AS year
		FROM
			phs.tbl_student a,
			(
			SELECT t1.*
			FROM phs.tbl_enrollment t1
			LEFT JOIN phs.tbl_enrollment t2
			ON t1.studentId=t2.studentId AND t1.year < t2.year
			WHERE t1.year IS NOT NULL AND t2.year IS NULL
			) AS b
		WHERE
			a.studentId=b.studentId AND
			${concatStudentName} LIKE'%" . $searchphrase . "%'
		ORDER BY stuname";
	global $db;
	$rs=$db->query($sql) or die("find_student: " . $db->error);
	while($tmp=$rs->fetch_assoc()) { $ret[]=$tmp; }
	$db->close;
	return $ret;
}

function student_transcript($stuid) {
	$db=new mysqli("phsmysql.moe", "mysql", "mysql", "phs");
	$fields = "a.studentId AS stuid, CONCAT(a.firstName,' ',IF(a.middleName,CONCAT(a.middleName,' '),''),a.lastName) AS stuname, b.year, b.grade, e.name AS coursename, e.departmentId, CONCAT(f.firstName, ' ', f.lastName) AS tchrName, CONCAT(d.semester, '-', d.period) AS 'sem-per', c.q1grade, c.q1abs, c.q2grade, c.q2abs, c.semscore AS score, c.semletter AS ltrgrade, c.semgpa AS gpa, IF(c.semgpa>=1,1,0) AS earned_cr";
	$sql="SELECT $fields FROM tbl_student a, tbl_enrollment b, tbl_schedule c, tbl_class d, tbl_course e, tbl_teacher f WHERE a.studentId=b.studentId AND b.enrolId=c.enrolId AND c.classid=d.classid AND d.courseId=e.courseId AND d.teacherID=f.teacherID AND a.studentId=$stuid ORDER BY b.year, d.semester, d.period";
	$rs=$db->query($sql) or die("find_student: " . $db->error);
	while($tmp=$rs->fetch_assoc()) { $ret[] = $tmp; }
	$db->close;
	return $ret;
}

function student_info1($stuid) {
	if(!is_numeric($stuid)) die("invalid stuid provided to function student_info1");
	//student bio plus latest grade level and year graduated
	$db=new mysqli("phsmysql.moe", "mysql", "mysql", "phs");
	$fields = "a.studentId AS stuid, CONCAT(a.firstName,' ',IF(a.middleName,CONCAT(a.middleName,' '),''),a.lastName) AS stuname, a.gender, b.year, b.grade";
	$sql="SELECT $fields FROM tbl_student a, tbl_enrollment b WHERE a.studentId=b.studentId AND a.studentId=$stuid ORDER BY b.year DESC LIMIT 1";
	$rs=$db->query($sql) or die("find_student: " . $db->error);
	$ret=$rs->fetch_assoc();
	$db->close;
	return $ret;
}

function student_grades($stuid) {
	$db=new mysqli("phsmysql.moe", "mysql", "mysql", "phs");
	$fields = "a.studentId AS stuid, CONCAT(a.firstName,' ',IF(a.middleName,CONCAT(a.middleName,' '),''),a.lastName) AS stuname, b.year, b.grade, e.name AS coursename, CONCAT(f.firstName, ' ', f.lastName) AS tchrName, d.period, d.semester, c.semscore AS score, c.semletter AS ltrgrade, c.semgpa AS gpa, IF(c.semgpa>=1,1,0) AS earned_cr";
	$sql="SELECT $fields FROM tbl_student a, tbl_enrollment b, tbl_schedule c, tbl_class d, tbl_course e, tbl_teacher f WHERE a.studentId=b.studentId AND b.enrolId=c.enrolId AND c.classid=d.classid AND d.courseId=e.courseId AND d.teacherID=f.teacherID AND a.studentId=$stuid ORDER BY b.year, d.semester";
	$rs=$db->query($sql) or die("find_student: " . $db->error);
	while($tmp=$rs->fetch_assoc()) { $ret[] = $tmp; }
	$db->close;
	return $ret;
}

function existing_school_years($stuid) {
	#$link = mysql_connect("192.168.1.64","keizyshiro","titich");
	$link = mysql_connect("phsmysql.moe","mysql","mysql");
	mysql_select_db("phs",$link);
	$sql="SELECT a.studentId AS stuid, CONCAT(a.firstName,' ',IF(a.middleName,CONCAT(a.middleName,' '),''),a.lastName) AS stuname, b.year, b.grade, e.name AS coursename, c.semscore AS score, c.semletter AS ltrgrade, c.semgpa AS gpa, IF(c.semgpa>=1,1,0) AS earned_cr FROM tbl_student a, tbl_enrollment b, tbl_schedule c, tbl_class d, tbl_course e WHERE a.studentId=b.studentId AND b.enrolId=c.enrolId AND c.classid=d.classid AND d.courseId=e.courseId AND a.studentId=$stuid ORDER BY b.year, d.semester";
	$query=mysql_query($sql,$link) or die("find_student: " . mysql_error());
	while($tmp=mysql_fetch_assoc($query)) { $ret[]=$tmp; }
	return $ret;
}

function student_status_list() {
	$db=new mysqli("phsmysql.moe","mysql","mysql");
	$fields = "a.studentId, a.firstName, a.middleName, a.lastName, a.gender, b.statusId, b.type, b.reason, b.date, b.length, b.notes";
	$sql = "SELECT $fields FROM phs.tbl_student a, phs.tbl_status b WHERE a.studentId = b.studentid ORDER BY a.firstName, a.lastName";
	$rs=$db->query($sql) or die($db->error);
	while($tmp=$rs->fetch_assoc()) { $ret[] = $tmp; }
	$db->close;
	return $ret;
}

function courses_list($thesy=NULL) {
	if(is_numeric($thesy)) { $phssy = $thesy - 1; } else { $phssy = $_SESSION["sy"] - 1; }
	for($y=2003; $y<=$phssy; $y++) {
		$fields .= "SUM(IF(b.year = (" . $y . ") AND d.semester = 1, 1, 0)) AS '" . (substr($y + 1, 2, 2)) . "s1',
						SUM(IF(b.year = (" . $y . ") AND d.semester = 2, 1, 0)) AS '" . (substr($y + 1, 2, 2)) . "s2',";
	}
	$fields = "e.name, " . trim($fields, ",") . " ";
	$db=new mysqli("phsmysql.moe","mysql","mysql");
	$sql = "SELECT $fields
				FROM phs.tbl_student a,phs.tbl_enrollment b,phs.tbl_schedule c, phs.tbl_class d, phs.tbl_course e
				WHERE a.studentId=b.studentID AND b.enrolId=c.enrolId
					AND c.classId=d.classId AND d.courseId=e.courseId
					AND (c.q1grade > 0 OR c.q2grade > 0)
					AND e.departmentId != 15
					GROUP BY e.courseId ORDER BY e.name";
	$rs=$db->query($sql) or die($db->error);
	while($tmp=$rs->fetch_assoc()) { $ret[] = $tmp; }
	$db->close;
	return $ret;
}

function courses_list2($thesy=NULL) {
	if(is_numeric($thesy)) { $phssy = $thesy - 1; } else { $phssy = $_SESSION["sy"] - 1; }
	for($y=2003; $y<=$phssy; $y++) {
		$fields .= "SUM(IF(b.year = (" . $y . ") AND b.semester = 1, 1, 0)) AS '" . (substr($y + 1, 2, 2)) . "s1',
						SUM(IF(b.year = (" . $y . ") AND b.semester = 2, 1, 0)) AS '" . (substr($y + 1, 2, 2)) . "s2',";
	}
	$fields = "a.name, " . trim($fields, ",") . " ";
	$db=new mysqli("phsmysql.moe","mysql","mysql");
	$sql = "SELECT $fields
				FROM phs.tbl_course a, phs.tbl_class b WHERE a.courseId=b.courseId AND a.departmentId != 15 GROUP BY a.courseId ORDER BY a.name";
	$rs=$db->query($sql) or die($db->error);
	while($tmp=$rs->fetch_assoc()) { $ret[] = $tmp; }
	$db->close;
	return $ret;
}
?>
