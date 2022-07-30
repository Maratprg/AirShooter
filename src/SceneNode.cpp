#include "SceneNode.h"

SceneNode::SceneNode()
: sceneY(0.f)
{
     //ctor
}

SceneNode::~SceneNode()
{
    //dtor
}

void SceneNode::attachEnemy(float rangeEnemy, float worldX)
{
  // making only positions in node
  // NOT SET WIDTH AND HEIGH in game class
  // NOT SET SPRITE in game class

  float airX = 200 + rand()%((int)worldX - 400);
  float airY = sceneY;

  AirEnemy air;
  air.sP.setPosition(sf::Vector2f(airX, airY));
  air.setBV(6);

  sceneVec.push_back(air);
  //std::cout << "ATTACHED ENEMY AIR POSITIONED AT ! " << airX << " / " << airY << std::endl;

  // addition of range Y
  sceneY = sceneY - rangeEnemy;
}

void SceneNode::dettachEnemy(std::vector<AirEnemy>::iterator dellete)
{
    if(dellete != sceneVec.end()) sceneVec.erase(dellete);
    //std::cout << " DESTR AIR >>>>> >>>>> >>>>> ! " << std::endl;
    //std::cout << " SCENE NODE SIZE ***||||*** " << sceneVec.size() << std::endl;
}

void SceneNode::autoGenerateSceneNode(int enemyCount, float rangeEnemy, float worldX)
{
    for (int i=0; i<enemyCount; i++) this->attachEnemy(rangeEnemy, worldX);
}


