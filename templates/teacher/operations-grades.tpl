<div class=bodypanel>
<!-- class list -->
	<center>
		<span class=lbl2>List of Classes</span>
	</center>
	<table class=bodypanel>
		<thead>
			<tr>
				<th rowspan=2>Class<br />ID</th>
				<th rowspan=2>Course &<br />Period</th>
				<th rowspan=2>Stu<br />Count</th>
				<th colspan=5 style="border-left: 5px solid #567;">1st Qtr Mid Term</th>
				<th colspan=5 style="border-left: 5px solid #567;">1st Qtr Grades</th>
				<th colspan=5 style="border-left: 5px solid #567;">2nd Qtr Mid Term</th>
				<th colspan=5 style="border-left: 5px solid #567;">2nd Qtr Grades</th>
				<th rowspan=2 style="border-left: 5px solid #567;"></th>
			</tr>
			<tr>
				<th style="border-left: 5px solid #567;">N</th>
				<th>Min</th>
				<th>Max</th>
				<th>Avg</th>
				<th>StD</th>
				<th style="border-left: 5px solid #567;">N</th>
				<th>Min</th>
				<th>Max</th>
				<th>Avg</th>
				<th>StD</th>
				<th style="border-left: 5px solid #567;">N</th>
				<th>Min</th>
				<th>Max</th>
				<th>Avg</th>
				<th>StD</th>
				<th style="border-left: 5px solid #567;">N</th>
				<th>Min</th>
				<th>Max</th>
				<th>Avg</th>
				<th>StD</th>
			</tr>
		</thead>
		<tbody>
			<tr id=row>
				<td align=center>{classId}</td>
				<td>{courseName} {semester}.{period}</td>
				<td align=center>{countStudents}</td>
				<td style="border-left: 5px solid #567;">{countq1mScores}</td>
				<td>{minq1mScore}</td>
				<td>{maxq1mScore}</td>
				<td>{avgq1mScore}</td>
				<td>{stdq1mScore}</td>
				<td style="border-left: 5px solid #567;">{countq1eScores}</td>
				<td>{minq1eScore}</td>
				<td>{maxq1eScore}</td>
				<td>{avgq1eScore}</td>
				<td>{stdq1eScore}</td>
				<td style="border-left: 5px solid #567;">{countq2mScores}</td>
				<td>{minq2mScore}</td>
				<td>{maxq2mScore}</td>
				<td>{avgq2mScore}</td>
				<td>{stdq2mScore}</td>
				<td style="border-left: 5px solid #567;">{countq2eScores}</td>
				<td>{minq2eScore}</td>
				<td>{maxq2eScore}</td>
				<td>{avgq2eScore}</td>
				<td>{stdq2eScore}</td>
				<td align=right style="border-left: 5px solid #567;"><a href="?{hrefpre}&classId={classId}">&nbsp;&nbsp;<b>></b>&nbsp;</a></td>
			</tr>
		</tbody>
	</table>
<!-- /class list -->
<!-- class roster -->
	<center>
		<span class=lbl2>{courseName} - {period} Period, {semester} Semester</span>
	</center>
	{table_html}
<!-- /class roster -->
</div>