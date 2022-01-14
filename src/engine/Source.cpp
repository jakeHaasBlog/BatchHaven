
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "engine/Window.h"
#include <stdio.h>
#include <iostream>
#include <ios>
#include <chrono>

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

#include "EventsHandle.h"
#include "EventsManager.h"

#include "SoundData.h"
#include "SoundManager.h"

#include "RenderList.h"
#include "FrameRateTimer.h"
#include "Ruler.h"

#include "Geometry.h"

float v = 1.0f;
SoundData* soundEffect = nullptr;

FrameRateTimer timer;

class MyEvents : public EventsHandle {
public:

	void onKeyPress(int key) override {
		if (key == GLFW_KEY_Q) {
			v -= 0.05f;
		}
		if (key == GLFW_KEY_W) {
			v += 0.05f;
		}
	}

	void onLeftMousePress() override {
		SoundManager::playAudio(soundEffect, 0.1f, 1.0f);
	}

	void onRightMousePress() override {

	}

};


int main(int argc, char** argv) {
	SoundManager::__init();

	if (!glfwInit()) printf("GLFW did not initialize properly\n");
	Window::init();
	if (glewInit() != GLEW_OK) printf("GLEW did not initialize properly\n");

	MyEvents myHandle;
	EventsManager::setEventsHandleActive(&myHandle);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	Texture icon("assets/icon.png");
	Window::setIcon(icon);

	// testing audio
	//SoundData mySound("assets/SoloDance.wav");
	//SoundData mySound("assets/test.wav");
	//SoundManager::playAudio(&mySound, 0.2f, 1.0f);

	soundEffect = new SoundData("assets/popSounds.wav", 48.8, 50.3);
	//soundEffect = new SoundData("assets/SoloDance.wav");

	soundEffect->saveToFile("assets/doorOpening.wav");


	Texture myTex = Texture("assets/test.png");

	RenderList myList;
	myList.setTextureSlot(3, &myTex);

	Ruler rul = Ruler(30, 50);

	Texture renderTexture = Texture(1000, 1000);
	std::vector<std::array<float, 4>> pix = renderTexture.getPixels();
	for (int i = 0; i < pix.size(); i++) {
		pix[i] = { (float)i / pix.size(), 1, 1, 1 };
	}
	renderTexture.generateFromData(1000, 1000, &pix[0][0]);

	RenderList trl;
	{
		float x = 500, y = 500, r = 44000;
		trl.addEllipse(500, 500, 500, 1, 0, 0, 1);
		for (int i = 0; i < 10; i++) {
			trl.addEllipse(x, y, r, i / 10, i / 5, 1.0f - i / 10.0f, 1);
			x += (((float)rand() / RAND_MAX) * 2.0f - 1.0f) * 40;
			y += (((float)rand() / RAND_MAX) * 2.0f - 1.0f) * 40;
			r -= 40.0f;
		}
	}

	trl.renderToTexture(&renderTexture);


	glfwSwapInterval(1);
	int x = 0;
	while (!glfwWindowShouldClose(Window::getHandle())) {

		glfwSwapBuffers(Window::getHandle());
		timer.updatePerFrameBegin();
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		Window::update();

		myList.clear();
		
		float circleRad = 100;
		int circleItter = 0;
		for (float x = 0; x < Window::getWidth(); x += circleRad) {
			for (float y = Window::getHeight(); y > -circleRad; y -= circleRad) {
				float r = sinf(circleItter);
				float g = cosf(circleItter);
				float b = 1.0f - r;
				//int c = myList.addEllipse(x, y, circleRad, r / 5, g / 5, b / 5);
				//if (circleItter % 5 == 0) {
				//	myList.getEllipse(c)->setZ(0.4f);
				//}
				circleItter++;
			}
		}
		
		for (float x = 0; x < Window::getWidth(); x += circleRad) {
			for (float y = Window::getHeight(); y > -circleRad; y -= circleRad) {
				float g = cosf(circleItter);
				float r = 1.0f - g;
				float b = sinf(circleItter);
				//int c = myList.addEllipse(x, y, circleRad, r / 5, g / 5, b / 5, 0.3f);
				//if (circleItter % 2 == 0) {
				//	myList.getEllipse(c)->setZ(0.4f);
				//}
				circleItter++;
			}
		}

		float lx = Window::getWidth() / 2;
		float ly = Window::getHeight() / 2;
		float lr = 0.0f, lg = 0.0f, lb = 0.0f;
		float lWidth = 5;
		srand(120);
		for (int i = 0; i < 500; i++) {
			int lin = myList.addLine(lx, ly, 0, 0, lWidth, lr, lg, lb);
			lx += cosf(rand()) * 100;
			ly += sinf(rand()) * 100;
			lr = (float)rand() / RAND_MAX;
			lg = (float)rand() / RAND_MAX;
			lb = 1.0f - lr;
			lWidth = ((float)rand() / RAND_MAX) * 10 + 1;
			myList.getLine(lin)->setPositionB(lx, ly);
			myList.getLine(lin)->setColorB(lr, lg, lb, 1.0f);
			myList.getLine(lin)->setThicknessB(lWidth);
		}
		
		// corners
		myList.addQuad(Window::getWidth() / 2 - 25, Window::getHeight() / 2 - 25, 50, 50, 1.0f, 0.0f, 0.0f);
		myList.addQuad(0, 0, 50, 50, 1, 0, 0);
		int id = myList.addQuad(Window::getWidth() - 50, 0, 50, 50, 1, 0, 0);
		myList.addQuad(Window::getWidth() - 50, Window::getHeight() - 50, 50, 50, 1, 0, 0);
		myList.addQuad(0, Window::getHeight() - 50, 50, 50, 1, 0, 0);
		
		
		static float rads = 0.0f;
		rads += timer.getDeltaSeconds();
		
		myList.addEllipse(0, 0, 0, 1, 0, 0);
		myList.getEllipse(myList.getLastEllipse())->setBoundsAlongLineSeqment(100, 300, 1000, 600, 200);
		
		myList.setTextureSlot(0, &myTex);
		myList.addEllipse(500, 500, 100, 0);
		myList.getEllipse(myList.getLastEllipse())->rotateAboutCenter(rads * 5);
		
		
		float fx = 1300;
		float fy = 800;
		float rad = 200;
		int n = 50;
		float da = (3.14159f * 2.0f) / n;
		float t = 5;
		float r, g, b;
		for (int i = 0; i < n; i++) {
			r = sinf(i);
			g = cosf(i);
			b = 1 - r;
			int lineI = myList.addLine(fx, fy, fx + cosf(i * da) * rad, fy + sinf(i * da) * rad, t, r, g, b);
			myList.getLine(lineI)->setColorA(1, 1, 1, 0.3);
		}
		
		myList.addLine(fx, fy, fx + cosf(rads * 0.5f) * 300, fy + sinf(rads * 0.5f) * 300, 50, 0.4, 1, 0.4);
		myList.getLine(myList.getLastLine())->setThicknessA(30);
		myList.getLine(myList.getLastLine())->setThicknessB(60);
		int e = myList.addEllipse(0, 0, 1, 1, 0, 0);
		myList.getEllipse(e)->setBoundsAlongLineSeqment(fx, fy, fx + cosf(rads * 0.5f) * 300, fy + sinf(rads * 0.5f) * 300, 50);
		
		rul.addToRenderList(myList);


		myList.setTextureSlot(3, &renderTexture);
		myList.addQuad(2000, 200, 500, 500, 3);

		
		myList.render();
		
		
		static int frame = 0;
		frame++;
		if (frame == 10) {
			frame = 0;
		
			char t[256];
			sprintf_s(t, "%s - FPS: %.1f - delta time(%.2fms) - update time(%fms)", "Batch Haven", timer.getFPS(), timer.getDeltaTime(), timer.getUpdateTime());
			Window::setTitle(t);
		}


		SoundManager::__update();
		x++;

		timer.updatePerFrameEnd();

	}

	Window::cleanup();
	glfwTerminate();


	SoundManager::__cleanup();
}