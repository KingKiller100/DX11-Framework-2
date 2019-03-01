#include "QuadTree.h"

#define MAXOBJECTDENSITY 0
#define MAXLEVELS 10
QuadTree::QuadTree(Quadrant * b, const unsigned lvl) : level(lvl), bounds(b)
{
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		nodes[i] = nullptr;
	}
}

QuadTree::~QuadTree()
{
	delete bounds;
	bounds = nullptr;

	for (auto& node : nodes)
	{
		delete node;
		node = nullptr;
	}
}

/* Clears quad tree */
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
	const auto subScale = bounds->position * .25f;
	const auto subPosition = bounds->position;

	CreateNE(subPosition, subScale);
	CreateNW(subPosition, subScale);
	CreateSW(subPosition, subScale);
	CreateSE(subPosition, subScale);
}

void QuadTree::CreateNE(const Vector3f &subPosition, const Vector3f &subScale)
{
	if (!nodes[NORTHEAST])
		nodes[NORTHEAST] = new QuadTree(new Quadrant(Vector3f(subPosition.x + subScale.x, subPosition.y, subPosition.z - subScale.z), subPosition), level + 1);
}

void QuadTree::CreateNW(const Vector3f &subPosition, const Vector3f &subScale)
{
	if (!nodes[NORTHWEST])
		nodes[NORTHWEST] = new QuadTree(new Quadrant(subX - subWidth * .5f, subY + subHeight * .5f, subWidth, subHeight), level + 1);
}

void QuadTree::CreateSE(const Vector3f &subPosition, const Vector3f &subScale)
{
	if (!nodes[SOUTHEAST])
		nodes[SOUTHEAST] = new QuadTree(new Quadrant(subX + subWidth * .5f, subY - subHeight * .5f, subWidth, subHeight), level + 1);
}

void QuadTree::CreateSW(const Vector3f &subPosition, const Vector3f &subScale)
{
	if (!nodes[SOUTHWEST])
		nodes[SOUTHWEST] = new QuadTree(new Quadrant(subX - subWidth * .5f, subY - subHeight * .5f, subWidth, subHeight), level + 1);
}

/*
*Determines which node owns which object.
*-1 means object aren't completely fit within a child node
* of the parent node
*/
int QuadTree::GetIndex(GameObject *g) const
{
	signed int index = -1;
	const Vector3f midpoint = bounds->position;

	const Vector3f entityDimension = e->hasComponent<component::RectCollider>() ?
		Vector3f(e->getComponent<component::RectCollider>()->GetWidth(), e->getComponent<component::RectCollider>()->GetHeight())
		: Vector3f(e->getComponent<component::CircleCollider>()->GetRadius());

	const Vector3f offset = e->hasComponent<component::RectCollider>() ? e->getComponent<component::RectCollider>()->GetOffset()
		: e->getComponent<component::CircleCollider>()->GetOffset();

	const Vector3f entityPos = e->getComponent<component::Transform>()->GetPositionV2D() + offset;

	// Can object fully fit inside top quadrant
	const bool topQuad = entityPos.Y - entityDimension.Y > midpoint.Y;
	// Can object fully fit inside bottom quadrant
	const bool bottomQuad = entityPos.Y - entityDimension.Y < midpoint.Y && entityPos.Y + entityDimension.Y < midpoint.Y;

	// Can object completely fit inside left quadrant
	if (entityPos.X - entityDimension.X < midpoint.X && entityPos.X + entityDimension.X < midpoint.X) // West-side
	{
		if (topQuad)
			index = NORTHWEST;
		else if (bottomQuad)
			index = SOUTHWEST;
	}
	else if (entityPos.X - entityDimension.X > midpoint.X) // East-side
	{
		if (topQuad)
			index = NORTHEAST;
		else if (bottomQuad)
			index = SOUTHEAST;
	}

	return index;
}

void QuadTree::AddIntoTree(GameObject *e)
{
	int index = GetIndex(e);

	if (index != -1)
	{
		if (nodes[index] && level < MAXLEVELS)
		{
			nodes[index]->AddIntoTree(e);
			return;
		}
	}

	gameObjectList.emplace_back(e);

	if (index != -1)
		if (gameObjectList.size() > MAXOBJECTDENSITY && level < MAXLEVELS)
		{
			if (!nodes[index])
				Subdivide();

			size_t i = 0;

			while (i < gameObjectList.size())
			{
				index = GetIndex(gameObjectList[i]);

				if (index != -1)
				{
					nodes[index]->AddIntoTree(gameObjectList[i]);
					gameObjectList.erase(gameObjectList.begin() + i);
				}
				else
					i++;
			}
		}
}
void QuadTree::CollidablesList(std::vector<GameObject*> &returnList, GameObject *e)
{
	const int index = GetIndex(e);

	if (index != -1 && nodes[index])
		nodes[index]->CollidablesList(returnList, e);

	for (GameObject *entity : gameObjectList)
	{
		if (e != entity)
			returnList.emplace_back(entity);
	}
}