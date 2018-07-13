<span style='color: #778fbd; font-size: large;'>Select a student</span>

<div id=tab2>

	<div class=flbeg>
		<form class=tight action='' method=post>
		<span class=lbl1>Enter Student ID: </span><br />
		<input type=text name=set_student_id size=6 />
		<input type=submit value=go />
		</form>
	</div>

	<div class=flmid>
		&nbsp;or&nbsp;
	</div>

	<div class=flmid>
		<form class=tight action='' method=get>
		{getpre}
		<span class=lbl1>find student (enter search phrase): </span><br />
		<input type=text name=sp value='{sp}' size=20 />
		<input type=submit value=go />
		</form>
	</div>
<!-- found list -->
	<div class=flmid>
		<span class=lbl1>Students matching the search phrase.</span><br />
		<table class=bodypanel>
			<tr><th>No.</th><th>Student Name</th><th>Gender</th><th>Year</th><th>GLvl</th><th></th></tr>
			<tr id=row>
				<td>{no}.</td>
				<td>{studentName}</td>
				<td>{gender}</td>
				<td>{year}</td>
				<td>{gradeLevel}</td>
				<td><form class=tight action="" method=post>
					<input type=hidden name="set_student_id" value={studentId} />
					<input style="font-size: xx-small; padding: 0 auto 0 auto;" type=submit value=go />
					</form>
				</td>
			</tr>
		</table>
	</div>
<!-- /found list -->
	<div class=flend></div>

</div>
<!--
	<br />
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;or<br />
	<br />

<span class=lbl1>Click on a student name below</span><br />
<br />
<div id=tab1>

	<div class=flbeg>
		<span class=lbl1>FRESHMEN<br />
		{freshmen_list}
		</span>
	</div>

	<div class=flmid>
		<span class=lbl1>SOPHOMORES<br />
		{sophomores_list}
		</span>
	</div>

	<div class=flmid>
		<span class=lbl1>JUNIORS<br />
		{juniors_list}
		</span>
	</div>

	<div class=flmid>
		<span class=lbl1>SENIORS<br />
		{seniors_list}
		</span>
	</div>

	<div class=flend></div>

</div>
-->