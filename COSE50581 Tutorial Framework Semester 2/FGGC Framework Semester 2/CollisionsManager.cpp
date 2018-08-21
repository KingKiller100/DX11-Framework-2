#include "CollisionsManager.h"

// Initialise the instacne to null
CollisionsManager* CollisionsManager::mInstance = NULL;

CollisionsManager::CollisionsManager()
{
}

CollisionsManager::~CollisionsManager()
{
	mInstance = nullptr;
}

CollisionsManager * CollisionsManager::Instance()
{
	if (!mInstance)
		mInstance = new CollisionsManager;

	return mInstance;
}

bool CollisionsManager::CheckBoundingSphere(GameObject * go1, GameObject * go2)
{
	float distance = go1->GetTransformation()->GetPosition().Distance(go2->GetTransformation()->GetPosition());

	return (distance < go1->GetParticle()->GetRadius() + go2->GetParticle()->GetRadius());
}

bool CollisionsManager::CheckBoundingBox(GameObject * go1, GameObject * go2)
{
	Vector3D aVertices[8] =
	{
		Vector3D(1, 1, 1), // back top right
		Vector3D(1, 1, -1), // front top right
		Vector3D(-1, 1, -1), // front top left
		Vector3D(-1, 1, 1), // back top left
		Vector3D(-1, -1, 1), // back bottom left
		Vector3D(-1, -1,-1), // front bottom right
		Vector3D(1, -1, -1), // front bottom right 
		Vector3D(1, -1, 1), // back bottom right
	};

	for (Vector3D v : aVertices)
	{
		v *= go1->GetParticle()->GetRadius();
		v += go1->GetTransformation()->GetPosition();
	}

	Vector3D bVertices[8] =
	{
		Vector3D(1, 1, 1), // back top right
		Vector3D(1, 1, -1), // front top right
		Vector3D(-1, 1, -1), // front top left
		Vector3D(-1, 1, 1), // back top left
		Vector3D(-1, -1, 1), // back bottom left
		Vector3D(-1, -1,-1), // front bottom right
		Vector3D(1, -1, -1), // front bottom right 
		Vector3D(1, -1, 1), // back bottom right
	};

	for (Vector3D v : bVertices)
	{
		v *= go2->GetParticle()->GetRadius();
		v += go2->GetTransformation()->GetPosition();
	}

	return false;
	//float aMaxX = go1->GetTransformation()->GetPosition().x + go1->GetParticle()->GetRadius();
	//float aMinX = go1->GetTransformation()->GetPosition().x - go1->GetParticle()->GetRadius();
	//float aMaxY = go1->GetTransformation()->GetPosition().y + go1->GetParticle()->GetRadius();
	//float aMinY = go1->GetTransformation()->GetPosition().y - go1->GetParticle()->GetRadius();
	//float aMaxZ = go1->GetTransformation()->GetPosition().z + go1->GetParticle()->GetRadius();
	//float aMinZ = go1->GetTransformation()->GetPosition().z - go1->GetParticle()->GetRadius();

	//float bMaxX = go2->GetTransformation()->GetPosition().x + go2->GetParticle()->GetRadius();
	//float bMinX = go2->GetTransformation()->GetPosition().x - go2->GetParticle()->GetRadius();
	//float bMaxY = go2->GetTransformation()->GetPosition().y + go2->GetParticle()->GetRadius();
	//float bMinY = go2->GetTransformation()->GetPosition().y - go2->GetParticle()->GetRadius();
	//float bMaxZ = go2->GetTransformation()->GetPosition().z + go2->GetParticle()->GetRadius();
	//float bMinZ = go2->GetTransformation()->GetPosition().z - go2->GetParticle()->GetRadius();

	/*return (aMinX <= bMaxX && aMaxX >= bMinX) &&
		(aMinY <= bMaxY && aMaxY >= bMinY) && 
		(aMinZ <= bMaxZ && aMaxZ >= bMinZ);*/
}

bool CollisionsManager::CheckBoundingPlane(GameObject * go1, GameObject * go2)
{
	// Store plane data as if it's a 2D shape - only using x and y axis
	float aMaxX = go1->GetTransformation()->GetPosition().x + go1->GetTransformation()->GetScale().x;
	float aMinX = go1->GetTransformation()->GetPosition().x - go1->GetTransformation()->GetScale().x;
	float aMaxY = go1->GetTransformation()->GetPosition().y;
	float aMaxZ = go1->GetTransformation()->GetPosition().z + go1->GetTransformation()->GetScale().z;
	float aMinZ = go1->GetTransformation()->GetPosition().z - go1->GetTransformation()->GetScale().z;

	float bMaxX = go2->GetTransformation()->GetPosition().x + go2->GetParticle()->GetRadius();
	float bMinX = go2->GetTransformation()->GetPosition().x - go2->GetParticle()->GetRadius();
	float bMinY = go2->GetTransformation()->GetPosition().y - go2->GetParticle()->GetRadius();
	float bMaxZ = go2->GetTransformation()->GetPosition().z + go2->GetParticle()->GetRadius();
	float bMinZ = go2->GetTransformation()->GetPosition().z - go2->GetParticle()->GetRadius();

	return (aMinX <= bMaxX && aMaxX >= bMinX) && 
		(bMinY <= aMaxY) && 
		(aMinZ <= bMaxZ && aMaxZ >= bMinZ);
}

void CollisionsManager::Seperation(GameObject * go1, GameObject* go2)
{
	// Sperate objects after inter-object collision
	
	float radiiSum = go1->GetParticle()->GetRadius() + go2->GetParticle()->GetRadius();
	float distance = Vector3D::GetMagnitude(go1->GetTransformation()->GetPosition() - go2->GetTransformation()->GetPosition());
	float depth = radiiSum - distance;
	Vector3D direction = Vector3D::Normalize(go1->GetTransformation()->GetPosition() - go2->GetTransformation()->GetPosition());

	Vector3D object1Pos = go1->GetTransformation()->GetPosition() + direction * depth;
	Vector3D object2Pos = go2->GetTransformation()->GetPosition() - direction * depth;

	go1->GetTransformation()->SetPosition(object1Pos);
	go2->GetTransformation()->SetPosition(object2Pos);

	ResolveCollision(go1, go2);
}

void CollisionsManager::ResolveCollision(GameObject* go1, GameObject* go2)
{	
	// Resolves after seperating the two objects during collision
	float e = go1->GetParticle()->GetCoefficientOfRestitution() + go2->GetParticle()->GetCoefficientOfRestitution() / 2;

	Vector3D firstRest = go1->GetParticle()->GetVelocity() * (go1->GetParticle()->GetMass() - (go2->GetParticle()->GetMass() * e));
	//Vector3D secondRest = go2->GetParticle()->GetVelocity() * (go2->GetParticle()->GetMass() - (go1->GetParticle()->GetMass() * e));
	Vector3D secondRest = go2->GetParticle()->GetVelocity() * (go2->GetParticle()->GetMass() * (1.0f + e));

	Vector3D finalVel1 = (firstRest + secondRest) / (go1->GetParticle()->GetMass() + go2->GetParticle()->GetMass());

	firstRest = go1->GetParticle()->GetVelocity() * go1->GetParticle()->GetMass();
	secondRest = go2->GetParticle()->GetVelocity() * go2->GetParticle()->GetMass();

	Vector3D temp = finalVel1 * go1->GetParticle()->GetMass();
	Vector3D finalVel2 = (firstRest + secondRest - temp) / go2->GetParticle()->GetMass();

	Vector3D norm1 = Vector3D::Normalize(go1->GetTransformation()->GetPosition() - go2->GetTransformation()->GetPosition());
	Vector3D norm2 = norm1.ReverseVector();

	Vector3D relativeVel1 = norm1  * Vector3D::DotProduct(norm1, finalVel1);
	Vector3D relativeVel2 = norm2 * Vector3D::DotProduct(norm2, finalVel2);

	finalVel1 += relativeVel2 - relativeVel1;
	finalVel2 += relativeVel1 - relativeVel2;

	//finalVel1.y = fabsf(finalVel1.y * 0.85f);
	//finalVel2.y = fabsf(finalVel2.y * 0.85f);

	go1->GetParticle()->SetVelocity(finalVel2);
	go2->GetParticle()->SetVelocity(finalVel1);
}

void CollisionsManager::Update(GameObject * go1, GameObject * go2)
{
	if (go1->GetType() != go2->GetType())
		if (CheckBoundingSphere(go1, go2))
			Seperation(go1, go2);

	if (go1->GetType() == "Floor" && go1->GetType() != go2->GetType())
		if (CheckBoundingPlane(go1, go2))
		{
			go2->GetParticle()->SetVelocity(Vector3D(go2->GetParticle()->GetVelocity().x, go2->GetParticle()->GetVelocity().y * -0.75f, go2->GetParticle()->GetVelocity().z));
			if (go2->GetParticle()->GetVelocity().y < 0.2f)
				go2->GetTransformation()->SetPosition(Vector3D(go2->GetTransformation()->GetPosition().x, go1->GetTransformation()->GetPosition().y + go2->GetParticle()->GetRadius(), go2->GetTransformation()->GetPosition().z));
		}
}