#pragma once
#include "GameObject.h"
class Starfield :
	public GameObject
{
public:
	Starfield(Ogre::SceneManager*,Ogre::Node*,Ogre::Entity*);
	~Starfield(void);

	virtual void Update( const Ogre::FrameEvent& );
	virtual void Destroy();

	virtual bool IsCollided(GameObject* otherObject) { return false;}

private:
	Ogre::Vector3 transVector;
	float speed;
};
