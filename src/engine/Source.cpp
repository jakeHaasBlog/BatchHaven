
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
#include "PerlinNoiseGenerator.h"
#include "MazeGenerator.h"

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


	RenderList myList;
	PerlinNoiseGenerator g;
	g.setOctaves(3);
	g.setScaleX(0.03f);
	g.setScaleY(0.03f);
	g.setOctaves(20);
	Texture myTex = Texture("assets/test.png");
	Texture myTex2 = Texture("assets/nature.jpg");


	auto data = myTex.getPixels();
	for (int x = 0; x < myTex.getWidth(); x++) {
		for (int y = 0; y < myTex.getHeight(); y++) {

			float val = g.getValueAt(x, y);

			data[x + y * myTex.getWidth()][0] = val;
			data[x + y * myTex.getWidth()][1] = val;
			data[x + y * myTex.getWidth()][2] = val;
			data[x + y * myTex.getWidth()][3] = 1.0f;
		}
	}
	auto newData = data;

	int sampleAreaX = 30;
	int sampleAreaY = 30;
	for (int x = 0; x < myTex.getWidth(); x++) {
		for (int y = 0; y < myTex.getHeight(); y++) {

			float total = 0.0f;
			for (int x1 = -sampleAreaX / 2; x1 < sampleAreaX / 2; x1++) {
				for (int y1 = -sampleAreaY / 2; y1 < sampleAreaY / 2; y1++) {
					if (!(x + x1 < 0 || x + x1 >= myTex.getWidth() || y + y1 < 0 || y + y1 >= myTex.getHeight())) {
						total += data[(x + x1) + (y + y1) * myTex.getWidth()][0];
					}
				}
			}
			total /= sampleAreaX * sampleAreaY;

			newData[x + y * myTex.getWidth()][0] = total;
			newData[x + y * myTex.getWidth()][1] = total;
			newData[x + y * myTex.getWidth()][2] = total;

		}
	}

	for (int x = 0; x < myTex.getWidth(); x++) {
		for (int y = 0; y < myTex.getHeight(); y++) {

			float val = newData[x + y * myTex.getWidth()][0];

			val *= 10.0f;
			val = (int)val;
			val /= 10;

			newData[x + y * myTex.getWidth()][0] = val;
			newData[x + y * myTex.getWidth()][1] = val;
			newData[x + y * myTex.getWidth()][2] = val;
			
			newData[x + y * myTex.getWidth()][3] = 1.0f;
		}
	}

	myTex.generateFromData(myTex.getWidth(), myTex.getHeight(), &newData[0][0]);

	myList.setTextureSlot(0, &myTex);
	int a = myList.addQuad(0, 0, Window::getWidth(), Window::getHeight(), 0);
	myList.getQuad(a)->setTextureSampleArea(-1, -1, 2, 2);

	MazeGenerator mg(60, 30);
	RenderList mazeList;


	glfwSwapInterval(1);
	int x = 0;
	while (!glfwWindowShouldClose(Window::getHandle())) {

		glfwSwapBuffers(Window::getHandle());
		timer.updatePerFrameBegin();
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		Window::update();

		//myList.clear();
		//
		//
		//// corners
		//myList.addQuad(Window::getWidth() / 2 - 25, Window::getHeight() / 2 - 25, 50, 50, 1.0f, 0.0f, 0.0f);
		//myList.addQuad(0, 0, 50, 50, 1, 0, 0);
		//int id = myList.addQuad(Window::getWidth() - 50, 0, 50, 50, 1, 0, 0);
		//myList.addQuad(Window::getWidth() - 50, Window::getHeight() - 50, 50, 50, 1, 0, 0);
		//myList.addQuad(0, Window::getHeight() - 50, 50, 50, 1, 0, 0);
		//
		//
		myList.render();

		mazeList.clear();
		//mg = MazeGenerator(30, 30);
		//mg.fullyGenerate();
		mg.itterateGeneration();
		mg.appendToRenderList(mazeList, 100, 100, Window::getWidth() - 200, Window::getHeight() - 200);
		mazeList.render();
		
		
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