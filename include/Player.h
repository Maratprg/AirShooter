#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include <vector>

class Player : public Entity
{
    public:
        Player();
        ~Player();

       sf::Sprite sP;
       sf::Image img;
       sf::Color col;

       void autoSetPositionStart();
       void autoRemapColliders();
       void autoSetDirectionsZero();
       void autoSetBlameBehind();

       int countFLK; // flicker iteration counter
       int moduleFLK; // the modulus of the number of taking values from the global time
       int repeatCControl; // repeat controller variable

       int countROT;  // the numbers of rotaion
       float uRotANGL; // ungle of rotation


       int markTi; // variable that checks the color changing
       int colorTiRg; // time in milliseconds to change color

       float time_chc; // collor changing total time

       public:
            std::vector <sf::CircleShape> bulletVec;
            void startBullet();
            void dettachBullet(std::vector<sf::CircleShape>::iterator dellete);

            sf::CircleShape blameBehind[15];
            bool blameVisibleUP;
            bool blameVisibleDOWN;
            bool blameVisibleLEFT;
            bool blameVisibleRIGHT;
};

#endif // PLAYER_H
