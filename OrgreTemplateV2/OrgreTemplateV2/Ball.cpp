#include "Ball.h"

Ball::Ball(SceneManager* scn)
{
	mEntity = scn->createEntity("Ball", ballShape);
	mNode = scn->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mEntity);
	mNode->setPosition(position);
}

void Ball::hitGoal()
{
	mNode->setPosition(Vector3(0, 0, 0));
	position = mNode->getPosition();
	xVelocity = -5;
	yVelocity = rand() % 5 - 1;
}

void Ball::reboundBat()
{
	xVelocity *= -1; //reverse x speed
}

void Ball::reboundSides()
{
	yVelocity *= -1; //reverse y speed
}

void Ball::update()
{
	mNode->translate(Vector3(xVelocity, yVelocity, 0));
	position = mNode->getPosition();
}
