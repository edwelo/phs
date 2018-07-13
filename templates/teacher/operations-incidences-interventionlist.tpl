{save_status_message}

<!-- incident form -->
<div class=bodypanel>

	<form name=submitNote action="" method=post>
		<input type=hidden name=incidentId value={incidentId} />
		<input type=hidden name=studentId value={studentId} />
		<div style="float: right;">
			<input type=button value=Save onClick="javascript:document.submitNote.submit();" />
		</div>
		<input type=button value=Cancel onClick="location.href='?{back_menu_link}'" />
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>{stuid}</span><span class=lbl2> {studentName} &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>{id}</span><span class=lbl2> {incidentDate}</span><br />
		<div class=flend></div>
		<br />
		<span class=lbl1>Code: </span><input type=text name=code value="{Not In Database}" size=15 />
		<span class=lbl1>Category: </span>
			<select name=category>
				<option value="">-- select --</option>
				{incidentCategory_selopts}
			</select>
		<span class=lbl1>Reported By: </span><input type=text name=reportedBy value="{reportedBy}" />
		<span class=lbl1>Date: </span><input type=text name=incidentDate value="{incidentDate}" size=12 />
		<br />
		<span class=lbl1>Description: </span><br /><textarea name=description cols=100 rows=3>{description}</textarea><br />
		<br />
		<span class=lbl1>Location: </span><input type=text name=location value="{location}" />
		<span class=lbl1>Referred To: </span>
			<select name=referredTo>
				<option value="">-- select --</option>
				<option>Counselor</option>
				<option>Vice Principal</option>
				<option>Principal</option>
			</select>
		<span class=lbl1>Referred Date: </span><input type=text name=referredDate value="{referredDate}" size=12 />
		<span class=lbl1>Current Status: </span><input type=text name=currentStatus value="{Not In Database}" />
	</form>

</div>
<br />
<div class=bodypanel>
	<span class=lbl1>LIST AND STATUS OF INTERVENTIONS</span>&nbsp;&nbsp;&nbsp;
	<span class=lbl1>This does not exist, needs to be constructed.<br />
	<table class=bodypanel>
		<thead>
			<tr><th>No.</th><th>Code</th><th>Intervention</th><th>Responsible</th><th>Date</th><th>Duration</th><th>Status</th></tr>
		</thead>
		<tbody>
			<tr id=row><td>{no.}.</td><td>{actionCode}</td><td>{description}</td><td>{actionBy}</td><td>{actionDate}</td><td>{duration}</td><td>{actionCategory}</td></tr>
		</tbody>
	</table>
</div>
<!-- /incident form -->

<!-- intervention list -->
<div class=bodypanel>

	<form name=submitNote action="" method=post>
		<input type=hidden name=incidentId value={incidentId} />
		<input type=hidden name=studentId value={studentId} />
		<div style="float: right;">
			<input type=button value=Save onClick="javascript:document.submitNote.submit();" />
		</div>
		<input type=button value=Cancel onClick="location.href='?{back_menu_link}'" />
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>{stuid}</span><span class=lbl2> {studentName} &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>{id}</span><span class=lbl2> {incidentDate}</span><br />
		<div class=flend></div>
		<br />
		<span class=lbl1>Code: </span><input type=text name=code value="{Not In Database}" size=15 />
		<span class=lbl1>Category: </span>
			<select name=category>
				<option value="">-- select --</option>
				{incidentCategory_selopts}
			</select>
		<span class=lbl1>Reported By: </span><input type=text name=reportedBy value="{reportedBy}" />
		<span class=lbl1>Date: </span><input type=text name=incidentDate value="{incidentDate}" size=12 />
		<br />
		<span class=lbl1>Description: </span><br /><textarea name=description cols=100 rows=3>{description}</textarea><br />
		<br />
		<span class=lbl1>Location: </span><input type=text name=location value="{location}" />
		<span class=lbl1>Referred To: </span>
			<select name=referredTo>
				<option value="">-- select --</option>
				<option>Counselor</option>
				<option>Vice Principal</option>
				<option>Principal</option>
			</select>
		<span class=lbl1>Referred Date: </span><input type=text name=referredDate value="{referredDate}" size=12 />
		<span class=lbl1>Current Status: </span><input type=text name=currentStatus value="{Not In Database}" />
	</form>

</div>
<br />
<div class=bodypanel>
	<span class=lbl1>LIST AND STATUS OF INTERVENTIONS</span>&nbsp;&nbsp;&nbsp;
	<span class=lbl1>This does not exist, needs to be constructed.<br />
	<table class=bodypanel>
		<thead>
			<tr><th>No.</th><th>Code</th><th>Intervention</th><th>Responsible</th><th>Date</th><th>Duration</th><th>Status</th></tr>
		</thead>
		<tbody>
			<tr id=row><td>{no.}.</td><td>{actionCode}</td><td>{description}</td><td>{actionBy}</td><td>{actionDate}</td><td>{duration}</td><td>{actionCategory}</td></tr>
		</tbody>
	</table>
</div>
<!-- /intervention list -->

<!-- list recent -->
<div class=bodypanel>
	<center>
	<span class=lbl2>L I S T &nbsp;&nbsp; O F &nbsp;&nbsp; I N C I D E N C E S</span><br />
	<table class=bodypanel>
		<thead>
			<tr><th>No.</th><th>studentName</th><th>Date :: Type :: Reason :: Notes</th></tr>
		</thead>
		<tbody>
			<tr id=row>
				<td align=right>{no.}.</td>
				<td>{studentName}</td>
				<td><a href="?{xy13t1t2}&id={incidentId}" style="font-size: x-small;">{incidentDate}</a> :: <b>{category}</b> :: {description}</td>
			</tr>
		</tbody>
	</table>
	</center>
</div>
<!-- /list recent -->