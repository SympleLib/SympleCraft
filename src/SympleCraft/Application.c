#include <stdio.h>
#include <gl/glew.h>
#include <glfw/glfw3.h>

#include "SympleCraft/Math/Matrix.h"
#include "SympleCraft/Math/Vector.h"
#include "SympleCraft/Render/Renderer.h"
#include "SympleCraft/Render/Camera.h"
#include "SympleCraft/Render/Mesh.h"
#include "SympleCraft/Render/Shader.h"
#include "SympleCraft/Window.h"
#include "SympleCraft/World/Transform.h"

#define PI 3.1415926535

Shader shader;
Transform modelTransform;
Camera camera;

int main()
{
	if (!glfwInit())
	{
		fprintf(stderr, "[!]<GLFW init>: error initializing GLFW\n");

		system("pause");
		return -1;
	}

	InitMainWindow();
	SetMainWindowCallbacks();

	GLenum err = glewInit();
	if (err)
	{
		fprintf(stderr, "[!]<GLEW init>: %s\n", glewGetErrorString(err));

		glfwTerminate();
		system("pause");
		return -3;
	}
	fprintf(stdout, "[#]<GLEW version>: %s\n", glewGetString(GLEW_VERSION));

	const float vertices[24] = {
		-1, -1,  1,
		-1,  1,  1,
		 1,  1,  1,
		 1, -1,  1,

		-1, -1, -1,
		-1,  1, -1,
		 1,  1, -1,
		 1, -1, -1,
	};

	const unsigned int indices[36] = {
		0, 1, 2,
		0, 2, 3,

		0, 4, 5,
		0, 5, 1,

		0, 7, 4,
		0, 3, 7,

		2, 6, 7,
		2, 7, 3,

		2, 5, 6,
		2, 1, 5,

		6, 5, 4,
		6, 4, 7,
	};

	Mesh mesh = CreateMesh(vertices, indices, 8, 12);
	shader = CreateShader("res/shaders/main.vsh", "res/shaders/main.fsh");
	BindShader(shader);

	modelTransform = CreateTransformRef(CreateVector3(0, 0, 0), CreateVector3(0, 0, 0), CreateVector3(1, 1, 1));
	camera = CreatePerspectiveRef(CreateTransformRef(CreateVector3(0, 0, -10), CreateVector3(0, 0, PI), CreateVector3(0, 0, 0)), 80, 0.01, 100);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	SetBackgroundColor(0.25f, 0.25f, 0.25f, 1.0f);
	while (!MainWindowShouldClose())
	{
		if (GetKeys()[GLFW_KEY_LEFT] == GLFW_PRESS || GetKeys()[GLFW_KEY_LEFT] == GLFW_REPEAT)
		{
			camera->Transform->Rotation->y += PI / 40;
			if (camera->Transform->Rotation->y > PI * 2)
				camera->Transform->Rotation->y = -PI * 2;
		}
		if (GetKeys()[GLFW_KEY_RIGHT] == GLFW_PRESS || GetKeys()[GLFW_KEY_RIGHT] == GLFW_REPEAT)
		{
			camera->Transform->Rotation->y -= PI / 40;
			if (camera->Transform->Rotation->y < -PI * 2)
				camera->Transform->Rotation->y = PI * 2;
		}
		if (GetKeys()[GLFW_KEY_UP] == GLFW_PRESS || GetKeys()[GLFW_KEY_UP] == GLFW_REPEAT)
		{
			camera->Transform->Rotation->x -= PI / 40;
			if (camera->Transform->Rotation->x < -PI)
				camera->Transform->Rotation->x = -PI;
		}
		if (GetKeys()[GLFW_KEY_DOWN] == GLFW_PRESS || GetKeys()[GLFW_KEY_DOWN] == GLFW_REPEAT)
		{
			camera->Transform->Rotation->x += PI / 40;
			if (camera->Transform->Rotation->x > PI)
				camera->Transform->Rotation->x = PI;
		}

		if (GetKeys()[GLFW_KEY_SPACE] == GLFW_PRESS || GetKeys()[GLFW_KEY_SPACE] == GLFW_REPEAT)
		{
			camera->Transform->Translation->y -= 0.3;
		}
		if (GetKeys()[GLFW_KEY_LEFT_SHIFT] == GLFW_PRESS || GetKeys()[GLFW_KEY_LEFT_SHIFT] == GLFW_REPEAT)
		{
			camera->Transform->Translation->y += 0.3;
		}
		if (GetKeys()[GLFW_KEY_W] == GLFW_PRESS || GetKeys()[GLFW_KEY_W] == GLFW_REPEAT)
		{
			Matrix view = CameraView(camera);
			Vector forward = FindForward(view);
			camera->Transform->Translation->x -= forward->x * 0.3;
			camera->Transform->Translation->z -= forward->z * 0.3;
			DeleteVector(forward);
			DeleteMatrix(view);
		}
		if (GetKeys()[GLFW_KEY_S] == GLFW_PRESS || GetKeys()[GLFW_KEY_S] == GLFW_REPEAT)
		{
			Matrix view = CameraView(camera);
			Vector forward = FindForward(view);
			camera->Transform->Translation->x += forward->x * 0.3;
			camera->Transform->Translation->z += forward->z * 0.3;
			DeleteVector(forward);
			DeleteMatrix(view);
		}

		if (GetKeys()[GLFW_KEY_A] == GLFW_PRESS || GetKeys()[GLFW_KEY_A] == GLFW_REPEAT)
		{
			Matrix view = CameraView(camera);
			Vector right = FindRight(view);
			camera->Transform->Translation->x -= right->x * 0.3;
			camera->Transform->Translation->z -= right->z * 0.3;
			DeleteVector(right);
			DeleteMatrix(view);
		}
		if (GetKeys()[GLFW_KEY_D] == GLFW_PRESS || GetKeys()[GLFW_KEY_D] == GLFW_REPEAT)
		{
			Matrix view = CameraView(camera);
			Vector right = FindRight(view);
			camera->Transform->Translation->x += right->x * 0.3;
			camera->Transform->Translation->z += right->z * 0.3;
			DeleteVector(right);
			DeleteMatrix(view);
		}
		Clear();

		{
			Matrix model = TransformToMatrix(modelTransform);
			SetShaderUniformMat(shader, "uModel", model);
			DeleteMatrix(model);
		}

		{
			Matrix view = CameraView(camera);
			SetShaderUniformMat(shader, "uView", view);
			DeleteMatrix(view);
		}
		
		{
			Matrix proj = CameraProj(camera);
			SetShaderUniformMat(shader, "uProj", proj);
			DeleteMatrix(proj);
		}
		Render(mesh, shader);

		UpdateMainWindow();
	}
	DeleteTransform(modelTransform);
	DeleteCamera(camera);
	DeleteShader(shader);
	DeleteMesh(mesh);

	DestroyMainWindow();
	
	glfwTerminate();
}