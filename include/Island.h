#ifndef ISLAND_H
#define ISLAND_H

#include <cmath>

#include "Entity.h"

unsigned const int organicNebula = 16;

class Island : public Entity
{
    public:
        Island();
       ~Island();

    float getPosX () {return posX;}
    float getPosY () {return posY;}
    void  setPosXY (float x, float y);

    void updateMovex(sf::Vector2f& s_World, bool isBoss);

    void setAlpha(float a){alpha = a;};
    float getAlpha() {return alpha;};
    void stepAlpha();

    void autoSetOrganicIslandT();
    void autoSetOrganicIslandB();
    void autoSetSpIsland();

    void RotateOrganicBP(); // clockwise rotation
    void RotateOrganicTP(); // against clockwise rotation

    sf::Sprite islandSp;
    sf::CircleShape organicIB[organicNebula]; //bottom
    sf::CircleShape organicIT[organicNebula]; //top

    public:
        float globalRadiusB;
        float globalRadiusT;

    private:
       float posX;
       float posY;

       float alpha; // ungle in radians (rotation)
};

#endif // ISLAND_H
