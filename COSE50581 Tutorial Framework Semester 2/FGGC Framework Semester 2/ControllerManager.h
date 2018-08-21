#pragma once
#include "ParticleSystem.h"

class ControllerManager
{
private:
	static ControllerManager* mInstance;

	char moveForward;
	char moveBackward;
	char moveRight;
	char moveLeft;

	//vector<GameObject*> gameObjects;
	ParticleSystem* ps;
	int currentObject;

private:
	ControllerManager();
public:
	~ControllerManager();

	static ControllerManager* Instance();
	void init(ParticleSystem* p);

	void Update();

	// Movement Accessor Methiods
	void SetForwardButton(const char f)					{ moveForward = f; }
	void SetBackwardButton(const char b)				{ moveForward = b; }
	void SetRightButton(const char r)					{ moveForward = r; }
	void SetLeftButton(const char l)					{ moveForward = l; }

	// CO Accessor Methods
	void SetCurrentObject(const int co)					{ currentObject = co; }
};

