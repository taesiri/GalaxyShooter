#include "GalaxyShooter.h"
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

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

	// add Spacecraft
	Ogre::Entity *ent = mSceneMgr->createEntity("Spacecraft", "Spacecraft.mesh");
	Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("SpacecraftNode");
	Ogre::SceneNode *nodeShip = mSceneMgr->getSceneNode("SpacecraftNode")->createChildSceneNode("Ship");
	nodeShip->attachObject(ent);
	nodeShip->scale(Ogre::Vector3(15,15,15));

	Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create("shipmatt", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::TextureUnitState* shipture = mat->getTechnique(0)->getPass(0)->createTextureUnitState("SimpleShip.tga");
	ent->setMaterial(mat);

	Ogre::SceneNode *nodeOrigins = mSceneMgr->getRootSceneNode()->createChildSceneNode("Origins");



	Ogre::MaterialPtr astmat = Ogre::MaterialManager::getSingleton().create("astroidMatt", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::TextureUnitState* asture = astmat->getTechnique(0)->getPass(0)->createTextureUnitState("Asteroid.tga");


	// create the light
	Ogre::Light *light = mSceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_POINT);
	light->setPosition(Ogre::Vector3(0, 150, 250));
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue::White);
}

void GalaxyShooter::createFrameListener(void)
{
	BaseApplication::createFrameListener();

	// Populate the camera container
	mCamNode = mCamera->getParentSceneNode();

	// set the rotation and move speed
	mRotate = 0.13;
	mMove = 250;
	transVector = Ogre::Vector3::ZERO;
	mDirection = Ogre::Vector3::ZERO;
}
bool GalaxyShooter::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(mWindow->isClosed())
		return false;

	if(mShutDown)
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	mTrayMgr->frameRenderingQueued(evt);

	//Handle Movements

	Ogre::Vector3 vec = mSceneMgr->getSceneNode("SpacecraftNode")->getChild("Ship")->getPosition();
	Ogre::Vector3 translation = transVector * evt.timeSinceLastFrame;

	if(abs(vec.x + translation.x) < 500)
	{
		mSceneMgr->getSceneNode("SpacecraftNode")->getChild("Ship")->translate(translation, Ogre::Node::TS_LOCAL);
	}
	else
	{
	}

	UpdateGameObjects(evt);

	return true;}

// OIS::KeyListener
bool GalaxyShooter::keyPressed( const OIS::KeyEvent &arg )
{
	switch (arg.key)
	{
	case OIS::KC_ESCAPE:
		mShutDown = true;
		break;

	case OIS::KC_W:
		transVector.y = mMove;
		break;
	case OIS::KC_S:
		transVector.y -= mMove;
		break;

	case OIS::KC_D:
		transVector.x = mMove;
		break;
	case OIS::KC_A:
		transVector.x -= mMove;
		break;

	default:
		break;
	}

	return true;
}

bool GalaxyShooter::keyReleased( const OIS::KeyEvent &arg )
{
	switch (arg.key)
	{
	case OIS::KC_W:
		transVector.y = 0;
		break;
	case OIS::KC_S:
		transVector.y = 0;
		break;
	case OIS::KC_D:
		transVector.x = 0;
		break;
	case OIS::KC_A:
		transVector.x = 0;
		break;

	default:
		break;
	}
	return true;
}
// OIS::MouseListener
bool GalaxyShooter::mouseMoved( const OIS::MouseEvent &arg )
{
	if (arg.state.X.rel > 1 || arg.state.X.rel < -1)
	{
		transVector.x = 50 * arg.state.X.rel;
	}
	else
	{
		transVector.x = 0;
	}

	if (arg.state.Y.rel > 1 || arg.state.Y.rel < -1)
	{
		transVector.y = -50 * arg.state.Y.rel;
	}
	else
	{
		transVector.y = 0;
	}
	return true;
}
bool GalaxyShooter::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	Ogre::Light *light = mSceneMgr->getLight("Light1");
	switch (id)
	{
	case OIS::MB_Left:
		/*light->setVisible(! light->isVisible());*/
		Shoot();
		break;
	default:
		break;
	}
	return true;
}
bool GalaxyShooter::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}

void GalaxyShooter::Shoot()
{
	//Get Current Position of SpaceCraft;
	Ogre::Vector3 pos = mSceneMgr->getSceneNode("SpacecraftNode")->getChild("Ship")->getPosition();

	static int counter = 0;
	counter++;

	stringstream itemName;
	itemName << "astroid-" << counter;

	Ogre::Entity *ent = mSceneMgr->createEntity(itemName.str(), "ast.mesh");
	Ogre::SceneNode *node =	mSceneMgr->getSceneNode("Origins")->createChildSceneNode(itemName.str());
	node->attachObject(ent);
	node->setPosition(pos + Ogre::Vector3(0,15,0));
	node->setScale(Ogre::Vector3(.7f,.7f,.7f));

	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("astroidMatt");
	ent->setMaterial(material);


	GameObject newobject(mSceneMgr, node, itemName.str());

	sceneObjects.push_back(newobject);
}

void GalaxyShooter::UpdateGameObjects(const Ogre::FrameEvent& evt)
{
	for (vector<GameObject>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
	{
		(*i).Update(evt);
	}
}

void test(){
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