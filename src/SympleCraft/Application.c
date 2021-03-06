#include <pch.h>

#include <gl/glew.h>
#include <glfw/glfw3.h>

#include "SympleCraft/Math/Matrix.h"
#include "SympleCraft/Math/Vector.h"
#include "SympleCraft/Render/Renderer.h"
#include "SympleCraft/Render/Camera.h"
#include "SympleCraft/Render/Mesh.h"
#include "SympleCraft/Render/Shader.h"
#include "SympleCraft/Util/List.h"
#include "SympleCraft/Window.h"
#include "SympleCraft/World/Chunk.h"
#include "SympleCraft/World/Transform.h"
#include "SympleCraft/World/World.h"

#define PI 3.141592653596

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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	fprintf(stdout, "[#]<OpenGL version>: %s\n", glGetString(GL_VERSION));

	World world = CreateWorld(3, 3);
	WorldGenerateChunk(world, 0, 0);
	WorldGenerateChunk(world, 0, 1);
	WorldGenerateChunk(world, 1, 0);
	WorldGenerateChunk(world, 2, 0);
	//WorldGenerateChunk(world, 1, 1);
	WorldGenerateChunkMeshes(world);

	shader = CreateShader("res/shaders/main.vsh", "res/shaders/main.fsh");
	BindShader(shader);

	modelTransform = CreateTransformRef(CreateVector3(0, 0, 0), CreateVector3(0, 0, 0), CreateVector3(1, 1, 1));
	camera = CreatePerspectiveRef(CreateTransformRef(CreateVector3(0, 0, -10), CreateVector3(0, 0, PI), CreateVector3(0, 0, 0)), 80, 0.01, 100);

	glPointSize(10);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	SetBackgroundColor(0.25f, 0.25f, 0.25f, 1.0f);
	while (!MainWindowShouldClose())
	{
		// Input
		{
			camera->Transform->Rotation->y -= GetDeltaMouseX() * PI / 180 * 0.7;
			if (camera->Transform->Rotation->y > PI * 2)
				camera->Transform->Rotation->y = -camera->Transform->Rotation->y;
			if (camera->Transform->Rotation->y < -PI * 2)
				camera->Transform->Rotation->y = -camera->Transform->Rotation->y;

			camera->Transform->Rotation->x += GetDeltaMouseY() * PI / 180 * 0.7;
			if (camera->Transform->Rotation->x < -PI / 2 + PI / 180)
				camera->Transform->Rotation->x = -PI / 2 + PI / 180;
			if (camera->Transform->Rotation->x > PI / 2 - PI / 180)
				camera->Transform->Rotation->x = PI / 2 - PI / 180;

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
				Vector forward = CreateVector3(sinf(camera->Transform->Rotation->y), 0, cosf(camera->Transform->Rotation->y));
				camera->Transform->Translation->x += forward->x * 0.3;
				camera->Transform->Translation->z += forward->z * 0.3;
				DeleteVector(forward);
				DeleteMatrix(view);
			}
			if (GetKeys()[GLFW_KEY_S] == GLFW_PRESS || GetKeys()[GLFW_KEY_S] == GLFW_REPEAT)
			{
				Matrix view = CameraView(camera);
				Vector forward = CreateVector3(sinf(camera->Transform->Rotation->y), 0, cosf(camera->Transform->Rotation->y));
				camera->Transform->Translation->x -= forward->x * 0.3;
				camera->Transform->Translation->z -= forward->z * 0.3;
				DeleteVector(forward);
				DeleteMatrix(view);
			}

			if (GetKeys()[GLFW_KEY_A] == GLFW_PRESS || GetKeys()[GLFW_KEY_A] == GLFW_REPEAT)
			{
				Matrix view = CameraView(camera);
				Vector right = CreateVector3(sinf(camera->Transform->Rotation->y - PI / 2), 0, cosf(camera->Transform->Rotation->y - PI / 2));
				camera->Transform->Translation->x -= right->x * 0.3;
				camera->Transform->Translation->z -= right->z * 0.3;
				DeleteVector(right);
				DeleteMatrix(view);
			}
			if (GetKeys()[GLFW_KEY_D] == GLFW_PRESS || GetKeys()[GLFW_KEY_D] == GLFW_REPEAT)
			{
				Matrix view = CameraView(camera);
				Vector right = CreateVector3(sinf(camera->Transform->Rotation->y - PI / 2), 0, cosf(camera->Transform->Rotation->y - PI / 2));
				camera->Transform->Translation->x += right->x * 0.3;
				camera->Transform->Translation->z += right->z * 0.3;
				DeleteVector(right);
				DeleteMatrix(view);
			}
		}
		Clear();

		// Projection
		{
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
		}

		RenderWorld(world, shader);

		UpdateMainWindow();
	}
	DeleteTransform(modelTransform);
	DeleteCamera(camera);
	DeleteShader(shader);
	DeleteWorld(world);

	DestroyMainWindow();
	
	glfwTerminate();
}