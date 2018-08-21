#include "GameObject.h"

GameObject::GameObject(string type, Appearance* appearance) : _type(type)
{
	_appearance = appearance;
	_transform = new Transformation();
	_particle = new Particle(_transform);
}

GameObject::~GameObject()
{
}

void GameObject::Update(float t)
{
	_particle->Update(t);
	_transform->UpdateWorldMatrix();
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	_appearance->Draw(pImmediateContext);
}