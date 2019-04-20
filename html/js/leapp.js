'use strict';

class Leapp {
	constructor() {
		this.debug = false;
		this.windowtitle = "";
		this.windowstate = "";
		this.windowwidth = 100;
		this.windowheight = 100;
	}

	get ping () {
		return "pong";
	}
	set debugEnable (enable) {
		this.debug = (typeof(enable) != 'undefined' && (enable == "1" || enable == "true")) ? 1 : 0;
		console.log(this.methodName);
	}
	set windowTitle(title) {
		this.windowtitle = title;
		console.log(this.methodName);
	}
	set windowState(state) {
		state = state.toLowerCase();
		if (state == "active" || state == "fullscreen" || state == "maximized" || state == "minimized" || state == "nostate") {
			this.windowstate = state;
			console.log(this.methodName);
		}
	}
	set width(w) {
		if (typeof(w) != 'undefined' && !Number.isNaN(Number(w))) {
			this.windowwidth = Number(w);
			console.log(this.methodName);
		}
	}
	set height(h) {
		if (typeof(h) != 'undefined' && !Number.isNaN(Number(h))) {
			this.windowheight = Number(h);
			console.log(this.methodName);
		}
	}
	trayMenuClick(name) {
		return;
	}
	reload() {
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