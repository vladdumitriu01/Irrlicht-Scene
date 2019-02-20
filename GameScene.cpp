#include "GameScene.h"
#include "AddSceneObjects.h"
#include <iostream>

// Constructor does nothing for now

// InitialiseScene method creates the basic Irrlicht device	
bool GameScene::InitialiseScene()
{
	// Create device.
	device = createDevice(EDT_DIRECT3D9, dimension2d<u32>(800, 600), 16, false, true, false, &keyb);
	if (device == NULL)
		return false;
	scnmgr = device->getSceneManager();
	driver = device->getVideoDriver();
	return true;
	}

// Run method contains the Irrlicht main loop
void GameScene::Run()
{
	IGUIFont* font = device->getGUIEnvironment()->getFont("./media/bigfont.png");
	u32 fps = 0;
	//create the GUI node
	IGUIStaticText *guiText = device->getGUIEnvironment()->addStaticText(L"GUI text", rect<s32>(15, 15, 100, 30), true);
	//set the background color for the gui 
	guiText->setBackgroundColor(SColor(255, 255, 155, 100));
	while (device->run())
	{// Exit Run if ESCAPE key has been pressed
		if(keyb.IsKeyDown(KEY_ESCAPE))
		{
			return;
		}
		u32 fps_now = driver->getFPS(); //get the fps at that moment
										//if statement that make the fps to show on the screen
		if (fps_now != fps) {
			stringw msg = "FPS = ";
			msg += fps_now;
			guiText->setText(msg.c_str());

			fps = fps_now;


		}
		// Draw frame
		driver->beginScene(true, true, SColor(255, 101, 100, 240));
		scnmgr->drawAll();
		device->getGUIEnvironment()->drawAll();
		driver->endScene();
	}



}


void GameScene::AddTerrain()
{
	ITerrainSceneNode *terrain = scnmgr->addTerrainSceneNode(
		"./media/terrain-heightmap.bmp", 0, -1,
		vector3df(-1000.0f, -20.0f, -1000.0f),
		vector3df(0.0f, -10.0f, 0.0f),
		vector3df(7.0f, 0.1f, 7.0f),
		SColor(255, 255, 255, 255), 4, ETPS_9, 4);
	terrain->setMaterialFlag(EMF_LIGHTING, false); //set the light for the terrain
	terrain->setMaterialTexture(0, driver->getTexture("./media/rock2.jpg"));//set the texture for the terrain
	terrain->setMaterialType(EMT_DETAIL_MAP);//set the material type for the terrain
	terrain->scaleTexture(1.0f, 20.0f);//scale the texture for the terrain


	ITriangleSelector* selector
		= scnmgr->createTerrainTriangleSelector(terrain, 0);//create the triangle selector

	terrain->setTriangleSelector(selector);

	ISceneNodeAnimator *anim = scnmgr->createCollisionResponseAnimator( //create the collision 
		selector, camera, vector3df(10.0f, 10.0f, 10.0f),
		vector3df(0.0f, 0.0f, 0.0f),
		vector3df(0.0f, 0.0f, 0.0f));
	if (anim)
	{
		selector->drop();
		camera->addAnimator(anim);
		anim->drop();
	}
}


void GameScene::SetAmbientLight()
{
	scnmgr->setAmbientLight(SColor(255, 50, 50, 50));
}

void GameScene::AddPointLight()
{
	ILightSceneNode *Light = scnmgr->addLightSceneNode();
	Light->setPosition(vector3df(0.0f, 50.0f, 0.0f));
	SLight lightData;
	lightData.DiffuseColor = SColor(255, 255, 255, 0);
	Light->setLightData(lightData);
}

void GameScene::AddWater()
{
	//create the hill mesh that is animated to simulate water
	//Tile is 20x20 and there are 40x40 tiles
	//Texture repeated 10x10 times

	IAnimatedMesh *mesh = scnmgr->addHillPlaneMesh("pool", dimension2d<f32>(10, 10), dimension2d<u32>(40, 40),0,0,dimension2d<f32>(0, 0),dimension2d<f32>(10, 10));

	//Add the water scene node for the mesh
	//Wave height is 3.0 units, speed is 300 units and lenght is 30
	ISceneNode *water_node = scnmgr->addWaterSurfaceSceneNode(mesh->getMesh(0), 3.0f, 300.0f, 30.0f);
	water_node->setPosition(vector3df(0, 7, 0));

	//Set the water and the bottom of the water
	water_node->setMaterialTexture(0, driver->getTexture("./media/water.jpg"));
	water_node->setMaterialTexture(1, driver->getTexture("./media/stones.jpg"));

	//Enable reflection layer 2 to show the bottom texture
	water_node->setMaterialType(EMT_REFLECTION_2_LAYER);
}

void GameScene::DisableCursor()
{
	// disable mouse cursor
	device->getCursorControl()->setVisible(false);


}


void GameScene::SkyBox()
{
	//create the pointers for the skybox and add the textures
	ITexture *top = driver->getTexture("./media/up.png");
	ITexture *bottom = driver->getTexture("./media/down.png");
	ITexture *left = driver->getTexture("./media/left.png");
	ITexture *right = driver->getTexture("./media/right.png");
	ITexture *front = driver->getTexture("./media/forward.png");
	ITexture *back = driver->getTexture("./media/back.png");

	//create the skybox 
	ISceneNode *skybox = scnmgr->addSkyBoxSceneNode(top, bottom, left, right, front, back);

}
// CleanUp method invokes the drop method
// to tell Irrlicht to release resources used
// to store models for example
void GameScene::CleanUp()
{
	device->drop();

}


// AddFPSCamera method creates a basic
// FPS camera object
void GameScene::FPSCamera()
{
	camera = scnmgr->addCameraSceneNodeFPS();
	camera->setPosition(vector3df(-50, 50, -400));
}



//Add 10 billboards
void GameScene::AddBilboards()
{
	AddSceneObjects billboards[10];
	billboards[1].createBillboard(driver, scnmgr, 250.0f, 250.0f, vector3df(1300.0f, 100.0f, 1000.0f), "./media/billboard5.png");
	billboards[2].createBillboard(driver, scnmgr, 250.0f, 250.0f, vector3df(700.0f, 75.0f, 1000.0f), "./media/billboard4.png");
	billboards[3].createBillboard(driver, scnmgr, 500.0f, 500.0f, vector3df(120.0f, 100.0f, 905.0f), "./media/billboard3.png");
	billboards[4].createBillboard(driver, scnmgr, 500.0f, 200.0f, vector3df(-150.0f, 30.0f, 905.0f), "./media/billboard2.png");
	billboards[5].createBillboard(driver, scnmgr, 500.0f, 500.0f, vector3df(-650.0f, 100.0f, 550.0f), "./media/billboard1.png");
	billboards[6].createBillboard(driver, scnmgr, 500.0f, 500.0f, vector3df(-650.0f, 100.0f, 150.0f), "./media/billboard6.png");
	billboards[7].createBillboard(driver, scnmgr, 500.0f, 500.0f, vector3df(-650.0f, 100.0f, -450.0f), "./media/billboard7.png");
	billboards[8].createBillboard(driver, scnmgr, 500.0f, 500.0f, vector3df(-650.0f, 600.0f, -150.0f), "./media/billboard8.png");
	billboards[9].createBillboard(driver, scnmgr, 500.0f, 500.0f, vector3df(-450.0f, 100.0f, -750.0f), "./media/billboard9.png");
	billboards[10].createBillboard(driver, scnmgr, 500.0f, 500.0f, vector3df(950.0f, 100.0f, 1150.0f), "./media/billboard10.png");
}

//Add 10 animated objects
void GameScene::AddAnimatedObjects()
{
	AddSceneObjects AnimatedObjects[10];
	//Buildings Class Order ( Driver Manager, Position, Scale, Rotation, Model File, Texture File, Scene Manager, EMD2_Animation_type)
	AnimatedObjects[1].createObject(driver, vector3df(0.0f, 0.0f, 200.0f), vector3df(3.0f, 3.0f, 3.0f), vector3df(0.0f, 0.0f, 0.0f), "./media/flag.md2", "./media/flag.pcx", scnmgr, EMAT_STAND);
	AnimatedObjects[2].createObject(driver, vector3df(400.0f, 0.0f, 0.0f), vector3df(1.0f, 1.0f, 1.0f), vector3df(0.0f, 0.0f, 0.0f), "./media/horse.md2", "./media/horse.pcx", scnmgr, EMAT_STAND);
	AnimatedObjects[3].createObject(driver, vector3df(500.0f, 110.0f, 500.0f), vector3df(1.0f, 1.0f, 1.0f), vector3df(0.0f, 0.0f, 0.0f), "./media/fire.md2", "./media/fire.png", scnmgr, EMAT_STAND);
	AnimatedObjects[4].createObject(driver, vector3df(8.0f, 260.0f, 1.0f), vector3df(0.05f, 0.05f, 0.05f), vector3df(0.0f, 0.0f, 0.0f), "./media/bird_final.md2", "./media/bird_final.pcx", scnmgr, EMAT_STAND);
	AnimatedObjects[5].createObject(driver, vector3df(220.0f, 12.0f, 1.0f), vector3df(1.0f, 1.0f, 1.0f), vector3df(0.0f, 0.0f, 0.0f), "./media/sydney.md2", "./media/sydney.bmp", scnmgr, EMAT_FLIP);
	AnimatedObjects[6].createObject(driver, vector3df(0.0f, 0.0f, 50.0f), vector3df(0.3f,0.3f,0.3f), vector3df(0.0f, 90.0f, 0.0f), "./media/dolphin.md2", "./media/dolphin_f.pcx", scnmgr, EMAT_STAND);
}


//Add 10 buildings
void GameScene::AddBuildings()
{
	AddSceneObjects Buildings[10];

	//Buildings Class Order ( Driver Manager, Position, Scale, Rotation, Model File, Texture File, Scene Manager, EMD2_Animation_type)

	Buildings[1].createObject(driver, vector3df(500.0f, -25.0f, 500.0f), vector3df(3.5f, 3.5f, 3.5), vector3df(0.0f, 0.0f, 0.0f), "./media/building1.obj", "./media/building2.jpg", scnmgr, EMAT_STAND);
	Buildings[2].createObject(driver, vector3df(500.0f, -17.0f, 700.0f), vector3df(0.7f, 0.7f, 0.7f), vector3df(0.0f, 0.0f, 0.0f), "./media/woodcabin.obj", "./media/woodcabin.jpg", scnmgr, EMAT_STAND);
	Buildings[3].createObject(driver, vector3df(1000.0f, -12.0f, 750.0f), vector3df(0.3f, 0.3f, 0.3f), vector3df(0.0f, 0.0f, 0.0f), "./media/church.obj", "./media/church.tga", scnmgr, EMAT_STAND);
	Buildings[4].createObject(driver, vector3df(-550.0f, 0.0f, -250.0f), vector3df(30.0f, 30.0f, 30.0f), vector3df(0.0f, 0.0f, 0.0f), "./media/Build.obj", "./media/buil.jpg", scnmgr, EMAT_STAND);
	Buildings[5].createObject(driver, vector3df(1000.0f, 0.0f, 0.0f), vector3df(25.0f, 25.0f, 25.0f), vector3df(0.0f, 0.0f, 0.0f), "./media/warehouse.obj", "./media/warehouse.jpg", scnmgr, EMAT_STAND);
	Buildings[6].createObject(driver, vector3df(800.0f, 0.0f, -100.0f), vector3df(1.0f, 1.0f, 1.0f), vector3df(0.0f, 0.0f, 0.0f), "./media/Medieval_House.obj", "./media/Medieval_House.png", scnmgr, EMAT_STAND);
	Buildings[7].createObject(driver, vector3df(750.0f, 0.0f, -400.0f), vector3df(1.0f, 1.0f, 1.0f), vector3df(0.0f, 90.0f, 0.0f), "./media/build10.obj", "./media/building2.jpg", scnmgr, EMAT_STAND);
	Buildings[8].createObject(driver, vector3df(300.0f, 0.0f, -200.0f), vector3df(1.0f, 1.0f, 1.0f), vector3df(0.0f, 0.0f, 0.0f), "./media/build11.obj", "./media/warehouse.jpg", scnmgr, EMAT_STAND);
	Buildings[9].createObject(driver, vector3df(-250.0f, 0.0f, 0.0f), vector3df(2.0f, 2.0f, 2.0f), vector3df(0.0f, 0.0f, 0.0f), "./media/houseA_obj.obj", "./media/houseA.jpg", scnmgr, EMAT_STAND);
	Buildings[10].createObject(driver, vector3df(0.0f, 0.0f, 500.0f), vector3df(10.0f, 10.0f, 10.0f), vector3df(0.0f, 0.0f, 0.0f), "./media/build13.3ds", "./media/wall11.jpg", scnmgr, EMAT_STAND);

}

//Add 10 static objects
void GameScene::AddStaticObjects()
{

	AddSceneObjects objects[10];

	//Objects Class Order ( Driver Manager, Position, Scale, Rotation, Model File, Texture File, Scene Manager, EMD2_Animation_type)
	objects[1].createObject(driver, vector3df(0.0f, 0.0f, 0.0f), vector3df(0.5f,0.5f,0.5f), vector3df(0.0f, 0.0f, 0.0f), "./media/zombie_hand.obj", "./media/zombie_hand.png", scnmgr, EMAT_STAND);
	objects[2].createObject(driver, vector3df(3.0f, 0.0f, 2.0f), vector3df(20.0f, 20.0f, 20.0f), vector3df(0.0f, 0.0f, 0.0f), "./media/HorrorTree.obj", "./media/HorrorTree.jpg", scnmgr, EMAT_STAND);
	objects[3].createObject(driver, vector3df(600.0f, -25.0f, 800.0f), vector3df(1.0f,1.0f,1.0f), vector3df(0.0f, 0.0f, 0.0f), "./media/car.obj", "./media/black.jpg", scnmgr, EMAT_STAND);
	objects[4].createObject(driver, vector3df(50.0f, 0.0f, 170.0f), vector3df(20.0f, 20.0f, 20.0f), vector3df(270.0f, 90.0f, 0.0f), "./media/dog.dae", "./media/dog.tga", scnmgr, EMAT_STAND);
	objects[5].createObject(driver, vector3df(150.0f, -26.0f, 330.0f), vector3df(20.0f, 20.0f, 20.0f), vector3df(0.0f, 180.0f, -15.0f), "./media/skull.obj", "./media/skull.png", scnmgr, EMAT_STAND);
	objects[6].createObject(driver, vector3df(150.0f, -26.0f, 430.0f), vector3df(20.0f, 20.0f, 20.0f), vector3df(0.0f, 180.0f, -15.0f), "./media/rock.obj", "./media/rock.jpg", scnmgr, EMAT_STAND);
	objects[7].createObject(driver, vector3df(150.0f, -26.0f, 720.0f), vector3df(0.4f, 0.4f, 0.4f), vector3df(0.0f, 180.0f, -15.0f), "./media/Stone_stele.obj", "./media/rock.jpg", scnmgr, EMAT_STAND);
	//objects[8].createObject(driver, vector3df(150.0f, -26.0f, 330.0f), vector3df(1.0f,1.0f,1.0f), vector3df(0.0f, 180.0f, -15.0f), "./media/Zombie_Man.obj", "./media/skull.png", scnmgr, EMAT_STAND);
	objects[9].createObject(driver, vector3df(150.0f, -26.0f, -630.0f), vector3df(20.0f, 20.0f, 20.0f), vector3df(0.0f, 180.0f, -15.0f), "./media/tree.obj", "./media/HorrorTree.jpg", scnmgr, EMAT_STAND);
	objects[10].createObject(driver, vector3df(150.0f, -26.0f, 630.0f), vector3df(1.6f, 1.6f, 1.6f), vector3df(0.0f, 180.0f, -15.0f), "./media/generic110.obj", "./media/HorrorTree.jpg", scnmgr, EMAT_STAND);

}
