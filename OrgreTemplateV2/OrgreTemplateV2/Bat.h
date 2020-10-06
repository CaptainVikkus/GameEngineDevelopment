#pragma once
#include "Ogre.h"

using namespace Ogre;

class Bat
{
private:
    String batShape = "cube.mesh";
    float batSpeed = 10;
    Vector3 position = Vector3(-650, 0, 0);

    Entity* mEntity;
    SceneNode* mNode;

public:
    Bat(SceneManager* scn);
    virtual ~Bat() {}

    Vector3 getPosition() { return position; }
    String getShape() { return batShape; }

    void moveUp();
    void moveDown();
    void update();
};

