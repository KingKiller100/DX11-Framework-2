#pragma once
#include "GameObject.h"
#include "GravityGenerator.h"
#include <vector>

class ParticleManager
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
	ParticleManager(vector<GameObject*> p);
	ParticleManager(GameObject * g);
	~ParticleManager();

	vector<GameObject*> GetGameObjectList()								{ return gameObjects; }

	void Update(float t);
	void AddParticle(GameObject * g);
	void AddGenerator(ForceGenerator* fg);
};

