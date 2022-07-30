#include "Island.h"

Island::Island()
: globalRadiusB(170.f)
, globalRadiusT(120.f)
{
  //ctor
  setVelocity(sf::Vector2f(0.f,0.7));
}

Island::~Island()
{
  //dtor
}

void Island::setPosXY(float x, float y)
{
   posX = x;
   posY = y;
   this->autoSetSpIsland();
   this->autoSetOrganicIslandB();
   this->autoSetOrganicIslandT();
}

void Island::autoSetSpIsland()
{
   float pX = posX - getW()/2 + 20.f;
   float pY = posY - getH()/2 + 20.f;
   islandSp.setPosition(sf::Vector2f(pX,pY));
}

void Island::autoSetOrganicIslandT()
{
 float halfPart = globalRadiusT/2;
 float quatroPart =  globalRadiusT/4;
 float largQuatroPart = halfPart + quatroPart;
 float trans;
 //posX posY
 //float badgeR = 1;

        for(int i=0; i<organicNebula; i++)
            {
            trans = 100 + rand()%155;
            organicIT[i].setRadius(25);
            organicIT[i].setFillColor(sf::Color(153, 255, 255, trans ));
            }

   organicIT[0].setPosition(sf::Vector2f ( posX , posY-globalRadiusT ));
   organicIT[1].setPosition(sf::Vector2f ( posX+quatroPart , posY-largQuatroPart ));
   organicIT[2].setPosition(sf::Vector2f ( posX+halfPart , posY-halfPart ));
   organicIT[3].setPosition(sf::Vector2f ( posX+largQuatroPart , posY-quatroPart ));
     organicIT[4].setPosition(sf::Vector2f ( posX+globalRadiusT , posY ));
     organicIT[5].setPosition(sf::Vector2f ( posX+largQuatroPart , posY+quatroPart ));
     organicIT[6].setPosition(sf::Vector2f ( posX+halfPart , posY+halfPart ));
     organicIT[7].setPosition(sf::Vector2f ( posX+quatroPart, posY+largQuatroPart ));
    organicIT[8].setPosition(sf::Vector2f ( posX, posY+globalRadiusT ));
    organicIT[9].setPosition(sf::Vector2f ( posX-quatroPart, posY+largQuatroPart ));
    organicIT[10].setPosition(sf::Vector2f ( posX-halfPart, posY+halfPart ));
    organicIT[11].setPosition(sf::Vector2f ( posX-largQuatroPart, posY+quatroPart ));
   organicIT[12].setPosition(sf::Vector2f ( posX-globalRadiusT, posY ));
   organicIT[13].setPosition(sf::Vector2f ( posX-largQuatroPart, posY-quatroPart ));
   organicIT[14].setPosition(sf::Vector2f ( posX-halfPart, posY-halfPart ));
   organicIT[15].setPosition(sf::Vector2f ( posX-quatroPart, posY-largQuatroPart ));
}

void Island::autoSetOrganicIslandB()
{
 float halfPart = globalRadiusB/2;
 float quatroPart =  globalRadiusB/4;
 float largQuatroPart = halfPart + quatroPart;
 float trans;

        for(int i=0; i<organicNebula; i++)
            {
            trans = 100 + rand()%155;
            organicIB[i].setRadius(25);
            organicIB[i].setFillColor(sf::Color(153, 255, 255, trans ));
            }

   organicIB[0].setPosition(sf::Vector2f ( posX , posY-globalRadiusB ));
   organicIB[1].setPosition(sf::Vector2f ( posX+quatroPart , posY-largQuatroPart ));
   organicIB[2].setPosition(sf::Vector2f ( posX+halfPart , posY-halfPart ));
   organicIB[3].setPosition(sf::Vector2f ( posX+largQuatroPart , posY-quatroPart ));
     organicIB[4].setPosition(sf::Vector2f ( posX+globalRadiusB , posY ));
     organicIB[5].setPosition(sf::Vector2f ( posX+largQuatroPart , posY+quatroPart ));
     organicIB[6].setPosition(sf::Vector2f ( posX+halfPart , posY+halfPart ));
     organicIB[7].setPosition(sf::Vector2f ( posX+quatroPart, posY+largQuatroPart ));
    organicIB[8].setPosition(sf::Vector2f ( posX, posY+globalRadiusB ));
    organicIB[9].setPosition(sf::Vector2f ( posX-quatroPart, posY+largQuatroPart ));
    organicIB[10].setPosition(sf::Vector2f ( posX-halfPart, posY+halfPart ));
    organicIB[11].setPosition(sf::Vector2f ( posX-largQuatroPart, posY+quatroPart ));
   organicIB[12].setPosition(sf::Vector2f ( posX-globalRadiusB, posY ));
   organicIB[13].setPosition(sf::Vector2f ( posX-largQuatroPart, posY-quatroPart ));
   organicIB[14].setPosition(sf::Vector2f ( posX-halfPart, posY-halfPart ));
   organicIB[15].setPosition(sf::Vector2f ( posX-quatroPart, posY-largQuatroPart ));
}

 void Island::stepAlpha()
{
}

void Island::RotateOrganicBP()
{
}

void Island::RotateOrganicTP()
{
}


void Island::updateMovex(sf::Vector2f& s_World, bool isBoss)
{
  posX = posX + getVelocity().x;
  posY = posY + getVelocity().y;

  islandSp.move(getVelocity());
  //std::cout << islandSp.getPosition().x << " / " << islandSp.getPosition().y << std::endl;
  //std::cout << getVelocity().x << " / " << getVelocity().y << std::endl;

  for (int i=0; i<organicNebula; i++)
  {
      organicIB[i].move(getVelocity());
      organicIT[i].move(getVelocity());
  }

  if(posY > s_World.y + 170.f)
  {
      int wX = (int)s_World.x - 700;
      float newX = (350 + rand()%wX) * 1.f;
      float newY = -690.f;
      setPosXY(newX,newY);

      //std::cout << "ISLAND :::: " << newX << " / " << newY << std::endl;

      if (isBoss) {this->setVisible(false);}
      else { this->setVisible(true); }
  }

}

