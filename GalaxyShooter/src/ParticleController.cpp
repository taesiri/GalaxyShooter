#include "ParticleController.h"

ParticleController::ParticleController(Ogre::ParticleSystem* particleSystem, float lifeScale , Ogre::SceneManager* SceneMgr,Ogre::Node* node, Ogre::Entity* entity ) : GameObject(SceneMgr, node,entity)
{
	particle = particleSystem;
	lifeTime = lifeScale;
	isEnable =true;
	isPhysicsEnabled= false;
}

ParticleController::~ParticleController(void)
{
}

void ParticleController::Update( const Ogre::FrameEvent& evt)
{
	if (isEnable){
		lifeTime-= (1*evt.timeSinceLastEvent);
		if (lifeTime <= 0){
			Destroy();
		}
	}
}

void ParticleController::Destroy()
{
	particle->setEmitting(false);
	isEnable= false;

	GalaxyShooter::deleteList.push_back(this);
}


bool ParticleController::IsCollided( GameObject* otherObject )
{
		return false;
}
