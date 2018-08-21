#include "LaminarDragGenerator.h"
#include "Particle.h"`


LaminarDragGenerator::LaminarDragGenerator()
{
}


LaminarDragGenerator::~LaminarDragGenerator()
{
}

void LaminarDragGenerator::Update(Particle * p, float deltaTime)
{
	if (p->isLaminarOn())
	{
		Vector3D dragForce = p->GetVelocity() * -dragCoefficient;
		p->AddForce(dragForce);
	}
}
