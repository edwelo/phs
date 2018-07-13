<div class=bodypanel>
	<span class=lbl1>Daily Absences</span><br /><br />
	
	<form class=tight action="" method=post>
		<span class=lbl1>Start Date: </span>
		<input type=text name=startDate value="{startDate}" size=12 />
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>End Date: </span>
		<input type=text name=endDate value="{endDate}" size=12 />
		&nbsp;&nbsp;&nbsp;
		<input type=submit value=go />
	</form>
	<hr />
	{content}
	
	<!--
	Absences Table<br />
	<table class=bodypanel>
	<tr><th>Date</th><th>Absent 1 class</th><th>Absent 2 classes</th><th>Absent 3 Classes</th><th>Absent All 4 Classes</th></tr>
	<tr id=row1><td>{absenceDate}</td><td>{abs1}</td><td>{abs2}</td><td>{abs3}</td><td>{abs4}</td></tr>
	</table>
	-->

</div>