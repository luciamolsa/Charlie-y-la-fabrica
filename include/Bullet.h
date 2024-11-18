#ifndef BULLET_H
#define BULLET_H
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Collisionable.h"
class Base;
using namespace std;

class Bullet: public sf:: Drawable, public Collisionable {
    public:
        Bullet();
        virtual ~Bullet();
        bool update();
        void respawn(const sf::Sprite& baseSprite);
        void draw(sf::RenderTarget& target,sf::RenderStates states)const override;
        sf::FloatRect getBounds() const override;
    private:
        sf::Sprite _bullet;
        sf::Texture _texture;
        sf::Vector2f _velocity;
        sf::Sound _sound;
        sf::SoundBuffer _buffer;

};

#endif // BULLET_H
