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

void ControllerManager::init(ParticleSystem* p)
{
	ps = p;
}

void ControllerManager::Update()
{
	// Move particle
	if (GetAsyncKeyState('W')) // forward
	{
		if (GetAsyncKeyState(VK_SHIFT))
			ps->GetGameObject()[currentObject]->GetParticle()->AddForce(Vector3D(0.0f, 0.0f, powf(ps->GetGameObject()[currentObject]->GetParticle()->GetMass(), 3)));
		else
			ps->GetGameObject()[currentObject]->GetParticle()->AddForce(Vector3D(0.0f, 0.0f, powf(ps->GetGameObject()[currentObject]->GetParticle()->GetMass(), 2)));
	}
	else if (GetAsyncKeyState('S')) // down
	{
		ps->GetGameObject()[currentObject]->GetParticle()->AddForce(Vector3D(0.0f, 0.0f, -powf(ps->GetGameObject()[currentObject]->GetParticle()->GetMass(), 2)));
	}

	if (GetAsyncKeyState('A')) // right
	{
		ps->GetGameObject()[currentObject]->GetParticle()->AddForce(Vector3D(-powf(ps->GetGameObject()[currentObject]->GetParticle()->GetMass(), 2), 0.0f, 0.0f));
	}
	else if (GetAsyncKeyState('D')) // left
	{
		ps->GetGameObject()[currentObject]->GetParticle()->AddForce(Vector3D(powf(ps->GetGameObject()[currentObject]->GetParticle()->GetMass(), 2), 0.0f, 0.0f));
	}
	if (GetAsyncKeyState('F')) // fly
	{
			ps->GetGameObject()[currentObject]->GetParticle()->AddForce(Vector3D(0.0f, powf(ps->GetGameObject()[currentObject]->GetParticle()->GetMass(), 2), 0.0f));
	}
	else if (GetAsyncKeyState(VK_SPACE)) // jump
	{
		if (CollisionsManager::Instance()->CheckBoundingPlane(ps->GetGameObject()[0], ps->GetGameObject()[currentObject]))
			ps->GetGameObject()[currentObject]->GetParticle()->AddForce(Vector3D(0.0f, powf(ps->GetGameObject()[currentObject]->GetParticle()->GetMass(), 3), 0.0f));
	}
}

