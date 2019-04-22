var closetry = 0;

if (typeof leapp != 'undefined') {
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
	$(document).ready(function() {
		$("#path").val(leapp.path());
		$("#wintitle").val(leapp.title + " Example");
	});
	var timerId;
	$(document).on('click', '.changestyle', function(event) {
		clearTimeout(timerId);
		timerId = setTimeout(function(){
			leapp.style = 0;
		}, 20000);
		alert("Window style set do default after 20 second");
		leapp.style = document.getElementById('wstyle').value;
	});
}



$(document).on('click', '.sendsql', function(event) {
	event.preventDefault();
	var query = $("input", $(this).parent().parent()).val();
	leapp.sql(query, function(data){
		if (typeof data.rows != 'undefined') {
			var resulthead = "";
			var resultbody = "";
			for (var i = 0; i < data.rows.length; i++) {
				resulthead = "<tr>";
				resultbody += "<tr>";
				for (keys in data.rows[i]) {
					resulthead += "<td>" + keys + "</td>";
					resultbody += "<td>" + data.rows[i][keys] + "</td>";
				}
				resulthead += "</tr>";
				resultbody += "</tr>";
			}
			$(".sqlresult").html("<thead>" + resulthead + "</thead><tbody>" + resultbody + "<tbody>");
		}
		console.log(data.error);
		if (typeof data.error != 'undefined') {
			$(".sqlresult").html("<thead>" + data.error + "</thead>");
		}
		$(".sqlinfo").html("<thead><tr><td>numRowsAffected</td><td>lastInsertId</td></tr></thead><tbody><tr><td>" + data.numRowsAffected + "</td><td>" + data.lastInsertId + "</td></tr></tbody>");
	})
});

$(document).on('click', '.select > div a', function(event) {
	event.preventDefault();
	var parent = $(this).parent().parent();
	$("input", parent).val($(this).attr('item'));
	$("p", parent).html($(this).html());
});


// for (key in data.rows) {
// 			if (typeof data[key] === "object") {
// 				for (tkey in data[key]) {
// 					if (typeof data[key][tkey] === "object") {
// 						for (rkey in data[key][tkey]) {
// 							console.log(rkey + ": " + data[key][tkey][rkey]);
// 						}
// 					}else{
// 						console.log(tkey + ": " + data[key][tkey]);
// 					}
// 				}
// 			}else{
// 				console.log(key + ": " + data[key]);
// 			}
// 		}