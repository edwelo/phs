<?PHP

###############
## phs teachers module
## Edwel 120714
###############

//security
$authorized = ".. keizyshiro romaldaemesiochl ulaitomoichi cynthiamalsol yurikishigawa edwel";
$permitted = 0; if($uid && strpos($authorized,$uid)) { $permitted = 1; }

if(!$permitted) {
	$printstr = "<p class='alert1'>You do not have the proper authorization<br />to access student lists</p>\r";
} else {

	require_once($tpldata["functions_dir"] . "functions-db.inc");
	require_once($tpldata["functions_dir"] . "functions-db-students-phs.inc");

	$script_file_fullpath = $script_files_path . $topmenu_item_str . "-" . $leftmenu_item_str . ".inc";
	$template_file_fullpath = $template_files_path . $topmenu_item_str . "-" . $leftmenu_item_str . ".tpl";

	##################
	## initialize some variables and htmls
	##################

	unset($thesy);
	$sy_html = "<form class=tight action='' method=get>\n" . $getpre . "<input type=hidden name=tab value=" . $tab . " />\n<span class=lbl1>School Year: </span>\n<select name=thesy onChange=submit()>\n";
	for($y = $_SESSION["sy"]; $y >= 2004; $y--) {
		$sy_html .= "<option";
		if($_GET["thesy"] == $y) { $thesy = $y; $sy_html .= " selected"; }
		$sy_html .= ">" . $y . "</option>\n";
	}
	$sy_html .= "</select>\n</form>\n<br />\n";

	if(!$thesy) $thesy = $_SESSION["sy"];
	$phssy = $thesy - 1;

	$semhtml = "<form class=tight name=semselect action='' method=get>\n$getpre\n<input type=hidden name=tab value=$tab />\n<input type=hidden name=thesy value=$thesy /><span class=lbl1>semester:</span> \n<select name=sem onChange=submit()>\n<option></option>\n<option value=1>first sem</option>\n<option value=2>second sem</option>\n</select>\n</form>\n<br />\n";
	if(is_numeric($_GET["sem"])) { $semhtml = str_replace("value=" . $_GET["sem"], "value=" . $_GET["sem"] . " selected", $semhtml); $sem=$_GET["sem"]; }

	$sql = "SELECT DISTINCT(f.teacherId) AS tchrid, CONCAT(f.firstName, IF(f.middleName, CONCAT(' ', f.middleName), ''), ' ', f.lastName) AS tchrname FROM phs.tbl_teacher f, phs.tbl_class b WHERE f.teacherId=b.teacherId AND b.year=$phssy AND f.firstName != '' AND f.firstName IS NOT NULL ORDER BY tchrname";
	$rs=db_query($sql);

	if(file_exists($script_file_fullpath)) {
		require_once($script_file_fullpath);
	} else {
		$printstr = file_get_contents("under_construction.txt");
	}

}

$tpl = $printstr;

?>
