#pragma once
#include "GameObject.h"
#include <vector>

class ParticleManager
{
private:
	vector<GameObject*> gameObjects;
	vector<Vector3f> originalPos;

	const int killTime;
	bool isDead;

private:
	void StoreInitialPosition(GameObject* g);
	void RepositionParticle(GameObject* g);

public:
	ParticleManager(vector<GameObject*> p);
	ParticleManager(GameObject * g);
	~ParticleManager();

	vector<GameObject*> GetGameObjectList()	const							{ return gameObjects; }

	void Update(float t);
	void AddParticle(GameObject * g);
};

