#pragma once
#include <DirectXMath.h>
#include "Vector3D.h"

using namespace DirectX;

class Transformation
{
private:
	Vector3D _position;
	Vector3D _rotation;
	Vector3D _scale;

	XMFLOAT4X4 _world;
	Transformation * _parent;
public:
	Transformation();
	~Transformation();

	// Setters and Getters for position/rotation/scale/original position

	void SetPosition(Vector3D position)					{ _position = position; }
	void SetPosition(float x, float y, float z)			{ _position.x = x; _position.y = y; _position.z = z; }

	Vector3D GetPosition() const						const { return _position; }
	XMMATRIX GetTranslationMatrix();

	void SetScale(Vector3D scale)						{ _scale = scale; }
	void SetScale(float x, float y, float z)			{ _scale.x = x; _scale.y = y; _scale.z = z; }

	Vector3D GetScale() const							const { return _scale; }
	XMMATRIX GetScaleMatrix();

	void SetRotation(Vector3D rotation)					{ _rotation = rotation; }
	void SetRotation(float x, float y, float z)			{ _rotation.x = x; _rotation.y = y; _rotation.z = z; }

	Vector3D GetRotation() const						const { return _rotation; }
	XMMATRIX GetRotationMatrix();

	XMMATRIX GetWorldMatrix()							const { return XMLoadFloat4x4(&_world); }
	void UpdateWorldMatrix();

	void SetParent(Transformation * parent) { _parent = parent; }
};

