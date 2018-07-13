<div class=bodypanel>
	<div style="float: right;">
		<button onClick="location.href='?{hrefpre}&id=new'">+</button>
	</div>
	<div>
		<center>
			<span class=lbl2>L I S T &nbsp;&nbsp; O F &nbsp;&nbsp; I N C I D E N C E S</span><br />
		</center>
	</div>
	<div style="clear: both;"></div>
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
</div>