<?php

function student_age($dob=NULL, $calcDate=NULL) {
	if($calcDate != date("Y-m-d", strtotime($dob))) { $calcDate = date("Y-m-d"); }
	if($dob == date("Y-m-d", strtotime($dob))) {
		if($dob <= $calcDate) {
			$y = substr($dob, 0, 4);
			$md = substr($dob, 5, 5);
			$ny = date("Y");
			$nmd = date("m-d");
			$age = $ny - $y;
			if($nmd < $md) $age--;
		} else {
			$age = "";
		}
	} else {
		$age = "";
	}
	return $age;
}

function student_biodata($stuid=NULL) {
	$tmp = get_record("phs.tbl_student", "studentId", $stuid);
	if(is_array($tmp)) {
		$stubio_arr["studentId"] = $stuid;
		$stubio_arr["studentName"] = str_replace("  ", " ", $tmp["firstName"] . " " . $tmp["middleName"] . " " . $tmp["lastName"]);
		$stubio_arr["gender"] = $tmp["gender"];

		$stubio_arr["picName"] = strtolower(trim($tmp["firstName"]) . trim($tmp["lastName"]));

		$stubio_arr["currentAge"] = student_age($tmp["birthDate"]);

		$stubio_arr["residence"] = $tmp["placeResidence"];
		$stubio_arr["responsibleAdult"] = $tmp["responsibleAdult"];
		$stubio_arr["phone"] = $tmp["phone"];

		$sql = "SELECT * FROM phs.tbl_enrollment WHERE studentId=$stuid ORDER BY year DESC LIMIT 1";
		$tmp_arr = db_query($sql);

		$glvl = $tmp_arr[0]["grade"];
		$glvlyear = $tmp_arr[0]["year"];

		$stubio_arr["gradeLevel"] = $glvl;
		if($glvl == 12 && $glvlyear < $csy) $stubio_arr["gradeLevel"] .= " (" . $glvlyear . ")";

		$stubio_arr["completionStatus"] = "-";
		$stubio_arr["entryDate"] = 17;
		$stubio_arr["entryLevel"] = "Freshmman";
		$stubio_arr["entryAge"] = 15;

		//these fields are not in the database?
		if(!$stubio_arr["suffix"]) $stubio_arr["suffix"] = "";
		if(!$stubio_arr["counselor"]) $stubio_arr["counselor"] = "";
		if(!$stubio_arr["advisor"]) $stubio_arr["advisor"] = "";

		return $stubio_arr;
	} else {
		return "";
	}
}

function student_academic_status($courses=array()) {

}

?>