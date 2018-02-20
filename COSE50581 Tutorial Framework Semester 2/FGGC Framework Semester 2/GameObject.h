#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "Vector3D.h"

#include "Transformation.h"
#include "Appearance.h"
#include "Particle.h"

using namespace DirectX;
using namespace std;


class GameObject
{
public:
	GameObject(string type, Appearance* appearance);
	~GameObject();

	string GetType() const { return _type; }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }

	Transformation * GetTransformation() const { return _transform; }
	Particle * GetParticle() const { return _particle; }
	Appearance * GetAppearance() const { return _appearance; }

	void SetParent(GameObject * parent) { _parent = parent; }

	void Update(float t);
	void Draw(ID3D11DeviceContext * pImmediateContext);
private:
	Transformation* _transform;
	Particle* _particle;
	Appearance* _appearance;

	string _type;

	XMFLOAT4X4 _world;

	GameObject * _parent;
};

