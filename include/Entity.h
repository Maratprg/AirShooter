#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"


class Entity
{
    public:
        Entity();
        ~Entity();

        sf::Vector2f getVelocity() { return velocity; }
        void setVelocity(sf::Vector2f val) { velocity = val; }
        void setVelocity(float x, float y) { velocity.x = x; velocity.y = x; }

        void setWH(float w, float h) { width = w; height = h; }
        float getW() { return width; };
        float getH() { return height; };

        bool getTrigerable() { return trigerable; }
        void setTrigerable(bool val) { trigerable = val; }

        bool getVisible() { return visible; }
        void setVisible(bool val) { visible = val; }

        int getHealth() { return health; }
        void setHealth(int h) { health = h; }

        int getScore() { return score; }
        void setScore(int s) { score = s; }

        void setColliderPointX (int n, float x);
        float getColliderPointX (int n);

        void setColliderPointY (int n, float y);
        float getColliderPointY (int n);

        void setColliderPointsXY(int n, float x, float y);
        sf::Vector2f& getColliderPointVector (int n);

        void setBV (float bV); // bullet velocity
        float getBV ();

        void swapVisible();

    public:
        bool isUP;      //directions of entity
        bool isDOWN;
        bool isLEFT;
        bool isRIGHT;

    private:
        sf::Vector2f velocity;      //velocity of entity
        bool trigerable;            //trigering in game
        bool visible;               //visibility
        int health;                 //health
        int score;                  //score
        float colliderPointsX [8];  //colliderpoinsX
        float colliderPointsY [8];  //colliderpoinsY

        float width; float height;  // with and height enemy
         float bulletVel;           // velocity bullet
};

#endif // ENTITY_H
