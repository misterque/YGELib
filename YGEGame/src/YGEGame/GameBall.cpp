#include "GameBall.h"
#include "GameManager.h"

GameBall::GameBall() {

	hull = new YGEPhysics::YGESimpleHullAsset();
	this->addAsset(hull);

	mesh = new YGEGraphics::YGESimpleSphere();
	mesh->setRadius(10.0f);

	this->addAsset(mesh);
}


void GameBall::processCollision(YGEPhysics::YGEPhysicsAsset* bodyPart, YGEPhysics::YGEPhysicsAsset* collider){
	if(collider != NULL){
		getParent()->removeChild(this);
	}

	GameManager::getInstance()->getCore()->processCommand("balldestroyed");

};
