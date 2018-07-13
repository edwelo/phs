<!-- form -->
<div class=bodypanel>

	<form name=submitNote class=tight action="" method=post>
		<input type=hidden name=activityId value="{activityId}" />
		<div style="float: right;">
			<input type=button value=save onClick="javascript:document.submitNote.submit();" />
		</div>
		<input type=button value=back onClick="location.href='?{xy13t1t2}'" />
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>ACTIVITIES FORM</span>
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>ID: {activityId}</span>
		&nbsp;&nbsp;&nbsp;
		<span class=lbl1>{save_status_message}</span><br />
		<div class=flend></div>
		<br />
		<span class=lbl1>Date: </span><input type=text name=date value="{date}" size=12 />&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Type: </span><input type=text name=type value="{type}" size=25 />&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Title: </span><input type=text name=title value="{title}" size=60 /><br />
		<br />
		<span class=lbl1>Description: </span><input type=text name=description value="{description}" size=120 /><br />
		<br />
		<span class=lbl1>Notes: </span><input type=text name=notes value="{notes}" size=120 /><br />
		<br />
		<span class=lbl1>Total Hours: </span><input type=text name=ttlhours value="{ttlhours}"  size=5/>&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Location: </span><input type=text name=location value="{location}" />&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Total Participants: </span><input type=text name=ttlparticipants value="{ttlparticipants}" size=5 /><br />
	</form>

</div>
<!-- /form -->

<!-- list recent -->
<div class=bodypanel>
	<div style="float: right;">
		<input type=button value="+" onClick="location.href='?{xy13t1t2}&id=new'" />
	</div>
	<span class=lbl1>LIST OF ACTIVITIES BY RECENT DATE</span><br />
	<table class=bodypanel>
		<thead>
			<tr><th>Id</th><th>Date</th><th>Title</th><th>Location</th><th>Hours</th><th>Participants</th></tr>
		</thead>
		<tbody>
			<tr id=row><td><a href="?{xy13t1t2}&id={activityId}">{activityId}</a></td><td>{date}</td><td>{title}</td><td>{location}</td><td>{ttlhours}</td><td>{ttlparticipants}</td></tr>
		</tbody>
	</table>

</div>
<!-- /list recent -->