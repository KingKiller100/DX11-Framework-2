#include "ParticleManager.h"

ParticleManager::ParticleManager(vector<GameObject*> g) : killTime(10)
{
	gameObjects = g;
	isDead = false;

	for (GameObject* g : g)
	{
		StoreInitialPosition(g);
	}
}

ParticleManager::ParticleManager(GameObject* g) : killTime(10)
{
	gameObjects.push_back(g);
	isDead = false;

	StoreInitialPosition(g);
}

ParticleManager::~ParticleManager()
{
	for (GameObject* g : gameObjects)
	{
		if (g)
		{
			delete g;
			g = nullptr;
		}
	}
}

void ParticleManager::StoreInitialPosition(GameObject* g)
{
	originalPos.push_back(g->GetTransformation()->GetPosition());
}

void ParticleManager::AddParticle(GameObject* g)
{
	gameObjects.push_back(g);
	StoreInitialPosition(g);
}

void ParticleManager::RepositionParticle(GameObject* g)
{
	for (int i = gameObjects.size() - 1; i > 1; i--)
	{
		if (g->GetType() == gameObjects[i]->GetType())
		{
			g->GetTransformation()->SetPosition(originalPos[i]);
			g->GetParticle()->SetVelocity(Vector3D());
			g->GetParticle()->SetAcceleration(Vector3D());
		}
	}
}

void ParticleManager::AddGenerator(ForceGenerator* fg)
{
	for (GameObject* g : gameObjects)
	{
			g->GetParticle()->AddGenerator(fg);
	}
}

void ParticleManager::Update(float t)
{
	for (GameObject* g : gameObjects)
	{
		g->Update(t);
	}

	for (GameObject* g : gameObjects)
	{
		if (g->GetParticle()->GetLifetimer() >= killTime && g->GetParticle()->GetIsKillable())
		{
			RepositionParticle(g);
			g->GetParticle()->ResetLifeTimer();
		}
	}
}
