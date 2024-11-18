#include<iostream>
#include "Base.h"
#include "Bullet.h"
using namespace std;

Base::Base() {

    _texture.loadFromFile("base.png");
    _base.setTexture(_texture);
    _base.setPosition(360,550);
    _velocity = 4;
    _base.setOrigin(_base.getGlobalBounds().width/2,0);
    _shooterActive = false;
}

void Base::update() {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _base.move(_velocity,0);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_base.move(-_velocity,0);
    }

    if(_base.getGlobalBounds().left < 10) {
        _base.setPosition(_base.getOrigin().x+10,_base.getPosition().y);
    }

    if(_base.getPosition().x + _base.getGlobalBounds().width > 840) {
        _base.setPosition(840 - _base.getGlobalBounds().width,_base.getPosition().y);
    }

    if (_shooterActive && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        Bullet bala;
        bala.respawn(_base);
        _balas.push_back(bala);
    }

    for (auto it = _balas.begin(); it != _balas.end();) {
        if (!it->update()) {
            it = _balas.erase(it);
        } else {
            ++it;
        }
    }

}
void Base:: respawn() {

    _base.setPosition(360,550);

}

void Base::draw(sf::RenderTarget& target, sf::RenderStates states)const {

    target.draw(_base, states);

    for (const auto& bala : _balas) {
        target.draw(bala, states);
    }
}

sf::FloatRect Base:: getBounds()const {

    return _base.getGlobalBounds();

}

void Base::increaseSpeed(int n) {
	n=4+n*0.2;
	_velocity=n;
}

float Base::getVelocity() {
	return _velocity;
}

void Base::sizeReduce() {
    _base.scale(0.7f, 1.0f);
}

void Base::sizeIncrease() {
    _base.scale(2.0f, 1.0f);

}

void Base::activateShoot() {
    _shooterActive = true;
}

const vector<Bullet>& Base::getBalas() {
    return _balas;
}

Base::~Base()
{
    //dtor
}

