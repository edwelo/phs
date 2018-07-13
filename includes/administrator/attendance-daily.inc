<?php

if($_POST["absenceDate"]) {

	$tpldata["absenceDate"] = $_POST["absenceDate"];

} else {

	$tpldata["absenceDate"] = date("Y-m-d");

}

$db=new mysqli("phsmysql.moe","mysql","mysql","phs");

$sql = "SELECT 
        a.absenceDate, a.studentId, CONCAT(c.firstName, ' ', c.lastName) AS stuname, b.period, CONCAT(d.nameAbbrv, '/', e.lastName) AS className 
FROM 
        tbl_absence_phscouns a, tbl_class b, tbl_student c, tbl_course d, tbl_teacher e 
WHERE 
        a.classId=b.classID AND 
        a.studentId=c.studentId AND 
	b.courseId=d.courseId AND
	b.teacherId=e.teacherId AND 
        absenceDate = '" .  $tpldata["absenceDate"] . "' AND 
        absenceInfo LIKE 'on%'
ORDER BY
	stuname";
#printsql($sql);
$rs = $db->query($sql) or die($db->error . "<br />" . str_replace("<", "&lt;", $sql));

if($rs->num_rows) {
	//records exist
	
	while($tmp = $rs->fetch_assoc()) {
		$absenceCount_arr[$tmp["studentId"]]["stuname"] = $tmp["stuname"];
		$absenceCount_arr[$tmp["studentId"]]["total"]++;
		$absenceCount_arr[$tmp["studentId"]][$tmp["period"]] = $tmp["className"];
		$totals[$tmp["period"]]++;
	}
	
	#dumpvar($absenceCount_arr);
	
	$html = "Absent Students Total<br />\n<table class=bodypanel>\n";
	$html .= "<tr><th></th><th>1st Period</th><th>2nd Period</th><th>3rd Period</th><th>4th Period</th></tr>\n";
	$html .= "<tr><td>Total</td>";
		$html .= "<td>" . $totals[1] . "</td>";
		$html .= "<td>" . $totals[2] . "</td>";
		$html .= "<td>" . $totals[3] . "</td>";
		$html .= "<td>" . $totals[4] . "</td></tr>";
	$html .= "</table>\n<br />\n";

	$html .= "Absent Students List<br />\n<table class=bodypanel>\n";
	$html .= "<tr><th>ID</th><th>Student</th><th>Total</th><th>1st Period</th><th>2nd Period</th><th>3rd Period</th><th>4th Period</th></tr>\n";
	
	foreach($absenceCount_arr as $studentId=>$row) {
		$html .= "<tr><td>" . $studentId . "</td><td>" . $row["stuname"] . "</td><td>" . $row["total"] . "</td>";
		for($i = 1; $i < 5; $i++) {
			$html .= "<td>" . $row[$i] . "</td>";
		}
		$html .= "</tr>\n";
	}		
	$html .= "</table>\n";
	
} else {
	//no records
	$html = "<p style='color: red;'>No absences found during this period'</p>\n";
}

$db->close;

$tpldata["content"] = $html;

$tpl = file_get_contents($template_file_fullpath);

?>
