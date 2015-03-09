#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "InputReceiver.h"
#include <btBulletCollisionCommon.h>
#include "BulletHelper.h"
#include "IGameObject.h"
#include "BulletHelper.h"
#include "GameWorld.h"
#include "Projectile.h"

class Player : public IGameObject
{
private:
	InputReceiver* input;
	btRigidBody* body;
	scene::IAnimatedMeshSceneNode* node;
	BulletHelper* helper;
	ISceneManager* smgr;
	Projectile *p;
	vector2di oldMousePos;

	bool justJumped;
	bool isGrounded();
public:
	Player(ISceneManager* smgr, IVideoDriver* driver, BulletHelper* helper, GameWorld* world,InputReceiver* input, io::path meshName, io::path textureName, Shape_Type bodyType, btScalar bodyMass = 1,vector3df position = vector3df(0, 0, 0), vector3df rotation = vector3df(0, 0, 0), vector3df scale = vector3df(1, 1, 1));
	void Initialize();
	void Initialize(ISceneManager* smgr, IVideoDriver* driver, BulletHelper* helper, GameWorld* world, InputReceiver* input, io::path meshName, io::path textureName, Shape_Type bodyType, btScalar bodyMass, vector3df position = vector3df(0, 0, 0), vector3df rotation = vector3df(0, 0, 0), vector3df scale = vector3df(1, 1, 1));
	void Update(u32 frameDeltaTime);
	void PlayerMovement(u32 frameDeltaTime);
	void Fire();
	vector3df getNodePosition();
	GameObjectType getType();
};

#endif // !__PLAYER_H__