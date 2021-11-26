#include "KeyboardState.h"
#include "Window.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

bool KeyboardState::keyIsDown(int key)
{
	int state = glfwGetKey(Window::getHandle(), key);
	return state == GLFW_PRESS;
}

bool KeyboardState::ctrlIsDown()
{
	return false;
}

bool KeyboardState::leftShiftIsDown()
{
	return false;
}

bool KeyboardState::rightShiftIsDown()
{
	return false;
}

bool KeyboardState::leftAltIsDown()
{
	return false;
}

bool KeyboardState::rightAltIsDown()
{
	return false;
}

bool KeyboardState::capsLockIsOn()
{
	return false;
}

bool KeyboardState::numLockIsOn()
{
	return false;
}

bool KeyboardState::isFullsizeKeyboard()
{
	return false;
}
