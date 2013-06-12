#pragma once
#include "GalaxyShooter.h"
#include "GameObject.h"
#include "Projectile.h"

class Enemy :
	public GameObject
{
public:
	Enemy(Ogre::SceneManager*,Ogre::Node*, Ogre::Entity*);
	~Enemy(void);

	virtual void Update( const Ogre::FrameEvent& );
	virtual void Destroy();

	virtual void keyPressed( const OIS::KeyEvent & );
	virtual void keyReleased( const OIS::KeyEvent & );
	virtual void mousePressed( const OIS::MouseEvent&, OIS::MouseButtonID );
	virtual void mouseReleased( const OIS::MouseEvent&, OIS::MouseButtonID );
	virtual void mouseMoved( const OIS::MouseEvent & );

	virtual void Collided( GameObject* );


private:
	float speed;
	Ogre::Vector3 transVector;
};

