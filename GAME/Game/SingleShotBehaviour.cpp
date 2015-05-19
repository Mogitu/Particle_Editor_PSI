#include "SingleShotBehaviour.h"

void SingleShotBehaviour::setUpWeaponBehaviour(GameWorld* w)
{
	this->setWorld(w);
}

void SingleShotBehaviour::doWeaponBehaviour(btVector3 &offset, btVector3 &direction, stringw name)
{
	Projectile *p = getPool()->create();
	if (p)
	{
		if (!p->warmedUp)
		{
			this->getWorld()->addGameObject(p);
		}

		p->Initialize(Common::smgr, Common::helper, name, offset, direction);
		p->fire(offset, direction);

		Common::soundEngine->play2D("../Assets/Sounds/shoot.wav");
	}
}