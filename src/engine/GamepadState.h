#pragma once


// gamepad states are based on an xbox one controller but will work for other gamepads as well
class GamepadState {
public:
	static bool gamepadIsConnected(int gamepadID = 0);

	static bool getXdown(int gamepadID = 0);
	static bool getYdown(int gamepadID = 0);
	static bool getBdown(int gamepadID = 0);
	static bool getAdown(int gamepadID = 0);

	// from 0.0(not pressed) to 1.0(maximum press distance)
	static float getRightTriggerValue(int gamepadID = 0);
	static bool getRightBumperDown(int gamepadID = 0);

	// from 0.0(not pressed) to 1.0(maximum press distance)
	static float getleftTriggerValue(int gamepadID = 0);
	static bool getleftBumperDown(int gamepadID = 0);

	// from -1.0(all the way left) to 1.0(all the way right)
	static float getLeftJoystickX(int gamepadID = 0);

	// from -1.0(all the way down) to 1.0(all the way up)
	static float getLeftJoystickY(int gamepadID = 0);


	// from -1.0(all the way left) to 1.0(all the way right)
	static float getRightJoystickX(int gamepadID = 0);

	// from -1.0(all the way down) to 1.0(all the way up)
	static float getRightJoystickY(int gamepadID = 0);

	static bool getDPadLeft(int gamepadID = 0);
	static bool getDPadRight(int gamepadID = 0);
	static bool getDPadUp(int gamepadID = 0);
	static bool getDPadDown(int gamepadID = 0);

	static bool getSelectIsDown(int gamepadID = 0);
	static bool getStartIsDown(int gamepadID = 0);
	static bool getGuideIsDown(int gamepadID = 0);

private:


};