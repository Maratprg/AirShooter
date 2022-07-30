#include<ctime>
#include "Cloud.h"

Cloud::Cloud()
: posX(200.f)
, posY(100.f)
{
  setVelocity(sf::Vector2f(0, 1.5)); //velocity
  setWH( 189.f, 131.f ); //width height

  this->autoSetCloudOrganic();
}

Cloud::~Cloud()
{
    //dtor
}

void Cloud::setPX(float x, float y)
{
    posX = x;
    posY = y;
}

float Cloud::getPX() {  return posX;  };
float Cloud::getPY() {  return posY;  };


void Cloud::autoSetCloudSp()
{
    float clonePOSX = posX;
    float addpX = 30;
    for(int i=0; i<3; i++)
    {
        cloudSp[i].setPosition(sf::Vector2f(clonePOSX,posY));
        clonePOSX = clonePOSX+addpX;
    }
}

void Cloud::autoSetSpCurr()
{
  int who;
  float step = 80.f; // horizontal and vertical offset of matrix
  who = rand()%100;

    if (who < 50)
        {
          cloudSp[0].setPosition(sf::Vector2f(posX, posY));
          cloudSp[1].setPosition(sf::Vector2f(posX+step, posY+step));
          cloudSp[2].setPosition(sf::Vector2f(posX, posY+step*2));
        }

    if (who > 50)
        {
          cloudSp[0].setPosition(sf::Vector2f(posX+step, posY));
          cloudSp[1].setPosition(sf::Vector2f(posX, posY+step));
          cloudSp[2].setPosition(sf::Vector2f(posX+step, posY+step*2));
        }
}

void Cloud::autoSetCloudOrganic()
{
    float subpX = -20.f; // the place where matrix shape go X (first X)
    float subRNGE_X = 20.f; // range X value, it is subtract from X
    float addRNGE_Y = 40.f; // range Y value, it is addict to Y
    float subpY = posY - 20.f;
    for(int i=0; i<organicCloudsNumbers; i++)
    {
        organicMatrix[i] = rand()%255;
        cloudOrganic[i].setFillColor(sf::Color(sf::Color(255.f,255.f,255.f,organicMatrix[i])));
        cloudOrganic[i].setRadius(10);

        if (subpX > 260) {
             cloudOrganic[i].setPosition(posX + (subpX), subpY);
             subpY = subpY + addRNGE_Y;
             subpX = -20.f;
        }
        else {
            cloudOrganic[i].setPosition(posX + (subpX), subpY);
            subpX = subpX + subRNGE_X;
        };

    };
}

void Cloud::remapCloudOrganic()
{
    float subpX = -20.f; // value of ofset for the sprites (from the center point of second sprite)
    float subRNGE_X = 20.f; // range value X
    float addRNGE_Y = 40.f; // range value Y
    float subpY = posY - 20.f;
    for(int i=0; i<organicCloudsNumbers; i++)
    {
        if (subpX > 260) {
             cloudOrganic[i].setPosition(posX + (subpX), subpY);
             subpY = subpY + addRNGE_Y;
             subpX = -20.f;
        }
        else {
            cloudOrganic[i].setPosition(posX + (subpX), subpY);
            subpX = subpX + subRNGE_X;
        };
    };
}

void Cloud::autoSetIntRects()
{
    for (int i=0; i<3; i++) {
    int how = rand()%3;
     if (how == 0) { cloudSp[i].setTextureRect(sf::IntRect(0.f,0.f,getW(),getH())); }
     if (how == 1) { cloudSp[i].setTextureRect(sf::IntRect(getW(),getH(),-getW(),-getH())); }
     if (how == 2) { cloudSp[i].setTextureRect(sf::IntRect(0.f,getH(),+getW(),-getH())); }
     else { cloudSp[i].setTextureRect(sf::IntRect(getW(),0,-getW(),getH())); };
     //std::cout << "RAND_cloudeHOW " << how << std::endl;
    };
}

void Cloud::autoTranseCloude()
{
   for (int i=0; i<3; i++) {
   float trans = 120 + rand()%135;
   cloudSp[i].setColor(sf::Color(255.f,255.f,255.f,trans));
   };
}

void Cloud::autoSetThreeClouds()
{
   for(int i=0; i< 3; i++)
    {
    threeClouds[i] = rand()%100;
    //std::cout << "ThreeCloudsArr " << threeClouds[i] << std::endl;
    }
}

void Cloud::autoSetPositionStart(sf::Vector2f& world_S) // little bit back frome visible area
{
   float cloudX = ( rand()%(240 - ((int)world_S.x - 240))  ) * 1.f;
   setPX(cloudX, -690.f);
}
void Cloud::autoSetDirectionZero()
{
isUP = false;
isDOWN = true;
isLEFT = false;
isRIGHT = false;
}

void Cloud::updateMovex(sf::Vector2f& world_S, bool isBoss)
{

   posX = posX + getVelocity().x;
   posY = posY + getVelocity().y;

   this->remapCloudOrganic();

   for (int i=0; i<3; i++) {
   cloudSp[i].move(getVelocity());}

   if (posY > world_S.y + 10.f)
   {
      this->autoSetPositionStart(world_S);
      this->autoSetCloudOrganic();
      this->autoSetSpCurr();
      this->autoSetIntRects();
      this->autoTranseCloude();
      this->autoSetThreeClouds();

      if (!isBoss) { this->setVisible(true); } //***** isBoss!!! *****
      else { this->setVisible(false); };

   }
}

