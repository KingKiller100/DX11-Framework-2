#pragma once
#include "GameObject.h"
#include "Particle.h"
#include "GravityGenerator.h"
#include "LaminarDragGenerator.h"
#include "TurbulentDragGenerator.h"
#include <vector>

class ParticleSystem
{
private:
	vector<GameObject*> gameObjects;
	vector<Vector3D> originalPos;

	const int killTime;
	bool isDead;

private:
	void StoreInitialPosition(GameObject* g);
	void RepositionParticle(GameObject* g);
	//void KillParticle(GameObject* g);

public:
	ParticleSystem(vector<GameObject*> p);
	ParticleSystem(GameObject * g);
	~ParticleSystem();

	vector<GameObject*> GetGameObject()								{ return gameObjects; }

	void Update(float t);
	void AddParticle(GameObject * g);
	void AddGenerator(ForceGenerator* fg);
};

