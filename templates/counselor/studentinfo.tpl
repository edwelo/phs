<div class=bodypanel_light>

	<!--<div style='float: right;'><img src='../data/phs/stupics/{picName}.jpg' height=128 width=128 /></div>-->
	<div style='float: right;'><img src='data/phs/stupics/pic.jpg' style='border-radius: .5em;' height=72 width=72 /></div>
	<div style='float: right; padding-right: 1em;'>
		<table>
			<tr>
				<td align=right><span class=lbl1>Grade Level:</span></td>
				<td><span class="txtspan1">{gradeLevel}</span></td>
			</tr>
			<tr>
				<td align=right><span class=lbl1>Academic Status:</span></td>
				<td><span class="txtspan1">{academicStatus}</span></td>
			</tr>
			<tr>
				<td align=right><span class=lbl1>Enrollment Status:</span></td>
				<td><span class="txtspan1">{enrollmentStatus}</span></td>
			</tr>
		</table>
	</div>
	<div style='float: left;'>
		<span style='font-size: small;'>{studentId}</span>
		&nbsp;
		<span style='font-weight: bold; font-size: x-large;'>{studentName}</span>

		&nbsp;&nbsp;&nbsp;
		<form class=tight action="" method=post>
			<input type=hidden name=set_student_id value=0 />
			<input type=submit value=exit />
		</form>
		<br />

		<span class=lbl1>Gender:</span> <span class="txtspan1">{gender}</span>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Current Age:</span> <span class="txtspan1">{currentAge}</span>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<br />
		<span class=lbl1>Periods</span>&nbsp;
		<span class=lbl1>1st:</span> <span class="txtspan1">English</span>
		<span class=lbl1>2nd:</span> <span class="txtspan1">Math</span>
		<span class=lbl1>3rd:</span> <span class="txtspan1">Science</span>
		<span class=lbl1>4th:</span> <span class="txtspan1">Social Studies</span>
	</div>
	<div class='flend'></div>

</div>

<br />