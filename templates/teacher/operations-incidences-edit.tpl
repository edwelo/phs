{save_status_message}

<!-- incident edit form -->
<div class=bodypanel>

	<div style="float: right;">
		<input type=button value=Save onClick="javascript:document.updateincident.submit();" />
	</div>
	<button><a style="text-decoration: none; color: black;" href="">cancel</a></button>
	&nbsp;
	<span class=lbl2>
		I N C I D E N C E &nbsp; R E C O R D &nbsp; E D I T
	</span>
	&nbsp;&nbsp;
	<span class=lbl1>{stuid}</span><span class=lbl2> {studentName}
	&nbsp;&nbsp;
	<span class=lbl1>{id}</span><span class=lbl2> {incidentDate}</span><br />
	<div class=flend></div>

	<form name=updateincident action="" method=post>
		<input type=hidden name=action value="saveIncident" />
		<input type=hidden name=incidentId value={incidentId} />
		<input type=hidden name=studentId value={studentId} />
		<input type=hidden name=incidentDate value={incidentDate} />
		<center>
			<span class=lbl1>Incident Time: </span><input type=text name=incidentTime value="{incidentTime}" size=5 />
			<span class=lbl1>Location: </span><input type=text name=location value="{location}" size=15 />
		</center>
		<br />
		<span class=lbl1>Code: </span><input type=text name=code value="{code}" size=10 />
		<span class=lbl1>Category: </span>
			<select name=category>
				<option value="">-- select --</option>
				{incidentCategory_selopts}
			</select>
		<span class=lbl1>Reported By: </span><input type=text name=reportedBy value="{reportedBy}" />
		<span class=lbl1>Date: </span><input type=text name=reportedDate value="{reportedDate}" size=10 />
		<br />
		<span class=lbl1>Description: </span><br /><textarea name=description style="width: 100%; height: 4em;">{description}</textarea><br />
		<br />
		<span class=lbl1>Referred To: </span>
			<select name=referredTo>
				<option value="">-- select --</option>
				<option>Counselor</option>
				<option>Vice Principal</option>
				<option>Principal</option>
			</select>
		<span class=lbl1>Referred Date: </span><input type=text name=referredDate value="{referredDate}" size=10 />
		<span class=lbl1>Current Status: </span>{status}<br />
		<span class=lbl1>Notes: </span><br /><textarea name=notes style="width: 100%; height: 4em;">{notes}</textarea><br />
	</form>

</div>