#pragma once
#include "GalaxyShooter.h"
#include "GameObject.h"
#include "Projectile.h"
#include "Enemy.h"
#include "ParticleController.h"


class SpaceCraft : public GameObject
{
public:
	SpaceCraft(Ogre::SceneManager*,Ogre::Node*,Ogre::Entity*);
	~SpaceCraft(void);

	void Shoot();

	virtual void Update( const Ogre::FrameEvent& );
	virtual void Destroy();

	virtual void keyPressed( const OIS::KeyEvent & );
	virtual void keyReleased( const OIS::KeyEvent & );
	virtual void mousePressed( const OIS::MouseEvent&, OIS::MouseButtonID );
	virtual void mouseReleased( const OIS::MouseEvent&, OIS::MouseButtonID );
	virtual void mouseMoved(const OIS::MouseEvent & );

	virtual void Collided( GameObject* );


private:
	Ogre::Vector3 transVector;
	Ogre::Real mRotate;	
	Ogre::Real mMove;
};
