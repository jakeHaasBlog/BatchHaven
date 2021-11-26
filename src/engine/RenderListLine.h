#pragma once

#include "RenderListVertexAttribs.h"
#include <array>




// known bug: CentercoordY does not interpolate smoothly for some reason, this results in the ends of lines with uneven thickness to not be perfect semi-circles, this is only really an issue when extremely thick lines are drawn


class RenderListLine {
private: RenderListLine();
private: RenderListLine(const RenderListLine&);
public:

	void setPosition(float ax, float ay, float bx, float by);
	void setPositionA(float ax, float ay);
	void setPositionB(float bx, float by);

	void setThickness(float t);
	void setThicknessA(float t);
	void setThicknessB(float t);

	void setColor(float r, float g, float b, float a);
	void setColorA(float r, float g, float b, float a);
	void setColorB(float r, float g, float b, float a);

	void setZ(float z);

private:
	void resetEdgeCoords(float lineLength, float thicknessA, float thicknessB);
	void updateVertexPositions(std::array<float, 2> a, std::array<float, 2> b, float thicknessA, float thicknessB);

	void innerSetRealPosA(float x, float y);
	void innerSetRealPosB(float x, float y);
	void getRealPosA(float* x, float* y);
	void getRealPosB(float* x, float* y);

private:
	RenderListVertexAttribs attribs[4];

};