#pragma once
#include <string>
#include <sstream>

#include <OgreSceneManager.h>
#include <OgreEntity.h>

#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(Ogre::SceneManager* sceneManager,Ogre::Node* node,string name) : GameObject(sceneManager,node,name)
	{

	}

	virtual void Update( const Ogre::FrameEvent& );

};

