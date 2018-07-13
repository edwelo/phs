<form class=tight action="" method=get >
	{getpre}
	<span class=lbl1>Student Name:</span>
	<select name=stuid onChange=submit()>
		<option> - - - </option>
		{selopts_students}
	</select>
</form>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
{save_status_message}
<br />

<!-- form -->
<div class=bodypanel>

	<form name=submitNote class=tight action="" method=post>
		<input type=hidden name=noteid value="{noteid}" />
		<div style="float: right;">
			<input type=button value=save onClick="javascript:document.submitNote.submit();" />
		</div>
		<input type=button value=back onClick="location.href='?{xy13t1t2}{backlink}'" />
		&nbsp;&nbsp;&nbsp;
		<span class=lbl2>{stuid} &nbsp;&nbsp;&nbsp; {studentName} &nbsp;&nbsp;&nbsp; {noteDate}</span><br />
		<div class=flend></div>
		<textarea style="padding: 1em; width: 100%; border-radius: 6px;" name=notes rows=20>{notetext}</textarea>
	</form>

</div>
<!-- /form -->

<!-- list -->
<div class=bodypanel>
	<div style="float: right;">
		<input type=button value="+" onClick="location.href='?{xy13t1t2}&stuid={stuid}&noteid=new'" />
	</div>
	<span class=lbl2>List of notes for &nbsp;&nbsp; <strong>{studentName}</strong></span><br />
	<table class=bodypanel>
		<thead>
			<tr><th>File Name</th><th>Note Date</th></tr>
		</thead>
		<tbody>
			<tr id=row><td><a href="?{xy13t1t2}&stuid={stuid}&noteid={noteId}">{noteId}</a></td><td>{noteDate}</td></tr>
		</tbody>
	</table>
</div>
<!-- /list -->

<!-- list recent -->
<div class=bodypanel>
	<span class=lbl1>LIST OF NOTES BY RECENT DATE</span><br />
	{htmltable}

</div>
<!-- /list recent -->