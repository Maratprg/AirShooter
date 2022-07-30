#ifndef BOSS_H
#define BOSS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"

class Boss : public Entity
{
    public:
        Boss();
        ~Boss();
        sf::Sprite bSp;

    public:
        uint64_t fromFlick;
        uint64_t toFlick;
        int flicCController;

        uint64_t fromChColor;
        uint64_t toChColor;
        int colorCController;

        uint64_t fromRotate;
        uint64_t toRotate;
        int rotateCController;

        uint64_t fromBurn;
        uint64_t toBurn;
        int burnCController;

    public:
        bool soundBorn;
        bool isAlive;
        bool bossIsBurn;

        int replCounter;
        int stageCounter;
        int burnCounter;

        void autoSetPosition(sf::Vector2f& world_S);
        void burnAutoSetPositionBoss();
        void dettachBurn(std::vector<sf::CircleShape>::iterator dellete, std::vector<sf::Vector2f>::iterator dellUVec);

    public:
        std::vector <sf::CircleShape> bulletVec;
        void startBullet(int stage, sf::Vector2f& world_S);
        void dettachBullet(std::vector<sf::CircleShape>::iterator dellete);
        sf::Vector2f threeUvec[3]; // the array of three unit vectors witch set the direction of bullets in the iteration
        void setThreeUVec(int stage);

        std::vector <sf::CircleShape> burnVec;
        std::vector <sf::Vector2f> burnUVec;
};

#endif // BOSS_H
