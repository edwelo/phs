<div style="float: right;">
	<form class=tight action="" method=get>
		{getpre}
		<input type=hidden name=tab value={tab} />
		<span class=lbl1>Teacher: </span>
		<select name=tchrid onChange=submit()>
			<option></option>
			{tchr_selopts}
		</select>
	</form>
</div>
<br />

<!-- start form -->

<span class=lbl1>Classes for </span>{teacherName}. <span class=lbl1>Click on a class to see the class list.</span>
<div class=flend></div>

<div class=flbeg>
	<span class=lbl1>11</span> <span class=lnk1><a href="?{hrefpre}&tab={tab}&tchrid={teacherId}&clsid={clsid11}">{cls11}</a> ({count11})</span><br />
	<span class=lbl1>12</span> <span class=lnk1><a href="?{hrefpre}&tab={tab}&tchrid={teacherId}&clsid={clsid12}">{cls12}</a> ({count12})</span><br />
	<span class=lbl1>13</span> <span class=lnk1><a href="?{hrefpre}&tab={tab}&tchrid={teacherId}&clsid={clsid13}">{cls13}</a> ({count13})</span><br />
	<span class=lbl1>14</span> <span class=lnk1><a href="?{hrefpre}&tab={tab}&tchrid={teacherId}&clsid={clsid14}">{cls14}</a> ({count14})</span><br />
	<span class=lbl1>21</span> <span class=lnk1><a href="?{hrefpre}&tab={tab}&tchrid={teacherId}&clsid={clsid21}">{cls21}</a> ({count21})</span><br />
	<span class=lbl1>22</span> <span class=lnk1><a href="?{hrefpre}&tab={tab}&tchrid={teacherId}&clsid={clsid22}">{cls22}</a> ({count22})</span><br />
	<span class=lbl1>23</span> <span class=lnk1><a href="?{hrefpre}&tab={tab}&tchrid={teacherId}&clsid={clsid23}">{cls23}</a> ({count23})</span><br />
	<span class=lbl1>24</span> <span class=lnk1><a href="?{hrefpre}&tab={tab}&tchrid={teacherId}&clsid={clsid24}">{cls24}</a> ({count24})</span><br />
</div>
<div class=flmid>
	<!-- start class list -->
	<span class=lbl1>{period} {courseName}</span>
	<br />

	<form name=teacherSchedule class=tight action="" method=post>

		<input type=hidden name=teacherId value="{teacherId}" />

		<table class=ct3>
			<tr><th>no</th><th>stuid</th><th>stuname</th><th>glvl</th></tr>
			<tr id=tblrow><td>{no}.</td><td>{stuid}</td><td>{stuname}</td><td>{glvl}</td></tr>
		</table>

	</form>
	<!-- end class list -->
</div>
<div class=flend></div>

<!-- end form -->
