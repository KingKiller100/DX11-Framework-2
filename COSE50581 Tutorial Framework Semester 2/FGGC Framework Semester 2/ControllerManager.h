#pragma once
#include "ParticleManager.h"

class ControllerManager
{
private:
	static ControllerManager* mInstance;

	char moveForward;
	char moveBackward;
	char moveRight;
	char moveLeft;
	char fly;
	char jump;

	ParticleManager* ps;
	int currentObject;

private:
	ControllerManager();

public:
	~ControllerManager();

	static ControllerManager* Instance();
	void init(ParticleManager* p);

	void Update();

	// Movement Accessor Methods
	void SetForwardButton(const char &f)				{ moveForward = f; }
	void SetBackwardButton(const char &b)				{ moveBackward = b; }
	void SetRightButton(const char &r)					{ moveRight = r; }
	void SetLeftButton(const char &l)					{ moveLeft = l; }
	void SetFlyButton(const char &f)					{ fly = f; }
	void SetJumpButton(const char &j)					{ jump = j; }


	// CO Accessor Methods
	void SetCurrentObject(const int co)					{ currentObject = co; }
};

