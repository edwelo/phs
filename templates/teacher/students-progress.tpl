<!-- student list -->
<div class=bodypanel>
	<table class=bodypanel>
		<caption>
			<span class=lbl2>Progress Completion Indicators</span>
		</caption>
		<thead>
			<tr>
				<th>No.</th><th>studentName</th><th>grade</th><th>course</th><th>q1score</th><th>q2score</th><th>incidenceCount</th><th>incidenceStatus</th><th>enrollStatus</th><th width=40>&nbsp;</th>
			</tr>
		</thead>
		<tbody>
			<tr id=row><td>{no.}.</td><td>{studentName}</td><td align=center>{grade}</td><td>{course}</td><td align=center>{q1score}</td><td align=center>{q2score}</td><td>{incidenceCount}</td><td>{incidenceStatus}</td><td>{enrollStatus}</td><td align=right><a href="?{xy13t1t2}&stuid={studentId},{departmentId}">>&nbsp;</a></td></tr>
		</tbody>
	</table>
</div>
<!-- /student list -->
<!-- student form -->
<div class=bodypanel_light>
	<!--<div style='float: right;'><img src='../data/phs/stupics/{picName}.jpg' height=128 width=128 /></div>-->
	<div style='float: right;'><img src='data/phs/stupics/pic.jpg' height=64 width=64 /></div>

	<div style='float: left;'>
		<span class=lnk1>[ <a href='?{xy13t1t2}'>back</a> ]</span>&nbsp;&nbsp;&nbsp;
		<span style='font-size: small;'>{studentId}</span> <span style='font-weight: bold; font-size: x-large;'>{studentName}</span>
		<br />
		<span class=lbl1>gender:</span> <span class="txtspan1">{gender}</span>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>age:</span> <span class="txtspan1">{currentAge}</span>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>current level:</span> <span class="txtspan1">{currentLevel}</span>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>GPA:</span> <span class="txtspan1">{gpa}</span>
		<br />
		<span class=lbl1>Fails:</span> <span class="txtspan1">{fails}</span>
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Repeats:</span> <span class="txtspan1">{repeats}</span>
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Incidences:</span> <span class="txtspan1">{incidences}</span>
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Status:</span> <span class="txtspan1">{status}</span>
	</div>
	<div class='flend'></div>
</div>

<br />

<table>
	<tr valign=top>
		<td>
			<div class=bodypanel>
				<table class=bodypanel>
					<caption>
						<span class=lbl2>Departmental Performance</span>
					</caption>
					<tr>
						<th>Course</th><th>Year.Sem</th><th>Q1Score</th><th>Q2Score</th><th>SemScore</th><th>Comments</th>
					</tr>
					<tr id=row_deptinfo>
						<td>{courseName}</td><td>{yrsem}</td><td>{q1score}</td><td>{q2score}</td><td>{semscore}</td><td>{comments}</td>
					</tr>
				</table>
			</div>
		</td>
		<td>
			<div class=bodypanel>
				<table class=bodypanel>
					<caption><span class=lbl2>Other Tests</span></caption>
					<tr><th>Test</th><th>Score</th><th>Comments</th></tr>
					<tr><td>PHS Math Placement</td><td>{cp1}</td><td>{cs1}</td></tr>
					<tr><td>PAT 10th Grade</td><td>{cp2}</td><td>{cs2}</td></tr>
					<tr><td>PAT 12th Grade</td><td>{cp3}</td><td>{cs3}</td></tr>
					<tr><td>SAT10</td><td>{cp4}</td><td>{cs4}</td></tr>
					<tr><td>SAT</td><td>{cp4}</td><td>{cs4}</td></tr>
					<tr><td>TOEFL</td><td>{cp4}</td><td>{cs4}</td></tr>
				</table>
			</div>
		</td>
	</tr>
	<tr valign=top>
		<td>
			<div class=bodypanel>
				<table class=bodypanel>
					<caption>
						<span class=lbl2>Attendance</span>
					</caption>
					<tr>
						<th>Attendance Graph</th>
					</tr>
					<tr>
						<td>
							{chart_html}
						</td>
					</tr>
				</table>
			</div>
		</td>
		<td>

		</td>
	</tr>
</table>
<!-- /student form -->