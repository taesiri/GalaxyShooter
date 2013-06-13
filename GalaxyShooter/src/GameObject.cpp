#include "GameObject.h"

int GameObject::instances = 0;

GameObject::GameObject(Ogre::SceneManager* SceneMgr,Ogre::Node* node, Ogre::Entity* entity )
{
	objectEntity = entity;
	localSceneManager = SceneMgr;
	objectNode = node;
	instances++;
	isPhysicsEnabled = true;
}

GameObject::~GameObject()
{
	instances--;
	if ( objectEntity != NULL){
		localSceneManager->destroyEntity(objectEntity);
	}
}

void GameObject::Update(const Ogre::FrameEvent& evt)
{
}

void GameObject::Translate( Ogre::Vector3 translateVector)
{
}

Ogre::Vector3* GameObject::getGlobalBoundaries()
{
	Ogre::Vector3* returnValue = new Ogre::Vector3[4];

	auto pos = objectNode->getPosition();
	auto scale = objectNode->getScale();

	auto center = objectEntity->getBoundingBox().getCenter();
	auto esize = objectEntity->getBoundingBox().getSize();

	returnValue[0] = Ogre::Vector3(((center.x - (esize.x/2)) *scale.x)+ pos.x,((center.y - esize.y/2) * scale.y) + pos.y, 0);
	returnValue[1] = Ogre::Vector3(((center.x + (esize.x/2)) *scale.x)+ pos.x,((center.y - esize.y/2) * scale.y) + pos.y, 0);
	returnValue[2] = Ogre::Vector3(((center.x - (esize.x/2)) *scale.x)+ pos.x,((center.y + esize.y/2) * scale.y) + pos.y, 0);
	returnValue[3] = Ogre::Vector3(((center.x + (esize.x/2)) *scale.x)+ pos.x,((center.y + esize.y/2) * scale.y) + pos.y, 0);

	return returnValue;
}

bool GameObject::IsCollided(GameObject* otherObject)
{
	if (this->isPhysicsEnabled && otherObject->isPhysicsEnabled)
	{
		Ogre::Vector3* otherObjectCordinates = otherObject->getGlobalBoundaries();

		// 4 Points Only
		Ogre::Vector3* baseObjectCordinates = getGlobalBoundaries();

		for (int i = 0 ; i < 4; i++)
		{
			if((otherObjectCordinates[i].x > baseObjectCordinates[0].x) &&  (otherObjectCordinates[i].x < baseObjectCordinates[1].x)
				&&(otherObjectCordinates[i].y >  baseObjectCordinates[0].y) &&  (otherObjectCordinates[i].y < baseObjectCordinates[3].y))
			{
				Collided(otherObject);
				return true;
			}
		}
	}
	return false;
}

void GameObject::Collided(GameObject* otherEntity)
{
}

void GameObject::Destroy()
{
}

void GameObject::keyPressed( const OIS::KeyEvent & )
{
}

void GameObject::keyReleased( const OIS::KeyEvent & )
{
}

void GameObject::mousePressed( const OIS::MouseEvent&, OIS::MouseButtonID )
{
}

void GameObject::mouseReleased( const OIS::MouseEvent&, OIS::MouseButtonID )
{
}

void GameObject::mouseMoved( const OIS::MouseEvent & )
{
}