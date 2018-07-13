{save_status_message}

<!-- new incident form -->
<div class=bodypanel>

	<div style="float: right;">
		<input type=button value=Save onClick="javascript:document.newincident.submit();" />
	</div>
	<div style="float: left;">
		<input type=button value="Cancel" onClick="location.href='?{main_back_link}'" />
	</div>

	<center>
		<span class=lbl2>N E W &nbsp;&nbsp; I N C I D E N T &nbsp;&nbsp; E N T R Y</span>
	</center>

	<div style="clear: both;"></div>

	<br />

	<form name=newincident action="" method=post>
		<input type=hidden name=action value="saveIncident" />
		<input type=hidden name=incidentId value={incidentId} />
		<input type=hidden name=studentId value={studentId} />
		<span class=lbl1>Student:</span>
		<select name=studentId>
			<option value="">-- select --</option>
			{stuid_selopts}
		</select>
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Incident Date</span><input type=text name=incidentDate size=10 />
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Time</span><input type=text name=incidentTime size=6 />
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Location: </span><input type=text name=location /><br />
		<div class=flend></div>
		<br />
		<span class=lbl1>Code: </span><input type=text name=code size=10 />
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
		<span class=lbl1>Notes: </span><br /><textarea name=notes style="width: 100%; height: 4em;">{notes}</textarea><br />
	</form>

</div>