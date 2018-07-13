		<thead>
			<tr>
				<th>Student</th>
				<th colspan=3 style="text-align: left;">
					{qtr} Quarter Grade
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<span style="font-size: x-small; color: lightblue;">
						[ <a style="font-size: x-small; color: lightblue; text-decoration: none;" href="?{back_menu_link}">cancel</a> ]</span>
					<span style="font-size: x-small; color: lightblue;">
						[ <a style="font-size: x-small; color: lightblue; text-decoration: none;" href="javascript:document.form_grades.submit()">save</a> ]</span>
				</th>
			</tr>
		</thead>
		<form name=form_grades action="?{back_menu_link}" method=post>
		<input type=hidden name=classId value="{classId}" />
		<input type=hidden name=form_id value="{form_id}" />
		<tbody>
			<tr id=row>
				<td style="width: 1px; white-space: nowrap;">{studentName}</td>
				<td>
					<input type=text name=d1[{studentId}] value="{q1e}" size=5 />
					&nbsp;&nbsp;
					{q1elg}
					&nbsp;&nbsp;
					{q1eabs}
				</td>
			</tr>
		</tbody>
		</form>
