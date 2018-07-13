<?php

function removeTableTop($tableHTML) {
	return preg_replace("/<table.*\/thead>/s", "", $tableHTML);
}

//return a basic html table
function basichtmltable($datars) {

	$data=$datars["rs"];
	if($datars["tblid"]) $tblid=$datars["tblid"];
	if($datars["tblname"]) $tblname=$datars["tblname"];
	if($datars["idlink"]) $idlink=$datars["idlink"];
	if($datars["caption"]) $caption=$datars["caption"];
	if($datars["atn"]) list($align,$ttlflds,$nf)=explode(",",$datars["atn"]);
	if($datars["tw"]) $tw=$datars["tw"];
	if($datars["szv"]) $szv=$datars["szv"];
	if($datars["tblstyle"]) $tblstyle=$datars["tblstyle"];
	if($datars["df"]) $df=$datars["df"];
	if($datars["rownums"]) $rownums="y";

	if(!$tblstyle) $tblstyle="ct3";

	$numrows = sizeof($data); $numfields = sizeof($data[0]);
	if($numfields) $keys=array_keys($data[0]);
	$cellalign["l"]="left"; $cellalign["c"]="center"; $cellalign["r"]="right";

	//table caption
	if($caption) {
		$caption = "<caption>$caption";
		if($dl) {
			$caption .= "&nbsp;&nbsp;&nbsp;&nbsp;\n";
			$caption .= "<form class=tight name=gotodownload action='download/downloadtablesimple.php?f=$dl";
			$caption .= "' method=post>\n";
			$caption .= "<input type=hidden name=f value='$dl.xls'>\n";
			$caption .= "<input type=hidden name=sql value='" . str_replace("'","&#039;",$sql) . "'>\n";
			#$ret .= "<input type=hidden name=caption value='$title - $caption'>\n";
			#$ret .= "<input type=hidden name=uid value='$uid'>\n";
			$caption .= "<span class=lnk1>[ <a href='javascript:document.gotodownload.submit()'>download</a> ]</span>\n";
			$caption .= "</form>\n";
		}
		$caption .= "</caption>\n";
	}

	//column headings
	$thead = "";
	for($i=0;$i<$numfields;$i++) {
		if(substr($df,$i,1)!="n") {
			$thead .= "<th";
			if(substr($align,$i,1)=="r") $thead .= " style='text-align: right;'";
			$thead .= ">" . $keys[$i] . "</th>";
		}
	}
	if($rownums) $thead = "<th align=right>no.</th>" . $thead;

	//tbody
	$tbody="";
	$thelink=explode(":x:",$idlink);
	if(is_array($data)) {
		$r=0;
		foreach($data as $tmp) {
			$i=0; $cells="";
			foreach($tmp as $key=>$value) { //start $tmp iteration (iterates through each field of the record)
				if(substr($df,$i,1)!="n") { //start $df (disable/hide field) check

					//table totals
					if(substr($ttlflds,$i,1)=="y" || substr($ttlflds,$i,1)=="a") { $ttl[$i]+=$value; }

					//set data item to &nbsp; if it is zero, otherwise print as string or formatted number
					if($value=="") {
						$value="&nbsp;";
					} else if(is_numeric(substr($nf,$i,1))) {
						if(is_numeric($value)) $value = number_format($value,substr($nf,$i,1));
					}

					//link or plain
					if($thelink[$i]) {
						$thepos = strrpos($thelink[$i],"=");
						if(($thepos + 1) < strlen($thelink[$i])) {
							$key2=substr($thelink[$i],$thepos + 1); //column position?
						} else {
							$key2=$i;
						}
						$value = "<a href='" . substr($thelink[$key2],0,$thepos) . "=" . $value . "'>$value</a>";
						//inserts dynamic values into the link
						foreach($tmp as $key_lfld => $value_lfld) {
							$value = str_replace("?" . $key_lfld . "?", $value_lfld, $value);
						}
					}

					$cells.="<td";
					if(substr($align,$i,1)=="r" || substr($align,$i,1)=="c") $cells .= " align=" . $cellalign[substr($align,$i,1)];
					$cells .= ">$value</td>";
				} //end $df (disable/hide field) check
				$i++;
			} //end $tmp iterate
			if($rownums) { $cells = "<td align=right>" . ++$r . ".</td>" . $cells; }
			$tbody .= "<tr>$cells</tr>\n";
		}
	}

	//tfoot
	if($ttlflds) {
		$tfoot="";
		for($i=0;$i<$numfields;$i++) {
			if(substr($df,$i,1)!="n") { //df = disabled (hidden) field
				$tt=$ttl[$i];
				if(substr($ttlflds,$i,1)=="a") $tt=$tt/$numrows;
				if(is_numeric(substr($nf,$i,1))) {
					$value = number_format($tt,substr($nf,$i,1),".",",");
				} else {
					$value = $tt;
				}
				$tfoot .= "<th";
				if(substr($align,$i,1)=="r" || substr($align,$i,1)=="c") $tfoot .= " align=" . $cellalign[substr($align,$i,1)];
				$tfoot .= ">$value</th>";
			}
		}
		if($rownums) $tfoot = "<th>&nbsp;</th>" . $tfoot;
	}

	$tblattribs="";
	if($tblid) $tblattribs.=" id=$tblid";
	if($tblname) $tblattribs.=" name=$tblname";
	if($tblstyle) $tblattribs.=" class=$tblstyle";
	if($tw) $tblattribs.=" width=$tw";

	if($caption) $caption=$caption . "\n";
	$ret="<table%s>\n%s<thead>\n<tr>%s</tr>\n</thead>\n<tfoot>\n<tr>%s</tr>\n</tfoot>\n<tbody>\n%s</tbody>\n</table>";
	$ret=sprintf($ret,$tblattribs,$caption,$thead,$tfoot,$tbody);
	#$ret .= "<span class=lbl1>displayed using basichtmltable</span><br />\n";

	return $ret;
}

?>
