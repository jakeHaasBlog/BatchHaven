#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <vector>
#include <array>
#include <unordered_map>
#include <list>

#include "Shader.h"
#include "Texture.h"
#include "OpenglBufferObjects.h"

#include "RenderListVertexAttribs.h"

#include "RenderListQuad.h"
#include "RenderListEllipse.h"
#include "RenderListLine.h"

// RenderList is the primary rendering class to be used in Batch Haven. Elements of many types are added to a RenderList during an update, then rendered simultainously when the render function is called.
// * this class does not free any pointers passed to it
// * make sure texture slots are set before adding textured elements
// * common practice with this class is to have a persisting RenderList instance, then clear and re-add all desired elements each time render is called, or each time the screen resizes.
// * note that each time any element is modified it requires all elements to be rebuffered before rendering. This means that modifying, adding, or removing any individual element is equally as costly as modifying every element.
// * it is faster to render as many things as possible at the same time rather than inividually rendering items in their own lists
// * it is a good idea to make a seperate list for static elements and only update it when the screen resizes
class RenderList {
public:
	RenderList();

	// Setting a custom shader is generally not advisable because the shader is quite large and complex but can be done.
	// You can see the default shader strings RenderList::vertexShaderString and RenderList::fragmentShaderString in src/engine/RenderList.cpp
	RenderList(Shader* customShader);
	~RenderList();

	int addQuad(float x, float y, float width, float height, float r, float g, float b, float a = 1.0f, float z = 0.0f);
	int addQuad(float x, float y, float width, float height, int textureSlot, float z = 0.0f);
	const std::vector<int>& getQuadIDs() const;
	RenderListQuad* getQuad(int id);
	int getLastQuad();

	int addEllipse(float x, float y, float radius, float r, float g, float b, float a = 1.0f, float z = 0.0f);
	int addEllipse(float x, float y, float radius, int textureSlot, float z = 0.0f);
	const std::vector<int>& getEllipseIDs() const;
	RenderListEllipse* getEllipse(int id);
	int getLastEllipse();

	int addLine(float ax, float ay, float bx, float by, float thickness, float r, float g, float b, float a = 1.0f, float z = 0.0f);
	const std::vector<int>& getLineIDs() const;
	RenderListLine* getLine(int id);
	int getLastLine();

	bool removeElement(int id);
	int duplicateElement(int id);

	// will render onto the Window's framebuffer
	void render();

	void renderToTexture(Texture* texture);

	// removes all elemments from the list
	void clear();

	// adds the elements of another RenderList to this one
	void addRenderList(RenderList& rList);

	// setting the custom shader to nullptr will bind the default shader
	void setCustomShader(Shader* shader);
	Shader* getActiveShader();

	void setTextureSlot(int slot, Texture* texture);
	Texture* getTextureInSlot(int slot);

private:
	int addElement(int type);
	RenderListVertexAttribs* getElementPointer(int id);
	bool elementExists(int id, int type);

private:
	std::vector<float> data;
	std::unordered_map<int, int> idToIndex;

	static const int typeID_quad = 0;
	static const int typeID_ellipse = 1;
	static const int typeID_line = 2;

	std::array<std::vector<int>, 3> elementIDs;

	int greatestID = 0;
	
	static std::string vertexShaderString;
	static std::string fragmentShaderString;
	static Shader defaultShader;
	Shader* activeShader;

	VertexBuffer* vb = nullptr;
	IndexBuffer* ib = nullptr;
	VertexArray* va = nullptr;

	bool buffersWereModified = true;
	void updateBuffers();

	void bindTextures();
	std::array<Texture*, 16> textureSlots;

};

