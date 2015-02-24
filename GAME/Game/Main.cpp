#include <irrlicht.h>
#include "BulletHelper.h"
#include  "Level.h"
#include <cstdlib>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


int main() {
	IrrlichtDevice *device;
	IVideoDriver *irrDriver;
	ISceneManager *smgr;
	IGUIEnvironment *guiEnv;
	IFileSystem *irrFile;
	ITimer *irrTimer;
	ILogger *irrLog;
	Level *level;
	BulletHelper* helper;

	// Initialize irrlicht	
	device = createDevice(video::EDT_OPENGL, dimension2d<u32>(800, 600), 32, false, false, false, 0);
	guiEnv = device->getGUIEnvironment();
	irrTimer = device->getTimer();
	smgr = device->getSceneManager();
	irrDriver = device->getVideoDriver();
	device->getCursorControl()->setVisible(0);
	
	// Add camera
	ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(0, 100, 0.1);
	camera->setPosition(vector3df(350, 250, 300));
	camera->setTarget(vector3df(0, 0, 0));	

	level = new Level(smgr, "../Assets/level.irr");	

	// Create the initial scene
	smgr->addLightSceneNode(0, core::vector3df(2, 5, -2), SColorf(4, 4, 4, 1));	

	helper = new BulletHelper();
	helper->buildIrrLevel(level);

	//Default mesh from demos
	IMesh* mesh = smgr->getMesh("../Assets/sydney.md2");		
	
	//default node setup
	IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);	
	node->setMaterialTexture(0, irrDriver->getTexture("../Assets/sydney.bmp"));	
	node->setPosition(vector3df(0,100,80));

	//createa a new rigidbody from earlier made node
	btRigidBody *b =helper->createBody(node,Shape_Type::CAPSULE, 1);
	b->setAngularFactor(btVector3(0,1,0));
	//apply impulse in direction and position off. Use linear velocitiy, or something, for movement.
	b->applyImpulse(btVector3(0, 40, -20), btVector3(0,0,0));	

	// Main loop
	u32 timeStamp = irrTimer->getTime(), deltaTime = 0;
	while (device->run()) {
		deltaTime = irrTimer->getTime() - timeStamp;
		timeStamp = irrTimer->getTime();
		helper->updatePhysics(deltaTime);
		irrDriver->beginScene(true, true, SColor(255, 20, 0, 0));
		smgr->drawAll();
		guiEnv->drawAll();
		irrDriver->endScene();
		device->run();
	}
	device->drop();

	return 0;
}










