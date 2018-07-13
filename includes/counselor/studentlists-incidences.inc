<?PHP

# student status.
# eo 120330

$thesy = 2012;

$tmp = student_status_list();
foreach($tmp as $row) {
	if($row["date"] >= ($thesy - 1) . "-08-01" && $row["date"] < $thesy . "-00-01") {
		$data["rs"][] = $row;
	}
}
$printstr .= basichtmltable($data);

?>
