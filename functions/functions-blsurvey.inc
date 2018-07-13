<?php
//functions

//get an empty record array from a table
function get_blank_record($table) {
	global $db, $error_messages;
	if($rs=$db->query("Desc $table")) {
		while($tmp = $rs->fetch_assoc()) $ret[$tmp["Field"]] = "";
		return $ret;
	} else {
		$error_messages .= "error - get_blank_record: " . $db->error . "\n";
	}
}

//get one or more records from a table, returns one empty record if no records are found
function get_records($table, $key=NULL, $keyvalue=NULL) {
	global $db, $error_messages;
	if($table) {
		if((!$key && !$keyvalue) || ($key && $keyvalue)) {
			$sql = "SELECT * FROM $table";
			if($key && $keyvalue) $sql .= " WHERE $key='$keyvalue'";
			if($rs=$db->query($sql)) {
				if($rs->num_rows > 0) {
					while($tmp = $rs->fetch_assoc()) $ret[] = $tmp;
				} else {
					$rs = $db->query("DESC $table");
					while($tmp = $rs->fetch_assoc()) $ret[$tmp["Field"]] = "";
				}
			} else {
				$error_messages = "error - get_records: " . $db->error . "\n" . $sql . "\n";
			}
		} else {
			$error_messages = "error - get_records: key='$key', keyvalue='$keyvalue', either none or both parameters are expected\n";
		}
	} else {
		$error_messages = "error - get_records: table name was not provided\n";
	}
	$rs->close;
	$db->close;
	return $ret;
}

//expects and gets only one record from a table, returns one empty record if no records are found
function get_record($table, $key=NULL, $keyvalue=NULL) {
	global $db, $error_messages;
	if($table) {
		if((!$key && !$keyvalue) || ($key && $keyvalue)) {
			if($key && $keyvalue) $sql = "SELECT * FROM $table";
			if($key && $keyvalue) $sql .= " WHERE $key='$keyvalue'";
			if($rs=$db->query($sql)) {
				if($rs->num_rows == 1) {
					$ret = $rs->fetch_assoc();
				} else if($rs->num_rows == 0){
					$rs = $db->query("DESC $table");
					while($tmp = $rs->fetch_assoc()) { $ret[$tmp["Field"]] = ""; }
				} else {
					$error_messages = "error - get_one: more than one result, only one expected.\n$sql\n";
				}
			} else {
				$error_messages = "error - get_records:\n$sql\n" . $db->error . "\n";
			}
		} else {
			$error_messages = "error - get_records: key='$key', keyvalue='$keyvalue', either none or both parameters are expected";
		}
	} else {
		$error_messages = "error - get_records: table name was not provided";
	}
	$rs->close;
	$db->close;
	return $ret;
}

//sql based db query for more complete requests
function db_query($sql) {
	if(substr($sql, 0, 6) == "SELECT" || substr($sql, 0, 6) == "INSERT" || substr($sql, 0, 6) == "UPDATE") {
		global $db, $error_messages;
		if($rs=$db->query($sql)) {
			if(substr($sql, 0, 6) == "INSERT" || substr($sql, 0, 6) == "UPDATE") {
				$error_messages = substr($sql, 0, 6) . " was successful";
			} else if(substr($sql, 0, 6) == "SELECT") {
				if($rs->num_rows > 0) {
					while($tmp = $rs->fetch_assoc()) $ret[] = $tmp;
				} else {
					$error_messages = "error - db_query: sql ok but returned no records\n$sql\n";
				}
			}
		} else {
			$error_messages = "error - db_query\n$sql\n" . $db->error . "\n";
		}
		$db->close;
	} else {
		$error_messages = "error - db_query: can only do select, update, insert for now\n$sql\n";
	}
	return $ret;
}


?>
