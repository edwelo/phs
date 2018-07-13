<div class=bodypanel>
	<span class=lbl1>Transfer data from Grades DB to Old DB</span><br /><br />
	
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
	<hr />

	SY<span id="sy">{sy}</span> Semester <span id="sem">{semester}</span> Quarter <span id="qtr">{quarter}</span><br />
	
	<p class=lbl1>Please note that this utility will clear out the student scores and student absences in the old database, and replace them with the scores and student absences from the grades database.</p>
	
	<p class=lbl1>Student scores and absences data for this quarter will be erased and replaced.</p>
	
	<div class=flbeg>
		<table class=bodypanel style="width: auto;">
			<tr><th>DB</th><th>Table</th><th>Stu/Classes</th><th>withScores</th><th>withoutScores</th><th>Matched</th></tr>
			<tr><td>Old DB</td><td>tbl_schedule</td><td>{N0}</td><td>{Ny0}</td><td>{Nn0}</td><td rowspan=2 valign=middle>{Nm0}</td></tr>
			<tr><td>New DB</td><td>tbl_grades</td><td>{N1}</td><td>{Ny1}</td><td>{Nn1}</td></tr>
		</table>
	</div>
	<div class=flmid>
		<table class=bodypanel style="width: auto;">
			<tr><th>DB</th><th>Table</th><th>Students</th><th>Matched</th></tr>
			<tr><td>Old DB</td><td>tbl_enrollment</td><td>{Ne}</td><td rowspan=2 valign=middle>{Nm3}</td></tr>
			<tr><td>New DB</td><td>tbl_grades</td><td>{Ng}</td></tr>
		</table>
	</div>
	<div class=flmid>
		<button>
			<a style="text-decoration: none; color: #f66;" href="javascript:moveToNewDB()">
				Transfer to Old DB
			</a>
		</button>
	</div>
	<div class=flend></div>
</div>