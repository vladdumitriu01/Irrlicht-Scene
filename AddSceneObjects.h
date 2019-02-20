#pragma once
#include <irrlicht.h>
#include <string>
#include "AddSceneObjects.h"

//Add the Irrlicht namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;


//Pragma comments for the Irrlicht library and to suppress the console window
#ifdef _MSC_VER
#pragma comment(lib, "irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class AddSceneObjects
{
public:
	AddSceneObjects();
	~AddSceneObjects();



	IBillboardSceneNode* createBillboard(IVideoDriver* myDriver, ISceneManager* mySceneManager, float Width, float Height, vector3df myPosition, const char* textureName);

	IAnimatedMeshSceneNode* createObject(
		IVideoDriver *myDriver,
		vector3df myObjectPosition, vector3df myScale, vector3df myObjectRotation, const char* MyMesh, const char* textureName, ISceneManager* mySceneManager, EMD2_ANIMATION_TYPE myAnimation);

};

