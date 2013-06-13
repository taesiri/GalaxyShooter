#include "Projectile.h"

Projectile::Projectile(Ogre::SceneManager* SceneMgr,Ogre::Node* node, Ogre::Entity* entity ) : GameObject(SceneMgr, node,entity)
{
	transVector = Ogre::Vector3(0,1,0);
	speed = 1000;
}

Projectile::~Projectile( void )
{

}

void Projectile::Update( const Ogre::FrameEvent& evt )
{
	objectNode->translate(speed*transVector * evt.timeSinceLastFrame);

	if (objectNode->getPosition().y > 510)
		Destroy();
}

void Projectile::Destroy()
{
	GalaxyShooter::deleteList.push_back(this);
}

void Projectile::Collided( GameObject* otherObject)
{
	if (dynamic_cast<Enemy*> (otherObject)!= NULL )
	{
		Destroy();
		otherObject->Destroy();
	}
}
