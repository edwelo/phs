var xmlhttp = new XMLHttpRequest();
xmlhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);
        document.getElementById("demo").innerHTML = myObj.name;
    }
};
var url = "http://localhost/~admin/dev_for_www.moe/dev_sis_report/apis/test.php";
xmlhttp.open("GET", url, true);
xmlhttp.send();