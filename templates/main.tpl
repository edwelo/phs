<!DOCTYPE html>
<html>
<head>
	<title>{unit_fullname}</title>
	<meta charset="UTF-8">
    <link rel="stylesheet" href="css/main.css">
	<script type='text/javascript' src='js/main.js'></script>
	<script type='text/javascript' src='js/{js}'></script>
	<style type="text/css">
		<!-- insert custom css here -->
	</style>
	<script type="text/javascript">
		//window.onload = function() { moveToNewDB(); }
	</script>
</head>

<body>

<div id="site_body">

	<div id="content_head">
		<div style="position: absolute; top-left: 0,0;">
			<a href=''><img src='graphics/logo_made.gif' height=72 width=72 border=0></a>
		</div>

		<div style="float: right; text-align: right;">
			<span class=lnk1><a href="phs.php">Home</a></span> | <span class=lnk1><a href="javascript:document.logaction.submit()">{log_action}</a></span>
			<form name=logaction style="display: none;" action="phs.php" method=post><input type=hidden name=log_action value="{log_action}" /></form>
			<span class=lbl1><br />{cn} visiting from: {client_ip}</span>
		</div>

		<div class='toptitle'>{unit_fullname}</div>
		<div style='background: #333; float: left; margin: 0; padding: 0 0 0 0 90px; width: 100%; text-align: center; color: #eef;'>
			<!-- location bar -->
			<a href='?{back_link}' class=button>Back</a>
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			{area}
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			<a href='?area={area}&t1=Menu' class=button>Menu</a>
			<!-- /location bar -->
		</div>

		<div style="clear: both;"></div>
	</div>

	<div id="content_body">

		<!-- insert dynamic content html -->

	</div>

</div>

<div id="site_footer">
	(c) FBCS, Inc., 5380 Ocean Drive, Unit 6D, Singer Island, FL 33404 | tel 561 842 4335, Cell 561 601 8211, Fax 561 844 3082
</div>

</body>
</html>