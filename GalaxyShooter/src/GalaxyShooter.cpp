#include "GalaxyShooter.h"
#include <sstream>
#include <string>
#include <cmath>
#include <time.h>

#include "DebugDrawer.h"

using namespace std;

vector<GameObject*> GalaxyShooter::NEWsceneObjects;
vector<GameObject*> GalaxyShooter::deleteList;

int GalaxyShooter::score = 0;
int GalaxyShooter::lives = 3;
//-------------------------------------------------------------------------------------
GalaxyShooter::GalaxyShooter(void) : isPlaying(true), isLost(false)
{
	srand (time(NULL));


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
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);

	// Spacecraft
	Ogre::Entity *spaceCraftEntity = mSceneMgr->createEntity("Spacecraft", "Spacecraft.mesh");
	Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("SpacecraftNode");
	Ogre::SceneNode *nodeShip = mSceneMgr->getSceneNode("SpacecraftNode")->createChildSceneNode("Ship");
	nodeShip->attachObject(spaceCraftEntity);
	nodeShip->scale(Ogre::Vector3(14,14,14));
	nodeShip->setPosition(Ogre::Vector3(0,0,-10));

	Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create("shipmatt", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::TextureUnitState* shipture = mat->getTechnique(0)->getPass(0)->createTextureUnitState("SimpleShip.tga");
	spaceCraftEntity->setMaterial(mat);

	SpaceCraft* myCraft = new SpaceCraft(mSceneMgr,nodeShip,spaceCraftEntity);
	sceneObjects.push_back(myCraft);
	// Spacecraft

	// Create Scene Nodes
	mSceneMgr->getSceneNode("SpacecraftNode")->createChildSceneNode("ProjectilesNode");
	Ogre::SceneNode *nodeOrigins = mSceneMgr->getRootSceneNode()->createChildSceneNode("EnvironmentNode");
	mSceneMgr->getSceneNode("EnvironmentNode")->createChildSceneNode("EnemiesNode");
	// Create Scene Nodes

	//Create Some Materials!
	Ogre::MaterialPtr astmat = Ogre::MaterialManager::getSingleton().create("astroidMatt", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::TextureUnitState* asture = astmat->getTechnique(0)->getPass(0)->createTextureUnitState("Asteroid.tga");

	Ogre::MaterialPtr prjMat = Ogre::MaterialManager::getSingleton().create("projectileMatt", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::TextureUnitState* Prjture = prjMat->getTechnique(0)->getPass(0)->createTextureUnitState("Plasma02.jpg");

	Ogre::MaterialPtr BackgrounMattSmall = Ogre::MaterialManager::getSingleton().create("StarsSmall", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::TextureUnitState* BackgrounMattSmallTexture = BackgrounMattSmall->getTechnique(0)->getPass(0)->createTextureUnitState("Stars.png");

	Ogre::MaterialPtr BackgrounMattLarge = Ogre::MaterialManager::getSingleton().create("StarsLarge", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::TextureUnitState* BackgrounMattLargeTexture = BackgrounMattLarge->getTechnique(0)->getPass(0)->createTextureUnitState("Stars_large.png");
	//Create Some Materials!

	// Background
	Ogre::Plane plane(Ogre::Vector3::UNIT_Z, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 2024, 2024, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);

	/*Ogre::MeshManager::getSingleton().createPlane("",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,,,,,,*/

	Ogre::Entity* backgroundEntity1 = mSceneMgr->createEntity("BackGround1", "ground");
	Ogre::Entity* backgroundEntity2 = mSceneMgr->createEntity("BackGround2", "ground");

	Ogre::SceneNode *nodePlane1 = mSceneMgr->getSceneNode("EnvironmentNode")->createChildSceneNode("BackgroundStars1Node");
	Ogre::SceneNode *nodePlane2 = mSceneMgr->getSceneNode("EnvironmentNode")->createChildSceneNode("BackgroundStars2Node");

	nodePlane1->attachObject(backgroundEntity1);
	nodePlane2->attachObject(backgroundEntity2);

	backgroundEntity1->setMaterialName("StarsLarge");
	backgroundEntity1->setCastShadows(false);

	backgroundEntity2->setMaterialName("StarsSmall");
	backgroundEntity2->setCastShadows(false);

	nodePlane1->translate(Ogre::Vector3(0,0,-200));
	nodePlane2->translate(Ogre::Vector3(0,2000,-198));

	Starfield* fieldOfStars1 = new Starfield(mSceneMgr,nodePlane1, backgroundEntity1);
	Starfield* fieldOfStars2 = new Starfield(mSceneMgr,nodePlane2, backgroundEntity2);

	sceneObjects.push_back(fieldOfStars1);
	sceneObjects.push_back(fieldOfStars2);

	// Background

	// JetEngine Particle
	Ogre::ParticleSystem* pSys2 = mSceneMgr->createParticleSystem("jetEngineParticle", "Examples/SpaceCraftParticle");
	Ogre::SceneNode* fNode = nodeShip->createChildSceneNode();
	fNode->attachObject(pSys2);
	fNode->translate(Ogre::Vector3(0, -4.9f,0));

	// Lights
	Ogre::Light *light1 = mSceneMgr->createLight("SceneLight1");
	light1->setType(Ogre::Light::LT_POINT);
	light1->setPosition(Ogre::Vector3(50, 0, 150));
	light1->setDiffuseColour(Ogre::ColourValue::White);
	light1->setSpecularColour(Ogre::ColourValue::Red);

	Ogre::Light *light2 = mSceneMgr->createLight("SceneLight2");
	light2->setType(Ogre::Light::LT_POINT);
	light2->setPosition(Ogre::Vector3(-50, 0, 150));
	light2->setDiffuseColour(Ogre::ColourValue::Black);
	light2->setSpecularColour(Ogre::ColourValue::Blue);
	// Lights

	// Initialize the DebugDrawer singleton
	//new DebugDrawer(mSceneMgr, 0.5f);
}

void GalaxyShooter::destroyScene( void )
{
	// Destroy DebugDrawer
	delete DebugDrawer::getSingletonPtr();
}

void GalaxyShooter::createFrameListener(void)
{
	BaseApplication::createFrameListener();

	// Populate the camera container
	mCamNode = mCamera->getParentSceneNode();
	mDirection = Ogre::Vector3::ZERO;

	stringstream stringHelper;
	stringHelper << "Score : " << score;

	scoreBoardLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "ScoreBoard", Ogre::DisplayString(stringHelper.str()), 250.0f);

	stringHelper.str("");
	stringHelper << "Lives : " << lives;

	livesBoard = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "LivesBoard", Ogre::DisplayString(stringHelper.str()), 250.0f);
	menuLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "MainMenuLable", Ogre::DisplayString("-- Main Menu --"), 250.0f);

	replayBtn = mTrayMgr->createButton(OgreBites::TL_CENTER, "ReplayBtn", "Play again",250.0f);
	exitBtn = mTrayMgr->createButton(OgreBites::TL_CENTER, "Exitbtn", "Exit Game",250.0f);

	menuLabel->hide();
	replayBtn->hide();
	exitBtn->hide();
	
	mTrayMgr->getTrayContainer(OgreBites::TL_CENTER)->hide();
}

bool GalaxyShooter::frameStarted( const Ogre::FrameEvent& evt )
{
	//for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
	//{
	//	auto corners = (*i)->objectEntity->getBoundingBox().getAllCorners();
	//	auto pos = (*i)->objectNode->getPosition();

	//	Ogre::Vector3 *vecs = new Ogre::Vector3[8];
	//	vecs[0] = corners[0] + pos;
	//	vecs[1] = corners[1] + pos;
	//	vecs[2] = corners[2] + pos;
	//	vecs[3] = corners[3] + pos;
	//	vecs[4] = corners[4] + pos;
	//	vecs[5] = corners[5] + pos;
	//	vecs[6] = corners[6] + pos;
	//	vecs[7] = corners[7] + pos;

	//	auto result = (*i)->getGlobalBoundaries();

	//	//DebugDrawer::getSingleton().drawCuboid(vecs, Ogre::ColourValue::Blue, true);
	//}

	// Right before the frame is rendered, call DebugDrawer::build().
	//DebugDrawer::getSingleton().build();
	return true;
}

bool GalaxyShooter::frameEnded( const Ogre::FrameEvent& evt )
{
	// After the frame is rendered, call DebugDrawer::clear()
	//DebugDrawer::getSingleton().clear();
	return true;
}

bool GalaxyShooter::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	// Add new Items
	sceneObjects.insert( sceneObjects.end(), NEWsceneObjects.begin(), NEWsceneObjects.end() );
	NEWsceneObjects.clear();

	// Destroy unwanted Objects
	for (int i = 0; i < deleteList.size();i++)
	{
		for (int j = 0; j <sceneObjects.size();)
		{
			if (sceneObjects[j] == deleteList[i])
			{
				delete sceneObjects.at(j);
				sceneObjects.erase(sceneObjects.begin() + j);
				break;
			}
			else
				j++;
		}
	}

	deleteList.clear();

	if(mWindow->isClosed())
		return false;

	if(mShutDown)
		return false;

	mKeyboard->capture();
	mMouse->capture();

	mTrayMgr->frameRenderingQueued(evt);

	if (isPlaying){
		UpdateGameObjects(evt);
		CheckCollisions();
		UpdateStats(evt);
	}

	return true;
}

// OIS::KeyListener
bool GalaxyShooter::keyPressed( const OIS::KeyEvent &arg )
{
	switch (arg.key)
	{
	case OIS::KC_ESCAPE:
		if(isPlaying && !isLost)
		{
			menuLabel->setCaption("-- Main Menu --");
			showMainMenu();
		}
		else if (!isPlaying && !isLost)
		{
			hideMainMenu();
		}
		//mShutDown = true;
		break;
	default:
		break;
	}

	if (isPlaying){
		for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
		{
			(*i)->keyPressed(arg);
		}
	}

	return true;
}

bool GalaxyShooter::keyReleased( const OIS::KeyEvent &evt )
{
	if (isPlaying){
		for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
		{
			(*i)->keyReleased(evt);
		}
	}

	return true;
}
// OIS::MouseListener
bool GalaxyShooter::mouseMoved( const OIS::MouseEvent &evt )
{
	if (isPlaying){
		for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
		{
			(*i)->mouseMoved(evt);
		}
	}
	if (!isPlaying){
		if (mTrayMgr->injectMouseMove(evt)) return true;
	}

	return true;
}
bool GalaxyShooter::mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
{
	if (isPlaying){

		for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
		{
			(*i)->mousePressed(evt,id);
		}

		switch (id){
		case OIS::MB_Left :
			RespawnEnemy();
			break;
		default:
			break;
		}
	}
	if (!isPlaying){
		 if (mTrayMgr->injectMouseDown(evt, id)) return true;
	}
	return true;
}
bool GalaxyShooter::mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
{
	if (isPlaying){
		for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
		{	
			(*i)->mouseReleased(evt,id);
		}
	}
	if (!isPlaying){
		if (mTrayMgr->injectMouseUp(evt, id)) return true;
	}
	return true;
}

void GalaxyShooter::UpdateGameObjects(const Ogre::FrameEvent& evt)
{	
	if (isPlaying){
		for (vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); i++)
		{
			(*i)->Update(evt);
		}
	}
}

void GalaxyShooter::RespawnEnemy()
{
	static int counter = 0;
	counter++;
	stringstream itemName;
	itemName << "enemy-" << counter;

	// Randomize Position

	int _x = rand() % 1000 + -500;
	int _y = 480;

	float _xS = ((rand() % 30)/10.0f)  + 1;
	float _yS = ((rand() % 30 )/10.0f) + 1;
	float _zS = ((rand() % 30)/10.0f)  + 1;
	//

	Ogre::Entity *enemyEntity = mSceneMgr->createEntity(itemName.str(), "ast.mesh");

	auto box = enemyEntity->getBoundingBox();

	auto sizeOfBox = box.getSize();
	auto centerOfBox = box.getCenter();

	Ogre::SceneNode *enemyNode =	mSceneMgr->getSceneNode("EnemiesNode")->createChildSceneNode(itemName.str());
	enemyNode->attachObject(enemyEntity);
	enemyNode->setPosition(Ogre::Vector3(_x,_y,0));
	enemyNode->setScale(Ogre::Vector3(_xS,_yS,_zS));

	auto Sclaedbox = enemyEntity->getBoundingBox();

	auto  SclaedsizeOfBox = box.getSize();
	auto  SclaedcenterOfBox = box.getCenter();

	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("astroidMatt");
	enemyEntity->setMaterial(material);

	Enemy* newEnemy = new Enemy(mSceneMgr,enemyNode ,enemyEntity);
	GalaxyShooter::NEWsceneObjects.push_back(newEnemy);
}

void GalaxyShooter::CheckCollisions()
{
	for (int i = 0; i< sceneObjects.size(); i++)
	{
		for (int j = i + 1; j < sceneObjects.size(); j++)
		{
			if ( sceneObjects[i]->IsCollided(sceneObjects[j]))
			{
			}
		}
	}
}

void GalaxyShooter::UpdateStats( const Ogre::FrameEvent& )
{
	stringstream stringHelper;
	stringHelper << "Score : " << score;

	scoreBoardLabel->setCaption(stringHelper.str());
	stringHelper.str("");
	stringHelper << "Lives : " << lives;

	livesBoard->setCaption(stringHelper.str());

	if(lives == 0)
	{
		Lose();
	}
	if (score >= 100){
		Win();
	}
}

void GalaxyShooter::ReduceLife()
{
	lives--;
}

void GalaxyShooter::Lose()
{
	// Stop the GAME
	menuLabel->setCaption("-- Game OVER! --");
	showMainMenu();
}

void GalaxyShooter::Win()
{
	menuLabel->setCaption("-- You WON! --");
	showMainMenu();
}

void GalaxyShooter::buttonHit(OgreBites::Button* b)
{
	if (b->getName() == "Exitbtn"){
		mShutDown = true;
	} else
	if ( b->getName() == "ReplayBtn" ){
		
		hideMainMenu();
		
		lives = 3;
		score = 0;
	}
}

void GalaxyShooter::showMainMenu()
{
	isPlaying = false;
	menuLabel->show();
	replayBtn->show();
	exitBtn->show();
	mTrayMgr->showCursor();
	mTrayMgr->getTrayContainer(OgreBites::TL_CENTER)->show();
}

void GalaxyShooter::hideMainMenu()
{
	isPlaying=true;
	menuLabel->hide();
	replayBtn->hide();
	exitBtn->hide();
	mTrayMgr->getTrayContainer(OgreBites::TL_CENTER)->hide();
	mTrayMgr->hideCursor();
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