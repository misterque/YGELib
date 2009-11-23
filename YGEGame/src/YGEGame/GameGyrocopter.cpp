#include "GameGyrocopter.h"

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


	addAsset(&mass);



}

void GameGyrocopter::update(){

	posRotorTop.rotateDGR(YGEMath::Vector3(0,1,0), 1.0f);

}