#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(Ogre::SceneManager*,Ogre::Node*,Ogre::Entity*);
	~Projectile(void);

	virtual void Update( const Ogre::FrameEvent& );
	virtual void Destroy();

	virtual void keyPressed( const OIS::KeyEvent & );
	virtual void keyReleased( const OIS::KeyEvent & );
	virtual void mousePressed( const OIS::MouseEvent&, OIS::MouseButtonID);
	virtual void mouseReleased( const OIS::MouseEvent&, OIS::MouseButtonID);
	virtual void mouseMoved( const OIS::MouseEvent &);

private:
	Ogre::Vector3 transVector;
	float speed;
};

