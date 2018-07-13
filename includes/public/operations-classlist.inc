<?php

$printstr = file_get_contents($template_file_fullpath);

if($permitted) {
	//set up tchr_selopts
	$tchr_selopts = "";
	$sql = "SELECT
				a.teacherId, b.firstName, b.lastName
			FROM phs_reg.tbl_regtchrassigns" . $csy . " a, phs.tbl_teacher b
			WHERE a.teacherId=b.teacherId GROUP BY a.teacherId
			ORDER BY b.firstName, b.lastName";
	$rs = db_query($sql);
	if(is_array($rs)) {

		unset($tchrid);

		foreach($rs as $value) {
			$tchr_selopts .= "<option value=" . $value["teacherId"];
			if($value["teacherId"] == $_GET["tchrid"]) {
				$tchr_selopts .= " selected";
				$tchrid=$value["teacherId"];
				$tchrname = $value["firstName"] . " " . $value["lastName"];
			}
			$tchr_selopts .= ">" . $value["firstName"] . " " . $value["lastName"] . "</option>\n";
		}

		$printstr = str_replace("{tchr_selopts}", $tchr_selopts, $printstr);
		$printstr = str_replace("{teacherId}", $tchrid, $printstr);
		$printstr = str_replace("{teacherName}", $tchrname, $printstr);

		if(!$tchrid) {
			$printstr = preg_replace("/<!-- start form.*end form -->\n/s", "", $printstr);
		} else {
			//load the list

			$sql = "SELECT a.classId, a.courseId, a.period, c.name AS courseName, COUNT(b.studentId) AS 'count'
					FROM
						phs_reg.tbl_regtchrassigns" . $csy . " a LEFT JOIN
						phs_reg.tbl_regclasses" . $csy . " b ON a.classId = b.classId,
						phs.tbl_course c
					WHERE a.courseId=c.courseId
						AND a.teacherId=" . $tchrid . "
					GROUP BY a.classId";
			$rs = db_query($sql);

			unset($classes);
			for($i=1; $i<5; $i++) { $classes["1" . $i] = ""; $classes["2" . $i] = ""; }

			if(is_array($rs)) {
				unset($classId, $sem, $per, $courseId, $courseName);
				foreach($rs as $value) {
					$period = $value["period"];
					$classes[$period]["classId"] = $value["classId"];
					$classes[$period]["courseName"] = $value["courseName"];
					$classes[$period]["count"] = $value["count"];
					if($value["classId"] == $_GET["clsid"]) {
						$classId=$value["classId"];
						$period = $value["period"];
						$courseName = $value["courseName"];
					}
				}

				for($i=1; $i<5; $i++) {
					$printstr = str_replace("{cls1" . $i . "}", $classes["1" . $i]["courseName"], $printstr);
					$printstr = str_replace("{cls2" . $i . "}", $classes["2" . $i]["courseName"], $printstr);
					$printstr = str_replace("{clsid1" . $i . "}", $classes["1" . $i]["classId"], $printstr);
					$printstr = str_replace("{clsid2" . $i . "}", $classes["2" . $i]["classId"], $printstr);
					$printstr = str_replace("{count1" . $i . "}", $classes["1" . $i]["count"], $printstr);
					$printstr = str_replace("{count2" . $i . "}", $classes["2" . $i]["count"], $printstr);
				}

				$printstr = str_replace("{cls_selopts}", $cls_selopts, $printstr);

				$printstr = str_replace("<!-- classes\n", "", $printstr);
				$printstr = str_replace("/classes -->\n", "", $printstr);

				if(!$classId) {
					$printstr = preg_replace("/<!-- start class list.*end class list -->\n/s", "", $printstr);
				} else {

					$printstr = str_replace("{period}", $period, $printstr);
					$printstr = str_replace("{courseName}", $courseName, $printstr);

					$sql = "SELECT
								a.classId, b.studentId, c.firstName, c.lastName, c.gender AS sex, d.gradeLevel
							FROM
								phs_reg.tbl_regtchrassigns" . $csy . " a,
								phs_reg.tbl_regclasses" . $csy . " b,
								phs.tbl_student c,
								phs_reg.tbl_regenroll" . $csy . " d
							WHERE
								a.classId = b.classId AND
								b.studentId=c.studentId AND
								c.studentId=d.studentId AND
								a.classId=" . $classId . "
							ORDER BY c.firstName, c.lastName";
					$rs = db_query($sql);
					if(is_array($rs)) {

						unset($tmp, $tmp2, $tbl_rows);

						preg_match("/.*<tr id=tblrow.*/", $printstr, $matches);

						$tmp = str_replace(" id=tblrow", "", $matches[0]);

						$i = 1;
						foreach($rs as $value) {
							$tmp2 = $tmp;
							$tmp2 = str_replace("{no}", $i++, $tmp2);
							$tmp2 = str_replace("{stuid}", $value["studentId"], $tmp2);
							$tmp2 = str_replace("{stuname}", $value["firstName"] . " " . $value["lastName"], $tmp2);
							$tmp2 = str_replace("{glvl}", $value["gradeLevel"], $tmp2);
							$tbl_rows .= $tmp2;
						}
						$printstr = str_replace($matches[0], $tbl_rows, $printstr);
					} else {
						$printstr .= "<br /><span class=alert1>There are no students for this class.</span><br />\n";
					}
				}
			} else {
				$printstr .= "<br /><span class=alert1>This teacher has no class assignments.</span><br />\n";
			}
		}

	} else {
		$printstr .= "<br /><span class=alert1>List of teachers not found. Contact program developer.</span><br />\n";
	}

	$printstr = $sy_html . $tabs_html . $printstr;

} else {

	if($persid) {
		$sql = "SELECT a.classId, a.period, c.name AS courseName, COUNT(b.studentId)
				FROM phs_reg.tbl_regtchrassigns2013 a, phs_reg.tbl_regclasses2013 b, phs.tbl_course c
				WHERE a.classId = b.classId AND a.courseId = c.courseId
				GROUP BY a.classId";
		$sql = "SELECT a.classId, a.period, c.name AS courseName, COUNT(b.studentId) AS 'N'
				FROM phs.tbl_regtchrassigns2013 a, phs_reg.tbl_regclasses2013 b, phs.tbl_course c, phs.tbl_teacher d
				WHERE a.classId = b.classId AND a.courseId = c.courseId AND a.teacherId=d.teacherId
					AND d.persid_moe=$persid
				GROUP BY a.classId";
		$rs = db_query($sql);
		if(is_array($rs)) {
			$tmp_arr = array("period"=>"", "classId"=>"", "courseName"=>"", "N"=>"");
			$cls[11] = $tmp_arr;
			$cls[12] = $tmp_arr;
			$cls[13] = $tmp_arr;
			$cls[14] = $tmp_arr;
			$cls[21] = $tmp_arr;
			$cls[22] = $tmp_arr;
			$cls[23] = $tmp_arr;
			$cls[24] = $tmp_arr;
			foreach($rs as $value) {
				$cls[$value["period"]]["period"] = $value["period"];
				$cls[$value["period"]]["classId"] = $value["classId"];
				$cls[$value["period"]]["courseName"] = $value["courseName"];
				$cls[$value["period"]]["N"] = "<class=lnk1><a href='?$hrefpre&tab=$tab&thesy=$csy&classId=" . $value["classId"] . "'>" . $value["N"] . "</a></span>";
				if($_GET["classId"] == $value["classId"]) {
					$className = $value["courseName"] . " period " . $value["period"];
				}
			}
			foreach($cls as $key=>$value) {
				$value["period"] = $key;
				$data["rs"][] = $value;
			}
			$data["caption"] = "Schedule for " . $cn;
			$printstr = $sy_html . $tabs_html . "<div class=flbeg>" . basichtmltable($data) . "</div>\n<div class=flmid>{classlist}</div>\n<div class=flend></div>\n";
			if($_GET["classId"]) {
				unset($data);
				$sql = "SELECT CONCAT(c.lastName, ', ', c.firstName) AS 'studentName', b.section
						FROM phs_reg.tbl_regclasses2013 a, phs_reg.tbl_regenroll2013 b, phs.tbl_student c
						WHERE a.studentId=b.studentId AND b.studentId=c.studentId AND a.classId=" . $_GET["classId"] . "
						ORDER BY c.lastName, c.firstName";
				$rs = db_query($sql);
				if(is_array($rs)) {
					foreach($rs as $value) {
						$data["rs"][] = $value;
					}
					$data["rownums"] = "y";
					$data["caption"] = "<span style='white-space: nowrap;'>Class List for $className</span>";
					$printstr = str_replace("{classlist}", basichtmltable($data), $printstr);
				} else {
					$printstr = str_replace("{classlist}", "", $printstr);
				}
			} else {
				$printstr = str_replace("{classlist}", "", $printstr);
			}
		} else {
			$printstr = $sy_html . $tabs_html;
		}
	} else {
		$printstr = $sy_html . $tabs_html;
	}
}

?>