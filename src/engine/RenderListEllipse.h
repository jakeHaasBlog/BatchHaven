#pragma once

#include "RenderListVertexAttribs.h"
#include "RenderListQuad.h"

class RenderListEllipse : public RenderListQuad {
private: RenderListEllipse();
private: RenderListEllipse(const RenderListEllipse&);

public:

	void setCircleBounds(float x, float y, float radius);
	void setQuadBounds(float topLeftX, float topLeftY, float topRightX, float topRightY, float bottomLeftX, float bottomLeftY, float bottomRightX, float bottomRightY);

	// the edge of the ellipse is guarenteed to intersect p1 and p2, the girth is the max width of the ellipse purpendicular to p1 and p2 
	void setBoundsAlongLineSeqment(float x1, float y1, float x2, float y2, float girth);

};