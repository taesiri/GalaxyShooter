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

	virtual void keyPressed( const OIS::KeyEvent & );
	virtual void keyReleased( const OIS::KeyEvent & );
	virtual void mousePressed( const OIS::MouseEvent&, OIS::MouseButtonID );
	virtual void mouseReleased( const OIS::MouseEvent&, OIS::MouseButtonID );
	virtual void mouseMoved( const OIS::MouseEvent & );

	virtual bool IsCollided(GameObject* otherObject) { return false;}

private:
	Ogre::Vector3 transVector;
	float speed;
};
