<span class=lbl1>Proposed Schedule</span>
<!-- section 1 -->
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<form class=tight action="" method=get>
	{getpre}
	<input type=hidden name=tab value={tab} />
	<input type=hidden name=thesy value={thesy} />
	<span class=lbl1>Show Department: </span>
	<select name=dept onChange=submit()>
		<option>All</option>
		{dept_selopts}
	</select>
</form>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<span class=lnk1>[ <a href="../print/print_phs_teachingschedule.php" target="teachingschedule">print</a> ]</span>
<!-- /section 1 -->
<br />
<table class=phstable width=100%>
<thead>
	<tr style="background: tan;"><th>department</th><th>id</th><th>teacher</th><th colspan=4>11</th><th colspan=4>12</th><th colspan=4>13</th><th colspan=4>14</th><th colspan=4>21</th><th colspan=4>22</th><th colspan=4>23</th><th colspan=4>24</th></tr>
</thead>
<tfoot>
	<tr></tr>
</tfoot>
<tbody>
	<tr id=tblrow style="padding-top: 1em; padding-bottom: 3px;">
		<td><span style='font-size: xx-small; color: grey;'>{department}</span></td>
		<td><span class=lnk1 style="font-size: x-small;"><a href="?{hrefpre}&tab=3&tchrid={teacherId}">{teacherId}</a></span></td>
		<td>{teacherName}</td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId211}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName211}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec211}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color211};'>
			<a href="" onClick="window.open('../print/print_phs_classlist.php?taId={taId211}', 'classlist',
			'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">
			{N211}</a></span>
			</td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId212}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName212}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec212}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color212};'>
			<a href="" onClick="window.open('../print/print_phs_classlist.php?taId={taId212}', 'classlist',
			'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">
			{N212}</a></span>
			</td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId213}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName213}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec213}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color213};'>
			<a href="" onClick="window.open('../print/print_phs_classlist.php?taId={taId213}', 'classlist',
			'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">
			{N213}</a></span>
			</td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId214}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName214}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec214}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color214};'>
			<a href="" onClick="window.open('../print/print_phs_classlist.php?taId={taId214}', 'classlist',
			'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">
			{N214}</a></span>
			</td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId221}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName221}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec221}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color221};'>
			<a href="" onClick="window.open('../print/print_phs_classlist.php?taId={taId221}', 'classlist2',
			'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">
			{N221}</a></span>
			</td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId222}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName222}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec222}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color222};'>
			<a href="" onClick="window.open('../print/print_phs_classlist.php?taId={taId222}', 'classlist2',
			'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">
			{N222}</a></span>
			</td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId223}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName223}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec223}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color223};'>
			<a href="" onClick="window.open('../print/print_phs_classlist.php?taId={taId223}', 'classlist2',
			'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">
			{N223}</a></span>
			</td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId224}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName224}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec224}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color224};'>
			<a href="" onClick="window.open('../print/print_phs_classlist.php?taId={taId224}', 'classlist2',
			'toolbar=no, directories=no, location=no, status=yes, menubar=no, scrollbars=yes, width=300, height=400'); return false">
			{N224}</a></span>
			</td>

	</tr>
	<!-- rowend -->

	<tr id=tblrow2 style="padding-top: 1em; padding-bottom: 3px;">
		<td><span style='font-size: xx-small; color: grey;'>{department}</span></td>
		<td><span class=lnk1 style="font-size: x-small;">{teacherId}</a></td>
		<td>{teacherName}</td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId211}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName211}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec211}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color211};'>{N211}</span></td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId212}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName212}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec212}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color212};'>{N212}</span></td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId213}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName213}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec213}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color213};'>{N213}</span></td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId214}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName214}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec214}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color214};'>{N214}</span></td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId221}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName221}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec221}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color221};'>{N221}</span></td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId222}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName222}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec222}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color222};'>{N222}</span></td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId223}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName223}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec223}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color223};'>{N223}</span></td>

		<td class=notr><span style='font-size: xx-small; color: grey;'>{taId224}</span></td>
		<td class=notrl><span style='font-size: xx-small; font-weight: bold;'>{courseName224}</span></td>
		<td class=notrl><span style='font-size: xx-small; color: grey;'>{sec224}</span></td>
		<td class=notl><span class=lnk1 style='font-size: xx-small; color: {color224};'>{N224}</span></td>

	</tr>
	<!-- rowend2 -->

</tbody>
</table>