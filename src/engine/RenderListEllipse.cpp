#include "RenderListEllipse.h"

void RenderListEllipse::setCircleBounds(float x, float y, float radius)
{
    setTopLeft(x - radius, y + radius);
    setTopRight(x + radius, y + radius);
    setBottomLeft(x - radius, y - radius);
    setBottomRight(x + radius, y - radius);
}

void RenderListEllipse::setQuadBounds(float topLeftX, float topLeftY, float topRightX, float topRightY, float bottomLeftX, float bottomLeftY, float bottomRightX, float bottomRightY)
{
    setTopLeft(topLeftX, topLeftY);
    setTopRight(topRightX, topRightY);
    setBottomLeft(bottomLeftX, bottomLeftY);
    setBottomRight(bottomRightX, bottomRightY);
}

void RenderListEllipse::setBoundsAlongLineSeqment(float x1, float y1, float x2, float y2, float girth)
{
    float a[2] = { x1, y1 };
    float b[2] = { x2, y2 };

    float d[2] = { b[0] - a[0], b[1] - a[1] };
    float dLen = sqrt(d[0] * d[0] + d[1] * d[1]);
    d[0] /= dLen;
    d[1] /= dLen;

    float pDir[2] = { -d[1], d[0] };

    // a = 2, 3
    // b = 0, 1
    attribs[2].x = a[0] + (pDir[0] * (girth / 2.0f));
    attribs[2].y = a[1] + (pDir[1] * (girth / 2.0f));
    attribs[3].x = a[0] - (pDir[0] * (girth / 2.0f));
    attribs[3].y = a[1] - (pDir[1] * (girth / 2.0f));

    attribs[0].x = b[0] + (pDir[0] * (girth / 2.0f));
    attribs[0].y = b[1] + (pDir[1] * (girth / 2.0f));
    attribs[1].x = b[0] - (pDir[0] * (girth / 2.0f));
    attribs[1].y = b[1] - (pDir[1] * (girth / 2.0f));
}
