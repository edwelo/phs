<?php

function get_quarters() {
	$sql = "SELECT * FROM phs.tbl_quarters ORDER BY sy";
	$db = new mysqli("phsmysql.moe", "mysql", "mysql");
	$rs = $db->query($sql) or die("get_quarters: " . $db->error);
	while($tmp = $rs->fetch_assoc()) {
		$ret[] = $tmp;
	}
	$db->close;
	return $ret;
}

function save_quarters() {
	$db = new mysqli("phsmysql.moe", "mysql", "mysql");
	
	$sy = $_POST["sy"]; unset($_POST["sy"]);
	
	foreach($_POST as $key=>$value) {
		$sqlb .= $key . "='${value}', ";
	}
	$sqlb = trim($sqlb, ", ");
	
	//check if the record exists
	$sql = "SELECT * FROM phs.tbl_quarters WHERE sy=${sy}";
	$rs = $db->query($sql) or die("save_quarters select: " . $db->error);
	if($rs->num_rows > 0) {
		$sql = "UPDATE phs.tbl_quarters SET ${sqlb} WHERE sy=${sy}";
	} else {
		$sql = "INSERT INTO phs.tbl_quarters SET sy=${sy}, ${sqlb}";
	}
	$db->query($sql) or die("save_quarters save: " . $db->error);
	
	$db->close;
}

if(isset($_POST["sy"]) && isset($_POST["s1q1s"])) {
	$tmp = save_quarters();
}

$rs = get_quarters();

$tpl = file_get_contents($template_file_fullpath);

if(is_array($rs)) {
	//records exist
	
	if(!isset($_POST["s1q1s"]) && is_numeric($_POST["sy"]) && $_POST["sy"] >= 2013 && $_POST["sy"] <= (date("Y") + 1)) {
		foreach($rs as $row) {
			if($row["sy"] == $_POST["sy"]) {
				$theRow = $row;
				break;
			}
		}
		if(!isset($theRow)) {
			$theRow = $rs[0];
			foreach($theRow as $key=>$value) {
				$theRow[$key] = NULL;
			}
		}
		$tpldata["qSY"] = $_POST["sy"];
		
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
		$data["rs"] = $rs;
		$data["tblstyle"] = "bodypanel";
		$html = basichtmltable($data);

	}
	
} else {
	//no records
	$html = "<p style='color: #c74;'>No quarter data found</p>\n";
}

$tpl = str_replace("{content}", $html, $tpl);
?>
