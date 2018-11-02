#pragma once
#include "Vector3D.h"

class Particle;

class ForceGenerator
{
public:
	virtual void Update(Particle* p, float deltaTime) = 0;
};

