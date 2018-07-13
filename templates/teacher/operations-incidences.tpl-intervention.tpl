{save_status_message}

<div class=bodypanel>
	<center>
		<span class=lbl2>I N T E R V E N T I O N S</span>
		&nbsp;&nbsp;
		<span class=lbl1>for incident id </span>
		<span class=lbl2>{incidentId}</span>
		<br />
		<span class=lbl1>{stuid} </span>
		<span class=lbl2>{studentName}, </span>
		<span class=lbl2>{incidentDate}, </span>
		<span class=lbl2>{location}, </span>
		<span class=lbl2>{incidentCategory}</span>
		<br />
		<span class=lbl2>{incidentDescription}</span>
		<br />
		<span class=lbl1>Referred To: </span>
			<span class=lbl2>{referredTo}</span>
		&nbsp;&nbsp;
		<span class=lbl1>Referred Date: </span>
			<span class=lbl2>{referredDate}</span>
	</center>

	<table class=bodypanel>
		<thead>
			<tr>
				<th>No.</th>
				<th>Code</th>
				<th>Intervention</th>
				<th>Responsible</th>
				<th>Date</th>
				<th>Duration</th>
				<th>Status</th>
				<th><button><a style="text-decoration: none; color: black; font-size: x-small" href="?{new_iid_link}">+</a></th>
			</tr>
		</thead>
		<tbody>
			<tr id=row>
				<td>{no.}.</td>
				<td>{actionCode}</td>
				<td>{description}</td>
				<td>{actionBy}</td>
				<td>{actionDate}</td>
				<td>{duration}</td>
				<td>{actionCategory}</td>
				<td><a style="text-decoration: none; font-size: x-small; font-weight: bold;" href="">&nbsp;&nbsp;>&nbsp;</a></td>
			</tr>
		</tbody>
	</table>
</div>

<!-- intervention form -->
<br />

<div class=bodypanel>

	<div style="float: right;">
		<input type=button value="Save" />
	</div>
	<div style="float: left;">
		<input type=button value="Cancel" />
	</div>

	<center>
		<span class=lbl2>
			Enter New Intervention
		</span>
	</center>
	<div style="clear: both;"></div>

	<center>
	<span class=lbl1>Code: </span>
		<input type=text name=code value="{code}" size=10 />
	<span class=lbl1>Intervention: </span>
		<input type=text name=intervention value="{intervention}" />
	<span class=lbl1>Responsible: </span>
		<input type=text name=responsible value="{responsible}" />
	<br />
	<span class=lbl1>Date: </span>
		<input type=text name=date value="{date}" size=10 />
	<span class=lbl1>Duration: </span>
		<input type=text name=duration value="{duration}" />
	<span class=lbl1>Status: </span>
		<input type=text name=status value="{status}" />

	</center>
</div>
<!-- /intervention form -->