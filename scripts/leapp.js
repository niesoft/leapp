'use strict';

class Leapp {
	constructor() {
		this.window = {
			width: 0, height: 0,
			minWidth: 0, minHeight: 0,
			left: 0, top: 0,
			title: "Example",
			state: 0, style: 0,
			path: ""
		};
		this.debug = false;
		this.windowstate = "";
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

// Изменение минимального размера родительского окна.
	minSize(width, height, callback) {
		if (typeof width == 'undefined' || !Number.isInteger(width)) width = -1;
		if (typeof height == 'undefined' || !Number.isInteger(height)) height = -1;
		var me = this;
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			channel.objects.leapp.minSize(width, height, function(data){
				if (typeof data.width != undefined && typeof data.height != undefined) {
					me.window.width = data.width;
					me.window.height = data.height;
				}
				if (typeof callback === "function") callback(data);
			});
		});
	}
// Изменение/получение минимальной ширины родительского окна.
	set minWidth(minWidth) {
		if (typeof minWidth != 'undefined' && !Number.isInteger(minWidth)) this.minSize(Number(minWidth));
	} get minWidth(){ return this.window.minWidth; }
// Изменение/получение минимальной высоты родительского окна.
	set minHeight(minHeight) {
		if (typeof minHeight != 'undefined' && !Number.isInteger(minHeight)) this.minSize(-1, Number(minHeight));
	} get minHeight(){ return this.window.minHeight; }

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
		if (typeof title == 'undefined') title = " ";
		var me = this;
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			me.window.title = title;
			channel.objects.leapp.title(title);
		});
	} get title() { return this.window.title; }
// Изменение/получение статуса родительского окна
	set state(state) {
		if (typeof state == 'undefined' || Number(state) > 4) state = 0;
		var me = this;
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			me.window.state = Number(state);
			channel.objects.leapp.state(Number(state));
		});
	} get state() { return this.window.state; }
// Изменение/получение стиля родительского окна
	set style(style) {
		if (typeof style == 'undefined' || Number(style) > 7) style = 0;
		var me = this;
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			me.window.style = Number(style);
			channel.objects.leapp.style(Number(style));
		});
	} get state() { return this.window.state; }
// Узнать путь к исполняемому файлу программы
	path() { return this.window.path; }


/////////////
// METHODS //
/////////////

// Перезагрузка содержимого окна
	reload(url) {
		if (typeof url == 'undefined') url = "";
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


///////////////
// FUNCTIONS //
///////////////

// Запрос к БД storage SQLLITE 3
	sql(query, callback) {
		// let event = {fun: "sql", query: query, callback: eval(callback).toString()};
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			var temp = channel.objects.leapp.sql(query, function(data){
				if (typeof callback === "function") callback(data);
			});
		});
	}
// Отправка GET запроса
	get(url, params, callback) {
		var webChannel = new QWebChannel( qt.webChannelTransport, function(channel) {
			var temp = channel.objects.leapp.get(url, params, function(data){
				if (typeof callback === "function") callback(data);
			});
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
let leapp = new Leapp();