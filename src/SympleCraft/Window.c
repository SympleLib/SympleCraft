#include <pch.h>
#include "SympleCraft/Window.h"

#include <stdlib.h>
#include <glfw/glfw3.h>

Window MainWindow;

static int Keys[GLFW_KEY_LAST];

void InitMainWindow()
{
	MainWindow = glfwCreateWindow(1280, 720, "SympleCraft", NULL, NULL);
	if (!MainWindow)
	{
		fprintf(stderr, "[!]: Cannot create window!\n");
		system("pause");
		exit(-2);
	}
	glfwMakeContextCurrent(MainWindow);
	glfwSwapInterval(1);
}
void DestroyMainWindow()
{
	glfwSetWindowShouldClose(MainWindow, GLFW_TRUE);
}

int MainWindowShouldClose()
{
	return glfwWindowShouldClose(MainWindow);
}
void UpdateMainWindow()
{
	glfwSwapBuffers(MainWindow);
	glfwPollEvents(MainWindow);
}

void ResizeMainWindow(int width, int height)
{
	glfwSetWindowSize(MainWindow, width, height);
}
void GetMainWindowSize(int* width, int* height)
{
	glfwGetWindowSize(MainWindow, width, height);
}

void SetMainWindowTitle(const char* title)
{
	glfwSetWindowTitle(MainWindow, title);
}

/* ----- Callbacks ----- */
static void MainWindowSizeCallback(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);
}
static void MainWindowKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		DestroyMainWindow();
		return;
	}
	Keys[key] = action;
}
/* ----- End Callbacks ----- */

void SetMainWindowCallbacks()
{
	glfwSetWindowSizeCallback(MainWindow, MainWindowSizeCallback);
	glfwSetKeyCallback(MainWindow, MainWindowKeyCallback);
}

const int* GetKeys()
{
	return Keys;
}