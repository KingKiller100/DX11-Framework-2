#pragma once

#include "ForceGenerator.h"
class GravityGenerator final : public ForceGenerator
{
public:
	GravityGenerator();
	GravityGenerator(const Vector3f &gravity);
	~GravityGenerator();

	float GetGravity() const											{ return currentGravity.y; }
	void SetGravity(const Vector3f &g)									{ currentGravity = realGravity = g; }
	void SetGravity(const float &f)										{ currentGravity = realGravity = Vector3f(0.f, f, 0.0f); }

	void KillGravity()													{ currentGravity = 0.f; }
	void RestartGravity()												{ currentGravity = realGravity; }

	void Update(Particle* p) override;

private:
	Vector3f currentGravity;
	Vector3f realGravity;
};

