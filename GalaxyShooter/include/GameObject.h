#pragma once
#include <string>
#include <sstream>

#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

using namespace std;

class GameObject{
public:
	// Constructor
	GameObject(Ogre::SceneManager*,Ogre::Node*,Ogre::Entity*);

	// Pure virtual Methods
	virtual void Update(const Ogre::FrameEvent&) = 0;
	virtual void Destroy()= 0;
	virtual void keyPressed(const OIS::KeyEvent &) = 0;
	virtual void keyReleased(const OIS::KeyEvent &) = 0;
	virtual void mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID) = 0;
	virtual void mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID) = 0;
	virtual void mouseMoved(const OIS::MouseEvent &) = 0;

	// Virtual Methods
	virtual void Translate(Ogre::Vector3);

protected:
	Ogre::SceneManager* localSceneManager;
	Ogre::Entity* objectEntity;
	Ogre::Node* objectNode;

	static int instances;
private:
};