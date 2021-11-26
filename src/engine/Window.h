#pragma once

#include "GL/glew.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>
#include <array>
#include <stack>

#include "engine/Texture.h"
#include "engine/Shader.h"

class Window {
public:
	enum ResolutionMode{
		Static,
		Dynamic,
		DynamicLimited
	};

	// dont call this function
	static void init();
	// dont call this function
	static void update();
	// dont call this function
	static void cleanup();

	static void setTitle(const std::string& title);
	static std::string& getTitle();

	static GLFWwindow* getHandle();

	// The width of the content area of the window in pixels
	static float getWidth();
	// The height of the content area of the window in pixels
	static float getHeight();

	
	//returns the aspect ratio of the framebuffer, pixelsPerCMx / y and PixelsPerInchX / Y are already adjusted for aspect ratio. You probably only want to use this for rendering with NSC coordinates.
	static float getAspectRatio();


	// The number of pixels per centimeter is a rough estimate and likely to be different in the x and y directions
	static float pixelsPerCMx();
	// The number of pixels per centimeter is a rough estimate and likely to be different in the x and y directions
	static float pixelsPerCMy();

	// The number of pixels per inch is a rough estimate and likely to be different in the x and y directions
	static float pixelsPerInchX();
	// The number of pixels per inch is a rough estimate and likely to be different in the x and y directions
	static float pixelsPerInchY();

	// The window is always exactly two normalized screen coordinates wide no matter the size or shape of the window
	static float pixelsPerNSCX();
	// The window is always exactly two normalized screen coordinates tall no matter the size or shape of the window
	static float pixelsPerNSCY();

	// Passed texture can be disposed of
	static void setIcon(Texture& tex);


	static void setFrameBufferResolutionMode(ResolutionMode mode);


private:
	Window();

	static std::string title;
	static GLFWwindow* windowHandle;
	static GLuint framebufferID;

	GLFWimage icon;

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	static float pixPerCMx;
	static float pixPerCMy;
	static void updateResolutionConversions();


};
