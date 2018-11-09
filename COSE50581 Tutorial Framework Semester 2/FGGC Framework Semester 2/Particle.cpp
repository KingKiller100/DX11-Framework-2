#include "Particle.h"
#include <random>

Particle::Particle(Transformation * transform) : _transform(transform)
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_real_distribution<float> distribution(0.001, 1);

	generalFriction = 0.98f;
	_radius = 0.5f;
	_mass = 1.0f;

	coefficientOfRestitution = distribution(generator);

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

void Particle::Update(float& t)
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

void Particle::AddForce(const Vector3D &f)
{
	netForce += f;
}

void Particle::AddGenerator(ForceGenerator* fg)
{
	_forceGenerators.push_back(fg);
}

void Particle::UpdateNetForce(float &t)
{
	for (ForceGenerator* fg : _forceGenerators)
	{
		fg->Update(this, t);
	}
}

void Particle::MoveParticle(float &t)
{
	Vector3D pos = _transform->GetPosition();	
	pos += _velocity * t + _acceleration * t * t * 0.5f;
	_transform->SetPosition(pos);
}

void Particle::UpdateVelocity(float &t)
{
	_velocity += _acceleration * t;
	_velocity *= generalFriction;
	//_velocity.Truncate(maxSpeed);
}

void Particle::UpdateAccel()
{
	_acceleration = netForce / _mass;
}