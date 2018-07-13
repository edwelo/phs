<div class=bodypanel>
	<span class=lbl1>List of Classes</span><br />
	<table class=bodypanel>
		<thead>
			<tr><th>Report Name</th><th>Description</th><th></th></tr>
		</thead>
		<tbody>
			<tr>
				<td>Data Download</td>
				<td>
					{teacherName}: Download Your Data.
				</td>
				<td align=right><a href="?{hrefpre}&r=Data Download">&nbsp;&nbsp;<b>></b>&nbsp;</a>
			</tr>
			<tr>
				<td>Class Grade Sheet Report</td>
				<td>
					{teacherName}: Choose a class. &nbsp;
					<form style="margin-bottom: 0px;" name=frm_gradesheet action="print/print.php" target="_blank" method=get>
						<input type=hidden name=report value="gradesheet" />
						Course:
						<select name=classId>
							<option></option>
							{classId_selopts}
						</select>
						&nbsp;&nbsp;
						Term:
						<select name=term>
							<option></option>
							<option value="q1m">1st Quarter Mid Term</option>
							<option value="q1e">1st Quarter Grades</option>
							<option value="q2m">2nd Quarter Mid Term</option>
							<option value="q2e">2nd Quarter Grades</option>
						</select>
					</form>
				</td>
				<td align=right><a href="javascript:document.frm_gradesheet.submit()">&nbsp;&nbsp;<b>></b>&nbsp;</a>
			</tr>
			<tr>
				<td>Grade Sheet Completion</td>
				<td>
					Shows completion of the grade sheets for every course
				</td>
				<td align=right><a href="?{hrefpre}&r=Grade Completion">&nbsp;&nbsp;<b>></b>&nbsp;</a>
			</tr>
		</tbody>
	</table>
</div>