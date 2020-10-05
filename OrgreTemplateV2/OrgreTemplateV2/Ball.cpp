#include "Ball.h"

Ball::Ball(SceneManager* scn)
{
	mEntity = scn->createEntity("Ball", ballShape);
	mNode = scn->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mEntity);
	mNode->setPosition(position);
}

bool Ball::hitBottom()
{
	return false;
}

void Ball::reboundBat()
{
}

void Ball::reboundSides()
{
}

void Ball::update()
{
	mNode->translate(Vector3(xVelocity, yVelocity, 0));
	position = mNode->getPosition();
}
