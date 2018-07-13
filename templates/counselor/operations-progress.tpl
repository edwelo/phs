<!-- list -->

<form class=tight action="" method=get >
	{getpre}
	<span class=lbl1>Grouping By:</span>
	<select name=stuid onChange=submit()>
		<option> - - - </option>
		<option>Grade Level</option>
		<option>Class</option>
		<option>At Risk</option>
	</select>
</form>

<br />

<div class=bodypanel>
	<table class=bodypanel>
		<caption>
			<span class=lbl2>Progress Completion Indicators</span>
		</caption>
		<thead>
			<tr>
				<th>studentId</th><th>studentName</th><th>gradeLevel</th><th>Earned Credits</th><th>GPA</th><th>Career Interest</th><th>College Search</th><th>FAFSA</th><th>Tests</th><th>College Application</th>
			</tr>
		</thead>
		<tbody>
			<tr id=row><td><a href="?{xy13t1t2}&stuid={studentId}">{studentId}</a></td><td>{studentName}</td><td>{gradeLevel}</td><td>{earnedCredits}</td><td>{gpa}</td><td>{Career Interest}</td><td>{College Search}</td><td>{FAFSA}</td><td>{Tests}</td><td>{College Application}</td></tr>
		</tbody>
	</table>
</div>

<!-- /list -->
<!-- form -->
<div class=bodypanel_light>
	<!--<div style='float: right;'><img src='../data/phs/stupics/{picName}.jpg' height=128 width=128 /></div>-->
	<div style='float: right;'><img src='data/phs/stupics/pic.jpg' height=128 width=128 /></div>

	<div style='float: left;'>
		<span class=lnk1>[ <a href='?{xy13t1t2}'>back</a> ]</span>&nbsp;&nbsp;&nbsp;
		<span style='font-size: small;'>{studentId}</span> <span style='font-weight: bold; font-size: x-large;'>{studentName}</span>
		<br />
		<br />
		<span class=lbl1>gender:</span> <span class="txtspan1">{gender}</span>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>age:</span> <span class="txtspan1">{currentAge}</span>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>current level:</span> <span class="txtspan1">{currentLevel}</span>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>GPA:</span> <span class="txtspan1">{gpa}</span>
		<br />
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

<div class=bodypanel>
	<table class=bodypanel>
		<caption>
			<span class=lbl2>GENERAL - Club or Extra-Curricular Activities</span>
		</caption>
		<tr>
			<th>Club/Activity Name</th><th>Club/Activity Purpose</th><th>Start</th><th>End</th><th>Notes</th>
		</tr>
		<tr>
			<td>{cn1}</td><td>{cp1}</td><td>{cs1}</td><td>{ce1}</td><td>{n1}</td>
		</tr>
		<tr>
			<td>{cn2}</td><td>{cp2}</td><td>{cs2}</td><td>{ce2}</td><td>{n2}</td>
		</tr>
		<tr>
			<td>{cn3}</td><td>{cp3}</td><td>{cs3}</td><td>{ce3}</td><td>{n3}</td>
		</tr>
		<tr>
			<td>{cn4}</td><td>{cp4}</td><td>{cs4}</td><td>{ce4}</td><td>{n4}</td>
		</tr>
	</table>
</div>

<br />

<div class=bodypanel>
	<table class=bodypanel>
		<caption>
				<div style="float: right;">
				<span style="font-size: small; color: #abc;">{ac1}</span>
			</div>
			<div style="float: left;">
				<span style="font-size: small; color: #abc;">{cc1}</span>
			</div>
		<span class=lbl2>9th GRADE CHECKLIST</span>
			<div class="flend"></div>
		</caption>
		<tr>
			<th colspan=2>&nbsp;</th>
		</tr>
		<tr>
			<td>Basic Career Plan Has Been Started <input type=checkbox />
			</td>
			<td>
				Interest And Aptitude Test Completed <input type=checkbox />
			</td>
		</tr>
		<tr><td>
			Area of Interest Identified <input type=checkbox /> &nbsp;&nbsp;&nbsp;
			<span class=lbl1a>Cluster Name:</span> <input type=text size=10 />
		</td>
		<td>&nbsp;</td></tr>
	</table>
</div>

<br />

<div class=bodypanel>
	<table class=bodypanel>
		<caption>
			<div style="float: right;">
				<span style="font-size: small; color: #abc;">{ac2}</span>
			</div>
			<div style="float: left;">
				<span style="font-size: small; color: #abc;">{cc2}</span>
			</div>
			<span class=lbl2>10th GRADE CHECKLIST</span>
			<div class="flend"></div>
		</caption>
		<tr>
			<th colspan=2>&nbsp;</th>
		</tr>
		<tr>
			<td>Basic Career Plan Has Been Updated &nbsp;&nbsp;&nbsp;<input type=checkbox />
			</td>
			<td>
				Tests and Assessments &nbsp;&nbsp;&nbsp;&nbsp;
				<span class=lbl1a>PAT</span> <input type=text size=4 /> &nbsp;&nbsp;&nbsp;
				<span class=lbl1a>SAT10</span> <input type=text size=4 />
			</td>
		</tr>
		<tr>
			<td colspan=2>
				<div style="font-size: x-small;">
					Cluster Completion<br />
					<table style="border-collapse: collapse;">
						<tr>
							<td style="font-size: x-small;">
								<input type=checkbox /> Agricultural & Natural Resources<br />
								<input type=checkbox /> Architecture & Construction<br />
								<input type=checkbox /> Arts, A/V Technology & Communications<br />
								<input type=checkbox /> Business & Administration<br />
							</td>
							<td style="font-size: x-small;">
								<input type=checkbox /> Education & Training<br />
								<input type=checkbox /> Finance<br />
								<input type=checkbox /> Government & Public Administration<br />
								<input type=checkbox /> Health Science<br />
							</td>
							<td style="font-size: x-small;">
								<input type=checkbox /> Hospitality & Tourism<br />
								<input type=checkbox /> Human Services <br />
								<input type=checkbox /> Information Technology <br />
								<input type=checkbox /> Law & Public Safety<br />
							</td>
							<td style="font-size: x-small;">
								<input type=checkbox /> Manufacturing<br />
								<input type=checkbox /> Marketing, Sales & Service<br />
								<input type=checkbox /> Scientific Research/Engineering<br />
								<input type=checkbox /> Transportation, Distribution & Logistics<br />
							</td>
						</tr>
					</table>
				</div>
			</td>
		</tr>
		<tr><td>
			Career Academy Selection &nbsp;&nbsp;&nbsp;&nbsp;
			<span class=lbl1a>Academy:</span> <input type=text size=10 /> &nbsp;&nbsp;&nbsp;
			<span class=lbl1a>Cluster:</span> <input type=text size=10 />
		</td><td>
			College Identification Activity &nbsp; <input type=checkbox />
		</td></tr>
	</table>
</div>

<br />

<div class=bodypanel>
	<table class=bodypanel>
		<caption>
			<div style="float: right;">
				<span style="font-size: small; color: #abc;">{ac3}</span>
			</div>
			<div style="float: left;">
				<span style="font-size: small; color: #abc;">{cc3}</span>
			</div>
			<span class=lbl2>11th GRADE CHECKLIST</span>
			<div class="flend"></div>
		</caption>
		<tr>
			<th colspan=2>&nbsp;</th>
		</tr>
		<tr>
			<td>Basic Career Plan Has Been Updated <input type=checkbox /></td>
			<td>Job Shadow Completed <input type=checkbox /></td>
		</tr>
		<tr>
			<td>College Search Completed <input type=checkbox /></td>
			<td>SAT10 Score &nbsp; <input type=text size=4 /></td>
		</tr>
	</table>
</div>

<br />

<div class=bodypanel>
	<table class=bodypanel>
		<caption>
			<div style="float: right;">
				<span style="font-size: small; color: #abc;">{ac4}</span>
			</div>
			<div style="float: left;">
				<span style="font-size: small; color: #abc;">{cc4}</span>
			</div>
			<span class=lbl2>12th GRADE CHECKLIST</span>
			<div class="flend"></div>
		</caption>
		<tr>
			<th colspan=3>&nbsp;</th>
		</tr>
		<tr><td>
				Basic Career Plan Has Been Updated <input type=checkbox />
			</td><td>
				Practicum Completed <input type=checkbox />
			</td><td>
				FAFSA Completed <input type=checkbox />
		</td></tr>
		<tr><td>
				Tests Completed &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<span class=lbl1a>TOEFL</span> <input type=text size=4 />&nbsp;&nbsp;&nbsp;
				<span class=lbl1a>SAT<span> <input type=text size=4 />&nbsp;&nbsp;&nbsp;
				<span class=lbl1a>PAT</span> <input type=text size=4 />
			</td><td colspan=2>
				Others Completed &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<span class=lbl1a>SWEP</span> <input type=checkbox />&nbsp;&nbsp;&nbsp;
				<span class=lbl1a>SLCAI<span> <input type=checkbox />&nbsp;&nbsp;&nbsp;
				<span class=lbl1a>Service Learning</span> <input type=checkbox />
		</td></tr>
	</table>
</div>
<!-- /form -->