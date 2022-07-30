#include "Text.h"
Text::Text()
: visible_BStart(true)
, visible_BRedifine(true)
, visible_BFinal(true)
, visible_Stage(true)
, swch_VCheck(false)
{
  if (!font.loadFromFile("consola.ttf")) {
  std::cout << " Error: Cant find font file! " << std::endl;
  }
  else {
  font.loadFromFile("consola.ttf");

  stage.setFont(font);
  score.setFont(font);
  health.setFont(font);
  boss_health.setFont(font);
  b_Start.setFont(font);
  b_Redifine.setFont(font);
  f_Score.setFont(font);

  stage.setCharacterSize(80);
  score.setCharacterSize(40);
  health.setCharacterSize(40);
  boss_health.setCharacterSize(40);
  b_Start.setCharacterSize(55);
  b_Redifine.setCharacterSize(35);
  b_Redifine.setStyle(sf::Text::Bold);
  f_Score.setCharacterSize(80);

  stage.setFillColor(sf::Color::White);
  score.setFillColor(sf::Color::White);
  health.setFillColor(sf::Color::White);
  boss_health.setFillColor(sf::Color::Blue);
  b_Start.setFillColor(sf::Color::White);
  b_Redifine.setFillColor(sf::Color::White);
  f_Score.setFillColor(sf::Color::White);

  stage.setString("STAGE << 1 >>");
  score.setString("SCORE: ");
  health.setString("HEALTH: ");
  boss_health.setString("BOSS_H: ");
  b_Start.setString("START ENTER");
  b_Redifine.setString("SPACE -> GamePad");
  f_Score.setString("DEF_LT");

  }//end of if else
}//end ctor

Text::~Text()
{
    //dtor
}

void Text::autoSetPosition(sf::Vector2f& world_S)
{
  stage.setPosition(sf::Vector2f(world_S.x/2 - 280.f, world_S.y/2 - 120.f));
  score.setPosition(sf::Vector2f(40.f, 20.f));
  health.setPosition(sf::Vector2f(40.f, 60.f));
  boss_health.setPosition(sf::Vector2f(world_S.x-300.f, 20.f));
  b_Start.setPosition(sf::Vector2f(780.f, 200.f));
  b_Redifine.setPosition(sf::Vector2f(782.f, 280.f));
  f_Score.setPosition(sf::Vector2f(world_S.x/2 - 40.f, world_S.y/2 - 197.f));
}

void Text::setBlinkStart(int t, int period)
{
 timeStart = t + period;
 periodStart = period;
}

void Text::setBlinkRedifine(int t, int period)
{
 timeRedifine = t + period;
 periodRedifine = period;
}

void Text::setBlinkFinal(int t, int period)
{
 timeFinal = t + period;
 periodFinal = period;
}

void Text::setShowStage(int t, int stg)
{
 timeCControllerStage = t + 100; // displaying time value
 std::string stg_str = "STAGE << " + std::to_string(stg) + " >>";
 stage.setString(stg_str);
 visible_Stage = true;
 swch_VCheck = true;
}

void Text::setShowWin(int t)
{
 timeCControllerStage = t + 100; // displaying time value
 stage.setString("<< WINNER >>");
 visible_Stage = true;
 swch_VCheck = true;
}
