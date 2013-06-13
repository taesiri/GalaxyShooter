#pragma once
#include "GalaxyShooter.h"
#include "GameObject.h"
#include "Enemy.h"

class Projectile : public GameObject
{
public:
	Projectile(Ogre::SceneManager*,Ogre::Node*,Ogre::Entity*);
	~Projectile(void);

	virtual void Update( const Ogre::FrameEvent& );
	virtual void Destroy();

	virtual void Collided( GameObject* );

private:
	Ogre::Vector3 transVector;
	float speed;
};

