#pragma once

#include "RenderList.h"

class Ruler {
public:
	Ruler(float x, float y, float lengthInCMs = 30, float widthInCMs = 1, float a = 0.8f, float z = 0.0f);
	void rotate(float rads);
	void setPivot(float x, float y);

	void translate(float x, float y);

	// translates the ruler so that its pivot is on the given point
	void setPosition(float x, float y);

	float getTLx();
	float getTLy();

	float getTRx();
	float getTRy();

	float getBLx();
	float getBLy();

	float getBRx();
	float getBRy();

	void setZ(float z);

	void addToRenderList(RenderList& list);
	void render();

private:
	RenderList rList;
	float pivotX;
	float pivotY;
	float currentRotation = 0.0f;
	int baseRulerID;

	void genNewBaseRuler(float x, float y, float lengthInCMs, float widthInCMs, float a, float z);
};