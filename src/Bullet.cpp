#include "Bullet.h"
#include "Base.h"

Bullet::Bullet() {
    _texture.loadFromFile("candy.png");
    _bullet.setTexture(_texture);
    _bullet.setPosition(350,530);

    _velocity = {1,1};

    _buffer.loadFromFile("laserShoot.wav");
    _sound.setBuffer(_buffer);
    _sound.setVolume(20.f);
}

bool Bullet::update() {

    _bullet.move(_velocity);

    return _bullet.getPosition().y + _bullet.getGlobalBounds().height > 0;
}

void Bullet::respawn(const sf::Sprite& baseSprite) {
    sf::Vector2f basePosition = baseSprite.getPosition();
    _bullet.setPosition(
        basePosition.x + baseSprite.getGlobalBounds().width / 2 - _bullet.getGlobalBounds().width / 2,
        basePosition.y - _bullet.getGlobalBounds().height
    );
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states)const {

    target.draw(_bullet, states);
}

sf::FloatRect Bullet::getBounds() const{

    return _bullet.getGlobalBounds();
}

Bullet::~Bullet()
{
    //dtor
}
