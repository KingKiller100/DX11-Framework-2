#pragma once
#include <d3d11_1.h>
#include "Transformation.h"

class Particle
{
public:
	Particle(Transformation* _transform, Vector3D initialVelocity, Vector3D initialAcceleration, float mass);
	~Particle();
	
	// Velocity Getters and Setters
	void SetVelocity(Vector3D v) { _velocity = v; }
	void SetVelocityXYZ(Vector3D v) { _velocity.x = v.x, _velocity.y = v.y, _velocity.z = v.z; }

	float GetSpeed() { return Vector3D::GetMagnitude(_velocity); }
	Vector3D GetVelocity() { return _velocity; }

	// Acceleration Getters and Setters
	void SetAcceleration(Vector3D a) { _acceleration = a; }
	void SetAccelerationXYZ(Vector3D a) { _acceleration.x = a.x, _acceleration.y = a.y, _acceleration.z = a.z; }
	void UseConstAcceleration(bool useConstAccel) { this->useConstAccel = useConstAccel; }

	float GetAccelerationMagnitude() { return Vector3D::GetMagnitude(_acceleration); }
	Vector3D GetAcceleration() { return _acceleration; }

	// Mass Getters and Setters
	void SetMass(float mass) { _mass = mass; }
	float GetMass() { return _mass; }

	// Update Physics
	void Update(float t);

	void UpdateVelocity(float t);
	// Update acceleration of object using Newton's Laws of Physics
	// Assumption: net external force is constant between consecutive updates of object state
	void UpdateAccelerate(float t);
	void CalculateNetForce();

private:
	Transformation* _transform;
	Vector3D _velocity;
	Vector3D _acceleration;
	float _mass;

	bool useConstAccel;

	// Force Variables
	Vector3D force;
	Vector3D netForce;

	// Physics methods
	void MoveWithConstVel(float t); // Update world position of object by adding displacement to precious position
	void MoveWithConstAccel(float t); // Update state of game object moving relative to previous position

	// Object movement
	void HandleInput(float t);
	void MoveForward(float t);
	void MoveBackward(float t);
	void MoveRight(float t);
	void MoveLeft(float t);
};

