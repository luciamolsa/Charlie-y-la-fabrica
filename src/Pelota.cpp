#include<iostream>
#include "Pelota.h"
using namespace std;


Pelota::Pelota(){

    _texture.loadFromFile("pelota.png");
    _sprite.setTexture(_texture);
    _sprite.setPosition(350,530);

    _velocity = {1,1};

    _buffer.loadFromFile("Rebote.wav");
    _sound.setBuffer(_buffer);
    _sound.setVolume(20.f);

}

bool Pelota::update(){

    _sprite.move(_velocity);

    if(_sprite.getPosition().x < 0){
        _velocity.x = -_velocity.x;
        _sound.play();

    }
    if(_sprite.getPosition().y < 0){
        _velocity.y = -_velocity.y;
        _sound.play();

    }
    if(_sprite.getPosition().x + _sprite.getGlobalBounds().width > 800){
        _velocity.x = -_velocity.x;
        _sound.play();

    }
    if(_sprite.getPosition().y + _sprite.getGlobalBounds().height > 600){ ///configurar piso para que pierda vidas

        return false;
    }
    return true;

}

void Pelota::bounce(){

    _velocity.y = -_velocity.y;
    _sound.play();

}

void Pelota::respawn(){

    _sprite.setPosition(350,530);
}

void Pelota::draw(sf::RenderTarget& target, sf::RenderStates states)const {

    target.draw(_sprite, states);
}

sf::FloatRect Pelota::getBounds() const {

    return _sprite.getGlobalBounds();
}

void Pelota::base(float v) {

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _sprite.move(v, 0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_sprite.move(-v, 0);
    }

    if(_sprite.getPosition().x + _sprite.getGlobalBounds().width > 750) {
        _sprite.setPosition(750 - _sprite.getGlobalBounds().width,_sprite.getPosition().y);
    }

    if(_sprite.getGlobalBounds().left < 50) {
        _sprite.setPosition(_sprite.getOrigin().x+50,_sprite.getPosition().y);
    }
}

void Pelota::increaseSpeed(float n) {
   _velocity.x *= n;    /// Incremento de velocidad en la misma direccion.
   _velocity.y *= n;     /// Incremento de velocidad en la misma direccion.
	/*n = n*0.7;
	_velocity = {n,n};*/
}

vector<Pelota> Pelota::multiply() const {
    vector<Pelota> pelotas;
    for (int i = 0; i < 3; i++) {
        pelotas.push_back(*this);
    }
    return pelotas;
}

Pelota::~Pelota()
{
    //dtor
}

