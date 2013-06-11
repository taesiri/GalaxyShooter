#include "GalaxyShooter.h"
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

vector<GameObject*> GalaxyShooter::NEWsceneObjects;

//-------------------------------------------------------------------------------------
GalaxyShooter::GalaxyShooter(void)
{
}

//-------------------------------------------------------------------------------------
GalaxyShooter::~GalaxyShooter(void)
{
}

//-------------------------------------------------------------------------------------
void GalaxyShooter::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("PlayerCamera");

	// set projection type
	mCamera->setProjectionType(Ogre::ProjectionType::PT_ORTHOGRAPHIC);

	mCamera->setOrthoWindowHeight(Ogre::Real(ORTHOGRAPHIC_SIZE));

	mCamera->setPosition(Ogre::Vector3(0,0,1000));

	mCamera->lookAt(Ogre::Vector3(0,0,0));

	// set the near clip distance
	mCamera->setNearClipDistance(NEAR_CLIP_DISTANCE);

	mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}
//-------------------------------------------------------------------------------------
void GalaxyShooter::createViewports(void)
{
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,1,1));

	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

//-------------------------------------------------------------------------------------
void GalaxyShooter::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));

	// Spacecraft
	Ogre::Entity *spaceCraftEntity = mSceneMgr->createEntity("Spacecraft", "Spacecraft.mesh");
	Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("SpacecraftNode");
	Ogre::SceneNode *nodeShip = mSceneMgr->getSceneNode("SpacecraftNode")->createChildSceneNode("Ship");
	nodeShip->attachObject(spaceCraftEntity);
	nodeShip->scale(Ogre::Vector3(14,14,14));

	Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create("shipmatt", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::TextureUnitState* shipture = mat->getTechnique(0)->getPass(0)->createTextureUnitState("SimpleShip.tga");
	spaceCraftEntity->setMaterial(mat);

	SpaceCraft* myCraft = new SpaceCraft(mSceneMgr,nodeShip,spaceCraftEntity);
	sceneObjects.push_back(myCraft);
	// Spacecraft

	// Create Scene Nodes
	mSceneMgr->getSceneNode("SpacecraftNode")->createChildSceneNode("Projectiles");
	Ogre::SceneNode *nodeOrigins = mSceneMgr->getRootSceneNode()->createChildSceneNode("Environment");
	// Create Scene Nodes

	//Create Some Materials!
	Ogre::MaterialPtr astmat = Ogre::MaterialManager::getSingleton().create("astroidMatt", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::TextureUnitState* asture = astmat->getTechnique(0)->getPass(0)->createTextureUnitState("Asteroid.tga");
	//Create Some Materials!

	// Background
	Ogre::Plane plane(Ogre::Vector3::UNIT_Z, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);

	//Ogre::MeshManager::getSingleton().createPlane("",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane)
	Ogre::Entity* backgroundEntity = mSceneMgr->createEntity("BackGround", "ground");
	Ogre::SceneNode *nodePlane= mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodePlane->attachObject(backgroundEntity);
	backgroundEntity->setMaterialName("Examples/Rockwall");
	backgroundEntity->setCastShadows(false);
	nodePlane->translate(Ogre::Vector3(100,20,-200));

	//GameObject* background = new GameObject(mSceneMgr,nodePlane, backgroundEntity);
	//sceneObjects.push_back(background);

	// Background

	// Lights
	Ogre::Light *light = mSceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_POINT);
	light->setPosition(Ogre::Vector3(0, 150, 250));
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue::White);
	// Lights
}

void GalaxyShooter::createFrameListener(void)
{
	BaseApplication::createFrameListener();

	// Populate the camera container
	mCamNode = mCamera->getParentSceneNode();
	mDirection = Ogre::Vector3::ZERO;
}
bool GalaxyShooter::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

	sceneObjects.insert( sceneObjects.end(), NEWsceneObjects.begin(), NEWsceneObjects.end() );
	NEWsceneObjects.clear();

	if(mWindow->isClosed())
		return false;

	if(mShutDown)
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	mTrayMgr->frameRenderingQueued(evt);

	//Handle Movements

	UpdateGameObjects(evt);

	return true;
}

// OIS::KeyListener
bool GalaxyShooter::keyPressed( const OIS::KeyEvent &arg )
{
	switch (arg.key)
	{
	case OIS::KC_ESCAPE:
		mShutDown = true;
		break;
	default:
		break;
	}

	for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
	{
		(*i)->keyPressed(arg);
	}

	return true;
}

bool GalaxyShooter::keyReleased( const OIS::KeyEvent &arg )
{
	for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
	{
		(*i)->keyReleased(arg);
	}

	return true;
}
// OIS::MouseListener
bool GalaxyShooter::mouseMoved( const OIS::MouseEvent &arg )
{
	for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
	{
		(*i)->mouseMoved(arg);
	}

	return true;
}
bool GalaxyShooter::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
	{
		(*i)->mousePressed(arg,id);
	}
	return true;
}
bool GalaxyShooter::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
	{
		(*i)->mouseReleased(arg,id);
	}

	return true;
}

void GalaxyShooter::UpdateGameObjects(const Ogre::FrameEvent& evt)
{
	for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
	{
		(*i)->Update(evt);
	}
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
	int main(int argc, char *argv[])
#endif
	{
		// Create application object
		GalaxyShooter app;

		try {
			app.go();
		} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif