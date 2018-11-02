#include "QuadTree.h"

#define MAXOBJECTDENSITY 1
#define MAXLEVELS 10

QuadTree::QuadTree(int lvl, Quadrant * b) : level(lvl), bounds(b)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i] = nullptr;
	}
}

QuadTree::~QuadTree()
{
	
}

void QuadTree::Clear()
{
	gameObjectList.clear();

	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i])
		{
			nodes[i]->Clear();
			nodes[i] = nullptr;
		}
	}
}

/* Splits node into 4 new sub-nodes */
void QuadTree::Subdivide()
{
	Vector3D subScale = bounds->scale / 2.f;
	Vector3D subPosition = bounds->position;

	cout << level << endl;
	CreateNE(subPosition, subScale);
	CreateNW(subPosition, subScale);
	CreateSW(subPosition, subScale);
	CreateSE(subPosition, subScale);
}

void QuadTree::CreateNE(const Vector3D& subPosition, const Vector3D& subScale)
{
	if (!nodes[NORTHEAST])
		nodes[NORTHEAST] = new QuadTree(level+1, new Quadrant(Vector3D(subPosition.x, subPosition.y, subPosition.z + subScale.z), subScale));
}

void QuadTree::CreateNW(const Vector3D& subPosition, const Vector3D& subScale)
{
	if (!nodes[NORTHWEST])
		nodes[NORTHWEST] = new QuadTree(level+1, new Quadrant(Vector3D(subPosition.x, subPosition.y, subPosition.z), subScale));
}

void QuadTree::CreateSW(const Vector3D& subPosition, const Vector3D& subScale)
{
	if (!nodes[SOUTHWEST])
		nodes[SOUTHWEST] = new QuadTree(level+1, new Quadrant(Vector3D(subPosition.x + subScale.x, subPosition.y, subPosition.z), subScale));
}

void QuadTree::CreateSE(const Vector3D& subPosition, const Vector3D& subScale)
{
	if (!nodes[SOUTHEAST])
		nodes[SOUTHEAST] = new QuadTree(level+1, new Quadrant(Vector3D(subPosition.x + subScale.x, subPosition.y, subPosition.z + subScale.z), subScale));
}


/*
*Determines which node owns which object.
*-1 means object aren't completely fit within a child node
* of the parent node
*/
int QuadTree::GetIndex(GameObject *g)
{
	signed int index = -1;
	Vector3D midpoint = bounds->position + bounds->scale / 2.f;

	Vector3D minPosition = g->GetTransformation()->GetPosition() - Vector3D(g->GetParticle()->GetRadius(), g->GetParticle()->GetRadius(), g->GetParticle()->GetRadius());
	float length = g->GetParticle()->GetDiameter();

	// Can object fully fit inside top quadrant
	bool topQuad = minPosition.x < midpoint.x && minPosition.x + length < midpoint.x;
	// Can object fully fit inside bottom quadrant
	bool bottomQuad = minPosition.x > midpoint.x;

	// Can object completely fit inside left quadrant
	if (minPosition.z < midpoint.z && minPosition.z + length < midpoint.z)
	{
		if (topQuad)
			index = NORTHWEST;
		else if (bottomQuad)
			index = SOUTHWEST;
	}
	else if (minPosition.z > midpoint.z)
	{
		if (topQuad)
			index = NORTHEAST;
		else if (bottomQuad)
			index = SOUTHEAST;
	}

	return index;
}

void QuadTree::Insert(GameObject *g)
{
	if (nodes[0] != nullptr)
	{
		const int index = GetIndex(g);

		if (index != -1)
		{
			if (!nodes[index])
			{
				switch (index)
				{
				case NORTHEAST:
					CreateNE(bounds->position, bounds->scale / 2.f);
					break;
				case NORTHWEST:
					CreateNW(bounds->position, bounds->scale / 2.f);
					break;
				case SOUTHWEST:
					CreateSW(bounds->position, bounds->scale / 2.f);
					break;
				case SOUTHEAST:
					CreateSE(bounds->position, bounds->scale / 2.f);
					break;
				default:
					NULL;
					break;
				}
			}
			nodes[index]->Insert(g);
			return;
		}
	}

	gameObjectList.push_back(g);

	if (gameObjectList.size() > MAXOBJECTDENSITY && level < MAXLEVELS)
		if (!nodes[0])
			Subdivide();

	for (int i = 0; i < gameObjectList.size(); i++)
	{
		const int index = GetIndex(gameObjectList.at(i));

		if (index != -1)
		{
			if (!nodes[index])
			{
				switch (index)
				{
				case NORTHEAST:
					CreateNE(bounds->position, bounds->scale / 2.f);
					break;
				case NORTHWEST:
					CreateNW(bounds->position, bounds->scale / 2.f);
					break;
				case SOUTHWEST:
					CreateSW(bounds->position, bounds->scale / 2.f);
					break;
				case SOUTHEAST:
					CreateSE(bounds->position, bounds->scale / 2.f);
					break;
				}
			}

			nodes[index]->Insert(gameObjectList.at(i));
			gameObjectList.erase(gameObjectList.begin() + i);
		}
	}
}

/* Returns list of all possible collisions*/	
void QuadTree::retrieve(vector<GameObject*> &returnList, GameObject* g)
{	
	const int index = GetIndex(g);
	
	if (index != -1)
		if (nodes[index] != nullptr)
			nodes[index]->retrieve(returnList, g);

	for (GameObject* object : gameObjectList)
		returnList.push_back(object);
}
	