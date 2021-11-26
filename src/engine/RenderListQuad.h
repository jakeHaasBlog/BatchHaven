#pragma once

#include "RenderListVertexAttribs.h"

#include "Texture.h"
#include <math.h>

class RenderListQuad {
private: RenderListQuad();
private: RenderListQuad(const RenderListQuad&);
public:
	void setRectangleBounds(float x, float y, float width, float height);

	void setTopLeft(float x, float y);
	void setTopRight(float x, float y);
	void setBottomLeft(float x, float y);
	void setBottomRight(float x, float y);

	void setTopLeftZ(float z);
	void setTopRightZ(float z);
	void setBottomLeftZ(float z);
	void setBottomRightZ(float z);
	void setZ(float z);

	float getTopLeftX();
	float getTopLeftY();

	float getTopRightX();
	float getTopRightY();

	float getBottomLeftX();
	float getBottomLeftY();

	float getBottomRightX();
	float getBottomRightY();

	// set thickness to -1 to fill
	void setOutlineThickness(float thickness);
	float getOutlineThickness();

	// set id to -1 to disable texture
	void setTextureID(int textureID);
	int getTextureID();

	void setColor(float r, float g, float b, float a = 1.0f);
	void setAlpha(float a);
	void setTopLeftColor(float r, float g, float b, float a = 1.0f);
	void setTopRightColor(float r, float g, float b, float a = 1.0f);
	void setBottomLeftColor(float r, float g, float b, float a = 1.0f);
	void setBottomRightColor(float r, float g, float b, float a = 1.0f);

	float getTopLeftR();
	float getTopLeftG();
	float getTopLeftB();
	float getTopLeftAlpha();
	float getTopRightR();
	float getTopRightG();
	float getTopRightB();
	float getTopRightAlpha();
	float getBottomRightR();
	float getBottomRightG();
	float getBottomRightB();
	float getBottomRightAlpha();
	float getBottomLeftR();
	float getBottomLeftG();
	float getBottomLeftB();
	float getBottomLeftAlpha();

	// If targetTex is specified, then sample coordinates are pixels measured from the bottom left of the texture [(0, 0) is bottom left]
	// If targetTex is nullptr, then sample coordinates are given as normalized screen coordinates [(-1, -1) is bottom left]
	void setTextureSampleArea(float x, float y, float width, float height, Texture* targetTex = nullptr);

	void rotateAboutCenter(float radians);
	void rotateAboutPoint(float x, float y, float radians);

	void scaleAboutCenter(float scale);
	void scaleAboutPoint(float x, float y, float scale);

	void translate(float dx, float dy);

	void mirrorAboutLine(float x, float y, float dx, float dy);

	float getCenterX();
	float getCenterY();

	void updateEdgeCoords();

protected:
	RenderListVertexAttribs attribs[4];
};