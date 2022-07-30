#include "AirEnemy.h"

AirEnemy::AirEnemy()
: isIsland(false)
{
    setVelocity(sf::Vector2f(0.f, 1.f)); // set velocity
    // IN ENTITY! seted direction
    setBV(4.f); // set bullet velocity
    sP.setPosition(sf::Vector2f(100.f, 100.f)); // set testing position

    setHealth(21);
    // NOT SET WIDTH AND HEIGH in game class
    // NOT SET SPRITE in game class
    // NOT SET BULLET VECTOR in game class
}

AirEnemy::~AirEnemy()
{
    //dtor
}

void AirEnemy::startBullet()
{
    float startPX = sP.getPosition().x + getW()/2 - 10.f; //halth radius
    float startPY = sP.getPosition().y  + getH();

    for (int i=0; i<3; i++){
    sf::CircleShape SHP;
    SHP.setRadius(10.f);
    SHP.setFillColor(sf::Color::Yellow);
    SHP.setOutlineThickness (-2.f);
    SHP.setOutlineColor(sf::Color::Red);
    SHP.setPosition(startPX, startPY);
    bulletVec.push_back(SHP);
    //std::cout << " started ONE BULLET! " << std::endl;
    }
}

void AirEnemy::dettachBullet(std::vector<sf::CircleShape>::iterator dellete)
{
    if(dellete != bulletVec.end()) bulletVec.erase(dellete);
    //std::cout << " DESTR ONE BULLET! " << std::endl;
    //std::cout << " BULLETS VECTOR SIZE " << bulletVec.size() << std::endl;
}
