#include "GameObject.h"

int GameObject::instances = 0;

GameObject::GameObject(Ogre::SceneManager* SceneMgr,Ogre::Node* node, Ogre::Entity* entity )
{
	objectEntity = entity;
	localSceneManager = SceneMgr;
	objectNode = node;
}

void GameObject::Update(const Ogre::FrameEvent& evt)
{
}

void GameObject::Translate( Ogre::Vector3 translateVector)
{
}