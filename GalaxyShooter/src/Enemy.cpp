#include "Enemy.h"


Enemy::Enemy(Ogre::SceneManager* SceneMgr,Ogre::Node* node, Ogre::Entity* entity ) : GameObject(SceneMgr, node,entity)
{
	speed =  100;
	transVector = Ogre::Vector3(0,-1,0);
}

Enemy::~Enemy(void)
{
	
}

void Enemy::Update( const Ogre::FrameEvent&evt)
{
	objectNode->translate(speed*transVector * evt.timeSinceLastFrame,Ogre::Node::TransformSpace::TS_WORLD);
	objectNode->rotate(Ogre::Vector3(1,0,0),Ogre::Degree(1.0));
	objectNode->rotate(Ogre::Vector3(0,1,0),Ogre::Degree(0.51));

	if (objectNode->getPosition().y < -520)
		Destroy();
}

void Enemy::Destroy()
{
	GalaxyShooter::deleteList.push_back(this);
}

void Enemy::keyPressed( const OIS::KeyEvent &arg)
{

}

void Enemy::keyReleased( const OIS::KeyEvent &arg)
{

}

void Enemy::mousePressed( const OIS::MouseEvent&arg, OIS::MouseButtonID id)
{

}

void Enemy::mouseReleased( const OIS::MouseEvent&arg, OIS::MouseButtonID id)
{
	
}

void Enemy::mouseMoved( const OIS::MouseEvent &arg)
{

}

void Enemy::Collided( GameObject* otherObject )
{
	if (dynamic_cast<Projectile*> (otherObject)!= NULL )
	{
		Destroy();
		otherObject->Destroy();
	}
}
