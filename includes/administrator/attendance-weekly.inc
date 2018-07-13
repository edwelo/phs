<?php

if($_POST["startDate"] && $_POST["endDate"]) {

	$tpldata["startDate"] = $_POST["startDate"]; $tpldata["endDate"] = $_POST["endDate"];

} else {

	$tpldata["endDate"] = date("Y-m-d");
	$tpldata["startDate"] = date("Y-m-d", mktime(0, 0, 0, date("n"), date("j") - 14, date("Y")));

}

$db=new mysqli("phsmysql.moe","mysql","mysql","phs");

$sql = "SELECT a.absenceDate, a.studentId, CONCAT(c.firstName,' ', c.lastName) AS stuname, COUNT(*) AS absenceCount FROM tbl_absence_phscouns a, tbl_class b, tbl_student c WHERE a.classId=b.classID AND a.studentId=c.studentId AND absenceDate >= '" . $tpldata["startDate"] . "' AND absenceDate <= '" .  $tpldata["endDate"] . "' AND absenceInfo LIKE 'on%' GROUP BY absenceDate, studentId";
#printsql($sql);
$rs = $db->query($sql) or die($db->error . "<br />" . str_replace("<", "&lt;", $sql));

if($rs->num_rows) {
	//records exist
	
	while($tmp = $rs->fetch_assoc()) {
		$absenceCount_arr[$tmp["absenceDate"]][$tmp["absenceCount"]] += 1;
	}
	
	#dumpvar($absenceCount_arr);
	
	$html = "Absences Table<br />\n<table class=bodypanel>\n";
	$html .= "<tr><th>Date</th><th>Absent 1 class</th><th>Absent 2 classes</th><th>Absent 3 Classes</th><th>Absent All 4 Classes</th></tr>\n";
	
	foreach($absenceCount_arr as $absDate=>$row) {
		$html .= "<tr><td>" . $absDate . "</td>\n";
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
