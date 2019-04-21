'use strict';

class Leapp {
	constructor() {
		this.window = {
			width: 0,
			height: 0,
			left: 0,
			top: 0,
			title: "Example"
		};
		this.debug = false;
		this.windowtitle = "";
		this.windowstate = "";
		this.windowwidth = 100;
		this.windowheight = 100;
		this.windowleft = 100;
		this.windowtop = 100;
	}

// Изменение размера родительского окна.
	resize(width, height, callback) {
		if (typeof width == 'undefined' || !Number.isInteger(width)) width = -1;
		if (typeof height == 'undefined' || !Number.isInteger(height)) height = -1;
		var me = this;
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			channel.objects.leapp.resize(width, height, function(data){
				if (typeof data.width != undefined && typeof data.height != undefined) {
					me.window.width = data.width;
					me.window.height = data.height;
				}
				if (typeof callback === "function") callback(data);
			});
		});
	}
// Изменение/получение ширины родительского окна.
	set width(width) {
		if (typeof width != 'undefined' && !Number.isInteger(width)) this.resize(Number(width));
	} get width(){ return this.window.width; }
// Изменение/получение высоты родительского окна.
	set height(height) {
		if (typeof height != 'undefined' && !Number.isInteger(height)) this.resize(-1, Number(height));
	} get height(){ return this.window.height; }


// Изменение положения родительского окна.
	move(left, top, callback) {
		if (typeof left == 'undefined' || !Number.isInteger(left)) left = -1;
		if (typeof top == 'undefined' || !Number.isInteger(top)) top = -1;
		var me = this;
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			channel.objects.leapp.move(left, top, function(data){
				if (typeof data.left != undefined && typeof data.top != undefined) {
					me.window.left = data.left;
					me.window.top = data.top;
				}
				if (typeof callback === "function") callback(data);
			});
		});
	}
// Изменение/получение позиции по оси x родительского окна.
	set left(left) {
		if (typeof left != 'undefined' && !Number.isInteger(left)) this.move(Number(left));
	} get left(){ return this.window.left; }
// Изменение/получение позиции по оси y родительского окна.
	set top(top) {
		if (typeof top != 'undefined' && !Number.isInteger(top)) this.move(-1, Number(top));
	} get top(){ return this.window.top; }
// Изменение/получение заголовка окна
	set title(title) {
		if (typeof title === undefined) title = " ";
		var me = this;
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			me.window.title = title;
			channel.objects.leapp.title(title);
		});
	} get title() { return this.window.title; }


/////////////
// METHODS //
/////////////

// Перезагрузка содержимого окна
	reload(url) {
		if (typeof url === undefined) url = "";
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			channel.objects.leapp.reload(url);
		});
	}
// Спрятать программу в трей.
	hide() {
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			channel.objects.leapp.hide();
		});
	}
// Показать программу
	show() {
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			channel.objects.leapp.show();
		});
	}
// Выход из приложения
	exit() {
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			channel.objects.leapp.exit();
		});
	}


////////////
// EVENTS //
////////////

// Событие изменения размера родительского окна
	onResize(width, height) {
		return true;
	}	
// событие при перемещении родительского окна
	onMove(left, top) {
		return true;
	}
// Событие при закрытии окна
	onResize(width, height) {
		return true;
	}



	get ping () {
		return "pong";
	}
	set debugEnable (enable) {
		this.debug = (typeof(enable) != 'undefined' && (enable == "1" || enable == "true")) ? 1 : 0;
		console.log(this.methodName);
	}

	set windowState(state) {
		this.windowstate = state;
		console.log(this.methodName);
	}


	
	sql(query, callback) {
		// let event = {fun: "sql", query: query, callback: eval(callback).toString()};
		// console.log(JSON.stringify(event));
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			var temp = channel.objects.qtObject.resize(300, 500, function(e){
				callback(e);
			});
		});
	}

	trayMenuClick(name) {
		return true;
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