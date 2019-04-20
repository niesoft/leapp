let leapp = new Leapp();
leapp.trayMenuClick = function(menu){
	if (menu == "Выход") leapp.exit();
	if (menu == "Настройки") console.log("Открываем меню настроек");
}
