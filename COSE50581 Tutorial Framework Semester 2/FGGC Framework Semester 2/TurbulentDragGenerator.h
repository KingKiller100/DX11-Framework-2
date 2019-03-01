#pragma once
#include "ForceGenerator.h"

class TurbulentDragGenerator : public ForceGenerator
{
public:
	TurbulentDragGenerator();
	~TurbulentDragGenerator();

	void SetDragCoefficient(const float dg)					{ dragCoefficient = dg; }
	void SetWaterCurrent(const Vector3f &wc)					{ waterCurrentVel = wc; }

	void Update(Particle* p);

private:
	float dragCoefficient;
	Vector3f waterCurrentVel;
};

