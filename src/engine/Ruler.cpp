#include "Ruler.h"

#include "Window.h"

Ruler::Ruler(float x, float y, float lengthInCMs, float widthInCMs, float a, float z)
{
	pivotX = x;
	pivotY = y;

	currentRotation = 0.0f;
	genNewBaseRuler(x, y, lengthInCMs, widthInCMs, a, z);
}

void Ruler::rotate(float rads)
{
	for (int id : rList.getQuadIDs()) {
		rList.getQuad(id)->rotateAboutPoint(pivotX, pivotY, rads);
	}
}

void Ruler::setPivot(float x, float y)
{
	pivotX = x;
	pivotY = y;
}

void Ruler::translate(float x, float y)
{
	pivotX += x;
	pivotY += y;

	for (int id : rList.getQuadIDs()) {
		rList.getQuad(id)->translate(x, y);
	}
}

void Ruler::setPosition(float x, float y)
{
	translate(x - pivotX, y - pivotY);
}

float Ruler::getTLx()
{
	return rList.getQuad(baseRulerID)->getTopLeftX();
}

float Ruler::getTLy()
{
	return rList.getQuad(baseRulerID)->getTopLeftY();
}

float Ruler::getTRx()
{
	return rList.getQuad(baseRulerID)->getTopRightX();
}

float Ruler::getTRy()
{
	return rList.getQuad(baseRulerID)->getTopRightY();
}

float Ruler::getBLx()
{
	return rList.getQuad(baseRulerID)->getBottomLeftX();
}

float Ruler::getBLy()
{
	return rList.getQuad(baseRulerID)->getBottomLeftY();
}

float Ruler::getBRx()
{
	return rList.getQuad(baseRulerID)->getBottomRightX();
}

float Ruler::getBRy()
{
	return rList.getQuad(baseRulerID)->getBottomRightY();
}

void Ruler::setZ(float z)
{
	for (int id : rList.getQuadIDs()) {
		rList.getQuad(id)->setZ(z);
	}
}

void Ruler::addToRenderList(RenderList& list)
{
	list.addRenderList(rList);
}

void Ruler::render()
{
	rList.render();
}

void Ruler::genNewBaseRuler(float x1, float y1, float lengthInCMs, float widthInCMs, float a, float z)
{
	rList.clear();

	// ruler
	int baseRuler = rList.addQuad(x1, y1, Window::pixelsPerCMx() * lengthInCMs, Window::pixelsPerCMy() * widthInCMs, 0, 0, 1, a, z);
	int rulerBody = baseRuler;

	float rulerX = x1;
	float rulerY = y1;
	float rulerWidth = rList.getQuad(rulerBody)->getBottomRightX() - rList.getQuad(rulerBody)->getBottomLeftX();
	float rulerHeight = rList.getQuad(rulerBody)->getTopLeftY() - rList.getQuad(rulerBody)->getBottomLeftY();

	rList.getQuad(rulerBody)->setTopLeft(rulerX, rulerY + rulerHeight);
	rList.getQuad(rulerBody)->setTopRight(rulerX + rulerWidth, rulerY + rulerHeight);
	rList.getQuad(rulerBody)->setBottomLeft(rulerX, rulerY);
	rList.getQuad(rulerBody)->setBottomRight(rulerX + rulerWidth, rulerY);

	// cm marks
	for (float x = 0; x < rulerWidth + Window::pixelsPerCMx() / 2; x += Window::pixelsPerCMx()) {
		rList.addQuad(rulerX + x - 2, rulerY, 4, rulerHeight / 5, 1, 1, 1);
	}

	// mm marks
	for (float x = 0; x < rulerWidth; x += Window::pixelsPerCMx() / 10) {
		rList.addQuad(rulerX + x, rulerY, 1, rulerHeight / 10, 1, 1, 1);
	}

	// inch marks
	for (float x = 0; x < rulerWidth; x += Window::pixelsPerInchX()) {
		rList.addQuad(rulerX + x - 2, rulerY + rulerHeight - rulerHeight / 2, 4, rulerHeight / 2, 1, 1, 1);
	}

	// 1/2 inch marks
	for (float x = 0; x < rulerWidth; x += Window::pixelsPerInchX() / 2) {
		rList.addQuad(rulerX + x - 2, rulerY + rulerHeight - rulerHeight / 3, 4, rulerHeight / 3, 1, 1, 1);
	}

	// 1/4 inch marks
	for (float x = 0; x < rulerWidth; x += Window::pixelsPerInchX() / 4) {
		rList.addQuad(rulerX + x - 2, rulerY + rulerHeight - rulerHeight / 4, 4, rulerHeight / 4, 1, 1, 1);
	}

	// 1/8 inch marks
	for (float x = 0; x < rulerWidth; x += Window::pixelsPerInchX() / 8) {
		rList.addQuad(rulerX + x - 1.5f, rulerY + rulerHeight - rulerHeight / 5, 3, rulerHeight / 5, 1, 1, 1);
	}

	// 1/16 inch marks
	for (float x = 0; x < rulerWidth; x += Window::pixelsPerInchX() / 16) {
		rList.addQuad(rulerX + x, rulerY + rulerHeight - rulerHeight / 8, 1, rulerHeight / 8, 1, 1, 1);
	}


	rList.getQuad(rulerBody)->setBottomLeftColor(0.3, 0, 0.3);
	rList.getQuad(rulerBody)->setBottomRightColor(0.3, 0, 0.3);
	rList.getQuad(rulerBody)->setTopLeftColor(0, 0.3, 0);
	rList.getQuad(rulerBody)->setTopRightColor(0, 0.3, 0);
}
