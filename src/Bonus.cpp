#include "Bonus.h"
#include "Base.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Bonus::Bonus() : _aparece(false) {
    _texture.loadFromFile("Ricky1.png");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);

    srand(static_cast<unsigned>(time(0)));
    resetPosition();
    _coin.loadFromFile("miami.wav");
	_canal.setBuffer(_coin);
	_canal.setVolume(200.f);
}

void Bonus::activar() {
    _aparece = true;
}

void Bonus::desactivar(){
   _aparece=false;
   resetPosition();
}

void Bonus::update() {
    if (_aparece) {
        _sprite.move(0, 2);

        if (_sprite.getPosition().y > 600) {
            _aparece = false;
            resetPosition();
        }
    }
}

void Bonus::resetPosition() {
    float x = static_cast<float>(rand() % 600);
    _sprite.setPosition(x, 0);
}

void Bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_aparece) {
        target.draw(_sprite, states);
    }
}

sf::FloatRect Bonus::getBounds() const {
    return _sprite.getGlobalBounds();
}

void Bonus::randomBonus(int randomOption, Base& base, vector<Pelota>& pelotas) {
    switch (randomOption) {
        case 1:
            base.sizeReduce();
            break;

        case 2:
            base.sizeIncrease();
            break;

        case 3:
            if (!pelotas.empty()) {
                vector<Pelota> nuevasPelotas = pelotas[0].multiply();

                pelotas.insert(pelotas.end(), nuevasPelotas.begin(), nuevasPelotas.end());
                // Agrega las pelotas necesarias partiendo desde el ppio del vector, insertando los elementos del nuevo vector
            }

            break;

        case 4:
            //for each -> es un for de cada elemento del vector :)
            for (Pelota& pelota : pelotas) {
                pelota.increaseSpeed(1.1);
            }
            break;

        default:
            cout << "Opcion invalida rey." << endl;
            break;
    }
}
