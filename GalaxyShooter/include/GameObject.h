#pragma once
#include <string>
#include <sstream>

#include <OgreSceneManager.h>
#include <OgreEntity.h>


using namespace std;

class GameObject{
public:
	
	static int instances;
	
	// Constructor
	GameObject(Ogre::SceneManager*,Ogre::Node*,string);

	// Fields
	string ObjectName;
	virtual void Update(const Ogre::FrameEvent&);
	
	void test();

private:
	Ogre::SceneManager* localSceneManager;
	Ogre::Node* objectNode;

};