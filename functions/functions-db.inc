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
//returns $ret[0][fld1][fld2]..., $ret[1][fld1][fld2]..., ... for one or more records
//returns $ret[fld1][fld2]... for 0 records.
function get_records($table, $key=NULL, $keyvalue=NULL, $orderby=NULL) {
	$db = new mysqli("phsmysql.moe", "mysql", "mysql");
	global $error_messages;
	if($table) {
		if((!$key && !$keyvalue) || ($key && $keyvalue)) {
			$sql = "SELECT * FROM $table";
			if($key && $keyvalue) $sql .= " WHERE $key='$keyvalue'";
			if($sql && $orderby) $sql .= " ORDER BY " . $orderby;
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

//get one or more records from a table, returns one empty record if no records are found
//returns $ret[0][fld1][fld2]..., $ret[1][fld1][fld2]..., ... for one or more records
//returns $ret[0][fld1][fld2] with empty elements for 0 records.
function get_records2($table, $key=NULL, $keyvalue=NULL, $orderby=NULL) {
	$db = new mysqli("phsmysql.moe", "mysql", "mysql");
	global $error_messages;
	if($table) {
		if((!$key && !$keyvalue) || ($key && $keyvalue)) {
			$sql = "SELECT * FROM $table";
			if($key && $keyvalue) $sql .= " WHERE $key='$keyvalue'";
			if($sql && $orderby) $sql .= " ORDER BY " . $orderby;
			if($rs=$db->query($sql)) {
				if($rs->num_rows > 0) {
					while($tmp = $rs->fetch_assoc()) $ret[] = $tmp;
				} else {
					$rs = $db->query("DESC $table");
					while($tmp = $rs->fetch_assoc()) $ret[0][$tmp["Field"]] = "";
					$error_messages = "notice - get_records: no records found.";
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
	$db = new mysqli("phsmysql.moe", "mysql", "mysql");
	global $error_messages;
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

//expects and gets only one record from a table, returns one empty record if no records are found
function get_sqlResult($sql) {
	$db = new mysqli("phsmysql.moe", "mysql", "mysql");
	if($rs=$db->query($sql)) {
		$ret = $rs->fetch_assoc();
	} else {
		die("error - get_sqlResult: " . $db->error . "<br />\n${sql}<br />\n");
	}
	$rs->close;
	$db->close;
	return $ret;
}

//expects and gets records from an sql command
function get_sqlResults($sql) {
	$db = new mysqli("phsmysql.moe", "mysql", "mysql");
	if($rs=$db->query($sql)) {
		while($tmp = $rs->fetch_assoc()) {
			$ret[] = $tmp;
		}
	} else {
		die("error - get_sqlResult: " . $db->error . "<br />\n${sql}<br />\n");
	}
	$rs->close;
	$db->close;
	return $ret;
}

//sql based db query for more complex requests
function db_query($sql) {
	$sql = trim($sql);
	$tmp = strtolower(substr($sql, 0, 6));
	#if($tmp != "select") echo $tmp . " is not equal!<br />\n";
	#printsql($sql);
	if($tmp == "select" || $tmp == "insert" || $tmp == "update" || $tmp == "replac" || $tmp == "delete") {
		$db = new mysqli("phsmysql.moe", "mysql", "mysql");
		#global $error_messages;
		if($rs = $db->query($sql)) {
			if($tmp == "insert" || $tmp == "update" || $tmp == "replac" || $tmp == "delete") {
				$error_messages = "success - db_query: " . $tmp . " was successful";
			} else if($tmp == "select") {
				if($rs->num_rows > 0) {
					while($tmp = $rs->fetch_assoc()) { $ret[] = $tmp; }
				} else {
					die("error - db_query: No records exist<br />\n${sql}");
				}
			}
		} else {
			die("error - db_query: " . $db->error . "<br />\n${sql}");
		}
		$db->close;
	} else {
		die("error - db_query: can only do select, update, insert for now<br />\n${sql}");
	}
	//echo $error_messages;
	return $ret;
}

?>
