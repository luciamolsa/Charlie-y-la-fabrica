#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Pelota.h"
#include "Base.h"
#include "Ladrillo.h"
#include "Puntaje.h"
#include "Menu.h"
#include "Bonus.h"
#include "BonusVida.h"
#include <vector>

void gameover();

int main()
{
	while (true){

		//inicializo ventana
		sf::RenderWindow window(sf::VideoMode(600,  600), "menu");
		window.setFramerateLimit(80);

		sf::Sprite imag;
		sf::Texture tex;
		tex.loadFromFile("fondoinicio.png");
		imag.setTexture(tex);

		sf::Music musica;
		musica.openFromFile("cancion.wav");
		musica.setVolume(10);
		musica.setLoop(true);
		musica.play();

		Menu menu;
		int option;

		//Game Loop
		while (window.isOpen()) {

			// Read Input: Actualiza los estados de los periféricos de entrada
			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed){

					window.close();
					return 0;
				}
				if (event.type == sf::Event::KeyReleased){

					if (event.key.code == sf::Keyboard::Up) {
						menu.moveUp();
						break;
					}
					if (event.key.code == sf::Keyboard::Down) {
						menu.moveDown();
						break;
					}
					// elegir opcion
					if (event.key.code == sf::Keyboard::Return) { // enter
						int x = menu.mainMenuPressed();

						switch (x){
						case 0:
							window.close();
							option = 0;
							break;
						case 1:
							window.close();
							option = 1;
							break;
						case 2:
							window.close();
							option = 2;
							break;

						}
					}
				}
				if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) ){
					return 0;
				}
			}

			window.clear();
			window.draw(imag);
			menu.Draw(window);
			window.display();

		}

		switch (option){
			case 0: {// jugar

				sf::RenderWindow window_play(sf::VideoMode(1200,  600), "play");
				window_play.setFramerateLimit(80);

				sf::Font font;
				font.loadFromFile("Raleway-Bold.ttf");
				sf::Text puntaje, vidas, puntMax, level;

				puntaje.setFont(font);
				vidas.setFont(font);
				puntMax.setFont(font);
				level.setFont (font);

				puntaje.setPosition(810,5);
				vidas.setPosition(810,35);
				puntMax.setPosition(810,65);
				level.setPosition(810, 315);

				std::vector<Pelota> pelota;
                Pelota p;
                pelota.push_back(p);
				Base base;
				Ladrillo ladrillo[81];
				BonusVida bonusvida;
				Bonus bonus;

				int ladrillos = 81;
				for (int i = 0; i < ladrillos; i++){
					ladrillo[i].position(i+1);
				}
				Puntaje pmax;

				int puntos = 0;
				int vida = 3;
				bool comienzo = false;
				int nivel = 1;
				int ladrillos_rotos = 0;

				sf::Sprite image, im;
				sf::Texture tex, gameO;
				tex.loadFromFile("fondo.png");
				gameO.loadFromFile("game-over.png");
				image.setTexture(tex);
				im.setTexture(gameO);

				sf::Sound canal, canal1, canal2;
				sf::SoundBuffer gameOver, bastaChicos, miami;
				gameOver.loadFromFile("game-over.wav");
				bastaChicos.loadFromFile("BastaChicos.wav");
				miami.loadFromFile("inicioNivel.wav");
				canal1.setVolume(150);
				canal.setVolume(150);
				canal2.setVolume(150);
				canal.setBuffer(gameOver);
				canal1.setBuffer(bastaChicos);
				canal2.setBuffer(miami);

				while (window_play.isOpen()){
					sf::Event event;

					while (window_play.pollEvent(event)){
						if (event.type == sf::Event::Closed){
							window_play.close();
						}
					}

					if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space)){
						comienzo = true;
					}

					if(comienzo){
						pelota[0].update();
						base.update();
						bonus.update();

						for (int i = 0; i < ladrillos; i++){
							if(pelota[0].isCollision(ladrillo[i])){
								ladrillo[i].roto();
								ladrillo[i].disapear();
								pelota[0].bounce();
								puntos++;
								ladrillos_rotos++;
							}
						}

						if(pelota[0].isCollision(base)){
							pelota[0].bounce();
						}
						///CUANDO SE ROMPA CIERTA CANTIDAD DE LADRILLOS CAIGA.
                        if (ladrillos_rotos % 5 == 0 && ladrillos_rotos > 0 ||
                            sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) { //Si se necesita probar el bonus, apretar TAB
                            bonus.activar();
                        }

                        if(bonus.isCollision(base)){
                            pelota[0].increaseSpeed(3);
                            puntos++;
                        }

                        if (bonus.aparece()) {
                            if (bonus.getBounds().top > 600) {
                                bonus.resetPosition();
                            }
                        }

                        if (ladrillos_rotos == ladrillos){
                            bonus.resetPosition();
                        }

						if(pelota[0].update() == false && vida > 1){
							vida--;
							canal.play();
							pelota[0].respawn();
							base.respawn();
							comienzo = false;
							pelota[0].increaseSpeed(2);
						}

						if(pelota[0].update() == false && vida == 1){
							vida = 0;
							pmax.leerDeDisco();
							if (puntos > pmax.getPuntaje()){
								pmax.setPuntaje(puntos);
								pmax.grabarEnDisco();
							}

							window_play.close();
							gameover();
						}

						if (ladrillos_rotos == ladrillos){
							//nuevo nivel

							canal2.play();

							nivel++;
							pelota[0].increaseSpeed(nivel);
							base.increaseSpeed(nivel);
							puntos += 10;
							vida = 3; // se restauran las 3 vidas
							pelota[0].respawn();
							base.respawn();
							comienzo = false;
							ladrillos_rotos = 0;

							for (int i = 0; i < ladrillos; i++){
								ladrillo[i].position(i+1); // vuelven a armarse la pared
							}

						}
					}
					else{
						// pelota y base en el medio. Se mueven juntas
						pelota[0].Base(base.getVelocity());
						base.update();
					}

					pmax.leerDeDisco();

					puntaje.setString(" Puntaje:  "+  std::to_string(puntos));
					vidas.setString(" Vidas:  "+ std::to_string(vida));
					puntMax.setString(" Puntaje Maximo:  "+ std::to_string(nivel));
					level.setString("  Nivel:   "+ std::to_string(pmax.getPuntaje()));

					window_play.clear();
					window_play.draw(image);
					window_play.draw(pelota[0]);
					window_play.draw(base);
					window_play.draw(bonus);
					for(int i = 0; i < ladrillos; i++){
						window_play.draw(ladrillo[i]);
					}
					window_play.draw(puntaje);
					window_play.draw(vidas);
					window_play.draw(puntMax);
					window_play.draw(level);
					window_play.display();

					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						pmax.leerDeDisco();
						if (puntos>pmax.getPuntaje()){
							pmax.setPuntaje(puntos);
							pmax.grabarEnDisco();
						}
						// vuelta al menu
						window_play.close();
					}

				}

			break;
			}
			case 1:{ // puntaje maximo
				sf::RenderWindow window_p(sf::VideoMode(600,  600), "puntaje_max", sf::Style::Close);

				sf::Sprite im;
				sf::Texture text;
				text.loadFromFile("fondoinicio.png");
				im.setTexture(text);

				sf::Font f;
				f.loadFromFile("gomarice_gogono_cocoa_mochi.ttf");
				sf::Text puntajeMax, punt;

				// puntaje maximo letras
				puntajeMax.setFont(f);
				puntajeMax.setCharacterSize(50);
				puntajeMax.setPosition(110,200);
				puntajeMax.setColor(sf::Color::Blue);
				// puntaje numero
				punt.setFont(f);
				punt.setCharacterSize(50);
				punt.setPosition(300,300);
				punt.setColor(sf::Color::Blue);

				while (window_p.isOpen()){
					sf::Event event;

					while (window_p.pollEvent(event)){
						if (event.type == sf::Event::Closed){
							window_p.close();
						}
						if (event.key.code == sf::Keyboard::Escape) {
							// vuelta al menu
							window_p.close();
						}
					}

					Puntaje pmax;
					pmax.leerDeDisco();
					puntajeMax.setString("Puntaje Maximo");
					punt.setString(std::to_string(pmax.getPuntaje()));

					window_p.clear();
					window_p.draw(im);
					window_p.draw(puntajeMax);
					window_p.draw(punt);
					window_p.display();

				}

			break;
			}
			case 2: { // salir
				return 0;
			}
		}

	}

return 0;
}

void gameover(){
	sf::RenderWindow window_gameover(sf::VideoMode(600,  600), "game over", sf::Style::Close);

	sf::Sprite im;
	sf::Texture text;
	text.loadFromFile("game-over.png");
	im.setTexture(text);

	sf::Font f;
	f.loadFromFile("gomarice_gogono_cocoa_mochi.ttf");
	sf::Text gameover;

	gameover.setFont(f);
	gameover.setCharacterSize(70);
	gameover.setPosition(130,200);
	gameover.setColor(sf::Color::Blue);

	sf::Sound canal1;
	sf::SoundBuffer bastaChicos;
	bastaChicos.loadFromFile("BastaChicos.wav");
	canal1.setVolume(150);
	canal1.setBuffer(bastaChicos);
	canal1.play();

	while (window_gameover.isOpen()){

		sf::Event event;

		while (window_gameover.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				// vuelta al menu
				window_gameover.close();
			}
			if (event.key.code == sf::Keyboard::Escape) {
				// vuelta al menu
				window_gameover.close();
			}
		}

		gameover.setString("GAME OVER");

		window_gameover.clear();
		window_gameover.draw(im);
		window_gameover.draw(gameover);
		window_gameover.display();
	}
}
