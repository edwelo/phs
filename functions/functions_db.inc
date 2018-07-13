<?php
# database functions
# eo 2013-07-13

/*
SELECT * FROM
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
	d.teacherId=f.teacherId;
*/

function get_class($info) {
	if($info["classId"]) {

	} else {

	}
	$sql = "SELECT * FROM
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
				d.classId=288";

}

?>