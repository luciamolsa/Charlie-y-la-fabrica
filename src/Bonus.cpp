#include "Bonus.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Bonus::Bonus() : _aparece(false) {
    _texture.loadFromFile("Ricky1.png");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);

    srand(static_cast<unsigned>(time(0)));
    resetPosition();
}

void Bonus::activar() {
    _aparece = true;
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
