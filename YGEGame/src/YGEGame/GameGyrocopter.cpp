#include "GameGyrocopter.h"
#include "YGEGraphicsAsset.h"
#include "YGELogger.h"

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



	addAsset(new YGEGraphics::YGESimpleBox());
	addAsset(&mass);

	throttle = 0;
	tailH = 0;
	tailV = 0;

	up = 5.81f;


}

void GameGyrocopter::tick(long delta){



	double seconds = delta / 1000000.0f;
	
	dBodyID bodyId = mass.getBodyId();

	const double* v = dBodyGetLinearVel(bodyId);

	dBodySetLinearDamping(bodyId, 0.1);
    
	//double up = v[2] / 10.0f;

		//mass.addRelativeForce(0, up, 0);
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

	//dBodyAddRelForce(bodyId, 0, throttle*0.1, -throttle);

	dReal d[4];

	dBodyGetRelPointPos(bodyId, -1, 0, 0, d);

	const double* pos = dBodyGetPosition(bodyId);

	d[0] -= pos[0];
	d[1] -= pos[1];
	d[2] -= pos[2];

	dBodyAddForce(bodyId, d[0] * throttle, d[1] * throttle, d[2] * throttle);

	//mass.addRelativeForce(0,0,-throttle * 1.0f);
//	mass.addRelativeForce(0,tailH / 200.0f, 0);
	debugout(d[0]);
	debugout(d[1]);
	debugout(d[2]);
	debugout("---");

	mass.addRelativeTorque(0, 0, tailV / 1000.0f);
	mass.addRelativeTorque(tailH / 1000.0f, 0, 0);

	//dBod

	posRotorTop.rotateDGR(YGEMath::Vector3(0,1,0), up * seconds * 50.0f);

}