#pragma once
#include "Ogre.h"

using namespace Ogre;

class Bat
{
private:
    String batShape = "cube.mesh";
    float batSpeed = 5;
    Vector3 position = Vector3(-600, 0, 0);

    Entity* mEntity;
    SceneNode* mNode;

public:
    Bat(SceneManager* scn);
    virtual ~Bat() {}

    Vector3 getPosition() { return position; }
    String getShape() { return batShape; }

    void MoveUp();
    void MoveDown();
    void Update();
};

