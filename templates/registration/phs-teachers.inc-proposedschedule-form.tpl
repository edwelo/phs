<span class=lnk1>[ <a href="?{hrefpre}&tab={tab}">back</a> ]</span>
&nbsp;
{teacherName} <span class=lbl1>Proposed Schedule</span>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<span class=lnk1>[ <a href="javascript:document.teacherSchedule.submit()">save</a> ]</span><br />

<form name=teacherSchedule class=tight action="" method=post>

	<input type=hidden name=teacherId value="{teacherId}" />

	<table class=ct3>
		<tr><th>Period</th><th>Course Name</th><th>Section</th><th>taId</th><th>&nbsp;&nbsp;&nbsp;&nbsp;N&nbsp;&nbsp;&nbsp;&nbsp;</th></tr>
		<tr><td colspan=5><strong>First Semester</strong></td></tr>
		<tr><td>1st period</td><td><select name=cls[11]><option></option>{cls11_selopts}</select></td><td><select name=sec[11]><option></option>{sec11_selopts}</select></td><td>{taId11}</td><td align=center>{N11}</td></tr>
		<tr><td>2nd period</td><td><select name=cls[12]><option></option>{cls12_selopts}</select></td><td><select name=sec[12]><option></option>{sec12_selopts}</select></td><td>{taId12}</td><td align=center>{N12}</td></tr>
		<tr><td>3rd period</td><td><select name=cls[13]><option></option>{cls13_selopts}</select></td><td><select name=sec[13]><option></option>{sec13_selopts}</select></td><td>{taId13}</td><td align=center>{N13}</td></tr>
		<tr><td>4th period</td><td><select name=cls[14]><option></option>{cls14_selopts}</select></td><td><select name=sec[14]><option></option>{sec14_selopts}</select></td><td>{taId14}</td><td align=center>{N14}</td></tr>
		<tr><td colspan=5><strong>Second Semester</strong></td></tr>
		<tr><td>1st period</td><td><select name=cls[21]><option></option>{cls21_selopts}</select></td><td><select name=sec[21]><option></option>{sec21_selopts}</select></td><td>{taId21}</td><td align=center>{N21}</td></tr>
		<tr><td>2nd period</td><td><select name=cls[22]><option></option>{cls22_selopts}</select></td><td><select name=sec[22]><option></option>{sec22_selopts}</select></td><td>{taId22}</td><td align=center>{N22}</td></tr>
		<tr><td>3rd period</td><td><select name=cls[23]><option></option>{cls23_selopts}</select></td><td><select name=sec[23]><option></option>{sec23_selopts}</select></td><td>{taId23}</td><td align=center>{N23}</td></tr>
		<tr><td>4th period</td><td><select name=cls[24]><option></option>{cls24_selopts}</select></td><td><select name=sec[24]><option></option>{sec24_selopts}</select></td><td>{taId24}</td><td align=center>{N24}</td></tr>
	</table>
	</table>

</form>