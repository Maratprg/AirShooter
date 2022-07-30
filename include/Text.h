#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


class Text
{
    public:
       Text();
       ~Text();

       sf::Text stage; // to display the level at the beginning of the game
       sf::Text score; // to display the player score
       sf::Text health; // to display the player health
       sf::Text boss_health; // to display boss health
       sf::Text b_Start; // to display first view blinking text (start)
       sf::Text b_Redifine; // to display first view blinking text (redifine)
       sf::Text f_Score; // to display the final score
       sf::Font font; // nesessary to load the font

    void autoSetPosition(sf::Vector2f& world_S);
    void setBlinkStart(int t, int period);
    void setBlinkRedifine(int t, int period);
    void setBlinkFinal(int t, int period);

    unsigned int timeStart;
    unsigned int timeRedifine;
    unsigned int timeFinal;

    unsigned int periodStart;
    unsigned int periodRedifine;
    unsigned int periodFinal;

    unsigned long long int timeCControllerStart;
    unsigned long long int timeCControllerRedifine;
    unsigned long long int timeCControllerFinal;

    void setShowStage(int t, int stg);
    void setShowWin(int t);

    unsigned long long int timeCControllerStage;

    bool visible_Stage;
    bool swch_VCheck;

    bool visible_BStart;
    bool visible_BRedifine;
    bool visible_BFinal;
};

#endif // TEXT_H
