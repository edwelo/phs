<?php

## Edwel 120728

$sql="SELECT a.teacherId, CONCAT(b.firstName, ' ', b.lastName) AS teacherName,
			b.departmentId, c.name AS departmentName, c.abbrev AS departmentAbbrev
		FROM phs_reg.tbl_regtchrassigns2013 a, phs.tbl_teacher b, phs.tbl_department c
		WHERE a.teacherId=b.teacherId AND b.departmentId=c.departmentId
		GROUP BY a.teacherId ORDER BY departmentAbbrev, teacherName";
$rs = db_query($sql);

unset($tmp, $printstr);

foreach($rs as $value) {
	$tmp[$value["departmentAbbrev"]][$value["teacherId"]] = $value["teacherName"];
}

$i=0;
foreach($tmp as $departmentAbbrev=>$teachers) {

	$tmp2 = "<div class=flmid style='border: 1px solid tan; padding: 6px; font-size: x-small;'><span style='font-size: small; font-weight: bold; color: brown;'>" . $departmentAbbrev . "</span><br />\n" . implode("<br />\n", $teachers) . "\n</div>\n";
	if($i == 0) { $tmp2 = str_replace("flmid", "flbeg", $tmp2); }

	$printstr .= $tmp2;

	$i++;

	if($i == 7) {
		$i=0;
		$printstr .= "<div class=flend></div>\n<br />\n";
	}
}

$printstr = "<span class=lbl1>LIST OF TEACHERS BY DEPARTMENT</span><br /><br />\n" . $printstr;

?>
