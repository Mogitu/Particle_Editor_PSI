#ifndef WEAPON_H
#define WEAPON_H

#include "WeaponBehaviour.h"
#include "Elementals.h"

class Weapon
{
private:
	WeaponBehaviour* weaponBehaviour;
	u32 shootIntervalTimer;
	u32 shootInterval;
	float damagePerProjectile;
public:
	bool canShoot;
	void Initialize(WeaponBehaviour* wpb, GameWorld* w, u32 interval, float dpp) 
	{ 
		weaponBehaviour = wpb;
		weaponBehaviour->setUpWeaponBehaviour(w); 
		shootIntervalTimer = 0;
		shootInterval = interval;
		canShoot = true;
		damagePerProjectile = dpp;
	}
	WeaponBehaviour* getWeaponBehaviour() const { return weaponBehaviour; }
	void Update(irr::u32 frameDeltaTime)
	{
		if (!canShoot)
			shootIntervalTimer += frameDeltaTime;

		if (shootIntervalTimer >= shootInterval)
		{
			shootIntervalTimer = 0;
			canShoot = true;
		}

		weaponBehaviour->Update(frameDeltaTime);
	}
	virtual void fire(btVector3 &offset, btVector3 &direction, stringw name) = 0;
	virtual ElementalType getWeaponElementalType() = 0;
	float getDamagePerProjectile() { return damagePerProjectile; }
	~Weapon() { delete weaponBehaviour; }
};


#endif