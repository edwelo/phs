<?php

## eo 180708

error_reporting(E_ALL ^ E_NOTICE); //get rid of undefined variable notice

if($_GET["teacherId"] && $_GET["semPer"]) {

	$db = new mysqli("phsmysql.moe", "mysql", "mysql");

	if($_GET["courseId"]) { //save
		//check if record exists
		$sql = "SELECT * FROM phs.tmp_scheduling 
				WHERE 
					teacherId = " . $_GET["teacherId"] . " AND 
					semPer = " . $_GET["semPer"];
		$rs = $db->query($sql);
		if(mysqli_num_rows($rs) > 0) {
			$sql = "UPDATE phs.tmp_scheduling SET 
						courseId = " . $_GET["courseId"] . "
					WHERE
						teacherId = " . $_GET["teacherId"] . " AND 
						semPer = " . $_GET["semPer"];		
		} else {
			$sql = "INSERT INTO phs.tmp_scheduling SET 
						teacherId = " . $_GET["teacherId"] . ", 
						semPer = " . $_GET["semPer"] . ", 	
						courseId = " . $_GET["courseId"];
		}
		$rs = $db->query($sql) or die("save tchr sched: " . $db->error);
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
			WHERE a.teacherId=" . $_GET["teacherId"] . " AND 
				a.semPer=" . $_GET["semPer"] . " AND 
				a.courseId=c.courseId 
			GROUP BY a.schedId";

	$rs = $db->query($sql) or die("asofdate: " . $db->error);
	$data = $rs->fetch_assoc();

	$db->close;

	if(isset($_GET["a"])) {
		var_dump($data);
	} else {
		$myJSON = json_encode($data);
		echo $myJSON;
	}
}

?>
