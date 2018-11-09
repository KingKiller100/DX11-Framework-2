#pragma once
#include <d3d11_1.h>
#include "Transformation.h"
#include "ForceGenerator.h"
#include <vector>
#include <iostream>

class Particle
{
private:
	Transformation* _transform;
	Vector3D _velocity;
	Vector3D _acceleration;
	Vector3D netForce;
	Vector3D thrustForce = Vector3D();
	std::vector<ForceGenerator*> _forceGenerators;

	float generalFriction;

	float _radius;
	float _mass;
	float coefficientOfRestitution;
	float maxSpeed = 55;

	float lifeTimer;

	bool isLaminar;
	bool isKillable;

private:
	void UpdateNetForce(float &t);
	void UpdateAccel();
	void MoveParticle(float &t);
	void UpdateVelocity(float &t);

public:
	Particle(Transformation* _transform);
	~Particle();
	
	// Transform Accessor Methods
	Transformation* getTransformation()													const { return _transform; }

	// Radius Accessor Methods
	void SetRadius(const float r)																{ _radius = fabsf(r); }
	float GetRadius()																	const { return _radius; }
	float GetDiameter()																	const { return GetRadius() * 2; }

	// Velocity Accessor Methods
	void SetVelocity(const Vector3D v)													{ _velocity = v; }
	void SetVelocity(const float x, const float y, const float z)											{ _velocity.x = x, _velocity.y = y, _velocity.z = z; }
	float GetSpeed()																	const { return Vector3D::GetMagnitude(_velocity); }
	Vector3D GetVelocity()																const { return _velocity; }

	// Acceleration Accessor Methods
	void SetAcceleration(const Vector3D a)												{ _acceleration = a; }
	void SetAcceleration(const float x, const float y, const float z)					{ _acceleration.x = x, _acceleration.y = y, _acceleration.z = z; }
	float GetAccelerationMagnitude()													const { return Vector3D::GetMagnitude(_acceleration); }
	Vector3D GetAcceleration()															const { return _acceleration; }

	// Sets whether object is laminar or not
	void SwitchLaminarOn(const bool l)													{ isLaminar = l; }
	bool isLaminarOn()																	const { return isLaminar; }

	// Mass Accessor Methods
	void SetMass(const float mass)														{ _mass = mass; }
	float GetMass()																		const { return _mass; }

	// Coefficient of Restitution Accessors
	float GetCoefficientOfRestitution()													{ return coefficientOfRestitution; }
	void SetCoefficientOfRestitution(const float cor)									{ coefficientOfRestitution = cor; }

	// Thrust Accessor Methods
	void SetThrust(const Vector3D v)													{ thrustForce = v; }
	void AddThrust()																	{ thrustForce = Vector3D(0.0f, 20.0f, 0.0f); }
	void AddThrust(const Vector3D thrust)												{ thrustForce = thrust; }
	Vector3D GetThrust()																const { return thrustForce; }

	// MaxSpeed Accessor Methods
	float GetMaxSpeed()																	const { return maxSpeed; }

	// Particle's life Accessor Methods
	int GetLifetimer()																	const{ return lifeTimer; }
	void ResetLifeTimer()																{ lifeTimer = 0; }

	// Sets whether particle should be reset or not
	bool GetIsKillable()																const { return isKillable; }
	void IsKillableOn(const bool k)														{ isKillable = k; }

	void AddForce(const Vector3D& f);
	void AddGenerator(ForceGenerator* fg);

	void Update(float& t);
};

