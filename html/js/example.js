var closetry = 0;
let leapp = new Leapp();
leapp.trayMenuClick = function(menu){
	if (menu == "Выход") leapp.exit();
	$("#traymenuclick").html(menu);
}
leapp.windowResize = function(w, h){
	$("#sizechanged").html('width: ' + w + 'px;<br>height: ' + h + 'px;');
}
leapp.windowMove = function(x, y){
	$("#winmove").html('x: ' + x + 'px;<br>y: ' + y + 'px;');
}
leapp.windowClose = function(){
	closetry += 1;
	if (closetry > 9) return true;
	$("#windowclose").html(closetry + " / 10 left until the window is closed");
	return false;
}

$(document).on('click', '.sendsql', function(event) {
	event.preventDefault();
	// leapp.sql("SELECT * FROM UserNew", function(){
	// 	console.log("done!");
	// })
	var valueTable = ["work", "on", "funnew"];
	leapp.sql(valueTable, function(result){
		console.log("result1 : " + result);
	});
});

$(document).on('click', '.select > div a', function(event) {
	event.preventDefault();
	var parent = $(this).parent().parent();
	$("p", parent).html($(this).html());
});


// $(document).ready(function($) {
	
// });

// 	var webChannel=new QWebChannel(
// 	qt.webChannelTransport,
// 	function(channel) {
// 		leappp.qt = this;
// 	extractKeys();
// 	console.log(this);
// 	}
// 	);

// 	function extractKeys() {
// 	try {
// 	var valueTable = [];
// 	$("[id]").each(
// 	function () {
// 	valueTable.push($(this).attr("id") + "izfunct");
// 	}
// 	);
		
// 		webChannel.objects.qtObject.onKeysExtracted(valueTable);
// 	}
// 	catch (e) {
// 	console.log(e);
// 	}
// 	}