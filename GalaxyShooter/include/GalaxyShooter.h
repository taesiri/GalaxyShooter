#ifndef __GalaxyShooter_h_
#define __GalaxyShooter_h_

#include "BaseApplication.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

#include <vector>
#include "GameObject.h"
#include "SpaceCraft.h"

class GalaxyShooter : public BaseApplication
{
public:
	GalaxyShooter(void);
	virtual ~GalaxyShooter(void);

private:
	// Game Private Static Constants;
	static const int ORTHOGRAPHIC_SIZE = 850;
	static const int NEAR_CLIP_DISTANCE = 10;

	public:
	void UpdateGameObjects(const Ogre::FrameEvent&);
	vector<GameObject*> sceneObjects;
	static vector<GameObject*> NEWsceneObjects;
protected:

	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createFrameListener(void);

	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

	Ogre::SceneNode *mCamNode;   // The SceneNode the camera is currently attached to
	Ogre::Vector3 mDirection;     // Value to move in the correct direction
	
	//friend class GameObject;
};

#endif // #ifndef __GalaxyShooter_h_
