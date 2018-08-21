#pragma once
#include "ForceGenerator.h"

class TurbulentDragGenerator : public ForceGenerator
{
public:
	TurbulentDragGenerator();
	~TurbulentDragGenerator();

	void SetDragCoefficient(float dg)					{ dragCoefficient = dg; }
	void SetWaterCurrent(Vector3D wc)					{ waterCurrentVel = wc; }

	void Update(Particle* p, float deltaTime);

private:
	float dragCoefficient;
	Vector3D waterCurrentVel;
};

