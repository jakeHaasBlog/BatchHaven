#include "GamepadState.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

bool GamepadState::gamepadIsConnected(int gamepadID)
{
	return glfwJoystickIsGamepad(gamepadID);
}

bool GamepadState::getXdown(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_X];
	}
	return false;
}

bool GamepadState::getYdown(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_Y];
	}
	return false;
}

bool GamepadState::getBdown(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_B];
	}
	return false;
}

bool GamepadState::getAdown(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_A];
	}
	return false;
}

float GamepadState::getRightTriggerValue(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state)) {
		return state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER];
	}

	return 0.0f;
}

bool GamepadState::getRightBumperDown(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER];
	}
	return false;
}

float GamepadState::getleftTriggerValue(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state)) {
		return state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER];
	}

	return 0.0f;
}

bool GamepadState::getleftBumperDown(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER];
	}
	return false;
}

float GamepadState::getLeftJoystickX(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state)) {
		return state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
	}

	return 0.0f;
}

float GamepadState::getLeftJoystickY(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state)) {
		return state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
	}

	return 0.0f;
}

float GamepadState::getRightJoystickX(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state)) {
		return state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
	}

	return 0.0f;
}

float GamepadState::getRightJoystickY(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state)) {
		return state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
	}

	return 0.0f;
}

bool GamepadState::getDPadLeft(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT];
	}
	return false;
}

bool GamepadState::getDPadRight(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT];
	}
	return false;
}

bool GamepadState::getDPadUp(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP];
	}
	return false;
}

bool GamepadState::getDPadDown(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN];
	}
	return false;
}

bool GamepadState::getSelectIsDown(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_BACK];
	}
	return false;
}

bool GamepadState::getStartIsDown(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_START];
	}
	return false;
}

bool GamepadState::getGuideIsDown(int gamepadID)
{
	GLFWgamepadstate state;
	if (glfwGetGamepadState(gamepadID, &state))
	{
		return state.buttons[GLFW_GAMEPAD_BUTTON_GUIDE];
	}
	return false;
}
