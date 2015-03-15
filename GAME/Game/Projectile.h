#include "BulletHelper.h"
#include "IGameObject.h"

#ifndef PROJECTILE_H
#define PROJECTILE_H
class Projectile: public IGameObject
{
public:
	Projectile();
	Projectile(ISceneManager *smgr, BulletHelper *h);
	~Projectile();	
	void fire(btVector3 &pos, btVector3 &direction);
	virtual void kill();
	void resurrect();
	virtual void Initialize();
	virtual void Update(u32 deltaTime);	

private:
	ISceneManager *smgr;
	//IMeshSceneNode *node;
	IMesh *mesh;
	BulletHelper *h;		
	u32 aliveTime;
	u32 speed;
	u32 maxLifeTime;
};
#endif // !PROJECTILE_H


