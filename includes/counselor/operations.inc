<?PHP

####
## Operations.
##
## Edwel 120920
####

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

	#echo $leftmenu_item_str . "<br />\n";
	#echo $script_file_fullpath . "<br />\n";

	if(file_exists($script_file_fullpath)) {

		#note: $phssy needs to be defined earlier in a more appropriate section
		#      that can handle switching from one phssy to another
		#      the below is only used for development and testing
		if(!$phssy) $phssy = date("Y") - 2;

		require_once($script_file_fullpath);
	} else {
		$printstr = file_get_contents("under_construction.txt");
	}
}

$tpl = $printstr;

?>
