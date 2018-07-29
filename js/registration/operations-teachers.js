//
//eo 180728

var teachers = null;
var deptsCourses = null;
var teachersAssigns = [];
var newCourseId = null;
var year = 0;
var phssy = 0;

var tbl = document.getElementById("teacherTable");
var tBody = tbl.tBodies[0];
var tblLength;
var tBodyLength;

var semPerCol = {"11":4,"12":5,"13":6,"14":7,"21":4,"22":5,"23":6,"24":7};

function set_new_course_id(obj) {

	document.getElementById("course_popup").classList.remove("show_popup");

	var popUpContent = document.getElementById("course_popup_content");
	rIndex = popUpContent.getElementsByTagName("input")[0].value;
	cIndex = popUpContent.getElementsByTagName("input")[1].value;
		
	var tbl = document.getElementById("teacherTable");

	if(obj == "clear") {
		tbl.rows[rIndex].cells[cIndex].innerHTML = "";
	}

	if(typeof obj == "object") {
		var text = obj.innerHTML.trim();
		var tmp = text.split(" ", 2);
		var courseId = tmp[0];
		
		tbl.rows[rIndex].cells[cIndex].innerHTML = text;
	}

	reset_popup();

}

function reset_popup() {
	var popUpContent = document.getElementById("course_popup_content");
	popUpContent.getElementsByTagName("input")[0].value = "";
	popUpContent.getElementsByTagName("input")[1].value = "";
	popUpContent.getElementsByTagName("span")[1].innerHTML = "";
	popUpContent.getElementsByTagName("span")[2].innerHTML = "";
	
	var div = document.getElementById("course_links");
	var spans = div.getElementsByTagName("span");
	spans[0].innerHTML = "";
	while(spans[1] != undefined) {
		div.removeChild(spans[1]);
	}
}

function choose_course(obj) {

	var cIndex = obj.cellIndex;
	var row = obj.parentNode;
	var rIndex = row.rowIndex;

	//console.log("object params:", rIndex, cIndex);

	var dept = row.getElementsByTagName("data")[0].innerHTML;
	var teacherName = row.getElementsByTagName("data")[2].innerHTML;
	
	var currentCourse = obj.innerHTML;
	var semPer = tbl.rows[1].cells[cIndex - 4].innerHTML;
	
	//console.log("course params:", dept, teacherName, currentCourse, semPer);

	reset_popup();
	
	var popUp = document.getElementById("course_popup");
	var popUpContent = document.getElementById("course_popup_content");
	
	popUpContent.getElementsByTagName("span")[1].innerHTML = teacherName;
	popUpContent.getElementsByTagName("span")[2].innerHTML = semPer;
	
	popUpContent.getElementsByTagName("input")[0].value = rIndex;
	popUpContent.getElementsByTagName("input")[1].value = cIndex;
	
	document.getElementById("current_course").innerHTML = currentCourse;
	
	var textArr = [];
	
	var divCourseLinks = document.getElementById("course_links");
	var spans = divCourseLinks.getElementsByTagName("span");
	
	sIndex = 0;
	for(i=0, il=deptsCourses.length; i<il; i++) {
	
		if(dept.substr(0, 3) == "CTE") {
			;
		}
	
		if(deptsCourses[i].abbrev == dept) {
			textArr.length = 0;
			for(j=0, jl=deptsCourses[i].courses.length; j<jl; j++) {
				var courseId = deptsCourses[i].courses[j].courseId;
				var crsSName = deptsCourses[i].courses[j].courseNameShort;
				if(crsSName) {
					if(spans[sIndex] == undefined) {
						var cln = spans[sIndex - 1].cloneNode(true);
						var theSpan = divCourseLinks.appendChild(cln);
					} else {
						var theSpan = spans[sIndex];
					}
					textArr.push({"courseId": courseId, "courseNameShort": crsSName});
					theSpan.innerHTML = courseId + " " + crsSName;
					sIndex++;
				}
			}
			break;
		}
	}
	
	popUp.classList.add("show_popup");

}

function clear_table() {

	tbl.rows[0].cells[3].innerHTML = ""; //year field
	
	while(tBody.rows[1] != undefined) {
		tBody.deleteRow(1);
	}
	var datas = tBody.rows[0].getElementsByTagName("data");
	for(i=0, il=datas.length; i<il; i++) {
		datas[i].innerHTML = "";
	}
	var inputs = tBody.rows[0].getElementsByTagName("input");
	for(i=0, il=inputs.length; i<il; i++) {
		inputs[i].value = "";
		if(inputs[i].name == "active") inputs[i].checked = false;
	}
}

function get_teachers(str) {
	
	if (str != "" && str != null && str != undefined) {
	
		if (window.XMLHttpRequest) {
			// code for IE7+, Firefox, Chrome, Opera, Safari
			xmlhttp = new XMLHttpRequest();
		} else {
			// code for IE6, IE5
			xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
		}
		xmlhttp.onreadystatechange = function() {
			if (this.readyState == 4 && this.status == 200) {
				
				//console.log(this.responseText);
				
				var obj = JSON.parse(this.responseText);
				
				teachers = obj["teachers"];
				
				deptsCourses = obj["depts"];
				
				clear_table();

				if(tBody.rows.length < 1) {
					alert("document.teacherTable must have at least 1 data row.");
					return;
				}
				
				var keys = ["11", "12", "13", "14", "21", "22", "23", "24"];
				
				for(r=0, rl=teachers.length; r<rl; r++) {
					
					if(tBody.rows[r] == undefined) {
						var cln = tBody.rows[r - 1].cloneNode(true);
						tBody.appendChild(cln);	
					}
					
					var row = tBody.rows[r];
					//if(r==0) console.log(row);
					
					var datas = row.getElementsByTagName("data");
					for(i=0, il=datas.length; i<il; i++) {
						datas[i].innerHTML = teachers[r][datas[i].value];
					}

					var inputs = row.getElementsByTagName("input");
					//if(r == 0) console.log(inputs);
					for(i=0, il=inputs.length; i<il; i++) {
						if(teachers[r][inputs[i].name]) {
							inputs[i].value = teachers[r][inputs[i].name];
							if(inputs[i].name == "active") {
								if(teachers[r]["active"] == "1") {
									inputs[i].checked = true;
								} else {
									inputs[i].checked = false;
								}
							}
						} else {
							inputs[i].value = "";
						}
					}
					
					var col = 3;
					for(i=0, il=keys.length; i<il; i++) {
						var col = +i + 4;
						var key = keys[i];	
						//console.log(r, i, col, key, teachers[r]["teacherId"], teachers[r][key]);						
						if(teachers[r][key]) {
							row.cells[col].innerHTML = teachers[r][key];
						} else {
							row.cells[col].innerHTML = "";
						}
					} 
				}
				
				tblLength = tbl.rows.length;
				tBodyLength = tBody.rows.length;
				
			}
		};
		
		if(str == "save" && year) {
			
			var json = save();
			//console.log(json);
			
			xmlhttp.open("PUT","apis/backend.php?pn=Registration&t1=Operations&t2=Teachers&year=" + year + "&save=1",true);
			xmlhttp.setRequestHeader('Content-type','application/json');
			xmlhttp.send(json);		

		} else {

			year = str;
			var phssy = year - 1;
		
			//alert(year);
		
			document.getElementById("year").innerHTML = year;
			//console.log(span_year);
		
			xmlhttp.open("GET","apis/backend.php?pn=Registration&t1=Operations&t2=Teachers&year=" + year,true);
			xmlhttp.send();		
		}

	}
}

function save() {

	console.log("tbl rows: " + tbl.rows.length, tbl.rows);
	console.log("tbody rows: " + tBody.rows.length, tBody.rows);
		
	var keys = ["11", "12", "13", "14", "21", "22", "23", "24"];
	
	//year = document.getElementById("year").innerHTML;
	
	var jsonId = "tchrAssigns_" + year;
	var toJSON = {};
	toJSON[jsonId] = [];
	
	console.log(toJSON);
	
	for(r=0, rl=tBodyLength; r<rl; r++) {
	
		var datas = tBody.rows[r].getElementsByTagName("data");
		var dept = datas[0].innerHTML;
		var teacherId = datas[1].innerHTML;
		var teacherName = datas[2].innerHTML;
		
		//semPer columns
		for(i=0; i<8; i++) {
			let c = i + 4;
			str = tBody.rows[r].cells[c].innerHTML;
			str.trim();
			if(str) {
				var key = keys[i];

				var tmp = str.split(" ", 2);
				var crsId = tmp[0];
				var crsSName = tmp[1];
				 
				var tmp2 = {};
				
				tmp2.deptAbbrv = dept;
				tmp2.teacherId = teacherId;
				tmp2.teacherName = teacherName;
				tmp2.semPer = key;
				tmp2.courseId = crsId;
				tmp2.courseNameShort = crsSName;
				
				//console.log(tmp2);
				
				toJSON[jsonId].push(tmp2);
				
			}
		}
	}

	var json = JSON.stringify(toJSON);
	
	console.log(toJSON);
	console.log(json);
	
	return json;
	
}