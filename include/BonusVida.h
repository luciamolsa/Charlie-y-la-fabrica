#ifndef BONUSVIDA_H_INCLUDED
#define BONUSVIDA_H_INCLUDED
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Collisionable.h"

class BonusVida : public sf::Drawable, public Collisionable {
    sf::Sprite _sprite;
    sf::Texture _texture;
    float _velocidad;
    bool _aparece;

public:
    BonusVida();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void reseteoPosicion();
    void activar();
    bool aparece() const { return _aparece; }
};

#endif // BONUSVIDA_H_INCLUDED
