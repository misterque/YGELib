#include "GameGyrocopter.h"
#include "YGEGraphicsAsset.h"
#include "YGELogger.h"

#include "GameRocket.h"
#include "YGEText.h"

GameGyrocopter::GameGyrocopter(){

	// load and add the body model for the gyrocopter
	meshBody.loadFromOBJ("models/gyro_body.obj");
	addAsset(&meshBody);

	// add the top rotor
	addChild(&posRotorTop);
	posRotorTop.addAsset(&meshRotorTop);
	posRotorTop.translate3d(0,5.5,0);
	meshRotorTop.loadFromOBJ("models/gyro_rotor_top.obj");

	// add the back rotor
	addChild(&posRotorBack);
	posRotorBack.addAsset(&meshRotorBack);
	//posRotorBack.translate3d(0,1,-1);
	//posRotorBack.rotateDGR(YGEMath::Vector3(1,0,0), 90);
	meshRotorBack.loadFromOBJ("models/gyro_rotor_back.obj");



	//addAsset(new YGEGraphics::YGESimpleBox());
	addAsset(&mass);

	
	throttle = 0;
	tailH = 0;
	tailV = 0;
	tailX = 0;

	up = 0.0f;

	reload = -1;
	fireFromRight = 1;


}

void GameGyrocopter::tick(long delta){



	double seconds = delta / 1000000.0f;

	dBodyID bodyId = mass.getBodyId();

	mass.getRelativeVelocity().z;

	dBodySetLinearDamping(bodyId, 0.03);
	dBodySetAngularDamping(bodyId, 0.1);


	//double up = v[2] / 10.0f;

	up += abs(mass.getRelativeVelocity().z / 3.0f * seconds);
	up -= 2.0f * seconds;
	debugout(mass.getRelativeVelocity().z);
	//debugout(mass.getRelativeVelocity().z);

	if(up < 0.0f) {
		up = 0.0f;
	};
	if(up > 10.0f) {
		up = 10.0f;
	}

	mass.addAbsoluteForce(0, up, 0);
	//	dBodyAddRelForceAtRelPos(bodyId,
	//		0, up, 0,
	//		0, 4, 0);
	/*
	dBodyAddRelForceAtRelPos(bodyId,
	tailV / 100.0f * 3.0f, 0, 0,
	0, 0, 4);

	dBodyAddForceAtRelPos(bodyId,
	0, tailH / 100.0f * 3.0f, 0,
	0, 0, 4);*/

	mass.addRelativeForce( 0, 0, -throttle * 0.2f);



	//z.rotateBy(q);



	//const double* pos = dBodyGetPosition(bodyId);

	//	d[0] -= pos[0];
	//	d[1] -= pos[1];
	//	d[2] -= pos[2];

	//dBodyAddForce(bodyId, d[0] * throttle, d[1] * throttle, d[2] * throttle);

	//mass.addRelativeForce(0,0,-throttle * 1.0f);
	//	mass.addRelativeForce(0,tailH / 200.0f, 0);
	/*debugout(d[0]);
	debugout(d[1]);
	debugout(d[2]);
	debugout(d[3]);
	debugout("---");
	*/
	mass.addRelativeTorque(0, 0, -tailV / 400.0f);
	mass.addRelativeTorque(-tailH / 400.0f, 0, 0);
	mass.addRelativeTorque(0, -tailX / 400.0f, 0);
	//dBod

	posRotorTop.rotateDGR(YGEMath::Vector3(0,1,0), up * seconds * 50.0f);

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
		rocket->translate(getOrientation().rotateVector(YGEMath::Vector3(2 * fireFromRight,1,0)));

		rocket->setOrientation(getOrientation());
		reload = 1000000;
		fireFromRight = fireFromRight * -1;
	} 
}