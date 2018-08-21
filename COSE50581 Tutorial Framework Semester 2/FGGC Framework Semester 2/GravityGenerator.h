#pragma once

#include "ForceGenerator.h"
class GravityGenerator : public ForceGenerator
{
public:
	GravityGenerator();
	~GravityGenerator();

	void SetGravity(Vector3D g) { gravity = g; }

	void Update(Particle* p, float deltaTime);

private:
	Vector3D gravity;
};

