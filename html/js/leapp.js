'use strict';

class Leapp {
	constructor() {
		this.debug = false;
		this.windowtitle = "";
		this.windowstate = "";
		this.windowwidth = 100;
		this.windowheight = 100;
		this.windowleft = 100;
		this.windowtop = 100;
	}

	get ping () {
		return "pong";
	}
	set debugEnable (enable) {
		this.debug = (typeof(enable) != 'undefined' && (enable == "1" || enable == "true")) ? 1 : 0;
		console.log(this.methodName);
	}
	set title(title) {
		this.windowtitle = title;
		console.log(this.methodName);
	} get title() { return this.windowtitle; }

	set windowState(state) {
		this.windowstate = state;
		console.log(this.methodName);
	}
	set width(w) {
		if (typeof(w) != 'undefined' && !Number.isNaN(Number(w))) {
			this.windowwidth = Number(w);
			console.log(this.methodName);
		}
	} get width(){ return this.windowwidth; }
	set height(h) {
		if (typeof(h) != 'undefined' && !Number.isNaN(Number(h))) {
			this.windowheight = Number(h);
			console.log(this.methodName);
		}
	} get height(){ return this.windowheight; }

	set left(x) {
		if (typeof(x) != 'undefined' && !Number.isNaN(Number(x))) {
			this.windowleft = Number(x);
			console.log(this.methodName);
		}
	} get left(){ return this.windowleft; }
	set top(y) {
		if (typeof(y) != 'undefined' && !Number.isNaN(Number(y))) {
			this.windowtop = Number(y);
			console.log(this.methodName);
		}
	} get top(){ return this.windowtop; }
	
	sql(query, callback) {
		// let event = {fun: "sql", query: query, callback: eval(callback).toString()};
		// console.log(JSON.stringify(event));
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			var temp = channel.objects.qtObject.onKeysExtracted(query, function(e){
				callback(e);
			});
		});
	}

	trayMenuClick(name) {
		return true;
	}
	windowClose() {
		return true;
	}
	windowResize(width, height) {
		return true;
	}
	windowMove(x, y) {
		return true;
	}
	reload() {
		console.log(this.methodName);
	}
	hide() {
		console.log(this.methodName);
	}
	show() {
		console.log(this.methodName);
	}
	exit() {
		console.log(this.methodName);
	}
	get methodName(){
	   let stack;
		try { 
			throw Exception() 
		} 
		catch(e) { 
			stack = e.stack.split(/\n/g); 
		}
		stack.shift();
		let row = stack[1].replace(/^\s*at\s+/,'').split(" ");
		row = (row[0] == "Leapp.set" || row[0] == "Leapp.get") ? "Leapp." + row[1] : row[0];
		return row;
	}

}