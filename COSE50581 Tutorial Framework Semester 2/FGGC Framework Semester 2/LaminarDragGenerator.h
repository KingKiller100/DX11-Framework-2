#pragma once
#include "ForceGenerator.h"

class LaminarDragGenerator : public ForceGenerator
{
public:
	LaminarDragGenerator();
	~LaminarDragGenerator();

	void SetDragCoefficient(float dg) { dragCoefficient = dg; }

	void Update(Particle* p, float deltaTime);
	
private:
	float dragCoefficient = 0.40f;
};

