#ifndef PELOTA_H
#define PELOTA_H
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Collisionable.h"


class Pelota: public sf:: Drawable, public Collisionable
{

public:
	Pelota();
	virtual ~Pelota();
	bool update();
	void bounce();
	void respawn();
	void draw(sf::RenderTarget& target,sf::RenderStates states)const override;
	sf::FloatRect getBounds() const override;
	void base(float);
	void increaseSpeed(int);
	std::vector<Pelota> multiply() const;

private:

	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _velocity;
	sf::Sound _sound;
	sf::SoundBuffer _buffer;
};

#endif // PELOTA_H
