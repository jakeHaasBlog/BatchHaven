#include "engine/Window.h"
#include <chrono>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

std::string Window::title = "Batch Haven";
GLFWwindow* Window::windowHandle = nullptr;
GLuint Window::framebufferID = -1;

float Window::pixPerCMx = 0.0f;
float Window::pixPerCMy = 0.0f;

void Window::init()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	windowHandle = glfwCreateWindow(1920, 1080, title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(windowHandle);
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(windowHandle, framebuffer_size_callback);
	updateResolutionConversions();

	//glGenBuffers(1, &framebufferID);

}

void Window::update()
{
	

}

void Window::cleanup()
{
	glfwDestroyWindow(windowHandle);
}

void Window::setTitle(const std::string& t)
{
	title = t;
	glfwSetWindowTitle(windowHandle, title.c_str());
}

std::string& Window::getTitle()
{
	return title;
}

GLFWwindow* Window::getHandle()
{
	return windowHandle;
}

float Window::getWidth()
{
	int width;
	glfwGetFramebufferSize(windowHandle, &width, nullptr);
	return width;
}

float Window::getHeight()
{
	int height;
	glfwGetFramebufferSize(windowHandle, nullptr, &height);
	return height;
}

float Window::getAspectRatio()
{
	int width, height;
	glfwGetFramebufferSize(windowHandle, &width, &height);
	return (float)width / height;
}

float Window::pixelsPerCMx()
{
	return pixPerCMx;
}

float Window::pixelsPerCMy()
{
	return pixPerCMy;
}

float Window::pixelsPerInchX()
{
	return pixelsPerCMx() * 2.54f;
}

float Window::pixelsPerInchY()
{
	return pixelsPerCMy() * 2.54f;
}

float Window::pixelsPerNSCX()
{
	return getWidth() / 2;
}

float Window::pixelsPerNSCY()
{
	return getHeight() / 2;
}

void Window::setIcon(Texture& tex)
{
	GLFWimage icon;

	icon.width = tex.getWidth();
	icon.height = tex.getHeight();
	icon.pixels = new unsigned char[icon.width * icon.height * 4];

	auto px = tex.getPixels();

	for (int i = 0; i < icon.width * icon.height; i++) {
		icon.pixels[i * 4 + 0] = px[i][0] * 255.0f;
		icon.pixels[i * 4 + 1] = px[i][1] * 255.0f;
		icon.pixels[i * 4 + 2] = px[i][2] * 255.0f;
		icon.pixels[i * 4 + 3] = px[i][3] * 255.0f;
	}

	glfwSetWindowIcon(windowHandle, 1, &icon);
}


void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);
	updateResolutionConversions();
}

void Window::updateResolutionConversions()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	int widthInScreenCoords = mode->width;
	int heightInScreenCoords = mode->height;

	int width_mm, height_mm;
	glfwGetMonitorPhysicalSize(monitor, &width_mm, &height_mm);

	float screenCoordsXperMM = (float)widthInScreenCoords / (width_mm);
	float screenCoordsYperMM = (float)heightInScreenCoords / (height_mm);

	float screenCoordsXperCM = screenCoordsXperMM * 10;
	float screenCoordsYperCM = screenCoordsYperMM * 10;

	// screen coords to pixels
	int windowScreenCoordsWide, windowScreenCoordsTall;
	glfwGetWindowSize(windowHandle, &windowScreenCoordsWide, &windowScreenCoordsTall);

	int windowPixelsWide, windowPixelsTall;
	glfwGetFramebufferSize(windowHandle, &windowPixelsWide, &windowPixelsTall);

	float ratioSCtoPX_width = (float)windowScreenCoordsWide / windowPixelsWide;
	float ratioSCtoPX_height = (float)windowScreenCoordsTall / windowPixelsTall;

	pixPerCMx = screenCoordsXperCM * ratioSCtoPX_width;
	pixPerCMy = screenCoordsYperCM * ratioSCtoPX_height;
}
