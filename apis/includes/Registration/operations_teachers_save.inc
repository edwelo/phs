<?php
//rq save, called by backend.php
//eo 180717

//echo "<p>Save start ...</p>";

$rqId = $tmp;

if($_GET["a"]) {
	$json = '{"tchrAssigns_2018":[{"deptAbbrv":"","teacherId":"311","teacherName":"Hsueh, W","semPer":"14","courseId":"245","courseNameShort":"Mand"},{"deptAbbrv":"CTE-All","teacherId":"302","teacherName":"Ngirengkoi, A","semPer":"13","courseId":"11","courseNameShort":"CD"},{"deptAbbrv":"CTE-AT","teacherId":"218","teacherName":"Chen, T","semPer":"24","courseId":"245","courseNameShort":"Mand"},{"deptAbbrv":"CTE-AT","teacherId":"313","teacherName":"Rechelluul, S","semPer":"11","courseId":"29","courseNameShort":"Auto"},{"deptAbbrv":"CTE-AT","teacherId":"313","teacherName":"Rechelluul, S","semPer":"12","courseId":"31","courseNameShort":"Auto"},{"deptAbbrv":"CTE-AT","teacherId":"153","teacherName":"Takeo, R","semPer":"11","courseId":"11","courseNameShort":"CD"},{"deptAbbrv":"CTE-AT","teacherId":"153","teacherName":"Takeo, R","semPer":"21","courseId":"32","courseNameShort":"Auto"},{"deptAbbrv":"CTE-AT","teacherId":"153","teacherName":"Takeo, R","semPer":"22","courseId":"30","courseNameShort":"Auto"},{"deptAbbrv":"CTE-BU","teacherId":"136","teacherName":"Leonardia, C","semPer":"13","courseId":"46","courseNameShort":"Comp"},{"deptAbbrv":"CTE-BU","teacherId":"136","teacherName":"Leonardia, C","semPer":"21","courseId":"33","courseNameShort":"Comp"},{"deptAbbrv":"CTE-BU","teacherId":"324","teacherName":"Ringang, G","semPer":"22","courseId":"36","courseNameShort":"Bkkpng"},{"deptAbbrv":"CTE-BU","teacherId":"242","teacherName":"Vicente, J","semPer":"11","courseId":"34","courseNameShort":"Intro"},{"deptAbbrv":"CTE-BU","teacherId":"242","teacherName":"Vicente, J","semPer":"13","courseId":"57","courseNameShort":"Keybrdng"},{"deptAbbrv":"CTE-BU","teacherId":"242","teacherName":"Vicente, J","semPer":"14","courseId":"49","courseNameShort":"Gen"},{"deptAbbrv":"CTE-CT","teacherId":"163","teacherName":"Hideos, P","semPer":"11","courseId":"27","courseNameShort":"Cnst"},{"deptAbbrv":"CTE-CT","teacherId":"163","teacherName":"Hideos, P","semPer":"12","courseId":"25","courseNameShort":"Cnst"},{"deptAbbrv":"CTE-CT","teacherId":"163","teacherName":"Hideos, P","semPer":"21","courseId":"26","courseNameShort":"Cnst"},{"deptAbbrv":"CTE-CT","teacherId":"163","teacherName":"Hideos, P","semPer":"22","courseId":"28","courseNameShort":"Cnst"},{"deptAbbrv":"CTE-HHS","teacherId":"254","teacherName":"Orrukem, M","semPer":"12","courseId":"37","courseNameShort":"Htl"},{"deptAbbrv":"CTE-HHS","teacherId":"254","teacherName":"Orrukem, M","semPer":"13","courseId":"50","courseNameShort":"Eng"},{"deptAbbrv":"CTE-HHS","teacherId":"254","teacherName":"Orrukem, M","semPer":"22","courseId":"39","courseNameShort":"TourG"},{"deptAbbrv":"CTE-HHS","teacherId":"165","teacherName":"Skiwo, R","semPer":"11","courseId":"38","courseNameShort":"Htl"},{"deptAbbrv":"CTE-HHS","teacherId":"165","teacherName":"Skiwo, R","semPer":"12","courseId":"11","courseNameShort":"CD"},{"deptAbbrv":"CTE-HHS","teacherId":"165","teacherName":"Skiwo, R","semPer":"21","courseId":"40","courseNameShort":"TourG"},{"deptAbbrv":"CTE-HHS","teacherId":"165","teacherName":"Skiwo, R","semPer":"22","courseId":"7","courseNameShort":"W"},{"deptAbbrv":"CTE-NR","teacherId":"130","teacherName":"Ngiraikelau, W","semPer":"12","courseId":"2","courseNameShort":"CD"},{"deptAbbrv":"CTE-NR","teacherId":"150","teacherName":"Thomas, V","semPer":"11","courseId":"23","courseNameShort":"Ag"},{"deptAbbrv":"CTE-NR","teacherId":"150","teacherName":"Thomas, V","semPer":"12","courseId":"21","courseNameShort":"Ag"},{"deptAbbrv":"CTE-NR","teacherId":"150","teacherName":"Thomas, V","semPer":"21","courseId":"22","courseNameShort":"Ag"},{"deptAbbrv":"CTE-NR","teacherId":"150","teacherName":"Thomas, V","semPer":"22","courseId":"24","courseNameShort":"Ag"},{"deptAbbrv":"ENG","teacherId":"107","teacherName":"Blesoch, A","semPer":"11","courseId":"80","courseNameShort":"Eng"},{"deptAbbrv":"ENG","teacherId":"285","teacherName":"Castro, J","semPer":"11","courseId":"41","courseNameShort":"Eng"},{"deptAbbrv":"ENG","teacherId":"285","teacherName":"Castro, J","semPer":"21","courseId":"12","courseNameShort":"Eng"},{"deptAbbrv":"ENG","teacherId":"262","teacherName":"Kloulechad, I","semPer":"11","courseId":"50","courseNameShort":"Eng"},{"deptAbbrv":"ENG","teacherId":"262","teacherName":"Kloulechad, I","semPer":"12","courseId":"237","courseNameShort":"Comm"},{"deptAbbrv":"ENG","teacherId":"268","teacherName":"Ngirakesau, H","semPer":"11","courseId":"12","courseNameShort":"Eng"},{"deptAbbrv":"ENG","teacherId":"268","teacherName":"Ngirakesau, H","semPer":"22","courseId":"3","courseNameShort":"Eng"},{"deptAbbrv":"ENG","teacherId":"210","teacherName":"Ngirengkoi, L","semPer":"11","courseId":"235","courseNameShort":"Comm"},{"deptAbbrv":"ENG","teacherId":"210","teacherName":"Ngirengkoi, L","semPer":"12","courseId":"50","courseNameShort":"Eng"},{"deptAbbrv":"ENG","teacherId":"210","teacherName":"Ngirengkoi, L","semPer":"21","courseId":"231","courseNameShort":"ColPrep"},{"deptAbbrv":"ENG","teacherId":"210","teacherName":"Ngirengkoi, L","semPer":"23","courseId":"41","courseNameShort":"Eng"},{"deptAbbrv":"ENG","teacherId":"298","teacherName":"Salvador, A","semPer":"12","courseId":"3","courseNameShort":"Eng"},{"deptAbbrv":"ENG","teacherId":"298","teacherName":"Salvador, A","semPer":"14","courseId":"80","courseNameShort":"Eng"},{"deptAbbrv":"ENG","teacherId":"237","teacherName":"Sungino, L","semPer":"13","courseId":"80","courseNameShort":"Eng"},{"deptAbbrv":"ENG","teacherId":"237","teacherName":"Sungino, L","semPer":"14","courseId":"3","courseNameShort":"Eng"},{"deptAbbrv":"ENG","teacherId":"237","teacherName":"Sungino, L","semPer":"21","courseId":"41","courseNameShort":"Eng"},{"deptAbbrv":"HLTH","teacherId":"278","teacherName":"Cabunagan, B","semPer":"11","courseId":"5","courseNameShort":"Health"},{"deptAbbrv":"HLTH","teacherId":"278","teacherName":"Cabunagan, B","semPer":"21","courseId":"240","courseNameShort":"ComHlth"},{"deptAbbrv":"HLTH","teacherId":"270","teacherName":"Reyes, J","semPer":"11","courseId":"228","courseNameShort":"An"},{"deptAbbrv":"HLTH","teacherId":"270","teacherName":"Reyes, J","semPer":"12","courseId":"5","courseNameShort":"Health"},{"deptAbbrv":"HLTH","teacherId":"270","teacherName":"Reyes, J","semPer":"14","courseId":"11","courseNameShort":"CD"},{"deptAbbrv":"JAP","teacherId":"166","teacherName":"Andrew, S","semPer":"11","courseId":"2","courseNameShort":"CD"},{"deptAbbrv":"JAP","teacherId":"220","teacherName":"Nogami, Y","semPer":"12","courseId":"52","courseNameShort":"Jap"},{"deptAbbrv":"JAP","teacherId":"220","teacherName":"Nogami, Y","semPer":"13","courseId":"48","courseNameShort":"Jap"},{"deptAbbrv":"MATH","teacherId":"208","teacherName":"Bautista, A","semPer":"11","courseId":"35","courseNameShort":"Bus"},{"deptAbbrv":"MATH","teacherId":"208","teacherName":"Bautista, A","semPer":"14","courseId":"43","courseNameShort":"Geom"},{"deptAbbrv":"MATH","teacherId":"126","teacherName":"Baysa, E","semPer":"11","courseId":"1","courseNameShort":"Alg"},{"deptAbbrv":"MATH","teacherId":"126","teacherName":"Baysa, E","semPer":"21","courseId":"10","courseNameShort":"Alg"},{"deptAbbrv":"MATH","teacherId":"247","teacherName":"Britanico, E","semPer":"11","courseId":"43","courseNameShort":"Geom"},{"deptAbbrv":"MATH","teacherId":"121","teacherName":"Dancel, M","semPer":"11","courseId":"1","courseNameShort":"Alg"},{"deptAbbrv":"MATH","teacherId":"121","teacherName":"Dancel, M","semPer":"23","courseId":"10","courseNameShort":"Alg"},{"deptAbbrv":"MATH","teacherId":"127","teacherName":"Fidel, N","semPer":"11","courseId":"54","courseNameShort":"Trig"},{"deptAbbrv":"MATH","teacherId":"226","teacherName":"Ludovico, J","semPer":"11","courseId":"82","courseNameShort":"App"},{"deptAbbrv":"MATH","teacherId":"226","teacherName":"Ludovico, J","semPer":"22","courseId":"238","courseNameShort":"Mth"},{"deptAbbrv":"MATH","teacherId":"301","teacherName":"Melairei, B","semPer":"11","courseId":"82","courseNameShort":"App"},{"deptAbbrv":"MATH","teacherId":"275","teacherName":"San Juan, J","semPer":"13","courseId":"10","courseNameShort":"Alg"},{"deptAbbrv":"MATH","teacherId":"275","teacherName":"San Juan, J","semPer":"14","courseId":"1","courseNameShort":"Alg"},{"deptAbbrv":"PAL","teacherId":"178","teacherName":"Gabriel, S","semPer":"11","courseId":"16","courseNameShort":"Pal"},{"deptAbbrv":"PAL","teacherId":"174","teacherName":"Ngirakesau, L","semPer":"11","courseId":"16","courseNameShort":"Pal"},{"deptAbbrv":"PAL","teacherId":"316","teacherName":"Omelau, V","semPer":"11","courseId":"6","courseNameShort":"Pal"},{"deptAbbrv":"PAL","teacherId":"280","teacherName":"Timarong, A","semPer":"12","courseId":"6","courseNameShort":"Pal"},{"deptAbbrv":"PE","teacherId":"167","teacherName":"Delong, S","semPer":"12","courseId":"246","courseNameShort":"PE"},{"deptAbbrv":"PE","teacherId":"310","teacherName":"Rumong, R","semPer":"14","courseId":"248","courseNameShort":"PE"},{"deptAbbrv":"PE","teacherId":"310","teacherName":"Rumong, R","semPer":"24","courseId":"247","courseNameShort":"PE"},{"deptAbbrv":"PE","teacherId":"169","teacherName":"Skiwo, F","semPer":"12","courseId":"247","courseNameShort":"PE"},{"deptAbbrv":"PE","teacherId":"309","teacherName":"Tmarsel, D","semPer":"14","courseId":"249","courseNameShort":"PE"},{"deptAbbrv":"SCI","teacherId":"251","teacherName":"Aquino, C","semPer":"11","courseId":"3","courseNameShort":"Eng"},{"deptAbbrv":"SCI","teacherId":"279","teacherName":"Britanico, M","semPer":"12","courseId":"42","courseNameShort":"Chem"},{"deptAbbrv":"SCI","teacherId":"296","teacherName":"Miclat, D","semPer":"11","courseId":"4","courseNameShort":"Gen"},{"deptAbbrv":"SCI","teacherId":"296","teacherName":"Miclat, D","semPer":"13","courseId":"53","courseNameShort":"Physics"},{"deptAbbrv":"SCI","teacherId":"274","teacherName":"Paulino, W","semPer":"11","courseId":"13","courseNameShort":"Bio"},{"deptAbbrv":"SCI","teacherId":"137","teacherName":"Pulgueras, L","semPer":"11","courseId":"42","courseNameShort":"Chem"},{"deptAbbrv":"SCI","teacherId":"137","teacherName":"Pulgueras, L","semPer":"14","courseId":"13","courseNameShort":"Bio"},{"deptAbbrv":"SCI","teacherId":"307","teacherName":"Remeliik, K","semPer":"12","courseId":"4","courseNameShort":"Gen"},{"deptAbbrv":"SCI","teacherId":"138","teacherName":"Reyes, N","semPer":"11","courseId":"53","courseNameShort":"Physics"},{"deptAbbrv":"SCI","teacherId":"306","teacherName":"Sasao, K","semPer":"12","courseId":"13","courseNameShort":"Bio"},{"deptAbbrv":"SCI","teacherId":"306","teacherName":"Sasao, K","semPer":"14","courseId":"4","courseNameShort":"Gen"},{"deptAbbrv":"SCI","teacherId":"306","teacherName":"Sasao, K","semPer":"21","courseId":"5","courseNameShort":"Health"},{"deptAbbrv":"SOC","teacherId":"308","teacherName":"Katosang, E","semPer":"11","courseId":"15","courseNameShort":"W"},{"deptAbbrv":"SOC","teacherId":"143","teacherName":"Ngiratrang, E","semPer":"11","courseId":"44","courseNameShort":"Pal"},{"deptAbbrv":"SOC","teacherId":"143","teacherName":"Ngiratrang, E","semPer":"14","courseId":"55","courseNameShort":"Comp"},{"deptAbbrv":"SOC","teacherId":"198","teacherName":"Ngiruos, R","semPer":"12","courseId":"7","courseNameShort":"W"},{"deptAbbrv":"SOC","teacherId":"145","teacherName":"Pedro, J","semPer":"12","courseId":"230","courseNameShort":"Intro"},{"deptAbbrv":"SOC","teacherId":"145","teacherName":"Pedro, J","semPer":"13","courseId":"47","courseNameShort":"US"},{"deptAbbrv":"SOC","teacherId":"145","teacherName":"Pedro, J","semPer":"21","courseId":"239","courseNameShort":"ComIss"},{"deptAbbrv":"SOC","teacherId":"147","teacherName":"Rdechor, M","semPer":"11","courseId":"15","courseNameShort":"W"},{"deptAbbrv":"SOC","teacherId":"147","teacherName":"Rdechor, M","semPer":"12","courseId":"44","courseNameShort":"Pal"},{"deptAbbrv":"SOC","teacherId":"147","teacherName":"Rdechor, M","semPer":"14","courseId":"47","courseNameShort":"US"},{"deptAbbrv":"SOC","teacherId":"282","teacherName":"Shiro, L","semPer":"11","courseId":"7","courseNameShort":"W"},{"deptAbbrv":"SPED","teacherId":"294","teacherName":"Imperial, M","semPer":"11","courseId":"244","courseNameShort":"IEP"},{"deptAbbrv":"SPED","teacherId":"264","teacherName":"Ngirchokebai, K","semPer":"11","courseId":"244","courseNameShort":"IEP"},{"deptAbbrv":"SPED","teacherId":"243","teacherName":"Rivera, R","semPer":"11","courseId":"244","courseNameShort":"IEP"},{"deptAbbrv":"SPED","teacherId":"322","teacherName":"Subris, E","semPer":"11","courseId":"244","courseNameShort":"IEP"}]}';
	$rcvArr = json_decode($json);
	$json = "JSON - GET: " . $json;
} else {
	if(isset($_POST)) {
		$json = file_get_contents('php://input');
		$rcvArr = json_decode($json);
		$json = "JSON FROM POST:<br />" . $json;
		#echo "post_got_this_" . json_encode($save_arr);
		#echo "<pre>"; print_r($save_arr); echo "</pre>"; exit;
	} else {
		echo "POST_NOT_RECEIVED!";
		exit;
	}
}

if($_GET["a"]) {
	$mainKey = key((array)$rcvArr);
	list($dataDesc, $sy) = explode("_", $mainKey);
	$teacherList = $rcvArr->$mainKey;
	echo "<p>JSON and Array from JSON:</p>";
	echo "<p style='x-small;'>Main Key: $mainKey , Desc: $dataDesc , SY: $sy</p>";
//	echo "<p style='x-small;'>" . $json . "</p>";
	echo "<pre>"; print_r($teacherList); echo "</pre>";
}

exit;

if(!isset($rcvArr)) $rcvArr = new stdClass();

$items = $rcvArr->items;

$rcvId = $items->recevingId;

//remove the following fields from \$rcvArr
$tmp = array("items", "receivingId");
foreach($tmp as $key) { unset($rqArr->$key); }

//tables

//base sqls
$rcvInsertSQL = "INSERT INTO ${rcvTable} SET %s";
$rcvUpdateSQL = "UPDATE ${rcvTable} SET %s WHERE receivingId = %s";
$itemInsertSQL = "INSERT INTO ${rcvItemsTable} SET %s";
$itemUpdateSQL = "UPDATE ${rcvItemsTable} SET %s WHERE receivingItemId = %s";
$itemVoidSQL = "UPDATE ${rcvItemsTable} SET isValid = 'x" . date("ymdHi") . "' WHERE receivingItemId = %s";

//rq

#####
# Set up the rcving sql
#####

$fields[] = array("receivingId", "int", 4, "NOT NULL", "AUTO_INCREMENT");
$fields[] = array("requisitionId", "int", 4, "DEFAULT NULL", "");
$fields[] = array("initiatingOffice", "varchar", 30, "DEFAULT NULL", "");
$fields[] = array("requestedBy", "varchar", 30, "DEFAULT NULL", "");
$fields[] = array("requestedDate", "date", "", "DEFAULT NULL", "");
$fields[] = array("preparedById", "int", 5, "DEFAULT NULL", "");
$fields[] = array("preparedByName", "varchar", 30, "DEFAULT NULL", "");
$fields[] = array("preparedDate", "date", "", "DEFAULT NULL", "");
$fields[] = array("justification", "varchar", 255, "DEFAULT NULL", "");
$fields[] = array("numItems", "int", 4, "DEFAULT NULL", "");
$fields[] = array("authNo", "varchar", 12, "DEFAULT NULL", "");
$fields[] = array("authDate", "date", "", "DEFAULT NULL", "");
$fields[] = array("authAmount", "decimal", 10, "DEFAULT NULL", "");
$fields[] = array("rcvDate", "date", "", "DEFAULT NULL", "");
$fields[] = array("rcvBy", "varchar", 30, "DEFAULT NULL", "");
$fields[] = array("invoiceNo", "varchar", 12, "DEFAULT NULL", "");
$fields[] = array("invoiceAmount", "decimal", 10, "DEFAULT NULL", "");
$fields[] = array("invoiceDate", "date", "", "DEFAULT NULL", "");
$fields[] = array("status", "varchar", 30, "DEFAULT NULL", "");
$fields[] = array("statusDate", "date", "", "DEFAULT NULL", "");
$fields[] = array("remarks", "varchar", 255, "DEFAULT ''", "");
$fields[] = array("isValid", "varchar", 20, "NOT NULL", "");

$l = count($fields) - 1;

$sqlData = "";

for($i=1; $i<$l; $i++) {
	$fieldName=$fields[$i][0]; $fieldType=$fields[$i][1]; $fieldLength = $fields[$i][2];
	if($rcvArr->$fieldName) {
		//echo "<p>" . $fieldName . ": " . $rcvArr->$fieldName . "</p>";
		$value = $rcvArr->$fieldName;
		if($fieldType == "varchar") {
			$value = "\"" . substr(mysqli_real_escape_string($db, $value), 0, $fieldLength) . "\"";
		}
		if($fieldType == "int" || $fieldType == "decimal") {
			if(!is_numeric($value)) $value = "NULL";
			if(strlen($value) > $fieldLength) $value = "NULL";
		}
		if($fieldType == "date") {
			$value = date("Y-m-d", strtotime($value));
			$minValue = "2009-10-01"; $maxValue = date("Y-m-d");
			if($value < $minValue || $value > $maxValue) {
				$value = "NULL";
			} else {
				$value = "\"" . $value . "\"";
			}
		}
		$sqlData .= " " . $fieldName . "=" . $value . ",";
	}
}
$sqlData = trim($sqlData, ",");

if(is_numeric($rcvId)) {
	$sql = sprintf($rcvUpdateSQL, $sqlData, $rcvId);
} else {
	$sql = sprintf($rcvInsertSQL, $sqlData);
}

$sqlHTML .= "<p style='font-size: small;'>" . str_replace("<", "&lt;", $sql) . ";</p>";

$db->query($sql) or die("Rcv_Save_Error: " . $db->error . "<br />\n<code>${sql}</code>\n");
if(!$rcvId || $rcvId == "new") {
	$rcvId = $db->insert_id;
	$newSaved = $rcvId;
}

#####
# Set up the rcving items sql
#####

unset($fields);

$fields[] = array("receivingItemId", "int", "5");
$fields[] = array("receivingId", "int", "4");
$fields[] = array("requisitionId", "int", "5");
$fields[] = array("requisitionItemId", "int", "5");
$fields[] = array("org", "varchar", "4");
$fields[] = array("costCenter", "varchar", "10");
$fields[] = array("acc", "varchar", "4");
$fields[] = array("description", "varchar", "255");
$fields[] = array("quantity", "decimal", "10");
$fields[] = array("unit", "varchar", "45");
$fields[] = array("price", "decimal", "10");
$fields[] = array("extended", "decimal", "10");
$fields[] = array("isValid", "varchar", "30");

$l = count($fields) - 1;

foreach($items as $item) {
	$sqlData = ""; unset($sql);
	for($i=1; $i<$l; $i++) {
		$fieldName=$fields[$i][0]; $fieldType=$fields[$i][1]; $fieldLength = $fields[$i][2];
		if($fieldName == "receivingId") {
			$item->$fieldName = $rcvId;
		}
		if($item->$fieldName) {
			$value = $item->$fieldName;
			if($fieldType == "varchar") {
				$value = "\"" . substr(mysqli_real_escape_string($db, $value), 0, $fieldLength) . "\"";
			}
			if($fieldType == "int" || $fieldType == "decimal") {
				if(!is_numeric($value)) $value = "NULL";
				if(strlen($value) > $fieldLength) $value = "NULL";
			}
			if($fieldType == "date") {
				$value = date("Y-m-d", strtotime($value));
				$minValue = "2009-10-01"; $maxValue = date("Y-m-d");
				if($value < $minValue || $value > $maxValue) {
					$value = "NULL";
				} else {
					$value = "\"" . $value . "\"";
				}
			}
			$sqlData .= " " . $fieldName . "=" . $value . ",";
		}
	}
	$sqlData = trim($sqlData, ",");

	if(is_numeric($item->receivingItemId)) {
		if($item->del == 1) {
			$sql = sprintf($itemVoidSQL, $item->receivingItemId);
		} else {
			$sql = sprintf($itemUpdateSQL, $sqlData, $item->receivingItemId);
		}
	} else {
		$sql = sprintf($itemInsertSQL, $sqlData);
	}

	$sqlHTML .= "<p style='font-size: small;'>" . str_replace("<", "&lt;", $sql) . ";</p>";

	$db->query($sql) or die("RcvItem_Save_Error: " . $db->error . "<br />\n<code>${sql}</code>\n");

}

if($_GET["a"]) {
	echo "<p>Save SQLs:</p>" . $sqlHTML;
	unset($sqlHTML);
}

?>