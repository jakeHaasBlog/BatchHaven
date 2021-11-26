#include "RenderListLine.h"

void RenderListLine::setPosition(float ax, float ay, float bx, float by)
{
    float thicknessA = attribs[2].thickness;
    float thicknessB = attribs[0].thickness;
    innerSetRealPosA(ax, ay);
    innerSetRealPosB(bx, by);
    updateVertexPositions({ ax, ay }, { bx, by }, thicknessA, thicknessB);
}

void RenderListLine::setPositionA(float ax, float ay)
{
    float thicknessA = attribs[2].thickness;
    float thicknessB = attribs[0].thickness;
    float bx, by;
    getRealPosB(&bx, &by);
    innerSetRealPosA(ax, ay);
    updateVertexPositions({ ax, ay }, { bx, by }, thicknessA, thicknessB);
}

void RenderListLine::setPositionB(float bx, float by)
{
    float thicknessA = attribs[2].thickness;
    float thicknessB = attribs[0].thickness;
    float ax, ay;
    getRealPosA(&ax, &ay);
    innerSetRealPosB(bx, by);
    updateVertexPositions({ ax, ay }, { bx, by }, thicknessA, thicknessB);
}

void RenderListLine::setThickness(float t)
{
    float thicknessA = t;
    float thicknessB = t;
    for (int i = 0; i < 4; i++) {
        attribs[i].thickness = t;
    }
    float ax, ay;
    float bx, by;
    getRealPosA(&ax, &ay);
    getRealPosB(&bx, &by);
    updateVertexPositions({ ax, ay }, { bx, by }, thicknessA, thicknessB);
}

void RenderListLine::setThicknessA(float t)
{
    float thicknessA = t;
    float thicknessB = attribs[0].thickness;
    float ax, ay;
    float bx, by;
    getRealPosA(&ax, &ay);
    getRealPosB(&bx, &by);
    updateVertexPositions({ ax, ay }, { bx, by }, thicknessA, thicknessB);
}

void RenderListLine::setThicknessB(float t)
{
    float thicknessA = attribs[2].thickness;
    float thicknessB = t;
    float ax, ay;
    float bx, by;
    getRealPosA(&ax, &ay);
    getRealPosB(&bx, &by);
    updateVertexPositions({ ax, ay }, { bx, by }, thicknessA, thicknessB);
}

void RenderListLine::setColor(float r, float g, float b, float a)
{
    for (int i = 0; i < 4; i++) {
        attribs[i].r = r;
        attribs[i].g = g;
        attribs[i].b = b;
        attribs[i].a = a;
    }
}

void RenderListLine::setColorA(float r, float g, float b, float a)
{
    attribs[2].r = r;
    attribs[2].g = g;
    attribs[2].b = b;
    attribs[2].a = a;

    attribs[3].r = r;
    attribs[3].g = g;
    attribs[3].b = b;
    attribs[3].a = a;
}

void RenderListLine::setColorB(float r, float g, float b, float a)
{
    attribs[0].r = r;
    attribs[0].g = g;
    attribs[0].b = b;
    attribs[0].a = a;

    attribs[1].r = r;
    attribs[1].g = g;
    attribs[1].b = b;
    attribs[1].a = a;
}

void RenderListLine::setZ(float z)
{
    for (int i = 0; i < 4; i++) {
        attribs[i].z = z;
    }
}

void RenderListLine::resetEdgeCoords(float lineLength, float thicknessA, float thicknessB)
{
    // a = 2, 3
    // b = 0, 1

    //b = (lineLength/2 + thicknessB/2) / (realLength / 2)

    float realLength = lineLength + (thicknessA / 2) + (thicknessB / 2);
    //float ratioLengthA = (lineLength / 2 + (thicknessA / 2)) / (lineLength / 2);
    //float ratioLengthB = (lineLength / 2 + (thicknessB / 2)) / (lineLength / 2);

    float ratioLengthA = -(lineLength / 2.0f) / (lineLength / 2.0f + thicknessA / 2.0f);
    float ratioLengthB = (lineLength / 2.0f) / (lineLength / 2.0f + thicknessB / 2.0f);

    attribs[2].centerCoordX = -1.0f;
    attribs[3].centerCoordX = -1.0f;
    
    attribs[0].centerCoordX = 1.0f;
    attribs[1].centerCoordX = 1.0f;

    attribs[2].centerCoordY = -1.0f;
    attribs[3].centerCoordY = 1.0f;

    attribs[0].centerCoordY = -1.0f;
    attribs[1].centerCoordY = 1.0f;

    for (int i = 0; i < 4; i++) {
        attribs[i].texX = ratioLengthA;
        attribs[i].texY = ratioLengthB;
    }

}

void RenderListLine::updateVertexPositions(std::array<float, 2> a, std::array<float, 2> b, float thicknessA, float thicknessB)
{
    attribs[2].thickness = thicknessA;
    attribs[0].thickness = thicknessB;

    float d[2] = { b[0] - a[0], b[1] - a[1] };
    float dLen = sqrtf((d[0] * d[0]) + (d[1] * d[1]));
    d[0] /= dLen;
    d[1] /= dLen;


    a[0] -= d[0] * (thicknessA / 2.0f);
    a[1] -= d[1] * (thicknessA / 2.0f);
    b[0] += d[0] * (thicknessB / 2.0f);
    b[1] += d[1] * (thicknessB / 2.0f);


    float pDir[2] = { d[1], -d[0] };

    // a = 2, 3
    // b = 0, 1
    attribs[2].x = a[0] + (pDir[0] * (thicknessA / 2.0f));
    attribs[2].y = a[1] + (pDir[1] * (thicknessA / 2.0f));
    attribs[3].x = a[0] - (pDir[0] * (thicknessA / 2.0f));
    attribs[3].y = a[1] - (pDir[1] * (thicknessA / 2.0f));

    attribs[0].x = b[0] + (pDir[0] * (thicknessB / 2.0f));
    attribs[0].y = b[1] + (pDir[1] * (thicknessB / 2.0f));
    attribs[1].x = b[0] - (pDir[0] * (thicknessB / 2.0f));
    attribs[1].y = b[1] - (pDir[1] * (thicknessB / 2.0f));
    
    resetEdgeCoords(dLen, thicknessA, thicknessB);
}

void RenderListLine::innerSetRealPosA(float x, float y)
{
    attribs[2].textureID = x;
    attribs[3].textureID = y;
}

void RenderListLine::innerSetRealPosB(float x, float y)
{
    attribs[0].textureID = x;
    attribs[1].textureID = y;
}

void RenderListLine::getRealPosA(float* x, float* y)
{
    *x = attribs[2].textureID;
    *y = attribs[3].textureID;
}

void RenderListLine::getRealPosB(float* x, float* y)
{
    *x = attribs[0].textureID;
    *y = attribs[1].textureID;
}
