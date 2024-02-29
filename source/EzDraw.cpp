#include "EzDraw.h"

EzDraw::EzDraw()
{
	_window = glfwCreateWindow(1820, 980, "EzDraw", NULL, NULL);
	if (_window == NULL) {
		std::cout << "Failed to create window" << std::endl;
	}
	glfwMakeContextCurrent(_window);
	glfwSetWindowUserPointer(_window, this);

	glfwSetCursorPosCallback(_window, mouse_callback);
	glfwSetScrollCallback(_window, scroll_callback);
	glfwSetMouseButtonCallback(_window, mouse_button_callback);
	glfwSwapInterval(1); // Enable vsync
	
	// init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad." << std::endl;
	}

	// setup imgui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsLight();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 430 core");

	// send command manager pointer to uimanager
	_UIManager.setCommandManager(&_CommandManager);
	_UIManager.setIDManager(&_IDManager);
	_UIManager.setLayerManager(&_LayerManager);

	// setup shader
	_Renderer.getShader()->Compile("line.vert", "line.frag");
	_Renderer.init();
}

EzDraw::~EzDraw()
{
	// Cleanup imgui stuff
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// clean up glfw stuff
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void EzDraw::init()
{
	// init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

void EzDraw::mouse_callback(double xpos, double ypos)
{
	ImGuiIO& io = ImGui::GetIO();

	if (!io.WantCaptureMouse)
	{
		if (is_Lbutton_down)
		{
			if (first_mouse)
			{
				last_mouse_x = (float)xpos;
				last_mouse_y = (float)ypos;
				first_mouse = false;
			}
			float deltax = (float)xpos - last_mouse_x;
			float deltay = (float)ypos - last_mouse_y;
			last_mouse_x = (float)xpos;
			last_mouse_y = (float)ypos;
			myViewPort.setProjection((float)deltax * -0.1f, (float)deltay * -0.1f);
		}
	}
}

void EzDraw::scroll_callback(double xoffset, double yoffset)
{
	ImGuiIO& io = ImGui::GetIO();
	if (!io.WantCaptureMouse)
	{
		myViewPort.setMagnifier((float)yoffset * 0.1f);
	}
}

void EzDraw::mouse_button_callback(int button, int action, int mods)
{
	ImGuiIO& io = ImGui::GetIO();
	if (!io.WantCaptureMouse)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (GLFW_PRESS == action)
			{
				is_Lbutton_down = true;
			}
			else if (GLFW_RELEASE == action)
			{
				is_Lbutton_down = false;
				first_mouse = true;
			}

		}
	}
}

void EzDraw::run()
{
	while (!glfwWindowShouldClose(_window)) {
		glfwPollEvents();
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_PassthruCentralNode);  // ENABLE DOCK SPACE

		// render main menu
		_UIManager.render();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(_UIManager.getUIState().clearColor.x, _UIManager.getUIState().clearColor.y, _UIManager.getUIState().clearColor.z, _UIManager.getUIState().clearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render graphic object here
		_Renderer.draw(&_LayerManager, &myViewPort);
		//_Renderer.drawDemo(&myViewPort);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(_window);
	}
}

void EzDraw::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	EzDraw* obj = static_cast<EzDraw*>(glfwGetWindowUserPointer(window));
	obj->mouse_callback(xpos, ypos);
}

void EzDraw::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	EzDraw* obj = static_cast<EzDraw*>(glfwGetWindowUserPointer(window));
	obj->scroll_callback(xoffset,yoffset);
}

void EzDraw::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	EzDraw* obj = static_cast<EzDraw*>(glfwGetWindowUserPointer(window));
	obj->mouse_button_callback(button, action, mods);
}


