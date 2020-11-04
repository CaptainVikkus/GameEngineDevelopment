#pragma once
#include "Ogre.h"

using namespace Ogre;

class RigidBody
{
public:
	//Particle Variables
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	//Physics Enabled
	bool isStatic;
	//Collision
	float sizeX;
	float sizeY;

	void Update();
};

class PhysicsEngine
{
public:
	static void Init();
	static void Update();
	static void Shutdown();

	//void CollisionRestitution();
};

