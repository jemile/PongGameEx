#pragma once
#include <thread>

#include "glad.h"
#include <GLFW/glfw3.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

class DRAW;
class MOVEMENT;

namespace FRAME
{
	extern int width;
	extern int height;

	extern GLFWwindow* window;
	extern DRAW* draw;
	extern MOVEMENT* movement;
	extern std::thread playerControl;

	extern void InitGlfwFlags();
	extern void RenderLoop();
	extern void SetupFrame();
	extern void UnloadFrame();
}