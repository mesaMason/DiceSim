// DiceSimApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../../bullet3-2.85.1/examples/CommonInterfaces/CommonExampleInterface.h"
#include "../../../bullet3-2.85.1/examples/CommonInterfaces/CommonGUIHelperInterface.h"
#include "../../../bullet3-2.85.1/examples/Utils/b3Clock.h"
#include "../../../bullet3-2.85.1/examples/OpenGLWindow/SimpleOpenGL3App.h"
#include <stdio.h>
#include "../../../bullet3-2.85.1/examples/ExampleBrowser/OpenGLGuiHelper.h"
#include "WeightedDie.h"

CommonExampleInterface*    example;
int gSharedMemoryKey=-1;

b3MouseMoveCallback prevMouseMoveCallback = 0;
static void OnMouseMove( float x, float y)
{
	bool handled = false; 
	handled = example->mouseMoveCallback(x,y); 	 
	if (!handled)
	{
		if (prevMouseMoveCallback)
			prevMouseMoveCallback (x,y);
	}
}

b3MouseButtonCallback prevMouseButtonCallback  = 0;
static void OnMouseDown(int button, int state, float x, float y) {
	bool handled = false;

	handled = example->mouseButtonCallback(button, state, x,y); 
	if (!handled)
	{
		if (prevMouseButtonCallback )
			prevMouseButtonCallback (button,state,x,y);
	}
}

class LessDummyGuiHelper : public DummyGUIHelper
{
	CommonGraphicsApp* m_app;
public:
	virtual CommonGraphicsApp* getAppInterface()
	{
		return m_app;
	}

	LessDummyGuiHelper(CommonGraphicsApp* app)
		:m_app(app)
	{
	}
};
int main(int argc, char* argv[])
{
	
	SimpleOpenGL3App* app = new SimpleOpenGL3App("Bullet Standalone Example",1024,768,true);
	
	prevMouseButtonCallback = app->m_window->getMouseButtonCallback();
	prevMouseMoveCallback = app->m_window->getMouseMoveCallback();

	app->m_window->setMouseButtonCallback((b3MouseButtonCallback)OnMouseDown);
	app->m_window->setMouseMoveCallback((b3MouseMoveCallback)OnMouseMove);
	
	OpenGLGuiHelper gui(app,false);
	//LessDummyGuiHelper gui(app);
	//DummyGUIHelper gui;

	CommonExampleOptions options(&gui);

	example = WeightedDieCreateFunc(options);
	example->initPhysics();
	example->resetCamera();
	
	b3Clock clock;

	do
	{
		app->m_instancingRenderer->init();
        app->m_instancingRenderer->updateCamera(app->getUpAxis());

		btScalar dtSec = btScalar(clock.getTimeInSeconds());
		example->stepSimulation(dtSec);
	  	clock.reset();

		example->renderScene();
 	
		DrawGridData dg;
        dg.upAxis = app->getUpAxis();
		app->drawGrid(dg);
		
		app->swapBuffer();
	} while (!app->m_window->requestedExit());

	example->exitPhysics();
	delete example;
	delete app;
	return 0;
}

