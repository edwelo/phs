<script type="text/javascript">

	function show_modal() {
	
	}

	function modal() {
	
		var r = this.parentNode.rowIndex;
		var c = this.cellIndex;
		var teacherId = this.parentNode.cells[1].innerHTML;
		var teacherName = this.parentNode.cells[2].innerHTML;
		var semPer = this.parentNode.parentNode.rows[0].cells[c].innerHTML;

		// Get the modal
		var modal = document.getElementById('modal');
		var btn = modal.getElementsByTagName("button")[0];
		var sel = modal.getElementsByTagName("select")[0];
		var spans = modal.getElementsByTagName("span");

		//display the modal
		modal.style.display = "block";

		var xmlhttp = new XMLHttpRequest();
		xmlhttp.onreadystatechange = function() {
			if (this.readyState == 4 && this.status == 200) {
				//console.log(this.responseText);
				data = JSON.parse(this.responseText);

				spans[3].innerHTML = teacherName;
				spans[5].innerHTML = 2017;
				spans[7].innerHTML = semPer;
				
	
			}
		};

		var courseId=null;
		sel.onchange = function() {
			if (sel.selectedIndex !== -1) {
				courseId = sel.options[sel.selectedIndex].value;
			}
		}
		console.log(courseId);

		var elt = document.getElementById('modal').getElementsByTagName("select")[0];
		if (elt.selectedIndex == -1) {
			var courseId=null;
		} else {
			var courseId = elt.options[elt.selectedIndex].value;
		}	
		var url = "apis/teachers_schedule.php?teacherId=" + teacherId + "&semPer=" + semPer + "&courseId=" + courseId;

		xmlhttp.open("GET", url, true);
		xmlhttp.send();		



		// When the user clicks on <span> (x), close the modal
		spans[0].onclick = function() {
			modal.style.display = "none";
		}

		// When the user clicks on the save button, close the modal
		// and call the get_data function
		btn.onclick = function() {
			if(courseId > 0) {
				modal.style.display = "none";
				data = get_data(teacherId, semPer);
				console.log("step 3" . data);
				//update_cell();
			}
		}

		// When the user clicks anywhere outside of the modal, close it
		window.onclick = function(event) {
			if (event.target == modal) {
				modal.style.display = "none";
			}
		}

	}

	//get data from backend
	function get_data(teacherId, semPer) {

		var elt = document.getElementById('modal').getElementsByTagName("select")[0];

		if (elt.selectedIndex == -1) {
			var courseId=null;
		} else {
			var courseId = elt.options[elt.selectedIndex].value;
		}
		
		var url = "apis/teachers_schedule.php?teacherId=" + teacherId + "&semPer=" + semPer + "&courseId=" + courseId;
		console.log(url);

		var xmlhttp = new XMLHttpRequest();
		xmlhttp.onreadystatechange = function() {
			if (this.readyState == 4 && this.status == 200) {
				//console.log(this.responseText);
				data = JSON.parse(this.responseText);
				
				var rows = document.getElementsById("schedTable");
				for(row in rows) {
					if(row.cells[1].innerHTML == data["teacherId"]) {
						for(c=3; c<11; c++) {
							if(rows[0].cells[c].innerHTML == data["semPer"]) {
								row.cells[c].innerHTML = data["courseId"] + ". " + data["courseAbbrv"] + " (" + data["numStudents"] + ")";
							}
						}
					}
				}
	
			}
		};

		xmlhttp.open("GET", url, true);
		xmlhttp.send();		
	}

</script>

<div id=modal style="display: none; position: fixed; z-index: 1; left: 0; top: 0px; width: 100%; height: 100%; overflow: auto; background-color: rgba(0,0,0,0.4);">

	<div style="background-color: #fefefe; margin: 15% auto; padding: 20px; border-radius: 10px; border: 1px solid #888;  width: 46%;">
		<span style="float: right; cursor: pointer;">&times;</span>
		<span style="color: #abc;">Assign a Teacher's Schedule</span><br /><br />
		<span style="font-size: small; color: grey;">Teacher: </span>
		<span style="display: inline-block; width: 200px;"></span>&nbsp;&nbsp;&nbsp;
		<span style="font-size: small; color: grey;">Year: </span>
		<span></span>&nbsp;&nbsp;&nbsp;
		<span style="font-size: small; color: grey;">Period: </span>
		<span></span><br /><br />
		<span style="font-size: small; color: grey;">Course: </span>
		<select style="width: 350px; font-size: large;"><option></option>{courses_selOpts}</select>
		&nbsp;&nbsp;&nbsp;
		<button>Save</button>
	</div>
</div>

<div class=bodypanel>
	<span class=lbl1>Classes Schedule</span><br /><br />

	<table id=schedTable class=bodypanel style="width: 100%;">

		<tr style="background: tan;">
			<th>department</th>
			<th>id</th>
			<th>teacher</th>
			<th style="min-width: 10em;">11</th>
			<th style="min-width: 10em;">12</th>
			<th style="min-width: 10em;">13</th>
			<th style="min-width: 10em;">14</th>
			<th style="min-width: 10em;">21</th>
			<th style="min-width: 10em;">22</th>
			<th style="min-width: 10em;">23</th>
			<th style="min-width: 10em;">24</th>
		</tr>

		<tr id=row style="padding-top: 1em; padding-bottom: 3px;">
			<td style="font-size: xx-small; color: grey;">{dept}</td>
			<td class=lnk1 style="font-size: x-small;">{teacherId}</td>
			<td>{teacherName}</td>

			<td style='font-size: xx-small;'>{11}</td>
			<td style='font-size: xx-small;'>{12}</td>
			<td style='font-size: xx-small;'>{13}</td>
			<td style='font-size: xx-small;'>{14}</td>
			<td style='font-size: xx-small;'>{21}</td>
			<td style='font-size: xx-small;'>{22}</td>
			<td style='font-size: xx-small;'>{23}</td>
			<td style='font-size: xx-small;'>{24}</td>

		</tr>
	</table>
	
	<script type="text/javascript">
		function show() {
			var r = this.parentNode.rowIndex;
			var c = this.cellIndex;
			var teacherId = this.parentNode.cells[1].innerHTML;
			var semPer = this.parentNode.parentNode.rows[0].cells[c].innerHTML;
			;
		}
		
		var tbl = document.getElementById("schedTable");
		var rows = tbl.rows;
		for(r=1, l=rows.length; r<l; r++) {
			for(j=1; j<=8; j++) {
				var c = j+2;
				rows[r].cells[c].addEventListener("click", show_modal);
			}
		}
	</script>

</div>