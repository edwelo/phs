<?PHP

####
## Student Info.
##
## Edwel 130130
####

//security
$authorized = ".. keizyshiro romaldaemesiochl ulaitomoichi cynthiamalsol yurikishigawa edwel";
$permitted = 0; if($uid && strpos($authorized, $uid)) { $permitted = 1; }

if(!$permitted) {
	$printstr .= "<p class='alert1'>You do not have the proper authorization<br />to access student info</p>\r";
} else {

	//load phs student database functions
	require_once($tpldata["functions_dir"] . "functions-db-students-phs.inc");

	//student id
	if($_GET["thesy"]) { $thesy=$_GET["thesy"]; } else { $thesy=$_SESSION["sy"]; }

	//set some variables
	if(is_numeric($_GET["stuid"])) {

		$stuid=$_GET["stuid"];

		$stubio_arr = get_record("phs.tbl_student", "studentId", $stuid);
	}

	if(is_array($stubio_arr)) {
		$stubio_arr["studentName"] = $stubio_arr["firstName"];
		if($stubio_arr["middleName"]) $stubio_arr["studentName"] .= " " . $stubio_arr["middleName"];
		$stubio_arr["studentName"] .= " " . $stubio_arr["lastName"];
		$stubio_arr["picName"] = strtolower(trim($stubio_arr["firstName"]) . trim($stubio_arr["lastName"]));

		//these fields are not in the database?
		if(!$stubio_arr["suffix"]) $stubio_arr["suffix"] = "";
		if(!$stubio_arr["counselor"]) $stubio_arr["counselor"] = "";
		if(!$stubio_arr["advisor"]) $stubio_arr["advisor"] = "";

		$tpl = file_get_contents($tpldata["templates_dir"] . "phscouns/stuinfo1.tpl");

		foreach($stubio_arr as $key=>$value) { $tpl = str_replace("{" . $key . "}", $value, $tpl); }

		$subscript_name = str_replace("/", "", str_replace(" ", "", strtolower($tabs[$tab])));

		$subscript_file_fullpath = $script_file_fullpath . "-" . $subscript_name . ".inc";

		if(file_exists($subscript_file_fullpath)) {
			$subtemplate_file = $tpldata["templates_dir"] . $subscripts_dir . $script_name . ".inc" . "-" . $subscript_name . ".tpl";
			require_once($subscript_file_fullpath);
		} else {
			$printstr .= "<br />\n<br />\n<br />\n<span style='font-size: large; color: red; font-weight: bold;'>Module Under Construction</span><br />\n";
		}

	} else {
		$printstr .= "<span style='color: #778fbd; font-size: large;'>Select a student</span>\n";

		$printstr .= "<br /><br />\n";

		$printstr .= "<form class=tight action='' method=get>\n$getpre\n<input type=hidden name=t3 value=$leftmenu_item />\n<span class=lbl1>Enter Student ID: <input type=text name=stuid size=6 />&nbsp;&nbsp;<input type=submit value=go />\n</form><br />\r";

		$printstr .= "<br />\n";
		$printstr .= "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;or<br />\n";
		$printstr .= "<br />\n";

		$printstr .= "<form class=tight action='' method=get>\n$getpre\n<input type=hidden name=t3 value='" . $tpldata["leftmenu_item"] . "' />\n<span class=lbl1>find student (enter search phrase): <input type=text name=sp value='" . $_GET["sp"] . "' size=20 />&nbsp;&nbsp;<input type=submit value=go />\n</form><br />\r";

		if($_GET["sp"]) {
			$data["idlink"]="?$hrefpre&t3=" . $tpldata["leftmenu_item"] . "&stuid=";
			$data["rs"]=find_student($_GET["sp"]);
			$printstr .= basichtmltable($data);
		}
	}

}

$tpl = $printstr;

?>