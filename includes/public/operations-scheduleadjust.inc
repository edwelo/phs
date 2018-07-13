<?php

if(!$permitted) {

	if($persid) {
		$sql = "SELECT a.period, a.classId, c.name AS courseName
				FROM phs_reg.tbl_regtchrassigns2013 a, phs.tbl_teacher b, phs.tbl_course c
				WHERE a.teacherId=b.teacherId AND a.courseId=c.courseId AND b.persid_moe = $persid";
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
				$cls[$value["period"]]["N"] = $value["N"];
			}
			foreach($cls as $key=>$value) {
				$value["period"] = $key;
				$data["rs"][] = $value;
			}
			$printstr = $sy_html . $tabs_html . "<span class=lbl1>Schedule for</span> " . $cn . "<br />\n" . basichtmltable($data);
		} else {
			$printstr = $sy_html . $tabs_html;
		}
	} else {
		$printstr = $sy_html . $tabs_html;
	}

} else {

	//save the data
	if($_POST["teacherId"] && $permitted) {
		#dumpvar($_POST);
		foreach($_POST["crs"] as $key=>$value) {
			#if($value) {
				unset($tmp);
				//check if record exists
				$sql = "SELECT * FROM phs_reg.tbl_regtchrassigns" . $thesy . " WHERE teacherId=" . $_POST["teacherId"] . " AND period=" . $key;
				$tmp = rsone($sql);
				//if it exists then update
				if(is_array($tmp)) {
					$sec = $_POST["sec"][$key];
					if(!$value) $sec="";
					$sql = "UPDATE phs_reg.tbl_regtchrassigns" . $thesy . " SET courseId='" . $value . "' WHERE teacherId=" . $_POST["teacherId"] . " AND period=" . $key;
					#printsql($sql);
					$tmp = $db->query($sql);
				//else insert
				} else {
					if($value) {
						$sql = "INSERT INTO phs_reg.tbl_regtchrassigns" . $thesy . " (teacherId, courseId, period) VALUES('" . $_POST["teacherId"] . "', '" . $value . "', '" . $key . "')";
						#printsql($sql);
						$tmp = $db->query($sql);
					}
				}
			#}
		}
	}

	$tpl = file_get_contents($template_file_fullpath);

	//set up tchr_selopts
	$tchr_selopts = "";
	$sql = "SELECT a.teacherId, b.firstName, b.lastName
			FROM phs_reg.tbl_regtchrassigns2013 a, phs.tbl_teacher b
			WHERE a.teacherId=b.teacherId GROUP BY a.teacherId ORDER BY b.firstName, b.lastName";
	$rs = db_query($sql);
	if(is_array($rs)) {

		unset($tchrid);

		foreach($rs as $value) {
			$tchr_selopts .= "<option value=" . $value["teacherId"];
			if($value["teacherId"] == $_GET["tchrid"]) { $tchr_selopts .= " selected"; $tchrid=$value["teacherId"]; $tchrname = $value["firstName"] . " " . $value["lastName"]; }
			$tchr_selopts .= ">" . $value["firstName"] . " " . $value["lastName"] . "</option>\n";
		}

		$printstr = str_replace("{tchr_selopts}", $tchr_selopts, $tpl);
		$printstr = str_replace("{teacherId}", $tchrid, $printstr);
		$printstr = str_replace("{teacherName}", $tchrname, $printstr);

		if(!$tchrid) {
			$printstr = preg_replace("/<!-- start form.*end form -->\n/s", "", $printstr);
		} else {
			//load the list

			unset($crs_selopts, $courses);
			$sql = "SELECT a.courseId, b.name AS courseName FROM phs_reg.tbl_regtchrassigns2013 a, phs.tbl_course b WHERE a.courseId=b.courseId GROUP BY a.courseId ORDER BY b.name";
			$rs = db_query($sql);
			foreach($rs as $value) { $crs_selopts .= "<option value=" . $value["courseId"] . ">" . $value["courseName"] . "</option>"; $courses[$value["courseId"]] = $value["courseName"]; }

			unset($sec_selopts);
			$sql = "SELECT section FROM phs_reg.tbl_regenroll2013 GROUP BY section ORDER BY section";
			$rs = db_query($sql);
			foreach($rs as $value) { $sec_selopts .= "<option>" . $value["section"] . "</option>"; }

			//load and populate the arrays with the new assignments

			$sql = "SELECT
						a.classId, a.period, a.courseId, CONCAT(IF(c.gradeLevel=9, '09', c.gradeLevel), c.section) AS section, COUNT(b.studentId) AS 'N'
					FROM
						phs_reg.tbl_regtchrassigns2013 a LEFT JOIN
						phs_reg.tbl_regclasses2013 b ON a.classId = b.classId LEFT JOIN
						phs_reg.tbl_regsections2013 c ON CONCAT(a.teacherId, '.', a.courseId, '.', a.period) = CONCAT(c.teacherid, '.', c.courseId, '.', c.period)
					WHERE a.teacherId=" . $tchrid . " GROUP BY a.period, a.courseId";
			#printsql($sql);
			$rs = db_query($sql);

			unset($sec_selopts, $tmp1, $tmp2, $assignments);

			foreach($rs as $value) {
				$period = $value["period"];
				$taid_arr[$period] = $value["classId"];
				$N_arr[$period] = $value["N"] ? $value["N"] : "";
				$crs_arr[$period] = $value["courseId"];
				$sec_arr[$period] = $value["section"];
			}

			//prepare the dynamic html

			for($i=1; $i<3; $i++) {
				for($j=1; $j<5; $j++) {
					$period = $i . $j;
					$tpl = str_replace("{crs" . $period . "_selopts}", str_replace("value=" . $crs_arr[$period] . ">", "value=" . $crs_arr[$period] . " selected>", $crs_selopts), $tpl);
					$tpl = str_replace("{sec" . $period . "_selopts}", str_replace(">" . $sec_arr[$period] . "<", " selected>" . $sec_arr[$period] . "<", $sec_selopts), $tpl);
					$tpl = str_replace("{classId" . $period . "}", $taid_arr[$period], $tpl);
					$tpl = str_replace("{sec" . $period . "}", $sec_arr[$period], $tpl);
					$tpl = str_replace("{N" . $period . "}", $N_arr[$period], $tpl);
				}
			}
		}
	} else {
		$printstr .= "<br />List of teachers not found. Contact web master.<br />]\n";
	}

	$printstr = $sy_html . $tabs_html . $printstr;

}

?>