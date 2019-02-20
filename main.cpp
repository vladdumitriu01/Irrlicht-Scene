// Include the GameScene class definition
#include "GameScene.h"

// Main function
int main() {
	// Create the game scene object below
	GameScene game;
	// Initialise the scene, check whether
	// initialisation was successful

	if (!game.InitialiseScene())
	{
		game.FPSCamera();
	}
	// Add the camera
	game.FPSCamera();

	// Set the ambient light
	game.SetAmbientLight();

	// Add the  point light
	game.AddPointLight();

	// Add water to the scene
	game.AddWater();

	// Add terrain to the scene
	game.AddTerrain();
	
	// Disable the cursor
	game.DisableCursor();

	// Add skybox to the scene
	game.SkyBox();

	// Add billboards to the scene
	game.AddBilboards();





	// Add all the objects to the scene
	game.AddAnimatedObjects();
	game.AddBuildings();
	game.AddStaticObjects();

	// Add Background sound
	ISoundEngine *engine2 = createIrrKlangDevice();
	ISound *sound = engine2->play2D("Media/saw.mp3", true, false);


	// Invoke the Run method to perform
	// the main loop
	game.Run();
	// Invoke the CleanUp method to 
	// release resources
	game.CleanUp();

	return 0;
}

