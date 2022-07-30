#ifndef SCENENODE_H
#define SCENENODE_H

#include <vector>
#include "AirEnemy.h"

class SceneNode
{
    public:
        SceneNode();
        ~SceneNode();

        void setSceneF(float y) { sceneY = y; };
        float getSceneF() { return sceneY; };

        //void accepts the number of players, the distance between players, the value of the width of the world
        void autoGenerateSceneNode(int enemyCount, float rangeEnemy, float worldX);

        std::vector <AirEnemy> sceneVec;
            void attachEnemy(float rangeEnemy, float worldX); // the distance between enemies is a positive number, it is subtracted there
            void dettachEnemy(std::vector<AirEnemy>::iterator dellete);

    private:
        float sceneY;
};

#endif // SCENENODE_H
