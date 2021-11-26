#include "EventsManager.h"

EventsHandle* EventsManager::activeEventsHandle = nullptr;

void EventsManager::setEventsHandleActive(EventsHandle* eventsHandle)
{
	static bool initialized = false;
	if (!initialized) {
		
		glfwSetKeyCallback(Window::getHandle(), key_callback);
		glfwSetMouseButtonCallback(Window::getHandle(), mouse_button_callback);
		glfwSetScrollCallback(Window::getHandle(), scroll_callback);
		glfwSetCharCallback(Window::getHandle(), character_callback);
		glfwSetCursorPosCallback(Window::getHandle(), cursor_position_callback);

		initialized = true;
	}

	activeEventsHandle = eventsHandle;
}

void EventsManager::setCursorDisabled()
{
	glfwSetInputMode(Window::getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void EventsManager::setCursorHidden()
{
	glfwSetInputMode(Window::getHandle(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void EventsManager::setCursorNormal() {
	glfwSetInputMode(Window::getHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void EventsManager::setMouseMotionRaw(bool isRaw)
{
	if (isRaw) glfwSetInputMode(Window::getHandle(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	else glfwSetInputMode(Window::getHandle(), GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
}

std::string EventsManager::getClipboardString()
{
	return glfwGetClipboardString(NULL);
}

void EventsManager::setClipboardString(const std::string& text)
{
	glfwSetClipboardString(NULL, text.c_str());
}

void EventsManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		activeEventsHandle->onKeyPress(key);
	}
	else if (action == GLFW_RELEASE) {
		activeEventsHandle->onKeyRelease(key);
	}
	else if (action == GLFW_REPEAT) {
		activeEventsHandle->onKeyRepeat(key);
	}
}

void EventsManager::character_callback(GLFWwindow* window, unsigned int codepoint)
{
}

void EventsManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) activeEventsHandle->onLeftMousePress();
		if (button == GLFW_MOUSE_BUTTON_RIGHT) activeEventsHandle->onRightMousePress();
	}
	else if (action == GLFW_RELEASE) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) activeEventsHandle->onLeftMouseRelease();
		if (button == GLFW_MOUSE_BUTTON_RIGHT) activeEventsHandle->onRightMouseRelease();
	}
}

void EventsManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	activeEventsHandle->onMouseScrollHorizonatal((float)xoffset);
	activeEventsHandle->onMouseScrollVertical((float)yoffset);
}

void EventsManager::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	static float preX = (float)xpos;
	static float preY = (float)ypos;
	activeEventsHandle->onMouseMove((float)xpos - preX, (float)ypos - preY);
	preX = (float)xpos;
	preY = (float)ypos;
}

void EventsManager::joystick_callback(int jid, int event)
{
	if (event == GLFW_CONNECTED)
	{
		activeEventsHandle->onControllerConnected(jid);
	}
	else if (event == GLFW_DISCONNECTED)
	{
		activeEventsHandle->onControllerDisconnected(jid);
	}
}
