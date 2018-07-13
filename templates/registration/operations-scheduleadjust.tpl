<div style="float: right;">
	<form class=tight action="" method=get>
		{getpre}
		<input type=hidden name=tab value={tab} />
		<span class=lbl1>Select Teacher: </span>
		<select name=tchrid onChange=submit()>
			<option></option>
			{tchr_selopts}
		</select>
	</form>
</div>

<!-- start form -->
<br />
<span class=lbl1>Proposed Schedule For: </span>{teacherName}
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<span class=lnk1>[ <a href="javascript:document.teacherSchedule.submit()">save</a> ]</span><br />

<div class=flend></div>

<form name=teacherSchedule class=tight action="" method=post>

	<input type=hidden name=teacherId value="{teacherId}" />

	<table class=phstable>
		<tr style="vertical-align: bottom; background: tan;"><th>Period</th>
			<th>Class Id</th><th width=40>Course</th><th width=40>N</th><th width=40>Section</th></tr>
		<tr style="background: #ccc;"><td colspan=5><strong>First Semester</strong></td></tr>
		<tr><td>1st period</td>
			<td class=nor align=center>{classId11}</td>
			<td class=norl><select name=crs[11]><option></option>{crs11_selopts}</select></td>
			<td class=norl align=center><span class=lnk1>
				<a href="" onClick="window.open('../print/print_phs_classlist.php?classId={classId11}', 'classlist', 'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">{N11}</a>
				</span></td>
			<td class=nol align=center>{sec11}</td></tr>
		<tr><td>2nd period</td>
			<td class=nor align=center>{classId12}</td>
			<td class=norl><select name=crs[12]><option></option>{crs12_selopts}</select></td>
			<td class=norl align=center><span class=lnk1>
				<a href="" onClick="window.open('../print/print_phs_classlist.php?classId={classId12}', 'classlist', 'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">{N12}</a>
				</span></td>
			<td class=nol align=center>{sec12}</td></tr>
		<tr><td>3rd period</td>
			<td class=nor align=center>{classId13}</td>
			<td class=norl><select name=crs[13]><option></option>{crs13_selopts}</select></td>
			<td class=norl align=center><span class=lnk1>
				<a href="" onClick="window.open('../print/print_phs_classlist.php?classId={classId13}', 'classlist', 'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">{N13}</a>
				</span></td>
			<td class=nol align=center>{sec13}</td></tr>
		<tr><td>4th period</td>
			<td class=nor align=center>{classId14}</td>
			<td class=norl><select name=crs[14]><option></option>{crs14_selopts}</select></td>
			<td class=norl align=center><span class=lnk1>
				<a href="" onClick="window.open('../print/print_phs_classlist.php?classId={classId14}', 'classlist', 'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">{N14}</a>
				</span></td>
			<td class=nol align=center>{sec14}</td></tr>
		<tr style="background: #ccc;"><td colspan=5><strong>Second Semester</strong></td></tr>
		<tr><td>1st period</td>
			<td class=nor align=center>{classId21}</td>
			<td class=norl><select name=crs[21]><option></option>{crs21_selopts}</select></td>
			<td class=norl align=center><span class=lnk1>
				<a href="" onClick="window.open('../print/print_phs_classlist.php?classId={classId21}', 'classlist', 'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">{N21}</a>
				</span></td>
			<td class=nol align=center>{sec21}</td></tr>
		<tr><td>2nd period</td>
			<td class=nor align=center>{classId22}</td>
			<td class=norl><select name=crs[22]><option></option>{crs22_selopts}</select></td>
			<td class=norl align=center><span class=lnk1>
				<a href="" onClick="window.open('../print/print_phs_classlist.php?classId={classId22}', 'classlist', 'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">{N22}</a>
				</span></td>
			<td class=nol align=center>{sec22}</td></tr>
		<tr><td>3rd period</td>
			<td class=nor align=center>{classId23}</td>
			<td class=norl><select name=crs[23]><option></option>{crs23_selopts}</select></td>
			<td class=norl align=center><span class=lnk1>
				<a href="" onClick="window.open('../print/print_phs_classlist.php?classId={classId23}', 'classlist', 'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">{N23}</a>
				</span></td>
			<td class=nol align=center>{sec23}</td></tr>
		<tr><td>4th period</td>
			<td class=nor align=center>{classId24}</td>
			<td class=norl><select name=crs[24]><option></option>{crs24_selopts}</select></td>
			<td class=norl align=center><span class=lnk1>
				<a href="" onClick="window.open('../print/print_phs_classlist.php?classId={classId24}', 'classlist', 'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">{N24}</a>
				</span></td>
			<td class=nol align=center>{sec24}</td></tr>
	</table>

</form>
<!-- end form -->
