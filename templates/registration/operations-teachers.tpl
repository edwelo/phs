<span class=lbl1>Enter Registration School Year: </span>
<select name="registration_year" onchange="get_teachers(this.value);">
	<option value="">- - -</option>
	<option value="2018">SY 2017-2018</option>
	<option value="2019">SY 2018-2019</option>
	<option value="2020">SY 2019-2020</option>
	<option value="2021">SY 2020-2021</option>
</select>
<br />

<table id=teacherTable class=bodypanel>
	<thead>
		<tr>
			<th rowspan=2>dept</th>
			<th rowspan=2>teacherId</th>
			<th rowspan=2>teacherName</th>
			<th rowspan=2><span id=year></span></th>
			<th colspan=4>1st Semester </th>
			<th colspan=4>2nd Semester</th>
		</tr>
		<tr>
			<th>11</th>
			<th>12</th>
			<th>13</th>
			<th>14</th>
			<th>21</th>
			<th>22</th>
			<th>23</th>
			<th>24</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><data value="dept"></data></td>
			<td><data value="teacherId"></data><input type=hidden name="teacherId" value="" /></td>
			<td><data value="teacherName"></data></td>
			<td><input type=checkbox name="active" value="" /></td>
			<td style="cursor: pointer" onclick="choose_course(this);"></td>
			<td style="cursor: pointer" onclick="choose_course(this);"></td>
			<td style="cursor: pointer" onclick="choose_course(this);"></td>
			<td style="cursor: pointer" onclick="choose_course(this);"></td>
			<td style="cursor: pointer" onclick="choose_course(this);"></td>
			<td style="cursor: pointer" onclick="choose_course(this);"></td>
			<td style="cursor: pointer" onclick="choose_course(this);"></td>
			<td style="cursor: pointer" onclick="choose_course(this);"></td>
		</tr>
	</tbody>
</table>

<div id="course_popup" class="course_popup">
	<div id="course_popup_content" class="course_popup_content">
		<div style="float: right;">
			<span style="cursor: pointer; font-weight: bold; display: inline-block; border: 1px solid grey; color: grey;" onclick="set_new_course_id(0);">&nbsp;&times;&nbsp;</span>
		</div>
		<div style="float: left; text-align: left; font-weight: bold;">Course Selector</div>
		<div style="clear: both;"></div>
	
		<input type=hidden name=rIndex value="" />
		<input type=hidden name=cIndex value="" />

		<table>
			<tr><td style="text-align: right; font-size: small; color: grey;">Teacher:</td><td style="text-align: left;"><span></span></td><tr>
			<tr><td style="text-align: right; font-size: small; color: grey;">semPer:</td><td style="text-align: left;"><span></span></td><tr>
		</table>
		<div id="course_links" style="float: right;">
			Choose New Course:<br />
			<span style="cursor: pointer; display: block;" onclick="set_new_course_id(this);"></span>
		</div>
		<p>
			Current Course:<br />
			<span id="current_course"></span>
			<br /><br />
			<button type="button" onclick="set_new_course_id('clear');">
				Clear current course
			</button>
	</div>
</div>

<script type="text/javascript">{incJS}</script>
