<?php

function get_teachers($sy = null) {
	
	if(!is_numeric($sy)) unset($sy);

	$sql = "SELECT 
				a.teacherId, a.firstName, a.middleName, a.lastName,
				a.homePhone, a.workPhone, a.role, a.persid_moe, 
				b.abbrev AS dept,
				MIN(c.year) AS minSISyr,
				MAX(c.year) AS maxSISyr,
				SUM(IF(c.semester=1, 1, 0)) AS sem1classes,
				SUM(IF(c.semester=2, 1, 0)) AS sem2classes
			FROM 
				phs.tbl_teacher a LEFT JOIN 
				phs.tbl_department b ON a.departmentId=b.departmentId, 
				phs.tbl_class c
			WHERE a.teacherId=c.teacherId 
			GROUP BY a.teacherId
			ORDER BY a.firstName, a.lastName";

	if($sy) $sql = str_replace("WHERE a.teacherId=c.teacherId", "WHERE a.teacherId=c.teacherId AND c.year=${sy}", $sql);

	$db = new mysqli("phsmysql.moe", "mysql", "mysql");
	$rs = $db->query($sql) or die("get_teachers: " . $db->error);
	while($tmp = $rs->fetch_assoc()) {
		$ret[] = $tmp;
	}
	$db->close;
	return $ret;
}

function get_years() {
	$sql = "SELECT DISTINCT(year) AS year FROM phs.tbl_class ORDER BY year DESC";
		$db = new mysqli("phsmysql.moe", "mysql", "mysql");
		$rs = $db->query($sql) or die("get_years: " . $db->error);
		while($tmp = $rs->fetch_assoc()) {
			$ret[] = $tmp["year"];
		}
		$db->close;
		return $ret;
}

function get_departments_list_text() {
	$sql = "SELECT * FROM phs.tbl_department";
		$db = new mysqli("phsmysql.moe", "mysql", "mysql");
		$rs = $db->query($sql) or die("get_years: " . $db->error);
		$ret = "";
		while($tmp = $rs->fetch_assoc()) {
			$id = $tmp["departmentId"]; $name = $tmp["name"];
			$l = strlen($id);
			$ret .= $id;
			for($i=0; $i<$l; $i++) { $ret .= "&nbsp;"; }
			 $ret .= $name . "<br />\n";
		}
		$db->close;
		return $ret;
}

function save_teacher() {
	$db = new mysqli("phsmysql.moe", "mysql", "mysql");
	
	$teacherId = $_POST["teacherId"]; unset($_POST["teacherId"]);
	
	foreach($_POST as $key=>$value) {
		if($value) {
			$sqlb .= $key . "='${value}', ";
		} else {
			$sqlb .= $key . "=NULL, ";
		}
	}
	$sqlb = trim($sqlb, ", ");
	
	if(is_numeric($teacherId)) {
		//check if the record exists
		$sql = "SELECT * FROM phs.tbl_teacher WHERE teacherId=${teacherId}";
		$rs = $db->query($sql) or die("save_teacher select: " . $db->error);
		if($rs->num_rows > 0) {
			$sql = "UPDATE phs.tbl_teacher SET ${sqlb} WHERE teacherId=${teacherId}";
		}
	}
	if($teacherId == "new") {
		$sql = "INSERT INTO phs.tbl_teacher SET ${sqlb}";
	}
	#echo $sql . "<br />\n";
	if($sql) {
		$db->query($sql) or die("save_teacher save: " . $db->error);
	}
	
	$db->close;
}

if(isset($_POST["teacherId"]) && isset($_POST["firstName"]) && isset($_POST["lastName"])) {
	#echo "<pre>"; print_r($_POST); echo "</pre>\n";
	$tmp = save_teacher();
}

$tpl = file_get_contents($template_file_fullpath);

$yrs = get_years();
$sisYrs_selOpts = "<option>all</option><option>" . implode("</option><option>", $yrs) . "</option>";

if($_POST["sisYear"]) {
	$listsy = $_POST["sisYear"];
	$sisYrs_selOpts = str_replace(">" . $listsy," selected>" . $listsy , $sisYrs_selOpts);
} else {
	unset($listsy);
}

$tpl = str_replace("{sisYrs_selOpts}", $sisYrs_selOpts , $tpl);

$rs = get_teachers($listsy);

if(is_array($rs)) {
	//records exist
	
	if($_POST["teacherId"]) {
		if(is_numeric($_POST["teacherId"])) {
			foreach($rs as $row) {
				if($row["teacherId"] == $_POST["teacherId"]) {
					$theRow = $row;
					break;
				}
			}
		}
		if($_POST["teacherId"]=="new") {
			$theRow = $rs[0];
			foreach($theRow as $key=>$value) {
				$theRow[$key] = NULL;
			}
			$theRow["teacherId"] = "new";
		}
		if(isset($theRow)) {
			$tpldata["teacherId"] = $_POST["teacherId"];
			$searchStr = "<div id=list>";
			$replaceStr = "<div id=list style=\"display: none;\">";
			$tpl = str_replace($searchStr, $replaceStr, $tpl);
			$searchStr = "<div id=form style=\"display: none;\">";
			$replaceStr = "<div id=form>";
			$tpl = str_replace($searchStr, $replaceStr, $tpl);
			foreach($theRow as $key=>$value) {
				$tpl = str_replace("{" . $key . "}", $value, $tpl);
			}
		} else {
			echo "bad teacherID received<br />\n";		
		}
		
		$tpl = str_replace("{departmentList}", get_departments_list_text(), $tpl);

	} else {
		
		$searchStr = "/\t+?<tr id=row.*?<\/tr>[\n\r]/s";
		preg_match($searchStr, $tpl, $matches);
		
		$rows_html = "";
		foreach($rs as $row) {
			$row_html = str_replace(" id=row", "", $matches[0]);
			foreach($row as $key=>$value) {
				$row_html = str_replace("{" . $key . "}", $value, $row_html);
			}
			$rows_html .= $row_html . "\n";
		}
		
		$tpl = str_replace($matches[0], $rows_html, $tpl);
	}
	
} else {
	//no records
	$html = "<p style='color: #c74;'>No quarter data found</p>\n";
}

$tpl = str_replace("{content}", $html, $tpl);
?>
