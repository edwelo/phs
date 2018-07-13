<div class="bodypanel">
	<span class=lbl2>Student Incidences</span><br />
	<table class=bodypanel>
		<thead>
			<tr>
				<th>redId</th>
				<th>date</th>
				<th>type</th>
				<th>reason</th>
				<th>length</th>
				<th>notes</th>
			</tr>
		</thead>
		{incidencesTableRows}
	</table>
</div>

<br />

<div class="bodypanel">

	<span class=lbl2>Incident Form</span>

	<br /><br />

	<span class=lbl1>Incident Date:</span>
	&nbsp;
	<input type=text name=incidentDate value="{incidentDate}" size=14 />

	&nbsp;&nbsp;&nbsp;

	<span class=lbl1>Type:</span>
	&nbsp;
	<input type=text name=incidentDate value="{incidentType}" size=30 />

	&nbsp;&nbsp;&nbsp;

	<span class=lbl1>Location:</span>
	&nbsp;
	<input type=text name=incidentLocation value="{incidentLocation}" size=20 />

	<br />
	<br />

	<span class=lbl1>Description</span><br />
	<textarea name=incidentDescription cols=80 rows=4>{incidentDescription}</textarea>

	<br /><br />

	<div class=flbeg>
		<span class=lbl1>Referred To</span><br />
		<input type=text name=incidentDescription value="{incidentDescription}" size=20 />
	</div>

	<div class=flmid>
		<span class=lbl1>Close Date</span><br />
		<input type=text name=incidentDescription value="{incidentDescription}" size=20 />
	</div>

	<div class=flend></div>

	<br />

	<span class=lbl1>Actions Taken</span><br />
	<textarea name=incidentDescription cols=80 rows=4>{incidentDescription}</textarea>

	<br />
</div>