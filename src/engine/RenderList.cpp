#include "RenderList.h"

#include "Window.h"


// maybe remove edge coord and use a geometry shader instaid

std::string RenderList::vertexShaderString =
"#version 330 core\n"
"\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec4 color;\n"
"layout(location = 2) in float thickness;\n"
"layout(location = 3) in float type;\n"
"layout(location = 4) in float texID;\n"
"layout(location = 5) in vec2 uvCoord;\n"
"layout(location = 6) in vec2 centerCoord;\n"
"\n"
"out vec4 v_color;\n"
"out float v_thickness;\n"
"out float v_type;\n"
"out float v_texID;\n"
"out vec2 v_uvCoord;\n"
"out vec2 v_centerCoord;\n"
"\n"
"uniform vec2 u_fbPixelSize;\n"
"\n"
"void main() {\n"
"   gl_Position = vec4((position[0] / u_fbPixelSize[0]) * 2.0f - 1.0f, (position[1] / u_fbPixelSize[1]) * 2.0f - 1.0f, position[2], 1);\n"
"   v_color = color;\n"
"   v_thickness = thickness;\n"
"   v_type = type;\n"
"   v_texID = texID;\n"
"   v_uvCoord = uvCoord;\n"
"   v_centerCoord = centerCoord;\n"
"};\n";

std::string RenderList::fragmentShaderString =
"#version 330 core\n"
"\n"
"layout(location = 0) out vec4 color;\n"
"\n"
"in vec4 v_color;\n"
"in float v_thickness;\n"
"in float v_type;\n"
"in float v_texID;\n"
"in vec2 v_uvCoord;\n"
"in vec2 v_centerCoord;\n"
"\n"
"uniform float u_thicknessMultiplier;\n"
"uniform sampler2D u_textures[15];\n"
"\n"
"void main() {\n"
"   int t = int(v_type);\n"
"   int texID = int(v_texID);\n"
"   if (texID >= 0 && t != 2) color = texture(u_textures[texID], v_uvCoord);\n"
"   else color = v_color;\n"
"   \n"
//  **** Quad ****
"   if (t == 0) {\n"
"       \n"
"       \n"
"       \n"
"   }\n"
//  **** Ellipse ****
"   else if (t == 1) {\n"
"       if (v_centerCoord[0] * v_centerCoord[0] + v_centerCoord[1] * v_centerCoord[1] > 0.5 * 0.5) {\n"
"           discard;\n"
"       }\n"
"   }\n"
//  **** Line ****
"   else if (t == 2) {\n"
"       float lineRatioA = v_uvCoord[0];\n"
"       float lineRatioB = v_uvCoord[1];\n"
"       float currentX = v_centerCoord[0];\n"
"       float dy = v_centerCoord[1];\n"
"       if (currentX < lineRatioA) {\n"
"           float dx = (lineRatioA - currentX) / (1.0f - abs(lineRatioA));\n"
"           if (sqrt((dx * dx) + (dy * dy)) > 1.0f) {\n"
"              discard;\n"
"           }\n"
"       }\n"
"       else if (currentX > lineRatioB) {\n"
"           float dx = abs(lineRatioB - currentX) / abs(1.0f - lineRatioB);\n"
"           if (sqrt((dx * dx) + (dy * dy)) > 1.0f) {\n"
"              discard;\n"
"           }\n"
"       }\n"
//"       color = vec4(dy, dy, dy, 1);" // shows the gradient bug with dy
"       \n"
"   }\n"
"   else {\n"
"       color = vec4(1, 1, 1, 1);\n"
"   }\n"
"};\n";

Shader RenderList::defaultShader = Shader(vertexShaderString, fragmentShaderString);

RenderList::RenderList()
{
    activeShader = &defaultShader;

    char array1[sizeof(RenderListQuad) != sizeof(RenderListVertexAttribs) * 4 ? -1 : 1]; // if this line won't compile, then RenderListQuad is not the right size
    char array2[sizeof(RenderListEllipse) != sizeof(RenderListVertexAttribs) * 4 ? -1 : 1]; // if this line won't compile, then RenderListEllipse is not the right size
    char array3[sizeof(RenderListLine) != sizeof(RenderListVertexAttribs) * 4 ? -1 : 1]; // if this line won't compile, then RenderListLine is not the right size

}

RenderList::RenderList(Shader* customShader)
{
    activeShader = customShader;
}

RenderList::~RenderList()
{
    buffersWereModified = true;
    updateBuffers();

    if (vb) delete vb;
    if (ib) delete ib;
    if (va) delete va;
}

int RenderList::addQuad(float x, float y, float width, float height, float r, float g, float b, float a, float z)
{
    int id = addElement(typeID_quad);
    RenderListQuad* quad = (RenderListQuad*)getElementPointer(id);
    
    quad->setTopLeft(x, y + height);
    quad->setTopRight(x + width, y + height);
    quad->setBottomLeft(x, y);
    quad->setBottomRight(x + width, y);
    quad->setZ(z);

    quad->setColor(r, g, b, a);

    buffersWereModified = true;
    return id;
}

int RenderList::addQuad(float x, float y, float width, float height, int textureSlot, float z)
{
    int id = addElement(typeID_quad);
    RenderListQuad* quad = (RenderListQuad*)getElementPointer(id);

    quad->setTopLeft(x, y + height);
    quad->setTopRight(x + width, y + height);
    quad->setBottomLeft(x, y);
    quad->setBottomRight(x + width, y);
    quad->setZ(z);

    quad->setTextureID(textureSlot);
    quad->setTextureSampleArea(0, 0, textureSlots[textureSlot]->getWidth(), textureSlots[textureSlot]->getHeight(), textureSlots[textureSlot]);

    buffersWereModified = true;
    return id;
}

const std::vector<int>& RenderList::getQuadIDs() const
{
    return elementIDs[typeID_quad];
}

int RenderList::addEllipse(float x, float y, float radius, float r, float g, float b, float a, float z)
{
    int id = addElement(typeID_ellipse);
    RenderListEllipse* ellipse = (RenderListEllipse*)getElementPointer(id);

    ellipse->setCircleBounds(x, y, radius);
    ellipse->setColor(r, g, b, a);
    ellipse->setTextureID(-1);
    ellipse->setZ(z);

    buffersWereModified = true;
    return id;
}

int RenderList::addEllipse(float x, float y, float radius, int textureSlot, float z)
{
    int id = addElement(typeID_ellipse);
    RenderListEllipse* ellipse = (RenderListEllipse*)getElementPointer(id);

    ellipse->setCircleBounds(x, y, radius);
    ellipse->setTextureID(textureSlot);
    ellipse->setTextureSampleArea(0, 0, textureSlots[textureSlot]->getWidth(), textureSlots[textureSlot]->getHeight(), textureSlots[textureSlot]);
    ellipse->setZ(z);

    int index = data.size() - (sizeof(RenderListVertexAttribs) / sizeof(float)) * 4;

    buffersWereModified = true;
    return id;
}

const std::vector<int>& RenderList::getEllipseIDs() const
{
    return elementIDs[typeID_ellipse];
}

int RenderList::addLine(float ax, float ay, float bx, float by, float thickness, float r, float g, float b, float a, float z)
{
    int id = addElement(typeID_line);
    RenderListLine* line = (RenderListLine*)getElementPointer(id);

    line->setThickness(thickness);
    line->setPosition(ax, ay, bx, by);
    line->setColor(r, g, b, a);
    line->setZ(z);

    buffersWereModified = true;
    return id;
}

const std::vector<int>& RenderList::getLineIDs() const
{
    return elementIDs[typeID_line];
}

RenderListLine* RenderList::getLine(int id)
{
    RenderListVertexAttribs* element = getElementPointer(id);
    if (!elementExists(id, typeID_line)) {
        return nullptr;
    }

    return (RenderListLine*)element;
}

int RenderList::getLastLine()
{
    return elementIDs[typeID_line].back();
}

RenderListQuad* RenderList::getQuad(int id)
{
    RenderListVertexAttribs* element = getElementPointer(id);
    if (!elementExists(id, typeID_quad)) {
        return nullptr;
    }
    
    return (RenderListQuad*)element;
}

int RenderList::getLastQuad()
{
    return elementIDs[typeID_quad].back();
}

RenderListEllipse* RenderList::getEllipse(int id)
{
    RenderListVertexAttribs* element = getElementPointer(id);
    if (!elementExists(id, typeID_ellipse)) {
        return nullptr;
    }

    return (RenderListEllipse*)element;
}

int RenderList::getLastEllipse()
{
    return elementIDs[typeID_ellipse].back();
}

void RenderList::updateBuffers()
{
    if (!buffersWereModified) return;
    
    int numAttribsPerVertex = sizeof(RenderListVertexAttribs) / sizeof(float);
    int numQuads = (data.size() / numAttribsPerVertex) / 4;
    std::vector<unsigned int> indices;
    indices.reserve(numQuads * 6);
    int removedQuads = 0;
    for (int i = 0; i < numQuads - removedQuads; i++) {

        // ** removing any quads that are completely off screen **
        indices.push_back(i * 4 + 0);
        indices.push_back(i * 4 + 1);
        indices.push_back(i * 4 + 2);

        indices.push_back(i * 4 + 2);
        indices.push_back(i * 4 + 1);
        indices.push_back(i * 4 + 3);
    }

    if (ib && vb) {
        vb->bufferData(&data[0], data.size() * sizeof(data[0]));
        ib->bufferData(&indices[0], indices.size() * sizeof(unsigned int));

        // should use buffer sub data to update only modified elements
    }
    else {
        ib = new IndexBuffer();
        ib->bufferData(&indices[0], indices.size() * sizeof(unsigned int));

        vb = new VertexBuffer();
        vb->bufferData(&data[0], data.size() * sizeof(data[0]));

        va = new VertexArray();
        va->setAttributes("fff ffff f f f ff ff", *vb, *ib);
    }

    buffersWereModified = false;
}

void RenderList::bindTextures() {
    for (int i = 0; i < textureSlots.size(); i++) {
        if (textureSlots[i]) {
            textureSlots[i]->bind(i);
        }
        else {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    
        defaultShader.setUniform1i("u_textures[" + std::to_string(i) + "]", i);
    }
}

bool RenderList::removeElement(int id)
{
    auto hashFind = idToIndex.find(id);
    if (hashFind == idToIndex.end()) return false;

    int index = (*hashFind).second;

    bool wasRemoved = false;
    RenderListVertexAttribs* attribs = (RenderListVertexAttribs*)&data[index];
    int type = attribs->type;
    for (int i = 0; i < elementIDs[type].size(); i++) {
        if (elementIDs[type][i] == id) {
            elementIDs[type].erase(elementIDs[type].begin() + i);
            wasRemoved = true;
            break;
        }
    }
    if (!wasRemoved) {
        return false;
    }

    data.erase(data.begin() + index, data.begin() + index + (sizeof(RenderListVertexAttribs) / sizeof(float)) * 4);

    for (auto hashItter = idToIndex.begin(); hashItter != idToIndex.end(); hashItter++) {
        if ((*hashItter).second >= index) {
            (*hashItter).second -= (sizeof(RenderListVertexAttribs) / sizeof(float)) * 4;
        }
    }

    buffersWereModified = true;
    return true;
}

int RenderList::duplicateElement(int id)
{
    auto hashFind = idToIndex.find(id);
    if (hashFind == idToIndex.end()) return -1;

    int index = (*hashFind).second;

    RenderListVertexAttribs* attribs = (RenderListVertexAttribs*)&data[index];
    int type = attribs->type;

    for (int i = 0; i < (sizeof(RenderListVertexAttribs) / sizeof(float)) * 4; i++) {
        data.push_back(0.0f);
    }

    RenderListVertexAttribs* dest = (RenderListVertexAttribs*)&data[data.size() - (sizeof(RenderListVertexAttribs) / sizeof(float)) * 4];

    memcpy_s(dest, sizeof(RenderListVertexAttribs) * 4, attribs, sizeof(RenderListVertexAttribs) * 4);

    greatestID++;
    int newId = greatestID;

    idToIndex.insert({ newId, data.size() - (sizeof(RenderListVertexAttribs) / sizeof(float)) * 4 });
    elementIDs[type].push_back(newId);

    buffersWereModified = true;
    return newId;
}

void RenderList::render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Window::getWidth(), Window::getHeight());

    updateBuffers();
    bindTextures();
    
    // set uniforms
    defaultShader.setUniform1f("u_thicknessMultiplier", 1.0f);
    defaultShader.setUniform2f("u_fbPixelSize", Window::getWidth(), Window::getHeight());

    activeShader->bind();
    va->bind();
    glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr);
    va->unbind();
    activeShader->unbind();

}

void RenderList::renderToTexture(Texture* texture)
{
    texture->bindAsRenderTarget();

    updateBuffers();
    bindTextures();

    // set uniforms
    defaultShader.setUniform1f("u_thicknessMultiplier", 1.0f);
    defaultShader.setUniform2f("u_fbPixelSize", texture->getWidth(), texture->getHeight());

    activeShader->bind();
    va->bind();
    glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr);
    va->unbind();
    activeShader->unbind();

    texture->unbindAsRenderTarget();
}

void RenderList::clear()
{
    data.clear();
    idToIndex.clear();
    buffersWereModified = true;
    greatestID = 0;

    for (int i = 0; i < elementIDs.size(); i++) {
        elementIDs[i].clear();
    }
}

void RenderList::addRenderList(RenderList& rList)
{
    for (int i = 0; i < rList.data.size(); i += (sizeof(RenderListVertexAttribs) / sizeof(float)) * 4) {
        for (int j = 0; j < (sizeof(RenderListVertexAttribs) / sizeof(float)) * 4; j++) {
            data.push_back(rList.data[i + j]);
        }
        
        RenderListVertexAttribs* attribs = (RenderListVertexAttribs*)&rList.data[i];
        int type = (int)attribs->type;

        greatestID++;
        elementIDs[type].push_back(greatestID);

        idToIndex[greatestID] = (data.size() - 1) - (sizeof(RenderListVertexAttribs) / sizeof(float)) * 4;
    }

    buffersWereModified = true;
}

void RenderList::setCustomShader(Shader* shader)
{
    activeShader = shader;
}

Shader* RenderList::getActiveShader()
{
    return activeShader;
}

void RenderList::setTextureSlot(int slot, Texture* texture)
{
    textureSlots[slot] = texture;
}

Texture* RenderList::getTextureInSlot(int slot)
{
    return textureSlots[slot];
}

int RenderList::addElement(int type)
{
    for (int i = 0; i < (sizeof(RenderListVertexAttribs) / sizeof(float)) * 4; i++) {
        data.push_back(0.0f);
    }

    int index = data.size() - (sizeof(RenderListVertexAttribs) / sizeof(float)) * 4;

    greatestID++;
    int id = greatestID;
    idToIndex.insert({ id, index });

    elementIDs[type].push_back(id);
    RenderListVertexAttribs* attribs = getElementPointer(id);
    for (int i = 0; i < 4; i++) {
        attribs[i].textureID = -1;
        attribs[i].z = 0.0f;
        attribs[i].type = type;
    }

    buffersWereModified = true;

    return id;
}

RenderListVertexAttribs* RenderList::getElementPointer(int id)
{
    auto hashFind = idToIndex.find(id);
    if (hashFind == idToIndex.end()) {
        return nullptr;
    }

    int index = (*hashFind).second;

    buffersWereModified = true;
    return (RenderListVertexAttribs*)&data[index];
}

bool RenderList::elementExists(int id, int type)
{
    bool validID = false;
    for (int a : elementIDs[type]) {
        if (a == id) validID = true;
    }

    return validID;
}

