 #include "ControllerManager.h"
#include "CollisionsManager.h"

// Initialise instance to Null
ControllerManager* ControllerManager::mInstance = NULL;


ControllerManager::ControllerManager()
{
	moveForward = 'W';
	moveLeft = 'A';
	moveBackward = 'S';
	moveRight = 'D';
	fly = 'F';
	jump = 'J';

	currentObject = 1;
}


ControllerManager::~ControllerManager()
{
}

ControllerManager * ControllerManager::Instance()
{
	if (!mInstance)
		mInstance = new ControllerManager;

	return mInstance;
}

void ControllerManager::init(GameObjectManager* p)
{
	ps = p;
}

void ControllerManager::Update()
{
	// Move particle
	if (GetAsyncKeyState(moveForward)) // forward
	{
		if (GetAsyncKeyState(VK_SHIFT))
			ps->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(0.0f, 0.0f, powf(ps->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 3)));
		else
			ps->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(0.0f, 0.0f, powf(ps->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 2)));
	}
	else if (GetAsyncKeyState(moveBackward)) // down
	{
		ps->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(0.0f, 0.0f, -powf(ps->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 2)));
	}

	if (GetAsyncKeyState(moveRight)) // right
	{
		ps->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(-powf(ps->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 2), 0.0f, 0.0f));
	}
	else if (GetAsyncKeyState(moveLeft)) // left
	{
		ps->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(powf(ps->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 2), 0.0f, 0.0f));
	}
	if (GetAsyncKeyState(fly)) // fly
	{
			ps->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(0.0f, powf(ps->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 2), 0.0f));
	}
	else if (GetAsyncKeyState(VK_SPACE)) // jump
	{
		if (CollisionsManager::Instance()->CheckBoundingPlane(ps->GetGameObjectList()[0], ps->GetGameObjectList()[currentObject]))
			ps->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(0.0f, powf(ps->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 3), 0.0f));
	}
}
