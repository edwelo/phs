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

	unset($stuid);

	if($_GET["stuid"] == "0") {
		unset($_GET["stuid"], $_SESSION["stuid"]);
	}

	if($_SESSION["stuid"]) {
		$stuid = $_SESSION["stuid"];
	} else {
		if($_GET["stuid"] && is_numeric($_GET["stuid"])) {
			$_SESSION["stuid"] = $_GET["stuid"];
			$stuid = $_GET["stuid"];
		}
	}

	//set some variables
	if($stuid) {
		$stubio_arr = get_record("phs.tbl_student", "studentId", $stuid);
	}

	if(is_array($stubio_arr)) {
		$stubio_arr["studentName"] = $stubio_arr["firstName"];
		if($stubio_arr["middleName"]) $stubio_arr["studentName"] .= " " . $stubio_arr["middleName"];
		$stubio_arr["studentName"] .= " " . $stubio_arr["lastName"];
		$stubio_arr["picName"] = strtolower(trim($stubio_arr["firstName"]) . trim($stubio_arr["lastName"]));

		#$stubio_arr["currentAge"] = calculate_age_years($stubio_arr["birthDate"]);

		$sql = "SELECT * FROM phs.tbl_enrollment WHERE studentId=$stuid ORDER BY year DESC LIMIT 1";
		$tmp_arr = db_query($sql); $glvl = $tmp_arr[0]["grade"]; $glvlyear = $tmp_arr[0]["year"];
		$stubio_arr["currentLevel"] = $gradeLevelName[$glvl];
		if($glvl == 12 && $glvlyear < $csy) $stubio_arr["currentLevel"] .= " (" . $tmp_arr[0]["year"] . ")";

		$stubio_arr["completionStatus"] = "-";
		$stubio_arr["entryDate"] = 17;
		$stubio_arr["entryLevel"] = "Freshmman";;
		$stubio_arr["entryAge"] = 15;

		//these fields are not in the database?
		if(!$stubio_arr["suffix"]) $stubio_arr["suffix"] = "";
		if(!$stubio_arr["counselor"]) $stubio_arr["counselor"] = "";
		if(!$stubio_arr["advisor"]) $stubio_arr["advisor"] = "";

		$printstr = file_get_contents($tpldata["templates_dir"] . "phscouns/studentinfo.tpl");

		foreach($stubio_arr as $key=>$value) { $printstr = str_replace("{" . $key . "}", $value, $printstr); }

		$script_file_fullpath = $script_files_path . $topmenu_item_str . "-" . $leftmenu_item_str . ".inc";
		$template_file_fullpath = $template_files_path . $topmenu_item_str . "-" . $leftmenu_item_str . ".tpl";

		#echo $leftmenu_item_str . "<br />\n";
		#echo $script_file_fullpath . "<br />\n";

		if(file_exists($script_file_fullpath)) {
			require_once($script_file_fullpath);
		} else {
			$printstr = file_get_contents("under_construction.txt");
		}

	} else {
		//student search module

		$printstr .= file_get_contents($tpldata["templates_dir"] . $scripts_dir . "studentinfo-findstudent.tpl");

		//build class lists
		$sql = "SELECT * FROM phs.tbl_student a, phs.tbl_enrollment b WHERE a.studentId=b.studentId AND year=" . ($csy - 1) . " AND grade>8 AND grade<13";
		unset($tmp_arr, $tmp2_arr, $lists_arr);
		$tmp_arr = db_query($sql);
		foreach($tmp_arr as $value) {
			$tmp2_arr[$value["firstName"] . $value["lastName"] . $value["studentId"]] = $value;
		}
		ksort($tmp2_arr);
		foreach($tmp2_arr as $value) {
			$lists_arr[$value["grade"]] .= trim($value["firstName"] . " " . $value["middleName"] . " " . $value["lastName"] . " " . $value["suffix"]) . "<br />\n";
		}
		$printstr = str_replace("{freshmen_list}", $lists_arr[9], $printstr);
		$printstr = str_replace("{sophomores_list}", $lists_arr[10], $printstr);
		$printstr = str_replace("{juniors_list}", $lists_arr[11], $printstr);
		$printstr = str_replace("{seniors_list}", $lists_arr[12], $printstr);

		if($_GET["sp"]) {
			$printstr = str_replace("{sp}", $_GET["sp"], $printstr);
			$data["idlink"]="?$hrefpre&tab=$tab&stuid=";
			$data["rs"]=find_student($_GET["sp"]);
			$printstr = str_replace("<!-- stu_list -->", basichtmltable($data), $printstr);
		} else {
			$printstr = str_replace("{sp}", "", $printstr);
		}
	}

}

$tpl = $printstr;

?>