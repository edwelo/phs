<!-- student list -->
<div class=bodypanel>
<center>STUDENT LIST FOR <strong>{cn}</strong></center>
<table class=bodypanel>
	<thead>
		<tr>
			<th>No.</th>
			<th>Student Name</th>
			<th>Gender</th>
			<th>Age</th>
			<th>Residence</th>
			<th>Responsible Adult</th>
			<th>Phone</th>
			<th>&nbsp;</th>
		</tr>
	</thead>
	<tbody>
		<tr id=row>
			<td>{no.}.</td>
			<td>{studentName}</td>
			<td>{gender}</td>
			<td>{age}</td>
			<td>{residence}</td>
			<td>{responsibleAdult}</td>
			<td>{phone}</td>
			<td align=center>
				<a	style="font-weight: bold; text-decoration: none;"
					href="?{hrefpre}&stuid={studentId}">
					>
				</a>
			</td>
		</tr>
	</tbody>
</table>
</div>
<!-- /student list -->
<!-- student form -->
<center>INDIVIDUAL STUDENT INFO, from <strong>{cn}</strong> classes</center>
<br />
<div class=flbeg>
	<div class=bodypanel>
		{studentName}<br />
		<div class=flbeg>
			<img src='data/phs/stupics/pic.jpg' height=128 width=128 />
		</div>
		<div class=flmid>
			<span class=lbl1>Gender: </span>{gender}<br />
			<span class=lbl1>Age: </span>{currentAge}<br />
			<span class=lbl1>Grade: </span>{grade}<br />
		</div>
		<div class=flend></div>
		<br />
		<span class=lbl1>Gender: </span>{gender}
		<br />
		<span class=lbl1>Age: </span>{currentAge}
		<br />
		<span class=lbl1>Residence: </span>{residence}
		<br />
		<span class=lbl1>Responsible Adult: </span>{responsibleAdult}
		<br />
		<span class=lbl1>Phone: </span>{phone}
	</div>
</div>
<div class=flmid>
	<div class=bodypanel>
		<span class=lbl1>Classes</span>
		<table class=bodypanel>
			<tr><th>Period</th><th>1st Semester</th><th>2nd Semester</th></tr>
			<tr><td>1st Period</td><td>{teacher1.1} - {course1.1}</td><td>{teacher2.1} - {course2.1}</td></tr>
			<tr><td>2nd Period</td><td>{teacher1.2} - {course1.2}</td><td>{teacher2.2} - {course2.2}</td></tr>
			<tr><td>3rd Period</td><td>{teacher1.3} - {course1.3}</td><td>{teacher2.3} - {course2.3}</td></tr>
			<tr><td>4th Period</td><td>{teacher1.4} - {course1.4}</td><td>{teacher2.4} - {course2.4}</td></tr>
		</table>
	</div>
</div>
<div class=flmid>
	<div class=bodypanel>
	&nbsp;

	</div>
</div>
<div class=flend></div>
<!-- /student form -->