#include "Starfield.h"

Starfield::Starfield(Ogre::SceneManager* SceneMgr,Ogre::Node* node, Ogre::Entity* entity ) : GameObject(SceneMgr, node,entity)
{
	transVector = Ogre::Vector3(0,-1,0);
	speed = 90;
	isPhysicsEnabled = false;
}

Starfield::~Starfield(void)
{
}

void Starfield::Update( const Ogre::FrameEvent& evt)
{
	static int counter = 0;
	counter++;

	objectNode->translate(speed*transVector * evt.timeSinceLastFrame);

	if (objectNode->getPosition().y < -2000)
	{
		if ( counter % 2 == 1){
			objectNode->setPosition(Ogre::Vector3(0,1500,-200));
		}
		else{
			objectNode->setPosition(Ogre::Vector3(0,1500,-250));
		}
	}
}

void Starfield::Destroy()
{
}
