#include "Bat.h"

Bat::Bat(SceneManager* scn)
{
    mEntity = scn->createEntity("cube.mesh");
    mNode = scn->getRootSceneNode()->createChildSceneNode();
    mNode->setPosition(position);
    mNode->setScale(0.5, 3, 0.5);
    mNode->attachObject(mEntity);

}

void Bat::moveUp()
{
    mNode->translate(Vector3(0, batSpeed, 0));
    position = mNode->getPosition();
}

void Bat::moveDown()
{
    mNode->translate(Vector3(0, -batSpeed, 0));
    position = mNode->getPosition();
}

void Bat::update()
{
}
