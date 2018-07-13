function toggle(div_id) {
	var el = document.getElementById(div_id);
	if ( el.style.display == 'none' ) {	el.style.display = 'block';}
	else {el.style.display = 'none';}
}
/* popup javascript from http://www.pat-burt.com/web-development/how-to-do-a-css-popup-without-opening-a-new-window/
*/
function blanket_size(popUpDivVar) {
	if (typeof window.innerWidth != 'undefined') {
		viewportheight = window.innerHeight;
	} else {
		viewportheight = document.documentElement.clientHeight;
	}
	if ((viewportheight > document.body.parentNode.scrollHeight) && (viewportheight > document.body.parentNode.clientHeight)) {
		blanket_height = viewportheight;
	} else {
		if (document.body.parentNode.clientHeight > document.body.parentNode.scrollHeight) {
			blanket_height = document.body.parentNode.clientHeight;
		} else {
			blanket_height = document.body.parentNode.scrollHeight;
		}
	}
	var blanket = document.getElementById('blanket');
	blanket.style.height = blanket_height + 'px';
	var popUpDiv = document.getElementById(popUpDivVar);
	popUpDiv_height=blanket_height/2-150;//150 is half popup's height
	//popUpDiv.style.top = popUpDiv_height + 'px';
	popUpDiv.style.top = '100px';
}
function window_pos(popUpDivVar) {
	if (typeof window.innerWidth != 'undefined') {
		viewportwidth = window.innerHeight;
	} else {
		viewportwidth = document.documentElement.clientHeight;
	}
	if ((viewportwidth > document.body.parentNode.scrollWidth) && (viewportwidth > document.body.parentNode.clientWidth)) {
		window_width = viewportwidth;
	} else {
		if (document.body.parentNode.clientWidth > document.body.parentNode.scrollWidth) {
			window_width = document.body.parentNode.clientWidth;
		} else {
			window_width = document.body.parentNode.scrollWidth;
		}
	}
	var popUpDiv = document.getElementById(popUpDivVar);
	window_width=window_width/2-150;//150 is half popup's width
	//popUpDiv.style.left = window_width + 'px';
	popUpDiv.style.left = '200px';
}
function popup(windowname) {
	blanket_size(windowname);
	window_pos(windowname);
	toggle('blanket');
	toggle(windowname);
}
function popUpSave(windowname) {
	document.myform.submit();
	popup(windowname)
}

function getData(_row) {
	popup('popUpDiv');
	var _temp=document.getElementById(_row+"c0").innerHTML;
	document.getElementById("ffc0").value=_temp;
	var _temp=document.getElementById(_row+"c1").innerHTML;
	document.getElementById("respName").innerHTML=_temp;
	for(var i=2;i<11;i++) {
		var _temp=document.getElementById(_row+"c"+i).innerHTML;
		document.getElementById("fc"+i).value=_temp;
		document.getElementById("ffc"+i).value=_temp;
	}
}

function over(_row){
  document.getElementById("r"+_row).style.backgroundColor="red";
}

function out(_row){
  document.getElementById("r"+_row).style.backgroundColor="#ACF";
}
