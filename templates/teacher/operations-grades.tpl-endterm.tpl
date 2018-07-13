	<div style="float: left; margin-right: 1em;">
		<table id=form_gradeentry class=bodypanel>
			<thead>
				<tr>
					<th colspan=2>Student</th>
					<th colspan=4 style="text-align: center;">
						{qtr} Quarter {term}
					</th>
				</tr>
				<tr>
					<th>Id</th>
					<th>Name</th>
					<th>score</th>
					<th>ltr grade</th>
					<th>absence</th>
					<th>behavior</th>
				</tr>
			</thead>
			<form name=form_grades action="?{back_menu_link}" method=post>
			<input type=hidden name=classId value="{classId}" />
			<input type=hidden name=form_id value="{form_id}" />
			<tbody>
				<tr id=row>
					<td style="width: 1px; white-space: nowrap;">{studentId}</td>
					<td style="width: 1px; white-space: nowrap;">{studentName}</td>
					<td><input type=text name=students[{studentId}][score] value="{score}" size=5 /></td>
					<td><input type=text name=students[{studentId}][ltrgrade] value="{letter}" size=5 /></td>
					<td><input type=text name=students[{studentId}][absence] value="{absence}" size=5 /></td>
					<td><input type=text name=students[{studentId}][behavior] value="{behavior}" size=5 /></td>
				</tr>
			</tbody>
			</form>
		</table>
	</div>
	<div style="float: left; width: 300px;">
		<p class=lbl1>Student Scores:<br />Enter the student scores.</p>
		<p class=lbl1>Letter Grades:<br />Enter the letter grade. The letter grade is generated from the grading scale if it is empty.</p>
		<p class=lbl1>Absence:<br />Enter the absence counts. If you used the system's attendance module, the absence counts are pulled from there.</p>
		<p class=lbl1>Behavior:<br />Enter the behavior ratings.</p>

		<p class=lbl1 style="color: orange;">Don't forget to save.</p>

		<span style="font-size: x-small; color: lightblue;">
			[ <a style="font-size: x-small; color: lightblue; text-decoration: none;" href="?{back_menu_link}">cancel</a> ]</span>
		<span style="font-size: x-small; color: lightblue;">
			[ <a style="font-size: x-small; color: lightblue; text-decoration: none;" href="javascript:document.form_grades.submit()">save</a> ]</span>
		<span style="font-size: x-small; color: lightblue;">
			[ <a style="font-size: x-small; color: lightblue; text-decoration: none;" href="print/print.php?form=gradesheet&class={classId}" target="_blank">print</a> ]</span>

	</div>
	<div style="clear: both;"></div>