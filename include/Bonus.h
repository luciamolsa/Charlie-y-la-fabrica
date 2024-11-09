#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Collisionable.h"

class Bonus : public sf::Drawable, public Collisionable {
    sf::Sprite _sprite;
    sf::Texture _texture;
    float _velocidad;
    bool _aparece;
public:
    Bonus();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void resetPosition();
    void activar();
    bool aparece() const { return _aparece; }
};

#endif // BONUS_H_INCLUDED
