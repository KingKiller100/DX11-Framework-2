#include "Particle.h"

Particle::Particle(Transformation * transform)
{
	_transform = transform;
	
	generalFriction = 0.98f;
	_radius = 0.5f;
	_mass = 1.0f;

	coefficientOfRestitution = 0.5462f;

	_velocity = Vector3D();
	_acceleration = Vector3D();
	netForce = Vector3D();

	isLaminar = true;
	isKillable = false;

	lifeTimer = -1;
}

Particle::~Particle()
{
}

void Particle::Update(float t)
{
	if (_mass < 0)
		return;

	UpdateNetForce(t);
	UpdateAccel();
	MoveParticle(t);
	UpdateVelocity(t);

	netForce.Zero();

	lifeTimer += t;  
}

void Particle::AddForce(Vector3D &f)
{
	netForce += f;
}

void Particle::AddGenerator(ForceGenerator* fg)
{
	_forceGenerators.push_back(fg);
}

void Particle::UpdateNetForce(float t)
{
	for (ForceGenerator* fg : _forceGenerators)
	{
		fg->Update(this, t);
	}
}

void Particle::MoveParticle(float t)
{
	Vector3D pos = _transform->GetPosition();
	
	pos += _velocity * t + _acceleration * t * t * 0.5f;
	
	_transform->SetPosition(pos);
}

void Particle::UpdateVelocity(float t)
{
	_velocity += _acceleration * t;
	_velocity *= generalFriction;
	//_velocity.Truncate(maxSpeed);
}

void Particle::UpdateAccel()
{
	_acceleration = netForce / _mass;
}