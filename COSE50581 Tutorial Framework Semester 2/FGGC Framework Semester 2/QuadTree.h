#pragma once
#include <vector>
#include <array>
#include "GameObject.h"

enum Compass
{
	NORTHEAST = 0,
	NORTHWEST,
	SOUTHWEST,
	SOUTHEAST,
};

struct Quadrant
{
	Vector3D position;
	Vector3D scale;

	Quadrant()
	{
		position = scale = Vector3D();
	}

	Quadrant(const float xVal, const float zVal, const float w, const float h) : position(Vector3D(xVal, 0, zVal)), scale(Vector3D(w, 0, h)) {/* Empty */ }

	Quadrant(const Vector3D &p, const Vector3D &s) : position(p), scale(s)
	{
	}
};

class QuadTree
{
private:
	u_int level;
	std::vector<GameObject*> gameObjectList;
	Quadrant *bounds;
	std::array<QuadTree*, 4> nodes;

private:
	void Subdivide();
	int GetIndex(GameObject *g);

	void CreateNE(const Vector3D &subPosition, const Vector3D &subScale);
	void CreateNW(const Vector3D &subPosition, const Vector3D &subScale);
	void CreateSE(const Vector3D &subPosition, const Vector3D &subScale);
	void CreateSW(const Vector3D &subPosition, const Vector3D &subScale);

public:
	QuadTree(int lvl, Quadrant *b);
	~QuadTree();

	void Clear();
	void Insert(GameObject *g);

	void retrieve(vector<GameObject*> &returnList, GameObject* g);
};
