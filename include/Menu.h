#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#define Max_main_menu 3

class Menu
{
	public:
		Menu();
		void draw(sf::RenderWindow &window);
		void moveUp();
		void moveDown();
		int mainMenuPressed(){return mainMenuSelected;}

	private:
		int mainMenuSelected;
		sf::Font font;
		sf::Text mainMenu[Max_main_menu];
		sf::Texture tex;

};

#endif // MENU_H
