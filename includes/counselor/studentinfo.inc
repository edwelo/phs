<?PHP

####
## Student Info.
##
## Edwel 130130
####

//load student info functions
require_once(str_replace(".inc", "-functions.inc", $script_file_fullpath));

//security
$authorized = ".. keizyshiro romaldaemesiochl ulaitomoichi cynthiamalsol yurikishigawa edwel";
$permitted = 0; if($uid && strpos($authorized, $uid)) { $permitted = 1; }

if(!$permitted) {
	$printstr = "<p class='alert1'>You do not have the proper authorization<br />to access student info</p>\r";
} else {

	//load phs student database functions
	require_once($tpldata["functions_dir"] . "functions-db-students-phs.inc");

	//school year
	if($_GET["thesy"]) { $thesy=$_GET["thesy"]; } else { $thesy=$_SESSION["sy"]; }

	//student id
	unset($stuid);
	if(is_numeric($_POST["set_student_id"])) {
		if($_POST["set_student_id"] == 0) {
			unset($_SESSION["studentId"]);
		} else {
			$_SESSION["studentId"] = $_POST["set_student_id"];
		}
	}
	if($_SESSION["studentId"]) $stuid=$_SESSION["studentId"];

	//set some variables
	if($stuid) $stubio_arr = student_biodata($stuid);

	if(is_array($stubio_arr)) {
		$printstr = file_get_contents($template_file_fullpath);

		foreach($stubio_arr as $key=>$value) { $printstr = str_replace("{" . $key . "}", $value, $printstr); }

		$script_file_fullpath = str_replace(".inc", "-${leftmenu_item_str}.inc", $script_file_fullpath);
		$template_file_fullpath = str_replace(".tpl", "-${leftmenu_item_str}.tpl", $template_file_fullpath);

		if(file_exists($script_file_fullpath)) {
			require_once($script_file_fullpath);
		} else {
			$printstr = file_get_contents("under_construction.txt");
		}
	} else {
		//student search module
		$printstr = file_get_contents($tpldata["templates_dir"] . $scripts_dir . "studentinfo-findstudent.tpl");

		/*//build class lists
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
		*/

		if($_GET["sp"]) {
			$printstr = str_replace("{sp}", $_GET["sp"], $printstr);
			$data = find_student($_GET["sp"]);

			unset($tbl_row, $tbl_rows);
			preg_match("/\t*<tr id=row.*?\/tr>/s", $printstr, $matches);
			$i=0;
			foreach($data as $value) {
				$tbl_row = str_replace("{no}", ++$i, $matches[0]);
				$tbl_row = str_replace("{studentName}", $value["stuname"], $tbl_row);
				$tbl_row = str_replace("{gender}", $value["gender"], $tbl_row);
				$tbl_row = str_replace("{year}", $value["year"], $tbl_row);
				$tbl_row = str_replace("{gradeLevel}", $value["glvl"], $tbl_row);
				$tbl_row = str_replace("{studentId}", $value["stuid"], $tbl_row);
				$tbl_rows .= $tbl_row;
			}
			$printstr = str_replace($matches[0], $tbl_rows, $printstr);
		} else {
			$printstr = str_replace("{sp}", "", $printstr);
			$printstr = preg_replace("/<!-- found list.*\/found list -->/s", "", $printstr);
		}
	}

}

$tpl = $printstr;

?>