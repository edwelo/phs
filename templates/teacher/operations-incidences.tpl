{save_status_message}

<div class=bodypanel>

	<div style="float: right;">
		<form style="margin-bottom: 0; display: inline;" action="" method=post>
			<input type=hidden name=id value={incidentId} />
			<input type=submit value=Edit />
		</form>
	</div>
	<span class=lbl2>
		I N C I D E N C E &nbsp; R E C O R D &nbsp; <span class=lbl1>{id}</span>
	</span>
	&nbsp;&nbsp;&nbsp;
	<span class=lbl1>{stuid}</span>
		<span class=lbl2> {studentName}</span>
		&nbsp;&nbsp;&nbsp;
	<span class=lbl1>Incident Date:</span>
		<span class=lbl2> {incidentDate}</span>
	<br />
	<center>
		<span class=lbl1>Incident Time:</span>
			<span class=blacktext> {incidentTime}</span>
			&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Location:</span>
			<span class=blacktext> {location}</span>
	</center>

	<p style="margin: 4px 0 4px 0;">
		<span class=lbl1>Code: </span>
			<span class=blacktext>{code}</span>
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Category: </span>
			<span class=blacktext>{category}</span>
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Reported By: </span>
			<span class=blacktext>{reportedBy}</span>
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl1>Date: </span>
			<span class=blacktext>{incidentDate}</span>
	</p>

	<p style="margin: 4px 0 4px 0;">
		<span class=lbl1>Description: </span>
			<span class=blacktext>{description}</span>
	</p>

	<span class=lbl1>Referred To: </span>
		<span class=blacktext>{referredTo}</span>
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
	<span class=lbl1>Referred Date: </span>
		<span class=blacktext>{referredDate}</span>
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
	<span class=lbl1>Current Status: </span>
		<span class=blacktext>{status}</span>

	<p style="margin: 4px 0 4px 0;">
		<span class=lbl1>Notes: </span>
			<span class=blacktext>{notes}</span>
	</p>

	<br />
	<center>
		<button onClick="location.href='?{hrefpre}&iid='">Go To Interventions</button>
	</center></div>
