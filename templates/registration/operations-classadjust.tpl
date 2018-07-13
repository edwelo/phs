<br />
<span class=alert1>Under Construction. Not Operational Yet.</span><br />

<div class=flbeg>
	<form class=tight action="" method=get>
		{getpre}
		<input type=hidden name=tab value={tab} />
		<span class=lbl1>Teacher: </span>
		<select name=tchrid onChange=submit()>
			<option></option>
			{tchr_selopts}
		</select>
	</form>

	<br />

	<form class=tight action="" method=get>
		{getpre}
		<input type=hidden name=tab value={tab} />
		<input type=hidden name=tchrid value={teacherId} />
		<span class=lbl1>Class: </span>
		<select name=clsid onChange=submit()>
			<option></option>
			{cls_selopts}
		</select>
	</form>

	<br />

	{period} {courseName}, <span class=lbl1>by {teacherName}</span>
	<br />

	<form name=teacherSchedule class=tight action="" method=post>

		<input type=hidden name=teacherId value="{teacherId}" />

		<table class=ct3>
			<tr><th>no</th><th>stuid</th><th>stuname</th><th>glvl</th></tr>
			<tr id=tblrow><td>{no}</td><td>{stuid}</td><td>{stuname}</td><td>{glvl}</td></tr>
		</table>

	</form>
</div>

<div class=flmid style="background: grey;">
	<br />
	&nbsp;&nbsp;>>&nbsp;&nbsp;<br />
	<br />
	&nbsp;&nbsp;>>&nbsp;&nbsp;<br />
	<br />
	&nbsp;&nbsp;>>&nbsp;&nbsp;<br />
	<br />
</div>

<div class=flmid>
	<form class=tight action="" method=get>
		{getpre}
		<input type=hidden name=tab value={tab} />
		<span class=lbl1>Teacher: </span>
		<select name=tchrid onChange=submit()>
			<option></option>
			{tchr_selopts}
		</select>
	</form>

	<br />

	<form class=tight action="" method=get>
		{getpre}
		<input type=hidden name=tab value={tab} />
		<input type=hidden name=tchrid value={teacherId} />
		<span class=lbl1>Class: </span>
		<select name=clsid onChange=submit()>
			<option></option>
			{cls_selopts}
		</select>
	</form>

	<br />

	{period} {courseName}, <span class=lbl1>by {teacherName}</span>
	<br />

	<form name=teacherSchedule class=tight action="" method=post>

		<input type=hidden name=teacherId value="{teacherId}" />

		<table class=ct3>
			<tr><th>no</th><th>stuid</th><th>stuname</th><th>glvl</th></tr>
			<tr id=tblrow><td>{no}</td><td>{stuid}</td><td>{stuname}</td><td>{glvl}</td></tr>
		</table>

	</form>
</div>
<div class=flend></div>