#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "imGui/imgui.h"
#include "imGui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"
#include <stdio.h>

#include "ViewPort.h"
#include "UIManager.h"
#include "graphicObject/IDManager.h"
#include "graphicObject/LayerManager.h"
#include "CommandPackage/CommandManager.h"
#include "GPUsystem/Renderer.h"
class EzDraw
{
public:
	EzDraw(); // need to call init before constructor
	~EzDraw();
	static void init();
	void mouse_callback(double xpos, double ypos);
	void scroll_callback(double xoffset, double yoffset);
	void mouse_button_callback(int button, int action, int mods);
	void run();
private:
	GLFWwindow* _window;
	ViewPort myViewPort;
	// mouse state
	bool is_Lbutton_down = false;
	bool first_mouse = true;
	float last_mouse_x = 0, last_mouse_y = 0;
	// static callback
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	// Manager
	UIManager _UIManager;
	IDManager _IDManager;
	LayerManager _LayerManager;
	CommandManager _CommandManager;
	// renderer
	Renderer _Renderer;
};

