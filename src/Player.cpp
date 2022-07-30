#include "Player.h"

Player::Player()
: countFLK(0)
, moduleFLK(10)
, repeatCControl(0) //
, countROT(0)
, uRotANGL(2)
, markTi(0)
, colorTiRg(0)
, blameVisibleUP(false)
{
   col.Black;
   this->setWH(189.f,189.f);
   this->sP.setOrigin( (getH()/2), (getW()/2) );
   this->setBV(-7.0);

}

Player::~Player()
{
    //dtor
}

void Player::autoSetPositionStart()
{
     sP.setPosition(570.f, 670.f);
     sP.setTextureRect(sf::IntRect(0.f, 0.f,189.f,189.f));
     this->autoRemapColliders();
     this->autoSetDirectionsZero();
     this->autoSetBlameBehind();
}

void Player::autoRemapColliders()
{
    float WorH = 189.f; // width or length of side of the sprite
    float halfPart = WorH/2; // halth width
    float xC = sP.getPosition().x; // the position of the x coordinate at this moment
    float yC = sP.getPosition().y; // the position of the y coordinate at this moment

    // collider points wrotes in array by ñlockwise
    this->setColliderPointsXY(0, xC, yC);
    this->setColliderPointsXY(1, (xC + halfPart), yC);
    this->setColliderPointsXY(2, (xC + WorH), yC);
    this->setColliderPointsXY(3, (xC + WorH), (yC + halfPart));
    this->setColliderPointsXY(4, (xC + WorH), (yC + WorH));
    this->setColliderPointsXY(5, (xC + halfPart), (yC + WorH));
    this->setColliderPointsXY(6, xC, (yC + WorH));
    this->setColliderPointsXY(7, xC, (yC + halfPart));
}

void Player::autoSetDirectionsZero()
{
   isUP = false;
   isDOWN = false;
   isLEFT = false;
   isDOWN =false;
}

void Player::startBullet()
{
    float startPX = sP.getPosition().x - 10.f; //halth radius
    float startPY = sP.getPosition().y - getH()/2;

    sf::CircleShape SHP;
    SHP.setRadius(10.f);
    SHP.setFillColor(sf::Color::Yellow);
    SHP.setOutlineThickness (-2.f);
    SHP.setOutlineColor(sf::Color::Red);
    SHP.setPosition(startPX, startPY);
    bulletVec.push_back(SHP);
    //std::cout << "START << BULLET *** " << std::endl;
}

void Player::dettachBullet(std::vector<sf::CircleShape>::iterator dellete)
{
    if(dellete != bulletVec.end()) bulletVec.erase(dellete);
    //std::cout << "detachBULL << BV SIZE " << bulletVec.size() << std::endl;

}

void Player::autoSetBlameBehind()
{
    float blameX = sP.getPosition().x - 23.5f;
    float blameY = sP.getPosition().y + getH()/2 - 27.f;
    float step = 10.f;
    float novaX = blameX;
    float novaY = blameY;

    for (int blm=0; blm<15; blm++)
    {
        float trans = 110 + rand()%140;
        float radius = 4;
        blameBehind[blm].setFillColor(sf::Color(127,226,255,trans));
        blameBehind[blm].setRadius(radius);

        if (novaX > (blameX + step*3))
        {
           blameBehind[blm].setPosition(novaX, novaY);
           novaX = blameX;
           novaY = novaY+step;
        }
        else
        {
           blameBehind[blm].setPosition(novaX, novaY);
           novaX = novaX+step;
        };//end of if
    };//end of for
}
