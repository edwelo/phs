<script type="text/javascript">

</script>

<div class=bodypanel>
	<span class=lbl1>Set School Quarters Dates</span><br /><br />
	
	<div id=list>

		School Year:
		<form class=tight action="" method="post">
			<select id="sisYearSel" name="sisYear" style="-webkit-appearance: menulist-button;" onchange="this.form.submit();">
				{sisYrs_selOpts}
			</select>
		</form>
		&nbsp;&nbsp;&nbsp;

		List of <span id="listYear">{listYear}</span> Teachers
		&nbsp;&nbsp;&nbsp;
		<form class=tight action="" method=post>
			<span class=lbl1>To add or edit, enter "new" or teacherId: </span>
			<input type=text name=teacherId size=6 />
			<input type=submit value=go />
		</form>
		<br />
		<table class=bodypanel>
			<tr>
				<th>teacherId</th>
				<th>teacherName</th>
				<th>dept</th>
				<th>homePhone</th>
				<th>workPhone</th>
				<th>role</th>
				<th>persid</th>
				<th align=center>years</th>
				<th align=center>sem 1/2 classes</th>
			</tr>
			<tr id=row>
				<td>{teacherId}</td>
				<td>{firstName} {middleName} {lastName}</td>
				<td>{dept}</td>
				<td>{homePhone}</td>
				<td>{workPhone}</td>
				<td>{role}</td>
				<td>{persid_moe}</td>
				<td align=center>{minSISyr} - {maxSISyr}</td>
				<td align=center>{sem1classes} / {sem2classes}</td>
			</tr>
		</table>
		<span class=lbl1>
			Column names ... s1/s2 = semester 1/2, q1/q2 = quarter 1/2, s/m/e = start/mid/end
		</span>
	</div>

	<center>
		<div id=form style="display: none;">
			<div style="float: left; margin-right: 2em; text-align: left;">
				Departments<br />
				<p style="font-size: small;">{departmentList}</p>
			</div>
			<div style="float: left;">
				Teacher Id# <span id="teacherId">{teacherId}</span> Edit/Entry
				&nbsp;&nbsp;&nbsp;
				<button onClick="location.href=''">Cancel</button>
				<button onClick="javascript:document.teacherSave.submit()">Save</button>
				<form id="teacherEditForm" class=tight name=teacherSave action="" method=post>
					<input type=hidden name=teacherId value='{teacherId}' />
					<table class=bodypanel style="width: auto;">
						<tr><td>departmentId</td><td><input type=text name=departmentId value="{departmentId}" size=20 /></td></tr>
						<tr><td>firstName</td><td><input type=text name=firstName value="{firstName}" size=20 /></td></tr>
						<tr><td>middleName</td><td><input type=text name=middleName value="{middleName}" size=20 /></td></tr>
						<tr><td>lastName</td><td><input type=text name=lastName value="{lastName}" size=20 /></td></tr>
						<tr><td>homePhone</td><td><input type=text name=homePhone value="{homePhone}" size=20 /></td></tr>
						<tr><td>workPhone</td><td><input type=text name=workPhone value="{workPhone}" size=20 /></td></tr>
						<tr><td>extension</td><td><input type=text name=extension value="{extension}" size=20 /></td></tr>
						<tr><td>email</td><td><input type=text name=email value="{email}" size=20 /></td></tr>
						<tr><td>inSession</td><td><input type=text name=inSession value="{inSession}" size=20 /></td></tr>
						<tr><td>notes</td><td><input type=text name=notes value="{notes}" size=20 /></td></tr>
						<tr><td>persid_moe</td><td><input type=text name=persid_moe value="{persid_moe}" size=20 /></td></tr>
						<tr><td>role</td><td><input type=text name=role value="{role}" size=20 /></td></tr>
					</table>
				</form>
			</div>
			<div style="clear: both;"></div>
		<div>
	</center>
</div>