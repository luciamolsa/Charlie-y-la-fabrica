#include "Menu.h"

Menu::Menu()
{
	font.loadFromFile("gomarice_gogono_cocoa_mochi.ttf");
	//tex.loadFromFile("fondo.png");

	// jugar
	mainMenu[0].setFont(font);
	mainMenu[0].setColor(sf::Color::Blue);
	mainMenu[0].setString("Jugar");
	mainMenu[0].setCharacterSize(50);
	mainMenu[0].setPosition(120, 80);

	//puntaje maximo
	mainMenu[1].setFont(font);
	mainMenu[1].setColor(sf::Color::Black);
	mainMenu[1].setString("Puntaje Maximo");
	mainMenu[1].setCharacterSize(50);
	mainMenu[1].setPosition(120, 160);

	//salir
	mainMenu[2].setFont(font);
	mainMenu[2].setColor(sf::Color::Black);
	mainMenu[2].setString("Salir");
	mainMenu[2].setCharacterSize(50);
	mainMenu[2].setPosition(120, 240);

	mainMenuSelected = 0;
}

void Menu::Draw(sf::RenderWindow &window){
	for (int i=0; i<3; i++){
		window.draw(mainMenu[i]);
	}
}

void Menu::moveDown(){
	if (mainMenuSelected + 1 <= Max_main_menu) { // chequea que no sea el ultimo item (salir)
		mainMenu[mainMenuSelected].setColor(sf::Color::Black); // cambia color del anterior

		mainMenuSelected++; //se mueve al item de abajo
		if (mainMenuSelected == 3) mainMenuSelected = 0;

		mainMenu[mainMenuSelected].setColor(sf::Color::Blue); // cambia el color del que se elige
	}
}

void Menu::moveUp(){
	if (mainMenuSelected - 1 >= -1) { // chequea que no sea el primer item (jugar)
		mainMenu[mainMenuSelected].setColor(sf::Color::Black); // cambia color del anterior

		mainMenuSelected--; //se mueve al item de arriba
		if (mainMenuSelected == -1) mainMenuSelected = 2;

		mainMenu[mainMenuSelected].setColor(sf::Color::Blue); // cambia el color del que se elige
	}
}
