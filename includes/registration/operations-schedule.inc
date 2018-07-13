<?php

//show the whole schedule

//load the list

$tmp_arr = array("id"=>"", "teacherName"=>"", "department"=>"");

for($i=1; $i<3; $i++) {
	for($j=1; $j<5; $j++) {
		$tmp_arr["taId" . $i . $j] = "";
		$tmp_arr["courseName" . $i . $j] = "";
		$tmp_arr["sec" . $i . $j] = "";
		$tmp_arr["N" . $i . $j] = "";
		$tmp_arr["color" . $i . $j] = "";
		$tmp_arr["taId2" . $i . $j] = "";
		$tmp_arr["courseName2" . $i . $j] = "";
		$tmp_arr["sec2" . $i . $j] = "";
		$tmp_arr["N2" . $i . $j] = "";
		$tmp_arr["color2" . $i . $j] = "";
	}
}

//department select options
$dept_selopts=""; unset($deptid);
$sql = "SELECT * FROM phs.tbl_department WHERE abbrev != '' ORDER BY abbrev";
$rs = db_query($sql);
foreach($rs as $value) {
	$dept_selopts .= "<option value=" . $value["departmentId"] . ">" . $value["abbrev"] . "</option>\n";
}
if($dept_selopts = str_replace("value=" . $_GET["dept"] . ">", "value=" . $_GET["dept"] . " selected>", $dept_selopts)) {
	$deptid = $_GET["dept"];
}

$sql = "SELECT
			e.departmentId, e.abbrev AS department,
			a.classId, a.period,
			a.teacherId, CONCAT(c.firstName, ' ', c.lastName) AS teacherName,
			d.courseId, d.name AS courseName, d.nameAbbrv As shortCourseName,
			SUM(IF(b.studentId, 1, 0)) AS 'N'
		FROM
			phs_reg.tbl_regtchrassigns2013 a LEFT JOIN
			phs_reg.tbl_regclasses2013 b ON a.classId=b.classId,
			phs.tbl_teacher c,
			phs.tbl_course d,
			phs.tbl_department e
		WHERE
			a.teacherId=c.teacherId AND
			a.courseId=d.courseId AND
			c.departmentId=e.departmentId
		GROUP BY a.teacherId, a.period
		ORDER BY department, teacherName";
if($deptid) {
	$sql = str_replace("GROUP BY", " AND c.departmentId=" . $deptid . " GROUP BY", $sql);
}

#printsql($sql);

$rs2 = db_query($sql);

foreach($rs2 as $value) {
	if(!isset($tmp2_arr[$value["teacherId"]])) {
		$tmp2_arr[$value["teacherId"]] = $tmp_arr;
		$tmp2_arr[$value["teacherId"]]["id"] = $value["teacherId"];
		$tmp2_arr[$value["teacherId"]]["teacherName"] = $value["teacherName"];
		$tmp2_arr[$value["teacherId"]]["department"] = $value["department"];
	}
	$key = $value["period"];
	$tmp2_arr[$value["teacherId"]]["sec2" . $key] = $value["section"];
	$tmp2_arr[$value["teacherId"]]["taId2" . $key] = $value["classId"];
	$tmp2_arr[$value["teacherId"]]["N2" . $key] = $value["N"];
	$tmp2_arr[$value["teacherId"]]["color2" . $key] = "brown"; if($value["N"] > 20 ) $tmp2_arr[$value["teacherId"]]["color" . $key] = "red";
	$tmp2_arr[$value["teacherId"]]["courseName2" . $key] = $value["shortCourseName"];
}

#dumpvar($tmp2_arr);

#============================

$tpl = file_get_contents($template_file_fullpath);

$tpl = str_replace("{dept_selopts}", $dept_selopts, $tpl);

if($permitted) {
	$search = "/<tr id=tblrow2 .* rowend2 -->\n/s";
	$tpl = preg_replace($search, "", $tpl);
	preg_match("/<tr id=tblrow .* rowend -->\n/s", $tpl, $matches);
	$tblrow = str_replace(" id=tblrow", "", $matches[0]);
	$tblrow = str_replace("<!-- rowend -->\n", "", $tblrow);
} else {
	$search = "/<!-- section 1 .* \/section 1 -->\n/s";
	$tpl = preg_replace($search, "", $tpl);
	$search = "/<tr id=tblrow .* rowend -->\n/s";
	$tpl = preg_replace($search, "", $tpl);
	preg_match("/<tr id=tblrow2 .* rowend2 -->\n/s", $tpl, $matches);
	$tblrow = str_replace(" id=tblrow2", "", $matches[0]);
	$tblrow = str_replace("<!-- rowend2 -->\n", "", $tblrow);
}

#dumpvar($tmp2_arr);

unset($tmp, $tmp2, $tblrows);
foreach($tmp2_arr as $key=>$value) {
	$tmp = str_replace("{department}", $value["department"], $tblrow);
	$tmp = str_replace("{teacherId}", $key, $tmp);
	$tmp = str_replace("{teacherName}", $value["teacherName"], $tmp);
	$tmp = str_replace("{section}", $value["section"], $tmp);
	for($i=1; $i<3; $i++) {
		for($j=1; $j<5; $j++) {
			$tmp = str_replace("{taId2" . $i . $j . "}", $value["taId2" . $i . $j], $tmp);
			$tmp = str_replace("{N2" . $i . $j . "}", $value["N2" . $i . $j], $tmp);
			$tmp = str_replace("{courseName2" . $i . $j . "}", $value["courseName2" . $i . $j], $tmp);
			$tmp = str_replace("{sec2" . $i . $j . "}", $value["sec2" . $i . $j], $tmp);
			$tmp = str_replace("{color2" . $i . $j . "}", $value["color2" . $i . $j], $tmp);
		}
	}
	$tblrows .= "\t" . $tmp . "\n";
}

$printstr = str_replace($matches[0], $tblrows, $tpl);

$tpldata["hrefpre"] = $hrefpre;
$tpldata["getpre"] = $getpre;
$tpldata["tab"] = $tab;
$tpldata["thesy"] = $thesy;
$printstr = $sy_html . $tabs_html . $printstr;

?>