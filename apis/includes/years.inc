<?php
//eo 180728

$sql = "SELECT year AS phssy, 
		SUM(IF(semester=1 AND classid, 1, 0)) AS s1classes,  
		SUM(IF(semester=2 AND classid, 1, 0)) AS s2classes   
		FROM phs.tbl_class GROUP BY year";

if($_GET["a"]) {
	echo "GET_YEARS: <pre>" . str_replace("<", "&lt;", $ql) . "</pre>";
}

if($rs = $db->query($sql)) {
	if($_GET["a"]) {
		echo "<p>GET_YEARS success with " . $rs->num_rows . "</p>";
	}
	foreach($tmp = $rs->fetch_assoc()) {
		$data["years"][] = $tmp;
	}
} else {
	if($_GET["a"]) {
		echo "<p>GET_YEARS failed: <br />" . $db->error . "</p>";
	} else {
		echo "GET_YEARS_FAIL";
	}
}

?>
