#include "GameGyrocopter.h"
#include "GameManager.h"
#include "YGEGraphicsAsset.h"
#include "YGELogger.h"
#include "YGEParticleSystem.h"
#include "GameRocket.h"
#include "YGEText.h"

GameGyrocopter::GameGyrocopter(){

	destroyed = false;

	addChild(&posBody);
	posBody.translate3d(0, -1.2, 1);
	// add a particle system
	//engineParticles = new YGEGraphics::YGEParticleSystem();
	posBody.addAsset(&engineParticles);


	// load and add the body model for the gyrocopter
	meshBody.loadFromOBJ("models/gyro_body.obj");
	posBody.addAsset(&meshBody);

	// add the top rotor
	posBody.addChild(&posRotorTop);
	posRotorTop.addAsset(&meshRotorTop);
	posRotorTop.translate3d(0,5.5,0);
	meshRotorTop.loadFromOBJ("models/gyro_rotor_top.obj");

	// add the back rotor
	posBody.addChild(&posRotorBack);
	posRotorBack.addAsset(&meshRotorBack);
	posRotorBack.translate3d(0,3,1.5);
	meshRotorBack.loadFromOBJ("models/gyro_rotor_back.obj");

	// add the h tail
	posBody.addChild(&posTailH);
	posTailH.addAsset(&meshTailH);
	posTailH.translate3d(0,1,2);
	meshTailH.loadFromOBJ("models/gyro_tail_H.obj");

	// add the v tail
	posBody.addChild(&posTailV);
	posTailV.addAsset(&meshTailV);
	posTailV.translate3d(0,3,2);
	meshTailV.loadFromOBJ("models/gyro_tail_V.obj");

	backRotorAngularVelocity = 0.0f;



	//addAsset(new YGEGraphics::YGESimpleBox());


	throttle = 100;
	tailH = 0;
	tailV = 0;
	tailX = 0;

	tailHRot = 0;
	tailVRot = 0;

	up = 0.0f;

	reload = -1;
	fireFromRight = 1;

	idleSound.setSound("sounds/prop_idle.wav");
	lowSound.setSound("sounds/prop_low.wav");
	midSound.setSound("sounds/prop_mid.wav");
	highSound.setSound("sounds/prop_high.wav");

	addAsset(&idleSound);
	addAsset(&lowSound);
	addAsset(&midSound);
	addAsset(&highSound);

	posRotorTop.addAsset(&collider);

	posRotorTop.addChild(&posColliderLeft);
	posColliderLeft.addAsset(&colliderLeft);
	posColliderLeft.translate3d(-8, 0, 0);

	posRotorTop.addChild(&posColliderRight);
	posColliderRight.addAsset(&colliderRight);
	posColliderRight.translate3d(8, 0, 0);

	collider.setRadius(1);
	collider.setCollisionListener(this);

	colliderLeft.setRadius(0.2);
	colliderLeft.setCollisionListener(this);

	colliderRight.setRadius(0.2);
	colliderRight.setCollisionListener(this);


	soundstate = -1;


	
	addAsset(&mass);
	mass.setLinearDamping(0.2 );
	mass.setAngularDamping(0.3 );
	
	mass.setSize(YGEMath::Vector3(3, 2, 4));
	mass.setMass(1);



}

void GameGyrocopter::tick(long delta){

	switch(soundstate){
		case -1:
			soundstate = 0;
			idleSound.playLooped();
			break;
			// idle
		case 0:
			if(backRotorAngularVelocity > 5.0f) {
				soundstate = 1;
				idleSound.stop();
				lowSound.playLooped();
			}
			break;
			// low
		case 1:
			if(backRotorAngularVelocity > 50.0f) {
				soundstate = 2;
				lowSound.stop();
				midSound.playLooped();
			} else if(backRotorAngularVelocity < 5.0f) {
				soundstate = 0;
				lowSound.stop();
				idleSound.playLooped();
			}

			break;
			// mid
		case 2:
			if(backRotorAngularVelocity > 80.0f) {
				soundstate = 3;
				midSound.stop();
				highSound.playLooped();
			} else if(backRotorAngularVelocity <= 50.0f) {
				soundstate = 1;
				midSound.stop();
				lowSound.playLooped();
			}

			break;
			// high
		case 3:
			if(backRotorAngularVelocity < 80.0f) {
				soundstate = 2;
				highSound.stop();
				midSound.playLooped();
			}

			break;

	}

	double seconds = delta / 1000000.0f;

	//dBodyID bodyId = mass.getBodyId();

	mass.getRelativeVelocity().z;



	//// reset the force & torque accummulators

	mass.setForce(0, 0, 0);
	mass.setTorque(0, 0, 0);

	//double up = v[2] / 10.0f;

	up += abs(mass.getRelativeVelocity().z / 3.0f * seconds);
	up -= 2.0f * seconds;

	if(up < 0.0f) {
		up = 0.0f;
	};

	if(up > 10.0f) {
		up = 10.0f;
	}

	double damp = 20.0f;
	backRotorAngularVelocity += (throttle - backRotorAngularVelocity) * seconds;
	tailHRot += (tailH - tailHRot) * seconds * 3.0f;
	tailVRot += (tailV - tailVRot) * seconds * 3.0f;


	if(!destroyed) {
	mass.addAbsoluteForce(0, up, 0);

	mass.addRelativeForce( 0, 0, -backRotorAngularVelocity * 0.6f);

	mass.addRelativeTorque(0, 0, -tailV / 100.0f);
	mass.addRelativeTorque(-tailH / 100.0f, 0, 0);
	mass.addRelativeTorque(0, -tailX / 100.0f, 0);
	}

	posRotorTop.rotateDGR(YGEMath::Vector3(0,1,0), up * seconds * 50.0f);
	posRotorBack.rotateDGR(YGEMath::Vector3(0,0,1), seconds * backRotorAngularVelocity * 20.0f);

	posTailH.setOrientation(YGEMath::Quaternion());

	posTailH.rotateDGR(YGEMath::Vector3(1,0,0), tailHRot / 100.0f * 30.0f);

	posTailV.setOrientation(YGEMath::Quaternion());

	posTailV.rotateDGR(YGEMath::Vector3(0,1,0), tailVRot / 100.0f * 30.0f);


	if(reload > 0) {
		reload -= delta;
	}

}

void GameGyrocopter::fireRocket(){
	if(reload <= 0) {
		GameRocket* rocket = new GameRocket();
		this->getParent()->addChild(rocket);
		rocket->setPosition(this->getPosition());
		//getOrientation().rotateVector(YGEMath::Vector3(3* fireFromRight,3,0));
		rocket->translate(getOrientation().rotateVector(YGEMath::Vector3(1.5f * fireFromRight,2,-8)));

		rocket->setOrientation(getOrientation());
		reload = 1000000;
		fireFromRight = fireFromRight * -1;
	} 
}


void GameGyrocopter::processCollision(YGEPhysics::YGEPhysicsAsset* bodyPart, YGEPhysics::YGEPhysicsAsset* collider){
	if( ( (YGEPhysics::YGEPhysicsAsset*)(&(this->collider)) == bodyPart  ||
		(YGEPhysics::YGEPhysicsAsset*)(&(this->colliderLeft)) == bodyPart  ||
		(YGEPhysics::YGEPhysicsAsset*)(&(this->colliderRight)) == bodyPart  )
		&& collider == NULL){
			GameManager::getInstance()->getCore()->processCommand("collision");
			//posRotorBack.addAsset(new YGEPhysics::YGEBodyAsset());

			YGEPhysics::YGEBodyAsset* rotorMass = new YGEPhysics::YGEBodyAsset();
			posRotorTop.addAsset(rotorMass);
			this->getParent()->addChild(&posRotorTop);

			posRotorTop.setPosition(posRotorTop.getAbsPosition());
			posRotorTop.setOrientation(posRotorTop.getAbsOrientation());

			
			YGEMath::Vector3 rand = YGEMath::Vector3::random(10);
			mass.addAbsoluteForce(rand.x, rand.y, rand.z);

			rand = YGEMath::Vector3::random(10);
			rotorMass->addAbsoluteForce(rand.x, rand.y, rand.z);
			rand = YGEMath::Vector3::random(10);
			rotorMass->addRelativeTorque(rand.x, rand.y, rand.z);

			destroyed = true;


	}


};
