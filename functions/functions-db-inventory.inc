<?php

#################
## DATABASE FUNCTIONS - INVENTORY
#################

function list1($criteria) {

	list($fld,$value)=explode("::",$criteria);
	if(!$fld || !$value) {
		$ret="error: bad criteria";
	} else {

		$sql="
			SELECT
				a.prodtype,
				a.mfr,
				b.rpno,
				CONCAT(a.specname,' ',a.modelname) AS product,
				a.modelnumber,
				b.serialnumber,
				d.officename,
				b.pono,
				DATE_FORMAT(b.acqdate,'%c/%e/%y') AS acqdate,
				DATE_FORMAT(b.mfrdate,'%c/%e/%y') AS mfrdate
			FROM
				inventory.products a,
				inventory.proddetail b
				LEFT JOIN inventory.prodlocation c ON b.locid=c.locid
				LEFT JOIN moe.tbloffices d ON c.offid=d.id
			WHERE
				a.prodid=b.prodid
				AND b.dispid IS NULL
				AND $fld='$value'
			ORDER BY a.$fld,product
		";

		$ret=array();

		$db=new mysqli("localhost","mysql","mysql");
		$rs=$db->query($sql) or die($db->error);

		while($tmp=$rs->fetch_assoc()) {
			$ret[]=$tmp;
		}
		$db->close;
	}

	return $ret;
}

function vehicles_by_unit($unitid=NULL) {

	$sql = "SELECT a.assigndate, b.prddtlid, d.mfr, d.genname, d.specname, d.modelname, c.rpno FROM inventory.prodlocation a, (SELECT t1.* FROM inventory.prodlocationdetail t1 LEFT JOIN inventory.prodlocationdetail t2 ON t1.prddtlid=t2.prddtlid AND t1.locid_date < t2.locid_date WHERE t2.locid_date IS NULL) b, inventory.proddetail c, inventory.products d WHERE a.locid=b.locid AND b.prddtlid=c.prddtlid AND c.prodid=d.prodid AND d.prodtype='vehicle'";

	if($unitid && is_numeric($unitid)) $sql = str_replace(" AND d.prodtype=", " AND a.offid=$unitid AND d.prodtype=", $sql);

	#echo "<span style='font-size: x-small; color: red;'>$sql</span><br />\n";

	$rs = db_query($sql);
	foreach($rs as $value) {
		$ret[$value["prddtlid"]] = $value["mfr"] . " " . $value["modelname"] . " " . $value["genname"] . ", rpno: " . $value["rpno"];
	}

	return $ret;
}

?>


