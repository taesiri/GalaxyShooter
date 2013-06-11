#include "Projectile.h"

Projectile::Projectile(Ogre::SceneManager* SceneMgr,Ogre::Node* node, Ogre::Entity* entity ) : GameObject(SceneMgr, node,entity)
{
	transVector = Ogre::Vector3(0,1,0);
	speed = 1000;
}

Projectile::~Projectile( void )
{

}

void Projectile::Update( const Ogre::FrameEvent&arg )
{
	objectNode->translate(speed*transVector * arg.timeSinceLastFrame);
}

void Projectile::Destroy()
{
	
}

void Projectile::keyPressed( const OIS::KeyEvent &arg )
{
	
}

void Projectile::keyReleased( const OIS::KeyEvent &arg )
{
	
}

void Projectile::mousePressed( const OIS::MouseEvent&arg, OIS::MouseButtonID id)
{
	
}

void Projectile::mouseReleased( const OIS::MouseEvent&arg, OIS::MouseButtonID id )
{
	
}

void Projectile::mouseMoved( const OIS::MouseEvent &arg )
{
	
}


