'use strict';

class Leapp {
	constructor(isdebug) {
		this.isdebug = isdebug;
		this.windowTitle = "";

	}
	ping () {
		return "pong";
	}
	debug (msg, type) {
		console.log(arguments.callee.name);
	}
	setWindowTitle(title) {
		this.windowTitle = title;
		console.log(this.methodName);
	}
	get methodName(){
	   let stack;
		try{ throw Exception() } 
		catch(e) { stack = e.stack.split(/\n/g); }
		stack.shift();
		let row = stack[1].replace(/^\s*at\s+/,'').split(" ")[0];
		return row;
	}
	getWindowTitle() {
		return this.windowTitle;
	}

}

var leapp = new Leapp(true);
