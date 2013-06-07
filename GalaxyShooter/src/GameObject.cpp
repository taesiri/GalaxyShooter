#include "GameObject.h"

int GameObject::instances = 0;

GameObject::GameObject( Ogre::SceneManager* SceneMgr,Ogre::Node* node, string name )
{
	ObjectName = name;
	localSceneManager = SceneMgr;
	objectNode = node;
}

void GameObject::Update(const Ogre::FrameEvent& evt)
{
	float speed = 920.0f;
	objectNode->translate(Ogre::Vector3(0,evt.timeSinceLastFrame*speed,0));
}

void GameObject::test()
{

}
