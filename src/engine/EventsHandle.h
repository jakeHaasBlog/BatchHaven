#pragma once

#include <string>

class EventsHandle {
public:

	// when the mouse is moved, the difference in position will be given. Can query the current mouse position through the MouseState static class
	virtual void onMouseMove(float deltaX, float deltaY) {};
	
	// will be called when the left mouse button is pressed
	virtual void onLeftMousePress() {};
	// will be called when the left mouse button is released
	virtual void onLeftMouseRelease() {};

	// will be called when the right mouse button is pressed
	virtual void onRightMousePress() {};
	// will be called when the left mouse button is released
	virtual void onRightMouseRelease() {};

	// will be called as the mouse is scrolling vertically, the increments of movement will be given. (normal scroll speed is around +-1.0f)
	virtual void onMouseScrollVertical(float deltaY) {};

	// will be called as the mouse is scrolling horizontally, the increments of movement will be given. (normal scroll speed is around +-1.0f)
	virtual void onMouseScrollHorizonatal(float deltaX) {};

	// will be called when a key is pressed, the key given can be compared using GLFW_KEY_?
	virtual void onKeyPress(int key) {};

	// will be called when a key is pressed, the key given can be compared using GLFW_KEY_?
	virtual void onKeyRelease(int key) {};

	// will be called when a key has been held down for a short amount of time. This most often occurs when typing. the key given can be compared using GLFW_KEY_?
	virtual void onKeyRepeat(int key) {};

	// will be called when a controller or joystick is connected, its ID will be given
	virtual void onControllerConnected(int controllerID) {};

	// will be called when a controller or joystick is disconnected, its ID will be given
	virtual void onControllerDisconnected(int controllerID) {};

	// will be called when a file is dragged and dropped onto the window, its filepath will be given
	virtual void onFileDropped(const std::string& filepath) {};

};
