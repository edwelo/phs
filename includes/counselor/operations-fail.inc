<?php

	$sql = "SELECT
				a.studentId,
				CONCAT(a.firstName, ' ', a.lastName) AS studentName,
				b.grade AS gradeLevel,
				SUM((IF(c.q1grade < 65, 1, 0) + IF(c.q2grade < 65, 1, 0))) AS numFails,
				'not available' AS numInterventions,
				'not available' AS lastIntervention,
				'not available' AS status
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
			GROUP BY a.studentId
			ORDER BY gradeLevel, studentName";
	#echo str_replace("<", "&lt;", $sql) . "<br />\n";

	$error_messages = "";
	$data["rs"] = db_query($sql);
	$data["atn"] = "llcc";
	$data["tblstyle"] = "bodypanel";
	#$data["idlink"] = "?" . $_SERVER["QUERY_STRING"] . "&stuid=";

	$description = "Students who received a failing score in any quarter. (" . sizeof($data["rs"]) . " students)";
	$printstr .= "<div class=bodypanel>\n<span class=lbl1>" . $description . "</span><br />\n" . basichtmltable($data) . "<br />\n</div>\n";

?>
