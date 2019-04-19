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
		try { 
			throw Exception() 
		} 
		catch(e) { 
			stack = e.stack.split(/\n/g); 
		}
		stack.shift();
		let row = stack[1].replace(/^\s*at\s+/,'').split(" ")[0];
		return row;
	}
	getWindowTitle() {
		return this.windowTitle;
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

}

var leapp = new Leapp(true);
leapp.trayMenuClick = function(menu){
	if (menu == "Выход") leapp.exit();
	if (menu == "Настройки") console.log("Открываем меню настроек");
}