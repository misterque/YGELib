#include "GameStates.h"
#include "YGEStaticMesh.h"
#include "YGEMassAsset.h"

GameStateX::GameStateX(){
	space = new YGESpace();

	space->initTime();

	YGEEntity* boxPos = new YGEEntity();

	gyro = new GameGyrocopter();

	boxPos->addChild(gyro);

	smallBoxPos = new YGEEntity();
	YGESimpleBox* smallBox = new YGESimpleBox();

	YGEMath::Vector3 pos;
	pos.x = 0;
	pos.y = 0;
	pos.z = -10;
	boxPos->setPosition(pos);

	YGEMath::Vector3 pos2;
	pos2.x = 4;
	pos2.y = 0;
	pos2.z = 0;

	YGEMath::Vector3 scale;
	scale.x = 0.5;
	scale.y = 0.5;
	scale.z = 0.5;

	YGEMath::Quaternion q;
	q.x = 0;
	q.y = 1;
	q.z = 0;
	q.w = 0;

	smallBoxPos->setPosition(pos2);
	smallBoxPos->setScale(scale);
	smallBoxPos->setOrientation(q );

	smallBoxPos->addAsset(smallBox);

	YGEPhysics::YGEMassAsset* mass = new YGEPhysics::YGEMassAsset();

	smallBoxPos->addAsset(mass);

	boxPos->addChild(smallBoxPos);

	//boxPos->addAsset(box);
	space->getRootEntity()->addChild(boxPos);

	boxPos->translate3d(0,-10,-15);

}

YGESceneList GameStateX::getScenesToRender(){
	YGEScene s;
	s.first = space;
	s.second = NULL;
	YGESceneList list;
	list.push_back(s);
	return list;
}

void GameStateX::update() {
	YGECore::YGELogger::getInstance()->log("Updating Gamestate X");

	gyro->update();

	space->timeStep();


}

void GameStateX::draw(YGECore::YGEEngineCore* core) {

	// Finished Drawing The Triangle
}