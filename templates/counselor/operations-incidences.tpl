<form class=tight action="" method=get >
	{getpre}
	<span class=lbl1>Student Name:</span>
	<select name=stuid onChange=submit()>
		<option> - - - </option>
		{selopts_students}
	</select>
</form>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<span class=lbl1>sort by code: <input type=text value="not in database" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<span class=lbl1>filter by code: <input type=text value="not in database" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
{save_status_message}
<br />

<!-- form -->
<div class=bodypanel>

	<form name=submitNote class=tight action="" method=post>
		<input type=hidden name=date value={date} />
		<input type=hidden name=statusId value={statusId} />
		<input type=hidden name=studentId value={studentId} />
		<div style="float: right;">
			<input type=button value=save onClick="javascript:document.submitNote.submit();" />
		</div>
		<input type=button value=back onClick="location.href='?{xy13t1t2}{backlink}'" />
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>{stuid}</span><span class=lbl2> {studentName} &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>{id}</span><span class=lbl2> {date}</span><br />
		<div class=flend></div>
		<br />
		<span class=lbl1>Type: </span><input type=text name=type value="{type}" size=40 />&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Reason: </span><input type=text name=reason value="{reason}" size=60 /><br />
		<br />
		<span class=lbl1>Notes: </span><input type=text name=notes value="{notes}" size=120 /><br />
		<br />
		<span class=lbl1>Incident Code: </span><input type=text name=code value="{Not In Database}" />
			<span class=lbl1>Incident types are pre-listed and coded.<br />
		<span class=lbl1>Referred By: </span><input type=text name=referer value="{Not In Database}" />
			<span class=lbl1>Who (teacher, counselor, staff, etc) initiated this report<br />
		<span class=lbl1>Location: </span><input type=text name=location value="{Not In Database}" />
			<span class=lbl1>Where did the incident take place?<br />
		<span class=lbl1>Current Status: </span><input type=text name=currentStatus value="{Not In Database}" />
			<span class=lbl1>One? word description of student status after each [escalating] intervention<br />
	</form>

	<br /><br />

	<span class=lbl1>LIST AND STATUS OF INTERVENTIONS</span>&nbsp;&nbsp;&nbsp;
	<span class=lbl1>This does not exist, needs to be constructed.<br />
	<table class=bodypanel>
		<thead>
			<tr><th>Code</th><th>Intervention</th><th>Responsible</th><th>Start Date</th><th>End Date</th><th>Status</th></tr>
		</thead>
		<tbody>
			<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></tr>
			<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></tr>
			<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></tr>
			<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></tr>
			<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></tr>
			<tr><td>&nbsp;</td><td></td><td></td><td></td><td></td><td></td></tr>
		</tbody>
	</table>

</div>
<!-- /form -->

<!-- list -->
<div class=bodypanel>
	<div style="float: right;">
		<input type=button value="+" onClick="location.href='?{xy13t1t2}&stuid={stuid}&id=new'" />
	</div>
	<span class=lbl2>List of notes for &nbsp;&nbsp; <strong>{studentName}</strong></span><br />
	<table class=bodypanel>
		<thead>
			<tr><th>Id</th><th>Date</th><th>Type</th><th>Reason</th><th>Notes</th></tr>
		</thead>
		<tbody>
			<tr id=row><td><a href="?{xy13t1t2}&stuid={stuid}&id={statusId}">{statusId}</a></td><td>{date}</td><td>{type}</td><td>{reason}</td><td>{notes}</td></tr>
		</tbody>
	</table>
</div>
<!-- /list -->

<!-- list recent -->
<div class=bodypanel>
	<span class=lbl1>LIST OF NOTES BY RECENT DATE</span><br />
	<table class=bodypanel>
		<thead>
			<tr><th>Id</th><th>studentId</th><th>studentName</th><th>Date</th><th>Type</th><th>Reason</th><th>Notes</th></tr>
		</thead>
		<tbody>
			<tr id=row><td><a href="?{xy13t1t2}&id={statusId}">{statusId}</a></td><td>{studentId}</td><td>{studentName}</td><td>{date}</td><td>{type}</td><td>{reason}</td><td>{notes}</td></tr>
		</tbody>
	</table>

</div>
<!-- /list recent -->