#pragma once

#include <irrlicht.h>
#include <irrKlang.h>
#include "KeyEventReceiver.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;
using namespace irrklang;


#ifdef _MSC_VER
#pragma comment(lib, "irrlicht.lib")
#pragma comment(lib, "irrklang.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

//Game Scene Class, which is drawing all the scene things

class GameScene {
public:

	//Constructor
	GameScene() {
	};

	//Call this to initialise the scene,
	// e.g. load models,billboards,etc

	bool InitialiseScene();


	//call this to run the main loop
	//call this after inilitialising the scene

	void Run();


	//call this to clean up any resources
	//including irrlicht device after the main loop has finished

	void CleanUp();

	//Add FPS camera 

	void FPSCamera();

	//call these 2 to set the light

	void SetAmbientLight();

	void AddPointLight();

	//call this to set the water

	void AddWater();

	//call this to draw the terrain

	void AddTerrain();

	//call this to not show the cursor on the screen while the device is running

	void DisableCursor();

	//call this to draw the skybox

	void SkyBox();

	//call this to draw the GUI

	void GUI();

	//call this to import all the billboards

	void AddBilboards();

	//call this to import all the buildings

	void AddBuildings();

	//call this to import all the animated objects

	void AddAnimatedObjects();

	//call this to import all the static objects

	void AddStaticObjects();

	//call this to run the background sound

	ISceneManager *scnmgr;
	IVideoDriver *driver;
	IrrlichtDevice * device;
//private data
private:
	
	
	
	ICameraSceneNode *camera;
	KeyEventReceiver keyb;
	IAnimatedMeshSceneNode *NPC;
};
