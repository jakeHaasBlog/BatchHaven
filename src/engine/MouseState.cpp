#include "MouseState.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Window.h"

float MouseState::getCursorX()
{
	double xpos;
	glfwGetCursorPos(Window::getHandle(), &xpos, nullptr);
	return (float)xpos;
}

float MouseState::getCursorY()
{
	double ypos;
	glfwGetCursorPos(Window::getHandle(), &ypos, nullptr);
	return (float)ypos;
}
