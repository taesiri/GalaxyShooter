#include "Enemy.h"


Enemy::Enemy(Ogre::SceneManager* SceneMgr,Ogre::Node* node, Ogre::Entity* entity ) : GameObject(SceneMgr, node,entity)
{
	speed =  100;
	transVector = Ogre::Vector3(0,-1,0);
}

Enemy::~Enemy(void)
{
	
}

void Enemy::Update( const Ogre::FrameEvent&evt)
{
	objectNode->translate(speed*transVector * evt.timeSinceLastFrame,Ogre::Node::TransformSpace::TS_WORLD);
	objectNode->rotate(Ogre::Vector3(1,0,0),Ogre::Degree(1.0));
	objectNode->rotate(Ogre::Vector3(0,1,0),Ogre::Degree(0.51));

	if (objectNode->getPosition().y < -520)
		Destroy();
}

void Enemy::Destroy()
{
	GalaxyShooter::deleteList.push_back(this);
}

void Enemy::Collided( GameObject* otherObject )
{
	static int counter = 0;
	counter++;

	if (dynamic_cast<Projectile*> (otherObject)!= NULL )
	{

		stringstream itemName;
		itemName << "explosion-" << counter;

		Ogre::ParticleSystem* explosionParticle = localSceneManager->createParticleSystem(itemName.str(), "Explosion");
		Ogre::SceneNode *explosionNode =localSceneManager->getSceneNode("EnemiesNode")->createChildSceneNode(itemName.str());
		explosionNode->attachObject(explosionParticle);
		explosionNode->setPosition(objectNode->getPosition());

		ParticleController* particleCtler = new ParticleController(explosionParticle,1,localSceneManager,explosionNode, NULL);
		GalaxyShooter::NEWsceneObjects.push_back(particleCtler);

		GalaxyShooter::score+=10;

		Destroy();
		otherObject->Destroy();
	}
	else if (dynamic_cast<SpaceCraft*> (otherObject)!= NULL )
	{
		GalaxyShooter::ReduceLife();
	}
}
