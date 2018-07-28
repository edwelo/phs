//
//eo 180728

var teachers = null;
var deptsCourses = null;
var teachersAssigns = [];

var semPerCol = {"11":4,"12":5,"13":6,"14":7,"21":4,"22":5,"23":6,"24":7};

function choose_course(obj) {

	var tbl = document.getElementById("teacherTable");

	var cIndex = obj.cellIndex;
	var row = obj.parentNode;
	var rIndex = row.rowIndex;
	var dept = row.getElementsByTagName("data")[0].innerHTML;
	var teacherName = row.getElementsByTagName("data")[2].innerHTML;
	
	var currentCourse = obj.innerHTML;
	var semPer = tbl.rows[1].cells[cIndex].innerHTML;
	
	//console.log("choose_course_params:", dept, teacherName, currentCourse, semPer);
	
	var text = "Assign Period " + semPer + " Course for\n";
	text += "Teacher: " + teacherName + ", dept: " + dept + ".\n\n";
	
	var textArr = [];
	
	for(i=0, il=deptsCourses.length; i<il; i++) {
		if(deptsCourses[i].abbrev == dept) {
			textArr.length = 0;
			for(j=0, jl=deptsCourses[i].courses.length; j<jl; j++) {
				var courseId = deptsCourses[i].courses[j].courseId;
				var crsSName = deptsCourses[i].courses[j].courseNameShort;
				if(crsSName) {
					text += courseId + " " + crsSName + "\n";
					textArr.push({"courseId": courseId, "courseNameShort": crsSName});
				}
			}
			break;
		}
	}
	
	text += "\nEnter CourseId:";
	//console.log(textArr);

	var chosenCourse = prompt(text, currentCourse);
	if(chosenCourse != null) {
		obj.value = chosenCourse;
	}
}

function clear_table(obj) {
	while(obj.rows[1] != undefined) {
		obj.deleteRow(1);
	}
	var datas = obj.rows[0].getElementsByTagName("data");
	for(i=0, il=datas.length; i<il; i++) {
		datas[i].innerHTML = "";
	}
	var inputs = obj.rows[0].getElementsByTagName("input");
	for(i=0, il=inputs.length; i<il; i++) {
		inputs[i].value = "";
		if(inputs[i].name == "active") inputs[i].checked = false;
	}
}

function get_teachers(str) {
	if (str == "") {
		document.getElementById("txtHint").innerHTML = "";
		return;
	} else { 
	
		var year = str;
		var phssy = year - 1;
	
		document.getElementById("year").innerHTML = year;
	
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
				
				var tBody = document.getElementById("teacherTable").tBodies[0];
				clear_table(tBody);
				
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
				
			}
		};
		xmlhttp.open("GET","apis/backend.php?pn=Registration&t1=Operations&t2=Teachers&year=" + year,true);
		xmlhttp.send();
	}
}