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

public:
	Transformation();
	~Transformation();

	// Setters and Getters for position/rotation/scale
	void SetPosition(Vector3D position) { _position = position; }
	void SetPositionXYZ(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }

	Vector3D GetPosition() const { return _position; }
	XMMATRIX GetTranslationMatrix();

	void SetScale(Vector3D scale) { _scale = scale; }
	void SetScaleXYZ(float x, float y, float z) { _scale.x = x; _scale.y = y; _scale.z = z; }

	Vector3D GetScale() const { return _scale; }
	XMMATRIX GetScaleMatrix();

	void SetRotation(Vector3D rotation) { _rotation = rotation; }
	void SetRotationXYZ(float x, float y, float z) { _rotation.x = x; _rotation.y = y; _rotation.z = z; }

	Vector3D GetRotation() const { return _rotation; }
	XMMATRIX GetRotationMatrix();
};

