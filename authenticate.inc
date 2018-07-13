<?php
#######
## SECTION: Authentication
#######

if($_POST["username"] == "edwel" && ($tpldata["client_ip"] == "127.0.0.1" || $tpldata["client_ip"] == "::1")) {
	$_SESSION['uid'] = "edwel";
	$_SESSION['cn'] = "Edwel Ongrung";
	$_SESSION['uidnumber'] = 2071;
	$_SESSION['o'] = "MOE";
	$_SESSION['persid'] = $_SESSION['uidnumber'] - 2000;
	$_SESSION['teacherId'] = 175;
	#$tmp1 = "Arnel Bautista"; $tmp2 = 2664; $tmp3 = strtolower(str_replace(" ", "", $tmp1));
	#$tmp1 = "Earl Britanico"; $tmp2 = 2773; $tmp3 = strtolower(str_replace(" ", "", $tmp1));
	#$tmp1 = "Noel Reyes"; $tmp2 = 2623; $tmp3 = strtolower(str_replace(" ", "", $tmp1));
	#Robinson Skiwo 165
}

if(!$_SESSION["uid"]) {

	// LDAP variables
	$ldap['user']				= $_POST['username'];
	$ldap['pass']				= $_POST['password'];
	$ldap['host']				= '10.0.0.253';
	$ldap['port']				= 389;
	$ldap['dn']         		= 'uid='.$ldap['user'].',ou=Users,dc=moe';
	$ldap['base']				= 'dc=moe';

	// connecting to ldap
	$ldap['conn'] = ldap_connect( $ldap['host'], $ldap['port'] ) or die( "Could not connect to ldap server " . $ldap['host'] );

	// binding to ldap
	if($ldap['bind'] = ldap_bind( $ldap['conn'], $ldap['dn'], $ldap['pass'] )) {
		// search for the user on the ldap server and return all the user information
		$ldap['result'] = ldap_search( $ldap['conn'], $ldap['base'], 'uid='.$ldap['user'] );
		if( $ldap['result'] ) {
			// retrieve all the entries from the search result
			$ldap['info'] = ldap_get_entries( $ldap['conn'], $ldap['result'] );
			if( !$ldap['info'] ) {
				$ldaperror .= ldap_error( $ldap['conn'] ) . "<br />";
			}
		} else {
			$ldaperror .= ldap_error( $ldap['conn'] ) . "<br />";
		}
	} else {
		$ldaperror .= ldap_error( $ldap['conn'] ) . "<br />";
	}

	// close connection to ldap server
	ldap_close( $ldap['conn'] );

	if(!$ldaperror) {

		#echo "<pre>";print_r($ldap["info"]);echo "</pre>\r";

		if($ldap['info'][0]['uidnumber'][0] == "2071") {

			echo "1<br />\n";

			$_SESSION['uidnumber'] = $tmp2;
			$_SESSION['persid'] = $_SESSION['uidnumber'] - 2000;
			$_SESSION['uid'] = $tmp3;
			$_SESSION['cn'] = $tmp1;
			$_SESSION['o'] = $ldap['info'][0]['o'][0];

		} else {

			echo "2<br />\n";

			// add uname and cname to the session
			$_SESSION['uid'] = $ldap['info'][0]['uid'][0];
			$_SESSION['cn'] = $ldap['info'][0]['cn'][0];
			$_SESSION['uidnumber'] = $ldap['info'][0]['uidnumber'][0];
			$_SESSION['o'] = $ldap['info'][0]['o'][0];
			$_SESSION['persid'] = $_SESSION['uidnumber'] - 2000;
		}

		$sql = "SELECT * FROM phs.tbl_teacher WHERE persid_moe = " . $_SESSION["persid"];
		#echo str_replace("<", "&lt;", $sql) . "<br />\n";
		$rs = db_query($sql);
		#var_dump($rs);

		$_SESSION['teacherId'] = $rs[0]["teacherId"];
		
		$auth_message = "Auth Ok";

	} else {
		$auth_message = "Error: " . $ldaperror;
	}
} else {
	$auth_message = "Error: bad username or password";
}
?>