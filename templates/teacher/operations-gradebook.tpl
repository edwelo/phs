<div class=bodypanel>
<!-- class list -->
	<span class=lbl1>List of Classes</span><br />
	<table class=bodypanel>
		<thead>
			<tr><th>Class ID</th><th>Course Name</th><th>Semester</th><th>Period</th><th>Number of Students</th><th></th></tr>
		</thead>
		<tbody>
			<tr id=row><td align=center>{classId}</td><td>{courseName}</td><td align=center>{semester}</td><td align=center>{period}</td><td align=center>{numberEnrolled}</td><td align=right><a href="?{hrefpre}&classId={classId}">&nbsp;&nbsp;<b>></b>&nbsp;</a></tr>
		</tbody>
	</table>
<!-- /class list -->
<!-- class roster -->
	<center>
		<span class=lbl2>{courseName} - Semester {semester}, Period {period}</span>
	</center>
	<table class=bodypanel>
		{table_innnerhtml}
	</table>
<!-- /class roster -->
<!-- class roster edit -->
	<form class=tight action="?{back_menu_link}" method=post>
		<span class=lbl1>{courseName}, sem {semester}, period {period}
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			Activity for {edit_dateday}
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			<input type=submit value=save />
			</span><br />
		<table class=bodypanel>
			<thead>
				<tr>
					<th>Student</th>
					<th>Score</th>
					<th>Notes</th>
			</thead>
			<tbody>
				<tr id=row>
					<td>{studentName}</td>
					<td align=center><input name={score} type=text value="" size=10 /></td>
					<td align=center><input name={day5} type=text value='{absenceNote}' size=60 /></td>
				</tr>
			</tbody>
		</table>
	</form>
<!-- /class roster edit -->
</div>