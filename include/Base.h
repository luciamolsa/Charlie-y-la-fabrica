#ifndef BASE_H
#define BASE_H
#include <SFML\Graphics.hpp>
#include "Collisionable.h"
#include "Bullet.h"
using namespace std;

class Base: public sf:: Drawable, public Collisionable {

    public:
        Base();
        virtual ~Base();
        void update();
        void respawn();
        void draw(sf::RenderTarget& target,sf::RenderStates states)const override;
        sf::FloatRect getBounds()const override;
        void increaseSpeed(int);
		float getVelocity();
		void sizeReduce();
		void sizeIncrease();
		void activateShoot();
		const vector<Bullet>& getBalas();


    private:

        sf::Sprite _base;
        sf::Texture _texture;
        float _velocity;
        bool _shooterActive;
        vector<Bullet> _balas;
};

#endif // BASE_H
