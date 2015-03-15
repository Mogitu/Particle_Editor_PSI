#include "GameWorld.h"
#include "BulletHelper.h"
#include "ParticleWorld.h"


GameWorld::GameWorld(BulletHelper *h, IrrlichtDevice *device) :helper(h), device(device)
{

}
GameWorld::~GameWorld()
{
	clearGameObjects();
}

//TODO: Game Objects that are being removed from the Game World now still exists in the Physics World -Jos�
void GameWorld::clearGameObjects()
{
	for (core::list<IGameObject *>::Iterator Iterator = gameObjects.begin(); Iterator != gameObjects.end(); ++Iterator)
	{
		IGameObject* gameObject = *Iterator;

		delete gameObject;
	}

	gameObjects.clear();
}

void GameWorld::update(u32 frameDeltaTime)
{
	for (core::list<IGameObject *>::Iterator Iterator = gameObjects.begin(); Iterator != gameObjects.end(); ++Iterator)
	{
		IGameObject* gameObject = *Iterator;
		gameObject->Update(frameDeltaTime);
		helper->updatePhysics(gameObject->body);

		stringw nodeName = gameObject->node->getName();
		
		if (!gameObject->isAlive || nodeName=="dead")
		{
			gameObject->kill();
			gameObjects.erase(Iterator);
			delete gameObject;
			return;			
		}			
	}
	
	//collision detection
	//TODO: VERY SLOPPY; in its current state this will need a lot of special case checks. Needs to be improved in later sprints.
	int numManifolds = helper->getWorld()->getDispatcher()->getNumManifolds();
	for (int i = 0; i<numManifolds; i++)
	{
		btPersistentManifold* contactManifold = helper->getWorld()->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)contactManifold->getBody0();
		btCollisionObject* obB = (btCollisionObject*)contactManifold->getBody1();

		ISceneNode *nodeA =  (ISceneNode*)contactManifold->getBody0()->getUserPointer();
		ISceneNode *nodeB = (ISceneNode*)contactManifold->getBody1()->getUserPointer();		

		std::string nameA = nodeA->getName();
		std::string nameB = nodeB->getName();
		
		if ((nameB == "Enemy"&&nameA == "Projectile") || (nameA == "Enemy"&&nameB == "Projectile"))
		{					
			int numContacts = contactManifold->getNumContacts();
			for (int j = 0; j<numContacts; j++)
			{
				btManifoldPoint& pt = contactManifold->getContactPoint(j);
				if (pt.getDistance()<0.f)
				{
					const btVector3& ptA = pt.getPositionWorldOnA();
					const btVector3& ptB = pt.getPositionWorldOnB();
					const btVector3& normalOnB = pt.m_normalWorldOnB;
					//std::cout << "Hit" << std::endl;
					IParticleSystemSceneNode* ps = ParticleWorld::createParticleSystem(vector3df(ptA.getX(),ptA.getY(), ptA.getZ()), vector3df(2, 2, 2), "../Assets/fire.bmp");
					ParticleWorld::createBoxParticle(ps, "../Assets/testEffect.xml", device);
				}
				nodeA->setName("dead");
				nodeB->setName("dead");
			}
		}		
	}
}



void GameWorld::addGameObject(IGameObject* gameObject)
{
	this->gameObjects.push_back(gameObject);
}

//TODO: Game Objects that are being removed from the Game World now still exists in the Physics World -Jos�
void GameWorld::removeGameObject(IGameObject* gameObject)
{
	for (core::list<IGameObject *>::Iterator Iterator = gameObjects.begin(); Iterator != gameObjects.end(); ++Iterator)
	{
		if (gameObject == *Iterator)
		{
			gameObjects.erase(Iterator);
			delete gameObject;
			break;
		}
	}
}