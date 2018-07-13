<div class=bodypanel>
<!-- class list -->
	<span class=lbl1>List of Classes</span><br />
	<table class=bodypanel>
		<thead>
			<tr><th>Class ID</th><th>Course Name</th><th>Semester</th><th>Period</th><th>Number of Students</th><th></th></tr>
		</thead>
		<tbody>
			<tr id=row><td align=center>{classId}</td><td>{courseName}</td><td align=center>{semester}</td><td align=center>{period}</td><td align=center>{numberEnrolled}</td><td align=right><a href="?{hrefpre}&classId={classId}">&nbsp;&nbsp;<b>></b>&nbsp;</a></tr>
		</tbody>
	</table>
<!-- /class list -->
<!-- class roster -->
	<center>
		<span class=lnk1>[ <a href="?{prevqtrlink}">previous quarter</a> ]</span>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lbl2>{courseName} - {period} Period {semester} Semester {quarter} Quarter</span>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<span class=lnk1>[ <a href="?{nextqtrlink}">next quarter</a> ]</span>
	</center>
	<table class=bodypanel>
		<thead>
			<tr>
				<th colspan=2 rowspan=2>Student</th>
				<th colspan=5 style="border-left: 3px solid #567;">Wk 1<br />{w1d1}</th>
				<th colspan=5 style="border-left: 3px solid #567;">Wk 2<br />{w2d1}</th>
				<th colspan=5 style="border-left: 3px solid #567;">Wk 3<br />{w3d1}</th>
				<th colspan=5 style="border-left: 3px solid #567;">Wk 4<br />{w4d1}</th>
				<th colspan=5 style="border-left: 3px solid #567;">Wk 5<br />{w5d1}</th>
				<th colspan=5 style="border-left: 3px solid #567;">Wk 6<br />{w6d1}</th>
				<th colspan=5 style="border-left: 3px solid #567;">Wk 7<br />{w7d1}</th>
				<th colspan=5 style="border-left: 3px solid #567;">Wk 8<br />{w8d1}</th>
				<th colspan=5 style="border-left: 3px solid #567;">Wk 9<br />{w9d1}</th>
				<th colspan=5 style="border-left: 3px solid #567;">Wk 10<br />{w10d1}</th>
				<th colspan=3 style="border-left: 3px solid #567;">Absence<br />Totals</th>
			</tr>
			<tr>
				<th style='border-left: 3px solid #567;'><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date0}'>m</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date1}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date2}'>w</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date3}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date4}'>f</a></th>

				<th style='border-left: 3px solid #567;'><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date5}'>m</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date6}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date7}'>w</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date8}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date9}'>f</a></th>

				<th style='border-left: 3px solid #567;'><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date10}'>m</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date11}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date12}'>w</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date13}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date14}'>f</a></th>

				<th style='border-left: 3px solid #567;'><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date15}'>m</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date16}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date17}'>w</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date18}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date19}'>f</a></th>

				<th style='border-left: 3px solid #567;'><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date20}'>m</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date21}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date22}'>w</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date23}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date24}'>f</a></th>

				<th style='border-left: 3px solid #567;'><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date25}'>m</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date26}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date27}'>w</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date28}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date29}'>f</a></th>

				<th style='border-left: 3px solid #567;'><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date30}'>m</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date31}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date32}'>w</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date33}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date34}'>f</a></th>

				<th style='border-left: 3px solid #567;'><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date35}'>m</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date36}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date37}'>w</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date38}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date39}'>f</a></th>

				<th style='border-left: 3px solid #567;'><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date40}'>m</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date41}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date42}'>w</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date43}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date44}'>f</a></th>

				<th style='border-left: 3px solid #567;'><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date45}'>m</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date46}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date47}'>w</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date48}'>t</a></th>
				<th><a style='font-size: x-small; color: #39f; text-decoration: none; font-weight: normal;' href='?{hrefpre}&date={date49}'>f</a></th>

				<th style='border-left: 3px solid #567; text-align: right;'>A</th>
				<th style=' text-align: right;'>T</th>
				<th style=' text-align: right;'>tA</th>
			</tr>
		</thead>
		<tbody>
			<tr id=row>
				<td style="width: 1px; white-space: nowrap;">{studentName}</td>
				<td>{studentId}</td>
				<td style="border-left: 3px solid #567;">{day1}</td>
				<td>{day2}</td>
				<td>{day3}</td>
				<td>{day4}</td>
				<td>{day5}</td>
				<td style="border-left: 3px solid #567;">{day6}</td>
				<td>{day7}</td>
				<td>{day8}</td>
				<td>{day9}</td>
				<td>{day10}</td>
				<td style="border-left: 3px solid #567;">{day11}</td>
				<td>{day12}</td>
				<td>{day13}</td>
				<td>{day14}</td>
				<td>{day15}</td>
				<td style="border-left: 3px solid #567;">{day16}</td>
				<td>{day17}</td>
				<td>{day18}</td>
				<td>{day19}</td>
				<td>{day20}</td>
				<td style="border-left: 3px solid #567;">{day21}</td>
				<td>{day22}</td>
				<td>{day23}</td>
				<td>{day24}</td>
				<td>{day25}</td>
				<td style="border-left: 3px solid #567;">{day26}</td>
				<td>{day27}</td>
				<td>{day28}</td>
				<td>{day29}</td>
				<td>{day30}</td>
				<td style="border-left: 3px solid #567;">{day31}</td>
				<td>{day32}</td>
				<td>{day33}</td>
				<td>{day34}</td>
				<td>{day35}</td>
				<td style="border-left: 3px solid #567;">{day36}</td>
				<td>{day37}</td>
				<td>{day38}</td>
				<td>{day39}</td>
				<td>{day40}</td>
				<td style="border-left: 3px solid #567;">{day41}</td>
				<td>{day42}</td>
				<td>{day43}</td>
				<td>{day44}</td>
				<td>{day45}</td>
				<td style="border-left: 3px solid #567;">{day46}</td>
				<td>{day47}</td>
				<td>{day48}</td>
				<td>{day49}</td>
				<td>{day50}</td>
				<td style="border-left: 3px solid #567; text-align: right;">{tA}</td>
				<td style="text-align: right;">{tT}</td>
				<td style="text-align: right;">{tTA}</td>
			</tr>
		</tbody>
	</table>
<!-- /class roster -->
<!-- class roster edit -->
	<form class=tight action="?{back_menu_link}" method=post>
		<input type=hidden name=classId value={classId} />
		<input type=hidden name=date value={edit_date} />
		<center>
			<span style="font-size: medium; color: #eef;">
				{dateday}
				&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				{courseName}, {period} Period {semester} Semester
				&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<input type=button value=cancel onClick="location.href='?{back_menu_link}'" />
				<input type=submit value=save />
			</span><br />
		</center>
		<table class=bodypanel>
			<thead>
				<tr>
					<th></th>
					<th>Student</th>
					<th>Absent</th>
					<th>Tardy</th>
					<th>Excused</th>
					<th>Comments</th>
					<th></th>
			</thead>
			<tbody>
				<tr id=row>
					<td style="border: none;"></td>
					<td style="width: 1%; white-space: nowrap; border: none; font-size: medium; font-family: Sans-Serif; color: #345; vertical-align: middle;">{studentName}</td>
					<td style="width: 1%; white-space: nowrap; border: none; text-align: center;">
						<input style="height: 15px; width: 25px;" name=absinfo[{studentId}][0] type=checkbox {absent} /></td>
					<td style="width: 1%; white-space: nowrap; border: none; text-align: center;">
						<input style="height: 15px; width: 25px;" name=absinfo[{studentId}][1] type=checkbox {tardy} /></td>
					<td style="width: 1%; white-space: nowrap; border: none; text-align: center;">
						<input style="height: 15px; width: 25px;" name=absinfo[{studentId}][2] type=checkbox {excused} /></td>
					<td style="width: 1%; white-space: nowrap; border: none;">
						<input style="background: transparent; margin: 0 auto 0 auto; font-size: small; color: #345;" name=absinfo[{studentId}][3] type=text value='{comment}' size=60 />
						<input type=hidden name=absinfo[{studentId}][4] value={edit_designation} />
					</td>
					<td style="border: none;"></td>
				</tr>
			</tbody>
		</table>
	</form>
<!-- /class roster edit -->
</div>