#pragma once
#include "Ogre.h"

using namespace Ogre;

class Ball
{
private:
    String ballShape = "ogrehead.mesh";
    Vector3 position = Vector3(0, 0, 0);
    float xVelocity = -5;
    float yVelocity = 0.2;

    Entity* mEntity;
    SceneNode* mNode;

public:
    Ball(SceneManager* scn);
    virtual ~Ball() {}

    Vector3 getPosition() { return position; }
    String getShape() { return ballShape; }
    float getXVelocity() { return xVelocity; }

    void hitGoal();
    void reboundBat();
    void reboundSides();
    void update();
};

