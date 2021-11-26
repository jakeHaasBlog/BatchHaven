#pragma once


class KeyboardState {
public:
	static bool keyIsDown(int key);
	static bool ctrlIsDown();
	static bool leftShiftIsDown();
	static bool rightShiftIsDown();
	static bool leftAltIsDown();
	static bool rightAltIsDown();
	static bool capsLockIsOn();
	static bool numLockIsOn();

	static bool isFullsizeKeyboard();

private:


};