#ifndef CLOUD_H
#define CLOUD_H

#include <ctime>
#include "Entity.h"

unsigned int const organicCloudsNumbers = 144;

class Cloud : public Entity
{
    public:
        Cloud();
        ~Cloud();

    sf::Sprite cloudSp[3];
    sf::CircleShape cloudOrganic[organicCloudsNumbers]; // in each for changes from array
    float organicMatrix[organicCloudsNumbers];
    short threeClouds[3];

    void setPX(float x, float y);
    float getPX();
    float getPY();

    void autoSetCloudSp(); // setting the sprites' retreat and position relative one from each other
    void autoSetSpCurr(); // customizing the display of sprites
    void autoSetIntRects(); // auto randomization of the srpite display
    void autoTranseCloude(); // a method that adds transparency to clouds
    void autoSetCloudOrganic(); // configuring the nebula display array (matrix)
    void remapCloudOrganic(); // move matrix
    void autoSetPositionStart(sf::Vector2f& world_S); // little bit back frome visible area
    void autoSetDirectionZero(); // reset directions
    void autoSetThreeClouds(); // a method that adds a gradation of transparency to the illusion of height

    void updateMovex(sf::Vector2f& world_S, bool isBoss);

    private:
     float posX;
     float posY;
};

#endif // CLOUD_H
