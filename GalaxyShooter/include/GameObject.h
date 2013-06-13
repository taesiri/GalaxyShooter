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
	virtual void Update(const Ogre::FrameEvent&);
	virtual void Destroy();
	virtual void keyPressed(const OIS::KeyEvent &);
	virtual void keyReleased(const OIS::KeyEvent &);
	virtual void mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
	virtual void mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);
	virtual void mouseMoved(const OIS::MouseEvent &);

	// Virtual Methods
	virtual void Translate(Ogre::Vector3);
	virtual ~GameObject();
	virtual Ogre::Vector3* getGlobalBoundaries();

	virtual void Collided(GameObject*);
	virtual bool IsCollided (GameObject*);

public:
	Ogre::SceneManager* localSceneManager;
	Ogre::Entity* objectEntity;
	Ogre::Node* objectNode;
	bool isPhysicsEnabled;

	static int instances;
private:
	
};