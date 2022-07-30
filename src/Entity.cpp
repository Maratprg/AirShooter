#include "Entity.h"

//************************* class Entity
Entity::Entity()
: velocity(0.f,0.f)
,trigerable(true)
,visible(true)
,health(4)
,score(1)
,isUP(false)
,isDOWN(false)
,isLEFT(false)
,isRIGHT(false)
, bulletVel(-4.5)
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

void Entity::setColliderPointX (int n, float x)
    {
        if ( n >= 0 && n < static_cast<int>(sizeof(colliderPointsX)/sizeof(int)) ) { colliderPointsX[n] = x; }
        else
            { std::cout << "ER::: Incorrect x_Array Number" << std::endl; };
    }


float Entity::getColliderPointX (int n)
    {
        if ( n >= 0 && n < static_cast<int>(sizeof(colliderPointsX)/sizeof(int)) ) { return colliderPointsX[n]; }
        else
            { std::cout << "ER::: Incorrect x_Array Number returned 0" << std::endl; return 0; };
    }


void Entity::setColliderPointY (int n, float y)
    {
        if ( n >= 0 && n < static_cast<int>(sizeof(colliderPointsY)/sizeof(int)) ) { colliderPointsY[n] = y; }
        else
            { std::cout << "ER::: Incorrect y_Array Number" << std::endl; };
    }


float Entity::getColliderPointY (int n)
    {
        if ( n >= 0 && n < static_cast<int>(sizeof(colliderPointsY)/sizeof(int)) ) { return colliderPointsY[n]; }
        else
            { std::cout << "ER::: Incorrect y_Array Number returned 0" << std::endl; return 0; };
    }

void Entity::setColliderPointsXY(int n, float x, float y)
    {
        if ( n >= 0 && n < static_cast<int>(sizeof(colliderPointsX)/sizeof(int)) )
                     {
                        colliderPointsX[n] = x;
                        colliderPointsY[n] = y;
                     }
        else
            { std::cout << "ER::: Incorrect y_Array Number" << std::endl; };
    }

sf::Vector2f& Entity::getColliderPointVector (int n)
    {
        if ( n >= 0 && n < static_cast<int>(sizeof(colliderPointsX)/sizeof(int)) )
                    {
                        sf::Vector2f rV(colliderPointsX[n], colliderPointsY[n]);
                        return rV;
                    }
        else
            { std::cout << "ER::: Incorrect y_Array Number returned 0 value v2f" << std::endl;
                        sf::Vector2f rV(0,0);
                        return rV;
            };
    }
void Entity::swapVisible()
{
    if(visible == true) { visible = false; }
    else { visible = true; };
}

void Entity::setBV (float bV)
{
    bulletVel = bV;
}

float Entity::getBV()
{
    return bulletVel;
}


