#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Collisionable.h"
#include "Base.h"
#include "Pelota.h"
using namespace std;

class Bonus : public sf::Drawable, public Collisionable {

private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    float _velocidad;
    bool _aparece;
    sf::Sound _canal;
	sf::SoundBuffer _coin;

public:
    Bonus();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void resetPosition();
    void activar();
    void desactivar();
    bool aparece() const { return _aparece; }
    void randomBonus(int random, Base& b, vector<Pelota>& pelota);
};

#endif // BONUS_H_INCLUDED
