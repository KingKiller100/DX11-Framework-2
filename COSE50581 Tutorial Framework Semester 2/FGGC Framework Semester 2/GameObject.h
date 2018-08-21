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
private:
	Transformation* _transform;
	Particle* _particle;
	Appearance* _appearance;
	string _type;

public:
	GameObject(string type, Appearance* appearance);
	~GameObject();

	string GetType()									const { return _type; }
	Transformation * GetTransformation()				const { return _transform; }
	Particle * GetParticle()							const { return _particle; }
	Appearance * GetAppearance()						const { return _appearance; }

	void Update(float t);
	void Draw(ID3D11DeviceContext * pImmediateContext);
};

