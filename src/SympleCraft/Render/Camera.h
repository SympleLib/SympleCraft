#pragma once

#include "SympleCraft/World/Transform.h"
#include "SympleCraft/Math/Matrix.h"

typedef enum CameraType
{
	CameraType_Perspective,
	CameraType_Orthographic
} const *CameraType;

typedef struct Camera
{
	Transform Transform;
	
	CameraType Type;

	float Near, Far;

	// Perspective Data
	float Fov;
	// Othographic Data
	Vector Bounds;
} *Camera;

Camera CreatePerspective(const Transform transform, float fov, float near, float far);
Camera CreatePerspectiveRef(const Transform transform, float fov, float near, float far);
Camera CreateOrthografic(const Transform transform, const Vector bounds, float near, float far);
Camera CreateOrthograficRef(const Transform transform, const Vector bounds, float near, float far);
Camera CreateOrthograficTRef(const Transform transform, const Vector bounds, float near, float far);
Camera CreateOrthograficVRef(const Transform transform, const Vector bounds, float near, float far);
void DeleteCamera(const Camera camera);

Matrix CameraView(const Camera camera);
Matrix CameraProj(const Camera camera);