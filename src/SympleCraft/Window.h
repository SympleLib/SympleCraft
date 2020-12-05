#pragma once

typedef struct GLFWwindow *Window;

extern Window MainWindow;

void InitMainWindow();
void SetMainWindowCallbacks();
void DestroyMainWindow();

int MainWindowShouldClose();
void UpdateMainWindow();

void ResizeMainWindow(int width, int height);
void GetMainWindowSize(int* width, int* height);

void SetMainWindowTitle(const char* title);

const int* GetKeys();
double GetMouseX();
double GetMouseY();
double GetPMouseX();
double GetPMouseY();
double GetDeltaMouseX();
double GetDeltaMouseY();