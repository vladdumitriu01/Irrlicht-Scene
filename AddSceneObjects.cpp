#include "AddSceneObjects.h"
#include <iostream>


/*Encapsulation - The concept of classes. Classes hold data members (e.g int myHealth)
and "member functions" (e.g: void increaseHealth(amount)). The

*/
//Abstraction - THe concept of Declarations in header files AND definitions in .cpp files. 
// THe point of abstraction is for the developer to view only the header file contents. 
// Another definition (Main definition) of abstraction is to hide all data members which are not needed, preventing them from being modified
// by other people. This is very important for large projects where multiple people can make many mistakes
//and access data members which only need to be read and not written to (Modified/assigned a value)
//We use functions to limit the access to a variable (Getters and setters)
AddSceneObjects::AddSceneObjects()
{
}


AddSceneObjects::~AddSceneObjects()
{
}


IBillboardSceneNode *AddSceneObjects::createBillboard(IVideoDriver *myDriver, ISceneManager* mySceneManager, float Width, float Height, vector3df myPosition, const char* textureName)
{


	IBillboardSceneNode *billboard = mySceneManager->addBillboardSceneNode(NULL, dimension2d<f32>(Width, Height), myPosition);


	billboard->setMaterialFlag(EMF_LIGHTING, false);//add the light for the billboard
	billboard->setMaterialTexture(0, myDriver->getTexture(textureName));//add the texture for the billboard
	billboard->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);//remove the black background from the image
	return billboard;
}

IAnimatedMeshSceneNode *AddSceneObjects::createObject(
	IVideoDriver *myDriver,
	vector3df myObjectPosition, vector3df myScale, vector3df myObjectRotation, const char* MyMesh, const char* textureName, ISceneManager* mySceneManager, EMD2_ANIMATION_TYPE myAnimation)
{
	IAnimatedMesh* objectnode = mySceneManager->getMesh(MyMesh);
	IAnimatedMeshSceneNode* object = mySceneManager->addAnimatedMeshSceneNode(objectnode);

	object->setMaterialFlag(EMF_LIGHTING, false);
	object->setMaterialTexture(0, myDriver->getTexture(textureName));
	object->setPosition(vector3df(myObjectPosition));
	object->setScale(vector3df(myScale));
	object->setRotation(vector3df(myObjectRotation));
	object->setMD2Animation(myAnimation);
	return object; //Need to return an object of type IMeshSceneNode


}
