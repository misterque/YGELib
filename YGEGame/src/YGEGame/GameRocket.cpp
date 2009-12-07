#include "GameRocket.h"
#include "YGEParticleSystem.h"

GameRocket::GameRocket(){
	// add the body
	addAsset(&body);
	// add the mesh
	meshRocket = new YGEGraphics::YGESimpleBox();
	addAsset(meshRocket);

	addAsset(&explosion);
	addAsset(&trail);
	explosion.disable();

	engineSound = new YGEAudio::YGESoundAsset();
	engineSound->setSound("sounds/rocket.wav");
	addAsset(engineSound);
	engineSound->playOnce();

	//@todo add the particle system

	lifetime = 0;

}

void GameRocket::tick(long delta){

	lifetime += delta / 1000000.0f;
	//unaffect the rocket by gravity
	body.addAbsoluteForce(0, 0.81f, 0);

	//thrust the rocket!
	body.addRelativeForce(0,0,-100.0f);

		//dBodySetLinearDamping(body.getBodyId(), 0.01);

		if(lifetime > 6) {
			body.disable();
			getParent()->removeChild(this);
			//delete this;
			return;
		}
}

void GameRocket::processCollision(YGEPhysics::YGEPhysicsAsset* bodyPart, YGEPhysics::YGEPhysicsAsset* collider){
	
	explode();
	
};

void GameRocket::explode(){
	body.disable();

	trail.disable();

	meshRocket->disable();

	engineSound->stop();
	YGEAudio::YGESoundAsset* sound = new YGEAudio::YGESoundAsset();
	sound->setSound("sounds/explosion.wav");
	addAsset(sound);
	sound->playOnce();


	//explosion.

}