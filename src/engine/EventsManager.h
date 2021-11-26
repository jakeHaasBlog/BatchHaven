#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Window.h"
#include "EventsHandle.h"

#include <string>

class EventsManager {
public:
	static void setEventsHandleActive(EventsHandle* eventsHandle);

	static void setCursorDisabled();
	static void setCursorHidden();
	static void setCursorNormal();

	/* removes mouse acceleration and sensitivity from mouse movement 
	** ONLY WORKS WHILE CURSOR IS DISABLED **
	*/
	static void setMouseMotionRaw(bool isRaw);

	static std::string getClipboardString();
	static void setClipboardString(const std::string& text);

private:
	static EventsHandle* activeEventsHandle;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void character_callback(GLFWwindow* window, unsigned int codepoint);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void joystick_callback(int jid, int event);


};