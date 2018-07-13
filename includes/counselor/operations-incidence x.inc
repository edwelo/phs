<?php

	$sql = "SELECT
				a.studentId,
				CONCAT(a.firstName, ' ', a.lastName) AS studentName,
				SUM((IF(c.q1grade < 65, 1, 0) + IF(c.q2grade < 65, 1, 0))) AS numFails
			FROM
				phs.tbl_student a,
				(SELECT t1.* FROM phs.tbl_enrollment t1 WHERE t1.year=$phssy) AS b,
				phs.tbl_schedule c,
				phs.tbl_class d,
				phs.tbl_course e,
				phs.tbl_teacher f
			WHERE a.studentId=b.studentId
			AND b.enrolId=c.enrolId
			AND c.classId=d.classId
			AND d.courseId=e.courseId
			AND d.teacherId=f.teacherId
			AND (c.q1grade < 65 OR c.q2grade < 65)
			GROUP BY a.studentId";
	$sql = "SELECT
				a.studentId,
				CONCAT(a.firstName, ' ', a.lastName) AS studentName,
				g.date,
				g.type,
				g.reason,
				g.notes
			FROM
				phs.tbl_student a,
				(SELECT t1.* FROM phs.tbl_enrollment t1 WHERE t1.year=$phssy) AS b,
				phs.tbl_schedule c,
				phs.tbl_class d,
				phs.tbl_course e,
				phs.tbl_teacher f,
				phs.tbl_status g
			WHERE a.studentId=b.studentId
			AND b.enrolId=c.enrolId
			AND c.classId=d.classId
			AND d.courseId=e.courseId
			AND d.teacherId=f.teacherId
			AND a.studentId=g.studentId
			ORDER BY a.studentId, g.date";

	#echo str_replace("<", "&lt;", $sql) . "<br />\n";

	$error_messages = "";
	$data["rs"] = db_query($sql);
	echo str_replace("<", "&lt;",$error_messages) . "<br />\n";

	$data["atn"] = "llcc";
	$data["idlink"] = "?" . $_SERVER["QUERY_STRING"] . "&stuid=";

	$description = "Students who received a failing score in any quarter.";
	$printstr .= "<span class=lbl1>" . $description . "</span><br />\n" . basichtmltable($data) . "<br />\n";

?>