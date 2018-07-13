<div class=bodypanel>
	<span class=lbl1>Mid Term Grades</span><br /><br />
	
	<form class=tight action="" method=post>
		<span class=lbl1>School Year: </span>
		<input type=text name=sy value="{sy}" size=5 />
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Semester: </span>
		<input type=radio name=semester value=1 /><span class=lbl1>1</span>
		<input type=radio name=semester value=2 /><span class=lbl1>2</span>
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>quarter: </span>
		<input type=radio name=quarter value=1 /><span class=lbl1>1</span>
		<input type=radio name=quarter value=2 /><span class=lbl1>2</span>
		&nbsp;&nbsp;&nbsp;
		<input type=submit value=go />
	</form>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
	<span class=lbl1>Mid Term Date: </span><span style="color: white; font-size: small;">{qeDate}</span>
	<hr />
	<div style='float: right;'>
		<span class=lnk1>
			[ <a href='apis/gradesdump.php?type=mid&phssy={phssy}&sem={semester}&qtr={quarter}' target='_blank'>download</a> ]
		</span>
	</div>	
	Mid Term Scores<br />
	<div style='clear: both;'></div>

	{content}
	
</div>