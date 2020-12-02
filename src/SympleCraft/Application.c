#include <stdio.h>
#include <gl/glew.h>
#include <glfw/glfw3.h>

#include "SympleCraft/Math/Vector.h"
#include "SympleCraft/Math/Matrix.h"
#include "SympleCraft/World/Transform.h"
#include "SympleCraft/Render/Renderer.h"
#include "SympleCraft/Render/Shader.h"
#include "SympleCraft/Render/Mesh.h"

#define PI 3.1415926535

Shader shader;
Transform modelTransform;
Transform camTransform;

void WindowSizeCallback(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);

	Matrix proj = PerspectiveMatrix((float)width / (float)height, 80, 0.1, 100);
	//Matrix proj = OrthoMatrix(-5, 5, 5, -5, 0.1, 100);
	SetShaderUniformMat(shader, "uProj", proj);
	DeleteMatrix(proj);
}

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
	{
		fprintf(stderr, "[!]<GLFW init>: error initializing GLFW\n");

		system("pause");
		return -1;
	}

	window = glfwCreateWindow(1280, 720, "SympleCraft", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		system("pause");
		return -2;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, WindowSizeCallback);
	glfwSwapInterval(1);

	GLenum err = glewInit();
	if (err)
	{
		fprintf(stderr, "[!]<GLEW init>: %s\n", glewGetErrorString(err));

		glfwTerminate();
		system("pause");
		return -3;
	}
	fprintf(stdout, "[#]<GLEW version>: %s\n", glewGetString(GLEW_VERSION));

	const float vertices[] = {
		-1, -1,
		-1,  1,
		 1,  1,
		 1, -1,
	};

	const unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	Mesh mesh = CreateMesh(vertices, indices, 4, 6);
	shader = CreateShader("res/shaders/main.vsh", "res/shaders/main.fsh");
	BindShader(shader);

	modelTransform = CreateTransformRef(CreateVector3(0, 0, 0), CreateVector3(0, 0, 0), CreateVector3(1, 1, 1));
	camTransform = CreateTransformRef(CreateVector3(0, 0, -10), CreateVector3(0, 0, 0), CreateVector3(0, 0, 0));

	{
		Matrix model = TransformToMatrix(modelTransform);
		SetShaderUniformMat(shader, "uModel", model);
		DeleteMatrix(model);
	}

	{
		Matrix view = TransformViewMatrix(camTransform);
		SetShaderUniformMat(shader, "uView", view);
		DeleteMatrix(view);
	}

	{
		Matrix proj = PerspectiveMatrix((float)16 / (float)9, 80, 0.1, 100);
		//Matrix proj = OrthoMatrix(-5, 5, 5, -5, 0.1, 100);
		SetShaderUniformMat(shader, "uProj", proj);
		DeleteMatrix(proj);
	}

	SetBackgroundColor(0.25f, 0.25f, 0.25f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		Clear();

		Render(mesh);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	DeleteTransform(modelTransform);
	DeleteTransform(camTransform);
	DeleteShader(shader);
	DeleteMesh(mesh);
	
	glfwTerminate();
}