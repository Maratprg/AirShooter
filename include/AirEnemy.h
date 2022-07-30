#ifndef AIRENEMY_H
#define AIRENEMY_H

#include "Entity.h"

class AirEnemy : public Entity
{
    public:
        AirEnemy();
        ~AirEnemy();

    sf::Sprite sP;
    void setIsland (bool b) { isIsland = b; };
    bool getIsland () { return isIsland; };

        int countFLK; // flicker iteration counter
        int moduleFLK; // the modulus of the number of taking values from the global time
        int repeatCControl; // repeat controller variable

        int repeatCEnemyControl; // controller variable that remember time to generator of bullets (may be never used)

    public:
            std::vector <sf::CircleShape> bulletVec;
            void startBullet();
            void dettachBullet(std::vector<sf::CircleShape>::iterator dellete);
    private:
         bool isIsland;

};

#endif // AIRENEMY_H
