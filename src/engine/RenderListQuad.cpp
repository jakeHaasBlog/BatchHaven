#include "RenderListQuad.h"


void RenderListQuad::setRectangleBounds(float x, float y, float width, float height)
{
    setBottomLeft(x, y);
    setBottomRight(x + width, y);
    setTopLeft(x, y + height);
    setTopRight(x + width, y + height);
}

void RenderListQuad::setTopLeft(float x, float y)
{
    attribs[0].x = x;
    attribs[0].y = y;

    updateEdgeCoords();
}

void RenderListQuad::setTopRight(float x, float y)
{
    attribs[1].x = x;
    attribs[1].y = y;

    updateEdgeCoords();
}

void RenderListQuad::setBottomLeft(float x, float y)
{
    attribs[2].x = x;
    attribs[2].y = y;

    updateEdgeCoords();
}

void RenderListQuad::setBottomRight(float x, float y)
{
    attribs[3].x = x;
    attribs[3].y = y;

    updateEdgeCoords();
}

void RenderListQuad::setTopLeftZ(float z)
{
    attribs[0].z = z;
}

void RenderListQuad::setTopRightZ(float z)
{
    attribs[1].z = z;
}

void RenderListQuad::setBottomLeftZ(float z)
{
    attribs[2].z = z;
}

void RenderListQuad::setBottomRightZ(float z)
{
    attribs[3].z = z;
}

void RenderListQuad::setZ(float z)
{
    for (int i = 0; i < 4; i++) {
        attribs[i].z = z;
    }
}

float RenderListQuad::getTopLeftX()
{
    return attribs[0].x;
}

float RenderListQuad::getTopLeftY()
{
    return attribs[0].y;
}

float RenderListQuad::getTopRightX()
{
    return attribs[1].x;
}

float RenderListQuad::getTopRightY()
{
    return attribs[1].y;
}

float RenderListQuad::getBottomLeftX()
{
    return attribs[2].x;
}

float RenderListQuad::getBottomLeftY()
{
    return attribs[2].y;
}

float RenderListQuad::getBottomRightX()
{
    return attribs[3].x;
}

float RenderListQuad::getBottomRightY()
{
    return attribs[3].y;
}

void RenderListQuad::setOutlineThickness(float thickness)
{
    for (int i = 0; i < 4; i++) {
        attribs[i].thickness = thickness;
    }
}

float RenderListQuad::getOutlineThickness()
{
    return attribs[0].thickness;
}

void RenderListQuad::setTextureID(int textureID)
{
    for (int i = 0; i < 4; i++) attribs[i].textureID = textureID;
}

int RenderListQuad::getTextureID()
{
    return (int)attribs[0].textureID;
}

void RenderListQuad::setColor(float r, float g, float b, float a)
{
    for (int i = 0; i < 4; i++) {
        attribs[i].r = r;
        attribs[i].g = g;
        attribs[i].b = b;
        attribs[i].a = a;
    }
}

void RenderListQuad::setAlpha(float a)
{
    for (int i = 0; i < 4; i++) {
        attribs[i].a = a;
    }
}

void RenderListQuad::setTopLeftColor(float r, float g, float b, float a)
{
    attribs[0].r = r;
    attribs[0].g = g;
    attribs[0].b = b;
    attribs[0].a = a;
}

void RenderListQuad::setTopRightColor(float r, float g, float b, float a)
{
    attribs[1].r = r;
    attribs[1].g = g;
    attribs[1].b = b;
    attribs[1].a = a;
}

void RenderListQuad::setBottomLeftColor(float r, float g, float b, float a)
{
    attribs[2].r = r;
    attribs[2].g = g;
    attribs[2].b = b;
    attribs[2].a = a;
}

void RenderListQuad::setBottomRightColor(float r, float g, float b, float a)
{
    attribs[3].r = r;
    attribs[3].g = g;
    attribs[3].b = b;
    attribs[3].a = a;
}

float RenderListQuad::getTopLeftR()
{
    return attribs[0].r;
}

float RenderListQuad::getTopLeftG()
{
    return attribs[0].g;
}

float RenderListQuad::getTopLeftB()
{
    return attribs[0].b;
}

float RenderListQuad::getTopLeftAlpha()
{
    return attribs[0].a;
}

float RenderListQuad::getTopRightR()
{
    return attribs[1].r;
}

float RenderListQuad::getTopRightG()
{
    return attribs[1].g;
}

float RenderListQuad::getTopRightB()
{
    return attribs[1].b;
}

float RenderListQuad::getTopRightAlpha()
{
    return attribs[1].a;
}

float RenderListQuad::getBottomRightR()
{
    return attribs[3].r;
}

float RenderListQuad::getBottomRightG()
{
    return attribs[3].g;
}

float RenderListQuad::getBottomRightB()
{
    return attribs[3].b;
}

float RenderListQuad::getBottomRightAlpha()
{
    return attribs[3].a;
}

float RenderListQuad::getBottomLeftR()
{
    return attribs[2].r;
}

float RenderListQuad::getBottomLeftG()
{
    return attribs[2].g;
}

float RenderListQuad::getBottomLeftB()
{
    return attribs[2].b;
}

float RenderListQuad::getBottomLeftAlpha()
{
    return attribs[2].a;
}



void RenderListQuad::setTextureSampleArea(float x, float y, float width, float height, Texture* targetTex)
{

    if (targetTex) {
        attribs[0].texX = x / targetTex->getWidth();
        attribs[0].texY = y / targetTex->getHeight();

        attribs[1].texX = (x + width) / targetTex->getWidth();
        attribs[1].texY = y / targetTex->getHeight();

        attribs[2].texX = x / targetTex->getWidth();
        attribs[2].texY = (y + height) / targetTex->getHeight();

        attribs[3].texX = (x + width) / targetTex->getWidth();
        attribs[3].texY = (y + height) / targetTex->getHeight();
    }
    else {

        attribs[0].texX = (x + 1) / 2;
        attribs[0].texY = (y + 1) / 2;

        attribs[1].texX = (x + 1) / 2 + width / 2;
        attribs[1].texY = (y + 1) / 2;

        attribs[2].texX = (x + 1) / 2;
        attribs[2].texY = (y + 1) / 2 + height / 2;

        attribs[3].texX = (x + 1) / 2 + width / 2;
        attribs[3].texY = (y + 1) / 2 + height / 2;
    }

}

void RenderListQuad::rotateAboutCenter(float radians)
{

    float rotateAboutOriginMat2x2_0 = cosf(radians);
    float rotateAboutOriginMat2x2_1 = -sinf(radians);
    float rotateAboutOriginMat2x2_2 = -rotateAboutOriginMat2x2_1;
    float rotateAboutOriginMat2x2_3 = rotateAboutOriginMat2x2_0;

    float cx = 0.0f;
    float cy = 0.0f;

    for (int i = 0; i < 4; i++) {
        cx += attribs[i].x;
        cy += attribs[i].y;
    }

    cx /= 4;
    cy /= 4;

    for (int i = 0; i < 4; i++) {
        attribs[i].x -= cx;
        attribs[i].y -= cy;
    }

    for (int i = 0; i < 4; i++) {
        float x = attribs[i].x;
        float y = attribs[i].y;

        attribs[i].x = rotateAboutOriginMat2x2_0 * x + rotateAboutOriginMat2x2_1 * y;
        attribs[i].y = rotateAboutOriginMat2x2_2 * x + rotateAboutOriginMat2x2_3 * y;
    }

    for (int i = 0; i < 4; i++) {
        attribs[i].x += cx;
        attribs[i].y += cy;
    }


    updateEdgeCoords();
}

void RenderListQuad::rotateAboutPoint(float x, float y, float radians)
{
    float rotateAboutOriginMat2x2_0 = cosf(radians);
    float rotateAboutOriginMat2x2_1 = -sinf(radians);
    float rotateAboutOriginMat2x2_2 = -rotateAboutOriginMat2x2_1;
    float rotateAboutOriginMat2x2_3 = rotateAboutOriginMat2x2_0;

    float cx = x;
    float cy = y;

    for (int i = 0; i < 4; i++) {
        attribs[i].x -= cx;
        attribs[i].y -= cy;
    }

    for (int i = 0; i < 4; i++) {
        float x = attribs[i].x;
        float y = attribs[i].y;

        attribs[i].x = rotateAboutOriginMat2x2_0 * x + rotateAboutOriginMat2x2_1 * y;
        attribs[i].y = rotateAboutOriginMat2x2_2 * x + rotateAboutOriginMat2x2_3 * y;
    }

    for (int i = 0; i < 4; i++) {
        attribs[i].x += cx;
        attribs[i].y += cy;
    }

    updateEdgeCoords();
}

void RenderListQuad::scaleAboutCenter(float scale)
{
    float cx = 0.0f;
    float cy = 0.0f;

    for (int i = 0; i < 4; i++) {
        cx += attribs[i].x;
        cy += attribs[i].y;
    }

    cx /= 4;
    cy /= 4;

    for (int i = 0; i < 4; i++) {
        float dx = attribs[i].x - cx;
        float dy = attribs[i].y - cy;

        attribs[i].x = cx + dx * scale;
        attribs[i].y = cy + dy * scale;
    }

    updateEdgeCoords();
}

void RenderListQuad::scaleAboutPoint(float x, float y, float scale)
{

    for (int i = 0; i < 4; i++) {
        float dx = attribs[i].x - x;
        float dy = attribs[i].y - y;

        attribs[i].x = x + dx * scale;
        attribs[i].y = y + dy * scale;
    }

    updateEdgeCoords();
}

void RenderListQuad::translate(float dx, float dy)
{
    for (int i = 0; i < 4; i++) {
        attribs[i].x += dx;
        attribs[i].y += dy;
    }

    updateEdgeCoords();
}

void RenderListQuad::mirrorAboutLine(float x, float y, float dx, float dy)
{

    auto mirrorPoint = [](float& pointX, float& pointY, float x, float y, float dx, float dy) {

        float a = (dx * dx - dy * dy) / (dx * dx + dy * dy);
        float b = 2 * dx * dy / (dx * dx + dy * dy);

        float x2 = a * (pointX - x) + b * (pointY - y) + x;
        float y2 = b * (pointX - x) - a * (pointY - y) + y;

        pointX = x2;
        pointY = y2;
    };

    for (int i = 0; i < 4; i++) {
        mirrorPoint(attribs[i].x, attribs[i].y, x, y, dx, dy);
    }

    updateEdgeCoords();
}

float RenderListQuad::getCenterX()
{
    float totalX = 0.0f;

    for (int i = 0; i < 4; i++) {
        totalX += attribs[i].x;
    }

    return totalX / 4.0f;
}

float RenderListQuad::getCenterY()
{
    float totalY = 0.0f;

    for (int i = 0; i < 4; i++) {
        totalY += attribs[i].y;
    }

    return totalY / 4.0f;
}

void RenderListQuad::updateEdgeCoords()
{
    attribs[0].centerCoordX = -0.5;
    attribs[0].centerCoordY = 0.5;

    attribs[1].centerCoordX = 0.5;
    attribs[1].centerCoordY = 0.5;

    attribs[2].centerCoordX = -0.5;
    attribs[2].centerCoordY = -0.5;

    attribs[3].centerCoordX = 0.5;
    attribs[3].centerCoordY = -0.5;

}
