<html>
<head>
	<title>PHS Counseling System</title>
	<style type="text/css">
		<!-- insert css -->

	</style>
</head>

<body bgcolor={bgcolor} style='font-family: "Lucida Grande", Arial, sans-serif;'>

<div class=mainpanel>

	<div style="position: absolute; top-left: 0,0;">
		<a href='../'><img src='{graphics_dir}logo_made.gif' height=72 width=72 border=0></a>
		<br />
		<ul id="leftmenu">
			{leftmenu}
		</ul>

		<p class=lbl1><br />visiting from:<br />{client_ip}</p>

		<hr />

		<p style="font-size: xx-small; color: #abc;">
		(c) FBCS, Inc<br />5380 Ocean Drive<br >Unit 6D<br >Singer Island<br >FL 33404<br >561 842 4335<br >Cell 561 601 8211<br >Fax 561 844 3082
		</p>
	</div>

	<div style="float: right;">
		<span class=lnk1><a href="{home_link}">Home</a> | <span class=lnk1><a href="?t={unit_abbrv}&t1=Resources" target="_self">Resources</a> | <a href="javascript:document.logaction.submit()">{log_action}</a></span>
		<form name=logaction style="display: none;" action="" method=post><input type=hidden name=log_action value="{log_action}" /></form>
	</div>

	<div class='toptitle'>{unit_fullname}</div>
	<ul id="topmenu">
		<li>{location}</li>
	</ul>

	<div style="clear: both;"></div>

	<div style="margin-left: 100px; min-height: 480px; padding: 4px 6px 4px 8px;">

		<span class='location'>{location}</span><br /><br />

		<!-- insert dynamic html -->

	</div>

</div>

</body>

</html>