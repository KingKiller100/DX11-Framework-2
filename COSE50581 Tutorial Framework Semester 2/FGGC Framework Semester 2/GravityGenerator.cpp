#include "GravityGenerator.h"
#include "Particle.h"


GravityGenerator::GravityGenerator()
{
	gravity = Vector3D(0.0f, -9.81f, 0.0f);
}


GravityGenerator::~GravityGenerator()
{
}

void GravityGenerator::Update(Particle* p, float deltatime)
{
	p->AddForce(gravity * p->GetMass());
}