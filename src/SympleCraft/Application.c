#include <stdio.h>
#include <gl/glew.h>
#include <glfw/glfw3.h>

#include "SympleCraft/Math/Vector.h"
#include "SympleCraft/Math/Matrix.h"
#include "SympleCraft/Renderer.h"
#include "SympleCraft/Shader.h"
#include "SympleCraft/Mesh.h"

void WindowSizeCallback(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);
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
		-0.5f, -0.5f,
		-0.5f,  0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f
	};

	const unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	Mesh mesh = CreateMesh(vertices, indices, 4, 6);
	//Vector color = CreateVector3(0, 1, 0);

	Shader shader = CreateShader("res/shaders/main.vsh", "res/shaders/main.fsh");
	BindShader(shader);
	//SetShaderUniformVec(shader, "uCol", color);

	SetBackgroundColor(0.25f, 0.25f, 0.25f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		Clear();

		Render(mesh);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
}