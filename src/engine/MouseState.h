#pragma once


class MouseState {
public:
	bool leftMouseDown();
	bool rightMouseDown();
	bool scrollButtonDown();

	float getCursorX();
	float getCursorY();

	bool isHoveringOverWindow();

private:


};