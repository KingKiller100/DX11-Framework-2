#pragma once
#include "GameObject.h"

class CollisionsManager
{
private:
	static CollisionsManager* mInstance;

private:
	CollisionsManager();

public:
	~CollisionsManager();

	static CollisionsManager* Instance();

	bool CheckBoundingSphere(GameObject* go1, GameObject* go2) const;
	bool CheckBoundingBox(GameObject* go1, GameObject* go2);
	bool CheckBoundingPlane(GameObject* go1, GameObject* go2) const;

	void Separation(GameObject* go1, GameObject* go2);
	void ResolveCollision(GameObject* go1, GameObject* go2);

	void Update(GameObject * go1, GameObject * go2);

};

