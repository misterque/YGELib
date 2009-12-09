#include "GameBall.h"
#include "GameManager.h"

GameBall::GameBall(double radius, double r, double g, double b) {

	hull = new YGEPhysics::YGESimpleHullAsset();
	this->addAsset(hull);
	hull->setRadius(radius);

	mesh = new YGEGraphics::YGESimpleSphere();
	mesh->setRadius(radius);
	mesh->setColor(r, g, b);

	this->addAsset(mesh);
}


void GameBall::processCollision(YGEPhysics::YGEPhysicsAsset* bodyPart, YGEPhysics::YGEPhysicsAsset* collider){
	if(collider != NULL){
		getParent()->removeChild(this);

		GameManager::getInstance()->getCore()->processCommand("balldestroyed");
	}


};
