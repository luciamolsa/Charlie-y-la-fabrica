#include<iostream>
#include "Base.h"
#include "Bullet.h"
#include "Bullet.h"
using namespace std;

Base::Base() {

    _texture.loadFromFile("base.png");
    _base.setTexture(_texture);
    _base.setPosition(360,550);
    _velocity = 4;
    _shooterActive = false;
    _base.setOrigin(_base.getLocalBounds().width/2,0);
}

void Base::update() {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _base.move(_velocity,0);

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_base.move(-_velocity,0);
    }

    if(_base.getPosition().x - _base.getLocalBounds().width/2  * _base.getScale().x < 10){

        _base.setPosition(_base.getLocalBounds().width/2 * _base.getScale().x +10 ,_base.getPosition().y);
    }

    if(_base.getPosition().x + _base.getLocalBounds().width/2  * _base.getScale().x > 790){
        _base.setPosition(790 -_base.getLocalBounds().width/2 * _base.getScale().x , _base.getPosition().y);
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
    _base.setScale(1.0f,1.0f);
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
	n = 4 + n*0.2;
	_velocity = n;
}

float Base::getVelocity() {
	return _velocity;
}

void Base::sizeReduce() {
    _base.setScale(0.7f, 1.0f);
    _base.setOrigin(_base.getLocalBounds().width/2,0);
}

void Base::sizeIncrease() {
    _base.setScale(2.0f, 1.0f);
    _base.setOrigin(_base.getLocalBounds().width/2,0);
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

