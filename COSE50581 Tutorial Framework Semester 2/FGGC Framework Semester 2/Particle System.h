#pragma once
#include "Particle.h"
#include <vector>

using namespace std;

class ParticleSystem
{
public:
	void CreateParticle(); // Creates particle
	void DestroyParticle(); // deletes paticle

	void Update(float deltaTime);
	void Draw();

private:
	int NumParticles;
	vector<Particle*> particleList;
};