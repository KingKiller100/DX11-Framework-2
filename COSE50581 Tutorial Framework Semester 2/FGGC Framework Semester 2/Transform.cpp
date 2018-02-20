#include "Transform.h"

Transform::Transform()
{
	_position = Vector3D();
	_rotation = Vector3D();
	_scale = Vector3D(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
}

// Calculate world matrix
XMMATRIX Transform::GetTranslationMatrix()
{
	XMMATRIX translation = XMMatrixTranslation(_position.x, _position.y, _position.z);
	return translation;
}

XMMATRIX Transform::GetScaleMatrix()
{
	XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	return scale;
}

XMMATRIX Transform::GetRotationMatrix()
{
	XMMATRIX rotation = XMMatrixRotationX(_rotation.x) * XMMatrixRotationY(_rotation.y) * XMMatrixRotationZ(_rotation.z);
	return rotation;
}
