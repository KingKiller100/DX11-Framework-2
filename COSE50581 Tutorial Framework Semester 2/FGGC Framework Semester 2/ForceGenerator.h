#pragma once
#include "Maths/kMaths.h"

class Particle;

class ForceGenerator
{
public:
	virtual ~ForceGenerator() = 0;
	virtual void Update(Particle* p) = 0;
};

