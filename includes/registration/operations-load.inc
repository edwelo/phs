<?php

	//show the whole schedule

	//load the list

	unset($teachers_arr, $statistics_arr);

	$statistics_arr = array("ttltchrs"=>0, "obtchrs"=>0, "tbatchrs"=>0, "ttlstu"=>0, "tsratio"=>0, "fttchrs1"=>0, "2ttchrs1"=>0, "1ttchrs1"=>0, "0ttchrs1"=>0, "fttchrs2"=>0, "2ttchrs2"=>0, "1ttchrs2"=>0, "0ttchrs2"=>0);

	#$tchrassigntbl = "phs.tbl_teacherassignments2013"; //phs.tbl_regtchrassigns2013
	$sql = "SELECT a.teacherId, CONCAT(b.firstName, ' ', b.lastName) AS teacherName
			FROM phs_reg.tbl_regtchrassigns2013 a, phs.tbl_teacher b
			WHERE a.teacherId=b.teacherId ORDER BY teacherName";
	$rs = db_query($sql);
	foreach($rs as $value) {
		$teachers_arr[$value["teacherId"]]["teacherId"] = $value["teacherId"];
		$teachers_arr[$value["teacherId"]]["teacherName"] = $value["teacherName"];
	}

	$sql = "SELECT teacherId,
				SUM(IF(courseId > 0 AND SUBSTRING(period, 1, 1) = 1, 1, 0)) AS sem1classes,
				SUM(IF(courseId > 0 AND SUBSTRING(period, 1, 1) = 2, 1, 0)) AS sem2classes
			FROM phs_reg.tbl_regtchrassigns2013 GROUP BY teacherId";
	$rs = db_query($sql);
	foreach($rs as $value) {
		$teachers_arr[$value["teacherId"]]["sem1classes"] = $value["sem1classes"];
		$teachers_arr[$value["teacherId"]]["sem2classes"] = $value["sem2classes"];
	}

	$sql = "SELECT
				a.teacherId, COUNT(b.studentId) AS students
			FROM
				phs_reg.tbl_regtchrassigns2013 a LEFT JOIN
				phs_reg.tbl_regclasses2013 b ON a.classId=b.classId
			GROUP BY a.teacherId";
	$rs = db_query($sql);
	foreach($rs as $value) {
		$teachers_arr[$value["teacherId"]]["students"] = $value["students"];
	}

	$tbl123_html = "
<div class=flbeg>
<table class=ct3>
	<caption>Teacher Counts</caption>
	<tr><th>field</th><th>value</th></tr>
	<tr>
		<td align=right><span class=lbl1>Total Teachers:</span></td>
		<td>{ttltchrs}</td>
	<tr>
	<tr>
		<td align=right><span class=lbl1>On Board Teachers:</span></td>
		<td>{obtchrs}</td>
	<tr>
	<tr>
		<td align=right><span class=lbl1>TBA Teachers:</span></td>
		<td>{tbatchrs}</td>
	<tr>
	<tr>
		<td align=right><span class=lbl1>Total Students:</span></td>
		<td>{ttlstu}</td>
	<tr>
	<tr>
		<td align=right><span class=lbl1>Teacher/Student Ratio:</span></td>
		<td>{tsratio}</td>
	<tr>
</table>
</div>
<div class=flmid>
<table class=ct3>
	<caption>Work Load Counts</caption>
	<tr><th>field</th><th>Sem 1</th><th>Sem 2</th></tr>
	<tr>
		<td align=right><span class=lbl1>Full Time Teachers:</span></td>
		<td>{fttchrs1}</td>
		<td>{fttchrs2}</td>
	<tr>
	<tr>
		<td align=right><span class=lbl1>2/3 Time Teachers:</span></td>
		<td>{2ttchrs1}</td>
		<td>{2ttchrs2}</td>
	<tr>
	<tr>
		<td align=right><span class=lbl1>1/3 Time Teachers:</span></td>
		<td>{1ttchrs1}</td>
		<td>{1ttchrs2}</td>
	<tr>
	<tr>
		<td align=right><span class=lbl1>No Class Teachers:</span></td>
		<td>{0ttchrs1}</td>
		<td>{0ttchrs2}</td>
	<tr>
</table>
</div>
<div class=flend></div>
<br />
";

	$statistics_arr["ttltchrs"] = count($teachers_arr);

	foreach($teachers_arr as $value) {
		$full1 = $value["sem1classes"]; if($full1 > 3) $full1 = 3;
		$full2 = $value["sem2classes"]; if($full2 > 3) $full2 = 3;
		$xtra1 = 0; if($value["sem1classes"] > 3) $xtra1 = $value["sem1classes"] - 3;
		$xtra2 = 0; if($value["sem2classes"] > 3) $xtra2 = $value["sem2classes"] - 3;

		if(substr($value["teacherName"], 0, 3) == "Tba") $statistics_arr["tbatchrs"]++;
		if(substr($value["teacherName"], 0, 3) == "Tba") $statistics_arr["tbatchrs"]++;
		if(!$full1) $statistics_arr["0ttchrs1"]++;
		if($full1 == 1) $statistics_arr["1ttchrs1"]++;
		if($full1 == 2) $statistics_arr["2ttchrs1"]++;
		if($full1 > 2) $statistics_arr["fttchrs1"]++;
		if(!$full2) $statistics_arr["0ttchrs2"]++;
		if($full2 == 1) $statistics_arr["1ttchrs2"]++;
		if($full2 == 2) $statistics_arr["2ttchrs2"]++;
		if($full2 > 2) $statistics_arr["fttchrs2"]++;

		$value["sem1 full time"] = "<div style='width: " . (3 * 30) . ";'><div style='background-color: tan; width: " . $full1 * 30 . "px; height: 12px;'></div></div>";
		$value["sem1 extra"] = "<div style='background-color: brown; width: " . $xtra1 * 30 . "px; height: 12px;'></div>";
		$value["sem2 full time"] = "<div style='width: " . (3 * 30) . ";'><div style='background-color: tan; width: " . $full2 * 30 . "px; height: 12px;'></div></div>";
		$value["sem2 extra"] = "<div style='background-color: brown; width: " . $xtra2 * 30 . "px; height: 12px;'></div>";
		if($permitted) {
			$value["class list"] = "<span class=lnk1><a href='../print/print_phs_allclasseslist.php?teacherId=" . $value["teacherId"] . "' target='teacherClassList'>print</a></span>";
		} else {
			unset($value["teacherId"]);
		}
		$data["rs"][] = $value;
	}
	$data["rownums"] = "y";
	$data["atn"] = "lccn"; if($permitted) $data["atn"] = "clccn";

	$statistics_arr["obtchrs"] = $statistics_arr["ttltchrs"] - $statistics_arr["tbatchrs"];

	foreach($statistics_arr as $key=>$value) {
		$tbl123_html = str_replace("{" . $key . "}", $value, $tbl123_html);
	}

	$tpldata["hrefpre"] = $hrefpre;

	$printstr = $sy_html . $tbl123_html . basichtmltable($data);

?>