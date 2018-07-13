<?php

######
# functions for phstchrs/operations-incidences.inc
# eo 131106
######

function save_incident() {

	//clean
	foreach($_POST as $key=>$value) {
		$_POST[$key] = trim($value);
	}

	//check required fields, continue if ok
	if($_POST["incidentId"]
		&& (is_numeric($_POST["incidentId"]) || $_POST["incidentId"] == "new")
		&& $_POST["studentId"] && is_numeric($_POST["studentId"])
		&& $_POST["incidentDate"]
		&& $_POST["incidentDate"] == date("Y-m-d", strtotime($_POST["incidentDate"]))
		&& $_POST["location"] && $_POST["category"] && $_POST["description"])
	{
		if($_POST["incidentId"] == "new")
		{
			//insert if new
			$sql = "INSERT INTO phs.tbl_incident SET
						studentId='" . $_POST["studentId"] . "',
						incidentDate='" . $_POST["incidentDate"] . "',
						incidentTime='" . $_POST["incidentTime"] . "',
						location='" . $_POST["location"] . "',
						code='" . $_POST["code"] . "',
						category='" . $_POST["category"] . "',
						description='" . $_POST["description"] . "',
						reportedBy='" . $_POST["reportedBy"] . "',
						reportedDate='" . $_POST["reportedDate"] . "',
						notes='" . $_POST["notes"] . "',
						enteredBy='" . $_SESSION["teacherId"] . "',
						enteredDate='" . date("Y-m-d") . "'";
			$db = new mysqli("localhost", "mysql", "mysql", "phs");
			$rs = $db->query($sql) or die("Save new incident error: " . $db->error);
			return $db->insert_id;
			$db->close;
		}
		else
		{
			//or update
			$sql = "UPDATE phs.tbl_incident SET
						incidentTime='" . $_POST["incidentTime"] . "',
						location='" . $_POST["location"] . "',
						code='" . $_POST["code"] . "',
						category='" . $_POST["category"] . "',
						description='" . $_POST["description"] . "',
						reportedBy='" . $_POST["reportedBy"] . "',
						reportedDate='" . $_POST["reportedDate"] . "',
						notes='" . $_POST["notes"] . "',
						referredTo='" . $_POST["referredTo"] . "',
						referredDate='" . $_POST["referredDate"] . "',
						modifiedBy='" . $_SESSION["teacherId"] . "',
						modifiedDate='" . date("Y-m-d") . "'
					WHERE incidentId=" . $_POST["incidentId"];
			$db = new mysqli("localhost", "mysql", "mysql", "phs");
			$rs = $db->query($sql) or die("update incident error: " . $db->error);
			$db->close;
		}
		#printsql($sql);
	}
	else
	{
		die("Save Incident Aborted: bad entry");
	}
}


?>