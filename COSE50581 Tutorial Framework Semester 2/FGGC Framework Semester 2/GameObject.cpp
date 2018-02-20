#include "GameObject.h"

GameObject::GameObject(string type, Appearance* appearance) : _type(type)
{
	_parent = nullptr;
	_appearance = appearance;
	_transform = new Transformation();
	_particle = new Particle(_transform, Vector3D(0.05f, 0.05f, 0.05f), Vector3D(0.05f, 0.05f, 0.05f), 1.0f);
}

GameObject::~GameObject()
{
}

void GameObject::Update(float t)
{
	XMStoreFloat4x4(&_world, _transform->GetScaleMatrix() * _transform->GetRotationMatrix() * _transform->GetTranslationMatrix());

	if (_parent)
	{
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parent->GetWorldMatrix());
	}
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	_appearance->Draw(pImmediateContext);
}