#pragma once

#include "ForceGenerator.h"
class GravityGenerator : public ForceGenerator
{
public:
	GravityGenerator();
	~GravityGenerator();

	void SetGravity(const Vector3D &g)									{ gravity = g; }
	void SetGravity(const float &f)										{ gravity = Vector3D(0.f, f, 0.0f); }

	void Update(Particle* p, float deltaTime);

private:
	Vector3D gravity;
};

