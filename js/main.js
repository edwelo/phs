//module variables
var myData = null;

//ajax call
function ajax() {
	var xmlhttp = new XMLHttpRequest();
	xmlhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			var myObj = JSON.parse(this.responseText);
			document.getElementById("demo").innerHTML = myObj.name;
		}
	};
	var url = "apis/backend.php";
	xmlhttp.open("GET", url, true);
	xmlhttp.send();
}