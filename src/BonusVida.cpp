#include "BonusVida.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

BonusVida::BonusVida() : _aparece(false) {
    _texture.loadFromFile("MasVida.jpg");

    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);

    srand(static_cast<unsigned>(time(0)));
    reseteoPosicion();
}

void BonusVida::activar() {
    _aparece = true;
}

void BonusVida::update() {
    if (_aparece) {
        _sprite.move(0, 2);

        if (_sprite.getPosition().y > 600) {
            _aparece = false;
            reseteoPosicion();
        }
    }
}

void BonusVida::reseteoPosicion() {
    float x = static_cast<float>(rand() % 600);
    _sprite.setPosition(x, 0);
}

void BonusVida::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_aparece) {
        target.draw(_sprite, states);
    }
}

sf::FloatRect BonusVida::getBounds() const {
    return _sprite.getGlobalBounds();
}
