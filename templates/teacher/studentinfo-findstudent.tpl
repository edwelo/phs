<span style='color: #778fbd; font-size: large;'>Select a student</span>

<br /><br />

<div id=tab2>

	<form class=tight action='' method=post>
		<span class=lbl1>Enter Student ID: </span>
		<input type=text name=set_student_id size=6 />
		&nbsp;&nbsp;
		<input type=submit value=go />
	</form><br />

	<br />
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;or<br />
	<br />

	<div class=flbeg>
		<form class=tight action='' method=get>
		{getpre}
		<span class=lbl1>find student (enter search phrase): </span><br />
		<input type=text name=sp value='{sp}' size=20 />
		&nbsp;&nbsp;
		<input type=submit value=go />
		</form><br />
	</div>
	<div class=flmid>
		<span class=lbl1>Students matching the search phrase.</span><br />
		<!-- stu_list -->
	</div>
	<div class=flend></div>

</div>

	<br />
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;or<br />
	<br />

<span class=lbl1>Click on a student name below</span><br />
<br />
<div id=tab1>

	<div class=flbeg>
		<span class=lbl1>FRESHMEN<br />
		{freshmen_list}
		</span>
	</div>

	<div class=flmid>
		<span class=lbl1>SOPHOMORES<br />
		{sophomores_list}
		</span>
	</div>

	<div class=flmid>
		<span class=lbl1>JUNIORS<br />
		{juniors_list}
		</span>
	</div>

	<div class=flmid>
		<span class=lbl1>SENIORS<br />
		{seniors_list}
		</span>
	</div>

	<div class=flend></div>

</div>

