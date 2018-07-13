<?php

	if($tchrid && $clsid) {

		//save
		if($_POST["clsid"] && $_POST["thedate"]) {
			foreach($_POST["data"] as $key=>$value) {
				if($value != $_POST["orig"][$key]) {
					if($value) {
						printsql("REPLACE INTO phs.tbl_absence SET absdate='" . $_POST["thedate"] . "', classId=" . $_POST["clsid"] . ", studentId=" . $key . ", modifiedby='" . $uid . "', is_valid='Y'");
					} else {
						printsql("REPLACE INTO phs.tbl_absence SET absdate='" . $_POST["thedate"] . "', classId=" . $_POST["clsid"] . ", studentId=" . $key . ", modifiedby='" . $uid . "', is_valid='N'");
					}
					if($db->query($sql)) {
						$savemsg = "<span class=alert2>" . ++$i . " records were updated</span>\n<br />\n";
					}
				}
			}
		}

		//
		$wo=0; if(is_numeric($_GET["wo"])) $wo = $_GET["wo"];
		$wop=$wo + 1; $won= $wo - 1; if($wo <= 0) { $wo = 0; $won = 0; }
		$datebeg = date("n-j-Y", mktime(0, 0, 0, date("n"), date("j") - date("w"), date("Y")));
		list($mbeg, $dbeg, $ybeg) = explode("-", $datebeg);
		if($wo) $dbeg = $dbeg - ($wo * 7);
		$tmp_arr = array(); for($i=0; $i<7; $i++) {
			$tmp_arr[$i] = date("Y-m-d", mktime(0, 0, 0, $mbeg, $dbeg + $i, $ybeg));
			if($_GET["thedate"] == $tmp_arr[$i]) $thedate = $_GET["thedate"];
		}
		//
		$sql = "SELECT a.studentId, CONCAT(a.firstName, IF(a.middleName, CONCAT(' ', a.middleName), ''), ' ', a.lastName) AS stuname, a.gender, a.birthDate, b.grade, b.year AS sy, d.semester, d.classId, e.name AS coursename, CONCAT(f.firstName, IF(f.middleName, CONCAT(' ', f.middleName), ''), ' ', f.lastName) AS teacher, g.date AS absdate
			FROM
				(phs.tbl_student a, phs.tbl_enrollment b, phs.tbl_schedule c, phs.tbl_class d, phs.tbl_course e, phs.tbl_teacher f)
			LEFT JOIN
				phs.tbl_absence g
				ON a.studentId=b.studentId
					AND c.classId=d.classId
					AND c.scheduleId=g.scheduleId
			WHERE a.studentId=b.studentId
				AND b.enrolId=c.enrolId
				AND c.classId=d.classId
				AND d.courseId=e.courseId
				AND d.teacherId=f.teacherId
				AND b.year=$phssy
				AND d.teacherId=$tchrid
				AND d.classId=$clsid
			ORDER BY d.semester, coursename, stuname";
		$rs= rsmany($sql);
		foreach($rs as $value) {
			$tmp[$value["studentId"]]["stuname"]=$value["stuname"];
			$tmp[$value["studentId"]]["sex"]=$value["gender"];
			$tmp[$value["studentId"]]["dob"]=$value["birthDate"];
			$tmp[$value["studentId"]]["glvl"]=$value["grade"];
			if($value["absdate"]) $tmp[$value["studentId"]][$value["absdate"]]=1;
		}
		$i=0;
		foreach($tmp as $key=>$value) {
			$data["rs"][$i]["stuid"] = $key;
			$data["rs"][$i]["stuname"] = $value["stuname"];
			$data["rs"][$i]["sex"] = $value["sex"];
			$data["rs"][$i]["dob"] = $value["dob"];
			$data["rs"][$i]["glvl"] = $value["glvl"];
			foreach($tmp_arr as $fld) {
				$data["rs"][$i][$fld] = $value[$fld];
			}
			$i++;
		}
		$tbl = "<table class=ct3>\n<thead>\n<tr>\n<th>%s</th>\n<th>%s</th>\n<th>%s</th>\n<th>%s</th>\n<th>%s</th>\n";
		$tbl = sprintf($tbl, "stuid", "stuname", "sex", "dob", "glvl");
		foreach($tmp_arr as $fld) {
			if($thedate) {
				$tbl .= "<th>" . date("l", strtotime($fld)) . "<br />" . date("n/j", strtotime($fld)) . "</th>\n";
			} else {
				$tbl .= "<th><a href='?$hrefpre&tab=$tab&tchrid=$tchrid&clsid=$clsid&wo=$wo&thedate=$fld'>" . date("l", strtotime($fld)) . "<br />" . date("n/j", strtotime($fld)) . "</a></th>\n";
			}
		}
		$tbl .="</tr>\n</thead>\n<tbody>\n";
		foreach($data["rs"] as $row) {
			$tbl .= "<tr>\n";
				$tbl .="<td>" . $row["stuid"] . "</td>\n<td>" . $row["stuname"] . "</td>\n<td>" . $row["sex"] . "</td>\n<td>" . $row["dob"] . "</td>\n<td>" . $row["glvl"] . "</td>\n";
				foreach($tmp_arr as $fld) {
					$tbl .= "<td align=center>";
					if($fld == $thedate) {
						$tbl .= "<input type=hidden name=orig[" . $row["stuid"] . "] value='" . $row[$fld] . "' /><input type=text name=data[" . $row["stuid"] . "] value='" . $row[$fld] . "' size=3 />";
					} else {
						$tbl .= $row[$fld] . "&nbsp;";
					}
					$tbl.= "</td>\n";
				}
			$tbl .= "</tr>\n";
		}
		$tbl .= "</tbody>\n</table>\n";
		$printstr .= "<span class=lbl1>Class List: $tchrname - $clsname</span>\n";
		if($thedate) {
			$tbl = "<form class=tight name=frm_absences action='?$hrefpre&tab=$tab&tchrid=$tchrid&clsid=$clsid&wo=$wo' method=post>\n<input type=hidden name=clsid value=$clsid />\n<input type=hidden name=thedate value='$thedate' />\n" . $tbl . "</form>\n";
			$printstr .= "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n<span class=lnk1>[ <a href='?$hrefpre&tab=$tab&tchrid=$tchrid&clsid=$clsid&wo=$wo'>cancel</a> ][ <a href='javascript:document:frm_absences.submit()'>save</a> ]</span>\n";
		} else {
			$printstr .= "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n<span class=lnk1><a href='?$hrefpre&tab=$tab&tchrid=$tchrid&clsid=$clsid&wo=$wop'><<</a></span>\n&nbsp;\n<span class=lbl1>week of: " . date("M j, 'y", mktime(0, 0, 0, $mbeg, $dbeg, $ybeg)) . " to " . date("M j, y", mktime(0, 0, 0, $mbeg, $dbeg + 6, $ybeg)) . "</span>\n&nbsp;\n<span class=lnk1><a href='?$hrefpre&tab=$tab&tchrid=$tchrid&clsid=$clsid&wo=$won'>>></a></span>\n";
		}
		$printstr .= "<br />\n" . $tbl . "<br />\n";
	} else {
		$printstr .= "<br /><br />\n<span class=lbl1>select teacher and class to proceed.</span><br />\n";
	}

?>