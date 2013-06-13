#pragma once

#include <Ogre.h>
#include "GameObject.h"
#include "GalaxyShooter.h"

class ParticleController : public GameObject
{
public:
	ParticleController(Ogre::ParticleSystem*, float, Ogre::SceneManager*,Ogre::Node*,Ogre::Entity*);
	~ParticleController(void);

public:
	// Public Members
	Ogre::ParticleSystem* particle;
	float lifeTime;

public:
	// Public Methods
	virtual void Update(const Ogre::FrameEvent&);
	virtual void Destroy();

	virtual bool IsCollided( GameObject*);


protected:
	bool isEnable;
};
