#include <pch.h>
#include "SympleCraft/Render/Camera.h"

#include "SympleCraft/Window.h"

Camera CreatePerspective(const Transform transform, float fov, float near, float far)
{
	Camera camera = malloc(sizeof(struct Camera));
	if (!camera)
		return NULL;

	camera->Type = CameraType_Perspective;
	camera->Near = near;
	camera->Far = far;
	camera->Bounds = CreateVector4(-5, 5, 5, -5);
	camera->Transform = CreateTransformFromTransform(transform);

	return camera;
}

Camera CreatePerspectiveRef(const Transform transform, float fov, float near, float far)
{
	Camera camera = malloc(sizeof(struct Camera));
	if (!camera)
		return NULL;

	camera->Type = CameraType_Perspective;
	camera->Near = near;
	camera->Far = far;
	camera->Fov = fov;
	camera->Bounds = CreateVector4(-5, 5, 5, -5);
	camera->Transform = transform;

	return camera;
}


Camera CreateOrthografic(const Transform transform, const Vector bounds, float near, float far)
{
	Camera camera = malloc(sizeof(struct Camera));
	if (!camera)
		return NULL;

	camera->Type = CameraType_Orthographic;
	camera->Near = near;
	camera->Far = far;
	camera->Fov = 80;
	camera->Bounds = CreateVectorFromVector(bounds);
	camera->Transform = CreateTransformFromTransform(transform);

	return camera;
}

Camera CreateOrthograficTRef(const Transform transform, const Vector bounds, float near, float far)
{
	Camera camera = malloc(sizeof(struct Camera));
	if (!camera)
		return NULL;

	camera->Type = CameraType_Orthographic;
	camera->Near = near;
	camera->Far = far;
	camera->Fov = 80;
	camera->Bounds = CreateVectorFromVector(bounds);
	camera->Transform = transform;

	return camera;
}

Camera CreateOrthograficVRef(const Transform transform, const Vector bounds, float near, float far)
{
	Camera camera = malloc(sizeof(struct Camera));
	if (!camera)
		return NULL;

	camera->Type = CameraType_Orthographic;
	camera->Near = near;
	camera->Far = far;
	camera->Fov = 80;
	camera->Bounds = bounds;
	camera->Transform = CreateTransformFromTransform(transform);

	return camera;
}

Camera CreateOrthograficRef(const Transform transform, const Vector bounds, float near, float far)
{
	Camera camera = malloc(sizeof(struct Camera));
	if (!camera)
		return NULL;

	camera->Type = CameraType_Orthographic;
	camera->Near = near;
	camera->Far = far;
	camera->Fov = 80;
	camera->Bounds = bounds;
	camera->Transform = transform;

	return camera;
}

void DeleteCamera(const Camera camera)
{
	DeleteVector(camera->Bounds);
	DeleteVector(camera->Transform);
	free(camera);
}

Matrix CameraView(const Camera camera)
{
	return TransformViewMatrix(camera->Transform);
}

Matrix CameraProj(const Camera camera)
{
	if (camera->Type == CameraType_Perspective)
	{
		int width, height;
		GetMainWindowSize(&width, &height);
		return PerspectiveMatrix((float)width / (float)height, camera->Fov, camera->Near, camera->Far);
	}
	else
		return OrthoMatrix(camera->Bounds->x, camera->Bounds->y, camera->Bounds->z, camera->Bounds->w, camera->Near, camera->Far);
}