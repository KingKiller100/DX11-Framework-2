#include "Particle.h"

Particle::Particle(Transformation * _transform, Vector3D initialVelocity, Vector3D initialAcceleration, float mass)
{
	this->_transform = _transform;
	_velocity = initialVelocity;
	_acceleration = initialAcceleration;
	_mass = mass;

	netForce = Vector3D();
	force = Vector3D();

	useConstAccel = false;
}

Particle::~Particle()
{
	if (_transform)
	{
		delete _transform;
		_transform = nullptr;
	}
}

void Particle::Update(float t)
{
	if (_mass >= 0.0f)
	{
		if (GetAsyncKeyState('V'))
		{
			useConstAccel = false;
		}
		if (GetAsyncKeyState('X'))
		{
			useConstAccel = true;
		}

		if (useConstAccel == true)
		{
			MoveWithConstAccel(t);
		}
		else
		{
			MoveWithConstVel(t);
		}
	}
	
}

void Particle::MoveWithConstVel(float t)
{
	if (_velocity.z * t > 0.2f)
	{
		_velocity.z = 0.2f;
	}
	if (_velocity.x * t > 0.2f)
	{
		_velocity.x = 0.2f;
	}
	if (_velocity.y * t > 0.2f)
	{
		_velocity.y = 0.2f;
	}
	HandleInput(t);
}

void Particle::UpdateVelocity(float t)
{
	_velocity += _acceleration * t;
}

void Particle::UpdateAccelerate(float t)
{
	_acceleration.x = netForce.x / _mass;
	_acceleration.y = netForce.y / _mass;
	_acceleration.z = netForce.z / _mass;
}

void Particle::CalculateNetForce()
{
	// calculate net external force
	netForce.x += force.x;
	netForce.y += force.y;
	netForce.z += force.z;
}

void Particle::MoveWithConstAccel(float t)
{
	// Updates acceleration
	HandleInput(t);
}

void Particle::HandleInput(float t)
{
	// Move gameobject
	if (GetAsyncKeyState('W'))
	{
		MoveForward(t);
	}
	else if (GetAsyncKeyState('S'))
	{
		MoveBackward(t);
	}
	else if (GetAsyncKeyState('A'))
	{
		MoveLeft(t);
	}
	else if (GetAsyncKeyState('D'))
	{
		MoveRight(t);
	}
}

void Particle::MoveForward(float t)
{
	Vector3D position = _transform->GetPosition();
	
	if (useConstAccel == true)
	{
		position.z -= (_velocity.z * t) + (0.5f * _acceleration.z * t * t);
		UpdateVelocity(t);
		//position.z -= _velocity.z;
	}
	else
	{
		position.z -= _velocity.z * t;
	}

	_transform->SetPosition(position);
}

void Particle::MoveBackward(float t)
{
	Vector3D position = _transform->GetPosition();
	if (useConstAccel == true)
	{
		position.z += (_velocity.z * t) + (0.5f * _acceleration.z * t * t);
		UpdateVelocity(t);
		//position.z += _velocity.z;
	}
	else
	{
		position.z += _velocity.z * t;
	}
	_transform->SetPosition(position);
}

void Particle::MoveRight(float t)
{
	Vector3D position = _transform->GetPosition();
	if (useConstAccel == true)
	{
		position.x += (_velocity.x * t) + (0.5f * _acceleration.x * t * t);
		UpdateVelocity(t);
		//position.z += _velocity.z;
	}
	else
	{
		position.x += _velocity.x * t;
	}
	_transform->SetPosition(position);
}

void Particle::MoveLeft(float t)
{
	Vector3D position = _transform->GetPosition();
	if (useConstAccel == true)
	{
		position.x -= (_velocity.x * t) + (0.5f * _acceleration.x * t * t);
		UpdateVelocity(t);
		//position.z += _velocity.z;
	}
	else
	{
		position.x -= _velocity.x * t;
	}
	_transform->SetPosition(position);
}
