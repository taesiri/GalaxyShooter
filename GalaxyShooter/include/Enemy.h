#pragma once
#include "GalaxyShooter.h"
#include "GameObject.h"
#include "Projectile.h"
#include "SpaceCraft.h"

class Enemy :
	public GameObject
{
public:
	Enemy(Ogre::SceneManager*,Ogre::Node*, Ogre::Entity*);
	~Enemy(void);

	virtual void Update( const Ogre::FrameEvent& );
	virtual void Destroy();

	virtual void Collided( GameObject* );


private:
	float speed;
	Ogre::Vector3 transVector;
};

