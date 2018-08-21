#include "TurbulentDragGenerator.h"
#include "Particle.h"


TurbulentDragGenerator::TurbulentDragGenerator()
{
	dragCoefficient = 0.70f;
	waterCurrentVel = Vector3D(0, 0, 5.0f);
}


TurbulentDragGenerator::~TurbulentDragGenerator()
{
}

void TurbulentDragGenerator::Update(Particle * p, float deltaTime)
{
	if (p->isLaminarOn() == false)
	{
		// Calculates magnitude of velocity
		float _velMag = Vector3D::GetMagnitude(waterCurrentVel);

		// Calculates unit of vector of velocity
		Vector3D _unitVel = Vector3D::Normalize(waterCurrentVel);

		// Calculates drag Magnitude
		float dragMag = dragCoefficient * _velMag * _velMag;

		// Calculate of x and y componenets of drag force
		Vector3D dragForce = _unitVel * -dragMag;

		p->AddForce(dragForce);
	}
}
