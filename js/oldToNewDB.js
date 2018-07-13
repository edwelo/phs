function moveToNewDB() {

	var sy = document.getElementById("sy").innerText;
	var sem = document.getElementById("sem").innerText;
	var qtr = document.getElementById("qtr").innerText;

	var xmlhttp = new XMLHttpRequest();
	xmlhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {

			if(this.responseText == "Could not proceed") {
				alert(this.responseText);			
			} else {
				var myArr = JSON.parse(this.responseText);
				alert(myArr);
			}
		}
	};
	var url = "apis/oldToNewDB.php?sy=" + sy + "&sem=" + sem + "&qtr=" + qtr;
	alert(url);
	xmlhttp.open("GET", url, true);
	xmlhttp.send();
}