#ifndef __GalaxyShooter_h_
#define __GalaxyShooter_h_

#include "BaseApplication.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

#include <vector>
#include "GameObject.h"
#include "SpaceCraft.h"
#include "Enemy.h"
#include "Starfield.h"
#include "ParticleController.h"

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
	//Public Methods

	void UpdateGameObjects(const Ogre::FrameEvent&);
	void UpdateStats(const Ogre::FrameEvent&);
	void CheckCollisions();

	void Lose();
	void Win();

	void showMainMenu();
	void hideMainMenu();

	bool isPlaying;
	bool isLost;

	void RespawnEnemy();

	vector<GameObject*> sceneObjects;

	static vector<GameObject*> NEWsceneObjects;
	static vector<GameObject*> deleteList;

	static int score;
	static int lives;

	static void ReduceLife();

protected:

	virtual void createScene(void);
	virtual void destroyScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createFrameListener(void);

	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual bool frameEnded(const Ogre::FrameEvent& evt);

	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );


	virtual void buttonHit(OgreBites::Button*);

	Ogre::SceneNode *mCamNode;   // The SceneNode the camera is currently attached to
	Ogre::Vector3 mDirection;     // Value to move in the correct direction

	OgreBites::Label* scoreBoardLabel; // Scoreboard
	OgreBites::Label* livesBoard; // Player Lives board


	OgreBites::Label* menuLabel; // Main Menu Label

	OgreBites::Button* replayBtn;
	OgreBites::Button* exitBtn;

};

#endif // #ifndef __GalaxyShooter_h_
