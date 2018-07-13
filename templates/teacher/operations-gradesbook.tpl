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
	<span class=lbl1>{courseName}, sem: {semester}, per: {period}</span><br />
	<table class=bodypanel>
		<thead>
			<tr>
				<th>Student</th>
				<th><a style="font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;" href='?{hrefpre}&date={-9 Days}'>{Act01}<br />{Date01}</a></th>
				<th><a style="font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;" href='?{hrefpre}&date={-8 Days}'>{Act02}<br />{Date02}</a></th>
				<th><a style="font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;" href='?{hrefpre}&date={-7 Days}'>{Act03}<br />{Date03}</a></th>
				<th><a style="font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;" href='?{hrefpre}&date={-6 Days}'>{Act04}<br />{Date04}</a></th>
				<th><a style="font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;" href='?{hrefpre}&date={-5 Days}'>{Act05}<br />{Date05}</a></th>
				<th><a style="font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;" href='?{hrefpre}&date={-4 Days}'>{Act06}<br />{Date06}</a></th>
				<th><a style="font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;" href='?{hrefpre}&date={-3 Days}'>{Act07}<br />{Date07}</a></th>
				<th><a style="font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;" href='?{hrefpre}&date={-2 Days}'>{Act08}<br />{Date08}</a></th>
				<th><a style="font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;" href='?{hrefpre}&date={-1 Day}'>{Act09}<br />{Date09}</a></th>
				<th><a style="font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;" href='?{hrefpre}&date={today}'>{Qtr}<br />{qtrdate}</a></th></tr>
		</thead>
		<tbody>
			<tr id=row><td>{studentName}</td><td>{day1}</td><td>{day2}</td><td>{day3}</td><td>{day4}</td><td>{day5}</td><td>{day6}</td><td>{day7}</td><td>{day8}</td><td>{day9}</td><td>{day10}</td></tr>
		</tbody>
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