#include "Boss.h"

Boss::Boss()
: fromFlick(0)
, toFlick(0)
, flicCController(0)
, fromChColor(0)
, toChColor(0)
, colorCController(0)
, fromRotate(0)
, toRotate(0)
, rotateCController(0)
, isAlive(false)
, replCounter(0)
, stageCounter(1)
, fromBurn(0)
, toBurn(0)
, burnCController(0)
, bossIsBurn(false)
, burnCounter(0)
, soundBorn(false)

{
    //ctor
    setHealth(5);
    setVelocity(sf::Vector2f(0.f,0.f));
    setBV(5.f);
    bSp.setPosition(480.f,20.f);

}

Boss::~Boss()
{
    //dtor
}

void Boss::startBullet(int stage, sf::Vector2f& world_S)
{
    if (stage == 1)
    {
        float LXplace = 100.f;
        float LYplace = 287.f;
        float RXplace = world_S.x - LXplace - 15.f;
        float RYplace = LYplace;
        float startPX = bSp.getPosition().x + getW()/2 - 10.f; //half width
        float startPY = bSp.getPosition().y  + getH();

        float goX = startPX;
        float goY = startPY;

          for (int i=0; i<3; i++){
          sf::CircleShape SHP;
          SHP.setRadius(10.f);
          SHP.setFillColor(sf::Color::Yellow);
          SHP.setOutlineThickness (-2.f);
          SHP.setOutlineColor(sf::Color::Red);
          SHP.setPosition(goX, goY);
          bulletVec.push_back(SHP);
         // std::cout << " started ONE BULLET! " << std::endl;
            if (goX == startPX){
                goX = LXplace;
                goY = LYplace;
                }
            else if (goX == LXplace){
                goX = RXplace;
                goY = RYplace;
                }
            else {
                goX = startPX;
                goY = startPY;
                }

         }//end of for
    }//end of if

    else if (stage == 2)
    {
         float LXplace = 110.f; // start position of x boss bullets
         float LYplace = 280.f; // start position of y boss bullets
         float RXplace = world_S.x - LXplace;
         float RYplace = LYplace;
         float startPX = bSp.getPosition().x + getW()/2 - 10.f; //half width
         float startPY = bSp.getPosition().y  + getH();

         float offset = 177.f;

         float goX = LXplace;
         float goY = LYplace;

           for (int i=0; i<5; i++){
           sf::CircleShape SHP;
           SHP.setRadius(10.f);
           SHP.setFillColor(sf::Color::Yellow);
           SHP.setOutlineThickness (-2.f);
           SHP.setOutlineColor(sf::Color::Red);
           SHP.setPosition(goX, goY);
           bulletVec.push_back(SHP);
           // std::cout << " started ONE BULLET! " << std::endl;
             if (goX == LXplace){
                 goX = LXplace+offset;
                 goY = LYplace;
                 }
             else if (goX == LXplace+offset){
                 goX = startPX;
                 goY = startPY;
                 }
             else if (goX == startPX){
                 goX = RXplace-offset;
                 goY = RYplace;
                 }
             else if (goX == RXplace-offset){
                 goX = RXplace;
                 goY = RYplace;
                 }
             else {
                 goX = LXplace;
                 goY = LYplace;
                 }
           }//end of for
    }//end of if

    else if (stage == 3)
    {
         float LXplace = 140.f; // start position of x boss bullets
         float LYplace = 180.f; // start position of y boss bullets
         float RXplace = world_S.x - LXplace;
         float RYplace = LYplace;
         float startPX = bSp.getPosition().x + getW()/2 - 10.f; //half width
         float startPY = bSp.getPosition().y  + getH();

         float offset = 156.f;

         float goX = startPX;
         float goY = startPY;

           for (int i=0; i<5; i++){
           sf::CircleShape SHP;
           SHP.setRadius(10.f);
           SHP.setFillColor(sf::Color::Yellow);
           SHP.setOutlineThickness (-2.f);
           SHP.setOutlineColor(sf::Color::Red);
           SHP.setPosition(goX, goY);
           bulletVec.push_back(SHP);
           // std::cout << " started ONE BULLET! " << std::endl;
             if (goX == LXplace){
                 goX = LXplace+offset;
                 goY = LYplace + 50.f;
                 }
             else if (goX == LXplace+offset){
                 goX = startPX;
                 goY = startPY;
                 }
             else if (goX == startPX){
                 goX = RXplace-offset;
                 goY = RYplace + 50.f;
                 }
             else if (goX == RXplace-offset){
                 goX = RXplace;
                 goY = RYplace;
                 }
             else {
                 goX = LXplace;
                 goY = LYplace;
                 }
           }//end of for
    }//end of if
    else{};
}//end of void

void Boss::dettachBullet(std::vector<sf::CircleShape>::iterator dellete)
{
    if(dellete != bulletVec.end()) bulletVec.erase(dellete);
    // std::cout << " DESTR ONE BULLET! " << std::endl;
    // std::cout << " BULLETS VECTOR SIZE " << bulletVec.size() << std::endl;

}

void Boss::autoSetPosition(sf::Vector2f& world_S)
{
   float pX = 30 + rand() % ((int)world_S.x - 400);
   // std::cout << " PLACE X = = = " << pX << std::endl;
   float pY = bSp.getPosition().y;
   bSp.setPosition(sf::Vector2f(pX,pY));
}

void Boss::setThreeUVec(int stage)
{
    if(stage == 1)
    {
        threeUvec[0].x = 0.f;
        threeUvec[0].y = getBV();
        threeUvec[1].x = 0.f;
        threeUvec[1].y = getBV();
        threeUvec[2].x = 0.f;
        threeUvec[2].y = getBV();
    }
    else if (stage == 2)
    {
       threeUvec[0].x = 0.f;
       threeUvec[0].y = getBV();
       threeUvec[1].x = 0.f;
       threeUvec[1].y = getBV();
       threeUvec[2].x = 0.f;
       threeUvec[2].y = getBV();
    }
    else if (stage == 3)
    {
       threeUvec[0].x = +1.25f;
       threeUvec[0].y = getBV();
       threeUvec[1].x = 0.f;
       threeUvec[1].y = getBV();
       threeUvec[2].x = -1.25f;
       threeUvec[2].y = getBV();

    }
    else {};
}

void Boss::burnAutoSetPositionBoss()
{
    float startBurnX = bSp.getPosition().x + getW()/2;
    float startBurnY = bSp.getPosition().y + getH()/2;
    burnVec.resize(8);

    for (int b=0; b<burnVec.size(); b++)
    {
       burnVec[b].setRadius(15.f);
       burnVec[b].setFillColor(sf::Color::White);
       burnVec[b].setOutlineThickness(-2.f);
       burnVec[b].setOutlineColor(sf::Color::Black);
       burnVec[b].setPosition(sf::Vector2f(startBurnX,startBurnY));
    }

   burnUVec.resize(8);
   float angl = 0.7;
   burnUVec[0].x = 0.f;
   burnUVec[0].y = -1.f;

   burnUVec[1].x = angl;
   burnUVec[1].y = -angl;

   burnUVec[2].x = 1.f;
   burnUVec[2].y = 0;

   burnUVec[3].x = +angl;
   burnUVec[3].y = +angl;

   burnUVec[4].x = 0.f;
   burnUVec[4].y = 1.f;

   burnUVec[5].x = -angl;
   burnUVec[5].y = +angl;

   burnUVec[6].x = -1.f;
   burnUVec[6].y = 0.f;

   burnUVec[7].x = -angl;
   burnUVec[7].y = -angl;
}

void Boss::dettachBurn(std::vector<sf::CircleShape>::iterator dellete, std::vector<sf::Vector2f>::iterator dellUVec)
{
   if(dellete != burnVec.end()) burnVec.erase(dellete);
   // std::cout << " DESTR ONE BULLET! " << std::endl;
   if(dellUVec != burnUVec.end()) burnUVec.erase(dellUVec);

   std::cout << " BURNS VEC SIZE " << burnVec.size() << " UVEC SIZE "  << burnUVec.size() << std::endl;
}
