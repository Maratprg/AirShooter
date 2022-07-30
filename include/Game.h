#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>

#include "ResourceHolder.h"
#include "Entity.h"
#include "Player.h"
#include "Cloud.h"
#include "AirEnemy.h"
#include "SceneNode.h"
#include "Island.h"
#include "Text.h"
#include "Boss.h"


//implementation of global
class Game
{
    public:
            Game();
            ~Game();
        void run();

    public:
         sf::Clock clock;
         sf::Clock iternal_clk;

    private:
        void processEvents();
        void processEnenmyBullets(int32_t t);
          void brainwishCollide();
        void update(sf::Time elapsedTime);
        void drawAll();
        void upDateAndDrawLandscape(bool boss);

        void handlePlayerInput(sf::Event event);
        void handleMouseButton();

    public:
        static const float      playerSpeed;
        static const sf::Time   timePerFrame;
        sf::RenderWindow mWindow;

        int airEnemyCControl; // bullets time variable
        int bossEnemyCControll; // bullets time variable

    // all for text
    public:
        Text gameText;

    // all for variables triger variables
    public:
        bool isBoss; // general boss trigger

        bool is_PlFlick; // player flick triger
        bool is_PlColor; // player change color triger
        bool is_PlSpin; // player spin triger
        void resetAllTrigers();

    // all for resourses, conception of RAII
    public:
        ResourceHolder ReS;

    // all for textures
    public:
        sf::Sprite      mLandscapeFirst; // sprite one for scrolling backplane
        sf::Sprite      mLandscapeSecond; // sprite two for scrolling backplane

        sf::Vector2f lVelo; // scrolling velocity

        sf::Sprite mFavoriteTV; // sprite to first and last game view

    // all for enteties and player
    public:
        Player player;
        void flickPl(int countFLICK, int moduleFLICK); // flick void
        void spinPl(int countROTAT, float uRotANGLUS); // spin void, rotation ungle value of 0 or 360 degrees
        void changePlCol(sf::Color c, int rangeI);

        AirEnemy testAirEnemy; // test air enemy, to view mechanics go processEnemyBullets void
        Boss boss;
        void bossFill(int stage); // filling the boss
        sf::Vector2f sclx[3]; // it is the scale of boss values, cause it sprites are different sizes


    // all for scen node
    public:
        SceneNode nodeEY;
        void nodeFilUp(int stage);
        void nodeFilNearView(int stage); //if is neccessary can fill it near visibale space of stage


    // all for clouds and islands
    public:
        Cloud cloud;
        Island island;

    public:
        enum S_STAGES
            {
                STRT,
                STG_ONE,
                STG_TWO,
                STG_THREE,
                GAME_OVER,
                ENUM_COUNT
            };
       S_STAGES globalScene;

    public:
        struct GamePad_Data{
        unsigned int port;
        unsigned int start;
         float maxX;
         float maxY;
         float rngX;
         float rngY;
        unsigned int fire;
        unsigned int rotation;
        unsigned int chColor;
        };
            GamePad_Data gamePad_Data;

        sf::CircleShape lookJB;

        bool checkGamePad_Data_File();
        void readGamePad_Data_File();
        void updateGamePad_Data_File();
        void updateGamePad_Data_File_By_Default();

        bool silenceCheckGamePad;
        int counterCheckGamePad;

        void updateStructOfGamePad(sf::Event event);

        void resetPlayerMoveBools();

    public:
        void setGameStageEntities(int stg);

    // all for music
    public:
        sf::Sound sound[14];
        bool serviceSound[14];
        void playSounds();

};

#endif // GAME_H
