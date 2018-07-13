<div class=bodypanel>
	<span class=lbl1>Set School Quarters Dates</span><br /><br />
	
	<div id=list>
		Quarters and Midterm Dates
		&nbsp;&nbsp;&nbsp;
		<form class=tight action="" method=post>
			<span class=lbl1>To add or edit, enter SY: </span>
			<input type=text name=sy size=6 />
			<input type=submit value=go />
		</form>
		<br />
		{content}
		<span class=lbl1>
			Column names ... s1/s2 = semester 1/2, q1/q2 = quarter 1/2, s/m/e = start/mid/end
		</span>
	</div>
	
	<center>
	<div id=form style="display: none;">
		SY{qSY} Quarters and Midterm Dates Edit/Entry
		&nbsp;&nbsp;&nbsp;
		<button onClick="location.href=''">Cancel</button>
		<button onClick="javascript:document.datesSave.submit()">Save</button>
		<form class=tight name=datesSave action="" method=post>
			<input type=hidden name=sy value={qSY} />
			<table class=bodypanel style="width: auto;">
				<tr><td>s1q1s</td><td><input type=text name=s1q1s value="{s1q1s}" size=12 /></td></tr>
				<tr><td>s1q1m</td><td><input type=text name=s1q1m value="{s1q1m}" size=12 /></td></tr>
				<tr><td>s1q1e</td><td><input type=text name=s1q1e value="{s1q1e}" size=12 /></td></tr>
				<tr><td>s1q2s</td><td><input type=text name=s1q2s value="{s1q2s}" size=12 /></td></tr>
				<tr><td>s1q2m</td><td><input type=text name=s1q2m value="{s1q2m}" size=12 /></td></tr>
				<tr><td>s1q2e</td><td><input type=text name=s1q2e value="{s1q2e}" size=12 /></td></tr>
				<tr><td>s2q1s</td><td><input type=text name=s2q1s value="{s2q1s}" size=12 /></td></tr>
				<tr><td>s2q1m</td><td><input type=text name=s2q1m value="{s2q1m}" size=12 /></td></tr>
				<tr><td>s2q1e</td><td><input type=text name=s2q1e value="{s2q1e}" size=12 /></td></tr>
				<tr><td>s2q2s</td><td><input type=text name=s2q2s value="{s2q2s}" size=12 /></td></tr>
				<tr><td>s2q2m</td><td><input type=text name=s2q2m value="{s2q2m}" size=12 /></td></tr>
				<tr><td>s2q2e</td><td><input type=text name=s2q2e value="{s2q2e}" size=12 /></td></tr>
			</table>
		</form>
	<div>
	</center>
</div>