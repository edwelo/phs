<div class=bodypanel>
	<center>
		<span class=lbl2>{cn}'s Grades Data</span>
		&nbsp;&nbsp;&nbsp;
		<span class=lnk1>
			[ <a href="downloads/student-grades.php?action=download&phssy={phssy}&teacherId={teacherId}">
				download
 	 	 	</a> ]
		</span>
	</center>
	<table class=bodypanel>
		<thead>
			<tr>
				<th rowspan=2>Course</th>
				<th rowspan=2>Student</th>
				<th colspan=4 style="border-left: 5px solid #567;">1st Qtr Mid Term</th>
				<th colspan=4 style="border-left: 5px solid #567;">1st Qtr Grade</th>
				<th colspan=4 style="border-left: 5px solid #567;">2nd Qtr Mid Term</th>
				<th colspan=4 style="border-left: 5px solid #567;">2nd Qtr Grades</th>
			</tr>
			<tr>
				<th style="border-left: 5px solid #567;">S</th>
				<th>L</th>
				<th>A</th>
				<th>B</th>
				<th style="border-left: 5px solid #567;">S</th>
				<th>L</th>
				<th>A</th>
				<th>B</th>
				<th style="border-left: 5px solid #567;">S</th>
				<th>L</th>
				<th>A</th>
				<th>B</th>
				<th style="border-left: 5px solid #567;">S</th>
				<th>L</th>
				<th>A</th>
				<th>B</th>
			</tr>
		</thead>
		<tbody>
			<tr id=row>
				<td>{courseName} {semester}.{period}</td>
				<td>{studentName}</td>
				<td style="border-left: 5px solid #567; text-align: center;">{q1ms}</td>
				<td>{q1ml}</td>
				<td>{q1ma}</td>
				<td>{q1mb}</td>
				<td style="border-left: 5px solid #567; text-align: center;">{q1es}</td>
				<td>{q1el}</td>
				<td>{q1ea}</td>
				<td>{q1eb}</td>
				<td style="border-left: 5px solid #567; text-align: center;">{q2ms}</td>
				<td>{q2ml}</td>
				<td>{q2ma}</td>
				<td>{q2mb}</td>
				<td style="border-left: 5px solid #567; text-align: center;">{q2es}</td>
				<td>{q2el}</td>
				<td>{q2ea}</td>
				<td>{q2eb}</td>
			</tr>
		</tbody>
	</table>
</div>