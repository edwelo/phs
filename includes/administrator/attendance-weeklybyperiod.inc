<?php

if($_POST["startDate"] && $_POST["endDate"]) {

	$tpldata["startDate"] = $_POST["startDate"]; $tpldata["endDate"] = $_POST["endDate"];

} else {

	$tpldata["endDate"] = date("Y-m-d");
	$tpldata["startDate"] = date("Y-m-d", mktime(0, 0, 0, date("n"), date("j") - 14, date("Y")));

}

$db=new mysqli("phsmysql.moe","mysql","mysql","phs");

$sql = "SELECT 
	a.absenceDate, a.studentId, CONCAT(c.firstName, ' ', c.lastName) AS stuname, b.period 
FROM 
	tbl_absence_phscouns a, tbl_class b, tbl_student c 
WHERE 
	a.classId=b.classID AND 
	a.studentId=c.studentId AND 
	absenceDate >= '" .  $tpldata["startDate"] . "' AND 
	absenceDate <= '" .  $tpldata["endDate"] . "' AND 
	absenceInfo LIKE 'on%'";

#printsql($sql);
$rs = $db->query($sql) or die($db->error . "<br />" . str_replace("<", "&lt;", $sql));

if($rs->num_rows) {
	//records exist
	
	while($tmp = $rs->fetch_assoc()) {
		$absenceCount_arr[$tmp["absenceDate"]][$tmp["period"]] += 1;
	}
	
	#dumpvar($absenceCount_arr);
	
	$html = "Absences Table<br />\n<table class=bodypanel>\n";
	$html .= "<tr><th>Date</th><th>Period 1 Abs</th><th>Period 2 Abs</th><th>Period 3 Abs</th><th>Period 4 Abs</th></tr>\n";
	
	foreach($absenceCount_arr as $absDate=>$row) {
		$html .= "<tr><td>" . $absDate . "</td>\n";
		for($i = 1; $i < 5; $i++) {
			$html .= "<td>" . $row[$i] . "</td>";
		}
		$html .= "</tr>\n";
	}		
	$html .= "</table>\n";
	
	/*
	$html = "Absences Table<br />\n<table>\n";
	$tmp = $rs->fetch_assoc();
	$html .= "<tr><th>" . implode("</th><th>", array_keys($tmp)) . "</th></tr>\n";
	$html .= "<tr><td>" . implode("</td><td>", $tmp) . "</td></tr>\n";
	while($tmp = $rs->fetch_assoc()) {
		$theRow = "<tr><td>" . implode("</td><td>", $tmp) . "</td></tr>\n";
		$html .= $theRow;
	}
	$html .= "</table>\n";
	*/

} else {
	//no records
	$html = "<p style='color: red;'>No absences found during this period'</p>\n";
}

$db->close;

$tpldata["content"] = $html;

$tpl = file_get_contents($template_file_fullpath);

?>
