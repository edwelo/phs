<?php

######
# functions for phstchrs/operations.inc
# eo 130918
######

function getClassList($teacherId, $phssy) {
	if(is_numeric($teacherId)) {
		$db=new mysqli("phsmysql.moe","mysql","mysql","phs");
		$sql = "SELECT
					c.classId,
					e.name AS courseName,
					d.semester,
					d.period,
					COUNT(*) AS numberEnrolled
				FROM
					phs.tbl_schedule c,
					phs.tbl_class d,
					phs.tbl_course e
				WHERE
					c.classId=d.classId AND
					d.courseId=e.courseId AND
					d.teacherId = " . $_SESSION["teacherId"] . " AND
					d.year = $phssy
				GROUP BY d.classId
				ORDER BY d.semester, d.period";
		$rs = $db->query($sql) or die("function getClassList db error: " . $db->error);;
		while($tmp = $rs->fetch_assoc()) { $ret[] = $tmp; }
		return $ret;
	} else {
		die("function getClassList aborted: missing teacher id");
	}
}

function getQuarterInfo($phssy=NULL, $semester=NULL, $offset=NULL) {
	global $csy;
	if(!is_int($phssy) || $phssy < 2004 || $phssy > $csy) $phssy = $_SESSION["phssy"];
	$year = $phssy + 1;
	if($semester == 1 || $semester == 2) {
		if(!$thedate) $thedate = date("Y-m-d");
		$tmp = file_get_contents("data/quarters.txt");
		preg_match("/" . $year . ":.*/", $tmp, $matches);
		if($matches[0]) {
			list(, $tmp2) = explode(":", $matches[0]);
			$tmp_arr = explode(",", $tmp2);
			#  0     1     2     3     4     5     6     7     8     9    10    11
			#s1q1s,s1q1m,s1q1e,s1q2s,s1q2m,s1q2e,s2q1s,s2q1m,s2q1e,s2q2s,s2q2m,s2q2e
			$ret = "1,1," . $tmp_arr[0] . "," . $tmp_arr[1] . "," . $tmp_arr[2];
			if($thedate >= $tmp_arr[3]) { $ret = "1,2," . $tmp_arr[3] . "," . $tmp_arr[4] . "," . $tmp_arr[5]; }
			if($thedate >= $tmp_arr[6]) { $ret = "2,1," . $tmp_arr[6] . "," . $tmp_arr[7] . "," . $tmp_arr[8]; }
			if($thedate >= $tmp_arr[9]) { $ret = "2,2," . $tmp_arr[9] . "," . $tmp_arr[10] . "," . $tmp_arr[11]; }
			return $ret;
		} else {
			die("Aborted function getQuarterInfo: quarter info does not exist for school year $year");
		}
	} else {
		die("Aborted function getQuarterInfo: invalid semester (" . $semester . ") provided.");
	}
}

function getClassInfo($classId=NULL) {
	if($classId) {
		$db=new mysqli("phsmysql.moe","mysql","mysql","phs");
		$sql = "SELECT d.*, e.name AS courseName,
					CONCAT(g.firstName, ' ', g.lastName) AS teacherName
				FROM phs.tbl_class d, phs.tbl_course e, phs.tbl_teacher g
				WHERE d.courseId=e.courseId AND d.teacherId=g.teacherId AND d.classId='" . $classId . "'";
		$rs=$db->query($sql) or die("function getClassInfo db error: " . $db->error);
		if($rs->num_rows) {
			$ret = $rs->fetch_assoc();
			//get quarter info
			if(is_file("../data/quarters.txt")) $tmp = file_get_contents("../data/quarters.txt");
			if(is_file("data/quarters.txt")) $tmp = file_get_contents("data/quarters.txt");
			preg_match("/" . ($ret["year"] + 1) . ":.*/", $tmp, $matches);
			if($matches[0]) {
				list(, $tmp2) = explode(":", $matches[0]);
				$tmp_arr = explode(",", $tmp2);
				#  0     1     2     3     4     5     6     7     8     9    10    11
				#s1q1s,s1q1m,s1q1e,s1q2s,s1q2m,s1q2e,s2q1s,s2q1m,s2q1e,s2q2s,s2q2m,s2q2e
				$index_start = 0; if($ret["semester"] == 2) $index_start = 6;
				$ret["quarterInfo"][1] = array("start"=>$tmp_arr[$index_start], "mid"=>$tmp_arr[$index_start + 1], "end"=>$tmp_arr[$index_start + 2]);
				$ret["quarterInfo"][2] = array("start"=>$tmp_arr[$index_start + 3], "mid"=>$tmp_arr[$index_start + 4], "end"=>$tmp_arr[$index_start + 5]);
				return $ret;
			} else {
				die("Aborted function getClassInfo: quarter info does not exist for school year " . $ret["year"]);
			}
		} else {
			die("Aborted function getClassInfo: Coulnd not find (" . $classId . ") in database");
		}
		$db->close;
	} else {
		die("Aborted function getClassInfo: invalid classid (" . $classId . ") provided");
	}
}

function getClassRosterAndGrades($classId = NULL) {
	$db=new mysqli("phsmysql.moe","mysql","mysql","phs");
	$sql = "SELECT
				t1.*, t2.*
			FROM
				(SELECT
					a.studentId AS stuid,
					CONCAT(a.lastName, ', ', a.firstName, ' ', a.middleName) AS studentName,
					a.gender, a.birthDate, b.grade, b.year AS sy
				FROM
					phs.tbl_student a,
					phs.tbl_enrollment b,
					phs.tbl_schedule c
				WHERE
					a.studentId=b.studentId AND
					b.enrolId=c.enrolId AND
					c.classId = '" . $classId . "') t1 LEFT JOIN
				phs.tbl_grades t2 ON t1.stuid=t2.studentId
			WHERE t2.classId = '" . $classId . "'
			ORDER BY studentName";
	$rs=$db->query($sql) or die($db->error);
	if($rs->num_rows) {
		while($tmp = $rs->fetch_assoc()) { $ret[] = $tmp; }
		return $ret;
	} else {
		die("getClassRosterAndGrades for classId = $classId failed with no records.");
	}
	$db->close;
}

function get_class_absences($classId) {
	$db=new mysqli("phsmysql.moe","mysql","mysql","phs");
	$sql = "SELECT
				*
			FROM
				phs.tbl_absence_phscouns
			WHERE
				classId = '" . $classId . "'";
	#printsql($sql);
	$rs=$db->query($sql) or die($db->error);
	while($tmp = $rs->fetch_assoc()) { $ret[] = $tmp; }
	return $ret;
	$db->close;
}

function count_absences($classId, $q1_params, $q2_params) {
	$absences_arr = get_class_absences($classId);
	if(is_array($absences_arr)) {
		foreach($absences_arr as $record) {
			unset($type);
			list($absent, $tardy, ) = explode("|", $record["absenceInfo"]);
			if($tardy) $type = "T";
			if($absent) $type = "A"; //this needs to come after tardy, A overrides T
			if($type) {
				if($record["absenceDate"] >= $q1_params["start"] && $record["absenceDate"] <= $q1_params["mid"]) $absences_counts[$record["studentId"]]["q1m"][$type]++;
				if($record["absenceDate"] >= $q1_params["start"] && $record["absenceDate"] <= $q1_params["end"]) $absences_counts[$record["studentId"]]["q1e"][$type]++;
				if($record["absenceDate"] >= $q2_params["start"] && $record["absenceDate"] <= $q2_params["mid"]) $absences_counts[$record["studentId"]]["q2m"][$type]++;
				if($record["absenceDate"] >= $q2_params["start"] && $record["absenceDate"] <= $q2_params["end"]) $absences_counts[$record["studentId"]]["q2e"][$type]++;
			}
		}
	}
	return $absences_counts;
}

function get_classesGradesSummaries($phssy, $teacherId=NULL) {
	$sql1 = "SELECT b.classId, COUNT(a.q1ms) AS countq1mScores, SUM(a.q1ms) AS sumq1mScores, '' AS avgq1mScore, MIN(a.q1ms) AS minq1mScore, MAX(a.q1ms) AS maxq1mScore, STD(a.q1ms) AS stdq1mScore, COUNT(a.q1es) AS countq1eScores, SUM(a.q1es) AS sumq1eScores, '' AS avgq1eScore, MIN(a.q1es) AS minq1eScore, MAX(a.q1es) AS maxq1eScore, STD(a.q1es) AS stdq1eScore, COUNT(a.q2ms) AS countq2mScores, SUM(a.q2ms) AS sumq2mScores, '' AS avgq2mScore, MIN(a.q2ms) AS minq2mScore, MAX(a.q2ms) AS maxq2mScore, STD(a.q2ms) AS stdq2mScore, COUNT(a.q2es) AS countq2eScores, SUM(a.q2es) AS sumq2eScores, '' AS avgq2eScore, MIN(a.q2es) AS minq2eScore, MAX(a.q2es) AS maxq2eScore, STD(a.q2es) AS stdq2eScore FROM phs.tbl_grades a, phs.tbl_class b WHERE a.classId=b.classId AND b.year=" . $_SESSION["phssy"] . " GROUP BY a.classId";

	$sql2 = "SELECT t4.teacherId, CONCAT(t4.firstName, ' ', t4.lastName) AS teacherName, t1.classId, t3.nameAbbrv AS courseName, t2.semester, t2.period, t2.courseId, t2.teacherId, COUNT(*) AS countStudents FROM phs.tbl_schedule t1, phs.tbl_class t2, phs.tbl_course t3, phs.tbl_teacher t4 WHERE t1.classId=t2.classId AND t2.courseId=t3.courseId AND t2.teacherId=t4.teacherId AND t2.year=" . $_SESSION["phssy"] . " GROUP BY t1.classId ORDER BY teacherName, semester, period";

	if($teacherId) {
		$sql1 = str_replace(" GROUP BY", " AND b.teacherId=$teacherId GROUP BY", $sql1);
		$sql2 = str_replace(" GROUP BY", " AND t2.teacherId=$teacherId GROUP BY", $sql2);
	}

	#printsql($sql1);

	unset($tmp_arr);
	$tmp_arr = db_query($sql1);

	foreach($tmp_arr as $value) {
		$classId = $value["classId"];
		unset($value["classId"]);
		$value["stdq1mScore"] = round($value["stdq1mScore"], 2);
		$value["stdq1eScore"] = round($value["stdq1eScore"], 2);
		$value["stdq2mScore"] = round($value["stdq2mScore"], 2);
		$value["stdq2eScore"] = round($value["stdq2eScore"], 2);
		$grades_arr[$classId] = $value;
	}

	$grades_arr_blank = current($grades_arr);
	foreach($grades_arr_blank as $key=>$value) {
		$grades_arr_blank[$key] = "";
	}

	unset($tmp_arr);
	$tmp_arr = db_query($sql2);
	foreach($tmp_arr as $key=>$value) {
		if(is_array($grades_arr[$value["classId"]])) {
			$classesInfo_arr[] = array_merge($value, $grades_arr[$value["classId"]]);
		} else {
			$classesInfo_arr[] = array_merge($value, $grades_arr_blank);
		}
	}

	#dumpvar($classesInfo_arr);

	return $classesInfo_arr;
}

function get_teachersStudentGrades($phssy, $teacherId) {

	$sql1 = "SELECT a.* FROM phs.tbl_grades a, phs.tbl_class b WHERE a.classId=b.classId AND b.teacherId = $teacherId AND b.year = $phssy";

	$sql2 = "SELECT
				d.teacherId,
				CONCAT(f.firstName, ' ', f.lastName) AS teacherName,
				c.classId,
				e.nameAbbrv AS courseName,
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
				d.year=$phssy AND
				d.teacherId=$teacherId
			ORDER BY teacherName, classId, studentName";

	#printsql($sql1);

	unset($tmp_arr);
	$tmp_arr = db_query($sql1);
	foreach($tmp_arr as $value) {
		$id = $value["classId"] . "." . $value["studentId"];
		unset($value["classId"], $value["studentId"]);
		array_pop($value); array_pop($value); array_pop($value); array_pop($value);
		$grades_arr[$id] = $value;
	}
	#dumpvar($grades_arr);

	$grades_arr_blank = current($grades_arr);
	foreach($grades_arr_blank as $key=>$value) {
		$grades_arr_blank[$key] = "";
	}

	unset($tmp_arr);
	$tmp_arr = db_query($sql2);
	#dumpvar($tmp_arr);
	foreach($tmp_arr as $key=>$value) {
		$id = $value["classId"] . "." . $value["studentId"];
		if(array_key_exists($id, $grades_arr)) {
			$classesInfo_arr[] = array_merge($value, $grades_arr[$id]);
		} else {
			$classesInfo_arr[] = array_merge($value, $grades_arr_blank);
		}
	}

	#dumpvar($classesInfo_arr);

	return $classesInfo_arr;

}

function get_teachers_student_list($teacherId, $phssy) {
	$db=new mysqli("phsmysql.moe","mysql","mysql","phs");
	$sql = "SELECT
				a.studentId,
				CONCAT(a.lastName, ', ', a.firstName) AS studentName
			FROM
				phs.tbl_student a,
				phs.tbl_enrollment b,
				phs.tbl_schedule c,
				phs.tbl_class d
			WHERE
				a.studentId = b.studentId AND
				b.enrolId = c.enrolId AND
				c.classId=d.classId AND
				d.teacherId = $teacherId AND
				d.year = $phssy
			GROUP BY a.studentId
			ORDER BY studentName";
	$rs = $db->query($sql) or die("function get_teachers_student_list db error: " . $db->error);;
	$db->close;
	if($rs->num_rows) {
		while($tmp = $rs->fetch_assoc()) { $ret[] = $tmp; }
		return $ret;
	} else {
		die("function get_teachers_student_list aborted: no records for teacher=$teacherId and phssy=$phssy");
	}
}

?>
