#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Pelota.h"
#include "Base.h"
#include "Ladrillo.h"
#include "Puntaje.h"
#include "Menu.h"
#include "Bonus.h"
#include <vector>
using namespace std;

void gameover();

int main()
{
    while (true) {
        // Inicializo ventana
        sf::RenderWindow window(sf::VideoMode(600, 600), "menu");
        window.setFramerateLimit(80);

        sf::Sprite imag;
        sf::Texture tex;
        tex.loadFromFile("fondoinicio.png");
        imag.setTexture(tex);

        sf::Music musica;
        //musica.openFromFile("cancion.wav");
        musica.setVolume(10);
        musica.setLoop(true);
        musica.play();

        Menu menu;
        int option;

        // Game Loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return 0;
                }
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Up) {
                        menu.moveUp();
                        break;
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        menu.moveDown();
                        break;
                    }
                    if (event.key.code == sf::Keyboard::Return) {
                        int x = menu.mainMenuPressed();
                        switch (x) {
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
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    return 0;
                }
            }

            window.clear();
            window.draw(imag);
            menu.Draw(window);
            window.display();
        }

        switch (option) {
        case 0: { // Jugar
            sf::RenderWindow window_play(sf::VideoMode(1200, 600), "play");
            window_play.setFramerateLimit(80);

            sf::Font font;
            font.loadFromFile("Raleway-Bold.ttf");
            sf::Text puntaje, vidas, puntMax, level;

            puntaje.setFont(font);
            vidas.setFont(font);
            puntMax.setFont(font);
            level.setFont(font);

            puntaje.setPosition(810, 5);
            vidas.setPosition(810, 35);
            puntMax.setPosition(810, 65);
            level.setPosition(810, 315);

            vector<Pelota> pelotas;
            Pelota pelotita;
            pelotas.push_back(pelotita);
            Base base;
            Ladrillo ladrillo[81];
            Bonus bonus;
            Bullet bullet;

            int cantidadLadrillos = 81;
            for (int i = 0; i < cantidadLadrillos; i++) {
                ladrillo[i].position(i + 1);
            }

            Puntaje pmax;

            int puntos = 0;
            int vida = 20;
            bool comienzo = false;
            int nivel = 1;
            int ladrillosRotos = 0;
            bool bonusCollisionActive = false;
            sf::Clock bonusTimer;


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

            while (window_play.isOpen()) {
                sf::Event event;
                while (window_play.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window_play.close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    comienzo = true;
                }

                if (comienzo) {
                    base.update();
                    bonus.update();
                    int tipoBonus = 0;
                    for (int i = 0; i < pelotas.size(); i++) {
                        pelotas[i].update();
                        if (pelotas[i].isCollision(base)) {
                            pelotas[i].bounce();
                        }

                        for (int j = 0; j < cantidadLadrillos; j++) {
                            if (pelotas[i].isCollision(ladrillo[j])) {
                                ladrillo[j].roto();
                                ladrillo[j].disapear();
                                pelotas[i].bounce();
                                puntos++;
                                ladrillosRotos++;
                            }
                        }

                        if (pelotas.size() == 1 && !pelotas[i].update() && vida > 1) {
                            vida--;
                            canal.play();
                            pelotas[i].respawn();
                            base.respawn();
                            comienzo = false;
                        }
                    }

                    if (ladrillosRotos % 5 == 0 && ladrillosRotos > 0 ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
                        bonus.activar();
                    }

                    if (bonusCollisionActive) {
                        if (bonusTimer.getElapsedTime().asMilliseconds() >= 1) {
                            bonusCollisionActive = false;
                            bonus.resetPosition();
                        }
                    }

                    if (bonus.isCollision(base)&& !bonusCollisionActive) {
                        bonusCollisionActive = true;
                        bonusTimer.restart();
                        puntos *= 2;
                        int tipoBonus = rand() % 4 + 1;
                        bonus.randomBonus(tipoBonus, base, pelotas);
                        for(int i; i < pelotas.size(); i++){
                            pelotas[i].update();
                        }
                        bonus.update();
                        base.update();
                    }
                    for (auto& bala : base.getBalas()) {
                        bullet.update();
                        for (int j = 0; j < cantidadLadrillos; j++) {
                            if (bala.getBounds().intersects(ladrillo[j].getBounds())) {
                                ladrillo[j].roto();
                                ladrillo[j].disapear();
                                puntos++;
                                ladrillosRotos++;
                            }
                        }
                    }

                    if (bonus.aparece() && bonus.getBounds().top > 600) {
                        bonus.resetPosition();
                    }

                    if (ladrillosRotos == cantidadLadrillos) {
                        bonus.resetPosition();
                    }

                    if (pelotas[0].update() == false && vida == 1) {
                        vida = 0;
                        pmax.leerDeDisco();
                        if (puntos > pmax.getPuntaje()) {
                            pmax.setPuntaje(puntos);
                            pmax.grabarEnDisco();
                        }
                        window_play.close();
                        gameover();
                    }

                    if (ladrillosRotos == cantidadLadrillos) {
                        canal2.play();
                        nivel++;
                        pelotas[0].increaseSpeed(nivel);
                        base.increaseSpeed(nivel);
                        puntos += 10;
                        vida = 3;
                        pelotas[0].respawn();
                        base.respawn();
                        comienzo = false;
                        ladrillosRotos = 0;

                        for (int i = 0; i < cantidadLadrillos; i++) {
                            ladrillo[i].position(i + 1);
                        }
                    }
                } else {
                    pelotas[0].base(base.getVelocity());
                    base.update();
                }

                pmax.leerDeDisco();

                puntaje.setString(" Puntaje:  " + std::to_string(puntos));
                vidas.setString(" Vidas:  " + std::to_string(vida));
                puntMax.setString(" Puntaje Maximo:  " + std::to_string(nivel));
                level.setString("  Nivel:   " + std::to_string(pmax.getPuntaje()));

                window_play.clear();
                window_play.draw(image);
                for (int i = 0; i < pelotas.size(); i++) {
                    window_play.draw(pelotas[i]);
                }
                window_play.draw(base);
                window_play.draw(bonus);
                for (int i = 0; i < cantidadLadrillos; i++) {
                    window_play.draw(ladrillo[i]);
                }
                window_play.draw(bullet);
                window_play.draw(puntaje);
                window_play.draw(vidas);
                window_play.draw(puntMax);
                window_play.draw(level);
                window_play.display();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    pmax.leerDeDisco();
                    if (puntos > pmax.getPuntaje()) {
                        pmax.setPuntaje(puntos);
                        pmax.grabarEnDisco();
                    }
                    window_play.close();
                }
            }
            break;
        }
        case 1: { // Puntaje máximo
            sf::RenderWindow window_p(sf::VideoMode(600, 600), "puntaje_max", sf::Style::Close);
            sf::Sprite im;
            sf::Texture text;
            text.loadFromFile("fondoinicio.png");
            im.setTexture(text);

            sf::Font f;
            f.loadFromFile("gomarice_gogono_cocoa_mochi.ttf");
            sf::Text puntajeMax, punt;

            puntajeMax.setFont(f);
            puntajeMax.setCharacterSize(50);
            puntajeMax.setPosition(110, 200);
            puntajeMax.setColor(sf::Color::Blue);
            punt.setFont(f);
            punt.setCharacterSize(50);
            punt.setPosition(300, 300);
            punt.setColor(sf::Color::Blue);

            while (window_p.isOpen()) {
                sf::Event event;
                while (window_p.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window_p.close();
                    }
                    if (event.key.code == sf::Keyboard::Escape) {
                        window_p.close();
                    }
                }
                Puntaje pmax;
                pmax.leerDeDisco();
                puntajeMax.setString("Puntaje Maximo:");
                punt.setString(std::to_string(pmax.getPuntaje()));
                window_p.clear();
                window_p.draw(im);
                window_p.draw(puntajeMax);
                window_p.draw(punt);
                window_p.display();
            }
            break;
        }
        case 2: { // Salir
            return 0;
        }
        }
    }
}

void gameover() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "gameover", sf::Style::Close);
    sf::Sprite imag;
    sf::Texture tex;
    tex.loadFromFile("game-over.png");
    imag.setTexture(tex);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(imag);
        window.display();
    }
}
