var closetry = 0;
let leapp = new Leapp();
leapp.trayMenuClick = function(menu){
	if (menu == "Выход") leapp.exit();
	$("#traymenuclick").html(menu);
}
leapp.onResize = function(w, h){
	$("#sizechanged").html('width: ' + w + 'px;<br>height: ' + h + 'px;');
}
leapp.onMove = function(x, y){
	$("#winmove").html('x: ' + x + 'px;<br>y: ' + y + 'px;');
}
leapp.onClose = function(){
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
	leapp.width = 200;
});

$(document).on('click', '.select > div a', function(event) {
	event.preventDefault();
	var parent = $(this).parent().parent();
	$("p", parent).html($(this).html());
});
