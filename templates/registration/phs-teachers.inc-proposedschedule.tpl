<span class=lbl1>Proposed Schedule</span>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<form class=tight action="" method=post>
	<span class=lbl1>Show </span>
	<select name=dept onChange=submit()>
		<option>All</option>
		{dept_selopts}
	</select>
</form>
<!-- &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<span class=lnk1>[ <a href="?{hrefpre}&tab={tab}&id=new">new</a> ]</span> -->
<br />
<div class=flend></div>
<table class=ct3>
<thead>
	<tr><th>id</th><th>teacher</th><th>11</th><th>12</th><th>13</th><th>14</th><th>21</th><th>22</th><th>23</th><th>24</th></tr>
</thead>
<tfoot>
	<tr></tr>
</tfoot>
<tbody>
	<tr id=tblrow><td><span class=lnk1 style="font-size: x-small;"><a href="?{hrefpre}&tab={tab}&id={teacherId}">{teacherId}</a></span></td><td>{teacherName}</td><td>{11}</td><td>{12}</td><td>{13}</td><td>{14}</td><td>{21}</td><td>{22}</td><td>{23}</td><td>{24}</td></tr>
</tbody>
</table>