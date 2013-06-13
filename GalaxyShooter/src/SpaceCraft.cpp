#include "SpaceCraft.h"

SpaceCraft::SpaceCraft(Ogre::SceneManager* SceneMgr,Ogre::Node* node, Ogre::Entity* entity ) : GameObject(SceneMgr, node,entity)
{
	mRotate = 0.13;
	mMove = 250;
	transVector = Ogre::Vector3::ZERO;
}

SpaceCraft::~SpaceCraft(void)
{
}

void SpaceCraft::Update( const Ogre::FrameEvent& evt)
{
	// Handle Updates Here
	Ogre::Vector3 vec = objectNode->getPosition();
	Ogre::Vector3 translation = transVector * evt.timeSinceLastFrame;

	if((vec.x + translation.x < 550) &&(vec.x + translation.x > -550) && (vec.y + translation.y < 390)&&(vec.y + translation.y > -365))
	{
		objectNode->translate(translation, Ogre::Node::TS_LOCAL);
	}
	else
	{
	}
}

void SpaceCraft::Destroy()
{
	// Destroy the GameObject
}

void SpaceCraft::keyPressed( const OIS::KeyEvent &arg)
{
	switch (arg.key)
	{
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
}

void SpaceCraft::keyReleased( const OIS::KeyEvent &arg)
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
}

void SpaceCraft::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	switch (id)
	{
	case OIS::MB_Left:
		Shoot();
		break;
	default:
		break;
	}
}

void SpaceCraft::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
}

void SpaceCraft::mouseMoved(const OIS::MouseEvent &arg)
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
}

void SpaceCraft::Shoot()
{
	static int counter = 0;
	counter++;
	stringstream itemName;
	itemName << "astroid-" << counter;

	//Get Current Position of SpaceCraft;
	Ogre::Vector3 pos = objectNode->getPosition();

	Ogre::Entity *projectileEntity = localSceneManager->createEntity(itemName.str(), "ast.mesh");
	Ogre::SceneNode *projectileNode =	localSceneManager->getSceneNode("ProjectilesNode")->createChildSceneNode(itemName.str());
	projectileNode->attachObject(projectileEntity);
	projectileNode->setPosition(pos + Ogre::Vector3(0,16,11));
	projectileNode->setScale(Ogre::Vector3(.7f,.7f,.7f));

	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("projectileMatt");
	projectileEntity->setMaterial(material);

	Projectile* prjc = new Projectile(localSceneManager,projectileNode ,projectileEntity);
	GalaxyShooter::NEWsceneObjects.push_back(prjc);
}

void SpaceCraft::Collided( GameObject* otherObject )
{
	static int counter = 0;
	counter++;

	if (dynamic_cast<Enemy*> (otherObject)!= NULL )
	{
		GalaxyShooter::ReduceLife();

		stringstream itemName;
		itemName << "Ship-explosion-" << counter;

		otherObject->Destroy();

		Ogre::ParticleSystem* explosionParticle = localSceneManager->createParticleSystem(itemName.str(), "Explosion");
		Ogre::SceneNode *explosionNode =localSceneManager->getSceneNode("EnemiesNode")->createChildSceneNode(itemName.str());
		explosionNode->attachObject(explosionParticle);
		explosionNode->setPosition(objectNode->getPosition());

		ParticleController* particleCtler = new ParticleController(explosionParticle,1,localSceneManager,objectNode, NULL);
		GalaxyShooter::NEWsceneObjects.push_back(particleCtler);
	}
}